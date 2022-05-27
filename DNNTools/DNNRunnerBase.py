import os
import numpy as np
import pandas as pd
from printing_utils import *
from utils import ensureDirectory
# from collections import OrderedDict
from ConvertRootToInputsBase import ConvertRootToInputsBase
from PreprocessInputsBase import PreprocessInputsBase
from TrainingBase import TrainingBase
from functions_dnn import float_to_str, classes_to_str

class DNNRunnerBase:
    def __init__(self, dnnparameters, year, plotprefix, samples, colors):
        self.dnnparameters = dnnparameters
        self.year = year
        self.plotprefix = plotprefix
        self.samples = samples
        self.colors = colors

        # bind functions
        # self.ConvertRootToInputs = ConvertRootToInputs.ConvertRootToInputs
        # self.PreprocessInputs  = PreprocessInputs.PreprocessInputs
        # self.PlotInputs  = PlotInputs.PlotInputs
        # self.TrainNetwork  = TrainNetwork.TrainNetwork

    def DefinePathsBase(self, root, raw, preproc=None, input=None, result=None, plots=None):
        self.filepath_root    = root
        self.filepath_raw     = raw
        self.filepath_preproc = preproc
        # self.filepath_input   = input
        self.filepath_result  = result
        self.filepath_plots   = plots
        ensureDirectory(self.filepath_raw)
        ensureDirectory(self.filepath_preproc)
        # ensureDirectory(self.filepath_input)
        ensureDirectory(self.filepath_result)
        ensureDirectory(self.filepath_plots)
        self.PrintContent()

    def PrintContent(self):
        print green('--> Set up DNNRunner for year %s:' % (str(self.year)))
        prettydict(self.__dict__, color= cyan)

    def CreateConverter(self):
        self.ConvertRootToInputs = ConvertRootToInputsBase()

    def CreateInputProcessor(self):
        self.PreprocessInputs = PreprocessInputsBase()

    def CreateTraining(self):
        self.Training = TrainingBase()

    def LoadInputsBase(self):
        print(blue('--> Loading'))
        frac = float_to_str(self.dnnparameters['runonfraction'])
        outdir = os.path.join(self.filepath_preproc, classes_to_str(self.dnnparameters['classes']))
        self.input_train   = pd.read_pickle(os.path.join(outdir, 'input_train_%s.pkl'   %frac ))
        self.input_val     = pd.read_pickle(os.path.join(outdir, 'input_val_%s.pkl'     %frac ))
        self.input_test    = pd.read_pickle(os.path.join(outdir, 'input_test_%s.pkl'    %frac ))
        self.label_train   = np.load(os.path.join(outdir, 'label_train_%s.npy'   %frac ))
        self.label_val     = np.load(os.path.join(outdir, 'label_val_%s.npy'     %frac ))
        self.label_test    = np.load(os.path.join(outdir, 'label_test_%s.npy'    %frac ))
        self.weights_train = pd.read_pickle(os.path.join(outdir, 'weights_train_%s.pkl' %frac ))
        self.weights_val   = pd.read_pickle(os.path.join(outdir, 'weights_val_%s.pkl'   %frac ))
        self.weights_test  = pd.read_pickle(os.path.join(outdir, 'weights_test_%s.pkl'  %frac ))

    def LoadInputs(self):
        self.LoadInputsBase()
