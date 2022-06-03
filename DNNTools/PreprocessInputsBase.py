import os
import numpy as np
import pandas as pd
from sklearn import preprocessing, model_selection
from sklearn.utils import class_weight

from printing_utils import green, blue
from functions_dnn import classes_to_str, float_to_str
from DNNutils import SavePandas, SaveNumpy


class PreprocessInputsBase():
    def __init__(self, inputdir='', outdir='', maxfiles_per_sample=None, runonfraction=1.0, train_test_val_split=(0.8, 0.1, 0.1), colname_category='category', colname_weights='event_weight'):
        self.maxfiles_per_sample = maxfiles_per_sample
        self.runonfraction = runonfraction
        self.train_test_val_split = train_test_val_split
        self.inputdir = inputdir
        self.outdir = outdir
        self.colname_category = colname_category
        self.colname_weights  = colname_weights

    def DefineSamples(self):
        raise NotImplementedError('DefineSamples method is not initialized. Fix this.')

    def DefineClasses(self):
        raise NotImplementedError('DefineClasses method is not initialized. Fix this.')

    def GetInputs(self):
        inputs = []
        for samplename in self.DefineSamples():
            list_of_inputfiles = list(filter(lambda x: samplename in x and not x.endswith('.py'), os.listdir(self.inputdir)))
            if self.maxfiles_per_sample != None and samplename in self.maxfiles_per_sample:
                list_of_inputfiles = list_of_inputfiles[:self.maxfiles_per_sample[samplename]]
            print(green('  --> Now starting with sample %s' % (samplename)))
            for i, inputfile in enumerate(list_of_inputfiles):
                print(green('    --> At file no. %i out of %i.' % (i+1, len(list_of_inputfiles))))
                inputs.append(pd.read_pickle(os.path.join(self.inputdir, inputfile)))
        self.df = pd.concat(inputs)
        self.df.rename(lambda x: x[0] if isinstance(x, tuple) else x , axis='columns', inplace=True)
        print(blue('Collected events: '+str(len(self.df))))

    def RemoveNanInf(self):
        self.df.replace([np.inf, -np.inf], np.nan, inplace=True)
        self.df.dropna()


    def SampleEvents(self, fraction=1.0, weights=None, random_state=123456):
        self.df = self.df.sample(frac=fraction, weights=weights, random_state=random_state)


    def Split(self, ratios={'train':0.8, 'validation':0.1, 'test':0.1}):
        inputs = self.df.copy(deep=True)
        weights = self.df.copy(deep=True).loc[:,self.colname_weights]
        labels = self.df.copy(deep=True).loc[:,self.colname_category].apply(lambda x: self.DefineClasses()[x])
        labels = labels.to_numpy().reshape(len(labels), 1)
        labels = preprocessing.OneHotEncoder(sparse=False).fit_transform(labels)
        inputs.drop(columns=[self.colname_weights, self.colname_category], inplace=True)
        if np.sum(ratios.values())!= 1:
            raise RuntimeError('Unexpected ratios for train-validation-test splitting.')
        self.inputs = {}
        self.labels = {}
        self.weights = {}
        self.inputs['train'], self.inputs['test'], self.labels['train'], self.labels['test'], self.weights['train'], self.weights['test'] = model_selection.train_test_split(inputs, labels, weights, train_size=ratios['train'])
        self.inputs['val'], self.inputs['test'], self.labels['val'], self.labels['test'], self.weights['val'], self.weights['test'] = model_selection.train_test_split(self.inputs['test'], self.labels['test'], self.weights['test'], test_size=ratios['test']/(ratios['test'] + ratios['validation']))

    def FitScalers(self):
        self.scalers = {}

    def Transform(self):
        for scaler in self.scalers.values():
            for mode in ['train', 'val', 'test']:
                scaled_features  = scaler.transform(self.inputs[mode])
                self.inputs[mode] = pd.DataFrame(scaled_features, index=self.inputs[mode].index, columns=self.inputs[mode].columns)

    def SaveBase(self):
        print(blue('--> saving'))
        frac = float_to_str(self.runonfraction)
        outdir = os.path.join(self.outdir, classes_to_str(self.DefineClasses()))
        for mode in ['train', 'val', 'test']:
            SavePandas(self.inputs[mode],  os.path.join(outdir, 'input_%s_%s.pkl'   %(mode,frac)))
            SaveNumpy(self.labels[mode],   os.path.join(outdir, 'label_%s_%s.npy'   %(mode,frac)))
            SavePandas(self.weights[mode], os.path.join(outdir, 'weights_%s_%s.pkl' %(mode,frac)))

    def Save(self):
        self.SaveBase()

    def Process(self):
        self.GetInputs()
        self.RemoveNanInf()
        self.SampleEvents(fraction=self.runonfraction)
        self.Split()
        self.FitScalers()
        self.Transform()
        self.Save()
