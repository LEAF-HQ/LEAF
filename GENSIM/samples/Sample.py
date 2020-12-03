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

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

# from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR

class YearDependentContainer():
    def __init__(self, vals={}):
        self.dict = {
            '2016': None,
            '2017': None,
            '2018': None
        }
        for key in vals.keys():
            if key in self.dict.keys():
                self.dict[key] = vals[key]
            else:
                raise AttributeError('Invalid key %s for year-dependent object.' % str(key))

    def __getitem__(self, year):
        if self.has_year(year):
            return self.dict[year]
        else:
            return None

    def has_year(self, year):
        if year in self.dict.keys():
            if self.dict[year] is not None:
                return True
        return False

    def __setitem__(self, year, value):
        if not self.has_year(year):
            self.dict = {year: value}
        else:
            raise AttributeError('Year-dependent dict already has an entry for year %s' % (str(year)))


class Sample:
    def __init__(self, type, name, nanopaths=YearDependentContainer(), tuplepaths=YearDependentContainer(), xsecs=YearDependentContainer(), xmlfiles=YearDependentContainer(), nevents=YearDependentContainer()):
        self.type = type
        self.name = name
        self.nanopaths = nanopaths
        self.tuplepaths = tuplepaths
        self.xsecs = xsecs
        self.xmlfiles = xmlfiles
        self.nevents = nevents

    def get_info(self, year):
        print '--> Info on sample \'%s\' for year %s:' % (self.name, str(year))
        print '  --> type: %s' % (str(self.type))
        print '  --> name: %s' % (str(self.name))
        print '  --> nanopath: %s' % (str(self.nanopaths[year].path))
        print '  --> tuplepath: %s' % (str(self.tuplepaths[year].path))
        print '  --> xsec: %s' % (str(self.xsecs[year]))
        print '  --> xmlfile: %s' % (str(self.xmlfiles[year]))
        print '  --> nevent: %s' % (str(self.nevents[year]))

    def get_var_for_year(self, varname, year):
        if varname is 'type' or varname is 'name':
            return getattr(self, varname)
        elif varname is 'nanopaths' or varname is 'tuplepaths':
            return getattr(self, varname)[year].path
        else:
            return getattr(self, varname)[year]
