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
    obj.to_pickle(fname)

def SaveNumpy(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    np.save(fname, obj)

def SaveMPL(obj, fname):
    CleanFile(fname)
    ensureDirectory(fname[:fname.rfind('/')])
    obj.savefig(fname)
