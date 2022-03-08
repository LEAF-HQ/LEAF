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
    def __init__(self, processnames, tag, individual_settings, general_settings, workdir_slurm, workarea, basefolder, cardfolder, mgfolder, generatorfolder, gridpackfolder, arch_tag, cmssw_tag_gp, T2_director, T2_path, T2_director_root, T3_director, T3_path, campaign, folderstructure, maxindex=100, nevents=1000, submit=False):
        self.processnames = processnames
        self.tag = tag
        self.individual_settings = individual_settings
        self.general_settings = general_settings
        self.workdir_slurm = workdir_slurm
        self.workarea = workarea
        self.basefolder = basefolder
        self.cardfolder = cardfolder
        self.mgfolder = mgfolder
        self.generatorfolder = generatorfolder
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
            for individual_setting in self.individual_settings:
                if self.submit:
                    make_card_flex(card_template_folder=self.cardfolder, card_output_folder=self.cardfolder+'/%s' % (processname), processname=processname, tag=self.tag, general_settings=self.general_settings, individual_setting=individual_setting, verbose=False)
                    if idx % 20 is 0:
                        print green('--> Produced %i out of %i set(s) of cards for process %s (%.2f%%).' % (idx+1, len(self.individual_settings), processname, float(idx+1)/float(len(self.individual_settings))*100))
                    idx += 1
            if not self.submit:
                print yellow('Would have produced %i cards for process %s.' % (len(self.individual_settings), processname))



    def SubmitGridpacks(self, runtime=(01,00,00), ncores=1):
        runtime_str, queue = format_runtime(runtime)

        # Submit gridpacks based on cards created above
        for processname in self.processnames:
            gpfolder = os.path.join(self.gridpackfolder, processname)
            ensureDirectory(gpfolder)
            for individual_setting in self.individual_settings:
                jobname = get_jobname_flex(processname=processname, ordered_dict=individual_setting, tag=self.tag)
                command = 'sbatch -J gridpacks_%s -p %s -t %s --cpus-per-task %i %s/submit_gridpacks.sh %s %s %s %s local' % (jobname, queue, runtime_str, ncores, self.generatorfolder, self.mgfolder, jobname, os.path.join(self.cardfolder, processname), gpfolder)
                if self.submit:
                    time.sleep(1)
                    os.system(command)
                else: print command

        if self.submit: print green('--> Done submitting gridpacks.')
        else:      print yellow('--> Would have submitted gridpacks.')




    def SubmitGenerationStep(self, generation_step, ncores=8, runtime=(10,00,00), mode='new'):
        # Submit event generation jobs to the SLURM cluster

        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        runtime_str, queue = format_runtime(runtime)

        commandfilebase = ''
        if mode is 'new':        commandfilebase = self.generatorfolder + '/commands/%s_' % (self.folderstructure[generation_step]['jobnametag'])
        elif mode is 'resubmit': commandfilebase = self.generatorfolder + '/commands/resubmit_%s_' % (self.folderstructure[generation_step]['jobnametag'])

        # Create command file for array of jobs
        for processname in self.processnames:
            for individual_setting in self.individual_settings:
                jobname = get_jobname_flex(processname=processname, ordered_dict=individual_setting, tag=self.tag)
                commandfilename = commandfilebase + jobname + '.txt'
                f = open(commandfilename, 'w')
                indices = -1
                if mode is 'new':
                    indices = range(self.maxindex)
                elif mode is 'resubmit':
                    print green('--> Now checking for missing files on T2 for generation step \'%s\' of job \'%s\'...' % (generation_step, jobname))
                    indices = missing_indices = findMissingRootFiles(filename_base=os.path.join(self.T2_director_root+self.T2_path,self.folderstructure[generation_step]['pathtag'], jobname, self.folderstructure[generation_step]['outfilenamebase']), maxindex=self.maxindex, treename='Events')

                njobs = 0
                for i in indices:
                    outfilename = '%s_%i.root' % (self.folderstructure[generation_step]['outfilenamebase'], i+1)
                    command = ''
                    if generation_step is not 'GENSIM':
                        infilename   = self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['infilepathtag']+'/'+jobname+'/%s_%i.root' % (self.folderstructure[generation_step]['infilenamebase'], i+1)
                        command = getcmsRunCommand(pset=self.folderstructure[generation_step]['pset'], infilename=infilename, outfilename=outfilename, N=-1, ncores=ncores)
                    else:
                        infilename   = self.gridpackfolder + '/' + processname + '/' + jobname + '_' + self.arch_tag + '_' + self.cmssw_tag_gp + '_tarball.tar.xz'
                        command = getcmsRunCommand(pset=self.folderstructure[generation_step]['pset'], gridpack=infilename, outfilename=outfilename, N=self.nevents, ncores=ncores, lumiblock=i+1)
                    f.write(command + '\n')
                    njobs += 1

                f.close()
                slurmjobname = ''
                if mode is 'new':        slurmjobname = '%s' % (self.folderstructure[generation_step]['jobnametag'])
                elif mode is 'resubmit': slurmjobname = 'resubmit_%s' % (self.folderstructure[generation_step]['jobnametag'])

                # command = 'sbatch -a 1-%s -J %s -p %s -t %s --exclude t3wn[49,50,54,40,44,39] --cpus-per-task %i %s/submit_cmsRun_command.sh %s %s %s %s %s' % (str(njobs), slurmjobname+'_'+jobname, queue, runtime_str, ncores, self.generatorfolder, self.generatorfolder, self.arch_tag, self.workarea+'/'+self.folderstructure[generation_step]['cmsswtag'], self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, commandfilename)
                command = 'sbatch -a 1-%s -J %s -p %s -t %s --cpus-per-task %i %s/submit_cmsRun_command.sh %s %s %s %s %s' % (str(njobs), slurmjobname+'_'+jobname, queue, runtime_str, ncores, self.generatorfolder, self.generatorfolder, self.arch_tag, self.workarea+'/'+self.folderstructure[generation_step]['cmsswtag'], self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, commandfilename)
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




    def RemoveSamples(self, generation_step):
        # Remove old samples from the T2 if they are no longer needed. This saves A LOT of space. This can run locally from the login node since it recursively deletes the entire folder.
        # Loop through samples to find all that should be deleted
        commands = []
        for processname in self.processnames:
            if self.configs is not None:
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
                        if self.submit:
                            print green('--> Will delete files from job %s for generation step %s'%(jobname, generation_step))
                        else:
                            print yellow('--> Would delete files from job %s for generation step %s'%(jobname, generation_step))
                        commands.append(command)

            else:
                jobname = get_jobname(processname=processname, mlq=None, mps=None, mch=None, lamb=None, tag=self.tag)
                samplepath    = self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname
                command       = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm -r %s' % (samplepath)
                if self.submit:
                    print green('--> Will delete files from job %s for generation step %s'%(jobname, generation_step))
                else:
                    print yellow('--> Would delete files from job %s for generation step %s'%(jobname, generation_step))
                commands.append(command)
        if self.submit:
            execute_commands_parallel(commands=commands, niceness=None)
