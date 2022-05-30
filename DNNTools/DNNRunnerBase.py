import os
import numpy as np
import pandas as pd
from printing_utils import *
from utils import ensureDirectory
# from collections import OrderedDict
from functions_dnn import float_to_str, classes_to_str

class DNNRunnerBase:
    def __init__(self, dnnparameters, year, samples):
        self.dnnparameters = dnnparameters
        self.year = year
        self.samples = samples

    def DefinePathsBase(self, **kwargs):
        self.filepath = {}
        self.filepath.update(kwargs)
        for path in self.filepath.values():
            ensureDirectory(path)
        self.PrintContent()

    def DefinePaths(self):
        raise NotImplementedError('DefinePaths method is not initialized. Fix this.')

    def PrintContent(self):
        print green('--> Set up DNNRunner for year %s:' % (str(self.year)))
        prettydict(self.__dict__, color= cyan)

    def CreateConverter(self):
        from ConvertRootToInputsBase import ConvertRootToInputsBase
        self.ConvertRootToInputs = ConvertRootToInputsBase()

    def CreateInputProcessor(self):
        from PreprocessInputsBase import PreprocessInputsBase
        self.PreprocessInputs = PreprocessInputsBase()

    def CreatePlotter(self):
        from PlotterBase import PlotterBase
        self.Plotter = PlotterBase()

    def CreateTraining(self):
        from TrainingBase import TrainingBase
        self.Training = TrainingBase()

    def LoadInputsBase(self):
        print(blue('--> Loading'))
        frac = float_to_str(self.dnnparameters['runonfraction'])
        outdir = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
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
