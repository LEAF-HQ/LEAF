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

from samples.Sample import *






class TuplizeRunner:
    def __init__(self, year, sample, config, workarea, basefolder, gensimfolder, submit=False):
        self.sample = sample
        self.submit = submit
        self.year   = year
        self.config = config[year]
        self.workarea = workarea
        self.basefolder = basefolder
        self.gensimfolder = gensimfolder

        # self.sample.get_info(year)
        # self.sample.get_var_for_year('xsecs', year)
        # self.sample.get_var_for_year('nanopaths', year)
        # self.sample.get_var_for_year('tuplepaths', year)

    def SubmitTuplize(self, ncores=1, runtime=(01,00), nevt_per_job=200000, mode='new'):
        # Submit tuplize jobs to the SLURM cluster
        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        queue   = 'wn' if runtime[0] > 1 else 'quick'      # quick -- wn
        runtime_str = '%02i:%02i:00' % runtime
        commandfilename = ''
        if mode is 'new':        commandfilename = join(self.gensimfolder, 'commands/tuplize_%s.txt' % (self.sample.name))
        elif mode is 'resubmit': commandfilename = join(self.gensimfolder, 'commands/resubmit_tuplize_%s.txt' % (self.sample.name))

        filelist = self.sample.nanopaths[self.year].filelist
        samplename = self.sample.name
        print green('--> Working on sample \'%s\'' % (samplename))
        outfoldername = self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path

        # split jobs such that at most nevt_per_job per job are processed
        commands = []
        for i, filename in enumerate(filelist):
            # get number of events
            command = 'Counter_NANOAOD %s' % (filename)
            commands.append((command, filename))
        outputs = getoutput_commands_parallel(commands=commands, max_time=10)
        newlist = []
        for o in outputs:
            nevt = int(o[0].split('\n')[0])
            filename = o[1]
            newlist.append((filename, int(math.ceil(float(nevt)/nevt_per_job))))

        commands = []
        njobs = 0
        for tuple in newlist:
            filename = tuple[0]
            ns = tuple[1]
            for n in range(ns):
                outfilename = 'Tuples_NANOAOD_%i.root' % (njobs+1)
                command = '%s %s %s %i %i' % ('Tuplizer_NANOAOD', filename, outfilename, n*nevt_per_job, (n+1)*nevt_per_job)
                commands.append(command)
                njobs += 1


        if mode is 'new':
            missing_indices = range(len(commands)) # all
        elif mode is 'resubmit':
            print green('--> Now checking for missing files on T3 for job \'%s\'...' % (samplename))
            missing_indices = findMissingFilesT3(filepath=self.sample.tuplepaths[self.year].path, filename_base='Tuples_NANOAOD', maxindex=len(commands), generation_step='Tuples_NANOAOD') # only the missing ones -- only works if tuplizing into a new directory

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
        command = 'sbatch -a 1-%i -J tuplize_%s -p %s -t %s --cpus-per-task %i submit_tuplize_nanoaod.sh %s %s %s %s %s' % (njobs, samplename, queue, runtime_str, ncores, self.config['arch_tag'], join(self.workarea, self.config['cmsswtag']), self.basefolder, outfoldername, commandfilename)
        if njobs > 0:
            if self.submit:
                os.system(command)
                print green("  --> Submitted an array of %i jobs for name %s"%(njobs, samplename))
            else:
                print command
                print yellow("  --> Would submit an array of %i jobs for name %s"%(njobs, samplename))
        else:
            if mode is 'resubmit':
                print green('  --> No jobs to resubmit for job %s.' % (samplename))
            else:
                print green('  --> No jobs to submit for job %s.' % (samplename))
