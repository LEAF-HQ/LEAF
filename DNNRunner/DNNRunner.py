import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
import PreprocessInputs
import ConvertRootToInputs
import PlotInputs
import TrainNetwork
import MakePrediction
import PlotPerformance


class DNNRunner:
    def __init__(self, dnnparameters, year, analysisname, input_base_path, result_base_path, selectionstage, selectionname, plotprefix, samples, colors=['C0', 'C3', 'C1', 'C2', 'C4']):

        self.dnnparameters = dnnparameters
        self.year = year
        self.analysisname  = analysisname
        self.input_base_path  = input_base_path
        self.selectionstage = selectionstage
        self.selectionname = selectionname
        self.plotprefix = plotprefix
        self.samples = samples
        self.colors = colors

        # stitch together a few paths
        self.inputpath_root        = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname)
        self.inputpath_raw         = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname, 'DNN', 'RawInputs')
        self.inputpath_preproc     = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname, 'DNN', 'ProcessedInputs')
        self.inputpath_predictions = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname, 'DNN', 'Predictions')
        self.resultpath            = os.path.join(result_base_path, analysisname, year, selectionstage, selectionname)
        self.plotoutput_path       = os.path.join(self.resultpath, 'plots')
        self.dataoutput_path       = os.path.join(self.resultpath, 'data')
        ensureDirectory(self.plotoutput_path)
        ensureDirectory(self.dataoutput_path)

        # bind functions
        DNNRunner.ConvertRootToInputs = ConvertRootToInputs.ConvertRootToInputs
        DNNRunner.PreprocessInputs  = PreprocessInputs.PreprocessInputs
        DNNRunner.PlotInputs  = PlotInputs.PlotInputs
        DNNRunner.TrainNetwork  = TrainNetwork.TrainNetwork
        DNNRunner.MakePrediction  = MakePrediction.MakePrediction
        DNNRunner.PlotPerformance  = PlotPerformance.PlotPerformance
        DNNRunner.plot_loss  = PlotPerformance.plot_loss
        DNNRunner.plot_accuracy  = PlotPerformance.plot_accuracy
        DNNRunner.plot_rocs  = PlotPerformance.plot_rocs


        print green('--> Set up DNNRunner for year %s:' % (str(year)))
        for key in self.__dict__.keys():
            print green('  --> %s: %s' % (str(key), str(self.__dict__[key])))
