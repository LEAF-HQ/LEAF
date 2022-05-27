import os, tqdm
import numpy as np
import pandas as pd
from printing_utils import *
from utils import ensureDirectory
from functions_dnn import *
from ConvertRootToInputsBase import CleanFile
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
matplotlib.style.use('default')
# matplotlib.style.use('seaborn')

def keyFromValue(dict_, val):
    return list(dict_.keys())[list(dict_.values()).index(val)]

class PlotterBase():
    def __init__(self, inputdir='', outdir=''):
        self.inputdir = inputdir
        self.outdir = outdir
        self.frac = float_to_str(1.0)
        self.common_style = {
            'linewidth': 1.5,
            'histtype': 'step',
            'alpha': 0.5,
            'bins': 100,
        }

    def DefineVariables(self):
        varnames = []
        return varnames

    def DefineSamples(self):
        samples = []
        return samples

    def DefineClasses(self):
        classes = []
        return classes

    def LoadInputsBase(self):
        print(blue('--> Loading'))
        inputdir = os.path.join(self.inputdir, classes_to_str(self.classes))
        inputs = []
        for label in ['train', 'val', 'test']:
            input   = pd.read_pickle(os.path.join(inputdir, 'input_%s_%s.pkl' %(label,self.frac) ))
            input['label'] = np.load(os.path.join(inputdir, 'label_%s_%s.npy' %(label,self.frac) )).tolist()
            input['label'] = np.argmax(np.array(input['label'].to_list()), axis = 1)
            input['weights'] = pd.read_pickle(os.path.join(inputdir, 'weights_%s_%s.pkl' %(label,self.frac) ))
            inputs.append(input)
        self.df = pd.concat(inputs)

    def LoadInputs(self):
        self.LoadInputsBase()

    def PlotSingleVariable(self, style, variable_name):
        plt.clf()
        fig = plt.figure()
        classes = list(set(self.df['label'].to_list()))

        for cl in classes:
            mask = self.df['label']==cl
            weights = self.df[mask]['weights']
            df = self.df[mask][variable_name]
            print cl, weights.shape, df.shape
            style_ = style[keyFromValue(self.DefineClasses(), cl)]
            style_.update(self.common_style)
            plt.hist(df, weights=weights, **style_)
            # weights=weights_train_classes[i], bins=bins, histtype='step', ylabel='Training sample, '+classtitles[i], color=self.colors[i])
        plt.legend(loc='best')
        plt.yscale('log')
        plt.xlabel(variable_name)
        plt.ylabel('Number of events / bin')
        fname = os.path.join(self.outdir, '%s_%s.pdf' % (variable_name, self.frac))
        CleanFile(fname)
        fig.savefig(fname)
        plt.close()


    def PlotBase(self, style):
        print len(self.df.columns)
        for variable_name in tqdm.tqdm(self.df.columns[80:], desc="Plots done"):
        # for variable_name in self.df.columns[80:]:
            print self.df[variable_name].dtypes
            if 'Label' in variable_name: continue
            print variable_name
            self.PlotSingleVariable(style, variable_name)

    def Plot(self):
        ensureDirectory(self.outdir)
        self.LoadInputs()
        style = {
            'QCDHad': {
                'label': 'QCDHad: training sample',
                'linestyle': 'solid',
                'color': 'C0'
                },
            'PsiPsiToLQChi': {
                'label': 'PsiPsiToLQChi: training sample',
                'linestyle': 'solid',
                'color': 'C1'
                },
            'VV': {
                'label': 'VV: training sample',
                'linestyle': 'solid',
                'color': 'C2'
                },
            }
        self.PlotBase(style)
        # if runonfullsample: fig.savefig('Plots/InputDistributions/' + classtag+  '/' + varname + '_full.pdf')
        # else: fig.savefig('Plots/InputDistributions/' + classtag+  '/' + varname + '_part.pdf')
        # idx += 1

        # sys.stdout.write( '{0:d} of {1:d} plots done.\r'.format(idx, len(variable_names)))
        # if not i == len(variable_names): sys.stdout.flush()

        # ax = df.plot.hist(column=['age'], by='gender', figsize=(10, 8))
