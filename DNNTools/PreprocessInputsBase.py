import os, pickle
import numpy as np
import pandas as pd
from sklearn import preprocessing, model_selection
from sklearn.utils import class_weight
from ConvertRootToInputsBase import SavePandas, SaveNumpy

from utils import ensureDirectory
from functions_dnn import *
import copy



class PreprocessInputsBase():
    def __init__(self, maxfiles_per_sample=None, runonfraction = 1.0, train_test_val_split=(0.8, 0.1, 0.1), inputdir='', outdir=''):
        self.maxfiles_per_sample = maxfiles_per_sample
        self.runonfraction = runonfraction
        self.train_test_val_split = train_test_val_split
        self.inputdir = inputdir
        self.outdir = outdir
        self.colname_label = 'label'
        self.colname_weights =  'Events.GenEvent.Event.weight'

    def DefineVariables(self):
        varnames = []
        return varnames

    def DefineSamples(self):
        samples = []
        return samples

    def DefineClasses(self):
        classes = []
        return classes

    def GetInputs(self):
        inputs = []
        for samplename in self.DefineSamples():
            list_of_inputfiles = list(filter(lambda x: samplename in x, os.listdir(self.inputdir)))
            if self.maxfiles_per_sample != None and samplename in self.maxfiles_per_sample:
                list_of_inputfiles = list_of_inputfiles[:self.maxfiles_per_sample[samplename]]
            print green('  --> Now starting with sample %s' % (samplename))
            for i, inputfile in enumerate(list_of_inputfiles):
                print green('    --> At file no. %i out of %i.' % (i+1, len(list_of_inputfiles)))
                inputs.append(pd.read_pickle(os.path.join(self.inputdir, inputfile)))
        self.df = pd.concat(inputs)
        self.df.rename(lambda x: x[0] if isinstance(x, tuple) else x , axis='columns', inplace=True)
        print(blue('Collected events: '+str(len(self.df))))

    def RemoveNanInf(self):
        # Treat inf and nan entries
        self.df.replace(np.inf, 999999, inplace=True)
        self.df.replace(-np.inf, -999999., inplace=True)
        self.df.replace(np.nan, 0, inplace=True)


    def SampleEvents(self, fraction=1.0, weights=None, random_state=123456):
        self.df = self.df.sample(frac=fraction, weights=weights, random_state=random_state)


    def Split(self, ratios={'train':0.8, 'validation':0.1, 'test':0.1}):
        inputs = self.df.copy(deep=True)
        weights = self.df.copy(deep=True).loc[:,self.colname_weights]
        labels = self.df.copy(deep=True).loc[:,self.colname_label].apply(lambda x: self.DefineClasses()[x])
        labels = labels.to_numpy().reshape(len(labels), 1)
        labels = preprocessing.OneHotEncoder(sparse=False).fit_transform(labels)
        inputs.drop(columns=[self.colname_weights, self.colname_label], inplace=True)
        if np.sum(ratios.values())!= 1: raise RuntimeError('Unexpected ratios for train-validation-test splitting.')
        self.input_train, self.input_test, self.label_train, self.label_test, self.weights_train, self.weights_test = model_selection.train_test_split(inputs, labels, weights, train_size=ratios['train'])
        self.input_val, self.input_test, self.label_val, self.label_test, self.weights_val, self.weights_test = model_selection.train_test_split(self.input_test, self.label_test, self.weights_test, test_size=ratios['test']/(ratios['test'] + ratios['validation']))

        print(len(self.input_train), len(self.input_val), len(self.input_test))
        print(type(self.input_train), type(self.label_train), type(self.weights_train))

    def FitScalers(self):
        self.scalers = {}
        # self.scalers['standard'] = preprocessing.StandardScaler().fit(self.input_train)

    def Transform(self):
        # for scaler in self.scalers.values():
        #     for df in [self.input_train,self.input_val,self.input_test]:
        #         print type(self.df),
        #         scaled_features = scaler.transform(df)
        #         df = pd.DataFrame(scaled_features, index=df.index, columns=df.columns)
        #         print type(df)

        for scaler in self.scalers.values():
            print type(self.input_train),
            scaled_features = scaler.transform(self.input_train)
            self.input_train = pd.DataFrame(scaled_features, index=self.input_train.index, columns=self.input_train.columns)
            print type(self.input_train)
            print type(self.label_train),
            scaled_features = scaler.transform(self.input_val)
            self.input_val = pd.DataFrame(scaled_features, index=self.input_val.index, columns=self.input_val.columns)
            print type(self.label_train)
            print type(self.weights_train),
            scaled_features = scaler.transform(self.input_test)
            self.input_test = pd.DataFrame(scaled_features, index=self.input_test.index, columns=self.input_test.columns)
            print type(self.weights_train)

    def SaveBase(self):
        print(blue('--> saving'))
        frac = float_to_str(self.runonfraction)
        outdir = os.path.join(self.outdir, classes_to_str(self.DefineClasses()))
        ensureDirectory(outdir)
        SavePandas(self.input_train,   os.path.join(outdir, 'input_train_%s.pkl'   %frac ))
        SavePandas(self.input_val,     os.path.join(outdir, 'input_val_%s.pkl'     %frac ))
        SavePandas(self.input_test,    os.path.join(outdir, 'input_test_%s.pkl'    %frac ))
        SaveNumpy(self.label_train,    os.path.join(outdir, 'label_train_%s.npy'   %frac ))
        SaveNumpy(self.label_val,      os.path.join(outdir, 'label_val_%s.npy'     %frac ))
        SaveNumpy(self.label_test,     os.path.join(outdir, 'label_test_%s.npy'    %frac ))
        SavePandas(self.weights_train, os.path.join(outdir, 'weights_train_%s.pkl' %frac ))
        SavePandas(self.weights_val,   os.path.join(outdir, 'weights_val_%s.pkl'   %frac ))
        SavePandas(self.weights_test,  os.path.join(outdir, 'weights_test_%s.pkl'  %frac ))

    def Save(self):
        self.SaveBase()

    def Process(self):
        self.GetInputs()
        self.RemoveNanInf()
        print(blue('Filtered events: '+str(len(self.df))))
        self.SampleEvents(fraction=self.runonfraction)
        print(blue('Final events: '+str(len(self.df))))
        self.Split()
        self.FitScalers()
        self.Transform()
        self.Save()





def PreprocessInputsOld(self, maxfiles_per_sample, train_test_val_split=(4./6, 1./6, 1./6)):
    # maxfiles_per_sample is a dictionary containing samplenames as keys and integers as value, giving the maximum absolute number of files to read in per sample.
    # If it is None, read all files available

    # Get dnnparameters
    classes = self.dnnparameters['classes']
    # Find initial file for each class
    inputfiles = os.listdir(self.filepath_raw)
    print 'inputfiles', inputfiles
    # return

    # load inputs and event weights for each sample in self.samples
    inputs = []
    for samplename in self.samples:
        list_of_inputfiles = list(filter(lambda x: samplename in x, inputfiles))
        if maxfiles_per_sample != None and samplename in maxfiles_per_sample:
            list_of_inputfiles = list_of_inputfiles[:maxfiles_per_sample[samplename]]
        print green('  --> Now starting with sample %s' % (samplename))
        for (i, inputfile) in enumerate(list_of_inputfiles):
            print green('    --> At file no. %i out of %i.' % (i+1, len(list_of_inputfiles)))
            inputs.append(pd.read_pickle(os.path.join(self.filepath_raw, inputfile)))

    input_total = pd.concat(inputs)

    print(blue('Collected events: '+str(len(input_total))))
    # Treat inf and nan entries
    input_total.replace(np.inf, 999999, inplace=True)
    input_total.replace(-np.inf, -999999., inplace=True)
    input_total.replace(np.nan, 0)
    # input_total.replace([np.inf, -np.inf], np.nan, inplace=True).dropna()
    # input_total.dropna()
    print(blue('Filtered events: '+str(len(input_total))))

    return

    # input_total.sample(frac=self.dnnparameters['runonfraction'], weights=None, replace=True, random_state=123456)
    #
    # eventweight_total = input_total.loc[:,'Events.GenEvent.Event.weight']
    # label_concatenated = input_total.loc[:,'label'].apply(lambda x: classes[x])
    # label_total = label_concatenated.to_numpy().reshape(len(label_concatenated), 1)
    # label_total = preprocessing.OneHotEncoder(sparse=False).fit_transform(label_total)
    # input_total.drop(columns=['Events.GenEvent.Event.weight', 'label'], inplace=True)

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

    with open(os.path.join(self.filepath_raw, 'variable_names.pkl'), 'r') as f:
        variable_names = pickle.load(f)

    # Write out scaler info
    ensureDirectory(os.path.join(self.filepath_preproc, classtag))
    norminfofile = os.path.join(self.filepath_preproc, classtag, 'NormInfo.txt')
    with open(norminfofile, 'w') as f:
        for i in range(scaler.mean_.shape[0]):
            var = variable_names[i]
            mean = scaler.mean_[i]
            scale = scaler.scale_[i]
            line = '%s StandardScaler %s %s\n' % (str(var), str(mean), str(scale))
            f.write(line)



    varnamefile = os.path.join(self.filepath_preproc, classtag, 'variable_names.pkl')
    with open(varnamefile, 'w') as f:
        pickle.dump(variable_names, f)


    np.save(os.path.join(self.filepath_preproc, classtag, 'input_%s_train.npy' % (float_to_str(percentage)) )  , input_train)
    np.save(os.path.join(self.filepath_preproc, classtag, 'input_%s_test.npy' % (float_to_str(percentage)) )   , input_test)
    np.save(os.path.join(self.filepath_preproc, classtag, 'input_%s_val.npy' % (float_to_str(percentage)) )    , input_val)
    np.save(os.path.join(self.filepath_preproc, classtag, 'labels_%s_train.npy' % (float_to_str(percentage)) ) , labels_train)
    np.save(os.path.join(self.filepath_preproc, classtag, 'labels_%s_test.npy' % (float_to_str(percentage)) )  , labels_test)
    np.save(os.path.join(self.filepath_preproc, classtag, 'labels_%s_val.npy' % (float_to_str(percentage)) )   , labels_val)

    np.save(os.path.join(self.filepath_preproc, classtag, 'sample_weights_%s_train.npy' % (float_to_str(percentage)) ), sample_weights_train)
    np.save(os.path.join(self.filepath_preproc, classtag, 'eventweights_%s_train.npy' % (float_to_str(percentage)) ), eventweight_train)
    np.save(os.path.join(self.filepath_preproc, classtag, 'sample_weights_%s_test.npy' % (float_to_str(percentage)) ), sample_weights_test)
    np.save(os.path.join(self.filepath_preproc, classtag, 'eventweights_%s_test.npy' % (float_to_str(percentage)) ), eventweight_test)
    np.save(os.path.join(self.filepath_preproc, classtag, 'sample_weights_%s_val.npy' % (float_to_str(percentage)) ), sample_weights_val)
    np.save(os.path.join(self.filepath_preproc, classtag, 'eventweights_%s_val.npy' % (float_to_str(percentage)) ), eventweight_val)
