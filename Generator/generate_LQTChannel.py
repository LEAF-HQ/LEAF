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
from collections import OrderedDict

from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR

from CrossSectionRunner import *
from GensimRunner import *

processes = ['LQTChannelTauNu_DynamicScale_VectorLQUFOFlexCorrectCouplings']
mlqs      = [100, 300, 700, 1000, 3000, 7000, 10000, 15000]
mlqs_xsec = range(100, 15001, 100)
# mlqs_xsec = range(100, 15001, 25)
# mlqs_xsec = [7000]


processes_xsec = processes
lambdas_xsec = [1.0]
betavalues_xsec = [
# {'B33R':-1.0, 'B33L':1.0, 'B32L':-0.11, 'B31L':0.0, 'B23L':0.11, 'B22L':0.02, 'B21L':0.0, 'B13L':-0.02, 'B12L':0.0, 'B11L':0.0}, # page 8 of 2109.08689, LQDM model choice
{'B33R':0.0, 'B33L':1.0, 'B32L':1.0, 'B31L':1.0, 'B23L':1.0, 'B22L':1.0, 'B21L':1.0, 'B13L':1.0, 'B12L':1.0, 'B11L':1.0}, # Democratic benchmark as discussed with Darius
{'B33R':-1.0, 'B33L':1.0, 'B32L':-0.21, 'B31L':0.0, 'B23L':0.21, 'B22L':0.03, 'B21L':0.0, 'B13L':-0.04, 'B12L':0.0, 'B11L':0.0}, # Table 2.3 (3rd section from top) in 2103.16558, using Vtd/Vts = 0.21 (PDG 2020), LH+RH
{'B33R':0.0, 'B33L':1.0, 'B32L':-0.15, 'B31L':0.0, 'B23L':0.19, 'B22L':0.014, 'B21L':0.0, 'B13L':-0.04, 'B12L':0.0, 'B11L':0.0} # Table 2.3 (1st section from top) in 2103.16558, using Vtd/Vts = 0.21 (PDG 2020), LH-only
]
# betavalues_xsec = [
# {'B33R':-1.0, 'B33L':1.0, 'B32L':-0.21, 'B31L':0.0, 'B23L':0.21, 'B22L':0.03, 'B21L':0.0, 'B13L':-0.04, 'B12L':0.0, 'B11L':0.0}, # Table 2.3 (3rd section from top) in 2103.16558, using Vtd/Vts = 0.21 (PDG 2020), LH+RH
# ]

general_settings = {
'UL17':{
    'BWCUTOFF': 15,
    'PDF':      315200
    }
}

individual_settings_xsec = []
for lamb in lambdas_xsec:
    for bv in betavalues_xsec:
        for mlq in mlqs_xsec:
            dict = OrderedDict()
            # dict keys: what to replace in cards
            # dict value tuples: (value, "name of parameter in samplename")
            dict['MLQ'] = (mlq, 'MLQ')
            dict['LAMBDA'] = (lamb, 'L')
            for key in bv:
                dict[key] = (bv[key], key)
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
sampletype     = 'LQTChannel'


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




folderstructure = {
'UL17':{
    'GENSIM': {
        'pset':            psetfolder+'/pset_01_gensim.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'gensim',
        'outfilenamebase': 'GENSIM',
        'pathtag':         'GENSIM/' + campaign + '/' + sampletype
    },
    'DR': {
        'pset':            psetfolder+'/pset_03_dr.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'dr',
        'outfilenamebase': 'DR',
        'infilepathtag':   'GENSIM/' + campaign + '/' + sampletype,
        'infilenamebase':  'GENSIM',
        'pathtag':         'DR/' + campaign + '/' + sampletype
    },
    'HLT': {
        'pset':            psetfolder+'/pset_04_hlt.py',
        'cmsswtag':        cmssw_tag_hlt,
        'jobnametag':      'hlt',
        'outfilenamebase': 'HLT',
        'infilepathtag':   'DR/' + campaign + '/' + sampletype,
        'infilenamebase':  'DR',
        'pathtag':         'HLT/' + campaign + '/' + sampletype
    },
    'AOD': {
        'pset':            psetfolder+'/pset_05_aod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'aod',
        'outfilenamebase': 'AOD',
        'infilepathtag':   'HLT/' + campaign + '/' + sampletype,
        'infilenamebase':  'HLT',
        'pathtag':         'AOD/' + campaign + '/' + sampletype
    },
    'MINIAOD': {
        'pset':            psetfolder+'/pset_06_miniaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'miniaod',
        'outfilenamebase': 'MINIAOD',
        'infilepathtag':   'AOD/' + campaign + '/' + sampletype,
        'infilenamebase':  'AOD',
        'pathtag':         'MINIAOD/' + campaign + '/' + sampletype
    }
}


}

ensureDirectory(workdir_slurm)



submit = True


CrossBRRunner = CrossSectionRunner(processnames=processes_xsec, tag=tag, individual_settings=individual_settings_xsec, general_settings=general_settings[campaign], cardfolder=cardfolder, crosssecfolder=crosssecfolder, generatorfolder=generatorfolder, mgfolder_local=mgfolder_local, workarea=workarea, cmssw_tag_sim=cmssw_tag_sim, workdir_slurm=workdir_slurm, submit=submit)
# CrossBRRunner.ProduceCards()
# CrossBRRunner.RunMG(only_resubmit=False, ncores=1, runtime=(01,00,00), maxjobs_per_proc=600)
# CrossBRRunner.ShortenCrossBR()
# CrossBRRunner.RunMG(only_resubmit=True, ignore_br=True, ncores=1, runtime=(01,00,00), maxjobs_per_proc=600)
# CrossBRRunner.ReadoutCrossBR(ignore_br=True)
CrossBRRunner.RootifyCrosssections(variables=['MLQ'], graphs_per=['LAMBDA', 'B23L'], forcepoints2d=None)
# CrossBRRunner.RootifyCrosssections(variables=['MLQ'], graphs_per=['LAMBDA', 'B23L'], forcepoints2d=get_all_combinations(preferred_configurations=preferred_configurations))
# CrossBRRunner.PlotCrosssections(overlay=['LAMBDA'], overlay_values=[None])
CrossBRRunner.PlotCrosssections(overlay=['B23L'], overlay_values=[['0p19', '0p21', '1p0']])
# CrossBRRunner.PlotCrosssections(overlay=['LAMBDA', 'B23L'], overlay_values=[['1p0', 'best'], None])
# CrossBRRunner.PlotCrosssections(overlay=None, overlay_values=None)



# EventGenerator = GensimRunner(processnames=processes, tag=tag, configs=None, lambdas=lambdas, preferred_configurations=None, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, generatorfolder=generatorfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator.ProduceCards()
# EventGenerator.SubmitGridpacks()
# EventGenerator.MoveGridpacks()
# EventGenerator.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00,00), mode='new')
# EventGenerator.SubmitGenerationStep(generation_step='GENSIM', ncores=8, runtime=(3,00,00), mode='resubmit')
# EventGenerator.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10,00), mode='new')
# EventGenerator.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10,00), mode='resubmit')
# EventGenerator.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00,00), mode='new')
# EventGenerator.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00,00), mode='resubmit')
# EventGenerator.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00,00), mode='new')
# EventGenerator.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00,00), mode='resubmit')
# EventGenerator.RemoveSamples(generation_step='DR')
# EventGenerator.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00,00), mode='new')
# EventGenerator.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00,00), mode='resubmit')
# EventGenerator.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00,00), mode='new')
# EventGenerator.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00,00), mode='resubmit')





#
