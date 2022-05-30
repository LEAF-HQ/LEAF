import os
import numpy as np
import pandas as pd
from utils import ensureDirectory


def CleanFile(fname):
    if os.path.exists(fname):
        os.remove(fname)

def SavePandas(obj, fname):
    CleanFile(fname)
    obj.to_pickle(fname)

def SaveNumpy(obj, fname):
    CleanFile(fname)
    np.save(fname, obj)
