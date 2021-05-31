import os, sys, math, copy
from ROOT import TFile
import subprocess

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



def order_haddlist(haddlist):
    # make sure the first element in the list actually contains an AnalysisTree. Will return an unchanged list if none of the elements contains an AnalysisTree.
    result = copy.deepcopy(haddlist)

    for idx, file in enumerate(haddlist):
        if file_contains_tree(filename=file, treename='AnalysisTree'):
            # print 'will move element no. %i to the front. ' % (idx)
            result.insert(0, result.pop(idx))
            break
    return result



def clean_haddlist(haddlist, use_se=False):
    # remove files that don't exist from the haddlist
    result = []
    DEVNULL = open(os.devnull, 'wb')
    for file in haddlist:
        if not use_se:
            if os.path.isfile(file):
                result.append(file)
        else:
            lscommand = 'LD_LIBRARY_PATH=\'\' PYTHONPATH=\'\' gfal-ls %s' % (file)
            proc = subprocess.Popen(lscommand, stdout=DEVNULL, stderr=DEVNULL, shell=True)
            # output = proc.communicate()[0]
            returncode = proc.returncode
            if not (returncode > 0): # ls succeeded
                result.append(file)
    DEVNULL.close()
    return result


def file_contains_tree(filename, treename):
    rootfile = TFile.Open(filename)
    # print filename
    try:
        tree = rootfile.Get(str(treename))
        entries = tree.GetEntriesFast()
        # print filename,'True entries',entries,entries>0
        return entries > 0
    except:
        # print 'False'
        return False
