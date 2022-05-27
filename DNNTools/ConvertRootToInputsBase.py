import os, ROOT
import numpy as np
import pandas as pd
from root_numpy import root2array, rec2array
from utils import ensureDirectory
from printing_utils import *

def CleanFile(fname):
    if os.path.exists(fname):
        os.remove(fname)

def SavePandas(obj, fname):
    CleanFile(fname)
    obj.to_pickle(fname)

def SaveNumpy(obj, fname):
    CleanFile(fname)
    np.save(fname, obj)


def Root2Pandas(input_filename, output_filename, output_folder, branches, chunksize, treename, label):
    ensureDirectory(output_folder)
    print green('  --> Creating numpy arrays for input sample %s' % (input_filename))
    inputfile = ROOT.TFile.Open(input_filename)
    tree = inputfile.Get(treename)
    entries = tree.GetEntriesFast()
    inputfile.Close()

    maxidx = int(entries/float(chunksize)) + 1
    if entries % chunksize == 0:
        maxidx -= 1
    print green('    --> Producing %i files with %i events each.' % (maxidx, chunksize))
    for i in range(maxidx):
        print green('      --> Working on file number: %i (%3.2f%%)' % (i+1, float(i+1)/maxidx * 100.))
        start, stop = (i*chunksize,(i+1)*chunksize)
        mymatrix = rec2array(root2array(filenames=input_filename, treename=treename, branches=branches, start=start, stop=stop))
        df = pd.DataFrame(mymatrix,columns=branches)
        df['label'] = [label]*len(df)
        outname = os.path.join(output_folder, '%s_%i.pkl' % (output_filename, i))
        SavePandas(df, outname)

class ConvertRootToInputsBase():
    def __init__(self, inputdir, outdir, chunksize=200000, treename='AnalysisTree', namebranch_weight='Events.GenEvent.Event.weight'):
        self.inputdir = inputdir
        self.outdir = outdir
        self.chunksize = chunksize
        self.treename = treename
        self.namebranch_weight = namebranch_weight

    def LoadDependanciesBase(self, libname='libLEAFClasses.so'):
        ROOT.gSystem.Load(libname)

    def LoadDependancies(self, classname=None):
        self.LoadDependanciesBase()
        if classname:
            self.LoadDependanciesBase(classname)

    def DefineVariables(self):
        varnames = []
        return varnames

    def DefineSamples(self):
        samples = []
        return samples

    def Convert(self):
        ensureDirectory(self.outdir)
        variables = self.DefineVariables()
        variables.append(self.namebranch_weight)
        samples = self.DefineSamples()
        for samplename in samples:
            label = samples[samplename].category
            infilename = os.path.join(self.inputdir, 'MC__%s.root' % (samplename))
            Root2Pandas(infilename, samplename, self.outdir, variables, chunksize=self.chunksize, treename=self.treename, label=label)
