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
from constants import *

from tkinter import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from TuplizeRunner import *
from samples.Storage import *
from samples.Sample import *
from samples.samples import *
from samples.Signals import *
from samples.Backgrounds import *
from samples.Data import *


username = 'areimers'
workarea = '/work/%s' % (username)
basefolder = join(workarea, 'LQDM')
gensimfolder = join(basefolder, 'GENSIM')
macrofolder = join(basefolder, 'macros')

config_per_year = {
    '2017': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_12'
    }
}


samplenames = sorted(data.keys()) + sorted(backgrounds.keys()) + sorted(signals.keys())



def run_function():
    year = var_year.get()
    action = var_action.get()
    submit = (var_submit.get() == 1)

    if year is '' or action is '':
        print '\'year\' or \'action\' not specified, please do so.'
        return
    print 'year is: %s' % year
    print 'action is: %s' % action
    if submit: print 'submit is True'
    else:      print 'submit is False'

    # options_action = ['', 'submit new', 'resubmit 1h', 'resubmit 5h', 'resubmit 23h', 'Create dataset XML file', 'Print DAS cross section', 'Create default config file from samples']
    if action == 'submit new':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=100000, mode='new')

    if action == 'resubmit 1h':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=100000, mode='resubmit')

    if action == 'resubmit 5h':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.SubmitTuplize(ncores=1, runtime=(05,00), nevt_per_job=100000, mode='resubmit')

    if action == 'resubmit 23h':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.SubmitTuplize(ncores=1, runtime=(23,00), nevt_per_job=100000, mode='resubmit')

    if action == 'Create dataset XML file':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.CreateDatasetXMLFile()

    if action == 'Print DAS cross section':
        for samplename in samplenames:
            s = samples[samplename]
            Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
            Tuplizer.PrintDASCrossSection(sample=s, year=year, recalculate=False)

    if action == 'Create default config file from samples':
        create_default_config(samplenames=samplenames, year='2017', configoutname=join(macrofolder, 'LQDM', 'config', 'Default.xml'))







def create_default_config(samplenames, year, configoutname='default_config.xml'):
    templatefilename = join(macrofolder, 'templates', 'config_template.xml')
    newlines = []
    with open(templatefilename, 'r') as f:
        lines = f.readlines()
        found_entity = False
        found_configuration = False
        found_dataset_start = False
        found_dataset_end = False
        for i, line in enumerate(lines):
            newline = line
            if '<!ENTITY' in line and not 'TargetLumi' in line and not 'outfilepath' in line :
                if found_entity: continue
                found_entity = True

                # replace this line with all the entities we need according to our samples
                for samplename in samplenames:
                    s = samples[samplename]
                    newline = '<!ENTITY %s SYSTEM "%s" >\n' % (s.name, join(macrofolder, s.xmlfiles[year]))
                    newlines.append(newline)
            elif '<Configuration' in line:
                if found_configuration: continue
                found_configuration = True
                newline = line.replace('$MYTOOLNAME', '#REPLACEME')
                newlines.append(newline)
            elif '<Dataset' in line and not found_dataset_end:
                if found_dataset_start: continue
                found_dataset_start = True
                for samplename in samplenames:
                    s = samples[samplename]
                    samplelumi = float(s.nevents[year]) / float(s.xsecs[year]) if s.xsecs[year] is not None else float(s.nevents[year])
                    newline = '        <Dataset Name="%s" Lumi="%.1f"  Type="%s" >\n' % (s.name, samplelumi, s.type)
                    newlines.append(newline)
                    newline2 = '            &%s;\n' % (s.name)
                    newlines.append(newline2)
                    newline3 = '        </Dataset>\n'
                    newlines.append(newline3)
            elif '</Dataset>' in line:
                found_dataset_end = True #don't append a newline, was already handeled
            elif found_dataset_start and not found_dataset_end:
                continue #skip the intermediate lines, they were already handeled
            else:
                newlines.append(line)
    # print newlines
    with open(configoutname, 'w') as f:
        for l in newlines:
            f.write(l)
    print green('--> created default config file \'%s\'' % (configoutname))


if  __name__ == '__main__':

    options_year = ['', '2017']
    options_action = ['', 'submit new', 'resubmit 1h', 'resubmit 5h', 'resubmit 23h', 'Create dataset XML file', 'Print DAS cross section', 'Create default config file from samples']


    window = Tk()
    window.title('Tuplizer GUI')
    # window.resizable(width=False, height=False)

    window.rowconfigure(0, minsize=100, weight=1)
    window.rowconfigure(1, minsize=40, weight=0)
    window.rowconfigure(2, minsize=100, weight=1)
    window.columnconfigure(0, minsize=500, weight=1)
    window.columnconfigure(1, minsize=500, weight=1)
    window.columnconfigure(2, minsize=200, weight=1)

    var_year = StringVar(window)
    var_year.set(options_year[0]) # default value
    var_action = StringVar(window)
    var_action.set(options_action[0]) # default value
    var_submit = IntVar()
    var_submit.set(False)

    lbl_year = Label(master=window, text='Choose the year to run')
    lbl_year.grid(row=0, column=0, sticky="s")
    lbl_action = Label(master=window, text='Choose the step to run')
    lbl_action.grid(row=0, column=1, sticky="s")
    menu_year = OptionMenu(window, var_year, *options_year)
    menu_year.grid(row=1, column=0, padx=10, pady=10, sticky='ew')
    menu_action = OptionMenu(window, var_action, *options_action)
    menu_action.grid(row=1, column=1, padx=10, pady=10, sticky='ew')

    box_submit = Checkbutton(window, text="submit", variable=var_submit).grid(row=1, column=2)

    button_run = Button(window, text="Run", command=run_function)
    button_run.grid(row=2, column=0, columnspan=2, padx=20, pady=20, sticky='nsew')
    button_exit = Button(window, text="Exit", command=window.destroy)
    button_exit.grid(row=2, column=2, padx=20, pady=20, sticky='nsew')

    mainloop()










#
