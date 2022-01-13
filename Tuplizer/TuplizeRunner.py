#! /usr/bin/env python

import os, sys, math
import numpy as np
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
import glob

from utils import *
from functions import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TTree, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from tdrstyle_all import *
import tdrstyle_all as TDR

from Samples.Sample import *
from Samples.Storage import *






class TuplizeRunner:
    def __init__(self, stage, year, sample, config, workarea, basefolder, tuplizefolder, sampleinfofolder, macrofolder, submit=False):
        self.sample = sample
        self.submit = submit
        self.stage   = stage
        self.year   = year
        self.config = config[year]
        self.workarea = workarea
        self.basefolder = basefolder
        self.tuplizefolder = tuplizefolder
        self.sampleinfofolder = sampleinfofolder
        self.macrofolder = macrofolder


    def CountEvents(self, check_missing=True):
        filedict = self.sample.get_filedict(sampleinfofolder=self.sampleinfofolder, stage=self.stage, year=self.year, check_missing=check_missing)



    def SubmitTuplize(self, ncores=1, runtime=(01,00), nevt_per_job=200000, mode='new'):
        # Submit tuplize jobs to the SLURM cluster
        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        # queue   = 'standard' if runtime[0] > 1 else 'short'      # short -- standard
        # runtime_str = '%02i:%02i:00' % runtime
        runtime_str, queue = format_runtime(runtime)
        commandfilename = ''
        if mode is 'new':        commandfilename = join(self.tuplizefolder, 'commands/tuplize_%s.txt' % (self.sample.name))
        elif mode is 'resubmit': commandfilename = join(self.tuplizefolder, 'commands/resubmit_tuplize_%s.txt' % (self.sample.name))

        samplename = self.sample.name
        filedict = self.sample.get_filedict(sampleinfofolder=self.sampleinfofolder, stage=self.stage, year=self.year)
        if filedict is False:
            return
        outfoldername = self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path


        if self.stage is 'nano':
            stagetag = 'NANOAOD'
        elif self.stage is 'mini':
            stagetag = 'MINIAOD'
        commands = []
        njobs = 0
        for filename in filedict:
            nevt_thisfile = filedict[filename]
            njobs_thisfile = int(math.ceil(float(nevt_thisfile)/nevt_per_job))
            for n in range(njobs_thisfile):
                outfilename = 'NTuples_%s_%i.root' % (stagetag, njobs+1)
                command = 'cmsRun %s type=%s infilename=%s outfilename=%s idxStart=%i idxStop=%i year=%s' % (os.path.join(self.macrofolder, 'python', 'ntuplizer_cfg.py'), self.sample.type, filename, outfilename, n*nevt_per_job, (n+1)*nevt_per_job, self.year)
                commands.append(command)
                njobs += 1

        if mode is 'new':
            missing_indices = range(len(commands)) # all
        elif mode is 'resubmit':
            print green('  --> Now checking for missing files on T3 for job \'%s\'...' % (samplename))
            missing_indices = self.sample.get_missing_tuples(sampleinfofolder=self.sampleinfofolder, stage=self.stage, year=self.year, ntuples_expected=len(commands), tuplebasename='NTuples', update_missing=True, update_all=False)

        njobs = 0
        idx = 0
        with open(commandfilename, 'w') as f:
            for command in commands:
                if idx not in missing_indices:
                    idx += 1
                    continue
                f.write(command + '\n')
                njobs += 1
                idx += 1

        slurm_max_array_size = 4000
        submit_more_arrays = True if (njobs > slurm_max_array_size) else False
        # if submit_more_arrays:
        njobs_left = njobs
        narrays = 0
        njobs_per_array = []
        if njobs == 0:
            if mode is 'resubmit':
                print green('  --> No jobs to resubmit for job %s.' % (samplename))
            else:
                print green('  --> No jobs to submit for job %s.' % (samplename))
            return

        while njobs_left > 0:
            idx_offset = slurm_max_array_size*narrays
            arrayend = min(njobs_left, slurm_max_array_size)
            njobs_per_array.append(arrayend)

            command = 'sbatch --parsable -a 1-%i -J tuplize_%s -p %s -t %s --cpus-per-task %i submit_tuplize.sh %s %s %s %s %s %i' % (arrayend, samplename, queue, runtime_str, ncores, self.config['arch_tag'], join(self.workarea, self.config['cmsswtag']), self.basefolder, outfoldername, commandfilename, idx_offset)
            if njobs > 0:
                if self.submit:
                    jobid = int(subprocess.check_output(command, shell=True))
                    print green("  --> Submitted an array of %i jobs for name %s with jobid %s"%(njobs_per_array[narrays], samplename, jobid))
                else:
                    print command
                    print yellow("  --> Would submit an array of %i jobs for name %s"%(njobs_per_array[narrays], samplename))
            njobs_left -= arrayend
            narrays += 1

    def CleanBrokenFiles(self, nevt_per_job=200000, only_check_missing=True):

        filedict = self.sample.get_filedict(sampleinfofolder=self.sampleinfofolder, stage=self.stage, year=self.year)
        if filedict is False: raise ValueError('Got invalid filedict when trying to delete broken tuples.')

        if self.stage is 'nano': stagetag = 'NANOAOD'
        elif self.stage is 'mini': stagetag = 'MINIAOD'
        njobs = 0
        for filename in filedict:
            nevt_thisfile = filedict[filename]
            njobs_thisfile = int(math.ceil(float(nevt_thisfile)/nevt_per_job))
            njobs += njobs_thisfile

        missing_indices = self.sample.get_missing_tuples(sampleinfofolder=self.sampleinfofolder, stage=self.stage, year=self.year, ntuples_expected=njobs, tuplebasename='NTuples', update_missing=only_check_missing, update_all = not only_check_missing)

        outfoldername = self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path
        missing_or_broken_tuples = [os.path.join(outfoldername, 'NTuples_%s_%s.root' % (stagetag, str(i+1))) for i in missing_indices]
        commands = []
        for f in missing_or_broken_tuples:
            command = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm %s' % (f)
            commands.append(command)


        if self.submit:
            print green('  --> Removing up to %i tuple files for sample %s.' % (len(commands), self.sample.name))
            execute_commands_parallel(commands, niceness=None)
        else:
            print yellow('  --> Would remove up to %i tuple files for sample %s.' % (len(commands), self.sample.name))
            print commands



    def CreateDatasetXMLFile(self, force_counting, count_weights=True):
        xmlfilename = join(self.macrofolder, self.sample.xmlfiles[self.year])
        inputfilepattern = join(self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path, '*.root')
        out = open(xmlfilename, 'w')
        l = list_folder_content_T2(foldername=self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path, pattern='*.root')
        print green("  --> Found %d files matching inputfilepattern for sample \'%s\'" % (len(l), self.sample.name))
        l.sort()
        commands = []

        n_genevents_sum = 0
        pbar = tqdm(l, desc="  --> Files counted")
        for filename in pbar:
            # n_genevents = 0
            # file_ok = True
            # try:
            #     f = ROOT.TFile.Open(filename)
            #     n_genevents = f.Get('AnalysisTree').GetEntriesFast()
            # except:
            #     print yellow('  --> Couldn\'t open file, skip this one: %s. Will not appear in xml file, so it\'s safe if this is not data.' % (filename))
            #     file_ok = False
            # try:
            #     f.Close()
            # except:
            #     file_ok = False
            # del f
            # n_genevents_sum += n_genevents
            n_genevents = count_genevents_in_file(filename, treename='AnalysisTree')
            if n_genevents > 0 and (n_genevents is not None):
                try:
                    if count_weights:
                        commands.append(('Counter_NANOAOD_weights %s' % (filename), filename))
                    out.write('<InputFile FileName="%s"/>\n' % filename)
                    n_genevents_sum += n_genevents
                except:
                    print yellow('  --> Couldn\'t read number of weighted events in file \'%s\', skip this one. Will not appear in XML file, so it\'s safe.' % (filename))

        # if self.sample.nevents.has_year(self.year) :
        if not force_counting:
            if self.sample.nevents.has_year(self.year):
                nevents = self.sample.nevents[self.year]
                out.write('<!-- Weighted number of events: %s -->\n' % str(nevents))
                print green('  --> Used stored number of events for sample \'%s\' in year %s: %s.' % (self.sample.name, self.year, str(nevents)))
            else:
                pass
        else:
            if count_weights:
                results = getoutput_commands_parallel(commands=commands, ncores=30, max_time=120, niceness=10)
                nevents = sum(float(r[0]) for r in results)
                out.write('<!-- Weighted number of events: %s -->\n' % str(nevents))
                if self.sample.nevents.has_year(self.year):
                    rel_diff = abs(nevents - self.sample.nevents[self.year]) / nevents
                    if rel_diff < 0.01:
                        print green('  --> Sample \'%s\' in year %s already has correct number of weighted events to be used for the lumi calculation: %s. No need for action.' % (self.sample.name, self.year, str(nevents)))
                    else:
                        print yellow('  --> Sample \'%s\' in year %s has a different number of weighted events than what we just counted (more than 1%% difference) to be used for the lumi calculation: %s. Should replace the existing number with this value or check what is going on.' % (self.sample.name, self.year, str(nevents)))
                else:
                    print yellow('  --> Sample \'%s\' in year %s has this number of weighted events to be used for the lumi calculation: %s. Should fill it in.' % (self.sample.name, self.year, str(nevents)))
            else:
                out.write('<!-- Generated number of events: %s -->\n' % str(n_genevents_sum))
                print green('  --> Only counted events, not weights. Wrote the XML file with number of generated events in sample.')


        out.close()


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
    result = []
    command = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-ls %s' % (foldername)
    list = subprocess.check_output(command, shell=True).split('\n')
    for l in list:
        filename = l.split(' ')[-1]
        if pattern is not None: # check pattern
            parser = parse.compile(pattern.replace('*', '{}'))
            tuple = parser.parse(filename)
            if tuple is not None:
                result.append(os.path.join(foldername, filename))
        else: #don't check pattern
            result.append(os.path.join(foldername, filename))
    # print len(result), result
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
