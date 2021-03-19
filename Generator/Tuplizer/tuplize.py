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

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from TuplizeRunner import *
from samples.Storage import *
from samples.Sample import *
from samples.Signals import *
from samples.Backgrounds import *
from samples.Data import *
from collections import OrderedDict


username = os.environ['USER']
workarea = '/work/%s' % (username)
basefolder = os.environ['LEAFPATH']
generatorpath = os.environ['GENERATORPATH']
tuplizefolder = join(generatorpath, 'Tuplizer')
sampleinfofolder = join(generatorpath, 'samples')
macrofolder = os.environ['ANALYZERPATH']

samples = OrderedDict()
data = OrderedDict()
data.update(tup for tup in datalist)
samples.update(tup for tup in datalist)

backgrounds = OrderedDict()
backgrounds.update(tup for tup in backgroundlist)
samples.update(tup for tup in backgroundlist)

signals = OrderedDict()
signals.update(tup for tup in signallist)
samples.update(tup for tup in signallist)

config_per_year = {
    '2017': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_12'
    }
}




year = '2017'
submit = False


# all
# samplenames = ['LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest']
samplenames = data.keys() + backgrounds.keys() + signals.keys()
# samplenames = sorted(data.keys()) + sorted(backgrounds.keys()) + sorted(signals.keys())
# samplenames = sorted(sorted(backgrounds.keys()) + sorted(signals.keys()))
# samplenames = sorted(sorted(signals.keys()))

# backgrounds
# samplenames = sorted(backgrounds.keys())
# samplenames = backgrounds.keys()

# data + bkg
# samplenames = sorted(backgrounds.keys()) + sorted(data.keys())

# signals
# samplenames = sorted(signals.keys())



def main():
    for samplename in samplenames:
        print green('--> Working on sample: \'%s\'' % (samplename))
    #     s = samples[samplename]
    #     Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, tuplizefolder=tuplizefolder, sampleinfofolder=sampleinfofolder, macrofolder=macrofolder, submit=submit)
    #     # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=100000, mode='new')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=100000, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(05,00), nevt_per_job=100000, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(23,00), nevt_per_job=100000, mode='resubmit')
        # Tuplizer.CreateDatasetXMLFile(update_nevt=False)
        # Tuplizer.PrintDASCrossSection(sample=s, year=year, recalculate=False)
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
                    if s.type is 'DATA':
                        samplelumi = 1.
                    elif s.xsecs[year] is not None:
                        samplelumi = float(s.nevents[year]) / float(s.xsecs[year])
                    elif s.nevents[year] is not None:
                        samplelumi = float(s.nevents[year]) # normalize to 1 pb
                    else:
                        raise ValueError('Cannot assign lumiweight for sample \'%s\', please check. Abort.')
                    newline = '        <Dataset Name="%s"                Lumi="%.10g"  Year="%s" Type="%s" Group="%s" >                 &%s;                </Dataset>\n' % (s.name, samplelumi, year, s.type, str(s.group[year]), s.name)
                    newlines.append(newline)
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



if __name__ == '__main__':
    main()
