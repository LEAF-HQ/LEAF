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
from multiprocessing import Pool

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
    def __init__(self, type, name, group=YearDependentContainer(), minipaths=YearDependentContainer(), nanopaths=YearDependentContainer(), tuplepaths=YearDependentContainer(), xsecs=YearDependentContainer(), xmlfiles=YearDependentContainer(), nevents=YearDependentContainer()):
        self.type = type
        self.name = name
        self.group = group
        self.minipaths = minipaths
        self.nanopaths = nanopaths
        self.tuplepaths = tuplepaths
        self.xsecs = xsecs
        self.xmlfiles = xmlfiles
        self.nevents = nevents

    def get_info(self, year):
        print '--> Info on sample \'%s\' for year %s:' % (self.name, str(year))
        print '  --> type: %s' % (str(self.type))
        print '  --> name: %s' % (str(self.name))
        print '  --> group: %s' % (str(self.group[year]))
        print '  --> minipath: %s' % (str(self.minipaths[year].path))
        print '  --> nanopath: %s' % (str(self.nanopaths[year].path))
        print '  --> tuplepath: %s' % (str(self.tuplepaths[year].path))
        print '  --> xsec: %s' % (str(self.xsecs[year]))
        print '  --> xmlfile: %s' % (str(self.xmlfiles[year]))
        print '  --> nevent: %s' % (str(self.nevents[year]))

    def get_var_for_year(self, varname, year):
        if varname is 'type' or varname is 'name':
            return getattr(self, varname)
        elif varname is 'minipaths' or varname is 'nanopaths' or varname is 'tuplepaths':
            return getattr(self, varname)[year].path
        else:
            return getattr(self, varname)[year]



    def get_filedict(self, sampleinfofolder, stage, year, check_missing=False):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')

        # first try to read it from the json
        filedict = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)
        if filedict is not False:
            if not check_missing:
                return filedict

        # if it wasn't found, call the function to find the list, update the json, and return the list then
        if stage is 'nano':
            filelist = self.nanopaths[year].get_file_list()
        elif stage is 'mini':
            filelist = self.minipaths[year].get_file_list()


        if filedict is not False:
            if len(filedict) == len(filelist):
                print green('  --> Sample \'%s\' has all files counted, continue.' % (self.name))
                return filedict
            else:
                missingfilelist = []
                for file in filelist:
                    if file not in filedict:
                        missingfilelist.append(file)
                filelist = missingfilelist
        filedict = self.count_events_in_files(filelist, stage=stage, chunksize=10)


        if not check_missing:
            self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=filedict)
        else:
            if self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year) is not False: # can't use filedict here, has been overwritten above.
                dict_from_json = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)
                for filename in filedict:
                    if filename in dict_from_json:
                        raise ValueError('Trying to insert counted file, but it exists already: %s' % (filename))
                    dict_from_json[filename] = filedict[filename]
                self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=dict_from_json)
            else:
                # raise ValueError('Asked for check_missing mode, but the json file does not exist (or the entry for this sample). Intended?')
                self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=filedict)

        # get from json to make sure it's always ordered in the same way
        filedict = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)

        if filedict is not False:
            return filedict
        else:
            raise ValueError('Unable to get filedict for sample %s.' % (self.name))



    def get_missing_tuples(self, sampleinfofolder, stage, year, tuplebasename, ntuples_expected, update_missing=True, update_all=False):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')
        if update_missing and update_all:
            raise AttributeError('Both update_missing and update_all are true. Can only choose one of them or neither, but not both.')

        # first try to read it from the json
        filelist_json = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        if filelist_json is not False:
            if not update_missing and not update_all:
                return filelist_json

        # if it wasn't found, call the function to find the list of all expected files and check how many there are. As many tuples are expected as well
        if stage is 'nano':
            # nfiles_exp = len(self.nanopaths[year].get_file_list())
            stagetag = 'NANOAOD'
        elif stage is 'mini':
            # ntuples_expected = len(self.minipaths[year].get_file_list())
            stagetag = 'MINIAOD'

        missingfilelist = []
        outfoldername = self.tuplepaths[year].director+self.tuplepaths[year].path
        # outfoldername = self.tuplepaths[year].path
        if filelist_json is not False and update_missing: # only check already listed files
            if len(filelist_json) == 0:
                print green('  --> Sample \'%s\' has all no missing tuples, continue.' % (self.name))
                missingfilelist = []
            else: # check only for files still in the list of missing files in the json
                expected_filelist = [os.path.join(outfoldername, '%s_%s_%s.root' % (tuplebasename, stagetag, str(i+1))) for i in filelist_json]
                files_and_events = self.count_events_in_files(expected_filelist, stage=stage, treename='AnalysisTree')

                #find missing entries
                for i in filelist_json:
                    expected_entry = os.path.join(outfoldername, '%s_%s_%s.root' % (tuplebasename, stagetag, str(i+1)))
                    if not expected_entry in files_and_events:
                        missingfilelist.append(expected_entry)

                # find entries with 0 events
                for file in files_and_events:
                    if not (files_and_events[file] > 0):
                        missingfilelist.append(file)
        else: # check for all files (again).
            missing_indices = findMissingFilesT3(filepath=outfoldername, filename_base='%s_%s' % (tuplebasename, stagetag), maxindex=ntuples_expected, generation_step='%s_%s' % (tuplebasename, stagetag))
            missingfilelist = [os.path.join(outfoldername, '%s_%s_%s.root' % (tuplebasename, stagetag, str(i+1))) for i in missing_indices]
            # expected_filelist = [os.path.join(outfoldername, '%s_%s_%s.root' % (tuplebasename, stagetag, str(i+1))) for i in range(nfiles_exp)]
            # files_and_events = self.count_events_in_files(expected_filelist, stage=stage)
            # missingfilelist = files_and_events.keys()

        # if we reach this point, the missing files JSON needs to be updated.

        #convert to indices
        missings = []
        for name in missingfilelist:
            missings.append(int(name.split('_')[-1][:-5]) - 1)
        self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=missings, basename='missingtuples')

        result = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        return result




    def get_filedict_from_json(self, sampleinfofolder, stage, year, basename='filelist'):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')
        jsonname = os.path.join(sampleinfofolder, '%s_%s_%s.json' % (basename, stage, year))
        dict_in_json = {}

        if not os.path.exists(jsonname):
            return False
        with open(jsonname, 'r') as j:
            dict_in_json = safe_load(j)

        if not self.name in dict_in_json.keys():
            return False
        return dict_in_json[self.name]


    def update_filedict_in_json(self, sampleinfofolder, stage, year, filedict, basename='filelist'):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')
        jsonname = os.path.join(sampleinfofolder, '%s_%s_%s.json' % (basename, stage, year))
        dict_in_json = {}
        if os.path.exists(jsonname):
            with open(jsonname, 'r') as j:
                dict_in_json = safe_load(j)

        # print dict_in_json
        dict_in_json[self.name] = filedict
        with open(jsonname, 'w') as j:
            json.dump(obj=dict_in_json, fp=j, indent=2, sort_keys=True)


    def count_events_in_files(self, filelist, stage, treename='Events', ncores=10, chunksize=5, maxtries=3):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')
        print green('  --> Going to count events in %i files' % (len(filelist)))


        commands = []
        for i, filename in enumerate(filelist):

            # get number of events
            command = 'Counter_NANOAOD %s %s' % (filename, treename)
            commands.append((command, filename))
        outputs = getoutput_commands_parallel(commands=commands, max_time=30, ncores=ncores)

        newdict = {}
        for o in outputs:
            try:
                nevt = int(o[0].split('\n')[0])
                filename = o[1]
                newdict[filename] = nevt
            except Exception as e:
                print yellow('  --> Caught exception \'%s\'. Sample \'%s\' is going to miss events.' % (e, self.name))
                # return False


        #################################


        # pool = Pool(processes=ncores)
        # # result = pool.map(countEventsInFileGrid, filelist, chunksize)
        # result = []
        # for x in tqdm(pool.imap(countEventsInFileGrid, filelist, chunksize), total=len(filelist), file=sys.stdout):
        #     result.append(x)
        # pool.terminate()
        # pool.close()
        #
        # # Output the result
        # newdict = {}
        # failed_files = []
        # for d in result:
        #     if d[d.keys()[0]] is None:
        #         failed_files.append(d.keys()[0])
        #     else:
        #         newdict.update(d)
        #
        # idx = 0
        # while len(failed_files) > 0 and idx < maxtries:
        #     failed_files_loop = []
        #
        #     pool = Pool(processes=ncores)
        #     # result = pool.map(countEventsInFileGrid, failed_files, chunksize)
        #     result = []
        #     for x in tqdm(pool.imap(countEventsInFileGrid, failed_files, 1), total=len(failed_files), file=sys.stdout):
        #         result.append(x)
        #     pool.terminate()
        #     pool.close()
        #
        #     for d in result:
        #         if d[d.keys()[0]] is None:
        #             failed_files_loop.append(d.keys()[0])
        #         else:
        #             newdict.update(d)
        #     failed_files = failed_files_loop
        #     idx += 1


        #################################


            # pbar = tqdm(range(len(failed_files)), desc="Files counted")
            # for idx in pbar:
            #     filename = failed_files[idx]
            #     nevt = countEventsInFileGrid(absolute_filename=filename)
            #     if nevt is None:
            #         failed_files_loop.append(filename)
            #     else:
            #         newdict[filename]=nevt
            # failed_files = failed_files_loop



        #################################



        # failed_files = []
        # newdict = {}
        # pbar = tqdm(range(len(filelist)), desc="Files counted")
        # for idx in pbar:
        #     filename = filelist[idx]
        #     nevt = countEventsInFileGrid(absolute_filename=filename)
        #     if nevt is None:
        #         failed_files.append(filename)
        #     else:
        #         newdict[filename]=nevt
        #
        # idx = 0
        # keep_going = True
        # while len(failed_files) > 0 and idx < maxtries:
        #     failed_files_loop = []
        #     pbar = tqdm(range(len(failed_files)), desc="Files counted")
        #     for idx in pbar:
        #         filename = failed_files[idx]
        #         nevt = countEventsInFileGrid(absolute_filename=filename)
        #         if nevt is None:
        #             failed_files_loop.append(filename)
        #         else:
        #             newdict[filename]=nevt
        #     failed_files = failed_files_loop


        print green('  --> Successfully counted events in %i files' % (len(newdict)))
        return newdict
