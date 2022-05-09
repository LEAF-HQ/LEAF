import numpy as np
import keras
import matplotlib
import math
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.utils import class_weight
from sklearn.metrics import roc_auc_score, roc_curve, auc
from sklearn.model_selection import train_test_split
from IPython.display import FileLink, FileLinks
from keras.models import Sequential
from keras.layers import Dense, Dropout, BatchNormalization
from keras.utils import to_categorical, plot_model
from keras.callbacks import History, ModelCheckpoint, ReduceLROnPlateau
from keras.optimizers import Adam
import pickle
import os
from utils import *
from functions_dnn import *
import copy
import tqdm

# parameters, inputfolder='input/'+classtag, filepostfix='', plotfolder='Plots/InputDistributions/' + classtag
def PlotInputs(self, filepostfix='', plotfoldername='InputDistributions'):

    # Get parameters
    classes = self.dnnparameters['classes']
    classtag = dict_to_str(classes)

    plotfolder = os.path.join(self.plotoutput_path, plotfoldername, classtag)
    ensureDirectory(plotfolder)

    # Get inputs
    inputfolder = os.path.join(self.inputpath_preproc, classtag)
    input_train, input_test, input_val, labels_train, labels_test, labels_val, sample_weights_train, sample_weights_test, sample_weights_val, eventweights_train, eventweights_test, eventweights_val = load_data(inputfolder=inputfolder, fraction=self.dnnparameters['runonfraction'], postfix=filepostfix)
    with open(inputfolder+'/variable_names.pkl', 'r') as f:
        variable_names = pickle.load(f)

    # Divide into classes
    input_train_classes = {}
    input_test_classes = {}
    input_val_classes = {}
    weights_train_classes = {}
    weights_test_classes = {}
    weights_val_classes = {}
    for i in range(labels_train.shape[1]):
        input_train_classes[i] = input_train[labels_train[:,i] == 1]
        input_test_classes[i] = input_test[labels_test[:,i] == 1]
        input_val_classes[i] = input_val[labels_val[:,i] == 1]
        weights_train_classes[i] = sample_weights_train[labels_train[:,i] == 1]
        weights_test_classes[i] = sample_weights_test[labels_test[:,i] == 1]
        weights_val_classes[i] = sample_weights_val[labels_val[:,i] == 1]

    # Create class-title dictionary
    classtitles = {}
    for key in classes.keys():
        list = classes[key]
        title = ''
        for i in range(len(list)):
            title = title + list[i]
            if i < len(list)-1:
                title = title + '+'
        classtitles[key] = title

    matplotlib.style.use('default')
    # print input_train_classes
    nbins = 50
    for idx in tqdm.tqdm(range(len(variable_names)), desc="Plots done"):

        varname = variable_names[idx]
        if isinstance(varname, tuple):
            varname = varname[0]
        varname = varname.replace('Events.', '')
        xmax = max([max(input_train_classes[i][:,idx]) for i in range(len(input_train_classes))])
        xmin = min([min(input_train_classes[i][:,idx]) for i in range(len(input_train_classes))])
        if xmax == xmin: xmax = xmin + 1.
        xmin = min([0,xmin])
        binwidth = (xmax - xmin) / float(nbins)
        bins = np.arange(xmin, xmax + binwidth, binwidth)

        plt.clf()
        fig = plt.figure()
        for i in range(len(input_train_classes)):
            mycolor = 'C'+str(i)
            plt.hist(input_train_classes[i][:,idx], weights=weights_train_classes[i], bins=bins, histtype='step', label='Training sample, '+classtitles[i], color=self.colors[i])
        plt.legend(loc='best')
        plt.yscale('log')
        plt.xlabel(varname)
        plt.ylabel('Number of events / bin')
        fig.savefig(os.path.join(plotfolder, '%s_%s.pdf' % (varname, float_to_str(self.dnnparameters['runonfraction']))))
        # if runonfullsample: fig.savefig('Plots/InputDistributions/' + classtag+  '/' + varname + '_full.pdf')
        # else: fig.savefig('Plots/InputDistributions/' + classtag+  '/' + varname + '_part.pdf')
        # idx += 1

        # sys.stdout.write( '{0:d} of {1:d} plots done.\r'.format(idx, len(variable_names)))
        # if not i == len(variable_names): sys.stdout.flush()
        plt.close()
