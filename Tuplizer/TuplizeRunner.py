#! /usr/bin/env python

import os, sys, math, parse
import numpy as np
import subprocess

from utils import *
from functions import *

from Samples.Sample import *
from Samples.Storage import *

from Submitter.UserSpecificSettings import UserSpecificSettings


class TuplizeRunner:
    def __init__(self, stage, year, sample, config, workarea, submit=False):
        self.sample = sample
        self.submit = submit
        self.stage  = stage
        self.year   = year
        self.config = config
        self.workarea = workarea
        ensureDirectory(self.workarea)
        user_settings = UserSpecificSettings(os.getenv('USER'))
        user_settings.LoadJSON()
        self.cluster = user_settings.Get('cluster')


    def CountEvents(self, check_missing=True):
        filedict = self.sample.get_filedict(sampleinfofolder=self.workarea, stage=self.stage, year=self.year, check_missing=check_missing)


    def SubmitTuplize(self, ncores=1, runtime=(01,00), nevt_per_job=200000, mode='new'):
        # Submit tuplize jobs to the SLURM cluster
        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        # queue   = 'standard' if runtime[0] > 1 else 'short'      # short -- standard
        # runtime_str = '%02i:%02i:00' % runtime
        runtime_str, queue = format_runtime(runtime)
        samplename = self.sample.name
        joboutput = os.path.join(self.workarea,'joboutput',samplename+'_'+self.year)
        ensureDirectory(joboutput)

        filedict = self.sample.get_filedict(sampleinfofolder=self.workarea, stage=self.stage, year=self.year)
        if not filedict:
            return

        outfoldername = self.sample.tuplepaths[self.year].get_path()
        stagetag = self.stage.upper()+'AOD'

        commands = []
        njobs = 0
        for filename, nevt_thisfile in filedict.items():
            njobs_thisfile = int(math.ceil(float(nevt_thisfile)/nevt_per_job))
            for n in range(njobs_thisfile):
                outfilename = 'NTuples_%s_%i.root' % (stagetag, njobs+1)
                command = 'cmsRun %s type=%s infilename=%s outfilename=%s idxStart=%i idxStop=%i year=%s' % (os.path.join(os.getenv('ANALYZERPATH'), 'python', 'ntuplizer_cfg.py'), self.sample.type, filename, outfilename, n*nevt_per_job, (n+1)*nevt_per_job, self.year)
                for obj in ['standard', 'pfcands', 'triggerobjects', 'extrajets', 'allgenparticles']:
                    command += ' '+obj+'='+str(obj in self.sample.contents[self.year])+' '
                commands.append(command)
                njobs += 1

        if mode is 'new':
            missing_indices = range(len(commands)) # all
        elif mode is 'resubmit':
            print green('  --> Now checking for missing files on T3 for job \'%s\'...' % (samplename))
            missing_indices = self.sample.get_missing_tuples(sampleinfofolder=self.workarea, stage=self.stage, year=self.year, ntuples_expected=len(commands), tuplebasename='NTuples', update_missing=True)
            njobs = len(missing_indices)

        if njobs == 0:
            if mode is 'resubmit':
                print green('  --> No jobs to resubmit for job %s.' % (samplename))
            else:
                print green('  --> No jobs to submit for job %s.' % (samplename))
            return

        if 'slurm' in self.cluster.lower():
            ensureDirectory(self.sample.tuplepaths[self.year].get_path(is_complete=True).replace('root://', 'gsiftp://'), use_se=True)
            idx = 0
            commandfilename = os.path.join(joboutput, '%stuplize_%s.txt' % ('resubmit_' if mode is 'resubmit' else '', samplename))
            with open(commandfilename, 'w') as f:
                for command in commands:
                    if idx in missing_indices:
                        f.write(command + '\n')
                    idx += 1
            slurm_max_array_size = 4000
            submit_more_arrays = True if (njobs > slurm_max_array_size) else False
            # if submit_more_arrays:
            njobs_left = njobs
            narrays = 0
            njobs_per_array = []

            while njobs_left > 0:
                idx_offset = slurm_max_array_size*narrays
                arrayend = min(njobs_left, slurm_max_array_size)
                njobs_per_array.append(arrayend)

                command = 'sbatch --parsable -a 1-%i -J tuplize_%s -p %s -t %s --cpus-per-task %i --chdir %s submit_tuplize.sh %s %s %s %s %s %i' % (arrayend, samplename, queue, runtime_str, ncores, os.path.join(self.workarea,'joboutput', samplename+'_'+self.year), self.config['arch_tag'], os.path.join(os.path.join(os.environ['CMSSW_BASE'], '..'), self.config['cmsswtag']), os.environ['LEAFPATH'], outfoldername.replace('root://', 'gsiftp://'), commandfilename, idx_offset)
                if njobs > 0:
                    if self.submit:
                        jobid = int(subprocess.check_output(command, shell=True))
                        print green("  --> Submitted an array of %i jobs for name %s with jobid %s"%(njobs_per_array[narrays], samplename, jobid))
                    else:
                        print command
                        print yellow("  --> Would submit an array of %i jobs for name %s"%(njobs_per_array[narrays], samplename))
                njobs_left -= arrayend
                narrays += 1
        elif 'htcondor' in self.cluster.lower():
            from Submitter.CondorBase import CondorBase
            CB = CondorBase(JobName=samplename)
            CB.CreateJobInfo()
            CB.ModifyJobInfo('outdir', joboutput+'/')
            # https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRABPrepareLocal
            CB.ModifyJobInfo('x509userproxy', '/user/'+os.getenv('USER')+'/tmp/x509up')
            CB.ModifyJobInfo('use_x509userproxy', 'True')
            CB.ModifyJobInfo('transfer_executable', 'False')
            jobs = {'executables': [], 'arguments':[]}
            ensureDirectory(outfoldername, use_se=('/pnfs' in outfoldername))
            for idx, command in enumerate(commands):
                if not idx in missing_indices:
                    continue
                exe = command.split()[0]
                arg = command.strip(exe).replace('outfilename=', 'outfilename='+outfoldername+'/' )
                jobs['executables'].append(os.path.join(list(filter(lambda x: os.path.isfile(os.path.join(x,exe)) ,os.environ.get("PATH").split(':')))[0],exe))
                jobs['arguments'].append(arg)
            if self.submit:
                CB.SubmitManyJobs(job_args=jobs['arguments'], job_exes=jobs['executables'])
                jobid = int(CB.JobInfo['ClusterId'])
                print green('  --> Submitted array of %i jobs for sample %s. JobID: %i' % (njobs, samplename, jobid))
            else:
                for job_id, exe in enumerate(jobs['executables']):
                    print yellow("  --> Would submit job: %s %s"%(exe, jobs['arguments'][job_id]))

    def CleanBrokenFiles(self, nevt_per_job=200000):

        outfoldername = self.sample.tuplepaths[self.year].get_path()

        filedict = self.sample.get_filedict(sampleinfofolder=self.workarea, stage=self.stage, year=self.year)
        if not filedict:
            raise ValueError('Got invalid filedict when trying to delete broken tuples.')

        stagetag = self.stage.upper()+'AOD'

        njobs = 0
        nevents_expected_per_ntuple = {}
        for filename in filedict:
            nevt_thisfile = filedict[filename]
            njobs_thisfile = int(math.ceil(float(nevt_thisfile)/nevt_per_job))
            for n in range(njobs_thisfile):
                # get the number of events expected in each ntuple file, later we will compare against this number to make sure we completely finished ntuplizing this file
                nevents_expected_per_ntuple[os.path.join(outfoldername, 'NTuples_%s_%i.root' % (stagetag, njobs+1))] = min(nevt_thisfile, (n+1)*nevt_per_job) - n*nevt_per_job
                njobs += 1


        missing_indices = self.sample.get_missing_tuples(sampleinfofolder=self.workarea, stage=self.stage, year=self.year, ntuples_expected=njobs, tuplebasename='NTuples', update_missing=True, nevents_expected_per_ntuple=nevents_expected_per_ntuple)

        missing_or_broken_tuples = [os.path.join(outfoldername, 'NTuples_%s_%s.root' % (stagetag, str(i+1))) for i in missing_indices]
        commands = ['LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm '+f for f in missing_or_broken_tuples]

        if self.submit:
            print green('  --> Removing up to %i tuple files for sample %s.' % (len(commands), self.sample.name))
            execute_commands_parallel(commands, niceness=None)
        else:
            print yellow('  --> Would remove up to %i tuple files for sample %s.' % (len(commands), self.sample.name))
            print commands



    def CreateDatasetXMLFile(self, force_counting, count_weights=True, treename='AnalysisTree'):
        xmlfilename = os.path.join(os.environ['LEAFPATH'], self.sample.xmlfiles[self.year])
        ensureDirectory(xmlfilename[:xmlfilename.rfind('/')])

        list_folder_content = [filename for filename in list_folder_content_T2(foldername=self.sample.tuplepaths[self.year].get_path(), pattern='*.root')]
        print green("  --> Found %d files matching inputfilepattern for sample \'%s\'" % (len(list_folder_content), self.sample.name))

        nevents_stored = OrderedDict()
        nevents_stored['das'] = self.sample.get_var_for_year('nevents_das', self.year) if self.sample.nevents_das.has_year(self.year) else None
        nevents_stored['generated'] = self.sample.get_var_for_year('nevents_generated', self.year) if self.sample.nevents_generated.has_year(self.year) else None
        nevents_stored['weighted'] = self.sample.get_var_for_year('nevents_weighted', self.year) if self.sample.nevents_weighted.has_year(self.year) else None

        for mode, nevents in nevents_stored.items():
            if nevents is None:
                print yellow(' --> Sample \'%s\' in year %s does not have number of %s events stored. Should fill it in.' % (self.sample.name, self.year, mode))

        if force_counting:
            nevents_new = {'generated': None, 'weighted': None}
            commands = [(('Counter_Entries %s %s' % (filename, treename), filename)) for filename in list_folder_content]
            results = getoutput_commands_parallel(commands=commands, ncores=30, max_time=120, niceness=10)
            nevents_new['generated'] = sum(float(r[0]) for r in results if r[0].strip('\n').replace('.','').isdigit())
            missing_files = [r[1] for r in results if not r[0].strip('\n').strip('.').isdigit()]
            if count_weights:
                commands = [(('Counter_Entries_Weights %s' % (filename), filename)) for filename in list_folder_content]
                results = getoutput_commands_parallel(commands=commands, ncores=30, max_time=120, niceness=10)
                nevents_new['weighted'] = sum(float(r[0]) for r in results if r[0].strip('\n').replace('.','').isdigit())
                missing_files = [r[1] for r in results if not r[0].strip('\n').replace('.','').isdigit()]
            else:
                print green('  --> Only counted events, not weights.')

            for mode, nevents in nevents_new.items():
                if nevents_stored[mode] is not None and nevents is not None:
                    rel_diff = abs(1 - nevents_stored[mode] / nevents)
                    if rel_diff < 0.01:
                        print green('  --> Sample \'%s\' in year %s already has correct number of %s events to be used for the lumi calculation: %s. No need for action.' % (self.sample.name, self.year, mode, str(nevents)))
                        continue
                if nevents is not None:
                    print yellow('  --> Sample \'%s\' in year %s has a different number of %s events (%s) than what we just counted (more than 1%% difference) to be used for the lumi calculation: %s. Should replace the existing number with this value or check what is going on.' % (self.sample.name, self.year, mode, str(nevents_stored[mode]), str(nevents)))
                    nevents_stored[mode] = nevents

        with open(xmlfilename, 'w') as out:
            for filename in list_folder_content:
                if force_counting:
                    if filename in missing_files: continue
                out.write('<InputFile FileName="%s"/>\n' % filename)
            for mode, nevents in nevents_stored.items():
                if nevents:
                    out.write('<!-- %s number of events: %s -->\n' % (mode.capitalize(), str(nevents)))


    def PrintDASCrossSection(self, sample, year, recalculate=False):
        xsec = None
        if self.stage is 'nano':
            stagetag = 'NANOAOD'
            director = sample.nanopaths[year].director
        elif self.stage is 'mini':
            stagetag = 'MINIAOD'
            director = sample.minipaths[year].director

        if not recalculate and sample.xsecs[year] is not None:
            print yellow('--> Sample \'%s\' in year %s already has a cross section filled in. Because \'recalculate\' is not set, skip.' % (sample.name, year))
            return
        if self.stage is 'nano' and isinstance(sample.nanopaths[year], Storage_DAS):
            print green('--> Sample \'%s\' in year %s is a NanoAOD dataset from DAS. Going to calculate its cross section * filter efficiency' % (sample.name, year))
            (minipath, primary_name, campaigntag, tiertag) = get_mini_parts_from_nano_name(sample.nanopaths[year].path)
        elif self.stage is 'mini' and isinstance(sample.minipaths[year], Storage_DAS):
            print green('--> Sample \'%s\' in year %s is a MiniAOD dataset from DAS. Going to calculate its cross section * filter efficiency' % (sample.name, year))
            (minipath, primary_name, campaigntag, tiertag) = get_mini_parts_from_mini_name(sample.minipaths[year].path)

        else:
            print yellow('--> Sample \'%s\' in year %s is not a dataset from DAS. Skip.' % (sample.name, year))
            return


        cmsrun_command = get_dasxsec_cmsrun_command(minipath=minipath, director=director)

        cmsrun_output = subprocess.check_output(cmsrun_command, shell=True).split('\n') #
        for l in cmsrun_output:
            if l.startswith('After filter: final cross section'):
                print l
                xsec = float(l.split('=')[1].split(' ')[1])
                break
        print green('  --> Final cross section: \'%s\': %f' % (year, xsec))


def list_folder_content_T2(foldername, pattern=None):
    command = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-ls %s' % (foldername)
    files = subprocess.check_output(command, shell=True).split('\n')

    # check pattern
    if pattern is not None:
        files = list(filter(lambda x: parse.compile(pattern.replace('*', '{}')).parse(x.split(' ')[-1]) is not None, files))

    result = sorted([os.path.join(foldername, l.split(' ')[-1]) for l in files])

    return result

def get_mini_parts_from_nano_name(nanopath):
    primary_name = nanopath.split('/')[1]
    campaigntag  = nanopath.split('/')[2].split('-')[0].replace('Nano', 'Mini')
    tiertag      = nanopath.split('/')[3].replace('NANO', 'MINI')
    dasgocommand = 'dasgoclient --limit=0 -query="dataset dataset=/%s/*%s*/%s"' % (primary_name, campaigntag, tiertag)
    output = subprocess.check_output(dasgocommand, shell=True).split('\n')
    minipath = [x.strip() for x in output][0]
    return (minipath, primary_name, campaigntag, tiertag)

def get_mini_parts_from_mini_name(nanopath):
    primary_name = nanopath.split('/')[1]
    campaigntag  = nanopath.split('/')[2].split('-')[0]
    tiertag      = nanopath.split('/')[3]
    dasgocommand = 'dasgoclient --limit=0 -query="dataset dataset=/%s/*%s*/%s"' % (primary_name, campaigntag, tiertag)
    output = subprocess.check_output(dasgocommand, shell=True).split('\n')
    minipath = [x.strip() for x in output][0]
    return (minipath, primary_name, campaigntag, tiertag)



def get_dasxsec_cmsrun_command(minipath, director):
    dasgocommand = 'dasgoclient --limit=100 -query="file dataset=%s"' % (minipath)
    print dasgocommand
    files = "/store"+subprocess.check_output(dasgocommand, shell=True).replace("\n",",").split("/store",1)[1]
    files = files.strip(',')
    result = 'cmsRun PSets/pset_xsecanalyzer.py inputFiles=\"%s\" maxEvents=%i  2>&1 | tee xsec_%s.log' % (files, 1e6, minipath.split('/')[1])
    # print result

    return result
