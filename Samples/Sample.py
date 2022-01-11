#! /usr/bin/env python

import os
from utils import *
from functions import *
import json
from yaml import safe_load

class YearDependentContainer():
    def __init__(self, vals={}):
        self.__dict = {
            '2016': None,
            '2017': None,
            '2018': None
        }
        for key in vals.keys():
            if key in self.__dict.keys():
                self.__dict[key] = vals[key]
            else:
                raise AttributeError('Invalid key %s for year-dependent object.' % str(key))

    def __getitem__(self, year):
        if self.has_year(year):
            return self.__dict[year]
        else:
            return None

    def has_year(self, year):
        if year in self.__dict.keys():
            if self.__dict[year] is not None:
                return True
        return False

    def __setitem__(self, year, value):
        if not self.has_year(year):
            self.__dict = {year: value}
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
        self.VerifyStage(stage)

        # first try to read it from the json
        filedict = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)
        if filedict is not False:
            if not check_missing:
                return filedict

        # if it wasn't found, call the function to find the list, update the json, and return the list then
        filelist = self.get_var_for_year(stage+"paths",year).get_file_list()


        if filedict is not False:
            filelist = list(set(filelist) - set(filedict.keys()))
            if len(filelist) == 0:
                print green('  --> Sample \'%s\' has all files counted, continue.' % (self.name))
                return filedict
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
        self.VerifyStage(stage)
        if update_missing and update_all:
            raise AttributeError('Both update_missing and update_all are true. Can only choose one of them or neither, but not both.')

        # first try to read it from the json
        filelist_json = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        if filelist_json is not False:
            if not update_missing and not update_all:
                return filelist_json

        # if it wasn't found, call the function to find the list of all expected files and check how many there are. As many tuples are expected as well
        if stage is 'nano':
            stagetag = 'NANOAOD'
        elif stage is 'mini':
            stagetag = 'MINIAOD'

        missingfilelist = []
        outfoldername = self.tuplepaths[year].director+self.tuplepaths[year].path
        if filelist_json is not False and update_missing: # only check already listed files
            if len(filelist_json) == 0:
                print green('  --> Sample \'%s\' has all no missing tuples, continue.' % (self.name))
                missingfilelist = []
            else: # check only for files still in the list of missing files in the json
                expected_filelist = [os.path.join(outfoldername, '%s_%s_%s.root' % (tuplebasename, stagetag, str(i+1))) for i in filelist_json]
                files_and_events = self.count_events_in_files(expected_filelist, stage=stage, treename='AnalysisTree')

                # find missing entries
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

        # if we reach this point, the missing files JSON needs to be updated.

        #convert to indices
        missings = []
        for name in missingfilelist:
            missings.append(int(name.split('_')[-1][:-5]) - 1)
        self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=missings, basename='missingtuples')

        result = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        return result




    def get_filedict_from_json(self, sampleinfofolder, stage, year, basename='filelist'):
        self.VerifyStage(stage)
        jsonname = os.path.join(sampleinfofolder, '%s_%s_%s.json' % (basename, stage, year))
        if os.path.exists(jsonname):
            with open(jsonname, 'r') as j:
                dict_in_json = safe_load(j)
            if self.name in dict_in_json.keys():
                return dict_in_json[self.name]
        return False


    def update_filedict_in_json(self, sampleinfofolder, stage, year, filedict, basename='filelist'):
        self.VerifyStage(stage)
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
        self.VerifyStage(stage)
        print green('  --> Going to count events in %i files' % (len(filelist)))

        commands = [('Counter_NANOAOD %s %s' % (filename, treename), filename) for filename in filelist]
        outputs = getoutput_commands_parallel(commands=commands, max_time=30, ncores=ncores)

        newdict = {}
        for o in outputs:
            try:
                nevt = int(o[0].split('\n')[0])
                filename = o[1]
                newdict[filename] = nevt
            except Exception as e:
                print yellow('  --> Caught exception \'%s\'. Sample \'%s\' is therefore currently missing events.' % (e, self.name))
                # return False


        print green('  --> Successfully counted events in %i files' % (len(newdict)))
        return newdict

    def VerifyStage(self,stage):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')
