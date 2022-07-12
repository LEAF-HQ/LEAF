import os, tqdm
import numpy as np
import pandas as pd

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from printing_utils import green, blue
from DNNutils import SaveMPL
from functions_dnn import classes_to_str, float_to_str, get_fpr_tpr_thr_auc, list_to_tgraph
from PlottingFunctions import plot_graphs
from collections import OrderedDict
from copy import deepcopy


class PlotterBase():
    def __init__(self, runonfraction=1.00):
        self.frac = float_to_str(runonfraction)

    def DefineCommonStyle(self):
        self.common_style = {
            'linewidth': 1.5,
            'histtype': 'step',
            'alpha': 0.5,
            'bins': 100,
        }

    def DefineStyle(self):
        raise NotImplementedError('DefineStyle method is not initialized. Fix this.')

    def DefineStylePerVariable(self):
        self.stylePerVariable = {}

    def PlotSingleVariable(self, dfs, weights, labels, style, variable_name, outdir, ylabel='Number of events / bin', yscale='log', normalize_all=False):
        plt.clf()
        fig = plt.figure()
        classes = list(set(self.classes.values()))

        hist_min = dfs[dfs.keys()[0]][variable_name].min()
        hist_max = dfs[dfs.keys()[0]][variable_name].max()
        for cl in classes:
            style_thisclass = dict(filter(lambda elem: not 'root' in elem[0], style[cl].items()))
            style_thisclass.update(self.common_style)
            for var in self.stylePerVariable:
                if var in variable_name:
                    style_thisclass.update(self.stylePerVariable[var])
            label = style_thisclass['label']
            for name, df in dfs.items():
                style_thisclass.update({'label': label+': '+name,
                                        'linestyle':'dashed' if 'val' in name else ('dotted' if 'test' in name else 'solid')}
                                       )
                mask = labels[name]==cl
                mask = mask[mask.columns[0]]
                weights_thisclass = weights[name][mask]
                weights_thisclass = weights_thisclass[weights_thisclass.columns[0]]
                df_thisclass = df[mask][variable_name]
                if normalize_all:
                    weights_thisclass *= 1./weights_thisclass.sum()
                plt.hist(df_thisclass, weights=weights_thisclass, range=(hist_min, hist_max), **style_thisclass)

        ncol = len(classes) if len(dfs.items()) > 1 else 1
        plt.legend(loc='best',ncol=ncol)
        plt.yscale(yscale)
        plt.xlabel(variable_name)
        plt.ylabel(ylabel)
        fname = os.path.join(outdir, '%s_%s.pdf' % (variable_name, self.frac))
        SaveMPL(fig, fname)
        plt.close()


    def PlotROCSingleVariable(self, df, weights, labels, variable_name, outdir, is_standardized=False, keep_only_every=1):
        style_per_class = self.DefineStyle()
        FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys = get_fpr_tpr_thr_auc(score=df[variable_name], labels=labels, weights=weights, is_standardized=is_standardized, keep_only_every=keep_only_every)
        rocs = OrderedDict()
        purities = OrderedDict()
        purities_vs_score = OrderedDict()
        pur_improvements_vs_score = OrderedDict()
        for i in sorted(labels[labels.columns[0]].unique()):
            g_roc = list_to_tgraph(TruePositiveRates[i], FalsePositiveRates[i])
            g_pur = list_to_tgraph(TruePositiveRates[i][1:], SignalPuritys[i][1:])
            g_pur_vs_score = list_to_tgraph(Thresholds[i][1:], SignalPuritys[i][1:])
            sumweights_sig = weights[(labels[labels.columns[0]] == i)][weights.columns[0]].sum()
            sumweights_backgrounds = weights[~(labels[labels.columns[0]] == i)][weights.columns[0]].sum()
            pur_inclusive = sumweights_sig / (sumweights_sig + sumweights_backgrounds)
            g_pur_improvements_vs_score = list_to_tgraph(Thresholds[i][1:], SignalPuritys[i][1:] / pur_inclusive)

            info = {'color': style_per_class[i]['rootcolor'], 'legendtext': style_per_class[i]['label'], 'auc': aucs[i]}
            info_pur = deepcopy(info)
            info_pur.pop('auc', None)
            info_pur_vs_score = info_pur
            info_pur_improvements_vs_score = info_pur

            rocs[g_roc] = info
            purities[g_pur] = info_pur
            purities_vs_score[g_pur_vs_score] = info_pur_vs_score
            pur_improvements_vs_score[g_pur_improvements_vs_score] = info_pur_improvements_vs_score

        plot_graphs(graphs=rocs, name=os.path.join(outdir, 'ROC_%s'%(variable_name)), x_title='Selection efficiency', y_title='Background efficiency', x_range=(-0.1, 1.1), y_range=(1e-04, 1.2))
        plot_graphs(graphs=purities, name=os.path.join(outdir, 'EfficiencyVsPurity_%s'%(variable_name)), x_title='Selection efficiency', y_title='Signal purity S/(S+B)', x_range=(-0.1, 1.1), y_range=(0, 1.5), logy=False)
        plot_graphs(graphs=purities_vs_score, name=os.path.join(outdir, 'ScoreVsPurity_%s'%(variable_name)), x_title='Lower cut on DNN score', y_title='Signal purity S/(S+B)', x_range=(-0.1, 1.1), y_range=(0, 1.5), logy=False)
        plot_graphs(graphs=pur_improvements_vs_score, name=os.path.join(outdir, 'ImprovementVsPurity_%s'%(variable_name)), x_title='Lower cut on DNN score', y_title='Improvement in S/(S+B)', x_range=(-0.1, 1.1), y_range=(0.1, 100.), logy=True)


    def PlotROCSummary(self, df, weights, labels, outdir, score_basename='score', is_standardized=False, keep_only_every=1):
        # for each class in df, use >> 'score_%i' % (cl) << to plot the "optimal" ROC curves for each node in the same plot
        style_per_class = self.DefineStyle()
        rocs = OrderedDict()
        purities = OrderedDict()
        purities_vs_score = OrderedDict()
        pur_improvements_vs_score = OrderedDict()
        for i in sorted(labels[labels.columns[0]].unique()):
            FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys = get_fpr_tpr_thr_auc(score=df['%s_%i'%(score_basename, i)], labels=labels, weights=weights, is_standardized=is_standardized, keep_only_every=keep_only_every)

            g_roc = list_to_tgraph(TruePositiveRates[i], FalsePositiveRates[i])
            g_pur = list_to_tgraph(TruePositiveRates[i][1:], SignalPuritys[i][1:])
            g_pur_vs_score = list_to_tgraph(Thresholds[i][1:], SignalPuritys[i][1:])
            sumweights_sig = weights[(labels[labels.columns[0]] == i)][weights.columns[0]].sum()
            sumweights_backgrounds = weights[~(labels[labels.columns[0]] == i)][weights.columns[0]].sum()
            pur_inclusive = sumweights_sig / (sumweights_sig + sumweights_backgrounds)
            g_pur_improvements_vs_score = list_to_tgraph(Thresholds[i][1:], SignalPuritys[i][1:] / pur_inclusive)

            info = {'color': style_per_class[i]['rootcolor'], 'legendtext': style_per_class[i]['label'], 'auc': aucs[i]}
            info_pur = deepcopy(info)
            info_pur.pop('auc', None)
            info_pur_vs_score = info_pur
            info_pur_improvements_vs_score = info_pur

            rocs[g_roc] = info
            purities[g_pur] = info_pur
            purities_vs_score[g_pur_vs_score] = info_pur_vs_score
            pur_improvements_vs_score[g_pur_improvements_vs_score] = info_pur_improvements_vs_score

        plot_graphs(graphs=rocs, name=os.path.join(outdir, 'ROC_summary'), x_title='Selection efficiency', y_title='Background efficiency', x_range=(-0.1, 1.1), y_range=(1e-04, 1.2))
        plot_graphs(graphs=purities, name=os.path.join(outdir, 'EfficiencyVsPurity_summary'), x_title='Selection efficiency', y_title='Signal purity S/(S+B)', x_range=(-0.1, 1.1), y_range=(0, 1.5), logy=False)
        plot_graphs(graphs=purities_vs_score, name=os.path.join(outdir, 'ScoreVsPurity_summary'), x_title='Lower cut on DNN score', y_title='Signal purity S/(S+B)', x_range=(-0.1, 1.1), y_range=(0, 1.5), logy=False)
        plot_graphs(graphs=pur_improvements_vs_score, name=os.path.join(outdir, 'ImprovementVsPurity_summary'), x_title='Lower cut on DNN score', y_title='Improvement in S/(S+B)', x_range=(-0.1, 1.1), y_range=(0.1, 100.), logy=True)


    def PlotDF(self, dfs, weights, labels, outdir, ylabel='Number of events / bin', yscale='log', normalize_all=False):
        print(blue('--> Plotting dataframe'))
        self.DefineCommonStyle()
        self.DefineStylePerVariable()
        for variable_name in tqdm.tqdm(dfs[dfs.keys()[0]].columns, desc="Plots done"):
            self.PlotSingleVariable(dfs=dfs, weights=weights, labels=labels, style=self.DefineStyle(), variable_name=variable_name, outdir=outdir, ylabel=ylabel, yscale=yscale, normalize_all=normalize_all)
        print(green('--> Plotted dataframe'))
