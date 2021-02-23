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

from samples.Sample import *
from samples.Storage import *






class TuplizeRunner:
    def __init__(self, year, sample, config, workarea, basefolder, tuplizefolder, sampleinfofolder, macrofolder, submit=False):
        self.sample = sample
        self.submit = submit
        self.year   = year
        self.config = config[year]
        self.workarea = workarea
        self.basefolder = basefolder
        self.tuplizefolder = tuplizefolder
        self.sampleinfofolder = sampleinfofolder
        self.macrofolder = macrofolder

    def SubmitTuplize(self, ncores=1, runtime=(01,00), nevt_per_job=200000, mode='new'):
        # Submit tuplize jobs to the SLURM cluster
        if mode is not 'new' and mode is not 'resubmit':
            raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)
        queue   = 'wn' if runtime[0] > 1 else 'quick'      # quick -- wn
        runtime_str = '%02i:%02i:00' % runtime
        commandfilename = ''
        if mode is 'new':        commandfilename = join(self.tuplizefolder, 'commands/tuplize_%s.txt' % (self.sample.name))
        elif mode is 'resubmit': commandfilename = join(self.tuplizefolder, 'commands/resubmit_tuplize_%s.txt' % (self.sample.name))

        samplename = self.sample.name
        # print green('--> Working on sample \'%s\'' % (samplename))
        filedict = self.sample.get_filedict_nano(sampleinfofolder=self.sampleinfofolder, year=self.year)
        if filedict is False:
            return
        outfoldername = self.sample.tuplepaths[self.year].director+self.sample.tuplepaths[self.year].path


        commands = []
        njobs = 0
        for filename in filedict:
            nevt_thisfile = filedict[filename]
            njobs_thisfile = int(math.ceil(float(nevt_thisfile)/nevt_per_job))
            for n in range(njobs_thisfile):
                outfilename = 'Tuples_NANOAOD_%i.root' % (njobs+1)
                command = '%s %s %s %s %i %i' % ('Tuplizer_NANOAOD', self.sample.type, filename, outfilename, n*nevt_per_job, (n+1)*nevt_per_job)
                commands.append(command)
                njobs += 1


        if mode is 'new':
            missing_indices = range(len(commands)) # all
        elif mode is 'resubmit':
            print green('  --> Now checking for missing files on T3 for job \'%s\'...' % (samplename))
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
        command = 'sbatch --parsable -a 1-%i -J tuplize_%s -p %s -t %s --cpus-per-task %i submit_tuplize_nanoaod.sh %s %s %s %s %s' % (njobs, samplename, queue, runtime_str, ncores, self.config['arch_tag'], join(self.workarea, self.config['cmsswtag']), self.basefolder, outfoldername, commandfilename)
        if njobs > 0:
            if self.submit:
                jobid = int(subprocess.check_output(command, shell=True))
                print green("  --> Submitted an array of %i jobs for name %s with jobid %s"%(njobs, samplename, jobid))
            else:
                print command
                print yellow("  --> Would submit an array of %i jobs for name %s"%(njobs, samplename))
        else:
            if mode is 'resubmit':
                print green('  --> No jobs to resubmit for job %s.' % (samplename))
            else:
                print green('  --> No jobs to submit for job %s.' % (samplename))

    def CreateDatasetXMLFile(self, update_nevt, count_weights=True):
        # print self.year, self.sample.nevents.has_year(self.year)
        # print self.sample.nevents[self.year]
        xmlfilename = join(self.macrofolder, self.sample.xmlfiles[self.year])
        inputfilepattern = join(self.macrofolder, self.sample.tuplepaths[self.year].path, '*.root')
        out = open(xmlfilename, 'w')
        l = glob.glob(inputfilepattern)
        print green("  --> Found %d files matching inputfilepattern for sample \'%s\'" % (len(l), self.sample.name))
        l.sort()
        commands = []
        idx = 0
        for filename in l:
            # print filename
            idx += 1
            f = ROOT.TFile.Open(filename)
            n_genevents = 0
            try:
                n_genevents = f.Get('AnalysisTree').GetEntriesFast()
            except AttributeError:
                print yellow('  --> Couldn\'t open file, skip this one: %s. Will not appear in xml file, so it\'s safe if this is not data.' % (filename))
            f.Close()
            del f
            if n_genevents > 0:
                try:
                    if count_weights: commands.append(('Counter_NANOAOD_weights %s' % (filename), filename))
                    out.write('<InputFile FileName="%s"/>\n' % filename)
                except:
                    print yellow('  --> Couldn\'t read number of weighted events in file, skip this one. Will not appear in XML file, so it\'s safe.')

        # if self.sample.nevents.has_year(self.year) :
        if self.sample.nevents.has_year(self.year) and not update_nevt:
            nevents = self.sample.nevents[self.year]
            out.write('<!-- Weighted number of events: %s -->\n' % str(nevents))
            print green('  --> Used stored number of events for sample \'%s\' in year %s: %s.' % (self.sample.name, self.year, str(nevents)))
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
                print green('  --> Did not count events. Simply wrote the XML file with number of generated/recorded events in sample.')

            # else:
            #     if count_weights:
            #         results = getoutput_commands_parallel(commands=commands, ncores=30, max_time=120, niceness=10)
            #         nevents = sum(float(r[0]) for r in results)
            #         out.write('<!-- Weighted number of events: %s -->\n' % str(nevents))
            #         if self.sample.nevents.has_year(self.year):
            #             rel_diff = abs(nevents - self.sample.nevents[self.year]) / nevents
            #             if rel_diff < 0.01:
            #                 print green('  --> Sample \'%s\' in year %s already has correct number of weighted events to be used for the lumi calculation: %s. No need for action.' % (self.sample.name, self.year, str(nevents)))
            #             else:
            #                 print yellow('  --> Sample \'%s\' in year %s has a different number of weighted events than what we just counted (more than 1%% difference) to be used for the lumi calculation: %s. Should replace the existing number with this value or check what is going on.' % (self.sample.name, self.year, str(nevents)))
            #         else:
            #             print yellow('  --> Sample \'%s\' in year %s has this number of weighted events to be used for the lumi calculation: %s. Should fill it in.' % (self.sample.name, self.year, str(nevents)))
            #     else:
            #         print green('  --> Did not count events. Simply wrote the XML file with number of generated/recorded events in sample.')
        out.close()


    def PrintDASCrossSection(self, sample, year, recalculate=False):
        xsec = None
        if not recalculate and sample.xsecs[year] is not None:
            print yellow('--> Sample \'%s\' in year %s already has a cross section filled in. Because \'recalculate\' is not set, skip.' % (sample.name, year))
            return
        if isinstance(sample.nanopaths[year], Storage_DAS):
            print green('--> Sample \'%s\' in year %s is a dataset from DAS. Going to calculate its cross section * filter efficiency' % (sample.name, year))

            (minipath, primary_name, campaigntag, tiertag) = get_mini_parts_from_nano_name(sample.nanopaths[year].path)
            cmsrun_command = get_dasxsec_cmsrun_command(minipath=minipath, director=sample.nanopaths[year].director)

        else:
            print yellow('--> Sample \'%s\' in year %s is not a dataset from DAS. Skip.' % (sample.name, year))
            return

        # print cmsrun_command
        # cmsrun_output = subprocess.check_output(cmsrun_command, shell=True, stderr=subprocess.STDOUT).split('\n') #
        cmsrun_output = subprocess.check_output(cmsrun_command, shell=True).split('\n') #
        for l in cmsrun_output:
            if l.startswith('After filter: final cross section'):
                xsec = float(l.split('=')[1].split(' ')[1])
                break
        print green('  --> Final cross section: \'%s\': %f' % (year, xsec))




def get_mini_parts_from_nano_name(nanopath):
    primary_name = nanopath.split('/')[1]
    campaigntag  = nanopath.split('/')[2].split('-')[0].replace('Nano', 'Mini')
    tiertag      = nanopath.split('/')[3].replace('NANO', 'MINI')
    dasgocommand = 'dasgoclient --limit=0 -query="dataset dataset=/%s/*%s*/%s"' % (primary_name, campaigntag, tiertag)
    output = subprocess.check_output(dasgocommand, shell=True).split('\n')
    minipath = [x.strip() for x in output][0]
    return (minipath, primary_name, campaigntag, tiertag)



def get_dasxsec_cmsrun_command(minipath, director):
    dasgocommand = 'dasgoclient --limit=100 -query="file dataset=%s"' % (minipath)
    files = "/store"+subprocess.check_output(dasgocommand, shell=True).replace("\n",",").split("/store",1)[1]
    files = files.strip(',')
    result = 'cmsRun PSets/pset_xsecanalyzer.py inputFiles=\"%s\" maxEvents=%i  2>&1 | tee xsec_%s.log' % (files, 1e6, minipath.split('/')[1])
    print result

    return result
