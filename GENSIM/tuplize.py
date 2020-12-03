#! /usr/bin/env python

import os, sys, math
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
from utils import *
from functions import *
from constants import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from TuplizeRunner import *
from samples.Storage import *
from samples.Sample import *
from samples.samples import *


username = 'areimers'
workarea = '/work/%s' % (username)
basefolder = join(workarea, 'LQDM')
gensimfolder = join(basefolder, 'GENSIM')

config_per_year = {
    '2017': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_12'
    }
}



# samplenames = ['TTToSemiLeptonic', 'TTTo2L2Nu', 'TTToHadronic']
samplenames = ['TTToSemiLeptonic']
# samplenames = ['TTTo2L2Nu', 'TTToHadronic']


submit = False

for samplename in samplenames:
    s = samples[samplename]
    Tuplizer = TuplizeRunner(sample=s, year='2017', config=config_per_year, workarea=workarea, basefolder=basefolder, gensimfolder=gensimfolder, submit=submit)
    Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00), nevt_per_job=200000, mode='resubmit')
