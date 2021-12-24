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
from collections import OrderedDict

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR

from CrossSectionRunner import *
from GensimRunner import *



processes_xsec = ['LQLQ']
lambdas_xsec = [1.0]

general_settings = {
'UL17':{
    'BWCUTOFF': 15,
    'PDF':      315200
    }
}

configs = []

individual_settings_xsec = []
for lamb in lambdas_xsec:
    for mlq in preferred_configurations.keys():
        for mch in preferred_configurations[mlq].keys():
            mps = preferred_configurations[mlq][mch][0]
            if mlq > 6500: # too heavy for 13 TeV collisions
                continue
            dict = OrderedDict()
            # dict keys: what to replace in cards
            # dict value tuples: (value, "name of parameter in samplename")
            dict['MLQ']    = (mlq, 'MLQ')
            dict['MCH']    = (mch, 'MCH')
            dict['MPS']    = (mps, 'MPS')
            dict['MC2']    = (int(round(2*mps - mch)), None) # delta_c2 = 2 * delta_ps => mc2 = 2mps - mch --> As done in paper, but value of mc2 doesn't matter for anomalies or relic abundance. Maybe increase to suppress this channel
            dict['MZP']    = (int(round(mlq/math.sqrt(2))), None) # as done in the paper, but doesn't really affect anomalies or relic abundance
            dict['LAMBDA'] = (lamb, 'L')
            individual_settings_xsec.append(dict)


tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 100   # Number of samples per configuration
nevents         = 1000  # Events per sample



username       = os.environ['USER']
arch_tag       = 'slc7_amd64_gcc700'
cmssw_tag_gp   = 'CMSSW_10_6_0'
cmssw_tag_sim  = 'CMSSW_10_6_12'
cmssw_tag_hlt  = 'CMSSW_9_4_14_UL_patch1'
campaign       = 'UL17'
sampletype     = 'ChiPsi'


workarea       = os.path.join('/work', username)
workdir_slurm  = os.path.join(workarea, 'workdir_slurm')
mgfolder       = os.path.join(workarea, cmssw_tag_sim, 'src', 'genproductions', 'bin', 'MadGraph5_aMCatNLO')
mgfolder_local = os.path.join(workarea, 'MG5_aMC_v2_7_2')
basefolder     = os.path.join(workarea, 'LEAF')
generatorfolder= os.path.join(basefolder, 'Generator')
gridpackfolder = os.path.join(generatorfolder, 'gridpacks', sampletype)
cardfolder     = os.path.join(generatorfolder, 'cards', sampletype)
crosssecfolder = os.path.join(generatorfolder, 'crosssections', sampletype)
psetfolder     = os.path.join(generatorfolder, 'PSets', campaign)
T2_director      = 'gsiftp://storage01.lcg.cscs.ch/'
T2_director_root = 'root://storage01.lcg.cscs.ch/'
T3_director      = 'root://t3dcachedb03.psi.ch/'
T2_path          = os.path.join('/pnfs/lcg.cscs.ch/cms/trivcat/store/user', username)
T3_path          = os.path.join('/pnfs/psi.ch/cms/trivcat/store/user', username)





ensureDirectory(workdir_slurm)



submit = True


CrossBRRunner = CrossSectionRunner(processnames=processes_xsec, tag=tag, individual_settings=individual_settings_xsec, general_settings=general_settings[campaign], cardfolder=cardfolder, crosssecfolder=crosssecfolder, generatorfolder=generatorfolder, mgfolder_local=mgfolder_local, workarea=workarea, cmssw_tag_sim=cmssw_tag_sim, workdir_slurm=workdir_slurm, submit=submit)
# CrossBRRunner.ProduceCards()
# CrossBRRunner.RunMG(only_resubmit=False, ncores=1, runtime=(01,00,00), maxjobs_per_proc=100)
# CrossBRRunner.ShortenCrossBR()
# CrossBRRunner.RunMG(only_resubmit=True, ncores=1, runtime=(01,00,00), maxjobs_per_proc=50)

CrossBRRunner.ReadoutCrossBR(ignore_br=True)
# CrossBRRunner.RootifyCrosssections(variables=['MPS'], graphs_per=['L', 'MLQ'], forcepoints2d=None)
# CrossBRRunner.RootifyCrosssections(variables=['MLQ', 'MCH'], graphs_per=['L'], forcepoints2d=get_all_combinations(preferred_configurations=preferred_configurations))

# CrossBRRunner.PlotCrosssections(variables=['MPS'], overlay=['MLQ', 'L'], overlay_values=[['1720', '3520', '7210', '10000'], ['1']])
# CrossBRRunner.PlotCrosssections(variables=['MLQ', 'MCH'], overlay=None, overlay_values=None)
# CrossBRRunner.PlotCrosssections(variables=['MLQ', 'MPS'], overlay=None, overlay_values=None)


#
