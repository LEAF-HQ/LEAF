import os
import numpy as np
import pandas as pd
from printing_utils import green, blue, cyan, prettydict
from utils import ensureDirectory
from functions_dnn import float_to_str, classes_to_str
from DNNutils import LoadDFWeightsLabelsIntoObject

class DNNRunnerBase:
    def __init__(self, dnnparameters, samples):
        self.dnnparameters = dnnparameters
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
        print(green('--> Set up DNNRunner' ))
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

    def LoadInputsBase(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading inputs (base)'))
        inputdir_inputs  = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        inputdir_weights = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        inputdir_label   = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        LoadDFWeightsLabelsIntoObject(self, inputdir_df=inputdir_inputs, basename_df='input', attribute_name_target='inputs', inputdir_weights=inputdir_weights, basename_weights='weights', inputdir_label=inputdir_label, basename_label='label', modes=modes, format=format, frac=float_to_str(self.dnnparameters['runonfraction']))
        print(green('--> Loaded inputs (base)'))

    def LoadInputs(self):
        self.LoadInputsBase()

    def EnsureInputsLoaded(self):
        if not hasattr(self, 'inputs'):
            self.LoadInputs()

    def LoadPredictionsBase(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading predictions (base)'))
        inputdir_pred    = self.filepath['predictions']
        inputdir_weights = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        inputdir_label   = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        LoadDFWeightsLabelsIntoObject(self, inputdir_df=inputdir_pred, basename_df='prediction', attribute_name_target='predictions', inputdir_weights=inputdir_weights, basename_weights='weights', inputdir_label=inputdir_label, basename_label='label', modes=modes, format=format, frac=float_to_str(self.dnnparameters['runonfraction']))
        print(green('--> Loaded predictions (base)'))

    def LoadPredictions(self):
        self.LoadPredictionsBase()

    def EnsurePredictionsLoaded(self):
        if not hasattr(self, 'predictions'):
            self.LoadPredictions()
