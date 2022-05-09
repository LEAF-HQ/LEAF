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

def PreprocessInputs(self, maxfiles_per_sample, train_test_val_split=(4./6, 1./6, 1./6)):

    # maxfiles_per_sample is a dictionary containing samplenames as keys and integers as value, giving the maximum absolute number of files to read in per sample.
    # If it is None, read all files available

    # Get dnnparameters
    classes = self.dnnparameters['classes']
    ensureDirectory(self.inputpath_preproc)


    # Find initial file for each class
    inputfiles = os.listdir(self.inputpath_raw)

    # load inputs and event weights for each sample in self.samples
    all_inputs = {}
    all_eventweights = {}
    all_labels = {}
    for samplename in self.samples:
        inputs_and_weights = read_inputs_and_weights_for_sample(samplename=samplename, inpath=self.inputpath_raw, inputfiles=inputfiles, maxfiles_per_sample=maxfiles_per_sample)
        all_inputs[samplename]       = inputs_and_weights['input']
        all_eventweights[samplename] = inputs_and_weights['weight']

        # find out label for this sample
        for label in classes:
            for procname in classes[label]:
                if samplename.startswith(procname):
                    tmp = np.empty(inputs_and_weights['input'].shape[0])
                    tmp.fill(label)
                    tmp = tmp.astype(np.int8)
                    all_labels[samplename] = tmp

    if len(all_inputs) != len(self.samples) or len(all_eventweights) != len(self.samples) or len(all_labels) != len(self.samples):
        raise ValueError('Number of input samples or eventweights or labels read in does not match number of \'self.samples\'.')
    if not all_inputs.keys() == all_eventweights.keys() and not all_inputs.keys() == all_labels.keys():
        raise ValueError('The keys of input, eventweight, and label dictionaries are not identical.')






    # Here we're making sure to loop through all classes in the numeric order to avoid confusing the labels of inputs -- dict might be unordered, but the input matrix has to be ordered! Thanks god the class names correspond to the list indices from 0 to nclasses-1
    input_total = np.concatenate((tuple([all_inputs[key] for key in sorted(all_inputs.keys())])))
    eventweight_total = np.concatenate((tuple([all_eventweights[key] for key in sorted(all_eventweights.keys())])))
    label_concatenated = np.concatenate((tuple([all_labels[key] for key in sorted(all_labels.keys())])))


    # Now create matrix with labels, it's zero everywhere, only the column corresponding to the class the example belongs to has ones. This is OneHotEncoding the limits
    label_total = np.zeros((label_concatenated.shape[0], len(classes)))
    for i in range(label_concatenated.shape[0]):
        label = label_concatenated[i]
        label_total[i,label] = 1
    label_total = label_total.astype(np.int8)

    # Treat inf and nan entries
    input_total[input_total == np.inf]    = 999999.
    input_total[input_total == -np.inf]   = -999999.
    input_total[np.isnan(input_total)] = 0.

    # print input_total[label_total[:,2]==1][0]


    shuffle = np.random.permutation(np.size(input_total, axis=0))
    input_total       = input_total[shuffle]
    eventweight_total = eventweight_total[shuffle]
    label_total       = label_total[shuffle]
    label_concatenated = label_concatenated[shuffle]

    # Cut off some events if not running on full sample
    percentage = self.dnnparameters['runonfraction']
    frac_train = train_test_val_split[0] * percentage
    frac_test  = train_test_val_split[1] * percentage
    frac_val   = train_test_val_split[2] * percentage
    sumweights = np.sum(eventweight_total, axis=0)

    print green('  --> shape of all inputs:    %s' % str(input_total.shape))
    print green('  --> shape of event weights: %s, \tsum of eventweights: %s' % (str(eventweight_total.shape), str(sumweights)))
    cutoffweighted_train = float(sumweights)*float(frac_train)
    cutoffweighted_test  = float(sumweights)*float(frac_train + frac_test)
    cutoffweighted_val   = float(sumweights)*float(frac_train + frac_test + frac_val)

    currentsum = 0.
    takeupto_train = 0
    takeupto_test  = 0
    takeupto_val   = 0
    sumweights_classes = {}

    # initialize this dict
    for i in range(label_total.shape[1]):
        sumweights_classes[i] = 0.

    for i in range(len(eventweight_total)):
        currentsum += eventweight_total[i,0]
        # if i%1000000 == 0: print i, currentsum
        if currentsum >= cutoffweighted_train and takeupto_train == 0:
            takeupto_train = i+1
        if currentsum >= cutoffweighted_test  and takeupto_test  == 0:
            takeupto_test = i+1
        if currentsum >= cutoffweighted_val  and takeupto_val  == 0:
            takeupto_val = i+1

        #find out which class this event belongs to
        thisclass = label_concatenated[i]
        sumweights_classes[thisclass] += eventweight_total[i,0]

    input_train = input_total[:takeupto_train]
    labels_train = label_total[:takeupto_train]
    eventweight_train = eventweight_total[:takeupto_train]

    input_test = input_total[takeupto_train:takeupto_test]
    labels_test = label_total[takeupto_train:takeupto_test]
    eventweight_test = eventweight_total[takeupto_train:takeupto_test]

    input_val = input_total[takeupto_test:takeupto_val]
    labels_val = label_total[takeupto_test:takeupto_val]
    eventweight_val = eventweight_total[takeupto_test:takeupto_val]
    print 'shapes of inputs (train, test, val): ', input_train.shape, input_test.shape, input_val.shape

    # Calculate class weights such, that after weighting by class_weight all classes have the same number of weighted events, where all events are ALSO weighted by eventweight --> total weight = class_weight * eventweight
    class_weights = {}

    # scale each class to the one with the smallest sum of weights
    minsum = sumweights_classes[0]
    for i in range(len(sumweights_classes)):
        if sumweights_classes[i] < minsum:
            minsum = sumweights_classes[i]

    for i in range(len(sumweights_classes)):
        weight = 1
        if sumweights_classes[i] != 0:
            weight = minsum/sumweights_classes[i]
        class_weights[i] = weight

    sample_weights_train_list = []
    sample_weights_test_list = []
    sample_weights_val_list = []
    for i in range(len(labels_train[:,0])):
        #loop over training examples i
        for j in range(len(labels_train[i,:])):
            #loop over possible classes j
            if labels_train[i,j] == 1:
                thisweight = class_weights[j] * eventweight_train[i]
                sample_weights_train_list.append(thisweight)
    for i in range(len(labels_test[:,0])):
        for j in range(len(labels_test[i,:])):
            if labels_test[i,j] == 1:
                thisweight = class_weights[j] * eventweight_test[i]
                sample_weights_test_list.append(thisweight)
    for i in range(len(labels_val[:,0])):
        for j in range(len(labels_val[i,:])):
            if labels_val[i,j] == 1:
                thisweight = class_weights[j] * eventweight_val[i]
                sample_weights_val_list.append(thisweight)


    # # Test: sum val-sampleweights for each class, should be the same value for all classes
    # sums = {}
    # for c in classes:
    #     sums[c] = 0.
    # for i in range(len(labels_train[:,0])):
    #     #loop over training examples i
    #     for j in range(len(labels_train[i,:])):
    #         #loop over possible classes j
    #         if labels_train[i,j] == 1:
    #             sums[j] += sample_weights_train_list[i]
    # print sums


    sample_weights_train = np.asarray(sample_weights_train_list).ravel()
    sample_weights_test  = np.asarray(sample_weights_test_list).ravel()
    sample_weights_val   = np.asarray(sample_weights_val_list).ravel()

    eventweight_train = np.asarray(eventweight_train).ravel()
    eventweight_test  = np.asarray(eventweight_test).ravel()
    eventweight_val   = np.asarray(eventweight_val).ravel()

    # Scale features
    scaler = preprocessing.StandardScaler()
    scaler.mean_ = np.mean(input_train, axis=0)
    scaler.scale_ = np.std(input_train, axis=0)
    input_train = copy.deepcopy(scaler.transform(input_train))
    input_test = copy.deepcopy(scaler.transform(input_test))
    input_val = copy.deepcopy(scaler.transform(input_val))


    classtag = dict_to_str(classes)

    with open(os.path.join(self.inputpath_raw, 'variable_names.pkl'), 'r') as f:
        variable_names = pickle.load(f)

    # Write out scaler info
    ensureDirectory(os.path.join(self.inputpath_preproc, classtag))
    norminfofile = os.path.join(self.inputpath_preproc, classtag, 'NormInfo.txt')
    with open(norminfofile, 'w') as f:
        for i in range(scaler.mean_.shape[0]):
            var = variable_names[i]
            mean = scaler.mean_[i]
            scale = scaler.scale_[i]
            line = '%s StandardScaler %s %s\n' % (str(var), str(mean), str(scale))
            f.write(line)



    varnamefile = os.path.join(self.inputpath_preproc, classtag, 'variable_names.pkl')
    with open(varnamefile, 'w') as f:
        pickle.dump(variable_names, f)


    np.save(os.path.join(self.inputpath_preproc, classtag, 'input_%s_train.npy' % (float_to_str(percentage)) )  , input_train)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'input_%s_test.npy' % (float_to_str(percentage)) )   , input_test)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'input_%s_val.npy' % (float_to_str(percentage)) )    , input_val)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'labels_%s_train.npy' % (float_to_str(percentage)) ) , labels_train)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'labels_%s_test.npy' % (float_to_str(percentage)) )  , labels_test)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'labels_%s_val.npy' % (float_to_str(percentage)) )   , labels_val)

    np.save(os.path.join(self.inputpath_preproc, classtag, 'sample_weights_%s_train.npy' % (float_to_str(percentage)) ), sample_weights_train)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'eventweights_%s_train.npy' % (float_to_str(percentage)) ), eventweight_train)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'sample_weights_%s_test.npy' % (float_to_str(percentage)) ), sample_weights_test)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'eventweights_%s_test.npy' % (float_to_str(percentage)) ), eventweight_test)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'sample_weights_%s_val.npy' % (float_to_str(percentage)) ), sample_weights_val)
    np.save(os.path.join(self.inputpath_preproc, classtag, 'eventweights_%s_val.npy' % (float_to_str(percentage)) ), eventweight_val)





def read_inputs_and_weights_for_sample(samplename, inpath, inputfiles, maxfiles_per_sample):
    first = True

    # Get list of input files for this class, it's a list of lists --> one list per sample belonging to this class
    list_of_inputfiles = []
    idx = 0
    for (j, inputfile) in enumerate(inputfiles):
        add_this_file = False
        if maxfiles_per_sample is None:
            add_this_file = True
        if not add_this_file and samplename in maxfiles_per_sample:
            if idx < maxfiles_per_sample[samplename]:
                add_this_file = True
        if ('%s_'%(samplename) in inputfile) and not ('Weights_' in inputfile) and (inputfile.endswith('.npy')) and add_this_file:
            list_of_inputfiles.append(inputfile)
            idx += 1
    # print list_of_inputfiles

    # Read files for this sample
    print green('  --> Now starting with sample %s' % (samplename))
    for (i, inputfile) in enumerate(list_of_inputfiles):
        print green('    --> At file no. %i out of %i.' % (i+1, len(list_of_inputfiles)))
        if first:
            input = np.load(os.path.join(inpath, inputfile))
            weight = np.load(os.path.join(inpath, 'Weights_%s' % (inputfile)))
            first = False
        else:
            input  = np.concatenate((input, np.load(os.path.join(inpath, inputfile))))
            weight = np.concatenate((weight, np.load(inpath, 'Weights_%s' % (inputfile))))
    # input = input.astype(np.float64)
    # weight = weight.astype(np.float64)
    return {'input': input, 'weight': weight}
