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
    def __init__(self, runonfraction=1.00):
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




    def PlotSingleVariable(self, df, style, variable_name, outdir, ylabel='Number of events / bin', yscale='log'):
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
        fname = os.path.join(outdir, '%s_%s.pdf' % (variable_name, self.frac))
        SaveMPL(fig, fname)
        plt.close()

    def PlotROCSingleVariable(self, df, style, variable_name, outdir):
        pass


    def PlotDF(self, df, outdir):
        print(blue('--> Plotting dataframe'))
        self.DefineCommonStyle()
        self.DefineStylePerVariable()
        for variable_name in tqdm.tqdm(df.columns, desc="Plots done"):
            if 'label' in variable_name: continue
            self.PlotSingleVariable(df=df, style=self.DefineStyle(), variable_name=variable_name, outdir=outdir)
        print(green('--> Plotted dataframe'))
