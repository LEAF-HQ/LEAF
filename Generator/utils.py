# Author: Arne Reimers
import os, sys
from fnmatch import fnmatch
import subprocess
import time
from preferred_configurations import *
from bisect import bisect_left
from constants import *
import distutils

from multiprocessing import Pool, Queue
import ROOT


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

def getoutput_commands_parallel(commands=[], ncores=10, max_time=10, do_nice=True, niceness=10, level=0):
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
        sys.stdout.write( green('  --> {0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(n_completed, n_jobs, percent)))
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

    if level > 1:
        return outputs
    if len(commands_resub) > 0:
        print yellow('\n  --> Resubmitting %i jobs.' % (len(commands_resub)))
        resub_outputs = getoutput_commands_parallel(commands_resub, max_time=max_time, level=level+1)
        for o in resub_outputs:
            outputs.append(o)
    return outputs

def format_runtime(hms):
    if not type(hms) == tuple: raise AttributeError('format_runtime needs to be passed a tuple as argument, containing the hours and minutes and seconds of runtime.')
    (h, m, s) = hms
    if s >=60 or m >= 60: raise ValueError('Minutes and seconds must be < 60, instead increase the hours or minutes.')
    if h > 24 or (h == 24 and (m > 0 or s > 0)): raise ValueError('Maximum runtime is 24, 0, 0.')

    runtime_str = '%02i:%02i:%02i' % (hms)
    if h == 24:
        runtime_str = '1-00:00:00'

    total_seconds = h*3600 + m*60 + s
    min_matching_qtime = min(i for i in slurm_queues_runtimes.keys() if i*3600 >= total_seconds)
    queue = slurm_queues_runtimes[min_matching_qtime]
    return (runtime_str, queue)

def tuplize_runtime(hms):
    if not type(hms) == str: raise AttributeError('format_runtime needs to be passed a string as argument, containing the hours and minutes and seconds of runtime separated by colons.')
    parts = hms.split(':')
    (h, m, s) = (int(parts[0]), int(parts[1]), int(parts[2]))
    if s >=60 or m >= 60: raise ValueError('Minutes and seconds must be < 60, instead increase the hours or minutes.')
    if h > 24 or (h == 24 and (m > 0 or s > 0)): raise ValueError('Maximum runtime is 24, 0, 0.')

    runtime_str = '%02i:%02i:%02i' % (h, m, s)
    if h == 24:
        runtime_str = '1-00:00:00'

    total_seconds = h*3600 + m*60 + s
    min_matching_qtime = min(i for i in slurm_queues_runtimes.keys() if i*3600 >= total_seconds)
    queue = slurm_queues_runtimes[min_matching_qtime]
    return ( (h,m,s), queue, runtime_str )


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


def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in xrange(0, len(lst), n):
        yield lst[i:i + n]


def execute_function_parallel(func, argumentlist, ncores=10):
    """
    Executes a function once per argument in argumentlist.

    Assumes the function takes exactly one argument.

    Does not return any output the function might produce or return
    """
    pool = Pool(processes=ncores)
    result = pool.map(func, argumentlist)
    pool.terminate()
    pool.close()



def hadd_large(outfilename, infilelist, force, notree, maxsize=int(5E11)): #default maxsize: 300GB (standard root: 100)
    ROOT.TTree.SetMaxTreeSize(maxsize)
    rm = ROOT.TFileMerger(False)
    rm.SetFastMethod(True)
    rm.SetNotrees(notree)

    for f in infilelist:
        rm.AddFile(f)

    rm.OutputFile(outfilename, force)
    rm.Merge()



def hadd_large_singlearg(arg): #default maxsize: 300GB (standard root: 100), good to be used with 'execute_function_parallel'
    singleargs = arg.split('---')
    outfilename = singleargs[0]
    infilestring = singleargs[1]
    infilelist = infilestring.split(' ')
    if singleargs[2] == 'True':
        force = True
    elif singleargs[2] == 'False':
        force = False
    else:
        raise ValueError('Invalid value for (singleargs[2])')

    if singleargs[3] == 'True':
        notree = True
    elif singleargs[3] == 'False':
        notree = False
    else:
        raise ValueError('Invalid value for (singleargs[3])')
    # print outfilename, infilelist, force, notree
    if len(singleargs) > 4:
        maxsize = int(singleargs[4])
        hadd_large(outfilename=outfilename, infilelist=infilelist, force=force, notree=notree, maxsize=maxsize)
    else:
        hadd_large(outfilename=outfilename, infilelist=infilelist, force=force, notree=notree)


def get_intersection(g1, g2):

    # find intersetion between two TGraphs

    result = None

    #find highest and lowest x:
    xmin = max(g1.GetX()[0], g2.GetX()[0] )
    xmax = min(g1.GetX()[g1.GetN()-1], g2.GetX()[g2.GetN()-1])

    # iteratively find intersection, by evaluating graphs at xmin, xmax, moving one of them, and repeating
    # ====================================================================================================
    y1lo = g1.Eval(xmin)
    y2lo = g2.Eval(xmin)
    y1hi = g1.Eval(xmax)
    y2hi = g2.Eval(xmax)
    if (y1lo < y2lo and y1hi < y2hi) or (y1lo > y2lo and y1hi > y2hi):
        # raise ValueError('graphs 1 and 2 either have no or multiple intersections')
        return None

    # find higher graph at xmin
    g1_from_top = True if y1lo > y2lo else False

    xmid = xmin + (xmax-xmin)/2.
    while math.fabs(xmin-xmax) > 1:
        y1mid = g1.Eval(xmid)
        y2mid = g2.Eval(xmid)
        if g1_from_top:
            if y1mid > y2mid:
                xmin = xmid
            else:
                xmax = xmid
        elif not g1_from_top:
            if y1mid > y2mid:
                xmax = xmid
            else:
                xmin = xmid
        xmid = xmin + (xmax-xmin)/2.

    return xmid
