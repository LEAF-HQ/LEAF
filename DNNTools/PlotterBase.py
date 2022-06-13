import os, tqdm
import numpy as np
import pandas as pd

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from printing_utils import green, blue
from DNNutils import SaveMPL, LoadPandas
from functions_dnn import classes_to_str, float_to_str


class PlotterBase():
    def __init__(self, inputdir='', outdir='', predictiondir='', runonfraction=1.0):
        self.inputdir = inputdir
        self.outdir = outdir
        self.predictiondir = predictiondir
        self.frac = float_to_str(runonfraction)

    def DefineCommonStyle(self):
        self.common_style = {
            'linewidth': 1.5,
            'histtype': 'step',
            'alpha': 0.5,
            'bins': 100,
        }

    def DefineStyle(self):
        raise NotImplementedError('DefineStyle method is not initialized. Fix this.')

    def DefineStylePerVariable(self):
        self.stylePerVariable = {}

    def DefineClasses(self):
        raise NotImplementedError('DefineClasses method is not initialized. Fix this.')

    def LoadDFAndWeightsAndLabels(self, inputdir_df, basename_df, attribute_name_target, inputdir_weights, basename_weights, inputdir_label, basename_label, modes=['train', 'val', 'test'], format='csv'):
        parts = []
        for mode in modes:
            print(blue('  --> Loading for subset \'%s\'' % (mode)))
            df            = LoadPandas(os.path.join(inputdir_df, '%s_%s_%s.%s' %(basename_df,mode,self.frac,format) ))
            df['label']   = np.load(os.path.join(inputdir_label, '%s_%s_%s.npy' %(basename_label,mode,self.frac) )).tolist()
            df['label']   = np.argmax(np.array(df['label'].to_list()), axis = 1)
            df['weights'] = LoadPandas(os.path.join(inputdir_weights, '%s_%s_%s.%s' %(basename_weights,mode,self.frac,format) ))
            parts.append(df)
            print(blue('  --> Loaded for subset \'%s\'' % (mode)))
        setattr(self, str(attribute_name_target), pd.concat(parts))

    def LoadInputsBase(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading inputs (base)'))
        inputdir_inputs  = os.path.join(self.inputdir, classes_to_str(self.classes))
        inputdir_weights = os.path.join(self.inputdir, classes_to_str(self.classes))
        inputdir_label   = os.path.join(self.inputdir, classes_to_str(self.classes))
        self.LoadDFAndWeightsAndLabels(inputdir_df=inputdir_inputs, basename_df='input', attribute_name_target='inputs', inputdir_weights=inputdir_weights, basename_weights='weights', inputdir_label=inputdir_label, basename_label='label', modes=modes, format=format)
        print(green('--> Loaded inputs (base)'))

    def LoadInputs(self):
        self.LoadInputsBase()

    def EnsureInputsLoaded(self):
        if not hasattr(self, 'inputs'):
            self.LoadInputs()


    def LoadPredictionsBase(self, modes=['train', 'val', 'test'], format='csv'):
        print(blue('--> Loading predictions (base)'))
        inputdir_pred    = self.predictiondir
        inputdir_weights = os.path.join(self.inputdir, classes_to_str(self.classes))
        inputdir_label   = os.path.join(self.inputdir, classes_to_str(self.classes))
        self.LoadDFAndWeightsAndLabels(inputdir_df=inputdir_pred, basename_df='prediction', attribute_name_target='predictions', inputdir_weights=inputdir_weights, basename_weights='weights', inputdir_label=inputdir_label, basename_label='label', modes=modes, format=format)
        print(green('--> Loaded predictions (base)'))

    def LoadPredictions(self):
        self.LoadPredictionsBase()

    def EnsurePredictionsLoaded(self):
        if not hasattr(self, 'predictions'):
            self.LoadPredictions()





    def PlotSingleVariable(self, df, style, variable_name, ylabel='Number of events / bin', yscale='log'):
        plt.clf()
        fig = plt.figure()
        classes = list(set(self.classes.values()))

        hist_min = df[variable_name].min()
        hist_max = df[variable_name].max()
        for cl in classes:
            mask = df['label']==cl
            weights_thisclass = df[mask]['weights']
            df_thisclass = df[mask][variable_name]

            style_thisclass = style[cl]
            style_thisclass.update(self.common_style)
            if variable_name in self.stylePerVariable:
                style_thisclass.update(self.stylePerVariable[variable_name])

            plt.hist(df_thisclass, weights=weights_thisclass, range=(hist_min, hist_max), **style_thisclass)

        plt.legend(loc='best')
        plt.yscale(yscale)
        plt.xlabel(variable_name)
        plt.ylabel(ylabel)
        fname = os.path.join(self.outdir, '%s_%s.pdf' % (variable_name, self.frac))
        SaveMPL(fig, fname)
        plt.close()


    def PlotBase(self, df, style):
        for variable_name in tqdm.tqdm(df.columns, desc="Plots done"):
            if 'label' in variable_name: continue
            self.PlotSingleVariable(df=df, style=style, variable_name=variable_name)

    def Plot(self):
        self.DefineCommonStyle()
        self.DefineStylePerVariable()
        self.EnsureInputsLoaded()
        self.PlotBase(df=self.inputs, style=self.DefineStyle())
