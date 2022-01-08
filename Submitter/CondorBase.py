import os, json
import htcondor
from utils import *

import htcondor

def green(string):
    return "\x1b[0;32m%s\033[0m"%string

def yellow(string):
    return "\x1b[0;33m%s\033[0m"%string

def red(string):
    return "\x1b[0;31m%s\033[0m"%string

def blue(string):
    return "\x1b[0;34m%s\033[0m"%string

def bold(string):
    return "\033[1m%s\033[0m"%strin

def prettydic(d, indent=8, color=blue):
    space = max([0]+[len(str(x)) for x in d])+2
    for key, value in d.items():
        print(color(" "*indent + str(key))),
        if isinstance(value, dict):
            print ""
            prettydic(value, len(" "*indent + str(key)+" "*(space+1-len(str(key)))))
        else:
            print(color(" "*(space-len(str(key))) + str(value)))

class CondorBase():
    def __init__(self, JobName = 'test', Memory = 2, Disk = 1):
        self.Memory = str(int(Memory)*1024)
        self.Disk   = str(int(Disk)*1024*1024)
        self.JobName = JobName
        self.UserEmail = 'andrea.malara@cern.ch'
        self.CreateShedd()

    def CreateShedd(self):
        self.schedd = htcondor.Schedd(htcondor.Collector().locate(htcondor.DaemonTypes.Schedd))

    def CreateJobInfo(self, executable="", arguments=""):
        if not hasattr(self, 'JobInfo'): self.JobInfo = {}
        outputname = str(self.JobName)+'_$(ClusterId)_$(ProcId)'
        self.JobInfo = {
            'universe':             'vanilla',
            'executable':           executable,                    # the program to run on the execute node
            'arguments':            arguments,                     # sleep for 10 seconds
            'JobBatchName':         str(self.JobName),             # name of the submitted job
            'outdir':               './log/',                      # directory to store log/out/err files from htcondor
            'output':               '$(outdir)'+outputname+'.out', # storage of stdout
            'error':                '$(outdir)'+outputname+'.err', # storage of stderr
            'log':                  '$(outdir)'+outputname+'.log', # storage of job log info
            'stream_output':        'True',                        # should transfer output file during the run.
            'stream_error':         'True',                        # should transfer error file during the run.
            'RequestCpus':          '1',                           # requested number of CPUs (cores)
            'RequestMemory':        self.Memory,                   # memory in GB
            'RequestDisk':          self.Disk,                     # disk space in GB
            'notify_user':          self.UserEmail,                  # send an email to the user if the notification condition is set. Doens't work FIXME
            'notification':         'Always',                        # Always/Error/Done Doens't work FIXME
            'getenv':               'True',                        # port the local environment to the cluster
            'hold': 'True',                                        # to start jobs in hold (eg. debugging)
            # 'transfer_executable':  'True',                        # copy the executable to the cluster Doens't work FIXME
            'WhenToTransferOutput': 'ON_EXIT_OR_EVICT',                     # specify when to transfer the outout back. Not tested yet
            # 'requirements':          "OpSysAndVer == 'CentOS7'",   # additional requirements. Not tested yet
            # '+RequestRuntime':       str(int(nHours*60*60)),       # requested run time. Not tested yet
            }

    def ModifyJobInfo(self,name,info):
        if not hasattr(self, 'JobInfo'): self.CreateJobInfo()
        self.JobInfo[name] = info

    def SubmitJob(self):
        if self.JobInfo['executable'] == "":
            raise ValueError("No executable passed. Please check")
        ensureDirectory(self.JobInfo["outdir"])
        submit_result = self.schedd.submit(htcondor.Submit(self.JobInfo)) # submit the job
        ClusterId = str(submit_result.cluster())
        ProcId = str(submit_result.first_proc())
        self.ModifyJobInfo('ClusterId', ClusterId)
        self.ModifyJobInfo('ProcId', ProcId)
        self.StoreJobInfo(extrainfo="_"+str(ClusterId)+"_"+str(ProcId))

    def SubmitManyJobs(self, job_args = [], job_exes = []):
        ensureDirectory(self.JobInfo["outdir"])
        sub = htcondor.Submit(self.JobInfo)
        if len(job_exes) == 0:
            if self.JobInfo['executable'] == "":
                raise ValueError("No executable passed. Please check")
            jobs = [ {'arguments': arg } for arg in job_args]
        elif len(job_exes) == len(job_args):
            jobs = [ {'arguments': job_args[n], 'executable': job_exes[n], } for n in range(len(job_args))]
        else:
            raise ValueError(red('Something is wrong in the SubmitManyJobs parameters'))
        with self.schedd.transaction() as txn:
            submit_result = sub.queue_with_itemdata(txn,1,iter(jobs))
            print submit_result.clusterad()['RequestDisk']
            print submit_result.clusterad()['RequestMemory']
            self.ModifyJobInfo('ClusterId',str(submit_result.cluster()))
            self.ModifyJobInfo('ExtraInfo', jobs)
            self.StoreJobInfo()

    def CheckStatus(self):
        for job in self.schedd.xquery(constraint = 'ClusterId == {}'.format(self.JobInfo['ClusterId']), ):
            print(repr(job))

    def StoreJobInfo(self, extrainfo=""):
        with open(self.JobInfo['outdir']+'JobInfo'+extrainfo+'.json', 'w') as f:
            json.dump(self.JobInfo, f, sort_keys=True, indent=4)

    def LoadJobInfo(self):
        with open(filename, 'r') as f:
            self.JobInfo = json.load(fp)

    def PrintJobInfo(self):
        print(blue("--> JobInfo"))
        prettydic(self.JobInfo)
