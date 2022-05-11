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
from ROOT import TCanvas, TFile, TH1F, TH2F, gROOT, kRed, kBlue, kGreen, kMagenta, kCyan, gStyle
from ROOT import gErrorIgnoreLevel, kInfo, kWarning, kError

def PlotPerformance(self, filepostfix='', use_best_model=False, plotfoldername='DNNPerformancePlots'):
    print green('  --> Plotting the performance now...')
    gErrorIgnoreLevel = kWarning


    # Get parameters
    classes = self.dnnparameters['classes']
    classtag = dict_to_str(classes)
    tag = parameters_to_tag(self.dnnparameters)

    plotfolder = os.path.join(self.plotoutput_path, plotfoldername, tag)
    ensureDirectory(plotfolder)

    # Get inputs
    inputfolder = os.path.join(self.inputpath_preproc, classtag)
    input_train, input_test, input_val, labels_train, labels_test, labels_val, sample_weights_train, sample_weights_test, sample_weights_val, eventweights_train, eventweights_test, eventweights_val = load_data(inputfolder=inputfolder, fraction=self.dnnparameters['runonfraction'], postfix=filepostfix)
    with open(inputfolder+'/variable_names.pkl', 'r') as f:
        variable_names = pickle.load(f)

    # Get model and its history
    modelpath = os.path.join(self.dataoutput_path, 'DNNModels', tag)
    model = keras.models.load_model(os.path.join(modelpath, 'model.h5'))
    with open(os.path.join(modelpath, 'model_history.pkl'), 'r') as f:
        model_history = pickle.load(f)

    # Get inputs
    modeltag = 'last'
    if use_best_model:
        modeltag = 'best'

    predictionfolder = os.path.join(self.inputpath_predictions, tag)
    pred_train, pred_test, pred_val = load_predictions(inputfolder=predictionfolder, modeltag=modeltag)



    # log_model_performance(parameters=parameters, model_history=model_history, outputfolder=outputfolder)
    self.plot_loss(plotfolder=plotfolder, model_history=model_history)
    # plot_accuracy(parameters=parameters, plotfolder=plotfolder, model_history=model_history)
    # plot_rocs(parameters=parameters, plotfolder=plotfolder, pred_val=pred_val, labels_val=labels_val, sample_weights_val=sample_weights_val, eventweights_val=eventweights_val, pred_signals=pred_signals, eventweight_signals=eventweight_signals, usesignals=usesignals, use_best_model=use_best_model)
    # plot_model(model, show_shapes=True, to_file=plotfolder+'/Model.pdf')
    # plot_confusion_matrices(parameters=parameters, plotfolder=plotfolder, pred_train=pred_train, labels_train=labels_train, sample_weights_train=sample_weights_train, eventweights_train=eventweights_train, pred_val=pred_val, labels_val=labels_val, sample_weights_val=sample_weights_val, eventweights_val=eventweights_val, use_best_model=use_best_model)
    #
    #
    # pred_trains, weights_trains, normweights_trains, lumiweights_trains, pred_vals, weights_vals, normweights_vals, lumiweights_vals, pred_tests, weights_tests, normweights_tests, lumiweights_tests = get_data_dictionaries(parameters=parameters, eventweights_train=eventweights_train, sample_weights_train=sample_weights_train, pred_train=pred_train, labels_train=labels_train, eventweights_val=eventweights_val, sample_weights_val=sample_weights_val, pred_val=pred_val, labels_val=labels_val, eventweights_test=eventweights_test, sample_weights_test=sample_weights_test, pred_test=pred_test, labels_test=labels_test)
    # plot_outputs_1d_nodes(parameters=parameters, plotfolder=plotfolder, pred_trains=pred_trains, labels_train=labels_train, weights_trains=weights_trains, lumiweights_trains=lumiweights_trains, normweights_trains=normweights_trains, pred_vals=pred_vals, labels_val=labels_val, weights_vals=weights_vals, lumiweights_vals=lumiweights_vals, normweights_vals=normweights_vals, pred_signals=pred_signals, eventweight_signals=eventweight_signals, normweight_signals=normweight_signals, usesignals=usesignals, use_best_model=use_best_model)
    #
    # plot_outputs_1d_classes(parameters=parameters, plotfolder=plotfolder, pred_trains=pred_trains, labels_train=labels_train, weights_trains=weights_trains, lumiweights_trains=lumiweights_trains, normweights_trains=normweights_trains, pred_vals=pred_vals, labels_val=labels_val, weights_vals=weights_vals, lumiweights_vals=lumiweights_vals, normweights_vals=normweights_vals, use_best_model=use_best_model)
    # plot_outputs_2d(parameters=param



def plot_loss(self, plotfolder, model_history):

    print green('    --> Plotting loss now...')
    eqweight = self.dnnparameters['eqweight']

    # def fitfunc(x, a, b, c, d, e):
    #     return a + b/x + c*x + d*x*x + e/x/x

    tag = parameters_to_tag(self.dnnparameters)
    plt.clf()
    fig = plt.figure()
    plt.grid()
    # x, fitx, fitfunc, postfitpars_train = fit_loss(model_history['loss'])
    # x, fitx, fitfunc, postfitpars_val = fit_loss(model_history['val_loss'])

    plt.plot(model_history['loss'], label = 'Training set')
    plt.plot(model_history['val_loss'], label = 'Validation set')
    # plt.plot(fitx, fitfunc(fitx, *postfitpars_train), label="Fit (training set)")
    # plt.plot(fitx, fitfunc(fitx, *postfitpars_val), label="Fit (validation set)")

    plt.legend(loc='upper right')
    # plt.ylim([0.1, 0.25])
    # if eqweight:
    #     plt.ylim([0.01, 0.06])
    plt.ylabel('Loss')
    plt.xlabel('Number of training epochs')
    fig.savefig(os.path.join(plotfolder, 'Loss.pdf'))
    plt.close()
    print green('    --> Done plotting loss.')




    print green('  --> Done plotting the performance.')
