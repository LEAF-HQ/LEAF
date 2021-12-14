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
result_base_path = '$MYLEAFPATH/..'

# colors = [ROOT.kRed+4, ROOT.kRed+1, ROOT.kViolet, ROOT.kAzure-2, ROOT.kOrange, ROOT.kGreen-2]
samples = {
    'WJets':                                 SampleSettings(name='WJets', color=ROOT.kSpring-6, linestyle=1, legendtext='W+jets'),
    'LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0': SampleSettings(name='LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', color=ROOT.kRed+4, linestyle=2, legendtext='M_{LQ} = 1000 GeV, M_{DM} = 100 GeV'),
    'LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0': SampleSettings(name='LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', color=ROOT.kRed+1, linestyle=2, legendtext='M_{LQ} = 1000 GeV, M_{DM} = 100 GeV'),
}



def main():


    # Class for running all sorts of scripts within given folder structure
    # ====================================================================


    ScriptRunnerInitial = ScriptRunner(year='2017', analysisname=analysisname, input_base_path=input_base_path, result_base_path=result_base_path, selectionstage='Preselection', selectionname='InitialSetup', samples=samples)

    ScriptRunnerInitial.CalculateSelectionEfficiencies(num_and_denom=[('input', 'input'), ('cleaner', 'input'), ('njets', 'input')], backgrounds=['WJets'], signals=['LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0'])



    # Class for running Combine and computing upper limits and other Combine outputs
    # ==============================================================================


    # Below, if considering more than one channel/cat, name them as a list of strings here, and with strings as dictionary keys, instead of a list with one None element (one None key in the dictionary). Expects histograms in file to be in the folder 'channel_cat_syst_<limithisttag>'
    # note that the nominal result must always be called "nominal", it's hardcoded in several places

    # example samples and settings, can vary strongly between analyses
    systematics  = ['nominal', 'lumi', 'rate_wjets']
    backgrounds  = ['WJets']
    signalmass_identifier = 'MLQ'
    signals      = ['LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0', 'LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0']
    channels     = [None]
    histnames_in_out_per_category = {
        None: ('metpt', 'MET'),
    }
    limithisttag = 'General'

    # example systematics, more to be added
    processes_per_systematic = {'lumi': 'all', 'rate_wjets': 'WJets'}
    pdf_per_systematic       = {'lumi': 'lnN', 'rate_wjets': 'lnN'}
    value_per_systematic     = {'lumi': 1.025, 'rate_wjets': 1.25}

    Analyzer = PostAnalyzer('2017', analysisname=analysisname, input_base_path=input_base_path, result_base_path=result_base_path, selectionstage='Preselection', selectionname='InitialSetup', systematics=systematics, backgrounds=backgrounds, signals=signals, signalmass_identifier=signalmass_identifier, channels=channels, histnames_in_out_per_category=histnames_in_out_per_category, limithisttag=limithisttag, processes_per_systematic=processes_per_systematic, pdf_per_systematic=pdf_per_systematic, value_per_systematic=value_per_systematic, crosssection_path=None)

    Analyzer.ProduceCombineHistograms(signal_scaled_by=0.01, use_fake_data=True)
    Analyzer.CreateDatacards()
    Analyzer.CombineChannels()
    Analyzer.ExecuteCombineCombination()
    Analyzer.PlotLimits(signal_scaled_by=0.01, draw_theory=False)















if __name__ == '__main__':
    main()
