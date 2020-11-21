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
# TDR.writeExtraText = False
# TDR.cmsText = ''
# TDR.lumi_13TeV = ''


# ----------------
# General settings
# ----------------

mass_configurations = [
    # MPS will automatically be taken from 'preferred_configurations'
    {'mlq': 1000, 'mch': 427},
    {'mlq': 1000, 'mch': 912},
    {'mlq': 1900, 'mch': 427},
    {'mlq': 1900, 'mch': 794},
]

processes = ['LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi', 'PsiPsiToLQChi']
processes_xsec = ['LQLQ', 'LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi', 'PsiPsiToLQChi']
# processes_xsec = ['LQLQ', 'PsiPsiToLQChi']

procname_to_latex = {
    'LQLQ': 'LQ LQ',
    'LQLQToBTau': 'LQ LQ #rightarrow b#tau b#tau',
    'LQLQToBTauPsiChi': 'LQ LQ #rightarrow b#tau #psi#chi_{1}',
    'LQLQToPsiChi': 'LQ LQ #rightarrow #psi#chi_{1} #psi#chi_{1}',
    'PsiPsiToLQChi': '#psi#psi #rightarrow LQ#chi_{1} LQ#chi_{1}'
}

decaymode_dict = {
    (5, -15): 'b #tau',
    (6, -16): 't #nu',
    (9000009, 9000007): '#psi #chi_{1}',
    (9000009, 9000008): '#psi #chi_{2}'
}

procname_to_decaymodes = {
    'LQLQToBTau': [(5, -15), (5, -15)],
    'LQLQToBTauPsiChi':  [(5, -15), (9000009, 9000007)],
    'LQLQToPsiChi':  [(9000009, 9000007), (9000009, 9000007)]
}

mlq_min = min(preferred_configurations.keys())
mlq_max = max(preferred_configurations.keys())
print mlq_max
mch_min = 999999999
mch_max = 0
for mlq in preferred_configurations.keys():
    for mch in preferred_configurations[mlq].keys():
        mch_min = min(mch_min, mch)
        mch_max = max(mch_max, mch)

all_combinations = {}
mlq_stepsize = 90
mch_exp_stepsize = 0.03
for mlq in range(mlq_min, mlq_max+mlq_stepsize, mlq_stepsize):
    all_combinations[mlq] = []
    for mch_exp in range(int(math.log(mch_min, 10)*100), int(math.log(mch_max, 10)*100) + int(mch_exp_stepsize*100), int(mch_exp_stepsize*100)):
        mch_exp = float(mch_exp / 100.)
        mch = int(round(10**(float(mch_exp))))
        all_combinations[mlq].append(mch)
# print all_combinations

# exclude combinations of process -- mass_config for processes without phase space
excluded_configurations = {}
for proc in processes_xsec:
    # if not ('PsiChi' in proc) and not (proc == 'LQLQ') and not ('PsiPsi' in proc): continue
    excl_configs = []
    for mlq in preferred_configurations.keys():
        for mch in preferred_configurations[mlq].keys():
            excl_config = {}
            excl_config['mlq'] = mlq
            excl_config['mch'] = mch
            dummy1, mps, dummy2 = get_mlq_mps_mch(excl_config)
            if 'PsiPsi' in proc:
                if mps > 13000./2.: #too heavy for 13TeV
                    excl_configs.append(excl_config)
            if 'LQLQ' in proc:
                if mlq > 13000./2.: #too heavy for 13TeV
                    excl_configs.append(excl_config)

                # now look at decay channels
                if 'PsiChi' in proc:
                    if mlq < mps + mch: #LQ cannot decay to psi+chi1
                        excl_configs.append(excl_config)
    excluded_configurations[proc] = excl_configs

preferred_lambdas = {}
for mlq in preferred_configurations.keys():
    preferred_lambdas[mlq] = float(1.1/2. * (mlq/1000.))

# lambdas = [1.0, 'best']
lambdas = [1.0]
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
gridpackfolder = gensimfolder + '/gridpacks'
cardfolder     = gensimfolder + '/cards/ChiPsi'
crosssecfolder = gensimfolder + '/crosssections/ChiPsi'
psetfolder     = gensimfolder + '/PSets/' + campaign
T2_director      = 'gsiftp://storage01.lcg.cscs.ch/'
T2_director_root = 'root://storage01.lcg.cscs.ch/'
T3_director      = 'root://t3dcachedb03.psi.ch/'
T2_path          = '/pnfs/lcg.cscs.ch/cms/trivcat/store/user/'+ username
T3_path          = '/pnfs/psi.ch/cms/trivcat/store/user/'+ username
tuple_path       = workarea + '/Tuples/' + campaign + '/GENSIM/LQDM'

colors = [kRed+4, kRed+1, kAzure-2, kOrange, kGreen-2]

configs = {
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

def main():

    make_cards         = False
    submit_gridpacks   = False
    move_gridpacks     = False
    clean_mg_area      = False

    make_cards_crossbr = False
    submit_crossbr     = False
    clean_crossbr      = False
    shorten_crossbr    = False
    resub_crossbr      = False
    readout_crossbr    = False
    rootify_crossbr    = False
    plot_crossbr       = True

    gensim             = False
    resub_gensim       = False

    dr                 = False
    resub_dr           = False

    hlt                = False
    resub_hlt          = False
    delete_dr          = False

    aod                = False
    resub_aod          = False
    delete_hlt         = False

    miniaod            = False
    resub_miniaod      = False
    delete_aod         = False

    nanoaod            = False
    resub_nanoaod      = False
    delete_miniaod     = False

    # flat               = False
    # resub_flat         = False
    # delete_nanoaod     = False

    tuplize_gen        = False
    add_gen            = False

    tuplize_nano       = False

    submit             = True

    ensureDirectory(workdir_slurm)


    # Gridpack generation
    if make_cards:       ProduceCards()
    if submit_gridpacks: SubmitGridpacks(submit=submit)
    if move_gridpacks:   MoveGridpacks(submit=submit)
    if clean_mg_area:    CleanMGArea(submit=submit)

    # Crosssection computation
    if submit_crossbr or make_cards_crossbr or shorten_crossbr or clean_crossbr or resub_crossbr or readout_crossbr or rootify_crossbr or plot_crossbr:   SubmitCrosssectionRuns(redo_cards=make_cards_crossbr, run_mg=submit_crossbr, clean_folders=clean_crossbr, shorten_crossbr=shorten_crossbr, rerun_mg=resub_crossbr, readout_crossbr=readout_crossbr, rootify_crossbr=rootify_crossbr, plot_crossbr=plot_crossbr, submit=submit)
    # if shorten_crossbr:  ShortenCrossBR()

    # GENSIM generation
    if gensim:           SubmitGenerationStep(submit=submit, generation_step='GENSIM', mode='new')
    if resub_gensim:     SubmitGenerationStep(submit=submit, generation_step='GENSIM', mode='resubmit')
    if dr:               SubmitGenerationStep(submit=submit, generation_step='DR', mode='new')
    if resub_dr:         SubmitGenerationStep(submit=submit, generation_step='DR', mode='resubmit')
    if hlt:              SubmitGenerationStep(submit=submit, generation_step='HLT', mode='new')
    if resub_hlt:        SubmitGenerationStep(submit=submit, generation_step='HLT', mode='resubmit')
    if delete_dr:        RemoveSamples(submit=submit, generation_step='DR')
    if aod:              SubmitGenerationStep(submit=submit, generation_step='AOD', mode='new')
    if resub_aod:        SubmitGenerationStep(submit=submit, generation_step='AOD', mode='resubmit')
    if delete_hlt:       RemoveSamples(submit=submit, generation_step='HLT')
    if miniaod:          SubmitGenerationStep(submit=submit, generation_step='MINIAOD', mode='new')
    if resub_miniaod:    SubmitGenerationStep(submit=submit, generation_step='MINIAOD', mode='resubmit')
    if delete_aod:       RemoveSamples(submit=submit, generation_step='AOD')
    if nanoaod:          SubmitGenerationStep(submit=submit, generation_step='NANOAOD', mode='new')
    if resub_nanoaod:    SubmitGenerationStep(submit=submit, generation_step='NANOAOD', mode='resubmit')
    if delete_miniaod:   RemoveSamples(submit=submit, generation_step='MINIAOD')
    # if flat:             SubmitGenerationStep(submit=submit, generation_step='FLAT', mode='new')
    # if resub_flat:       SubmitGenerationStep(submit=submit, generation_step='FLAT', mode='resubmit')
    # if delete_nanoaod:   RemoveSamples(submit=submit, generation_step='NANOAOD')

    # Tuple generation
    if tuplize_gen:      SubmitTuplize(submit=submit, generation_step='Tuples_GENSIM')
    if add_gen:          SubmitAdd(submit=submit, generation_step='Tuples_GENSIM')

    if tuplize_nano:     SubmitTuplize(submit=submit, generation_step='Tuples_NANOAOD')

    # continue the analysis with "macros" to plot simple files





# ----------
# Make cards
# ----------
def ProduceCards():
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue

            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                make_card(card_template_folder=cardfolder, card_output_folder=cardfolder, processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, verbose=True)
    print green('Done producing cards from templates')

def SubmitGridpacks(submit):
    # Submit gridpacks based on cards created above
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue

            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                jobname = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)

                command = 'sbatch -J gridpacks_%s -p wn -t 05:00:00 --cpus-per-task 1 submit_gridpacks.sh %s %s %s local' % (jobname, mgfolder, jobname, cardfolder)
                print command
                if submit: os.system(command)

    if submit: print green('Done submitting gridpacks.')
    else:      print yellow('Would have submitted gridpacks.')



def MoveGridpacks(submit):
    # Move gridpacks to new dir
    commands = []
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                jobname = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)

                gpname = jobname + '_' + arch_tag + '_' + cmssw_tag_gp + '_tarball.tar.xz'
                sourcefile = mgfolder + '/' + gpname
                targetfile = gridpackfolder + '/' + gpname
                command = 'mv %s %s' % (sourcefile, targetfile)
                commands.append(command)
                if submit:
                    print green('moving gridpack \'%s\'' % (gpname))
                else:
                    print yellow('would move gridpack \'%s\'' % (gpname))
    if submit:
        execute_commands_parallel(commands=commands, ncores=15)
        print green('\ndone moving gridpacks')



def CleanMGArea(submit):
    # Clean MG area from workdirs of gridpack generation
    commands = []
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                jobname   = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                command = 'rm -rf ' + mgfolder + '/' + jobname + '*'
                commands.append(command)
                if submit:
                    print green('removing MG files \'%s*\'' % (jobname))
                else:
                    print yellow('would remove MG files \'%s*\'' % (jobname))
    if submit:
        execute_commands_parallel(commands=commands, ncores=15)
        print green('\ndone cleaning up MG area')



def SubmitGenerationStep(submit, generation_step, mode='new'):
    # Submit event generation jobs to the SLURM cluster

    if mode is not 'new' and mode is not 'resubmit':
        raise ValueError('Value \'%s\' is invalid for variable \'mode\'.' % mode)

    ncores  = 8
    if generation_step is 'NANOAOD' or generation_step is 'MINIAOD':
        ncores = int(ncores / 2)
    elif generation_step is 'FLAT':
        ncores = int(ncores / 4)
    runtime_hrs = 10
    if generation_step is 'NANOAOD' or generation_step is 'FLAT':
        runtime_hrs = min(int(float(runtime_hrs)/10.), 1)
    runtime = '%i:00:00' % (runtime_hrs)
    #runtime = '10:00:00' # 01:00:00 -- 10:00:00
    queue   = 'wn' if runtime_hrs > 1 else 'quick'      # quick -- wn

    commandfilebase = ''
    if mode is 'new':        commandfilebase = gensimfolder + '/commands/%s_' % (configs[generation_step]['jobnametag'])
    elif mode is 'resubmit': commandfilebase = gensimfolder + '/commands/resubmit_%s_' % (configs[generation_step]['jobnametag'])

    # Create command file for array of jobs
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                commandfilename = commandfilebase + jobname + '.txt'
                f = open(commandfilename, 'w')
                indices = -1
                if mode is 'new':        indices = range(maxindex)
                elif mode is 'resubmit': indices = missing_indices = findMissingFilesT2(filepath=T2_director+T2_path+'/'+configs[generation_step]['pathtag']+'/'+jobname, filename_base=configs[generation_step]['outfilenamebase'], maxindex=maxindex)

                njobs = 0
                for i in indices:
                    outfilename = '%s_%i.root' % (configs[generation_step]['outfilenamebase'], i+1)
                    command = ''
                    if generation_step is not 'GENSIM':
                        infilename   = T2_director+T2_path+'/'+configs[generation_step]['infilepathtag']+'/'+jobname+'/%s_%i.root' % (configs[generation_step]['infilenamebase'], i+1)
                        command = getcmsRunCommand(pset=configs[generation_step]['pset'], infilename=infilename, outfilename=outfilename, N=nevents, ncores=ncores)
                    else:
                        infilename   = gridpackfolder + '/' + jobname + '_' + arch_tag + '_' + cmssw_tag_gp + '_tarball.tar.xz'
                        command = getcmsRunCommand(pset=configs[generation_step]['pset'], gridpack=infilename, outfilename=outfilename, N=nevents, ncores=ncores)

                    f.write(command + '\n')
                    njobs += 1

                f.close()
                slurmjobname = ''
                if mode is 'new':        slurmjobname = '%s' % (configs[generation_step]['jobnametag'])
                elif mode is 'resubmit': slurmjobname = 'resubmit_%s' % (configs[generation_step]['jobnametag'])
                command = 'sbatch -a 1-%s -J %s -p %s -t %s --cpus-per-task %i submit_cmsRun_command.sh %s %s %s %s %s' % (str(njobs), slurmjobname+'_'+jobname, queue, runtime, ncores, gensimfolder, arch_tag, workarea+'/'+configs[generation_step]['cmsswtag'], T2_director+T2_path+'/'+configs[generation_step]['pathtag']+'/'+jobname, commandfilename)
                if njobs > 0:
                    if submit:
                        os.system(command)
                        print green("Submitted an array of %i jobs for name %s"%(njobs, jobname))
                    else:
                        print command
                        print yellow("Would submit an array of %i jobs"%(njobs))

                else:
                    if mode is 'resubmit':
                        print green('No jobs to resubmit.')
                    else:
                        print green('No jobs to submit.')


def RemoveSamples(submit, generation_step):
    # Remove old samples from the T2 if they are no longer needed. This saves A LOT of space. This can run locally from the login node since it recursively deletes the entire folder.

    # Loop through samples to find all that should be deleted
    commands = []
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                if lamb == 'best':
                    lamb = preferred_lambdas[mlq]
                jobname      = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                samplepath   = T2_director+T2_path+'/'+configs[generation_step]['pathtag']+'/'+jobname
                command  = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm -r %s' % (samplepath)

                print command
                commands.append(command)

    if submit:
        execute_commands_parallel(commands=commands)






# def SubmitCrosssectionRuns(redo_cards=False, run_mg=False, shorten_crossbr=False, clean_folders=False, rerun_mg=False, readout_crossbr=False, rootify_crossbr=False, plot_crossbr=False, submit=False):
#     # Produce MG5 cards for running cross section and BR calculations
#     ncores = 2
#     maxjobs_per_proc = 100
#     runtime_hrs = 00
#     runtime_min = 45
#     runtime = '%02i:%02i:00' % (runtime_hrs, runtime_min)
#     queue   = 'wn' if runtime_hrs > 1 else 'quick'      # quick -- wn
#
#     # nprocesses = len(processes_xsec)
#     for processname in processes_xsec:
#         # Do cross sections for all configurations with MLQ < 3TeV
#         configs = []
#
#         for mlq in preferred_configurations.keys():
#             # if mlq > 6000: continue
#             for mch in preferred_configurations[mlq].keys():
#                 config = {}
#                 config['mlq'] = mlq
#                 config['mch'] = mch
#                 dummy1, mps, dummy2 = get_mlq_mps_mch(config)
#                 if not is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
#                     configs.append(config)
#
#         # loop through configs
#         if redo_cards:
#             idx = 0
#             for config in configs:
#                 for lamb in lambdas:
#                     mlq, mps, mch = get_mlq_mps_mch(config)
#                     if lamb == 'best':
#                         lamb = preferred_lambdas[mlq]
#                     make_card(card_template_folder=cardfolder+'/CrossBR', card_output_folder=cardfolder+'/CrossBR/%s' % (processname), processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, verbose=False)
#                     idx += 1
#                     if idx % 20 is 0:
#                         print green('Produced %i out of %i cards for process %s (%.2f%%).' % (idx, len(configs)*len(lambdas), processname, float(idx)/float(len(configs)*len(lambdas))*100))
#
#         if run_mg or rerun_mg:
#             if run_mg and rerun_mg:
#                 raise ValueError('Configured to run AND rerun MG at the same time. Please choose one.')
#             if rerun_mg:
#                 shortfilelist = get_filelist_crossbr(filepath=crosssecfolder+'/'+processname, short=True)
#             njobs = 0
#             commandfilename = gensimfolder + '/commands/CrossBR_%s.txt' % (processname)
#             f = open(commandfilename, 'w')
#             for config in configs:
#                 for lamb in lambdas:
#                     mlq, mps, mch = get_mlq_mps_mch(config)
#                     if lamb == 'best':
#                         lamb = preferred_lambdas[mlq]
#                     jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
#
#                     write_command = True
#                     if rerun_mg:
#                         write_command = False
#                         if len(shortfilelist) == 0:
#                             write_command = True
#                         else:
#                             param_card_shortname   = jobname+'_param_card_short.txt'
#                             crosssection_shortname = jobname+'_crosssection_short.txt'
#                             if (not (param_card_shortname in shortfilelist) or not (crosssection_shortname in shortfilelist)):
#                                 write_command = True
#                     # write to a command file the shell command: 'source run_crossbr.sh  .....' %
#                     command = 'source %s %s %s %s %s %s %s %s %i' % (gensimfolder+'/run_crossbr.sh', mgfolder_local, jobname, cardfolder+'/CrossBR/%s' % (processname), workarea + '/' + cmssw_tag_sim, workdir_slurm, crosssecfolder, processname, ncores)
#                     if write_command:
#                         # if njobs >= 20: continue
#                         f.write(command + '\n')
#                         njobs += 1
#             f.close()
#             slurmjobname = 'CrossBR_%s' % (processname)
#             command = 'sbatch --parsable -a 1-%s%%%i -J %s -p %s -t %s --cpus-per-task %i submit_crossbr_array.sh %s' % (str(njobs), maxjobs_per_proc, slurmjobname, queue, runtime, ncores, commandfilename)
#             if submit:
#                 if njobs == 0:
#                     print yellow('--> No jobs to be submitted for process %s. Continue.' % (processname))
#                     continue
#                 jobid = int(subprocess.check_output(command.split(' ')))
#                 print green("--> Submitted an array of %i jobs for process %s. Master-jobid: %i"%(njobs, processname, int(jobid)))
#             else:
#                 print command
#                 print yellow("--> Would submit an array of %i jobs for process %s"%(njobs, processname))
#
#         if shorten_crossbr:
#             # Do cross sections for all configurations with MLQ < 4TeV
#             # configs = []
#             longlist = get_filelist_crossbr(filepath=crosssecfolder+'/'+processname, short=False)
#             print green('going to shorten %i long files.' % (len(longlist)))
#             for filename in longlist:
#                 # is it the param card for the BR or the logfile for the cross section?
#                 is_param_card = True if 'param_card' in filename else False
#                 infilename = crosssecfolder+'/'+processname+'/'+filename
#                 shortfilename = join(crosssecfolder+'/'+processname+'/', filename[:-4] + '_short.txt')
#                 if not isfile(infilename):
#                     print 'logfile "%s" not found' % (infilename)
#                     continue
#                 fin = open(infilename,'r')
#                 lines = fin.readlines()
#                 erase_line = True
#                 found_systs = False
#                 found_start = False
#                 newlines = []
#                 if not is_param_card:
#                     for line in lines:
#                         if found_systs: erase_line = True # after the PDF line we don't need anything anymore
#                         if '  === Results Summary for run' in line:
#                             found_start = True
#                             erase_line = False
#                         if 'PDF variation' in line: found_systs = True
#                         if not erase_line:
#                             newlines.append(line)
#                 else:
#                     for line in lines:
#                         # start recording when finding the LQ decay
#                         if 'DECAY  9000005' in line:
#                             found_start = True
#                             erase_line = False
#                         # stop when reaching the next particle
#                         if '#      PDG        Width' in line:
#                             erase_line = True
#                         if not erase_line:
#                             newlines.append(line)
#
#                 fin.close()
#                 if (is_param_card and not found_start) or (not is_param_card and (not found_systs or not found_start)):
#                     print yellow('--> didn\'t find the summary or systematics in file %s, going to skip this file, won\'t create a shortfile, deleting the logfile.' % (infilename))
#                 elif submit:
#                     fout = open(shortfilename,'w')
#                     print green('--> Replacing long with shortened file: %s' % (shortfilename))
#                     for newline in newlines:
#                         fout.write(newline)
#                     fout.close()
#                 else:
#                     print yellow('--> Would replace long with shortened file %s' % (shortfilename))
#
#                 if submit:
#                     os.remove(infilename)
#             if submit: check_shortfiles(filepath=crosssecfolder+'/'+processname)
#
#
#         if readout_crossbr:
#
#             total_writelines_cross = []
#             total_writelines_br = []
#
#             total_writelines_cross.append('# ATTENTION: All cross sections in this file have the default BW cutoff of M +- 15 * Gamma.\n')
#             total_writelines_cross.append('crosssection = {\n')
#             total_writelines_br.append('branchingratio = {\n')
#             if 'LQLQ' in processname:
#                 total_writelines_cross.append('  # lambda --> mass(chi) -->  (mass(LQ),    sigma,       Q_low,   Q_up,    PDF)\n')
#                 total_writelines_br.append('  # mass(LQ) --> mass(chi) --> (dau1, dau2) --> (br, partial width)\n')
#             elif 'PsiPsi' in processname:
#                 total_writelines_cross.append('  # lambda --> mass(LQ)  -->  (mass(chi),   sigma,       Q_low,   Q_up,    PDF)\n')
#                 # total_writelines_br.append('  # mass(chi) --> mass(LQ) --> (dau1, dau2) --> (br, partial width)\n')
#             else:
#                 raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')
#
#             filenames = get_filelist_crossbr(filepath=crosssecfolder+'/'+processname, short=True)
#             # print len(filenames)
#             tuplelist = []
#             tupledicts_per_lambda = {}
#             target_tuplelist_dict = {}
#             brs_per_mref = {}
#             for lamb in lambdas:
#                 tupledicts_per_lambda[lamb] = {}
#             print '%i files found' % (len(filenames))
#             for filename in filenames:
#                 is_param_card = True if 'param_card' in filename else False
#                 parse_pattern_cross = processname + '_MLQ{}_MPS{}_MC1{}_L{}'
#                 parse_pattern_cross += '%s_crosssection{}' % (tag)
#                 parse_pattern_br = processname + '_MLQ{}_MPS{}_MC1{}_L{}'
#                 parse_pattern_br += '%s_param_card{}' % (tag)
#                 if not is_param_card:
#                     parser_cross = parse.compile(parse_pattern_cross)
#                     # print filename
#                     mlq, mps, mch, lambstr, dummy = parser_cross.parse(filename)
#                     mlq, mps, mch, lamb = float(mlq), float(mps), float(mch), float(lambstr.replace('p', '.'))
#
#                     # find correct lines to parse and set up the patterns
#                     pattern_crosssection = '{}:   {} +- {} pb\n'
#                     pattern_scale        = '{}: +{}% -{}%\n'
#                     pattern_pdf          = '{}: +{}% -{}%\n'
#                     fin = open(join(crosssecfolder+'/'+processname, filename), 'r')
#                     lines = fin.readlines()
#                     line_crosssection = ''
#                     line_scale        = 'TEST'
#                     line_pdf          = ''
#                     lineidx = 0
#                     for line in lines:
#                         if 'Cross-section :' in line: line_crosssection = line
#                         elif 'scale variation:' in line: line_scale = line
#                         elif 'PDF variation:' in line: line_pdf = line
#
#                     # do the parsing
#                     parser_xsec  = parse.compile(pattern_crosssection)
#                     parser_scale = parse.compile(pattern_scale)
#                     parser_pdf   = parse.compile(pattern_pdf)
#                     pre, xsec, xsec_unc = parser_xsec.parse(line_crosssection)
#                     pre, scale_up, scale_down = parser_scale.parse(line_scale)
#                     pre, pdf_up, pdf_down = parser_pdf.parse(line_pdf)
#
#                     # put everything into the right tuples and sort
#                     mref = mch if 'LQLQ' in processname else mlq
#                     mdep = mlq if 'LQLQ' in processname else mch
#                     if not mref in tupledicts_per_lambda[lamb]: tupledicts_per_lambda[lamb][mref] = []
#                     tupledicts_per_lambda[lamb][mref].append((mdep, xsec, scale_down, scale_up, str(max(float(pdf_up), float(pdf_down)))))
#
#                 else: # param card
#                     if not processname == 'LQLQ': continue
#                     parser_br = parse.compile(parse_pattern_br)
#                     # print filename
#                     mlq, mps, mch, lambstr, dummy = parser_br.parse(filename)
#                     mlq, mps, mch, lamb = float(mlq), float(mps), float(mch), float(lambstr.replace('p', '.'))
#                     mref = mlq if 'LQLQ' in processname else mch
#                     mdep = mch if 'LQLQ' in processname else mlq
#
#                     fin = open(join(crosssecfolder+'/'+processname, filename), 'r')
#                     lines = fin.readlines()
#                     branchingratios = {}
#                     for line in lines:
#                         if line[0:5] == 'DECAY' or line[0] == '#': continue
#                         # remaining lines contain BRs
#                         content = line.split()
#                         br, decaywidth, dau1, dau2 = float(content[0]), float(content[5]), int(content[2]), int(content[3])
#                         dautup = (dau1, dau2)
#                         brtup  = ((br, decaywidth))
#                         branchingratios[dautup] = brtup
#                     if not mref in brs_per_mref.keys():
#                         brs_per_mref[mref] = {}
#                     if not mdep in brs_per_mref[mref].keys():
#                         brs_per_mref[mref][mdep] = {}
#                     if not brs_per_mref[mref][mdep] == {}:
#                         print brs_per_mref[mref]
#                         raise ValueError('M_dep %f is already a key in the dictionary, how did this happen?' % mdep)
#                     brs_per_mref[mref][mdep] = branchingratios
#
#             for lambkey in tupledicts_per_lambda:
#                 for mrefkey in tupledicts_per_lambda[lambkey]:
#                     tupledicts_per_lambda[lambkey][mrefkey].sort(key=itemgetter(0))
#             for lamb in sorted(tupledicts_per_lambda):
#                 total_writelines_cross.append("%1.1f: {\n" % (lamb))
#                 for mref in sorted(tupledicts_per_lambda[lambkey]):
#                     total_writelines_cross.append('    %i: [\n' % (mref))
#                     for tup in tupledicts_per_lambda[lamb][mref]:
#                         total_writelines_cross.append('            ( %s, %s, %s, %s, %s),\n' % (str(int(tup[0])).rjust(4, ' '), str(tup[1]).ljust(9, ' '), str(tup[2]).ljust(4, ' '), str(tup[3]).ljust(4, ' '), tup[4].ljust(4, ' ')))
#                     total_writelines_cross[-1] = total_writelines_cross[-1].replace('),', ')')
#                     total_writelines_cross.append('        ], # closing for this mref\n')
#                 total_writelines_cross = total_writelines_cross[:-1]
#                 total_writelines_cross.append('        ] # closing for this mref\n')
#                 total_writelines_cross.append('    }, # Closing for this lambda\n')
#             total_writelines_cross = total_writelines_cross[:-1]
#             total_writelines_cross.append('    } # Closing for this lambda\n')
#             total_writelines_cross.append('} # Closing for entire dictionary\n')
#
#             # now make writelines for branching ratios
#             if processname == 'LQLQ':
#                 for mref in sorted(brs_per_mref):
#                     total_writelines_br.append('  %i: {\n' % (mref))
#                     for mdep in sorted(brs_per_mref[mref]):
#                         total_writelines_br.append('    %i: {\n' % (mdep))
#                         for daus in sorted(brs_per_mref[mref][mdep]):
#                             total_writelines_br.append('      (%i, %i): (%2.3f, %f),\n' % (daus[0], daus[1], brs_per_mref[mref][mdep][daus][0], brs_per_mref[mref][mdep][daus][1]))
#                         total_writelines_br[-1] = total_writelines_br[-1].replace('),', ')')
#                         total_writelines_br.append('    }, # closing for this mdep\n')
#                     total_writelines_br = total_writelines_br[:-1]
#                     total_writelines_br.append('    } # closing for this mdep\n')
#                     total_writelines_br.append('  }, # Closing for this mref\n')
#                 total_writelines_br = total_writelines_br[:-1]
#                 total_writelines_br.append('  } # Closing for this mref\n')
#                 total_writelines_br.append('} # Closing for entire dictionary\n')
#
#
#
#             #finally write the files
#             if submit:
#                 print green('--> Writing cross sections and branching fractions for process: %s' % (processname))
#                 outfilename = crosssecfolder+'/Crosssections_%s%s.py' % (processname, tag)
#                 with open(outfilename, 'w') as fout:
#                     for wl in total_writelines_cross:
#                         fout.write(wl)
#                 if processname == 'LQLQ':
#                     outfilename = crosssecfolder+'/Branchingratios_%s%s.py' % (processname, tag)
#                     with open(outfilename, 'w') as fout:
#                         for wl in total_writelines_br:
#                             fout.write(wl)
#             else:
#                 print yellow('--> Would write cross sections and branching fractions for process: %s' % (processname))
#
#
#         if clean_folders:
#             if run_mg:
#                 raise ValueError('When cleaning the MG folders, one shouldn\'t submit something just before. Abort.')
#
#             # get list of folders and files to clean up
#             print processname
#             commands_folders_mv = []
#             commands_files_mv   = []
#             commands_folders_rm = []
#             commands_files_rm   = []
#             commands_tmp     = []
#             for config in configs:
#                 for lamb in lambdas:
#                     mlq, mps, mch = get_mlq_mps_mch(config)
#                     if lamb == 'best':
#                         lamb = preferred_lambdas[mlq]
#                     jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
#                     # 1) move folders
#                     command_folder_mv = 'mv ' + mgfolder_local + '/' + jobname + ' ' + mgfolder_local + '/' + jobname + '_old'
#                     if os.path.exists(mgfolder_local + '/' + jobname):
#                         commands_folders_mv.append(command_folder_mv)
#                     command_file_mv = 'mv ' + mgfolder_local + '/commands_' + jobname + '.dat ' + mgfolder_local + '/commands_' + jobname + '_old.dat'
#                     if os.path.exists(mgfolder_local + '/commands_' + jobname + '.dat'):
#                         commands_files_mv.append(command_file_mv)
#
#             if submit:
#                 print len(commands_folders_mv)
#                 print len(commands_files_mv)
#                 execute_commands_parallel(commands_folders_mv, ncores=50, niceness=19)
#                 execute_commands_parallel(commands_files_mv, ncores=50, niceness=19)
#
#
#             for config in configs:
#                 for lamb in lambdas:
#                     mlq, mps, mch = get_mlq_mps_mch(config)
#                     if lamb == 'best':
#                         lamb = preferred_lambdas[mlq]
#                     jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
#                     # 1) remove moved folders
#                     command_folder_rm = 'rm -rf ' + mgfolder_local + '/' + jobname + '_old'
#                     if os.path.exists(mgfolder_local + '/' + jobname + '_old'):
#                         commands_folders_rm.append(command_folder_rm)
#                     command_file_rm = 'rm ' + mgfolder_local + '/commands_' + jobname + '_old.dat'
#                     if os.path.exists(mgfolder_local + '/commands_' + jobname + '_old.dat'):
#                         commands_files_rm.append(command_file_rm)
#
#             # get list of 'tmp*' directories and keep them, these can just be deleted
#             tmp_dir_list = subprocess.check_output(['ls', mgfolder_local]).split('\n')
#             for dir in tmp_dir_list:
#                 if dir[0:3] ==  'tmp':
#                     command_tmp = 'rm -rf ' + mgfolder_local + '/' + dir
#                     commands_tmp.append(command_tmp)
#
#
#             if submit:
#                 print len(commands_folders_rm)
#                 print len(commands_tmp)
#                 print len(commands_files_rm)
#                 execute_commands_parallel(commands_folders_rm, ncores=3, niceness=19)
#                 execute_commands_parallel(commands_tmp, ncores=3, niceness=19)
#                 execute_commands_parallel(commands_files_rm, ncores=3, niceness=19)
#
#
#         if rootify_crossbr:
#             outfilename_cross = crosssecfolder+'/Crosssections_%s%s.root' % (processname, tag)
#             cross_module = importlib.import_module('crosssections.ChiPsi.Crosssections_%s' % (processname))
#             crosssections = cross_module.crosssection
#             outfile = TFile(outfilename_cross, 'RECREATE')
#             print green('--> Now at sample %s' % (processname))
#             for lamb in lambdas:
#                 if not lamb in crosssections: continue
#                 print green('  --> Now at lambda: %1.1f' % (lamb))
#                 # for mlq in sorted(all_combinations.keys()):
#                 #     if not mlq in crosssections[lamb]:
#                 #         crosssections[lamb][mlq] = []
#                 #     for mch in all_combinations[mlq]:
#                 #         if (len(crosssections[lamb][mlq]) == 0) or (not mch in crosssections[lamb][mlq]):
#
#                 xsecs_per_mref = crosssections[lamb]
#                 graph2d = TGraph2D()
#                 npoints2d=0
#                 set_points ={}
#                 for mlq in all_combinations:
#                     set_points[mlq] = {}
#                     for mch in all_combinations[mlq]:
#                         set_points[mlq][mch] = False
#                 for mref in xsecs_per_mref:
#                     xsecs = xsecs_per_mref[mref]
#                     final_xsecs = []
#                     mdeps  = array('d')
#                     sigmas  = array('d')
#                     tot_los = array('d')
#                     tot_his = array('d')
#                     mdeps_lo = array('d')
#                     mdeps_hi = array('d')
#
#                     for tuple in xsecs:
#
#                         mdep, sigma, q_lo, q_hi, pdf = tuple
#                         tot_lo = XsecTotErr(sigma, q_lo, pdf)
#                         tot_hi = XsecTotErr(sigma, q_hi, pdf)
#                         final_xsecs.append((mdep, sigma, tot_lo, tot_hi))
#                         mdeps.append(mdep)
#                         sigmas.append(sigma)
#                         tot_los.append(tot_lo)
#                         tot_his.append(tot_hi)
#                         mdeps_lo.append(0.)
#                         mdeps_hi.append(0.)
#                         if 'LQLQ' in processname:
#                             graph2d.SetPoint(npoints2d, mdep, mref, sigma)
#                             set_points[mdep][mref] = True
#                         elif 'PsiPsi' in processname:
#                             graph2d.SetPoint(npoints2d, mref, mdep, sigma)
#                             set_points[mref][mdep] = True
#                         else:
#                             raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')
#                         npoints2d += 1
#
#                     # make TGraph out of it
#                     graph = TGraphAsymmErrors(len(mdeps), mdeps, sigmas, mdeps_lo, mdeps_hi, tot_los, tot_his)
#                     xaxistitle = 'M_{LQ} [GeV]' if 'LQLQ' in processname else 'M_{#chi_{1}} [GeV]'
#                     graph.GetXaxis().SetTitle('M_{LQ} [GeV]')
#                     graph.GetYaxis().SetTitle('#sigma [pb]')
#                     graphname = processname
#                     if 'LQLQ' in processname:
#                         graphname += '_MC1%i' % (mref)
#                     elif 'PsiPsi' in processname:
#                         graphname += '_MLQ%i' % (mref)
#                     else:
#                         raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')
#
#                     graphname += ('_L%1.1f' % (lamb)).replace('.', 'p')
#                     graph.SetName(graphname)
#                     # print 'graphname: %s' % (graphname)
#                     graphtitle = processname
#                     if 'LQLQ' in processname:
#                         graphtitle += ', M_{#chi_{1}} = %i GeV' % (mref)
#                     elif 'PsiPsi' in processname:
#                         graphtitle += ', M_{LQ} = %i GeV' % (mref)
#                     graphtitle += ', #lambda = %1.1f' % (lamb)
#                     # print 'graphtitle: %s' % (graphtitle)
#                     graph.SetTitle(graphtitle)
#                     outfile.cd()
#                     graph.Write()
#
#                 # fill remaining points in 2d graph with zeros
#                 for mlq in set_points:
#                     for mch in set_points[mlq]:
#                         if not set_points[mlq][mch]:
#                             graph2d.SetPoint(npoints2d, mlq, mch, 0.)
#                             npoints2d += 1
#                 graph2d.SetName(processname + ('_L%1.1f' % (lamb)).replace('.', 'p'))
#                 graph2d.GetXaxis().SetTitle('M_{LQ} [GeV]')
#                 graph2d.GetYaxis().SetTitle('M_{#chi_{1}} = %i [GeV]')
#                 graph2d.GetZaxis().SetTitle('#sigma [pb]')
#                 graph2d.SetTitle(processname + ', #lambda = %1.1f' % (lamb))
#                 graph2d.Write()
#             outfile.Close()
#
#             # also rootify BRs if we are looking at the LQLQ process without decays (just for fun, could also be any other LQLQ process)
#             if processname == 'LQLQ':
#
#                 outfilename_br = crosssecfolder+'/Branchingratios_%s%s.root' % (processname, tag)
#                 br_module = importlib.import_module('crosssections.ChiPsi.Branchingratios_%s' % (processname))
#                 brs = br_module.branchingratio
#                 outfile = TFile(outfilename_br, 'RECREATE')
#                 brs2d = {}
#                 npoints2d = {}
#                 set_points ={}
#                 for mlq in all_combinations:
#                     set_points[mlq] = {}
#                     for mch in all_combinations[mlq]:
#                         set_points[mlq][mch] = {}
#                         for decaymode in decaymode_dict.keys():
#                             set_points[mlq][mch][decaymode] = False
#                 for mlq in sorted(brs):
#                     mchs_per_decaymode = {}
#                     brs_per_decaymode = {}
#                     for mch in sorted(brs[mlq]):
#                         for decaymode in brs[mlq][mch]:
#                             if not decaymode in mchs_per_decaymode.keys(): mchs_per_decaymode[decaymode] = array('d')
#                             if not decaymode in brs_per_decaymode.keys(): brs_per_decaymode[decaymode] = array('d')
#                             # if not decaymode in set_points[mlq][mch].keys():
#                             #     # print mlq, mch, decaymode
#                             #     set_points[mlq][mch][decaymode] = False
#                             if not decaymode in brs2d.keys():
#                                 graphname2d = processname + ('_%i_%i' % (abs(decaymode[0]), abs(decaymode[1])))
#                                 # print graphname2d
#                                 npoints2d[decaymode] = 0
#                                 brs2d[decaymode] = TGraph2D()
#                                 brs2d[decaymode].SetName(graphname2d)
#                                 brs2d[decaymode].GetXaxis().SetTitle('M_{LQ} [GeV]')
#                                 brs2d[decaymode].GetYaxis().SetTitle('M_{#chi_{1}} = %i [GeV]')
#                                 brs2d[decaymode].GetZaxis().SetTitle('BR (LQLQ#rightarrow%s)' % (decaymode_dict[decaymode]))
#                                 brs2d[decaymode].SetTitle(processname + ', %s' % (decaymode_dict[decaymode]))
#
#                             mchs_per_decaymode[decaymode].append(mch)
#                             brs_per_decaymode[decaymode].append(brs[mlq][mch][decaymode][0])
#                             brs2d[decaymode].SetPoint(npoints2d[decaymode], mlq, mch, brs[mlq][mch][decaymode][0])
#                             set_points[mlq][mch][decaymode] = True
#                             npoints2d[decaymode] += 1
#
#                     for decaymode in mchs_per_decaymode.keys():
#                         graph = TGraph(len(mchs_per_decaymode[decaymode]), mchs_per_decaymode[decaymode], brs_per_decaymode[decaymode])
#                         graphname = processname + ('_MLQ%i_%i_%i' % (mlq, abs(decaymode[0]), abs(decaymode[1])))
#                         graph.SetName(graphname)
#                         graph.GetXaxis().SetTitle('M_{#chi_{1}} [GeV]')
#                         graph.GetYaxis().SetTitle('BR (LQLQ#rightarrow%s)' % (decaymode_dict[decaymode]))
#                         graph.SetTitle(processname + ', %s' % (decaymode_dict[decaymode]))
#                         graph.Write()
#                 # fill remaining points in 2d graph with zeros
#                 for mlq in set_points:
#                     for mch in set_points[mlq]:
#                         for decaymode in set_points[mlq][mch]:
#                             if not set_points[mlq][mch][decaymode]:
#                                 # print 'Setting BR for MLQ=%i, MCH=%i, decay=(%i, %i) to 0' % (mlq, mch, decaymode[0], decaymode[1])
#                                 brs2d[decaymode].SetPoint(npoints2d[decaymode], mlq, mch, 0)
#                                 npoints2d[decaymode] += 1
#                 for decaymode in brs2d:
#                     brs2d[decaymode].Write()
#                 outfile.Close()
#
#
#         if plot_crossbr:
#             gROOT.SetBatch(1)
#             print green('--> Plotting cross section and BR plots for process %s' % processname)
#
#             # for a reasonably spaced set of particle masses, find the closest correspondence in the preferred_configurations:
#             if 'PsiPsi' in processname:
#                 mrefs_initial = [1000, 2000, 3000, 4500, 6000]
#                 xaxis_min = 100
#                 xaxis_max = 5000
#                 xaxis_title = 'M_{#chi_{1}} [GeV]'
#
#             else:
#                 mrefs_initial = [100, 300, 1000, 3000, 10000]
#                 xaxis_min = 1000
#                 xaxis_max = 10000
#                 xaxis_title = 'M_{LQ} [GeV]'
#
#             mrefs = []
#             for mref in mrefs_initial:
#                 if 'PsiPsi' in processname:
#                     mrefs.append(find_closest(sorted(preferred_configurations), mref))
#                 else:
#                     mrefs.append(find_closest(sorted(preferred_configurations[preferred_configurations.keys()[0]]), mref))
#
#             # open rootfile and get corresponding graphs
#             if 'LQLQ' in processname:
#                 rootfilename_brs = crosssecfolder+'/Branchingratios_LQLQ%s.root' % (tag)
#             else:
#                 rootfilename_brs = ''
#             rootfilename = crosssecfolder+'/Crosssections_%s%s.root' % (processname, tag)
#             infile = TFile(rootfilename, 'READ');
#             for lamb in lambdas:
#                 ymin = 2E-15 #if 'LQLQ' in processname else 2E-15
#                 ymax = 1 if 'LQLQ' in processname else 1E5
#                 c = tdrCanvas('c', xaxis_min, xaxis_max, ymin, ymax, xaxis_title, '#sigma (pp #rightarrow %s) [pb]' % (procname_to_latex[processname]), square=True, iPeriod=0, iPos=11)
#                 c.SetLogy()
#                 leg = tdrLeg(0.55,0.55,0.9,0.9)
#                 idx = 0
#                 for mref in mrefs:
#                     graphname = processname
#                     if 'PsiPsi' in processname:
#                         graphname += '_MLQ'
#                     else:
#                         graphname += '_MC1'
#                     graphname += '%i_L%s' % (mref, get_lambdastring(lamb))
#                     graph = infile.Get(graphname)
#                     try:
#                         tdrDraw(graph, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.4)
#                         graph.GetXaxis().SetLabelSize(14)
#
#                         if 'PsiPsi' in processname:
#                             legtext = 'M_{LQ} = %i GeV' % (mref)
#                         else:
#                             legtext = 'M_{#chi_{1}} = %i GeV' % (mref)
#                         leg.AddEntry(graph, legtext, 'lf');
#                     except ReferenceError:
#                         # print 'skip this one'
#                         idx +=1
#                         continue
#                     idx += 1
#                 leg.Draw('SAME')
#                 plotname = crosssecfolder+'/plots/Crosssections_%s_L%s%s.pdf' % (processname, get_lambdastring(lamb), tag)
#                 if submit:
#                     c.SaveAs(plotname)
#
#                 if 'LQLQ' in processname and not processname == 'LQLQ':
#                     infile_brs = TFile(rootfilename_brs, 'READ')
#                     infile_lqlq = TFile(crosssecfolder+'/Crosssections_LQLQ.root', 'READ')
#                     decaymodes = procname_to_decaymodes[processname]
#                     graphname_br1 = 'LQLQ_%i_%i' % (abs(decaymodes[0][0]), abs(decaymodes[0][1]))
#                     graphname_br2 = 'LQLQ_%i_%i' % (abs(decaymodes[1][0]), abs(decaymodes[1][1]))
#                     graph_br1 = infile_brs.Get(graphname_br1)
#                     graph_br2 = infile_brs.Get(graphname_br2)
#
#                     idx = 0
#                     for mref in mrefs:
#                         c_ratio = tdrDiCanvas('c_ratio', xaxis_min, xaxis_max, ymin, ymax, 0.3, 1.7, xaxis_title, '#sigma (pp #rightarrow %s) [pb]' % (procname_to_latex[processname]), '#sigma (full) / #sigma #times BR', square=True, iPeriod=0, iPos=11)
#                         c_ratio.cd(1)
#                         gPad.SetLogy()
#                         leg_ratio = tdrLeg(0.55,0.8,0.9,0.9)
#                         graphname_top = processname + '_MC1%i_L%s' % (mref, get_lambdastring(lamb))
#                         graph_top = infile.Get(graphname_top)
#                         graphname_xsecbr = 'LQLQ_MC1%i_L%s' % (mref, get_lambdastring(lamb))
#                         graph_xsecbr = infile_lqlq.Get(graphname_xsecbr)
#                         try:
#                             c_ratio.cd(1)
#                             tdrDraw(graph_top, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.2)
#                             graph_top.GetXaxis().SetLabelSize(14)
#                             masses_orig_top = array('d')
#                             y_top_ups = array('d')
#                             y_top_dns = array('d')
#                             for i in range(graph_top.GetN()):
#                                 x=Double(0)
#                                 y=Double(0)
#                                 graph_top.GetPoint(i, x, y)
#                                 masses_orig_top.append(x)
#                                 y_top_ups.append(Double(graph_top.GetErrorYhigh(i)))
#                                 y_top_dns.append(Double(graph_top.GetErrorYlow(i)))
#
#                             nremoved = 0
#                             masses_orig_xsec = array('d')
#                             for i in range(graph_xsecbr.GetN()):
#                                 x=Double(0)
#                                 y=Double(0)
#                                 graph_xsecbr.GetPoint(i-nremoved, x, y)
#                                 br1 = graph_br1.Interpolate(x, mref)
#                                 br2 = graph_br2.Interpolate(x, mref)
#                                 n_channels = 1 if (decaymodes[0] == decaymodes[1]) else 2
#                                 newval = y * br1 * br2 * n_channels
#                                 if y == 0 or newval == 0:
#                                     graph_xsecbr.RemovePoint(i-nremoved)
#                                     nremoved += 1
#                                 else:
#                                     graph_xsecbr.SetPoint(i-nremoved, x, newval)
#                                     masses_orig_xsec.append(x)
#                             tdrDraw(graph_xsecbr, "LX", mcolor=colors[idx], lcolor=colors[idx])
#                             graph_xsecbr.SetLineStyle(2)
#
#                             # calculate ratio
#                             graph_top_up = TGraph(len(masses_orig_top), masses_orig_top, y_top_ups)
#                             graph_top_dn = TGraph(len(masses_orig_top), masses_orig_top, y_top_dns)
#                             xs = array('d')
#                             xs_up = array('d')
#                             xs_dn = array('d')
#                             ys = array('d')
#                             ys_up = array('d')
#                             ys_dn = array('d')
#                             for mass in masses_orig_top:
#                                 if mass in masses_orig_xsec:
#                                     xs.append(Double(mass))
#                                     xs_up.append(Double(0))
#                                     xs_dn.append(Double(0))
#                                     ys.append(Double(graph_top.Eval(mass) / graph_xsecbr.Eval(mass)))
#                                     ys_up.append(Double(graph_top_up.Eval(mass) / graph_xsecbr.Eval(mass)))
#                                     ys_dn.append(Double(graph_top_dn.Eval(mass) / graph_xsecbr.Eval(mass)))
#                             graph_ratio = TGraphAsymmErrors(len(xs), xs, ys, xs_dn, xs_up, ys_dn, ys_up)
#                             c_ratio.cd(2)
#                             tdrDraw(graph_ratio, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.4)
#                             legtext_ratio = 'M_{#chi_{1}} = %i GeV' % (mref)
#                             leg_ratio.AddEntry(graph_top, legtext_ratio, 'lf');
#                         except ReferenceError:
#                             idx +=1
#                             continue
#                         idx += 1
#                         plotname_ratio = crosssecfolder+'/plots/Crosssections_comparison_%s_MC1%i_L%s%s.pdf' % (processname, mref, get_lambdastring(lamb), tag)
#                         if submit:
#                             c_ratio.SaveAs(plotname_ratio)
#                     infile_brs.Close()
#                     infile_lqlq.Close()
#
#                 graphname2 = processname
#                 graphname2 += '_L%s' % (get_lambdastring(lamb))
#                 graph2d = infile.Get(graphname2)
#                 h2 = TH2D('h2', 'h2', 500, mlq_min, mlq_max, 500, 100, 21000)
#                 graph2d.SetHistogram(h2)
#                 c2 = TCanvas('c2', 'c2', 800, 600)
#                 graph2d.Draw("COLZ")
#                 graph2d.GetHistogram().SetContour(50)
#                 graph2d.GetHistogram().GetXaxis().SetNdivisions(505)
#                 graph2d.GetHistogram().GetXaxis().SetTitle('M_{LQ} [GeV]')
#                 graph2d.GetHistogram().GetYaxis().SetTitle('M_{#chi_{1}} [GeV]')
#                 graph2d.GetHistogram().GetZaxis().SetTitle('#sigma (pp#rightarrow %s) [pb]' % (procname_to_latex[processname]))
#                 graph2d.GetHistogram().GetZaxis().SetTitleOffset(1.25)
#                 graph2d.GetHistogram().GetYaxis().SetTitleOffset(1.0)
#                 graph2d.GetHistogram().SetMaximum(1E-1)
#                 graph2d.GetHistogram().SetMinimum(2E-19)
#                 c2.SetLogy()
#                 c2.SetLogz()
#                 c2.SetRightMargin(0.20)
#                 c2.SetLeftMargin(0.13)
#                 c2.SetTopMargin(0.05)
#                 c2.Update()
#                 plotname = crosssecfolder+'/plots/Crosssections2d_%s_L%s%s.pdf' % (processname, get_lambdastring(lamb), tag)
#                 if submit:
#                     c2.SaveAs(plotname)
#             infile.Close()
#             if processname == 'LQLQ':
#                 # decaymodes = [(5, -15), (6, -16), (9000009, 9000007), (9000009, 9000008)]
#                 decaymodes = decaymode_dict.keys()
#                 mlqs_initial = [1000, 2000, 3000, 4500, 6000]
#                 xaxis_min = 90
#                 xaxis_max = 20000
#                 xaxis_title = 'M_{#chi_{1}} [GeV]'
#                 mlqs = []
#                 for mlq in mlqs_initial:
#                     mlqs.append(find_closest(sorted(preferred_configurations), mlq))
#
#                 # open rootfile and get corresponding graphs
#                 infile_brs = TFile(rootfilename_brs, 'READ')
#                 for mlq in mlqs:
#                     c3 = tdrCanvas('c3', xaxis_min, xaxis_max, 0, 1.1, xaxis_title, 'Branching ratio', square=True, iPeriod=0, iPos=11)
#                     c3.SetLogx()
#                     leg3 = tdrLeg(0.55,0.65,0.9,0.9)
#                     legheader3 = 'M_{LQ} = %i GeV' % (mlq)
#                     tdrHeader(leg3, legheader3)
#                     idx = 0
#                     for decaymode in decaymodes:
#                         graphname3 = processname + '_MLQ%i_%i_%i' % (mlq, abs(decaymode[0]), abs(decaymode[1]))
#                         # print graphname
#                         graph3 = infile_brs.Get(graphname3)
#                         try:
#                             tdrDraw(graph3, "3L", mcolor=colors[idx], lcolor=colors[idx])
#                             graph3.GetXaxis().SetLabelSize(14)
#                             # legtext = 'M_{LQ} = %i GeV' % (mlq)
#                             legtext3 = 'LQ #rightarrow %s' % (decaymode_dict[decaymode])
#                             leg3.AddEntry(graph3, legtext3, 'l');
#                         except ReferenceError:
#                             # print 'skip this one'
#                             idx +=1
#                             continue
#                         idx += 1
#                     leg3.Draw('SAME')
#                     plotname = crosssecfolder+'/plots/Branchingratios_%s_MLQ%i%s.pdf' % (processname, mlq, tag)
#                     if submit:
#                         print plotname
#                         c3.SaveAs(plotname)
#
#                 for decaymode in decaymodes:
#                     graphname = processname + '_%i_%i' % (abs(decaymode[0]), abs(decaymode[1]))
#                     graph2d = infile_brs.Get(graphname)
#                     h2 = TH2D('h2', 'h2', 500, mlq_min, mlq_max, 500, 100, 21000)
#                     graph2d.SetHistogram(h2)
#                     c4 = TCanvas('c4', 'c4', 800, 600)
#                     graph2d.Draw("COLZ")
#                     graph2d.GetHistogram().SetContour(50)
#                     graph2d.GetHistogram().GetXaxis().SetNdivisions(505)
#                     graph2d.GetHistogram().GetXaxis().SetTitle('M_{LQ} [GeV]')
#                     graph2d.GetHistogram().GetYaxis().SetTitle('M_{#chi_{1}} [GeV]')
#                     graph2d.GetHistogram().GetZaxis().SetTitle('BR (LQ #rightarrow %s)' % (decaymode_dict[decaymode]))
#                     graph2d.GetHistogram().GetZaxis().SetTitleOffset(1.25)
#                     graph2d.GetHistogram().GetYaxis().SetTitleOffset(1.0)
#                     graph2d.GetHistogram().SetMaximum(0.7)
#                     graph2d.GetHistogram().SetMinimum(0.)
#                     c4.SetLogy()
#                     # c4.SetLogz()
#                     c4.SetRightMargin(0.20)
#                     c4.SetLeftMargin(0.13)
#                     c4.SetTopMargin(0.05)
#                     c4.Update()
#                     plotname = crosssecfolder+'/plots/Branchingratios2d_%s_%i_%i%s.pdf' % (processname, abs(decaymode[0]), abs(decaymode[1]), tag)
#                     if submit:
#                         c4.SaveAs(plotname)
#
#                 infile_brs.Close()





def SubmitTuplize(submit, generation_step):
    # Submit tuplize jobs to the SLURM cluster
    ncores = 1
    queue   = 'quick'       # quick -- wn
    runtime = '00:05:00' # 01:00:00 -- 10:00:00
    commandfilebase = gensimfolder + '/commands/tuplize_%s_' % (configs[generation_step]['jobnametag'])

    # Create command file for array of jobs
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                outfoldername = T3_director + T3_path + '/' + campaign + '/' + configs[generation_step]['pathtag'] + '/' + jobname
                commandfilename = commandfilebase + jobname + '.txt'
                f = open(commandfilename, 'w')
                njobs = 0
                for i in range(maxindex):
                    # infilename = T3_path + '/' + gensim_path_tag + '/' + jobname + '/GENSIM_%i.root' % (i+1)
                    infilename = T2_director_root + T2_path + '/' + configs[generation_step]['infilepathtag'] + '/' + jobname + '/' + configs[generation_step]['infilenamebase'] + '_' + str(i+1) + '.root'
                    outfilename = configs[generation_step]['outfilenamebase'] + '_%i.root' % (i+1)
                    command = '%s %s %s' % (configs[generation_step]['tuplizer'], infilename, outfilename)
                    f.write(command + '\n')
                    njobs += 1
                f.close()

                command = 'sbatch -a 1-%s -J tuplize_%s -p %s -t %s --cpus-per-task %i submit_tuplize.sh %s %s %s %s %s %s' % (str(maxindex), configs[generation_step]['jobnametag'], queue, runtime, ncores, arch_tag, workarea+'/'+configs[generation_step]['cmsswtag'], basefolder, outfoldername, commandfilename, configs[generation_step]['jobnametag'])
                if submit:
                    os.system(command)
                    print green("Submitted an array of %i jobs for name %s"%(njobs, jobname))
                else:
                    print command
                    print yellow("Would submit an array of %i jobs for name %s"%(njobs, jobname))



def SubmitAdd(submit, generation_step):
    # Submit add jobs to the SLURM cluster
    ncores = 1
    queue   = 'quick'       # quick -- wn
    runtime = '00:05:00' # 01:00:00 -- 10:00:00

    commandfilebase = gensimfolder + '/commands/add_'
    for processname in processes:
        for config in mass_configurations:
            if is_config_excluded(excluded_configurations=excluded_configurations, config=config, processname=processname):
                print yellow('Skip config %s for process \'%s\'' % (config, processname))
                continue
            for lamb in lambdas:
                mlq, mps, mch = get_mlq_mps_mch(config)
                jobname      = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                infoldername= T3_director + T3_path + '/' + campaign + '/' + configs[generation_step]['pathtag'] + '/' + jobname
                infilestring = ''
                for i in range(maxindex):
                    fn = infoldername +  '/' + configs[generation_step]['outfilenamebase'] + '_%i.root' % (i+1)
                    infilestring = infilestring + ' ' + fn
                outfilename = configs[generation_step]['outfilenamebase'] + '.root'
                outfoldername = infoldername
                commandfilename = commandfilebase + jobname + '.txt'
                f = open(commandfilename, 'w')
                command = 'hadd -f %s %s ; sleep 5 ; ' % (outfilename, infilestring)
                f.write(command)
                f.close()
                command = 'sbatch -J add_%s -p %s -t %s --cpus-per-task %i submit_add.sh %s %s' % (configs[generation_step]['jobnametag'], queue, runtime, ncores, arch_tag, workarea+'/'+configs[generation_step]['cmsswtag'], basefolder, outfoldername, commandfilename)
                if submit:
                    os.system(command)
                    print green("Submitted job for adding tuplized samples: %s."%(jobname))
                else:
                    print command
                    print yellow("Would submit job for adding tuplized samples: %s."%(jobname))












def make_card(card_template_folder, card_output_folder, processname, mlq, mps, mch, lamb=1.0, bwcutoff=15., lhapdfid=315200, verbose=False):
    # PDF CMS standard (Paolo):
    # 2016 LO:       263000
    # 2016 NLO:      260000
    # 2017 CP5:      303600
    # 2018 CP5:      303600 (same as 2017)
    # 2017/18 CP2:   315200 for 2017/8
    samplename = get_samplename(mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
    cardbasename = processname + '_template'
    cardtypes = ['proc_card.dat', 'run_card.dat', 'extramodels.dat', 'customizecards.dat']
    cards = [card_template_folder + '/' + cardbasename + '_' + c for c in cardtypes]

    newcards = []
    for card in cards:
        template = card
        newcard = card.replace('template', samplename).replace(card_template_folder, card_output_folder)
        newcards.append(newcard)

        # create newcard
        command = 'cp %s %s' % (template, newcard)
        # print command
        os.system(command)

    outputfoldername = processname + '_' + samplename
    replacement_dict = {
        'MLQ':      mlq,
        'MPS':      mps,
        'MCH':      mch,
        'MC2':      int(round(2*mps - mch)), # delta_c2 = 2 * delta_ps => mc2 = 2mps - mch --> As done in paper, but value of mc2 doesn't matter for anomalies or relic abundance. Maybe increase to suppress this channel
        'MZP':      int(round(mlq/math.sqrt(2))), # as done in the paper, but doesn't really affect anomalies or relic abundance
        'LAMBDA':   lamb,
        'BWCUTOFF': bwcutoff,
        'OUTPUT':   outputfoldername,
        'PDF':      lhapdfid
    }

    # replace values in the cards
    for card in newcards:
        replace_placeholders(card=card, replacement_dict=replacement_dict, verbose=verbose)
    if verbose:
        print green('--> Done making one set of cards.\n')


def replace_placeholders(card, replacement_dict, identifier = '$', verbose=False):
    fin = open(card,'r')
    lines = fin.readlines()
    newlines = []
    lineidx = 0
    for line in lines:
        lineidx += 1
        newline = line
        for key in replacement_dict.keys():
            pattern = identifier + key
            if pattern in line:
                newline = line.replace(pattern, str(replacement_dict[key]))
                if verbose:
                    print green('In file \'%s\': replaced %s with %s in line %i' % (card, pattern, str(replacement_dict[key]), lineidx))
        if identifier in newline and not newline.strip()[0] == '#':
            print yellow('found identifier in newline, meaning it hasn\'t been replaced. Line is: %s' % (newline[:-1]))
        newlines.append(newline)

    fin.close()

    fout = open(card, 'w')
    for l in newlines:
        fout.write(l)
    fout.close()
    if verbose:
        print green('--> Successfully created card %s' % (card))


def getcmsRunCommand(pset, outfilename, N, ncores, infilename=None, gridpack=None):
    """Submit PSet config file and gridpack to SLURM batch system."""

    if gridpack is not None and infilename is None:
        command = 'cmsRun %s gridpack=%s outfilename=%s nevents=%i nThreads=%i' % (pset, gridpack, outfilename, nevents, ncores)
    elif infilename is not None and gridpack is None:
        command = 'cmsRun %s infilename=%s outfilename=%s nevents=%i nThreads=%i' % (pset, infilename, outfilename, nevents, ncores)
    return command


def findMissingFilesT2(filepath, filename_base, maxindex):
    missing_indices = []
    filename_base = filepath+'/'+filename_base
    for idx in range(maxindex):
        filename = filename_base + '_' + str(idx+1) + '.root'
        # print 'didn\'t find file %s, going to try to open it' % (filename)
        result = subprocess.Popen(['/bin/bash', '%s/check_T2_file.sh' % (gensimfolder), filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, error = result.communicate()
        returncode = result.returncode
        if returncode > 0: # opening failed
            print 'opening failed for index %i' % (idx+1)
            missing_indices.append(idx)
        # else:
        #     size = int(output.split()[4])
        #     # print size
        #     if size < 5E9: # file too small.
        #         print 'size for index %i is %i, resubmit.' % (idx+1, size)
        #         missing_indices.append(idx)
    return missing_indices

def get_filelist_crossbr(filepath, short):
    postfix = ''

    if short:
        filenames = [f for f in os.listdir(filepath) if isfile(join(filepath, f)) and postfix in f and tag in f and '_short' in f]
    else:
        filenames = [f for f in os.listdir(filepath) if isfile(join(filepath, f)) and postfix in f and tag in f and not '_short' in f]
    return (filenames)

def check_shortfiles(filepath):
    filenames = get_filelist_crossbr(filepath=filepath, short=True)

        # check if the shortfile contains necessary info, otherwise delete it
    for filename in filenames:
        is_param_card = True if 'param_card' in filename else False
        infilename = join(filepath, filename)
        fin = open(infilename, 'r')
        lines = fin.readlines()
        found_start = False
        keep_file = False
        if not is_param_card:
            found_systs = False
            for line in lines:
                if '  === Results Summary for run' in line or 'Summary:' in line: found_start = True
                if 'PDF variation' in line: found_systs = True
            keep_file = found_start and found_systs
        else:
            found_end = False
            for line in lines:
                if 'DECAY  9000005' in line: found_start = True
                if line[0] == '#' and not line[1] == ' ': found_end = True
            keep_file = found_start and found_end
        if not keep_file:
            print yellow('Removing incomplete file %s' % (infilename))
            os.remove(infilename)

def XsecTotErr(sigma,*errs,**kwargs):
    """Helpfunction to calculate total error."""
    absolute = kwargs.get('abs', False)
    err2 = 0
    for err in errs:
        err2 += err**2
    toterr = sqrt(err2)
    if not absolute:
        toterr *= sigma/100.
    return toterr


if __name__ == '__main__':
    crossbrrunner = CrossSectionRunner(10)
    main()
