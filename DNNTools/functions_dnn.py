import os
from printing_utils import green
import numpy as np
from collections import OrderedDict
from sklearn.metrics import roc_auc_score, roc_curve, auc, confusion_matrix
from sklearn.utils.extmath import stable_cumsum
from sklearn.utils import check_consistent_length, assert_all_finite, column_or_1d, check_array
import scipy.optimize as opt
from scipy.optimize import fsolve
from sklearn.utils.multiclass import type_of_target
from sklearn.model_selection import train_test_split
import ROOT as rt

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

def list_to_tgraph(x, y):
    # x and y must be iterables (tuples, lists, ...) of equal length
    if not len(x) == len(y):
        raise ValueError('In \'list_to_tgraph(): Passed two lists with different length.\'')
    g = rt.TGraph(len(x), x, y)
    return g

def get_fpr_tpr_thr_auc(score, labels, weights,is_standardized=False):

    FalsePositiveRates = {}
    TruePositiveRates = {}
    Thresholds = {}
    SignalPuritys = {}
    aucs = {}

    for i in labels[labels.columns[0]].unique():
        fpr, tpr, thr, pur = roc_curve_and_purity(y_true=labels, y_score=score, sample_weight=weights, pos_label=i)

        # FalsePositiveRates[i], TruePositiveRates[i], Thresholds[i], SignalPuritys[i] = roc_curve_and_purity(y_true=labels, y_score=score, sample_weight=weights, pos_label=i)
        # aucs[i] = np.trapz(TruePositiveRates[i], FalsePositiveRates[i])
        if not is_standardized:
            Thresholds[i] = np.ma.masked_where((thr > 1) | (thr < 0), thr)
            mask = Thresholds[i].mask
            Thresholds[i] = Thresholds[i].compressed()
            FalsePositiveRates[i] = np.ma.masked_where(mask, fpr).compressed()
            TruePositiveRates[i]  = np.ma.masked_where(mask, tpr).compressed()
            SignalPuritys[i]      = np.ma.masked_where(mask, pur).compressed()
        else:
            Thresholds[i] = thr
            FalsePositiveRates[i] = fpr
            TruePositiveRates[i]  = tpr
            SignalPuritys[i]      = pur
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

    return fpr, tpr, thresholds, np.asarray(prt, dtype=fpr.dtype)

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
