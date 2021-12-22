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

processes_psipsi = ['PsiPsiToLQChi']
# mlqs_psipsi     = [1000, 2500, 4000, 5500, 7000, 8500, 10000]
mlqs_psipsi     = [1000, 4000, 7000, 10000]
mchs_exp_psipsi = [2.0, 2.33, 2.66, 3.0, 3.33]
# lambdas_psipsi  = [1.0, 'best']
lambdas_psipsi  = [1.0] # to reasonable precision, the Psi->LQ+DM decay kinematics do not depend on lambda


mass_configurations_psipsi = []
for mlq in mlqs_psipsi:
    prefmlq = find_closest(sorted(preferred_configurations.keys()), mlq)
    for exp in mchs_exp_psipsi:
        mch = find_closest(sorted(preferred_configurations[prefmlq].keys()), 10**exp)
        config = {'mlq': prefmlq, 'mch': mch}
        mass_configurations_psipsi.append(config)



# processes_xsec = ['LQLQ', 'LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi', 'PsiPsi']
processes_xsec = ['PsiPsi']
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
            if mps > 6500: # too heavy for 13 TeV collisions
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


CrossBRRunner = CrossSectionRunner(processnames=processes_xsec, tag=tag, individual_settings=individual_settings_xsec, general_settings=general_settings[campaign], cardfolder=cardfolder, crosssecfolder=crosssecfolder, generatorfolder=generatorfolder, mgfolder_local=mgfolder_local, workarea=workarea, cmssw_tag_sim=cmssw_tag_sim, workdir_slurm=workdir_slurm, submit=submit)
# CrossBRRunner.ProduceCards()
# CrossBRRunner.RunMG(only_resubmit=False, ncores=1, runtime=(01,00,00), maxjobs_per_proc=50)
# CrossBRRunner.ShortenCrossBR()
# CrossBRRunner.RunMG(only_resubmit=True, ncores=1, runtime=(01,00,00), maxjobs_per_proc=50)

# CrossBRRunner.ReadoutCrossBR(ignore_br=True)
# CrossBRRunner.RootifyCrosssections(variables=['MPS'], graphs_per=['L', 'MLQ'], forcepoints2d=None)
# CrossBRRunner.RootifyCrosssections(variables=['MLQ', 'MCH'], graphs_per=['L'], forcepoints2d=get_all_combinations(preferred_configurations=preferred_configurations))

# CrossBRRunner.PlotCrosssections(variables=['MPS'], overlay=['MLQ', 'L'], overlay_values=[['1720', '3520', '7210', '10000'], ['1']])
# CrossBRRunner.PlotCrosssections(variables=['MLQ', 'MCH'], overlay=None, overlay_values=None)
# CrossBRRunner.PlotCrosssections(variables=['MLQ', 'MPS'], overlay=None, overlay_values=None)






# EventGenerator_psipsi = GensimRunner(processnames=processes_psipsi, sampletype=sampletype, tag=tag, configs=mass_configurations_psipsi, lambdas=lambdas_psipsi, preferred_configurations=preferred_configurations, workdir_slurm=workdir_slurm, workarea=workarea, basefolder=basefolder, cardfolder=cardfolder, mgfolder=mgfolder, generatorfolder=generatorfolder, gridpackfolder=gridpackfolder, arch_tag=arch_tag, cmssw_tag_gp=cmssw_tag_gp, T2_director=T2_director, T2_path=T2_path, T2_director_root=T2_director_root, T3_director=T3_director, T3_path=T3_path, campaign=campaign, folderstructure=folderstructure, maxindex=maxindex, nevents=nevents, submit=submit)
# EventGenerator_psipsi.ProduceCards()
# EventGenerator_psipsi.SubmitGridpacks()
# EventGenerator_psipsi.MoveGridpacks()
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='GENSIM', ncores=2, runtime=(3,00,00), mode='resubmit')
# EventGenerator_psipsi.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10,00), mode='new')
# EventGenerator_psipsi.SubmitTuplize(generation_step='Tuples_GENSIM', ncores=1, runtime=(00,10,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='DR', ncores=8, runtime=(10,00,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='HLT', ncores=8, runtime=(10,00,00), mode='resubmit')
# EventGenerator_psipsi.RemoveSamples(generation_step='DR')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='AOD', ncores=4, runtime=(10,00,00), mode='resubmit')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00,00), mode='new')
# EventGenerator_psipsi.SubmitGenerationStep(generation_step='MINIAOD', ncores=2, runtime=(5,00,00), mode='resubmit')

#
