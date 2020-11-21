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
        print green('--> made directory "%s"'%(dirname))
        if not os.path.exists(dirname):
            print yellow('--> failed to make directory "%s"'%(dirname))
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
            time_to_sleep = 0.5
            if len(commands) > 10000:
                time_to_sleep = time_to_sleep/10000.
            time.sleep(time_to_sleep)
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
