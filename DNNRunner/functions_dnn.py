import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict

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


def list_to_str(list):
    return '+'.join([str(x).replace('.', 'p') for x in list])

def dict_to_str(dict):
    result = ''
    for key in dict:
        if isinstance(dict[key], list):
            result += '%s_%s_' % (str(key), list_to_str(dict[key]))
        else:
            result += '%s_%s_' % (str(key), str(dict[key]))
    return result.strip('_').replace('.', 'p')
