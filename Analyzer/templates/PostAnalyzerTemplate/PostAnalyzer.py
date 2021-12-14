import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
import functions.ProduceCombineHistograms
import functions.PlotLimits
import functions.Combine
# import ROOT


class PostAnalyzer:
    def __init__(self, year, analysisname, input_base_path, result_base_path, selectionstage, selectionname, systematics, backgrounds, signals, signalmass_identifier, channels, histnames_in_out_per_category, limithisttag, processes_per_systematic, pdf_per_systematic, value_per_systematic, crosssection_path=None):

        # bind arguments to class
        self.year = year
        self.analysisname  = analysisname
        self.input_base_path  = input_base_path
        self.selectionstage = selectionstage
        self.selectionname = selectionname
        self.user = os.environ['USER']
        self.systematics = systematics
        self.backgrounds = backgrounds
        self.signals = signals
        self.signalmass_identifier = signalmass_identifier
        self.channels = channels
        self.histnames_in_out_per_category = histnames_in_out_per_category
        self.limithisttag = limithisttag
        self.processes_per_systematic = processes_per_systematic
        self.pdf_per_systematic = pdf_per_systematic
        self.value_per_systematic = value_per_systematic

        # stitch together a few paths
        self.crosssection_path   = crosssection_path
        self.finalselection_path = os.path.join(input_base_path,  analysisname, year, selectionstage, selectionname)
        self.resultpath          = os.path.join(result_base_path, analysisname, year, selectionstage, selectionname)
        self.combineinput_path   = os.path.join(self.resultpath, 'data', 'combineinput')
        self.combineoutput_path  = os.path.join(self.resultpath, 'data', 'combineoutput')
        self.plotoutput_path     = os.path.join(self.resultpath, 'plots')
        ensureDirectory(self.combineinput_path)
        ensureDirectory(self.combineoutput_path)

        # bind functions
        PostAnalyzer.ProduceCombineHistograms  = functions.ProduceCombineHistograms.ProduceCombineHistograms
        PostAnalyzer.CreateDatacards           = functions.Combine.CreateDatacards
        PostAnalyzer.CombineChannels           = functions.Combine.CombineChannels
        PostAnalyzer.ExecuteCombineCombination = functions.Combine.ExecuteCombineCombination
        PostAnalyzer.PlotLimits                = functions.PlotLimits.PlotLimits

        # print settings
        print green('--> Set up PostAnalyzer for year %s:' % (str(year)))
        for key in self.__dict__.keys():
            print green('  --> %s: %s' % (str(key), str(self.__dict__[key])))

        #done
