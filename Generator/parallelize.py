# Author: Arne Reimers & Andrea Malara
import os, sys, time, glob
import functools
import subprocess
from multiprocessing import Pool
from printing_utils import blue, red

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
def MultiProcess(func,arglist,ncores=10):
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

def updateCouting(n_completed, n_jobs, time_to_sleep):
    sys.stdout.write(blue('  --> %d of %d (%.1f%%) jobs done.\r' %(n_completed, n_jobs, round(float(n_completed)/float(n_jobs)*100, 1))))
    sys.stdout.flush()
    time.sleep(time_to_sleep)

@timeit
def parallelize(commands, getoutput=False, logfiles=[], ncores=10, cwd=False, niceness=10, remove_temp_files=True, time_to_sleep = 0.5):
    processes, outputs, log_files = ({},{}, {})
    n_running, n_completed, n_jobs = (0,0, len(commands))
    is_log_given = not getoutput and len(logfiles)==n_jobs
    for index, command in enumerate(commands):
        cwd_ = command[0]  if cwd else None
        proc = command[1:] if cwd else command
        if isinstance(proc, list):
            proc = ' '.join(proc)
        if niceness is not None:
            proc = 'nice -n %i %s' % (niceness, proc)
        if getoutput:
            if not isinstance(proc, str):
                raise RuntimeError(red('getoutput supports only commands as string. Please fix this.'))
            processes[index] = subprocess.Popen(proc, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=cwd_)
        else:
            log_files[index] = open(list_logfiles[index] if is_log_given else os.path.join(cwd_ if cwd_ else '','parallelize_log_'+str(index)+'.txt'),'w')
            processes[index] = subprocess.Popen(proc, stdout=log_files[index], stderr=log_files[index], shell=True, cwd=cwd_)
        n_running += 1
        while (n_running >= ncores):
            for idx, proc in processes.items():
                if proc.poll() != None:
                    proc.wait()
                    n_running -= 1
                    n_completed += 1
                    if getoutput:
                        output = proc.communicate()
                        outputs[idx] = {'stdout': output[0],'stderr': output[1],'returncode':str(proc.returncode)+' '+commands[idx]}
                    else:
                        log_files[idx].close()
                    del processes[idx]
            updateCouting(n_completed, n_jobs, time_to_sleep if len(commands) < 10000 else time_to_sleep/10000.)
    while (n_completed < n_jobs):
        for idx, proc in processes.items():
            if proc.poll() != None:
                n_completed += 1
                if getoutput:
                    output = proc.communicate()
                    outputs[idx] = {'stdout': output[0],'stderr': output[1],'returncode':proc.returncode}
                else:
                    log_files[idx].close()
                del processes[idx]
        updateCouting(n_completed, n_jobs, time_to_sleep if len(commands) < 10000 else time_to_sleep/10000.)
    print(blue('\nAll jobs completed'))
    if remove_temp_files:
        a = map(os.remove, [x.name for x in log_files.values()])
    return outputs
