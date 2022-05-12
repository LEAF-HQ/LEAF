import os, sys, math, time
import subprocess
from utils import *
import numpy as np
from collections import OrderedDict
from sklearn import preprocessing, svm
from sklearn.metrics import roc_auc_score, roc_curve, auc, confusion_matrix
from sklearn.utils.extmath import stable_cumsum
from sklearn.utils import check_consistent_length, assert_all_finite, column_or_1d, check_array
import scipy.optimize as opt
from scipy.optimize import fsolve
from sklearn.utils.multiclass import type_of_target
from sklearn.model_selection import train_test_split

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

def get_classtitles(classes):
    result = {}
    for c in classes:
        result[c] = list_to_str(classes[c])
    return result



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

def float_to_str(f):
    s = '%1.2f' % f
    result = s.replace('.', 'p').replace('-', 'm')
    return result

def load_data(inputfolder, fraction, postfix):

    print green('    --> Loading data...')


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

def load_predictions(inputfolder, modeltag='last', filepostfix=''):

    print green('    --> Loading predictions...')

    # Load model prediction
    pred_train = np.load(os.path.join(inputfolder, 'prediction_%s_train%s.npy'%(modeltag, filepostfix)))
    pred_test = np.load(os.path.join(inputfolder, 'prediction_%s_test%s.npy'%(modeltag, filepostfix)))
    pred_val = np.load(os.path.join(inputfolder, 'prediction_%s_val%s.npy'%(modeltag, filepostfix)))

    return pred_train, pred_test, pred_val


def remove_and_numpy_save(filename, content):
    if os.path.exists(filename):
        os.remove(filename)
    np.save(filename, content)

def get_fpr_tpr_thr_auc(pred, labels, weights):

    FalsePositiveRates = {}
    TruePositiveRates = {}
    Thresholds = {}
    SignalPuritys = {}
    aucs = {}

    for i in range(labels.shape[1]):
        FalsePositiveRates[i], TruePositiveRates[i], Thresholds[i], SignalPuritys[i] = roc_curve_and_purity(labels[:,i], pred[:,i], sample_weight=weights)
        aucs[i] = np.trapz(TruePositiveRates[i], FalsePositiveRates[i])

    return (FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys)

def roc_curve_and_purity(y_true, y_score, pos_label=None, sample_weight=None, drop_intermediate=True):
    # Copied from https://github.com/scikit-learn/scikit-learn/blob/7389dba/sklearn/metrics/ranking.py#L535
    # Extended by purity-part

    fps, tps, thresholds = binary_clf_curve(y_true, y_score, pos_label=pos_label, sample_weight=sample_weight)
    if drop_intermediate and len(fps) > 2:
        optimal_idxs = np.where(np.r_[True, np.logical_or(np.diff(fps, 2), np.diff(tps, 2)), True])[0]
        fps = fps[optimal_idxs]
        tps = tps[optimal_idxs]
        thresholds = thresholds[optimal_idxs]

    if tps.size == 0 or fps[0] != 0 or tps[0] != 0:
        tps = np.r_[0, tps]
        fps = np.r_[0, fps]
        thresholds = np.r_[thresholds[0] + 1, thresholds]

    if fps[-1] <= 0:
        warnings.warn("No negative samples in y_true, "
                      "false positive value should be meaningless",
                      UndefinedMetricWarning)
        fpr = np.repeat(np.nan, fps.shape)
    else:
        fpr = fps / fps[-1]

    if tps[-1] <= 0:
        warnings.warn("No positive samples in y_true, "
                      "true positive value should be meaningless",
                      UndefinedMetricWarning)
        tpr = np.repeat(np.nan, tps.shape)
    else:
        tpr = tps / tps[-1]

    # purity!
    prt = []
    for i in range(len(tps)):
        if (tps[i]+fps[i]) > 0:
            prt.append(tps[i]/(tps[i]+fps[i]))
        else:
            prt.append(0.)

    return fpr, tpr, thresholds, prt

def binary_clf_curve(y_true, y_score, pos_label=None, sample_weight=None):
    # Check to make sure y_true is valid
    y_type = type_of_target(y_true)
    if not (y_type == "binary" or
            (y_type == "multiclass" and pos_label is not None)):
        raise ValueError("{0} format is not supported".format(y_type))

    check_consistent_length(y_true, y_score, sample_weight)
    y_true = column_or_1d(y_true)
    y_score = column_or_1d(y_score)
    assert_all_finite(y_true)
    assert_all_finite(y_score)

    if sample_weight is not None:
        sample_weight = column_or_1d(sample_weight)

    # ensure binary classification if pos_label is not specified
    classes = np.unique(y_true)
    if (pos_label is None and
        not (np.array_equal(classes, [0, 1]) or
             np.array_equal(classes, [-1, 1]) or
             np.array_equal(classes, [0]) or
             np.array_equal(classes, [-1]) or
             np.array_equal(classes, [1]))):
        raise ValueError("Data is not binary and pos_label is not specified")
    elif pos_label is None:
        pos_label = 1.

    # make y_true a boolean vector
    y_true = (y_true == pos_label)

    # sort scores and corresponding truth values
    desc_score_indices = np.argsort(y_score, kind="mergesort")[::-1]
    y_score = y_score[desc_score_indices]
    y_true = y_true[desc_score_indices]
    if sample_weight is not None:
        weight = sample_weight[desc_score_indices]
    else:
        weight = 1.

    # y_score typically has many tied values. Here we extract
    # the indices associated with the distinct values. We also
    # concatenate a value for the end of the curve.
    distinct_value_indices = np.where(np.diff(y_score))[0]
    threshold_idxs = np.r_[distinct_value_indices, y_true.size - 1]

    # accumulate the true positives with decreasing threshold
    tps = stable_cumsum(y_true * weight)[threshold_idxs]
    if sample_weight is not None:
        # express fps as a cumsum to ensure fps is increasing even in
        # the presence of floating point errors
        fps = stable_cumsum((1 - y_true) * weight)[threshold_idxs]
    else:
        fps = 1 + threshold_idxs - tps
    return fps, tps, y_score[threshold_idxs]
