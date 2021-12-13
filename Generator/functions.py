# Author: Arne Reimers
import os, sys
from os.path import isfile, join
from fnmatch import fnmatch
import subprocess
import time
import signal
import math
from math import sqrt, log, floor, ceil
from bisect import bisect_left
from ROOT import TFile
from utils import *
from constants import *
from tqdm import tqdm

from multiprocessing import Process, Queue

# def get_samplename(mlq=None, mps=None, mch=None, lamb=None, betaR=None, beta33L=None, beta32L=None, beta23L=None, tag=None):
#     # 'MLQ%i_MPS%i_MC1%i_L%s%s' % (mlq, mps, mch, get_lambdastring(lamb), format_tag(tag))
#     result = ''
#     if mlq is not None:
#         result += 'MLQ%i_'%mlq
#     if mps is not None:
#         result += 'MPS%i_'%mps
#     if mps is not None:
#         result += 'MC1%i_'%mch
#     if lamb is not None:
#         result += 'L%s_'%get_lambdastring(lamb)
#     if betaR is not None:
#         result += 'BetaR%s_'%get_lambdastring(betaR)
#     if beta33L is not None:
#         result += 'Beta33L%s_'%get_lambdastring(beta33L)
#     if beta32L is not None:
#         result += 'Beta32L%s_'%get_lambdastring(beta32L)
#     if beta23L is not None:
#         result += 'Beta23L%s_'%get_lambdastring(beta23L)
#     while result.endswith('_'):
#         result = result[:-1]
#     result += format_tag(tag) # still safe if tag is None
#     return result


def get_samplename_flex(ordered_dict, tag=None):
    # Expects the dict to be ordered and will concatenate keys with their values and then with other entries in the dictionary to a single string

    # both value and key will get converted to strings if not already

    if ordered_dict is None:
        return format_tag(tag)

    result = ''
    for key in ordered_dict:
        val = ordered_dict[key][0]
        namepart = ordered_dict[key][1]
        if isinstance(val, float) or isinstance(val, int):
            val = get_floatstring(val)
        result += '%s%s_' % (str(namepart), str(val))
    while result.endswith('_'):
        result = result[:-1]
    result += format_tag(tag) # still safe if tag is None
    return result

# def get_jobname(processname, mlq=None, mps=None, mch=None, lamb=None, tag=None):
#     if mlq is not None and mps is not None and mch is not None and lamb is not None:
#         return processname + '_' + get_samplename(mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=tag)
#     elif tag is not None:
#         return processname + format_tag(tag)
#     else:
#         return processname

def get_jobname_flex(processname, ordered_dict, tag=None):
    samplename = get_samplename_flex(ordered_dict=ordered_dict, tag=tag)
    if not samplename == '' and not samplename == format_tag(tag):
        return processname + '_' + samplename
    elif tag is not None:
        return processname + format_tag(tag)
    else:
        return processname

# def get_lambdastring(lamb):
#     if lamb == 'best':
#         str = lamb
#     else:
#         str = ('%1.1f' % (lamb)).replace('.', 'p')
#     return str

def get_floatstring(f):
    result = str(f).replace('.', 'p').replace('-', 'm')
    return result



# def get_lambdastring_withpoint(lamb):
#     if lamb == 'best':
#         str = '\'%s\'' % (lamb)
#     else:
#         str = ('%1.1f' % (lamb))
#     return str

def get_floatstring_withpoint(f):
    result = str(f)
    return result

# def lambstr_to_float(lambstr):
#     if lambstr == 'best':
#         result = lambstr
#     else:
#         result = float(lambstr.replace('p', '.'))
#     return result

def floattuple_to_str(t):
    return ','.join(['%s' % str(x) for x in list(t)])

def str_to_floattuple(s):
    return tuple(float(x) for x in s.split(','))

def str_to_inttuple(s):
    return tuple(int(x) for x in s.split(','))

def floatstring_to_float(s):
    result = float(s.replace('p', '.').replace('m', '-'))
    return result

def get_mlq_mps_mch(preferred_configurations, config):
    return (config['mlq'], preferred_configurations[config['mlq']][config['mch']][0], config['mch'])

def is_config_excluded(excluded_configurations, config, processname):
    if not processname in excluded_configurations.keys(): # no config of this proc is excluded
        return False

    if config in excluded_configurations[processname]:
        return True
    else:
        return False

def is_config_excluded_for_process(config, processname, preferred_configurations):
    is_excluded = False
    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=preferred_configurations, config=config)
    if 'PsiPsi' in processname:
        if mps > 13000./2.: #too heavy for 13TeV
            is_excluded = True

    if 'LQLQ' in processname:
        if mlq > 13000./2.: #too heavy for 13TeV
            is_excluded = True
        # now look at decay channels
        if 'PsiChi' in processname:
            if mlq < mps + mch: #LQ cannot decay to psi+chi1
                is_excluded = True
    return is_excluded


def get_config_list(preferred_configurations, processname):
    configs = []

    for mlq in preferred_configurations.keys():
        for mch in preferred_configurations[mlq].keys():
            config = {}
            config['mlq'] = mlq
            config['mch'] = mch
            if not is_config_excluded_for_process(config=config, processname=processname, preferred_configurations=preferred_configurations):
                configs.append(config)
    return configs



# def make_card(card_template_folder, card_output_folder, processname, sampletype, tag, mlq=None, mps=None, mch=None, lamb=None, beta33R=None, beta33L=None, beta32L=None, beta23L=None, bwcutoff=15., lhapdfid=315200, verbose=False):
#     # PDF CMS standard (Paolo):
#     # 2016 LO:       263000
#     # 2016 NLO:      260000
#     # 2017 CP5:      303600
#     # 2018 CP5:      303600 (same as 2017)
#     # 2017/18 CP2:   315200 for 2017/8
#     ensureDirectory(card_output_folder)
#     samplename = get_samplename(mlq=mlq, mps=mps, mch=mch, lamb=lamb, betaR=betaR, beta33L=beta33L, beta32L=beta32L, beta23L=beta23L, tag=tag)
#     if samplename == '':
#         samplename = processname
#     cardbasename = processname + '_template'
#     cardtypes = ['proc_card.dat', 'run_card.dat', 'extramodels.dat', 'customizecards.dat']
#     cards = [card_template_folder + '/' + cardbasename + '_' + c for c in cardtypes]
#
#     newcards = []
#     for card in cards:
#         template = card
#         if not samplename == processname:
#             newcard = card.replace('template', samplename).replace(card_template_folder, card_output_folder)
#         else:
#             newcard = card.replace('template_', '').replace(card_template_folder, card_output_folder)
#         newcards.append(newcard)
#
#         # create newcard
#         command = 'cp %s %s' % (template, newcard)
#         os.system(command)
#
#     if lamb == 'best':
#         lamb = get_best_lambda(mlq)
#     if not samplename == processname:
#         outputfoldername = processname + '_' + samplename
#     else:
#         outputfoldername = processname
#
#
#     # default replacements
#     replacement_dict = {
#         'BWCUTOFF': bwcutoff,
#         'OUTPUT':   outputfoldername,
#         'PDF':      lhapdfid
#     }
#
#
#     # ChiPsi specific
#     if sampletype == 'ChiPsi':
#         replacement_dict['MLQ']    = mlq
#         replacement_dict['MPS']    = mps
#         replacement_dict['MCH']    = mch
#         replacement_dict['MC2']    = int(round(2*mps - mch)) # delta_c2 = 2 * delta_ps => mc2 = 2mps - mch --> As done in paper, but value of mc2 doesn't matter for anomalies or relic abundance. Maybe increase to suppress this channel
#         replacement_dict['MZP']    = int(round(mlq/math.sqrt(2))) # as done in the paper, but doesn't really affect anomalies or relic abundance
#         replacement_dict['LAMBDA'] = lamb
#
#     # LQTChannel specific
#     elif sampletype == 'LQTChannel':
#         replacement_dict['MLQ']    = mlq
#         replacement_dict['LAMBDA'] = lamb
#         replacement_dict['B33R']  = beta33R
#         replacement_dict['B33L']  = beta33L
#         replacement_dict['B23L']  = beta23L
#         replacement_dict['B32L']  = beta32L
#
#     else:
#         raise AttributeError('Unknown sampletype \'%s\'. Add replacement_dict for this type.' % (sampletype))
#
#     # replace values in the cards
#     for card in newcards:
#         replace_placeholders(card=card, replacement_dict=replacement_dict, verbose=verbose)
#     if verbose:
#         print green('--> Done making one set of cards.\n')


def make_card_flex(card_template_folder, card_output_folder, processname, tag, individual_setting, general_settings, verbose=False):
    # PDF CMS standard (Paolo):
    # 2016 LO:       263000
    # 2016 NLO:      260000
    # 2017 CP5:      303600
    # 2018 CP5:      303600 (same as 2017)
    # 2017/18 CP2:   315200 for 2017/8

    ensureDirectory(card_output_folder)
    samplename = get_samplename_flex(individual_setting, tag=tag)
    if samplename == '':
        samplename = processname

    if not samplename == processname:
        outputfoldername = processname + '_' + samplename
    else:
        outputfoldername = processname

    # outputfoldername = 'mg_output'

    cardbasename = processname + '_template'
    cardtypes = ['proc_card.dat', 'run_card.dat', 'extramodels.dat', 'customizecards.dat']
    cards = [card_template_folder + '/' + cardbasename + '_' + c for c in cardtypes]

    newcards = []
    for card in cards:
        template = card
        if not samplename == processname:
            newcard = card.replace('template', samplename).replace(card_template_folder, card_output_folder)
        else:
            newcard = card.replace('template_', '').replace(card_template_folder, card_output_folder)
        newcards.append(newcard)

        # create newcard
        command = 'cp %s %s' % (template, newcard)
        os.system(command)


    replacement_dict = general_settings
    replacement_dict['OUTPUT'] = outputfoldername
    if individual_setting is not None:
        for k in individual_setting:
            if k == 'LAMBDA' and individual_setting[k][0] == 'best':
                replacement_dict[k] = get_best_lambda(individual_setting['MLQ'][0])
            else:
                replacement_dict[k] = individual_setting[k][0]


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



def get_filelist_crossbr(filepath, short, tag):
    postfix = ''

    if short:
        filenames = [f for f in os.listdir(filepath) if isfile(join(filepath, f)) and postfix in f and tag in f and '_short' in f]
    else:
        filenames = [f for f in os.listdir(filepath) if isfile(join(filepath, f)) and postfix in f and tag in f and not '_short' in f]
    return (filenames)

def check_shortfiles(filepath, tag):
    filenames = get_filelist_crossbr(filepath=filepath, short=True, tag=tag)

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



def XsecTotErrPandas(df,crosssectionname,*errnames,**kwargs):
    """Helpfunction to calculate total error."""
    absolute = kwargs.get('abs', False)
    err2 = 0

    for name in errnames:
        err2 += df[name]**2
    toterr = sqrt(err2)
    if not absolute:
        toterr *= df[crosssectionname]/100
    return toterr


def get_all_combinations(preferred_configurations, mlq_stepsize=90, mch_exp_stepsize=0.03):
    all_combinations = {}
    mlq_min = min(preferred_configurations.keys())
    mlq_max = max(preferred_configurations.keys())
    mch_min = 999999999
    mch_max = 0
    for mlq in preferred_configurations.keys():
        for mch in preferred_configurations[mlq].keys():
            mch_min = min(mch_min, mch)
            mch_max = max(mch_max, mch)

    for mlq in range(mlq_min, mlq_max+mlq_stepsize, mlq_stepsize):
        all_combinations[mlq] = []
        for mch_exp in range(int(math.log(mch_min, 10)*100), int(math.log(mch_max, 10)*100) + int(mch_exp_stepsize*100), int(mch_exp_stepsize*100)):
            mch_exp = float(mch_exp / 100.)
            mch = int(round(10**(float(mch_exp))))
            all_combinations[mlq].append(mch)
    return all_combinations


def get_best_lambda(mlq):
    # calculate lambda and round to 3 decimal points
    return float('%.3f' % float(1.1/2. * (mlq/1000.)))

# def findMissingFilesT2(filepath, filename_base, maxindex, treename='Events'):
#     missing_indices = []
#     filename_base = filepath+'/'+filename_base
#     pbar = tqdm(range(maxindex), desc="Files checked")
#     for idx in pbar:
#         filename = filename_base + '_' + str(idx+1) + '.root'
#
#         try:
#             f = TFile.Open(filename)
#             tree = f.Get(treename)
#             n_genevents = tree.GetEntriesFast()
#         except AttributeError:
#             print yellow('  --> Couldn\'t open file or tree, adding it to list of missing indices: %s.' % (filename))
#             missing_indices.append(idx)
#         except ReferenceError:
#             print yellow('  --> File is damaged, adding it to list of missing indices: %s.' % (filename))
#             missing_indices.append(idx)
#         try:
#             f.Close()
#         except:
#             pass
#     return missing_indices



def findMissingFilesT3(filepath, filename_base, maxindex, generation_step):
    missing_indices = []
    filename_base = filepath+'/'+filename_base
    pbar = tqdm(range(maxindex), desc="Files checked")
    for idx in pbar:
        filename = filename_base + '_' + str(idx+1) + '.root'
        n_genevents = count_genevents_in_file(filename, treename='AnalysisTree')
        if n_genevents is None:
            missing_indices.append(idx)

    return missing_indices



def count_genevents_in_file(filename, treename='Events'):
    n_genevents = None
    try:
        f = TFile.Open(filename)
        if not f:
            print yellow('  --> File is a nullptr, raising error: %s.' % (filename))
            raise ReferenceError()
        if f.IsZombie():
            print yellow('  --> File is a zombie, raising error: %s.' % (filename))
            raise ReferenceError()
        is_recovered = f.TestBit(ROOT.TFile.kRecovered)
        if is_recovered:
            print yellow('  --> File had to be recovered, raising error: %s.' % (filename))
            raise ReferenceError()
        tree = f.Get(treename)
        n_genevents = tree.GetEntriesFast()
    except AttributeError:
        print yellow('  --> Couldn\'t open file or tree: %s.' % (filename))
    except ReferenceError:
        print yellow('  --> File is damaged: %s.' % (filename))
    try:
        f.Close()
        del f
    except:
        pass
    return n_genevents







def getcmsRunCommand(pset, outfilename, N, ncores, infilename=None, gridpack=None):
    """Submit PSet config file and gridpack to SLURM batch system."""

    if gridpack is not None and infilename is None:
        command = 'cmsRun %s gridpack=%s outfilename=%s nevents=%i nThreads=%i' % (pset, gridpack, outfilename, N, ncores)
    elif infilename is not None and gridpack is None:
        command = 'cmsRun %s infilename=%s outfilename=%s nevents=%i nThreads=%i' % (pset, infilename, outfilename, N, ncores)
    return command
