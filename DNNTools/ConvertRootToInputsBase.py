import os, ROOT
import pandas as pd
from collections import OrderedDict
from root_numpy import root2array, rec2array
from printing_utils import green, blue
from DNNutils import ClearFolder, SavePandas

def ConvertRoot2Pandas(input_filename, output_filename, treename, start, stop, branches, columns, category):
    mymatrix = rec2array(root2array(filenames=input_filename, treename=treename, branches=branches, start=start, stop=stop))
    df = pd.DataFrame(mymatrix,columns=columns)
    df['category'] = [category]*len(df)
    SavePandas(df, output_filename)
    print(green('      --> Done with file number: %i' % (stop/(stop-start))))

def Root2Pandas(input_filename, output_filename, output_folder, branches, columns, chunksize, treename, category, run_on):
    if len(branches)!= len(columns):
        raise ValueError('Branches and columns have different lenght: '+str(len(branches))+', '+str(len(columns)))
    print(green('  --> Creating numpy arrays for input sample %s' % (input_filename)))
    inputfile = ROOT.TFile.Open(input_filename)
    tree = inputfile.Get(treename)
    entries = tree.GetEntriesFast()
    inputfile.Close()

    maxidx = int(entries/float(chunksize)) + 1
    if entries % chunksize == 0:
        maxidx -= 1
    print(green('    --> Producing %i files with %i events each.' % (maxidx, chunksize)))
    info = OrderedDict([
        ('input_filename',  input_filename),
        ('output_filename', ''),
        ('treename',        treename),
        ('start',           0),
        ('stop',            0),
        ('branches',        branches),
        ('columns',         columns),
        ('category',        category),
    ])

    if run_on.isdigit():
        print(green('    --> Running locally using %s cores.' % (run_on)))
        from multiprocessing import Process
        processes = []
        for i in range(maxidx):
            outname = os.path.join(output_folder, '%s_%i.pkl' % (output_filename, i))
            info.update({'start': i*chunksize, 'stop': (i+1)*chunksize, 'output_filename': outname})
            # ConvertRoot2Pandas(**info)
            processes.append(Process(target=ConvertRoot2Pandas, args=tuple(info.values())))
            if (i+1)%int(run_on)==0:
                for process in processes:
                    process.start()
                for process in processes:
                    process.join()
                del processes[:]
    elif run_on=='htcondor':
        print(green('    --> Submitting to htcondor...'))
        from Submitter.CondorBase import CondorBase
        CB = CondorBase(JobName='Root2Pandas_'+output_filename)
        CB.CreateJobInfo()
        CB.ModifyJobInfo('x509userproxy', '/user/'+os.getenv('USER')+'/tmp/x509up')
        CB.ModifyJobInfo('use_x509userproxy', 'True')
        CB.ModifyJobInfo('outdir', output_folder+'/joboutput_'+output_filename+'/')
        job_exes = []
        for i in range(maxidx):
            outname = os.path.join(output_folder, '%s_%i.pkl' % (output_filename, i))
            info.update({'start': i*chunksize, 'stop': (i+1)*chunksize, 'output_filename': outname})
            exe = outname.replace(output_filename,'submit_condor_'+output_filename).replace('.pkl','.py')
            with open(exe, "w") as f_:
                f_.write('#!/usr/bin/env python\n')
                f_.write('from collections import OrderedDict\n')
                f_.write('from DNNTools.ConvertRootToInputsBase import ConvertRoot2Pandas\n')
                f_.write('\ninfo='+str(info)+'\n\n')
                f_.write('ConvertRoot2Pandas(**info)\n')
            os.system('chmod +x '+exe)
            job_exes.append(exe)
        CB.SubmitManyJobs(job_exes=job_exes)
    else: raise ValueError('Not implemented option for run_on= '+run_on)



class ConvertRootToInputsBase():
    def __init__(self, inputdir, outdir, chunksize=200000, treename='AnalysisTree', namebranch_weight=('Events.GenEvent.Event.weight','event_weight'), run_on='1'):
        self.inputdir = inputdir
        self.outdir = outdir
        self.chunksize = chunksize
        self.treename = treename
        self.namebranch_weight = namebranch_weight
        self.run_on = run_on

    def LoadDependanciesBase(self, libname='libLEAFClasses.so'):
        ROOT.gSystem.Load(libname)

    def LoadDependancies(self, classname=None):
        self.LoadDependanciesBase()
        if classname:
            self.LoadDependanciesBase(classname)

    def DefineSamples(self):
        raise NotImplementedError('DefineSamples method is not initialized. Fix this.')

    def DefineVariables(self):
        raise NotImplementedError('DefineVariables method is not initialized. Fix this.')

    def Convert(self):
        samples = self.DefineSamples()
        branches, columns = self.DefineVariables()
        branches.append(self.namebranch_weight[0])
        columns.append(self.namebranch_weight[1])
        ClearFolder(self.outdir)
        vars = {
            'output_folder':self.outdir,
            'branches':branches,
            'columns':columns,
            'chunksize':self.chunksize,
            'treename':self.treename,
            'run_on':self.run_on,
        }
        for name, info in samples.items():
            vars.update({
                'input_filename':os.path.join(self.inputdir, info.filename),
                'output_filename':info.samplename,
                'category':info.category,
                })
            Root2Pandas(**vars)
