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

from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR

from CrossSectionRunner import *
from GensimRunner import *

# mass_configurations = [
#     # MPS will automatically be taken from 'preferred_configurations'
#     {'mlq': 1000, 'mch': 427},
#     {'mlq': 1000, 'mch': 912},
#     {'mlq': 1900, 'mch': 427},
#     {'mlq': 1900, 'mch': 794},
# ]

processes_lqlq = ['LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi']
mlqs_lqlq     = [1000, 1400, 1800, 2200, 2600]
mchs_exp_lqlq = [2.0, 2.33, 2.66, 3.0, 3.33, 3.66, 4.0, 4.33]
lambdas_lqlq  = [1.0, 'best']

processes_psipsi = ['PsiPsiToLQChi']
mlqs_psipsi     = [1000, 2500, 4000, 5500, 7000, 8500, 10000]
mchs_exp_psipsi = [2.0, 2.33, 2.66, 3.0, 3.33]
lambdas_psipsi  = [1.0, 'best']


mass_configurations_lqlq = []
for mlq in mlqs_lqlq:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_lqlq:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_lqlq.append(config)


mass_configurations_psipsi = []
for mlq in mlqs_psipsi:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_psipsi:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_psipsi.append(config)
print mass_configurations_psipsi, len(mass_configurations_psipsi)



processes_xsec = ['LQLQ', 'LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi', 'PsiPsi']
lambdas_xsec = [1.0, 'best']



tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 100   # Number of samples per configuration
nevents         = 1000  # Events per sample


username       = 'areimers'
arch_tag       = 'slc7_amd64_gcc700'
cmssw_tag_gp   = 'CMSSW_10_6_0'
cmssw_tag_sim  = 'CMSSW_10_6_12'
cmssw_tag_hlt  = 'CMSSW_9_4_14_UL_patch1'
campaign       = 'UL17'


workarea       = '/work/'+ username
workdir_slurm  = workarea + '/workdir_slurm'
mgfolder       = workarea + '/' + cmssw_tag_sim + '/src/genproductions/bin/MadGraph5_aMCatNLO'
mgfolder_local = workarea + '/' + 'MG5_aMC_v2_7_2'
basefolder     = workarea + '/LQDM'
macrofolder    = basefolder + '/macros'
gensimfolder   = basefolder + '/GENSIM'
gridpackfolder = gensimfolder + '/gridpacks/ChiPsi'
cardfolder     = gensimfolder + '/cards/ChiPsi'
crosssecfolder = gensimfolder + '/crosssections/ChiPsi'
psetfolder     = gensimfolder + '/PSets/' + campaign
T2_director      = 'gsiftp://storage01.lcg.cscs.ch/'
T2_director_root = 'root://storage01.lcg.cscs.ch/'
T3_director      = 'root://t3dcachedb03.psi.ch/'
T2_path          = '/pnfs/lcg.cscs.ch/cms/trivcat/store/user/'+ username
T3_path          = '/pnfs/psi.ch/cms/trivcat/store/user/'+ username
tuple_path       = workarea + '/Tuples/' + campaign + '/GENSIM/LQDM'



folderstructure = {
    'GENSIM': {
        'pset':            psetfolder+'/pset_01_gensim.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'gensim',
        'outfilenamebase': 'GENSIM',
        'pathtag':         'GENSIM/LQDM'
    },
    'DR': {
        'pset':            psetfolder+'/pset_03_dr.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'dr',
        'outfilenamebase': 'DR',
        'infilepathtag':   'GENSIM/LQDM',
        'infilenamebase':  'GENSIM',
        'pathtag':         'DR/LQDM'
    },
    'HLT': {
        'pset':            psetfolder+'/pset_04_hlt.py',
        'cmsswtag':        cmssw_tag_hlt,
        'jobnametag':      'hlt',
        'outfilenamebase': 'HLT',
        'infilepathtag':   'DR/LQDM',
        'infilenamebase':  'DR',
        'pathtag':         'HLT/LQDM'
    },
    'AOD': {
        'pset':            psetfolder+'/pset_05_aod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'aod',
        'outfilenamebase': 'AOD',
        'infilepathtag':   'HLT/LQDM',
        'infilenamebase':  'HLT',
        'pathtag':         'AOD/LQDM'
    },
    'MINIAOD': {
        'pset':            psetfolder+'/pset_06_miniaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'miniaod',
        'outfilenamebase': 'MINIAOD',
        'infilepathtag':   'AOD/LQDM',
        'infilenamebase':  'AOD',
        'pathtag':         'MINIAOD/LQDM'
    },
    'NANOAOD': {
        'pset':            psetfolder+'/pset_07_nanoaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'nanoaod',
        'outfilenamebase': 'NANOAOD',
        'infilepathtag':   'MINIAOD/LQDM',
        'infilenamebase':  'MINIAOD',
        'pathtag':         'NANOAOD/LQDM'
    },
    # 'FLAT': {
    #     'pset':            psetfolder+'/pset_08_flat.py',
    #     'cmsswtag':        cmssw_tag_sim,
    #     'jobnametag':      'flat',
    #     'outfilenamebase': 'FLAT',
    #     'infilepathtag':   'NANOAOD/LQDM',
    #     'infilenamebase':  'NANOAOD',
    #     'pathtag':         'FLAT/LQDM'
    # },
    'Tuples_GENSIM': {
        'jobnametag':      'tuples_gensim',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_GENSIM',
        'infilepathtag':   'GENSIM/LQDM',
        'infilenamebase':  'GENSIM',
        'pathtag':         'Tuples_GENSIM/LQDM',
        'tuplizer':        'Tuplizer'
    },
    'Tuples_NANOAOD': {
        'jobnametag':      'tuples_nanoaod',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_NANOAOD',
        'infilepathtag':   'FLAT/LQDM',
        'infilenamebase':  'FLAT',
        'pathtag':         'Tuples_NANOAOD/LQDM',
        'tuplizer':        'Tuplizer_NANOAOD'
    }

}

ensureDirectory(workdir_slurm)



submit = True


CrossBRRunner = CrossSectionRunner(processnames=processes_xsec, tag=tag, lambdas=lambdas_xsec, cardfolder=cardfolder, crosssecfolder=crosssecfolder, gensimfolder=gensimfolder, mgfolder_local=mgfolder_local, workarea=workarea, cmssw_tag_sim=cmssw_tag_sim, workdir_slurm=workdir_slurm, submit=submit)
# CrossBRRunner.ProduceCards()
# CrossBRRunner.RunMG(only_resubmit=False, ncores=2, runtime=(01,00), maxjobs_per_proc=50)
# CrossBRRunner.ShortenCrossBR()
# CrossBRRunner.RunMG(only_resubmit=True,  ncores=4, runtime=(01,00), maxjobs_per_proc=150)
# CrossBRRunner.ReadoutCrossBR()
# CrossBRRunner.RootifyCrossBR()
# CrossBRRunner.PlotCrossBR()



EventGenerator_lqlq = GensimRunner(processnames=processes_lqlq, tag=tag, configs=mass_configurations_lqlq, lambdas=lambdas_lqlq, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_lqlq.ProduceCards()
# EventGenerator_lqlq.SubmitGridpacks()
# EventGenerator_lqlq.MoveGridpacks()
# EventGenerator_lqlq.SubmitGenerationStep(generation_step='GENSIM', runtime=(0,30), mode='new')


EventGenerator_psipsi = GensimRunner(processnames=processes_psipsi, tag=tag, configs=mass_configurations_psipsi, lambdas=lambdas_psipsi, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
EventGenerator_psipsi.ProduceCards()
# EventGenerator_psipsi.SubmitGridpacks()
# EventGenerator_psipsi.MoveGridpacks()
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='GENSIM', runtime=(0,30), mode='new')





#
