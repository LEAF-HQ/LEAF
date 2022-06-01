import os
from printing_utils import green
import numpy as np
from collections import OrderedDict

def float_to_str(f):
    s = '%1.2f' % f
    result = s.replace('.', 'p').replace('-', 'm')
    return result

def list_to_str(list_, sep='+'):
    return sep.join([str(x).replace('.', 'p') for x in list_])

def keyFromValue(dict_, val):
    return list(dict_.keys())[list(dict_.values()).index(val)]

def classstring_from_label(classes, label):
    return list_to_str(list(k for k,v in classes.items() if v==label),sep='+')

def classes_to_str(dict_):
    vals = list(sorted(set(dict_.values())))
    return list_to_str(list(str(val)+'_'+classstring_from_label(dict_, val) for val in vals), sep='_')

def dict_to_str(dict_):
    result = ''
    for key in dict_:
        if isinstance(dict_[key], list):
            result += '%s_%s_' % (str(key), list_to_str(dict_[key]))
        else:
            result += '%s_%s_' % (str(key), str(dict_[key]))
    return result.strip('_').replace('.', 'p')





def load_data(inputfolder, fraction, postfix):

    print(green('--> Loading data...'))


    # os.path.join(self.inputpath_preproc, classtag, 'sample_weights_%s_train.npy' % (float_to_str(percentage)) )
    input_train = np.load(os.path.join(inputfolder,          'input_%s_train%s.npy' % (float_to_str(fraction), postfix)))
    input_test = np.load(os.path.join(inputfolder,           'input_%s_test%s.npy' % (float_to_str(fraction), postfix)))
    input_val = np.load(os.path.join(inputfolder,            'input_%s_val%s.npy' % (float_to_str(fraction), postfix)))
    labels_train = np.load(os.path.join(inputfolder,         'labels_%s_train%s.npy' % (float_to_str(fraction), postfix)))
    labels_test = np.load(os.path.join(inputfolder,          'labels_%s_test%s.npy' % (float_to_str(fraction), postfix)))
    labels_val = np.load(os.path.join(inputfolder,           'labels_%s_val%s.npy' % (float_to_str(fraction), postfix)))
    sample_weights_train = np.load(os.path.join(inputfolder, 'sample_weights_%s_train%s.npy' % (float_to_str(fraction), postfix)))
    eventweights_train = np.load(os.path.join(inputfolder,   'eventweights_%s_train%s.npy' % (float_to_str(fraction), postfix)))
    sample_weights_test = np.load(os.path.join(inputfolder,  'sample_weights_%s_test%s.npy' % (float_to_str(fraction), postfix)))
    eventweights_test = np.load(os.path.join(inputfolder,    'eventweights_%s_test%s.npy' % (float_to_str(fraction), postfix)))
    sample_weights_val = np.load(os.path.join(inputfolder,   'sample_weights_%s_val%s.npy' % (float_to_str(fraction), postfix)))
    eventweights_val = np.load(os.path.join(inputfolder,     'eventweights_%s_val%s.npy' % (float_to_str(fraction), postfix)))

    return input_train, input_test, input_val, labels_train, labels_test, labels_val, sample_weights_train, sample_weights_test, sample_weights_val, eventweights_train, eventweights_test, eventweights_val


def parameters_to_tag(parameters):

    tag = ''
    for key in parameters:
        val = parameters[key]
        if isinstance(val, OrderedDict):
            tag += '%s_%s__' % (key, dict_to_str(val))
        elif isinstance(val, list):
            tag += '%s_%s__' % (key, list_to_str(val))
        else:
            tag += '%s_%s__' % (key, val)
    return tag.strip('_').replace('.', 'p')
