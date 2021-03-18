import os, sys, math
from ROOT import TFile

def get_number_events_in_dataset(dataset, treename='AnalysisTree'):
    nevents = 0
    infiles_filled = []
    for infile in dataset.infiles:
        f = TFile(str(infile))
        try:
            n = f.Get(treename).GetEntriesFast()
            if n > 0:
                nevents += n
                infiles_filled.append(infile)
        except:
            print yellow('--> Inputfile does not contain TTree named \'%s\'.' % (treename))
        f.Close()
    dataset.infiles = infiles_filled
    return nevents
