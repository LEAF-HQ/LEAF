import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
import PreprocessInputs
import ConvertRootToInputs


class DNNRunner:
    def __init__(self, dnnparameters, year, analysisname, input_base_path, result_base_path, selectionstage, selectionname, plotprefix, samples):

        self.dnnparameters = dnnparameters
        self.year = year
        self.analysisname  = analysisname
        self.input_base_path  = input_base_path
        self.selectionstage = selectionstage
        self.selectionname = selectionname
        self.plotprefix = plotprefix
        self.samples = samples

        # stitch together a few paths
        self.inputpath_root      = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname)
        self.inputpath_raw       = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname, 'DNN', 'RawInputs')
        self.inputpath_preproc   = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname, 'DNN', 'ProcessedInputs')
        self.resultpath          = os.path.join(result_base_path, analysisname, year, selectionstage, selectionname)
        self.plotoutput_path     = os.path.join(self.resultpath, 'plots')
        self.dataoutput_path     = os.path.join(os.environ['ANALYZERPATH'], analysisname, 'data', year)
        ensureDirectory(self.plotoutput_path)

        # bind functions
        DNNRunner.ConvertRootToInputs = ConvertRootToInputs.ConvertRootToInputs
        DNNRunner.PreprocessInputs  = PreprocessInputs.PreprocessInputs

        print green('--> Set up DNNRunner for year %s:' % (str(year)))
        for key in self.__dict__.keys():
            print green('  --> %s: %s' % (str(key), str(self.__dict__[key])))
