# Author: Arne Reimers
import os, sys
from fnmatch import fnmatch
import subprocess
import time
from preferred_configurations import *
from bisect import bisect_left


def ensureDirectory(dirname, use_se=False):
    """Make directory if it does not exist."""
    if use_se:
        # print dirname
        command = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-mkdir -p %s' % (dirname)
        execute_command_silent(command)
    else:
        if not os.path.exists(dirname):
            os.makedirs(dirname)
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

def execute_command_silent(command):
    DEVNULL = open(os.devnull, 'wb')
    p = subprocess.Popen(command, stdout=DEVNULL, stderr=DEVNULL, shell=True)
    p.wait()
    DEVNULL.close()

def execute_commands_parallel(commands=[], ncores=10, niceness=10):
    n_running = 0
    n_completed = 0
    n_jobs = len(commands)
    processes = []
    DEVNULL = open(os.devnull, 'wb')
    for c in commands:
        if niceness is not None:
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
        # p = subprocess.Popen(c, shell=True)
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

def getoutput_commands_parallel(commands=[], ncores=10, max_time=10, do_nice=True, niceness=10):
    n_running = 0
    n_completed = 0
    n_jobs = len(commands)
    outputs = []
    processes = []
    commands_resub = []
    n_completed = 0
    for tuple in commands:
        c = tuple[0]
        info = tuple[1]
        if do_nice: c = 'nice -n %i %s' % (niceness, c)
        b_wait = (n_running >= ncores)
        while b_wait:
            n_running = 0
            # n_completed = 0
            for tuple in processes:
                proc = tuple[0]
                if proc.poll() == None:
                    n_running += 1
                else:
                    n_completed += 1
                    outputs.append((tuple[0].communicate()[0], tuple[1]))
                    proc.stdout.close()
                    processes.remove(tuple)
            percent = round(float(n_completed)/float(n_jobs)*100, 1)
            sys.stdout.write( '{0:d} of {1:d} ({2:4.2f}%) jobs done.\r'.format(n_completed, n_jobs, percent))
            sys.stdout.flush()
            time_to_sleep = 0.5
            if len(commands) > 10000:
                time_to_sleep = time_to_sleep/10000.
            time.sleep(time_to_sleep)
            b_wait = (n_running >= ncores)

        n_running += 1
        p = subprocess.Popen(c, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        processes.append((p, info, c))
    # submitted all jobs, now just wait.
    b_wait = (n_completed < n_jobs)
    time_gone = 0
    while b_wait:
        n_running = 0
        # n_completed = 0
        for tuple in processes:
            proc = tuple[0]
            if proc.poll() == None:
                n_running += 1
            else:
                n_completed += 1
                outputs.append((tuple[0].communicate()[0], tuple[1]))
                proc.stdout.close()
                processes.remove(tuple)
        percent = float(n_completed)/float(n_jobs)*100
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(n_completed, n_jobs, percent))
        sys.stdout.flush()
        timestep = 2
        time.sleep(timestep)
        time_gone += timestep
        b_wait = (n_completed < n_jobs) and (time_gone < max_time)
    resub_outputs = []
    for tuple in processes:
        if tuple[0].poll() is not None:
            outputs.append((tuple[0].communicate()[0], tuple[1]))
        else:
            tuple[0].kill()
            commands_resub.append((tuple[2].split('nice -n %i ' % (niceness))[1], tuple[1]))
            # tuple[0].stdout.close()
    if len(commands_resub) > 0:
        resub_outputs = getoutput_commands_parallel(commands_resub, max_time=max_time)
        for o in resub_outputs:
            outputs.append(o)
    return outputs


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
