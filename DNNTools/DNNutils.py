import os, shutil
import numpy as np
import pandas as pd
from printing_utils import green, blue
from utils import ensureDirectory

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

def LoadPandas(fname):
    if fname.endswith('.pkl'):
        result = pd.read_pickle(fname)
    elif fname.endswith('.csv'):
        result = pd.read_csv(fname)
    else:
        raise AttributeError('Trying to load a dataframe in an unsupported format.')
    return result

def SaveNumpy(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    np.save(fname, obj)

def SaveMPL(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    obj.savefig(fname)
