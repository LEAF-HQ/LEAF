# Author: Arne Reimers & Andrea Malara
import os, sys, time, glob
import functools
import subprocess
from multiprocessing import Pool
from printing_utils import blue, red

class SimpleNamespace:
    def __init__(self, **kwargs):
        self.__dict__.update(kwargs)
    def __repr__(self):
        items = (str(k)+'='+str(v) for k, v in self.__dict__.items())
        return "{}({})".format(type(self).__name__, ", ".join(items))
    def __eq__(self, other):
        if isinstance(self, SimpleNamespace) and isinstance(other, SimpleNamespace):
           return self.__dict__ == other.__dict__
        return NotImplemented

def timeit(method):
    @functools.wraps(method)
    def timed(*args, **kw):
        print(blue('--> Start of %r' %(method.__name__)))
        ts = time.time()
        result = method(*args, **kw)
        te = time.time()
        if 'log_time' in kw:
            name = kw.get('log_name', method.__name__.upper())
            kw['log_time'][name] = int((te - ts))
        else:
            print(blue('--> End of %r: %2.2f s' % (method.__name__, (te - ts))))
        return result
    return timed


@timeit
def MultiProcess(func,arglist,ncores=8):
    global func_singlearg
    def func_singlearg(kwargs):
        return func(**kwargs)
    pool = Pool(processes=int(ncores))
    pool.imap_unordered(func_singlearg, arglist)
    result = [i for i in pool.imap_unordered(func_singlearg, arglist)]
    pool.close()
    pool.join()
    del globals()['func_singlearg']
    return result

@timeit
def parallelize(commands, getoutput=False, logfiles=[], ncores=8, cwd=False, niceness=10, remove_temp_files=True, time_to_sleep = 0.5):
    def wait_for_process(sn):
        for idx, proc in sn.processes.items():
            if proc.poll() != None:
                proc.wait()
                sn.n_running -= 1
                sn.n_completed += 1
                if sn.getoutput:
                    output = proc.communicate()
                    sn.outputs[idx] = {'stdout': output[0],'stderr': output[1],'returncode':proc.returncode, 'command':sn.commands[idx]}
                else:
                    sn.log_files[idx].close()
                del sn.processes[idx]
        sys.stdout.write(blue('  --> %d of %d (%.1f%%) jobs done.\r' %(sn.n_completed, sn.n_jobs, round(float(sn.n_completed)/float(sn.n_jobs)*100, 1))))
        sys.stdout.flush()
        time.sleep(sn.time_to_sleep)
    #to be used in python3
    # from types import SimpleNamespace
    sn = SimpleNamespace(processes={}, outputs={}, log_files={},
                         commands=commands, getoutput=getoutput,
                         n_running=0, n_completed=0, n_jobs=len(commands),
                         time_to_sleep = time_to_sleep if len(commands) < 10000 else time_to_sleep/10000.
                         )
    is_log_given = not sn.getoutput and len(logfiles)==sn.n_jobs
    for index, command in enumerate(sn.commands):
        cwd_ = command[0]  if cwd else None
        proc = command[1:] if cwd else command
        if isinstance(proc, list):
            proc = ' '.join(proc)
        if niceness is not None:
            proc = 'nice -n %i %s' % (niceness, proc)
        if not isinstance(proc, str):
            raise RuntimeError(red('getoutput supports only commands as string. Please fix this.'))
        if sn.getoutput:
            stdout = subprocess.PIPE
            stderr = subprocess.STDOUT
        else:
            sn.log_files[index] = open(logfiles[index] if is_log_given else os.path.join(cwd_ if cwd_ else '','parallelize_log_'+str(index)+'.txt'),'w')
            stdout = sn.log_files[index]
            stderr = sn.log_files[index]
        sn.processes[index] = subprocess.Popen(proc, stdout=stdout, stderr=stderr, shell=True, cwd=cwd_)
        sn.n_running += 1
        while (sn.n_running >= ncores):
            wait_for_process(sn)
    while (sn.n_completed < sn.n_jobs):
        wait_for_process(sn)
    if remove_temp_files:
        a = map(os.remove, [x.name for x in sn.log_files.values()])
    return sn.outputs
