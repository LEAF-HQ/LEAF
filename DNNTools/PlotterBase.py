import os, tqdm
import numpy as np
import pandas as pd

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from printing_utils import green, blue
from DNNutils import SaveMPL
from functions_dnn import classes_to_str, float_to_str, get_fpr_tpr_thr_auc, list_to_tgraph
from PlottingFunctions import plot_rocs
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

    def PlotSingleVariable(self, dfs, weights, labels, style, variable_name, outdir, ylabel='Number of events / bin', yscale='log'):
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
                plt.hist(df_thisclass, weights=weights_thisclass, range=(hist_min, hist_max), **style_thisclass)

        plt.legend(loc='best',ncol=len(classes))
        plt.yscale(yscale)
        plt.xlabel(variable_name)
        plt.ylabel(ylabel)
        fname = os.path.join(outdir, '%s_%s.pdf' % (variable_name, self.frac))
        SaveMPL(fig, fname)
        plt.close()


    def PlotROCSingleVariable(self, df, weights, labels, variable_name, outdir, is_standardized=False):
        style_per_class = self.DefineStyle()
        FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys = get_fpr_tpr_thr_auc(score=df[variable_name], labels=labels, weights=weights, is_standardized=is_standardized)
        rocs = OrderedDict()
        purities = OrderedDict()
        purities_vs_score = OrderedDict()
        for i in sorted(labels[labels.columns[0]].unique()):
            g_roc = list_to_tgraph(TruePositiveRates[i], FalsePositiveRates[i])
            g_pur = list_to_tgraph(TruePositiveRates[i], SignalPuritys[i])
            g_pur_vs_score = list_to_tgraph(Thresholds[i], SignalPuritys[i])
            info = {'color': style_per_class[i]['rootcolor'], 'legendtext': style_per_class[i]['label'], 'auc': aucs[i]}
            info_pur = deepcopy(info)
            info_pur.pop('auc', None)
            info_pur_vs_score = info_pur
            rocs[g_roc] = info
            purities[g_pur] = info_pur
            purities_vs_score[g_pur_vs_score] = info_pur_vs_score

        plot_rocs(rocs=rocs, name=os.path.join(outdir, 'ROC_%s'%(variable_name)), x_title='Selection efficiency', y_title='Background efficiency')
        plot_rocs(rocs=purities, name=os.path.join(outdir, 'EfficiencyVsPurity_%s'%(variable_name)), x_title='Selection efficiency', y_title='Signal purity', logy=False)
        plot_rocs(rocs=purities_vs_score, name=os.path.join(outdir, 'ScoreVsPurity_%s'%(variable_name)), x_title='Lower cut on DNN score', y_title='Signal purity S/(S+B)', logy=False)


    def PlotROCSummary(self, df, weights, labels, outdir, score_basename='score', is_standardized=False):
        # for each class in df, use >> 'score_%i' % (cl) << to plot the "optimal" ROC curves for each node in the same plot
        style_per_class = self.DefineStyle()
        rocs = OrderedDict()
        purities = OrderedDict()
        purities_vs_score = OrderedDict()
        for i in sorted(labels[labels.columns[0]].unique()):
            FalsePositiveRates, TruePositiveRates, Thresholds, aucs, SignalPuritys = get_fpr_tpr_thr_auc(score=df['%s_%i'%(score_basename, i)], labels=labels, weights=weights, is_standardized=is_standardized)

            g_roc = list_to_tgraph(TruePositiveRates[i], FalsePositiveRates[i])
            g_pur = list_to_tgraph(TruePositiveRates[i], SignalPuritys[i])
            g_pur_vs_score = list_to_tgraph(Thresholds[i], SignalPuritys[i])
            info = {'color': style_per_class[i]['rootcolor'], 'legendtext': style_per_class[i]['label'], 'auc': aucs[i]}
            info_pur = deepcopy(info)
            info_pur.pop('auc', None)
            info_pur_vs_score = info_pur
            rocs[g_roc] = info
            purities[g_pur] = info_pur
            purities_vs_score[g_pur_vs_score] = info_pur_vs_score
        plot_rocs(rocs=rocs, name=os.path.join(outdir, 'ROC_summary'), x_title='Selection efficiency', y_title='Background efficiency')
        plot_rocs(rocs=purities, name=os.path.join(outdir, 'EfficiencyVsPurity_summary'), x_title='Selection efficiency', y_title='Signal purity', logy=False)
        plot_rocs(rocs=purities_vs_score, name=os.path.join(outdir, 'ScoreVsPurity_summary'), x_title='Lower cut on DNN score', y_title='Signal purity S/(S+B)', logy=False)


    def PlotDF(self, dfs, weights, labels, outdir):
        print(blue('--> Plotting dataframe'))
        self.DefineCommonStyle()
        self.DefineStylePerVariable()
        for variable_name in tqdm.tqdm(dfs[dfs.keys()[0]].columns, desc="Plots done"):
            self.PlotSingleVariable(dfs=dfs, weights=weights, labels=labels, style=self.DefineStyle(), variable_name=variable_name, outdir=outdir)
        print(green('--> Plotted dataframe'))
