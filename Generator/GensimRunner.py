#! /usr/bin/env python

import os, sys, math
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
from utils import *
from functions import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

# from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR


class GensimRunner:
    def __init__(self, processnames, tag, configs, lambdas, preferred_configurations, workdir_slurm, workarea, basefolder, cardfolder, mgfolder, gensimfolder, gridpackfolder, arch_tag, cmssw_tag_gp, T2_director, T2_path, T2_director_root, T3_director, T3_path, campaign, folderstructure, maxindex=100, nevents=1000, submit=False):
        self.processnames = processnames
        self.tag = tag
        self.configs = configs
        self.lambdas = lambdas
        self.preferred_configurations = preferred_configurations
        self.workdir_slurm = workdir_slurm
        self.workarea = workarea
        self.basefolder = basefolder
        self.cardfolder = cardfolder
        self.mgfolder = mgfolder
        self.gensimfolder = gensimfolder
        self.gridpackfolder = gridpackfolder
        self.arch_tag = arch_tag
        self.cmssw_tag_gp = cmssw_tag_gp
        self.T2_director = T2_director
        self.T2_path = T2_path
        self.T2_director_root = T2_director_root
        self.T3_director = T3_director
        self.T3_path = T3_path
        self.campaign = campaign
        self.folderstructure = folderstructure
        self.maxindex = maxindex
        self.nevents = nevents
        self.submit = submit


    def ProduceCards(self):
        for processname in self.processnames:
            idx = 0
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
            for config in allowed_configs:
                mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                for lamb in self.lambdas:
                    if self.submit:
                        ensureDirectory(self.cardfolder+'/%s' % (processname))
                        make_card(card_template_folder=self.cardfolder, card_output_folder=self.cardfolder+'/%s' % (processname), processname=processname, tag=self.tag, mlq=mlq, mps=mps, mch=mch, lamb=lamb, verbose=False)
                        print green('--> Produced %i out of %i cards for process %s (%.2f%%).' % (idx, len(allowed_configs)*len(self.lambdas), processname, float(idx)/float(len(allowed_configs)*len(self.lambdas))*100))
                    idx += 1

            if not self.submit:
                print yellow('Would have produced %i sets of cards for process %s.' % (len(allowed_configs)*len(self.lambdas), processname))



    def SubmitGridpacks(self):
        # Submit gridpacks based on cards created above
        for processname in self.processnames:
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
                else:
                    print yellow('Skip config %s for process \'%s\'' % (config, processname))
            for config in allowed_configs:
                for lamb in self.lambdas:
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    jobname = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    # if not jobname == 'LQLQToPsiChi_MLQ2170_MPS117_MC1100_Lbest': continue
                    command = 'sbatch -J gridpacks_%s -p quick -t 01:00:00 --cpus-per-task 1 --mem=4000 submit_gridpacks.sh %s %s %s local' % (jobname, self.mgfolder, jobname, self.cardfolder+'/%s' % (processname))
                    if self.submit:
                        time.sleep(5)
                        os.system(command)
                    else: print command


        if self.submit: print green('--> Done submitting gridpacks.')
        else:      print yellow('--> Would have submitted gridpacks.')


    def MoveGridpacks(self):
        # Move gridpacks to new dir
        commands = []
        for processname in self.processnames:
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
                else:
                    print yellow('Skip config %s for process \'%s\'' % (config, processname))
            for config in allowed_configs:
                for lamb in self.lambdas:
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    jobname = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)

                    gpname = jobname + '_' + self.arch_tag + '_' + self.cmssw_tag_gp + '_tarball.tar.xz'
                    sourcefile = '%s/%s' % (self.mgfolder, gpname)
                    targetfile = '%s/%s/%s' % (self.gridpackfolder, processname, gpname)
                    ensureDirectory('%s/%s' % (self.gridpackfolder, processname))
                    command = 'mv %s %s' % (sourcefile, targetfile)
                    commands.append(command)
                    if self.submit:
                        print green('moving gridpack \'%s\'' % (gpname))
                    else:
                        print yellow('would move gridpack \'%s\'' % (gpname))
        if self.submit:
            execute_commands_parallel(commands=commands, ncores=1)
            print green('\ndone moving gridpacks')



    def SubmitGenerationStep(self, generation_step, ncores=8, runtime=(10,00), mode='new'):
        # Submit event generation jobs to the SLURM cluster

        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        runtime_str = '%02i:%02i:00' % runtime
        queue   = 'wn' if runtime[0] > 1 else 'quick'      # quick -- wn

        commandfilebase = ''
        if mode is 'new':        commandfilebase = self.gensimfolder + '/commands/%s_' % (self.folderstructure[generation_step]['jobnametag'])
        elif mode is 'resubmit': commandfilebase = self.gensimfolder + '/commands/resubmit_%s_' % (self.folderstructure[generation_step]['jobnametag'])

        # Create command file for array of jobs
        for processname in self.processnames:
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
                else:
                    print yellow('Skip config %s for process \'%s\'' % (config, processname))
            # num = 0
            for config in allowed_configs:
                for lamb in self.lambdas:
                    # if num > 0: break
                    # num += 1
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    # resubs = ['LQLQToBTau_MLQ1360_MPS4843_MC14467_L1p0', 'LQLQToPsiChi_MLQ1000_MPS244_MC1214_L1p0', 'LQLQToPsiChi_MLQ2170_MPS117_MC1100_Lbest', 'PsiPsiToLQChi_MLQ7030_MPS244_MC1214_L1p0']
                    # if not jobname in resubs: continue
                    commandfilename = commandfilebase + jobname + '.txt'
                    f = open(commandfilename, 'w')
                    indices = -1
                    if mode is 'new':
                        indices = range(self.maxindex)
                    elif mode is 'resubmit':
                        print green('--> Now checking for missing files on T2 for generation step \'%s\' of job \'%s\'...' % (generation_step, jobname))
                        indices = missing_indices = findMissingFilesT2(filepath=self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, filename_base=self.folderstructure[generation_step]['outfilenamebase'], maxindex=self.maxindex, gensimfolder=self.gensimfolder, generation_step=generation_step)

                    njobs = 0
                    for i in indices:
                        outfilename = '%s_%i.root' % (self.folderstructure[generation_step]['outfilenamebase'], i+1)
                        command = ''
                        if generation_step is not 'GENSIM':
                            infilename   = self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['infilepathtag']+'/'+jobname+'/%s_%i.root' % (self.folderstructure[generation_step]['infilenamebase'], i+1)
                            command = getcmsRunCommand(pset=self.folderstructure[generation_step]['pset'], infilename=infilename, outfilename=outfilename, N=self.nevents, ncores=ncores)
                        else:
                            infilename   = self.gridpackfolder + '/' + processname + '/' + jobname + '_' + self.arch_tag + '_' + self.cmssw_tag_gp + '_tarball.tar.xz'
                            command = getcmsRunCommand(pset=self.folderstructure[generation_step]['pset'], gridpack=infilename, outfilename=outfilename, N=self.nevents, ncores=ncores)

                        f.write(command + '\n')
                        njobs += 1

                    f.close()
                    slurmjobname = ''
                    if mode is 'new':        slurmjobname = '%s' % (self.folderstructure[generation_step]['jobnametag'])
                    elif mode is 'resubmit': slurmjobname = 'resubmit_%s' % (self.folderstructure[generation_step]['jobnametag'])
                    # jobs_per_sample_string = '%10' if mode == 'new' else ''
                    command = 'sbatch -a 1-%s -J %s -p %s -t %s --cpus-per-task %i submit_cmsRun_command.sh %s %s %s %s %s' % (str(njobs), slurmjobname+'_'+jobname, queue, runtime_str, ncores, self.gensimfolder, self.arch_tag, self.workarea+'/'+self.folderstructure[generation_step]['cmsswtag'], self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, commandfilename)
                    if njobs > 0:
                        if self.submit:
                            # print command
                            os.system(command)
                            print green("  --> Submitted an array of %i jobs for name %s"%(njobs, jobname))
                        else:
                            print command
                            print yellow("  --> Would submit an array of %i jobs"%(njobs))

                    else:
                        if mode is 'resubmit':
                            print green('  --> No jobs to resubmit.')
                        else:
                            print green('  --> No jobs to submit.')




    def SubmitTuplize(self, generation_step, ncores=1, runtime=(01,00), mode='new'):
        # Submit tuplize jobs to the SLURM cluster
        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        queue   = 'wn' if runtime[0] > 1 else 'quick'      # quick -- wn
        runtime_str = '%02i:%02i:00' % runtime
        commandfilebase = ''
        if mode is 'new':        commandfilebase = self.gensimfolder + '/commands/tuplize_%s_' % (self.folderstructure[generation_step]['jobnametag'])
        elif mode is 'resubmit': commandfilebase = self.gensimfolder + '/commands/resubmit_tuplize_%s_' % (self.folderstructure[generation_step]['jobnametag'])

        # Create command file for array of jobs
        for processname in self.processnames:
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
                else:
                    print yellow('--> Skip config %s for process \'%s\'' % (config, processname))
            # num = 0
            for config in allowed_configs:
                for lamb in self.lambdas:
                    # if num > 0: break
                    # num += 1
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    outfoldername = self.T3_director + self.T3_path + '/' + self.campaign + '/' + self.folderstructure[generation_step]['pathtag'] + '/' + jobname
                    commandfilename = commandfilebase + jobname + '.txt'
                    f = open(commandfilename, 'w')
                    indices = -1
                    if mode is 'new':        indices = range(self.maxindex)
                    # elif mode is 'resubmit': indices = missing_indices = findMissingFilesT3(outfoldername, filename_base=self.folderstructure[generation_step]['outfilenamebase'], maxindex=self.maxindex, gensimfolder=self.gensimfolder, generation_step=generation_step)
                    elif mode is 'resubmit':
                        print green('--> Now checking for missing files on T3 for job \'%s\'...' % (jobname))
                        indices = missing_indices = findMissingFilesT3(self.T3_path + '/' + self.campaign + '/' + self.folderstructure[generation_step]['pathtag'] + '/' + jobname, filename_base=self.folderstructure[generation_step]['outfilenamebase'], maxindex=self.maxindex, generation_step=generation_step)

                    njobs = 0
                    for i in indices:
                        infilename = self.T2_director_root + self.T2_path + '/' + self.folderstructure[generation_step]['infilepathtag'] + '/' + jobname + '/' + self.folderstructure[generation_step]['infilenamebase'] + '_' + str(i+1) + '.root'
                        outfilename = self.folderstructure[generation_step]['outfilenamebase'] + '_%i.root' % (i+1)
                        command = '%s %s %s' % (self.folderstructure[generation_step]['tuplizer'], infilename, outfilename)
                        f.write(command + '\n')
                        njobs += 1
                    f.close()

                    command = 'sbatch -a 1-%s -J tuplize_%s -p %s -t %s --cpus-per-task %i submit_tuplize_gensim.sh %s %s %s %s %s %s' % (str(njobs), self.folderstructure[generation_step]['jobnametag']+'_'+jobname, queue, runtime_str, ncores, self.arch_tag, self.workarea+'/'+self.folderstructure[generation_step]['cmsswtag'], self.basefolder, outfoldername, commandfilename, self.folderstructure[generation_step]['jobnametag'])
                    if njobs > 0:
                        if self.submit:
                            os.system(command)
                            print green("  --> Submitted an array of %i jobs for name %s"%(njobs, jobname))
                        else:
                            print command
                            print yellow("  --> Would submit an array of %i jobs for name %s"%(njobs, jobname))
                    else:
                        if mode is 'resubmit':
                            print green('  --> No jobs to resubmit for job %s.' % (jobname))
                        else:
                            print green('  --> No jobs to submit for job %s.' % (jobname))

    def RemoveSamples(self, generation_step):
        # Remove old samples from the T2 if they are no longer needed. This saves A LOT of space. This can run locally from the login node since it recursively deletes the entire folder.
        # Loop through samples to find all that should be deleted
        commands = []
        for processname in self.processnames:
            allowed_configs = []
            for config in self.configs:
                if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=self.preferred_configurations):
                    allowed_configs.append(config)
                else:
                    print yellow('--> Skip config %s for process \'%s\'' % (config, processname))
            for config in allowed_configs:
                for lamb in self.lambdas:
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    samplepath    = self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname
                    command       = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm -r %s' % (samplepath)
                    # print command
                    if self.submit:
                        print green('--> Will delete files from job %s for generation step %s'%(jobname, generation_step))
                    else:
                        print yellow('--> Would delete files from job %s for generation step %s'%(jobname, generation_step))
                    commands.append(command)
        if self.submit:
            execute_commands_parallel(commands=commands, niceness=None)
