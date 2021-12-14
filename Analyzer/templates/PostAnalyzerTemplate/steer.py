#! /usr/bin/env python

import os, sys, math, time
import subprocess
from utils import *
from SampleSettings import *
from collections import OrderedDict
from PostAnalyzer import *
from ScriptRunner import *
import ROOT


# All constants to be used
analysisname     = '$MYANALYSISNAME'
user             = '$MYUSERNAME'
input_base_path  = os.path.join('/pnfs/psi.ch/cms/trivcat/store/user', user)
result_base_path = os.path.join('/work', user)

# colors = [ROOT.kRed+4, ROOT.kRed+1, ROOT.kViolet, ROOT.kAzure-2, ROOT.kOrange, ROOT.kGreen-2]
samples = {
    'TT':                                    SampleSettings(name='TT', color=ROOT.kRed+1, linestyle=1, legendtext='t#bar{t}'),
    'LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0': SampleSettings(name='LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', color=ROOT.kRed+1, linestyle=2, legendtext='M_{LQ} = 1000 GeV, M_{DM} = 100 GeV')
}



def main():



    ScriptRunner = ScriptRunner(year='2017', analysisname=analysisname, input_base_path=input_base_path, result_base_path=result_base_path, selectionstage='Preselection', selectionname='InitialSetup', samples=samples)

    ScriptRunner.CalculateSelectionEfficiencies(num_and_denom=[('input', 'input'), ('cleaner', 'input')], backgrounds=['TT'], signals=['LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0'])




    systematics  = ['nominal', 'lumi', 'rate_tt']
    backgrounds  = ['TT']
    signalmass_identifier = 'MLQ'
    signals      = ['LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0']
    channels     = ['tach']
    histnames_in_out_per_category = {
        'cat1': ('metpt', 'MET'),
    }
    limithisttag = 'General'

    processes_per_systematic = {'lumi': 'all', 'rate_tt': 'TT'}
    pdf_per_systematic       = {'lumi': 'lnN', 'rate_tt': 'lnN'}
    value_per_systematic     = {'lumi': 1.025, 'rate_tt': 1.056}

    Analyzer = PostAnalyzer('2017', analysisname=analysisname, input_base_path=input_base_path, result_base_path=result_base_path, selectionstage='Preselection', selectionname='InitialSetup', systematics=systematics, backgrounds=backgrounds, signals=signals, signalmass_identifier=signalmass_identifier, channels=channels, histnames_in_out_per_category=histnames_in_out_per_category, limithisttag=limithisttag, processes_per_systematic=processes_per_systematic, pdf_per_systematic=pdf_per_systematic, value_per_systematic=value_per_systematic, crosssection_path=None)

    # Analyzer.ProduceCombineHistograms(signal_scaled_by=0.01)
    # Analyzer.CreateDatacards()
    # Analyzer.CombineChannels()
    # Analyzer.ExecuteCombineCombination()
    # Analyzer.PlotLimits(signal_scaled_by=0.01, draw_theory=False)















if __name__ == '__main__':
    main()
