import numpy as np
from root_numpy import root2array, rec2array
from numpy import inf
import keras
import matplotlib
import math
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.utils import class_weight
from sklearn.metrics import roc_auc_score, roc_curve, auc
from sklearn.model_selection import train_test_split
from IPython.display import FileLink, FileLinks
from keras.models import Sequential
from keras.layers import Dense, Dropout, BatchNormalization
from keras.utils import to_categorical, plot_model
from keras.callbacks import History, ModelCheckpoint, ReduceLROnPlateau
from keras.optimizers import Adam
import pickle
import os
from utils import *
from functions_dnn import *

def ConvertRootToInputs(self, chunksize=200000, treename='AnalysisTree'):

    tag = parameters_to_tag(self.dnnparameters)
    outfolder = self.inputpath_raw
    ensureDirectory(outfolder)

    # ROOT.gInterpreter.ProcessLine('#include "LEAF/include/GenEvent.h"')
    ROOT.gSystem.Load('libLEAFClasses.so')
    ROOT.gSystem.Load('libLQDMClasses.so')

    for samplename in self.samples:
        print green('  --> Creating numpy arrays for input sample %s' % (samplename))
        infilename = os.path.join(self.inputpath_root, 'MC__%s.root' % (samplename))
        infile = ROOT.TFile.Open(infilename)

        tree = infile.Get(treename)
        entries = tree.GetEntriesFast()
        infile.Close()

        varnames_jets      = ['m_pt', 'm_eta', 'm_phi', 'm_m', 'm_score_DeepFlavB']
        njets = 5
        varnames_muons     = ['m_pt', 'm_eta', 'm_phi', 'm_m', 'm_dxy', 'm_dz', 'm_dxy_err', 'm_dz_err', 'm_iso_rel_04']
        nmuons = 2
        varnames_electrons = ['m_pt', 'm_eta', 'm_phi', 'm_m', 'm_dxy', 'm_dz', 'm_dxy_err', 'm_dz_err', 'm_iso_rel_03']
        nelectrons = 2
        varnames_taus      = ['m_pt', 'm_eta', 'm_phi', 'm_m', 'm_dxy', 'm_dz', 'm_score_deeptau_vse', 'm_score_deeptau_vsmu', 'm_score_deeptau_vsjet', 'm_comb_iso_dr03']
        ntaus = 2
        varnames_general   = ['met.m_pt', 'met.m_phi']
        varnames_all = []
        for v in varnames_jets:
            for i in range(njets):
                varnames_all.append(('Events.jets_ak4chs.%s[%i]' % (v, i), -99., 1))
        for v in varnames_muons:
            for i in range(nmuons):
                varnames_all.append(('Events.muons.%s[%i]' % (v, i), -99., 1))
        for v in varnames_electrons:
            for i in range(nelectrons):
                varnames_all.append(('Events.electrons.%s[%i]' % (v, i), -99., 1))
        for v in varnames_taus:
            for i in range(ntaus):
                varnames_all.append(('Events.taus.%s[%i]' % (v, i), -99., 1))
        for v in varnames_general:
            varnames_all.append('Events.%s' % (v))

        maxidx = int(entries/float(chunksize)) + 1
        if entries % chunksize == 0:
            maxidx -= 1

        print green('    --> Producing %i files with %i events each.' % (maxidx, chunksize))
        for i in range(maxidx):
            print green('      --> Working on file number: %i (%3.2f%%)' % (i+1, float(i+1)/maxidx * 100.))
            # (branch_or_expression, fill_value, length)
            mymatrix = root2array(filenames=infilename, treename=treename, branches=varnames_all, start=i*chunksize, stop=(i+1)*chunksize)
            mymatrix = rec2array(mymatrix)
            myweights = root2array(filenames=infilename, treename=treename, branches=['Events.GenEvent.Event.weight'], start=i*chunksize, stop=(i+1)*chunksize)
            myweights = rec2array(myweights)
            outname = os.path.join(outfolder, '%s_%i.npy' % (samplename, i))
            outname_weights = os.path.join(outfolder, 'Weights_%s_%i.npy' % (samplename, i))
            if os.path.exists(outname):
                os.remove(outname)
            if os.path.exists(outname_weights):
                os.remove(outname_weights)
            np.save(outname, mymatrix)
            np.save(outname_weights, myweights)
            # percent = float(i+1)/float(maxidx) * 100.
            # sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(i+1, maxidx, percent))
            # if not i == maxidx-1: sys.stdout.flush()

        print green('    --> Finished storing inputs, now storing the variable names and moving on.')
        outfilename_varnames = os.path.join(outfolder, 'variable_names.pkl')
        if os.path.exists(outfilename_varnames):
            os.remove(outfilename_varnames)
        with open(outfilename_varnames, 'w') as f:
            pickle.dump(varnames_all, f)
