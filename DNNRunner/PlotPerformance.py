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



    self.plot_loss(plotfolder=plotfolder, model_history=model_history)
    self.plot_accuracy(plotfolder=plotfolder, model_history=model_history)
    self.plot_rocs(plotfolder=plotfolder, pred_val=pred_val, labels_val=labels_val, eventweights_val=eventweights_val)
    self.plot_outputs_1d_nodes(
        plotfolder=plotfolder,
        pred_train=pred_train, labels_train=labels_train, weights_train=eventweights_train,
        pred_val=pred_val, labels_val=labels_val, weights_val=eventweights_val,
        use_best_model=use_best_model
    )
    # log_model_performance(parameters=parameters, model_history=model_history, outputfolder=outputfolder)
    # plot_model(model, show_shapes=True, to_file=plotfolder+'/Model.pdf')
    # plot_confusion_matrices(parameters=parameters, plotfolder=plotfolder, pred_train=pred_train, labels_train=labels_train, sample_weights_train=sample_weights_train, eventweights_train=eventweights_train, pred_val=pred_val, labels_val=labels_val, sample_weights_val=sample_weights_val, eventweights_val=eventweights_val, use_best_model=use_best_model)

    #
    # plot_outputs_1d_classes(parameters=parameters, plotfolder=plotfolder, pred_trains=pred_trains, labels_train=labels_train, weights_trains=weights_trains, lumiweights_trains=lumiweights_trains, normweights_trains=normweights_trains, pred_vals=pred_vals, labels_val=labels_val, weights_vals=weights_vals, lumiweights_vals=lumiweights_vals, normweights_vals=normweights_vals, use_best_model=use_best_model)
    # plot_outputs_2d(parameters=param





    print green('  --> Done plotting the performance.')



def plot_loss(self, plotfolder, model_history):

    print green('    --> Plotting loss now...')
    eqweight = self.dnnparameters['eqweight']

    # def fitfunc(x, a, b, c, d, e):
    #     return a + b/x + c*x + d*x*x + e/x/x

    plt.clf()
    fig = plt.figure()
    plt.grid()
    # x, fitx, fitfunc, postfitpars_train = fit_loss(model_history['loss'])
    # x, fitx, fitfunc, postfitpars_val = fit_loss(model_history['val_loss'])

    x = range(len(model_history['loss'])+1)
    x = x[1:]

    plt.plot(x, model_history['loss'], label = 'Training set')
    plt.plot(x, model_history['val_loss'], label = 'Validation set')
    # plt.plot(fitx, fitfunc(fitx, *postfitpars_train), label="Fit (training set)")
    # plt.plot(fitx, fitfunc(fitx, *postfitpars_val), label="Fit (validation set)")

    plt.legend(loc='upper right')
    plt.ylim([0., 3.])
    # if eqweight:
    #     plt.ylim([0.01, 0.06])
    plt.ylabel('Loss')
    plt.xlabel('Number of training epochs')
    fig.savefig(os.path.join(plotfolder, 'Loss.pdf'))
    plt.close()

def plot_accuracy(self, plotfolder, model_history):

    print green('    --> Plotting accuracy now...')
    plt.clf()
    fig = plt.figure()
    plt.grid()

    x = range(len(model_history['categorical_accuracy'])+1)
    x = x[1:]
    plt.plot(x, model_history['categorical_accuracy'], label = 'Training set')
    plt.plot(x, model_history['val_categorical_accuracy'], label = 'Validation set')

    plt.legend(loc='lower right')
    plt.ylim([0., 1.05])
    plt.ylabel('Prediction accuracy')
    plt.xlabel('Number of training epochs')
    fig.savefig(os.path.join(plotfolder, 'Accuracy.pdf'))

def plot_rocs(self, plotfolder, pred_val, labels_val, eventweights_val, use_best_model=False):

    classes = self.dnnparameters['classes']
    classtitles = get_classtitles(classes)

    print green('    --> Plotting ROCs now...')

    # lumiweighted
    FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys = get_fpr_tpr_thr_auc(pred=pred_val, labels=labels_val, weights=eventweights_val)
    plt.clf()
    fig = plt.figure()
    plt.xticks(np.arange(0.1,1.1,0.1))
    plt.grid(True, which='both')
    for i in range(len(FalsePositiveRates)):
        plt.semilogy(TruePositiveRates[i], FalsePositiveRates[i], label=classtitles[i] + ', AUC: '+str(round(aucs[i],3)), color=self.colors[i])
    plt.legend(loc='upper left')
    plt.ylim([0.0001, 1.05])
    plt.xlabel('Class selection efficiency')
    plt.ylabel('Class background efficiency')
    title = 'ROC_val'
    if use_best_model: title += '_best'
    else: title += '_last'
    title += '.pdf'
    fig.savefig(os.path.join(plotfolder, title))
    plt.close()

    plt.clf()
    fig = plt.figure()
    for i in range(len(TruePositiveRates)):
        plt.plot(TruePositiveRates[i], SignalPuritys[i], label=classtitles[i], color=self.colors[i])
    plt.legend(loc='best')
    plt.ylim([0., 1.05])
    plt.xlim([0., 1.])
    plt.xticks(np.arange(0.,1.1,0.1))
    plt.yticks(np.arange(0.,1.1,0.1))
    plt.grid(True, which='both')
    plt.xlabel('Selection efficiency')
    plt.ylabel('Purity')
    title = title.replace('ROC_', 'EffVsPur_')
    fig.savefig(os.path.join(plotfolder, title))
    plt.close()

    # Individual backgrounds: 1 plot per class, the other classes are individual curves. Therefore we only need to look at outputnode no. 'cl'
    for cl in classes.keys():
        #cl is the true class

        # Dictionaries to store the rocs against each individual background
        fprs_lum = {}
        tprs_lum = {}
        thrs_lum = {}
        aucss_lum = {}
        prts_lum = {}
        eff_signals_lum = {}
        auc_signals_lum = {}

        # Loop over all remaining classes, always keep predictions, labels, and weights for class 'cl' and this one background
        for i in classes.keys():
            # i is the index of the one background class
            if i == cl: continue
            mask = np.logical_or(labels_val[:,cl] == 1, labels_val[:,i] == 1)
            pred_this = pred_val[mask]
            labels_this = labels_val[mask]
            weights_lum = eventweights_val[mask]
            pred_this = pred_this[:,[cl,i]]
            labels_this = labels_this[:,[cl,i]]
            fprs_lum[i], tprs_lum[i], thrs_lum[i], aucss_lum[i], prts_lum[i] = get_fpr_tpr_thr_auc(pred=pred_this, labels=labels_this, weights=weights_lum)



        # Now just plot all individual curves
        plt.clf()
        fig = plt.figure()
        plt.xticks(np.arange(0.1,1.1,0.1))
        plt.grid(True, which='both')
        for i in fprs_lum.keys():
            plt.semilogy(tprs_lum[i][0], fprs_lum[i][0], label='Bkg: '+classtitles[i] + ', AUC: '+str(round(aucss_lum[i][0],3)), color=self.colors[i])

        plt.legend(loc='upper left')
        plt.ylim([0.0001, 1.05])
        plt.xlabel(classtitles[cl]+' selection efficiency')
        plt.ylabel('Class background efficiency')
        title = 'ROC_val_class%i' % cl
        if use_best_model: title += '_best'
        else: title += '_last'
        title += '.pdf'
        fig.savefig(os.path.join(plotfolder, title))
        plt.close()

        plt.clf()
        fig = plt.figure()
        for i in fprs_lum.keys():
            plt.plot(tprs_lum[i][0], prts_lum[i][0], label='Bkg: ' + classtitles[i], color=self.colors[i])
        plt.legend(loc='best')
        plt.ylim([0., 1.05])
        plt.xlim([0., 1.])
        plt.xticks(np.arange(0.,1.1,0.1))
        plt.yticks(np.arange(0.,1.1,0.1))
        plt.grid(True, which='both')
        plt.xlabel(classtitles[cl]+' selection efficiency')
        plt.ylabel('Purity wrt. given background')
        title = title.replace('ROC_', 'EffVsPur_')
        fig.savefig(os.path.join(plotfolder, title))
        plt.close()

def plot_outputs_1d_nodes(self, plotfolder, pred_train, pred_val, labels_train, labels_val, weights_train, weights_val, use_best_model):
    print green('    --> Plotting classifier output distributions now...')
    classes = self.dnnparameters['classes']
    classtitles = get_classtitles(classes)

    nbins = 100
    binwidth = 1./float(nbins)
    for node in classes:
        # 'node' is the output node number, we will make one plot per 'node'
        y_trains = {}
        y_vals = {}
        # y_trains_norm = {}
        # y_vals_norm = {}
        normweights_train = {}
        normweights_val = {}
        bin_edges = {}
        bin_centers = {}
        y_val_sumofweightquares = {}
        yerrs_val = {}


        for i in classes:
            # 'i' is the true class
            y_trains[i], bin_edges[i] = np.histogram(pred_train[labels_train[:,i]==1][:,node], bins=nbins, weights=weights_train[labels_train[:,i]==1])
            y_vals[i] = np.histogram(pred_val[labels_val[:,i]==1][:,node], bins=nbins, weights=weights_val[labels_val[:,i]==1])[0]
            y_val_sumofweightquares[i] = np.histogram(pred_val[labels_val[:,i]==1][:,node], bins=nbins, weights=weights_val[labels_val[:,i]==1]**2)[0]
            normweights_train[i] = 1./weights_train[labels_train[:,i]==1].sum()
            normweights_val[i] = 1./weights_val[labels_val[:,i]==1].sum()
            bin_centers[i] = 0.5*(bin_edges[i][1:] + bin_edges[i][:-1])
            # yerrs_val[i] = y_vals[i]**0.5
            yerrs_val[i] = y_val_sumofweightquares[i]**0.5

        plt.clf()
        fig = plt.figure()
        for i in classes:
            plt.hist(bin_centers[i], weights=y_trains[i]*normweights_train[i], bins=bin_edges[i], histtype='step', label='Training sample, ' + classtitles[i], color=self.colors[i])
            plt.errorbar(bin_centers[i], y_vals[i]*normweights_val[i], yerr=yerrs_val[i]*normweights_val[i], fmt = '.', drawstyle = 'steps-mid', linestyle=' ', label='Validation sample, ' + classtitles[i], color=self.colors[i])
        plt.legend(loc='best', prop={'size': 8})
        plt.yscale('log')
        plt.xlabel('Classifier output for node %s' % (classtitles[node]))
        plt.ylabel('Normalized number of events / bin')
        title = 'Distribution_node%i_norm' % (node)
        if use_best_model: title += '_best'
        else: title += '_last'
        title += '.pdf'
        fig.savefig(os.path.join(plotfolder, title))

        plt.clf()
        fig = plt.figure()
        for i in classes:
            plt.errorbar(bin_centers[i], y_vals[i], yerr=yerrs_val[i], fmt = '.', drawstyle = 'steps-mid', linestyle=' ', label='Validation sample, ' + classtitles[i], color=self.colors[i])

        plt.legend(loc='best', prop={'size': 8})
        plt.yscale('log')
        plt.xlabel('Classifier output for node %s' % (classtitles[node]))
        plt.ylabel('Events / bin')
        title = 'Distribution_node%i' % (node)
        if use_best_model: title += '_best'
        else: title += '_last'
        title += '.pdf'
        fig.savefig(os.path.join(plotfolder, title))
        plt.close()
