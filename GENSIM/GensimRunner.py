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
    def __init__(self, processnames, tag, configs, lambdas, preferred_configurations, workdir_slurm, workarea, cardfolder, mgfolder, gensimfolder, gridpackfolder, arch_tag, cmssw_tag_gp, T2_director, T2_path, folderstructure, maxindex=100, nevents=1000, submit=False):
        self.processnames = processnames
        self.tag = tag
        self.configs = configs
        self.lambdas = lambdas
        self.preferred_configurations = preferred_configurations
        self.workdir_slurm = workdir_slurm
        self.workarea = workarea
        self.cardfolder = cardfolder
        self.mgfolder = mgfolder
        self.gensimfolder = gensimfolder
        self.gridpackfolder = gridpackfolder
        self.arch_tag = arch_tag
        self.cmssw_tag_gp = cmssw_tag_gp
        self.T2_director = T2_director
        self.T2_path = T2_path
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



    def SubmitGenerationStep(self, generation_step, runtime=(10,00), mode='new'):
        # Submit event generation jobs to the SLURM cluster

        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)

        ncores  = 8
        if generation_step is 'NANOAOD' or generation_step is 'MINIAOD':
            ncores = int(ncores / 2)
        elif generation_step is 'FLAT':
            ncores = int(ncores / 4)
        if generation_step is 'NANOAOD' or generation_step is 'FLAT':
            runtime[0] = min(int(float(runtime[0])/10.), 1)
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
            num = 0
            for config in allowed_configs:
                for lamb in self.lambdas:
                    if num > 0: break
                    num += 1
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=self.preferred_configurations, config=config)
                    # if lamb == 'best':
                    #     lamb = preferred_lambdas[mlq]
                    jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    commandfilename = commandfilebase + jobname + '.txt'
                    f = open(commandfilename, 'w')
                    indices = -1
                    if mode is 'new':        indices = range(self.maxindex)
                    elif mode is 'resubmit': indices = missing_indices = findMissingFilesT2(filepath=T2_director+T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, filename_base=self.folderstructure[generation_step]['outfilenamebase'], maxindex=self.maxindex, gensimfolder=self.gensimfolder)

                    njobs = 0
                    for i in indices:
                        outfilename = '%s_%i.root' % (self.folderstructure[generation_step]['outfilenamebase'], i+1)
                        command = ''
                        if generation_step is not 'GENSIM':
                            infilename   = T2_director+T2_path+'/'+self.folderstructure[generation_step]['infilepathtag']+'/'+jobname+'/%s_%i.root' % (self.folderstructure[generation_step]['infilenamebase'], i+1)
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
                    command = 'sbatch -a 1-%s -J %s -p %s -t %s --cpus-per-task %i submit_cmsRun_command.sh %s %s %s %s %s' % (str(njobs), slurmjobname+'_'+jobname, queue, runtime_str, ncores, self.gensimfolder, self.arch_tag, self.workarea+'/'+self.folderstructure[generation_step]['cmsswtag'], self.T2_director+self.T2_path+'/'+self.folderstructure[generation_step]['pathtag']+'/'+jobname, commandfilename)
                    if njobs > 0:
                        if self.submit:
                            os.system(command)
                            print green("Submitted an array of %i jobs for name %s"%(njobs, jobname))
                        else:
                            print command
                            print yellow("Would submit an array of %i jobs"%(njobs))

                    else:
                        if mode is 'resubmit':
                            print green('No jobs to resubmit.')
                        else:
                            print green('No jobs to submit.')



#
