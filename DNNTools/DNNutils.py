import os, shutil
import numpy as np
import pandas as pd
from collections import OrderedDict
from printing_utils import green, blue
from utils import ensureDirectory
from functions_dnn import float_to_str

def ClearFolder(folder_path):
    shutil.rmtree(folder_path)
    ensureDirectory(folder_path)

def CleanFile(fname):
    if os.path.exists(fname):
        os.remove(fname)

def SavePandas(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    if fname.endswith('.pkl'):
        obj.to_pickle(fname)
    elif fname.endswith('.csv'):
        obj.to_csv(fname, index_label=False)
    else:
        raise AttributeError('Trying to save a dataframe in an unsupported format.')

def LoadPandas(fname, dtype=None):
    if fname.endswith('.pkl'):
        result = pd.read_pickle(fname)
    elif fname.endswith('.csv'):
        result = pd.read_csv(fname, dtype=dtype)
    else:
        raise AttributeError('Trying to load a dataframe in an unsupported format.')
    return result

def SaveNumpy(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    np.save(fname, obj)

def LoadNumpy(fname):
    if fname.endswith('.npy'):
        return np.load(fname)
    else:
        raise AttributeError('Trying to load numpy array in an unsupported format.')

def SaveMPL(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    obj.savefig(fname)

def LoadObjects(inputdir, basename, modes=['train', 'val', 'test'], format='csv', frac=float_to_str(1.00)):
    obj = OrderedDict()
    for mode in modes:
        print(blue('  --> Loading %s[%s]'%(basename,mode)))
        fname = os.path.join(inputdir, '%s_%s_%s.%s' %(basename,mode,frac,format))
        if format=='npy':
            obj[mode] = LoadNumpy(fname)
        elif format == 'pkl' or format == 'csv':
            obj[mode] = LoadPandas(fname, dtype='float32')
        else:
            raise AttributeError('Trying to load an object in an unsupported format.')
    return obj

def FromNumpyToOneHotEncoder(labels):
    from sklearn import preprocessing
    labels = labels.to_numpy().reshape(len(labels), 1)
    labels = preprocessing.OneHotEncoder(sparse=False).fit_transform(labels)
    return labels

def FromOneHotEncoderToNumpy(labels):
    return np.argmax(labels, axis = 1)
