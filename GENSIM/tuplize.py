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


# all
# samplenames = sorted(samples.keys())

# backgrounds
samplenames = sorted(backgrounds.keys())

# data + bkg
# samplenames = ['DATA_Tau_B', 'DATA_Tau_C', 'DATA_Tau_D', 'DATA_Tau_E', 'DATA_Tau_F', 'TTToSemiLeptonic', 'TTTo2L2Nu', 'TTToHadronic', 'WJetsToLNu', 'DYJetsToLNu', 'ST_tch_top', 'ST_tch_antitop', 'ST_sch', 'ST_tW_top', 'ST_tW_antitop']

# only data
# samplenames = ['DATA_Tau_B', 'DATA_Tau_C', 'DATA_Tau_D', 'DATA_Tau_E', 'DATA_Tau_F']

# signals
# samplenames = sorted(signals.keys())
# samplenames = ['LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_Lbest', 'LQLQToPsiChi_MLQ1360_MPS513_MC1457_Lbest', 'PsiPsiToLQChi_MLQ7030_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0', 'LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ1000_MPS117_MC1100_Lbest', 'LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ2620_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ1360_MPS513_MC1457_Lbest', 'LQLQToBTauPsiChi_MLQ2170_MPS507_MC1457_Lbest', 'LQLQToBTau_MLQ1000_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ1810_MPS508_MC1457_Lbest', 'LQLQToBTauPsiChi_MLQ2170_MPS507_MC1457_L1p0', 'PsiPsiToLQChi_MLQ3970_MPS505_MC1457_L1p0', 'LQLQToPsiChi_MLQ1810_MPS508_MC1457_L1p0', 'LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest', 'PsiPsiToLQChi_MLQ10000_MPS1052_MC1977_L1p0', 'PsiPsiToLQChi_MLQ7030_MPS2445_MC12089_L1p0', 'LQLQToPsiChi_MLQ1360_MPS513_MC1457_L1p0', 'PsiPsiToLQChi_MLQ3970_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ2170_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_Lbest', 'PsiPsiToLQChi_MLQ3970_MPS2551_MC12089_L1p0', 'PsiPsiToLQChi_MLQ10000_MPS2342_MC12089_L1p0', 'PsiPsiToLQChi_MLQ10000_MPS504_MC1457_L1p0', 'LQLQToBTau_MLQ1810_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ2620_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ2170_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ2170_MPS507_MC1457_L1p0', 'LQLQToBTauPsiChi_MLQ2620_MPS506_MC1457_Lbest', 'LQLQToBTau_MLQ1360_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ1810_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ2620_MPS506_MC1457_Lbest', 'LQLQToPsiChi_MLQ1810_MPS508_MC1457_Lbest', 'LQLQToPsiChi_MLQ2620_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ2620_MPS506_MC1457_L1p0', 'LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_Lbest', 'LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ1360_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ3970_MPS244_MC1214_L1p0', 'PsiPsiToLQChi_MLQ3970_MPS1106_MC1977_L1p0', 'PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0', 'PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0', 'PsiPsiToLQChi_MLQ10000_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ2620_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ2170_MPS507_MC1457_Lbest', 'LQLQToPsiChi_MLQ1360_MPS117_MC1100_Lbest', 'PsiPsiToLQChi_MLQ7030_MPS504_MC1457_L1p0', 'LQLQToBTauPsiChi_MLQ1360_MPS513_MC1457_L1p0', 'LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0', 'LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_Lbest', 'LQLQToPsiChi_MLQ2620_MPS506_MC1457_L1p0', 'PsiPsiToLQChi_MLQ7030_MPS1071_MC1977_L1p0', 'LQLQToBTauPsiChi_MLQ1810_MPS508_MC1457_L1p0', 'LQLQToPsiChi_MLQ1810_MPS117_MC1100_Lbest', 'LQLQToBTau_MLQ2170_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ7030_MPS244_MC1214_L1p0', 'LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_L1p0', 'LQLQToPsiChi_MLQ1810_MPS117_MC1100_L1p0', 'PsiPsiToLQChi_MLQ10000_MPS244_MC1214_L1p0']


year = '2017'
submit = True

def main():
    for samplename in samplenames:
        s = samples[samplename]
        Tuplizer = TuplizeRunner(sample=s, year=year, config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, macrofolder=macrofolder, submit=submit)
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=200000, mode='new')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=200000, mode='resubmit')
        # Tuplizer.CreateDatasetXMLFile()
        Tuplizer.PrintDASCrossSection(sample=s, year=year, recalculate=False)
    # create_default_config(samplenames=samplenames, year='2017', configoutname=join(macrofolder, 'LQDM', 'config', 'Default.xml'))












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



if __name__ == '__main__':
    main()
