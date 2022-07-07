import os
import numpy as np
import pandas as pd
from printing_utils import green, blue, cyan, prettydict
from utils import ensureDirectory
from functions_dnn import float_to_str, classes_to_str
from DNNutils import LoadObjects

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

    def LoadObjectBase(self, object_name, basename, inputdir, modes=['train', 'val', 'test'], format='csv'):
        frac = float_to_str(self.dnnparameters['runonfraction'])
        if not hasattr(self, object_name):
            print(blue('  --> %s is missing: loading...' %(object_name)))
            setattr(self, object_name, LoadObjects(inputdir=inputdir, basename=basename, modes=modes, format=format, frac=frac))
        else:
            missing_modes = [m for m in modes if not m in getattr(self, object_name)]
            if len(missing_modes) > 0:
                print(blue('  --> %s%s is missing: loading...' %(object_name,str(missing_modes))))
                getattr(self, object_name).update(LoadObjects(inputdir=inputdir, basename=basename, modes=missing_modes, format=format, frac=frac))
            else:
                print(blue('  --> %s exists: skipping' %(object_name)))

    def LoadInputs(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading inputs'))
        inputdir = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        for object_name in ['inputs', 'weights', 'labels']:
            self.LoadObjectBase(object_name=object_name, basename=object_name, inputdir=inputdir, modes=modes, format=format)
        print(green('--> Loaded inputs'))

    def LoadPredictions(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading predictions'))
        inputdir_pred = self.filepath['predictions']
        inputdir = os.path.join(self.filepath['preproc'], classes_to_str(self.dnnparameters['classes']))
        for object_name in ['predictions', 'weights', 'labels']:
            inputdir_ = inputdir_pred if object_name=='predictions' else inputdir
            self.LoadObjectBase(object_name=object_name, basename=object_name, inputdir=inputdir_, modes=modes, format=format)
        print(green('--> Loaded predictions'))
