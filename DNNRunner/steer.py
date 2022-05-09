#!/usr/bin/env python

import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict

# import numpy as np
# from numpy import inf
# import keras
# import matplotlib
# matplotlib.use('Agg')
# import matplotlib.pyplot as plt
# from sklearn import preprocessing
# from sklearn.metrics import roc_auc_score, roc_curve, auc
# from sklearn.model_selection import train_test_split
# from IPython.display import FileLink, FileLinks
# from keras.models import Sequential
# from keras.layers import Dense, Dropout, BatchNormalization
# from keras.utils import to_categorical, plot_model
# from keras.callbacks import History, ModelCheckpoint, ReduceLROnPlateau
# from keras.optimizers import Adam
# import math
# import pickle
import ROOT
from SampleSettings import *
from DNNRunner.DNNRunner import *

# All constants to be used
analysisname     = 'LQDM'
user             = 'areimers'
input_base_path  = os.path.join('/pnfs/psi.ch/cms/trivcat/store/user', user)
result_base_path = os.path.join('/work', user)

samples = {
    'PsiPsiToLQChi_MLQ1000_MCH100_MPS117_L1p0':   SampleSettings(name='PsiPsiToLQChi_MLQ1000_MCH100_MPS117_L1p0',   color=ROOT.kRed+4,   linestyle=2, legendtext='PsiPsiToLQChi_MLQ1000_MCH100_MPS117_L1p0'),
    # 'PsiPsiToLQChi_MLQ7030_MCH100_MPS117_L1p0':   SampleSettings(name='PsiPsiToLQChi_MLQ7030_MCH100_MPS117_L1p0',   color=ROOT.kRed+1,   linestyle=2, legendtext='PsiPsiToLQChi_MLQ7030_MCH100_MPS117_L1p0'),
    # 'PsiPsiToLQChi_MLQ1000_MCH457_MPS567_L1p0':   SampleSettings(name='PsiPsiToLQChi_MLQ1000_MCH457_MPS567_L1p0',   color=ROOT.kViolet,  linestyle=2, legendtext='PsiPsiToLQChi_MLQ1000_MCH457_MPS567_L1p0'),
    # 'PsiPsiToLQChi_MLQ7030_MCH457_MPS504_L1p0':   SampleSettings(name='PsiPsiToLQChi_MLQ7030_MCH457_MPS504_L1p0',   color=ROOT.kAzure-2, linestyle=2, legendtext='PsiPsiToLQChi_MLQ7030_MCH457_MPS504_L1p0'),
    # 'PsiPsiToLQChi_MLQ1000_MCH2089_MPS2221_L1p0': SampleSettings(name='PsiPsiToLQChi_MLQ1000_MCH2089_MPS2221_L1p0', color=ROOT.kOrange,  linestyle=2, legendtext='PsiPsiToLQChi_MLQ1000_MCH2089_MPS2221_L1p0'),
    # 'PsiPsiToLQChi_MLQ7030_MCH2089_MPS2445_L1p0': SampleSettings(name='PsiPsiToLQChi_MLQ7030_MCH2089_MPS2445_L1p0', color=ROOT.kGreen-2, linestyle=2, legendtext='PsiPsiToLQChi_MLQ7030_MCH2089_MPS2445_L1p0'),
    # 'VV':          SampleSettings(name='VV',     color=ROOT.kViolet,  linestyle=1, legendtext='VV'),
    # 'ST':          SampleSettings(name='ST',     color=ROOT.kGreen-2, linestyle=1, legendtext='ST'),
    # 'TT':          SampleSettings(name='TT',     color=ROOT.kRed+1,   linestyle=1, legendtext='TT'),
    # 'DYJets':      SampleSettings(name='DYJets', color=ROOT.kOrange,  linestyle=1, legendtext='DYJets'),
    # 'WJets':       SampleSettings(name='WJets',  color=ROOT.kGreen-2, linestyle=1, legendtext='WJets'),
    'QCDHad':      SampleSettings(name='QCDHad', color=ROOT.kAzure-2, linestyle=1, legendtext='QCDHad'),
}

dnnparameters = OrderedDict()
dnnparameters['layers'] = [512, 512]
dnnparameters['batchsize'] =  131072
dnnparameters['classes'] = OrderedDict([(0, ['QCDHad']), (1, ['PsiPsiToLQChi'])])
dnnparameters['regmethod'] =  'dropout'
dnnparameters['regrate'] =  0.60000
dnnparameters['batchnorm'] =  False
dnnparameters['epochs'] =  700
dnnparameters['learningrate'] =  0.00050
dnnparameters['runonfraction'] =  1.00
dnnparameters['eqweight'] = False



def main():

    Classifier = DNNRunner(dnnparameters=dnnparameters, year='UL17', analysisname=analysisname, input_base_path=input_base_path, result_base_path=result_base_path, selectionstage='Fullselection', selectionname='PsiPsi_05_Jets2_BTagTight1_DPhiJet1Met_DPhiJet2Met_PtratioJet2Met_LeptonCategories', plotprefix='PsiPsiToLQChi', samples=samples)
    Classifier.ConvertRootToInputs(chunksize=200000)
    # Classifier.PreprocessInputs(maxfiles_per_sample=None)

    # tag = dict_to_str(parameters)
    # classtag = get_classes_tag(parameters)


    # # Get all the inputs
    # # ==================
    # GetInputs(parameters)
    # PlotInputs(parameters, inputfolder='input/'+classtag, filepostfix='', plotfolder='Plots/InputDistributions/' + classtag)

    # # First network
    # # =============
    # TrainNetwork(parameters)
    # PredictExternal(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='')
    # PlotPerformance(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='', use_best_model=False, usesignals=[2,4])
    # PlotPerformance(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='', plotfolder='Plots/'+tag, use_best_model=True, usesignals=[2,4])
    # PlotInputs(parameters, inputfolder='output/'+tag+'/cut', filepostfix='_pass_best', plotfolder='Plots/'+tag+'/InputDistributions/pass')
    # PlotInputs(parameters, inputfolder='output/'+tag+'/cut', filepostfix='_fail_best', plotfolder='Plots/'+tag+'/InputDistributions/fail')
    # ExportModel(parameters, inputfolder='input/', outputfolder='output/', use_best_model=True)
    # RankNetworks(outputfolder='output/')







if __name__ == '__main__':
    main()
