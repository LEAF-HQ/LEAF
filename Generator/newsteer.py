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

processes_lqlq_sm = ['LQLQToBTau']
mlqs_lqlq_sm     = [1000, 1400, 1800, 2200, 2600]
# mchs_exp_lqlq_sm = [2.0, 2.33, 2.66, 3.0, 3.33, 3.66, 4.0, 4.33]
# mchs_exp_lqlq_sm = [2.0, 2.66, 3.33, 4.0, 4.33]
mchs_exp_lqlq_sm = [2.0] # to reasonable precision, the LQ->btau decay kinematics do not depend on DM/Psi masses
lambdas_lqlq_sm  = [1.0, 'best']

processes_lqlq_dark = ['LQLQToBTauPsiChi', 'LQLQToPsiChi']
# processes_lqlq_dark = ['LQLQToPsiChi']
mlqs_lqlq_dark     = [1000, 1400, 1800, 2200, 2600]
# mchs_exp_lqlq_dark = [2.0, 2.33, 2.66, 3.0, 3.33, 3.66, 4.0, 4.33] #Too many! do a coarser grid before!
mchs_exp_lqlq_dark = [2.0, 2.66, 3.33, 4.0, 4.33]
lambdas_lqlq_dark  = [1.0, 'best']

processes_psipsi = ['PsiPsiToLQChi']
# mlqs_psipsi     = [1000, 2500, 4000, 5500, 7000, 8500, 10000]
mlqs_psipsi     = [1000, 4000, 7000, 10000]
mchs_exp_psipsi = [2.0, 2.33, 2.66, 3.0, 3.33]
# lambdas_psipsi  = [1.0, 'best']
lambdas_psipsi  = [1.0] # to reasonable precision, the Psi->LQ+DM decay kinematics do not depend on lambda


mass_configurations_lqlq_dark = []
for mlq in mlqs_lqlq_dark:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_lqlq_dark:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_lqlq_dark.append(config)

mass_configurations_lqlq_sm = []
for mlq in mlqs_lqlq_sm:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_lqlq_sm:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_lqlq_sm.append(config)


mass_configurations_psipsi = []
for mlq in mlqs_psipsi:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_psipsi:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_psipsi.append(config)



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
basefolder     = workarea + '/LEAF'
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
tuple_path       = workarea + '/Tuples/' + campaign + '/GENSIM/ChiPsi'



folderstructure = {
    'GENSIM': {
        'pset':            psetfolder+'/pset_01_gensim.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'gensim',
        'outfilenamebase': 'GENSIM',
        'pathtag':         'GENSIM/ChiPsi'
    },
    'DR': {
        'pset':            psetfolder+'/pset_03_dr.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'dr',
        'outfilenamebase': 'DR',
        'infilepathtag':   'GENSIM/ChiPsi',
        'infilenamebase':  'GENSIM',
        'pathtag':         'DR/ChiPsi'
    },
    'HLT': {
        'pset':            psetfolder+'/pset_04_hlt.py',
        'cmsswtag':        cmssw_tag_hlt,
        'jobnametag':      'hlt',
        'outfilenamebase': 'HLT',
        'infilepathtag':   'DR/ChiPsi',
        'infilenamebase':  'DR',
        'pathtag':         'HLT/ChiPsi'
    },
    'AOD': {
        'pset':            psetfolder+'/pset_05_aod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'aod',
        'outfilenamebase': 'AOD',
        'infilepathtag':   'HLT/ChiPsi',
        'infilenamebase':  'HLT',
        'pathtag':         'AOD/ChiPsi'
    },
    'MINIAOD': {
        'pset':            psetfolder+'/pset_06_miniaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'miniaod',
        'outfilenamebase': 'MINIAOD',
        'infilepathtag':   'AOD/ChiPsi',
        'infilenamebase':  'AOD',
        'pathtag':         'MINIAOD/ChiPsi'
    },
    'NANOAOD': {
        'pset':            psetfolder+'/pset_07_nanoaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'nanoaod',
        'outfilenamebase': 'NANOAOD',
        'infilepathtag':   'MINIAOD/ChiPsi',
        'infilenamebase':  'MINIAOD',
        'pathtag':         'NANOAOD/ChiPsi'
    },
    # 'FLAT': {
    #     'pset':            psetfolder+'/pset_08_flat.py',
    #     'cmsswtag':        cmssw_tag_sim,
    #     'jobnametag':      'flat',
    #     'outfilenamebase': 'FLAT',
    #     'infilepathtag':   'NANOAOD/ChiPsi',
    #     'infilenamebase':  'NANOAOD',
    #     'pathtag':         'FLAT/ChiPsi'
    # },
    'Tuples_GENSIM': {
        'jobnametag':      'tuples_gensim',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_GENSIM',
        'infilepathtag':   'GENSIM/ChiPsi',
        'infilenamebase':  'GENSIM',
        'pathtag':         'Tuples_GENSIM/ChiPsi',
        'tuplizer':        'Tuplizer'
    },
    'Tuples_NANOAOD': {
        'jobnametag':      'tuples_nanoaod',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_NANOAOD',
        # 'infilepathtag':   'FLAT/ChiPsi',
        # 'infilenamebase':  'FLAT',
        'pathtag':         'Tuples_NANOAOD/ChiPsi',
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



EventGenerator_lqlq_sm = GensimRunner(processnames=processes_lqlq_sm, tag=tag, configs=mass_configurations_lqlq_sm, lambdas=lambdas_lqlq_sm, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_lqlq_sm.ProduceCards()
# EventGenerator_lqlq_sm.SubmitGridpacks()
# EventGenerator_lqlq_sm.MoveGridpacks()
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='GENSIM', ncores=8, runtime=(3,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='new')
# EventGenerator_lqlq_sm.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_sm.RemoveSamples(generation_step='DR')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='new')
EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='resubmit')



EventGenerator_lqlq_dark = GensimRunner(processnames=processes_lqlq_dark, tag=tag, configs=mass_configurations_lqlq_dark, lambdas=lambdas_lqlq_dark, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_lqlq_dark.ProduceCards()
# EventGenerator_lqlq_dark.SubmitGridpacks()
# EventGenerator_lqlq_dark.MoveGridpacks()
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00), mode='new')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='GENSIM', ncores=8, runtime=(3,00), mode='resubmit')
# EventGenerator_lqlq_dark.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='new')
# EventGenerator_lqlq_dark.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='resubmit')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_dark.RemoveSamples(generation_step='DR')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='new')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='new')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='resubmit')
# EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='new')
EventGenerator_lqlq_dark.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='resubmit')


EventGenerator_psipsi = GensimRunner(processnames=processes_psipsi, tag=tag, configs=mass_configurations_psipsi, lambdas=lambdas_psipsi, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_psipsi.ProduceCards()
# EventGenerator_psipsi.SubmitGridpacks()
# EventGenerator_psipsi.MoveGridpacks()
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00), mode='resubmit')
# EventGenerator_psipsi.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='new')
# EventGenerator_psipsi.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_psipsi.RemoveSamples(generation_step='DR')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='new')
EventGenerator_psipsi.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='resubmit')





#
