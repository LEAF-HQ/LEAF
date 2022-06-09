import os, tqdm
import numpy as np
import pandas as pd

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
# matplotlib.style.use('default')
# matplotlib.style.use('seaborn')

from printing_utils import green, blue
from DNNutils import SaveMPL, LoadPandas
from functions_dnn import classes_to_str, float_to_str


class PlotterBase():
    def __init__(self, inputdir='', outdir='', runonfraction = 1.0):
        self.inputdir = inputdir
        self.outdir = outdir
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

    def LoadInputsBase(self, format='csv'):
        print(blue('--> Loading'))
        inputdir = os.path.join(self.inputdir, classes_to_str(self.classes))
        inputs = []
        for label in ['train', 'val', 'test']:
            input   = LoadPandas(os.path.join(inputdir, 'input_%s_%s.%s' %(label,self.frac,format) ))
            input['label'] = np.load(os.path.join(inputdir, 'label_%s_%s.npy' %(label,self.frac) )).tolist()
            input['label'] = np.argmax(np.array(input['label'].to_list()), axis = 1)
            input['weights'] = LoadPandas(os.path.join(inputdir, 'weights_%s_%s.%s' %(label,self.frac,format) ))
            inputs.append(input)
        self.df = pd.concat(inputs)

    def LoadInputs(self):
        self.LoadInputsBase()

    def PlotSingleVariable(self, style, variable_name, ylabel='Number of events / bin', yscale='log'):
        plt.clf()
        fig = plt.figure()
        classes = list(set(self.classes.values()))

        hist_min = self.df[variable_name].min()
        hist_max = self.df[variable_name].max()
        for cl in classes:
            mask = self.df['label']==cl
            weights_thisclass = self.df[mask]['weights']
            df_thisclass = self.df[mask][variable_name]

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


    def PlotBase(self, style):
        for variable_name in tqdm.tqdm(self.df.columns, desc="Plots done"):
            if 'label' in variable_name: continue
            self.PlotSingleVariable(style, variable_name)

    def Plot(self):
        self.DefineCommonStyle()
        self.DefineStylePerVariable()
        self.LoadInputs()
        self.PlotBase(self.DefineStyle())
