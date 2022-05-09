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

def TrainNetwork(self):

    # Get parameters
    layers        = self.dnnparameters['layers']
    batch_size    = self.dnnparameters['batchsize']
    regmethod     = self.dnnparameters['regmethod']
    regrate       = self.dnnparameters['regrate']
    batchnorm     = self.dnnparameters['batchnorm']
    epochs        = self.dnnparameters['epochs']
    learningrate  = self.dnnparameters['learningrate']
    runonfraction = self.dnnparameters['runonfraction']
    classes       = self.dnnparameters['classes']
    eqweight      = self.dnnparameters['eqweight']
    tag           = parameters_to_tag(self.dnnparameters)
    classtag      = dict_to_str(classes)
    train_new_model = True
    modelpath = os.path.join(self.dataoutput_path, 'DNNModels', tag)
    ensureDirectory(modelpath)
    try:
        model = keras.models.load_model(os.path.join(modelpath, 'model.h5'))
        train_new_model = False
    except:
        pass
    if train_new_model:
        print 'Couldn\'t find the model "%s", a new one will be trained!' % (tag)
    else:
        print 'Found the model "%s", not training a new one, go on to next function.' % (tag)
        return

    inputfolder = os.path.join(self.inputpath_preproc, classtag)
    input_train, input_test, input_val, labels_train, labels_test, labels_val, sample_weights_train, sample_weights_test, sample_weights_val, eventweights_train, eventweights_test, eventweights_val = load_data(inputfolder=inputfolder, fraction=self.dnnparameters['runonfraction'], postfix='')


    # Define the network
    model = Sequential()
    kernel_regularizer = None
    if regmethod == 'L1':
        kernel_regularizer=regularizers.l1(regrate)
    elif regmethod == 'L2':
        kernel_regularizer=regularizers.l2(regrate)


    print 'Number of input variables: %i' % (input_train.shape[1])
    model.add(Dense(layers[0], activation='relu', input_shape=(input_train.shape[1],), kernel_regularizer=kernel_regularizer))
    if regmethod == 'dropout': model.add(Dropout(regrate))
    if batchnorm: model.add(BatchNormalization())

    for i in layers[1:len(layers)+1]:
        model.add(Dense(i, activation='relu', kernel_regularizer=kernel_regularizer))
        if batchnorm: model.add(BatchNormalization())
        if regmethod == 'dropout': model.add(Dropout(regrate))

    model.add(Dense(labels_train.shape[1], activation='softmax', kernel_regularizer=kernel_regularizer))
    # model.add(Dense(labels_train.shape[1], activation='sigmoid', kernel_regularizer=kernel_regularizer))
    print 'Number of output classes: %i' % (labels_train.shape[1])


    # Train the network
    opt = keras.optimizers.Adam(lr=learningrate, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.0, amsgrad=False)
    mymetrics = [keras.metrics.categorical_accuracy]
    # mymetrics = [metrics.categorical_accuracy, metrics.mean_squared_error, metrics.categorical_crossentropy, metrics.kullback_leibler_divergence, metrics.cosine_proximity]
    model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=mymetrics)
    print model.summary()

    period = epochs / 5
    checkpointer = keras.callbacks.ModelCheckpoint(filepath=os.path.join(modelpath, 'model_epoch{epoch:02d}.h5'), verbose=1, save_best_only=False, period=period)
    checkpointer_everymodel = keras.callbacks.ModelCheckpoint(filepath=os.path.join(modelpath, 'model_epoch{epoch:02d}.h5'), verbose=1, save_best_only=False, period=1)
    checkpoint_bestmodel = keras.callbacks.ModelCheckpoint(filepath=os.path.join(modelpath, 'model_best.h5'), monitor='val_loss', verbose=0, save_best_only=True, save_weights_only=False, mode='min', period=1)
    earlystopping = keras.callbacks.EarlyStopping(monitor='val_loss', min_delta=0.005, patience=20, verbose=0, mode='min', baseline=None, restore_best_weights=True)
    LRreducer = keras.callbacks.ReduceLROnPlateau(monitor='val_loss', factor=0.5, patience=50, min_delta=0.001, mode='min')

    weights_train, weights_test = eventweights_train, eventweights_test
    if eqweight:
        weights_train, weights_test = sample_weights_train, sample_weights_test
    # model.fit(input_train, labels_train, sample_weight=weights_train, batch_size=batch_size, epochs=epochs, shuffle=True, validation_data=(input_test, labels_test, weights_test), callbacks=[checkpointer, checkpoint_bestmodel, earlystopping], verbose=1)
    # model.fit(input_train, labels_train, sample_weight=weights_train, batch_size=batch_size, epochs=epochs, shuffle=True, validation_data=(input_test, labels_test, weights_test), callbacks=[checkpointer_everymodel, checkpoint_bestmodel, LRreducer], verbose=2)
    # model.fit(input_train, labels_train, sample_weight=weights_train, batch_size=batch_size, epochs=epochs, shuffle=True, validation_data=(input_test, labels_test, weights_test), callbacks=[checkpointer, checkpoint_bestmodel], verbose=1)
    model.fit(input_train, labels_train, sample_weight=weights_train, batch_size=batch_size, epochs=epochs, shuffle=True, validation_data=(input_test, labels_test, weights_test), callbacks=[checkpointer_everymodel, checkpoint_bestmodel], verbose=2)


    model.save(os.path.join(modelpath, 'model.h5'))
    with open(os.path.join(modelpath, 'model_history.pkl'), 'w') as f:
        pickle.dump(model.history.history, f)
