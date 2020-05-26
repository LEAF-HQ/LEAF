#! /usr/bin/env python

import os, sys
import subprocess
import time
from utils import *


# ----------------
# General settings
# ----------------

mass_configurations = [
    {'mlq': 600,  'mx': 220, 'mdm': 200},
    {'mlq': 700,  'mx': 275, 'mdm': 250},
    {'mlq': 800,  'mx': 330, 'mdm': 300},
    {'mlq': 900,  'mx': 385, 'mdm': 350},
    {'mlq': 1000, 'mx': 440, 'mdm': 400},
    {'mlq': 1100, 'mx': 495, 'mdm': 450},
    {'mlq': 1200, 'mx': 550, 'mdm': 500},
    {'mlq': 1300, 'mx': 605, 'mdm': 550},
    {'mlq': 1400, 'mx': 660, 'mdm': 600},
    {'mlq': 1500, 'mx': 715, 'mdm': 650},
    {'mlq': 1600, 'mx': 770, 'mdm': 700},
    {'mlq': 1700, 'mx': 825, 'mdm': 750},
    {'mlq': 1800, 'mx': 880, 'mdm': 800},
    {'mlq': 1900, 'mx': 935, 'mdm': 850},
    {'mlq': 2000, 'mx': 990, 'mdm': 900}
]
lambdas = [1.0]
tag = ''                # tags are auto-formatted to '_XXXX'
maxindex        = 100   # Number of samples per configuration
nevents         = 3000  # Events per sample


arch_tag       = 'slc7_amd64_gcc700'
cmssw_tag_gp   = 'CMSSW_9_3_16'
workarea       = '/work/areimers'
workdir_slurm  = workarea + '/workdir_slurm'
mgfolder       = workarea + '/CMSSW_10_2_10/src/genproductions/bin/MadGraph5_aMCatNLO'
basefolder     = workarea + '/LQDM/GENSIM'
gridpackfolder = basefolder + '/gridpacks'
pset           = 'pset_GENSIM.py'
pnfs_path      = '/pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM'

def main():

    make_cards       = False
    submit_gridpacks = False
    copy_gridpacks   = False
    clean_mg_area    = False

    gensim           = False
    resubmit         = False
    tuplize          = False
    add              = False

    submit           = False

    ensureDirectory(workdir_slurm)


    # steps until gridpacks are done
    if make_cards: ProduceCards()
    if submit_gridpacks: SubmitGridpacks(submit=submit)
    if copy_gridpacks: CopyGridpacks(submit=submit)
    if clean_mg_area: CleanMGArea(submit=submit)

    # steps after gridpacks until simple files
    if gensim:   SubmitGensim(submit=submit)
    if resubmit: ResubmitGensim(submit=submit)
    if tuplize:  SubmitTuplize(submit=submit)
    if add:      SubmitAdd(submit=submit)

    # continue the analysis with "macros" to plot simple files







# ----------
# Make cards
# ----------
def ProduceCards():
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            make_card(card_template_folder='/work/areimers/LQDM/GENSIM/cards/LQDM', mlq=mlq, mx=mx, mdm=mdm, lamb=lamb)
    print green('Done producing cards from templates')

def SubmitGridpacks(submit):
    # Submit gridpacks based on cards created above
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname = get_jobname(mlq, mx, mdm, lamb, tag)

            command = 'sbatch -J gridpacks_%s submit_gridpacks.sh %s ../../../../../LQDM/GENSIM/cards/LQDM local' % (jobname, jobname)
            print command
            if submit: os.system(command)
    print green('Done submitting gridpacks')



def CopyGridpacks(submit):
    # Copy gridpacks to new dir
    commands = []
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname = get_jobname(mlq, mx, mdm, lamb, tag)

            gpname = jobname + '_' + arch_tag + '_' + cmssw_tag_gp + '_tarball.tar.xz'
            sourcefile = mgfolder + '/' + gpname
            targetfile = gridpackfolder + '/' + gpname
            command = 'mv %s %s' % (sourcefile, targetfile)
            commands.append(command)
            print command
    if submit: execute_commands_parallel(commands=commands, ncores=15)
    print green('done moving gridpacks')



def CleanMGArea(submit):
    # Clean MG area from workdirs of gridpack generation
    commands = []
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname   = get_jobname(mlq, mx, mdm, lamb, tag)
            command = 'rm -rf ' + mgfolder + '/' + jobname + '*'
            commands.append(command)
            print command
    if submit: execute_commands_parallel(commands=commands, ncores=15)
    print green('done cleaning up MG area')

def SubmitGensim(submit):
    # Submit GENSIM jobs to the SLURM cluster
    ncores = 1
    commandfilebase = basefolder + '/commands/gensim_'

    # Create command file for array of jobs
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname      = get_jobname(mlq, mx, mdm, lamb, tag)
            gridpack     = gridpackfolder + '/' + jobname + '_' + arch_tag + '_' + cmssw_tag_gp + '_tarball.tar.xz'
            commandfilename = commandfilebase + jobname + '.txt'
            f = open(commandfilename, 'w')
            for i in range(maxindex):
                command = getCommandLine(basefolder, pset, gridpack, jobname, index=i+1, N=nevents, ncores=ncores)
                f.write(command + '\n')
            f.close()
            command = 'sbatch -a 1-%s -J gensim_%s -p quick -t 01:00:00 --cpus-per-task %i submit_gensim_interface.sh %s' % (str(maxindex), jobname, ncores, commandfilename)
            print command
            if submit: os.system(command)

def ResubmitGensim(submit):
    # Reubmit GENSIM jobs to the SLURM cluster
    ncores = 4
    commandfilebase = basefolder + '/commands/resubmit_'

    # Create command file for array of jobs
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname      = get_jobname(mlq, mx, mdm, lamb, tag)
            gridpack     = gridpackfolder + '/' + jobname + '_' + arch_tag + '_' + cmssw_tag_gp + '_tarball.tar.xz'
            missing_indices = findMissingFilesGENSIM(jobname, maxindex)
            nJobs_re = 0
            commandfilename = commandfilebase + jobname + '.txt'
            f = open(commandfilename, 'w')
            for i in missing_indices:
                command = getCommandLine(basefolder, pset, gridpack, jobname, index=i, N=nevents, ncores=ncores)
                f.write(command + '\n')
                nJobs_re += 1
            f.close()
            command = 'sbatch -a 1-%s -J resubmit_%s -p wn --cpus-per-task %i submit_gensim_interface.sh %s' % (str(nJobs_re), jobname, ncores, commandfilename)
            if nJobs_re > 0:
                print command
                if submit:
                    os.system(command)
                    print green("Resubmitted an array of %s jobs"%(str(nJobs_re)))
                else:
                    print yellow("Would resubmit an array of %s jobs"%(str(nJobs_re)))
            else:
                print green('No jobs to resubmit.')

def SubmitTuplize(submit):
    # Submit tuplize jobs to the SLURM cluster
    ncores = 1
    commandfilebase = basefolder + '/commands/tuplize_'

    # Create command file for array of jobs
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname      = get_jobname(mlq, mx, mdm, lamb, tag)
            commandfilename = commandfilebase + jobname + '.txt'
            f = open(commandfilename, 'w')
            for i in range(maxindex):
                infilename = pnfs_path + '/' + jobname + '/GENSIM_%i.root' % (i+1)
                outfilename = 'simple_files/' + jobname + '_GENSIM_simple_%i.root' % (i+1)
                command = './convertGENSIM.py %s -o %s' % (infilename, outfilename)
                f.write(command + '\n')
            f.close()
            command = 'sbatch -a 1-%s -J tuplize_%s -p quick -t 01:00:00 --cpus-per-task %i submit_tuplize.sh %s' % (str(maxindex), jobname, ncores, commandfilename)
            print command
            if submit: os.system(command)

def SubmitAdd(submit):
# Submit add jobs to the SLURM cluster
    for config in mass_configurations:
        for lamb in lambdas:
            mlq, mx, mdm = get_mlq_mx_mdm(config)
            jobname      = get_jobname(mlq, mx, mdm, lamb, tag)
            command = 'sbatch -J add_%s -p quick --cpus-per-task 1 submit_add.sh %s' % (jobname, jobname)
            print command
            if submit: os.system(command)
            print green("Submitted job for adding tuplized samples: %s."%(jobname))








def make_card(card_template_folder, mlq, mx, mdm, lamb=1.0, bwcutoff=15., lhapdfid=315200):
    #PDF CMS standard (Paolo):
    # 2016 LO:       263000
    # 2016 NLO:      260000
    # 2017 CP5:      303600
    # 2018 CP5:      303600 (same as 2017)
    # 2017/18 CP2:   315200 for 2017/8
    samplename = get_samplename(mlq, mx, mdm, lamb, tag)
    cardbasename = 'LQDM_template'
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

    outputfoldername = 'LQDM_' + samplename
    replacement_dict = {
    'MLQ':      mlq,
    'MX':       mx,
    'MDM':      mdm,
    'LAMBDA':   lamb,
    'BWCUTOFF': bwcutoff,
    'OUTPUT':   outputfoldername,
    'PDF':      lhapdfid
    }

    # replace values in the cards
    for card in newcards:
        replace_placeholders(card, replacement_dict)

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






def getCommandLine(basefolder, pset, gridpack, sample, index=-1, N=-1, ncores=1):
    """Submit PSet config file and gridpack to SLURM batch system."""
    global nJobs
    jobname  = sample
    gridpack = os.path.abspath(gridpack)
    options  = ""
    if index>0:
        jobname = "%s_%d"%(jobname,index)
        options = "%s -i %d"%(options,index)
    if N>0:
        options = "%s -N %s"%(options,N)
    if ncores>1:
        options  = "%s -c %s"%(options,ncores)
        options = options.lstrip(' ')
    command = 'source %s/submit_gensim.sh %s %s %s %s' % (basefolder, pset, gridpack, sample, options.strip())
    return command




def findMissingFilesGENSIM(jobname, maxindex):
    missing_indices = []
    filename_base = '%s/%s/GENSIM_' % (pnfs_path, jobname)
    for idx in range(1,maxindex+1):
        filename = filename_base + str(idx) + '.root'
        if not os.path.isfile(filename):
            missing_indices.append(idx)
        elif os.path.getsize(filename) < 100E+6: # file should have >100MB
            missing_indices.append(idx)
    return missing_indices



if __name__ == '__main__':
    main()
