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
import argparse

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

parser = argparse.ArgumentParser(description='newsteer.py')

parser.add_argument('-d','--dry', action = 'store_true', help = 'Run in dry mode (just displaying WP but not creating workspaces)')
parser.add_argument('-p','--noproxy', action = 'store_true', help = 'Do not renew voms proxy.')

options = parser.parse_args()

processName = []
n_batches = 1 # number of batches with nevents each
n_start = 0 # change this to the number of existing batches if you want to generate more events at a later point
procname_base = 'ProductionTauhTestFullProd'
for idx in range(n_start, n_batches):
    processName.append('_'.join([procname_base, str(idx)]))
print processName

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



tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 1000 #4000   # Number of samples per configuration #TODO: put here 1000
nevents         = 300000  # Events per sample


username       =  os.environ['USER']
arch_tag       = 'slc7_amd64_gcc700' # Scram arch 
cmssw_tag      = 'CMSSW_10_2_21'
campaign       = 'B-parking2018'


workarea       = '/work/'+ username + "/software/Analysis/leaf"
workdir_slurm  = workarea + '/workdir_slurm' # Will be created 
mgfolder       = workarea + '/' + cmssw_tag + '/src/genproductions/bin/MadGraph5_aMCatNLO' # For madgraph 
mgfolder_local = workarea + '/' + 'MG5_aMC_v2_7_2' # for madgraph
basefolder     = workarea + '/LEAF'
macrofolder    = basefolder + '/macros'
gensimfolder   = basefolder + '/Generator'
gridpackfolder = gensimfolder + '/gridpacks/ChiPsi' # For Madgraph 
cardfolder     = gensimfolder + '/cards/ChiPsi' # For Madgraph 
crosssecfolder = gensimfolder + '/crosssections/ChiPsi' # For Madgraph 
psetfolder     = gensimfolder + '/PSets/' + campaign # Where the cfg.py files are for cmsRun 
T2_director      = 'gsiftp://storage01.lcg.cscs.ch/'
T2_director_root = 'root://storage01.lcg.cscs.ch/'
T3_director      = 'root://t3dcachedb03.psi.ch/'
T2_path          = '/pnfs/lcg.cscs.ch/cms/trivcat/store/user/'+ username
T3_path          = '/pnfs/psi.ch/cms/trivcat/store/user/'+ username
tuple_path       = workarea + '/Tuples/' + campaign + '/GENSIM/ChiPsi'



folderstructure = {
    'GENSIM': {
        'pset':            psetfolder+'/BPH-RunIIFall18GS-BtoDstarTauNuSig_cfg.py',
        'cmsswtag':        cmssw_tag,
        'jobnametag':      'gensim',
        'outfilenamebase': 'GENSIM',
        'pathtag':         'GENSIM/BtoDstarTauNu'
    },
    'DR': {
        'pset':            psetfolder+'/step2.py',
        'cmsswtag':        cmssw_tag,
        'jobnametag':      'dr',
        'outfilenamebase': 'DR',
        'infilepathtag':   'GENSIM/BtoDstarTauNu',
        'infilenamebase':  'GENSIM',
        'pathtag':         'DR/BtoDstarTauNu' 
    },
#    'HLT': {
#        'pset':            psetfolder+'/pset_04_hlt.py',
#        'cmsswtag':        cmssw_tag_hlt,
#        'jobnametag':      'hlt',
#        'outfilenamebase': 'HLT',
#        'infilepathtag':   'DR/BtoDstarTauNu',
#        'infilenamebase':  'DR',
#        'pathtag':         'HLT/BtoDstarTauNu'
#    },
    'AOD': {
        'pset':            psetfolder+'/step3.py',
        'cmsswtag':        cmssw_tag,
        'jobnametag':      'aod',
        'outfilenamebase': 'AOD',
        'infilepathtag':   'DR/BtoDstarTauNu',
        'infilenamebase':  'DR',
        'pathtag':         'AOD/BtoDstarTauNu'
    },
    'MINIAOD': {
        'pset':            psetfolder+'/step4.py',
        'cmsswtag':        cmssw_tag,
        'jobnametag':      'miniaod',
        'outfilenamebase': 'MINIAOD',
        'infilepathtag':   'AOD/BtoDstarTauNu',
        'infilenamebase':  'AOD',
        'pathtag':         'MINIAOD/BtoDstarTauNu'
    },
#    'NANOAOD': {
#        'pset':            psetfolder+'/pset_07_nanoaod.py',
#        'cmsswtag':        cmssw_tag,
#        'jobnametag':      'nanoaod',
#        'outfilenamebase': 'NANOAOD',
#        'infilepathtag':   'MINIAOD/BtoDstarTauNu',
#        'infilenamebase':  'MINIAOD',
#        'pathtag':         'NANOAOD/BtoDstarTauNu'
#    },
    # 'FLAT': {
    #     'pset':            psetfolder+'/pset_08_flat.py',
    #     'cmsswtag':        cmssw_tag,
    #     'jobnametag':      'flat',
    #     'outfilenamebase': 'FLAT',
    #     'infilepathtag':   'NANOAOD/BtoDstarTauNu',
    #     'infilenamebase':  'NANOAOD',
    #     'pathtag':         'FLAT/BtoDstarTauNu'
    # },
#    'Tuples_GENSIM': {
#        'jobnametag':      'tuples_gensim',
#        'cmsswtag':        cmssw_tag,
#        'outfilenamebase': 'Tuples_GENSIM',
#        'infilepathtag':   'GENSIM/BtoDstarTauNu',     
#        'infilenamebase':  'GENSIM',
#        'pathtag':         'Tuples_GENSIM/BtoDstarTauNu',
#        'tuplizer':        'Tuplizer'          
#    },
#    'Tuples_NANOAOD': {
#        'jobnametag':      'tuples_nanoaod',
#        'cmsswtag':        cmssw_tag,
#        'outfilenamebase': 'Tuples_NANOAOD',
#        # 'infilepathtag':   'FLAT/BtoDstarTauNu',
#        # 'infilenamebase':  'FLAT',
#        'pathtag':         'Tuples_NANOAOD/BtoDstarTauNu',
#        'tuplizer':        'Tuplizer_NANOAOD'
#    }

}

ensureDirectory(workdir_slurm)


if (not options.noproxy): 
    os.system("voms-proxy-init  --voms cms --valid 200:00:00")


submit = not options.dry



EventGenerator_lqlq_sm = GensimRunner(processnames=processName, tag=tag, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, gensimfolder=gensimfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_lqlq_sm.ProduceCards()
# EventGenerator_lqlq_sm.SubmitGridpacks()
# EventGenerator_lqlq_sm.MoveGridpacks()
#EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='GENSIM', ncores=1, runtime=(12,00), mode='new') # could in principle be decreased by a factor 4 (or the num of events per job increased)
#EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='GENSIM', ncores=1, runtime=(12,00), mode='resubmit') #168
#EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='DR', ncores=4, runtime=(12,00), mode='new')
EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='DR', ncores=1, runtime=(20,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator_lqlq_sm.RemoveSamples(generation_step='DR')
#EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='AOD', ncores=2, runtime=(12,00), mode='new')
EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(12,00), mode='resubmit')
#EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(12,00), mode='new')
EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(12,00), mode='resubmit')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='new')
# EventGenerator_lqlq_sm.SubmitGenerationStep(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='resubmit')





#
