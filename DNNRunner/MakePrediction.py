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


def MakePrediction(self, filepostfix=''):
    print green('  --> Making predictions now...')

    # Get inputs and model(s)
    tag = parameters_to_tag(self.dnnparameters)
    classes = self.dnnparameters['classes']
    classtag = dict_to_str(classes)
    modelpath = os.path.join(self.dataoutput_path, 'DNNModels', tag)
    model = keras.models.load_model(os.path.join(modelpath, 'model.h5'))
    model_best = keras.models.load_model(os.path.join(modelpath, 'model_best.h5'))
    inputfolder = os.path.join(self.inputpath_preproc, classtag)
    input_train, input_test, input_val, labels_train, labels_test, labels_val, sample_weights_train, sample_weights_test, sample_weights_val, eventweights_train, eventweights_test, eventweights_val = load_data(inputfolder=inputfolder, fraction=self.dnnparameters['runonfraction'], postfix=filepostfix)

    # Do the predictions
    outdir = os.path.join(self.inputpath_predictions, tag)
    ensureDirectory(outdir)

    inputs = [input_train, input_test, input_val]
    labels = [labels_train, labels_test, labels_val]
    outfiletags = ['train', 'test', 'val']

    for (input, label, outfiletag) in zip(inputs, labels, outfiletags):
        print green('    --> Predicting for %s set, all classes' % (outfiletag))
        pred = model.predict(input)
        pred_best = model_best.predict(input)
        remove_and_numpy_save(os.path.join(outdir, 'prediction_last_%s.npy'%(outfiletag)), pred)
        remove_and_numpy_save(os.path.join(outdir, 'prediction_best_%s.npy'%(outfiletag)), pred_best)
        for cl in classes:
            print green('    --> Predicting for %s set, class %i' % (outfiletag, cl))
            tmp = pred[label[:,cl] == 1]
            tmp_best = pred_best[label[:,cl] == 1]
            remove_and_numpy_save(os.path.join(outdir, 'prediction_last_%s_class%i.npy'%(outfiletag,cl)) , tmp)
            remove_and_numpy_save(os.path.join(outdir, 'prediction_best_%s_class%i.npy'%(outfiletag,cl)) , tmp_best)

    print green('  --> Done making predictions.')
