import os
import numpy as np
import pandas as pd
from sklearn import model_selection
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

    def GetInputs(self,format='csv'):
        inputs = []
        for samplename in self.DefineSamples():
            list_of_inputfiles = list(filter(lambda x: samplename in x and x.endswith('.'+format), os.listdir(self.inputdir)))
            if self.maxfiles_per_sample != None and samplename in self.maxfiles_per_sample:
                list_of_inputfiles = list_of_inputfiles[:self.maxfiles_per_sample[samplename]]
            print(green('  --> Now starting with sample %s' % (samplename)))
            for i, inputfile in enumerate(list_of_inputfiles):
                if (i+1)%10==0:
                    print(green('    --> At file no. %i out of %i.' % (i+1, len(list_of_inputfiles))))
                inputs.append(pd.read_pickle(os.path.join(self.inputdir, inputfile)))
        self.df = pd.concat(inputs, ignore_index=True)
        del inputs
        self.df.rename(lambda x: x[0] if isinstance(x, tuple) else x , axis='columns', inplace=True)
        print self.df[['category']]
        print(blue('Collected events: '+str(len(self.df))))

    def RemoveNanInf(self, df):
        size_before = df.shape[0]
        df.replace([np.inf, -np.inf], np.nan, inplace=True)
        df.dropna(inplace=True)
        size_after = df.shape[0]
        print(green('  --> Removed %i events because of irregular features' % (size_before - size_after)))


    def SampleEvents(self, fraction=1.0, weights=None, random_state=123456):
        self.df = self.df.sample(frac=fraction, weights=weights, random_state=random_state)


    def Split(self, ratios={'train':0.8, 'validation':0.1, 'test':0.1}):
        weights = pd.DataFrame(self.df.loc[:,self.colname_weights], columns=[self.colname_weights])
        print self.DefineClasses()
        print self.df[[self.colname_category]]
        labels  = pd.DataFrame(self.df.loc[:,self.colname_category].apply(lambda x: self.DefineClasses()[x]), columns=[self.colname_category])
        self.df.drop(columns=[self.colname_weights, self.colname_category], inplace=True)
        if np.sum(ratios.values())!= 1:
            raise RuntimeError('Unexpected ratios for train-validation-test splitting.')
        self.inputs = {}
        self.labels = {}
        self.weights = {}
        self.inputs['train'], self.inputs['test'], self.labels['train'], self.labels['test'], self.weights['train'], self.weights['test'] = model_selection.train_test_split(self.df, labels, weights, train_size=ratios['train'])
        del self.df
        self.inputs['val'], self.inputs['test'], self.labels['val'], self.labels['test'], self.weights['val'], self.weights['test'] = model_selection.train_test_split(self.inputs['test'], self.labels['test'], self.weights['test'], test_size=ratios['test']/(ratios['test'] + ratios['validation']))

    def FitScalers(self):
        self.scalers = {}

    def Transform(self):
        for scaler in self.scalers.values():
            for mode in ['train', 'val', 'test']:
                scaled_features  = scaler.transform(self.inputs[mode]).astype('float32')
                self.inputs[mode] = pd.DataFrame(scaled_features, index=self.inputs[mode].index, columns=self.inputs[mode].columns)
                self.RemoveNanInf(df=self.inputs[mode])

    def SaveBase(self, format='csv'):
        print(blue('--> Saving'))
        frac = float_to_str(self.runonfraction)
        outdir = os.path.join(self.outdir, classes_to_str(self.DefineClasses()))
        for mode in ['train', 'val', 'test']:
            SavePandas(self.inputs[mode].astype('float32'),  os.path.join(outdir, 'inputs_%s_%s.%s'  %(mode,frac,format)))
            SavePandas(self.weights[mode].astype('float32'), os.path.join(outdir, 'weights_%s_%s.%s' %(mode,frac,format)))
            SavePandas(self.labels[mode].astype('int8'),  os.path.join(outdir, 'labels_%s_%s.%s'  %(mode,frac,format)))

    def Save(self):
        self.SaveBase()

    def Process(self):
        self.GetInputs(format='pkl')
        self.RemoveNanInf(df=self.df)
        self.SampleEvents(fraction=self.runonfraction)
        self.Split()
        self.FitScalers()
        self.Transform()
        self.Save()
