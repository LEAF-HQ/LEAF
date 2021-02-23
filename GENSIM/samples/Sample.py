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
import json
from yaml import safe_load

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

    def get_filedict_nano(self, sampleinfofolder, year, force_update=False):

        # first try to read it from the json
        filedict = self.get_filedict_nano_from_json(sampleinfofolder=sampleinfofolder, year=year)
        if filedict is not False:
            if not force_update:
                return filedict
            else:
                pass

        # if it wasn't found, call the function to find the list, update the json, and return the list then
        filelist = self.nanopaths[year].get_file_list()
        filedict = self.count_events_in_files(filelist)
        if filedict is False:
            return False
        self.update_filedict_nano_in_json(sampleinfofolder=sampleinfofolder, year=year, filedict=filedict)

        # get from json to make sure it's always ordered in the same way
        filedict = self.get_filedict_nano_from_json(sampleinfofolder=sampleinfofolder, year=year)
        if filedict is not False:
            return filedict
        else:
            raise ValueError('Unable to get filedict for sample %s.' % (self.name))

    def get_filedict_nano_from_json(self, sampleinfofolder, year):
        jsonname = os.path.join(sampleinfofolder, 'filelist_%s.json' % (year))

        dict_in_json = {}

        if not os.path.exists(jsonname):
            return False
        with open(jsonname, 'r') as j:
            dict_in_json = safe_load(j)

        if not self.name in dict_in_json.keys():
            return False
        return dict_in_json[self.name]


    def update_filedict_nano_in_json(self, sampleinfofolder, year, filedict):

        jsonname = os.path.join(sampleinfofolder, 'filelist_%s.json' % (year))
        dict_in_json = {}
        if os.path.exists(jsonname):
            with open(jsonname, 'r') as j:
                dict_in_json = safe_load(j)

        # print dict_in_json
        dict_in_json[self.name] = filedict
        with open(jsonname, 'w') as j:
            json.dump(obj=dict_in_json, fp=j, indent=2, sort_keys=True)


    def count_events_in_files(self, filelist):
        print green('  --> Going to count events in %i files' % (len(filelist)))
        commands = []
        for i, filename in enumerate(filelist):

            # get number of events
            command = 'Counter_NANOAOD %s' % (filename)
            commands.append((command, filename))
        outputs = getoutput_commands_parallel(commands=commands, max_time=30, ncores=10)

        newdict = {}
        for o in outputs:
            try:
                nevt = int(o[0].split('\n')[0])
                filename = o[1]
                newdict[filename] = nevt
            except Exception as e:
                print yellow('  --> Caught exception \'%s\'. Skip sample \'%s\'.' % (e, self.name))
                return False

        print green('  --> Successfully counted events in %i files' % (len(newdict)))
        return newdict
