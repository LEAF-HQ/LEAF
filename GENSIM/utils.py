# Author: Izaak Neutelings (October, 2019)
import os, sys
from fnmatch import fnmatch
import subprocess
import time
from preferred_configurations import *

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

def format_tag(tag):
    formatted = ('_' + tag.strip('_')) if not tag == '' else ''
    return formatted

def execute_commands_parallel(commands=[], ncores=10):
    n_running = 0
    n_completed = 0
    n_jobs = len(commands)
    processes = []
    for c in commands:
        b_wait = (n_running >= ncores)
        while b_wait:
            n_running = 0
            n_completed = 0
            for proc in processes:
                if proc.poll() == None: n_running += 1
                else:
                    n_completed += 1
            percent = round(float(n_completed)/float(n_jobs)*100, 1)
            sys.stdout.write( '{0:d} of {1:d} ({2:4.2f}%) jobs done.\r'.format(n_completed, n_jobs, percent))
            sys.stdout.flush()
            time.sleep(10)
            b_wait = (n_running >= ncores)
        n_running += 1
        p = subprocess.Popen(c, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
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
        time.sleep(10)
        b_wait = (n_completed < n_jobs)
