# Author: Arne Reimers
import os, sys
from fnmatch import fnmatch
import subprocess
import time
from preferred_configurations import *
from bisect import bisect_left


def ensureDirectory(dirname):
    """Make directory if it does not exist."""
    if not os.path.exists(dirname):
        os.makedirs(dirname)
        print '>>> made directory "%s"'%(dirname)
        if not os.path.exists(dirname):
            print '>>> failed to make directory "%s"'%(dirname)
    return dirname


def is_file_empty(file_path):
    """ Check if file is empty by confirming if its size is 0 bytes"""
    # Check if file exist and it is empty
    return os.path.exists(file_path) and os.stat(file_path).st_size == 0

def green(string):
    return "\x1b[0;32m%s\033[0m"%string

def yellow(string):
    return "\x1b[0;33m%s\033[0m"%string

def red(string):
    return "\x1b[0;31m%s\033[0m"%string

def blue(string):
    return "\x1b[0;34m%s\033[0m"%string

def bold(string):
    return "\033[1m%s\033[0m"%string




def get_samplename(mlq, mps, mch, lamb, tag):
    return 'MLQ%i_MPS%i_MC1%i_L%s%s' % (mlq, mps, mch, get_lambdastring(lamb), format_tag(tag))

def get_jobname(processname, mlq, mps, mch, lamb, tag):
    return processname + '_' + get_samplename(mlq, mps, mch, lamb, tag)

def get_lambdastring(lamb):
    return ('%1.1f' % (lamb)).replace('.', 'p')

def get_mlq_mps_mch(config):
    # return (config['mlq'], config['mps'], config['mch'])
    return (config['mlq'], preferred_configurations[config['mlq']][config['mch']][0], config['mch'])

def is_config_excluded(excluded_configurations, config, processname):
    if not processname in excluded_configurations.keys(): # no config of this proc is excluded
        return False

    if config in excluded_configurations[processname]:
        return True
    else:
        return False



def format_tag(tag):
    formatted = ('_' + tag.strip('_')) if not tag == '' else ''
    return formatted

def execute_commands_parallel(commands=[], ncores=10, niceness=10):
    n_running = 0
    n_completed = 0
    n_jobs = len(commands)
    processes = []
    DEVNULL = open(os.devnull, 'wb')
    for c in commands:
        c = 'nice -n %i %s' % (niceness, c)
        b_wait = (n_running >= ncores)
        while b_wait:
            n_running = 0
            n_completed = 0
            for proc in processes:
                if proc.poll() == None:
                    n_running += 1
                else:
                    n_completed += 1
            percent = round(float(n_completed)/float(n_jobs)*100, 1)
            sys.stdout.write( '{0:d} of {1:d} ({2:4.2f}%) jobs done.\r'.format(n_completed, n_jobs, percent))
            sys.stdout.flush()
            time.sleep(.5)
            b_wait = (n_running >= ncores)
        n_running += 1
        p = subprocess.Popen(c, stdout=DEVNULL, stderr=DEVNULL, shell=True)
        processes.append(p)
    # submitted all jobs, now just wait.
    b_wait = (n_completed < n_jobs)
    while b_wait:
        n_running = 0
        n_completed = 0
        for proc in processes:
            if proc.poll() == None: n_running += 1
            else:                   n_completed += 1
        percent = float(n_completed)/float(n_jobs)*100
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(n_completed, n_jobs, percent))
        sys.stdout.flush()
        time.sleep(2)
        b_wait = (n_completed < n_jobs)
    DEVNULL.close()


def find_closest(myList, myNumber):
    """
    Assumes myList is sorted. Returns closest value to myNumber.

    If two numbers are equally close, return the smallest number.
    """
    pos = bisect_left(myList, myNumber)
    if pos == 0:
        return myList[0]
    if pos == len(myList):
        return myList[-1]
    before = myList[pos - 1]
    after = myList[pos]
    if after - myNumber < myNumber - before:
       return after
    else:
       return before
