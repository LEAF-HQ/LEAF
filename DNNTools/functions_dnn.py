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
