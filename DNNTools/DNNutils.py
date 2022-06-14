import os, shutil
import numpy as np
import pandas as pd
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


def LoadDFWeightsLabelsIntoObject(obj, inputdir_df, basename_df, attribute_name_target, inputdir_weights, basename_weights, inputdir_label, basename_label, modes=['train', 'val', 'test'], format='csv', frac=float_to_str(1.00)):
    parts = []
    for mode in modes:
        print(blue('  --> Loading for subset \'%s\'' % (mode)))
        df            = LoadPandas(os.path.join(inputdir_df, '%s_%s_%s.%s' %(basename_df,mode,frac,format) ))
        df['label']   = np.load(os.path.join(inputdir_label, '%s_%s_%s.npy' %(basename_label,mode,frac) )).tolist()
        df['label']   = np.argmax(np.array(df['label'].to_list()), axis = 1)
        df['weights'] = LoadPandas(os.path.join(inputdir_weights, '%s_%s_%s.%s' %(basename_weights,mode,frac,format) ))
        parts.append(df)
        print(blue('  --> Loaded for subset \'%s\'' % (mode)))
    setattr(obj, str(attribute_name_target), pd.concat(parts))
