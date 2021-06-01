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

processes = ['ZToMuMuTauTau_Inclusive']

tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 100   # Number of samples per configuration
nevents         = 1000  # Events per sample


username       = os.environ['USER']
arch_tag       = 'slc7_amd64_gcc700'
cmssw_tag_gp   = 'CMSSW_10_6_0'
cmssw_tag_sim  = 'CMSSW_10_6_12'
cmssw_tag_hlt  = 'CMSSW_9_4_14_UL_patch1'
campaign       = 'UL17'
sampletype     = 'ZTo4L'


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
    'GENSIM': {
        'pset':            psetfolder+'/pset_01_gensim.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'gensim',
        'outfilenamebase': 'GENSIM',
        'pathtag':         'GENSIM/' + sampletype
    },
    'DR': {
        'pset':            psetfolder+'/pset_03_dr.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'dr',
        'outfilenamebase': 'DR',
        'infilepathtag':   'GENSIM/' + sampletype,
        'infilenamebase':  'GENSIM',
        'pathtag':         'DR/' + sampletype
    },
    'HLT': {
        'pset':            psetfolder+'/pset_04_hlt.py',
        'cmsswtag':        cmssw_tag_hlt,
        'jobnametag':      'hlt',
        'outfilenamebase': 'HLT',
        'infilepathtag':   'DR/' + sampletype,
        'infilenamebase':  'DR',
        'pathtag':         'HLT/' + sampletype
    },
    'AOD': {
        'pset':            psetfolder+'/pset_05_aod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'aod',
        'outfilenamebase': 'AOD',
        'infilepathtag':   'HLT/' + sampletype,
        'infilenamebase':  'HLT',
        'pathtag':         'AOD/' + sampletype
    },
    'MINIAOD': {
        'pset':            psetfolder+'/pset_06_miniaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'miniaod',
        'outfilenamebase': 'MINIAOD',
        'infilepathtag':   'AOD/' + sampletype,
        'infilenamebase':  'AOD',
        'pathtag':         'MINIAOD/' + sampletype
    },
    'NANOAOD': {
        'pset':            psetfolder+'/pset_07_nanoaod.py',
        'cmsswtag':        cmssw_tag_sim,
        'jobnametag':      'nanoaod',
        'outfilenamebase': 'NANOAOD',
        'infilepathtag':   'MINIAOD/' + sampletype,
        'infilenamebase':  'MINIAOD',
        'pathtag':         'NANOAOD/' + sampletype
    },
    'Tuples_GENSIM': {
        'jobnametag':      'tuples_gensim',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_GENSIM',
        'infilepathtag':   'GENSIM/' + sampletype,
        'infilenamebase':  'GENSIM',
        'pathtag':         'Tuples_GENSIM/' + sampletype,
        'tuplizer':        'Tuplizer'
    },
    'Tuples_NANOAOD': {
        'jobnametag':      'tuples_nanoaod',
        'cmsswtag':        cmssw_tag_sim,
        'outfilenamebase': 'Tuples_NANOAOD',
        'pathtag':         'Tuples_NANOAOD/' + sampletype,
        'tuplizer':        'Tuplizer_NANOAOD'
    }

}

ensureDirectory(workdir_slurm)



submit = True



EventGenerator = GensimRunner(processnames=processes, tag=tag, configs=None, lambdas=None, preferred_configurations=None, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, generatorfolder=generatorfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator.ProduceCards()
# EventGenerator.SubmitGridpacks()
# EventGenerator.MoveGridpacks()
# EventGenerator.SubmitGenerationStepSM(generation_step='GENSIM', ncores=2, runtime=(3,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='GENSIM', ncores=8, runtime=(3,00), mode='resubmit')
EventGenerator.SubmitGenerationStepSM(generation_step='DR', ncores=8, runtime=(3,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='DR', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator.SubmitGenerationStepSM(generation_step='HLT', ncores=8, runtime=(10,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='HLT', ncores=8, runtime=(10,00), mode='resubmit')
# EventGenerator.RemoveSamples(generation_step='DR')
# EventGenerator.SubmitGenerationStepSM(generation_step='AOD', ncores=4, runtime=(10,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='AOD', ncores=4, runtime=(10,00), mode='resubmit')
# EventGenerator.SubmitGenerationStepSM(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='MINIAOD', ncores=2, runtime=(5,00), mode='resubmit')
# EventGenerator.SubmitGenerationStepSM(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='new')
# EventGenerator.SubmitGenerationStepSM(generation_step='NANOAOD', ncores=1, runtime=(1,00), mode='resubmit')




#
