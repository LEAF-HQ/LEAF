#! /usr/bin/env python

import os, sys, math
import subprocess
import time
from utils import *
from preferred_configurations import *


# ----------------
# General settings
# ----------------

# mass_configurations = {
#     'LQLQ': [ # MPS will automatically be taken from 'preferred_configurations'
#     {'mlq': 1000, 'mch': 427},
#     {'mlq': 1000, 'mch': 912},
#     {'mlq': 1900, 'mch': 427},
#     {'mlq': 1900, 'mch': 794},
#     ], # end of LQLQ
#     'PSPS': [ # MPS will automatically be taken from 'preferred_configurations'
#     {'mlq': 1000, 'mch': 427},
#     {'mlq': 1000, 'mch': 912},
#     {'mlq': 1900, 'mch': 427},
#     {'mlq': 1900, 'mch': 794},
#     ], # end of PSPS
# }
mass_configurations = [
    # MPS will automatically be taken from 'preferred_configurations'
    {'mlq': 1000, 'mch': 427},
    {'mlq': 1000, 'mch': 912},
    {'mlq': 1900, 'mch': 427},
    {'mlq': 1900, 'mch': 794},
]

# exclude combinations of process -- mass_config for processes without phase space
excluded_configurations = {
    'LQLQToPsiChi': [
        {'mlq': 1000, 'mch': 912}
    ],
    'LQLQToBTauPsiChi': [
        {'mlq': 1000, 'mch': 912}
    ]
}

processes = ['LQLQToBTau', 'LQLQToBTauPsiChi', 'LQLQToPsiChi', 'PsiPsiToLQChi']

lambdas = [1.0]
tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 100   # Number of samples per configuration
nevents         = 1000  # Events per sample


username       = 'areimers'
arch_tag       = 'slc7_amd64_gcc700'
# cmssw_tag_gp   = 'CMSSW_9_3_16'
cmssw_tag_gp   = 'CMSSW_10_6_0'
cmssw_tag_sim  = 'CMSSW_10_6_12'
cmssw_tag_hlt  = 'CMSSW_9_4_14_UL_patch1'
campaign       = 'UL17'


workarea       = '/work/'+ username
workdir_slurm  = workarea + '/workdir_slurm'
mgfolder       = workarea + '/' + cmssw_tag_sim + '/src/genproductions/bin/MadGraph5_aMCatNLO'
basefolder     = workarea + '/LQDM'
macrofolder    = basefolder + '/macros'
gensimfolder   = basefolder + '/GENSIM'
gridpackfolder = gensimfolder + '/gridpacks'
cardfolder     = gensimfolder + '/cards/ChiPsi'
psetfolder     = gensimfolder + '/PSets/' + campaign
T2_director      = 'gsiftp://storage01.lcg.cscs.ch/'
T2_director_root = 'root://storage01.lcg.cscs.ch/'
T3_director      = 'root://t3dcachedb03.psi.ch/'
T2_path          = '/pnfs/lcg.cscs.ch/cms/trivcat/store/user/'+ username
T3_path          = '/pnfs/psi.ch/cms/trivcat/store/user/'+ username
tuple_path       = workarea + '/Tuples/' + campaign + '/GENSIM/LQDM'

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

    make_cards       = False
    submit_gridpacks = False
    move_gridpacks   = False
    clean_mg_area    = False

    gensim           = False
    resub_gensim     = False

    dr               = False
    resub_dr         = False

    hlt              = False
    resub_hlt        = False
    delete_dr        = False

    aod              = False
    resub_aod        = False
    delete_hlt       = False

    miniaod          = False
    resub_miniaod    = False
    delete_aod       = False

    nanoaod          = False
    resub_nanoaod    = False
    delete_miniaod   = False

    # flat             = False
    # resub_flat       = False
    # delete_nanoaod   = False

    tuplize_gen      = False
    add_gen          = False

    tuplize_nano     = True

    submit           = True

    ensureDirectory(workdir_slurm)


    # Gridpack generation
    if make_cards:       ProduceCards()
    if submit_gridpacks: SubmitGridpacks(submit=submit)
    if move_gridpacks:   MoveGridpacks(submit=submit)
    if clean_mg_area:    CleanMGArea(submit=submit)

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
                make_card(card_template_folder=cardfolder, processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb)
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
        raise ValueError('Value \'%s\' is invalide for variable \'mode\'.' % mode)

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
                jobname      = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
                samplepath   = T2_director+T2_path+'/'+configs[generation_step]['pathtag']+'/'+jobname
                command  = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-rm -r %s' % (samplepath)

                print command
                commands.append(command)

    if submit:
        execute_commands_parallel(commands=commands)





def SubmitTuplize(submit, generation_step):
    # Submit tuplize jobs to the SLURM cluster
    ncores = 1
    queue   = 'quick'       # quick -- wn
    runtime = '00:05:00' # 01:00:00 -- 10:00:00
    commandfilebase = gensimfolder + '/commands/tuplize_%s' % (configs[generation_step]['jobnametag'])

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












def make_card(card_template_folder, processname, mlq, mps, mch, lamb=1.0, bwcutoff=15., lhapdfid=315200):
    #PDF CMS standard (Paolo):
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
        newcard = card.replace('template', samplename)
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
        replace_placeholders(card, replacement_dict)
    print green('--> Done making one set of cards.\n')


def replace_placeholders(card, replacement_dict, identifier = '$'):
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
                print green('In file \'%s\': replaced %s with %s in line %i' % (card, pattern, str(replacement_dict[key]), lineidx))
        if identifier in newline and not newline.strip()[0] == '#':
            print yellow('found identifier in newline, meaning it hasn\'t been replaced. Line is: %s' % (newline[:-1]))
        newlines.append(newline)

    fin.close()

    fout = open(card, 'w')
    for l in newlines:
        fout.write(l)
    fout.close()
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



if __name__ == '__main__':
    main()
