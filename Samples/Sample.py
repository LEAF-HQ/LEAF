#! /usr/bin/env python

import os, json
from yaml import safe_load
from collections import OrderedDict
from utils import *
from functions import *

class YearDependentContainer():
    def __init__(self, vals={}):
        self.__dict = {
            'EOY16': None,
            'EOY17': None,
            'EOY18': None,
            'UL16preVFP': None,
            'UL16postVFP': None,
            'UL17': None,
            'UL18': None,
        }
        if any(not x in self.__dict for x in vals.keys()):
            raise AttributeError('Invalid key for year-dependent object. Given keys: '+(', '.join(vals.keys()))+'. Supported keys: '+(', '.join(self.__dict.keys())))
        self.__dict.update(vals)

        for key, val in self.__dict.items():
            if val is None:
                del self.__dict[key]

    def __str__(self):
        print('')
        prettydict(self.__dict, indent=14)
        return ''

    def has_year(self, year):
        if year in self.__dict.keys():
            if self.__dict[year] is not None:
                return True
        return False

    def __getitem__(self, year):
        if self.has_year(year):
            return self.__dict[year]
        else:
            return None

    def __setitem__(self, year, value):
        if not self.has_year(year):
            self.__dict = {year: value}
        else:
            raise AttributeError('Year-dependent dict already has an entry for year %s' % (str(year)))


class Sample:
    def __init__(self, type, name, group=YearDependentContainer(), minipaths=YearDependentContainer(), nanopaths=YearDependentContainer(), tuplepaths=YearDependentContainer(), xsecs=YearDependentContainer(), xmlfiles=YearDependentContainer(), nevents_das=YearDependentContainer(), nevents_generated=YearDependentContainer(), nevents_weighted=YearDependentContainer(), contents=YearDependentContainer()):
        # contents should be a list of names of the branch(es) of "RecoEvent" that is supposed to be stored here, or "standard".
        # Ex. contents = ['standard']
        # or
        # contents = ['pfcands']
        # or
        # contents = ['standard', 'pfcands'] if both a standard and an additional collection "pfcands" is stored (which really should not happen)
        # or
        # contents = ['pfcands', 'triggerobjects']
        self.type = type
        self.name = name
        self.group = group
        self.minipaths = minipaths
        self.nanopaths = nanopaths
        self.tuplepaths = tuplepaths
        self.xsecs = xsecs
        self.xmlfiles = xmlfiles
        self.nevents_das = nevents_das
        self.nevents_generated = nevents_generated
        self.nevents_weighted = nevents_weighted
        self.contents = contents
        # self.__dict = OrderedDict()
        # self.__dict['name'] = self.name
        # self.__dict['type'] = self.type
        # self.__dict['xsec'] = self.xsecs
        # self.__dict['nevents_das'] = self.nevents_das
        # self.__dict['nevents_generated'] = self.nevents_generated
        # self.__dict['nevents_weighted'] = self.nevents_weighted
        # self.__dict['group'] = self.group
        # self.__dict['minipath'] = self.minipaths
        # self.__dict['nanopath'] = self.nanopaths
        # self.__dict['tuplepath'] = self.tuplepaths
        # self.__dict['xmlfile'] = self.xmlfiles
        # self.__dict['content'] = self.contents


    def __str__(self):
        print('')
        prettydict(self.__dict__, indent=10)
        return ''

    def get_var_for_year(self, varname, year):
        if varname == 'type' or varname == 'name':
            return getattr(self, varname)
        else:
            return getattr(self, varname)[year]



    def get_filedict(self, sampleinfofolder, stage, year, check_missing=False):
        self.VerifyStage(stage)

        # first try to read it from the json
        filedict = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)

        if filedict and not check_missing:
            return filedict

        # if it wasn't found, call the function to find the list, update the json, and return the list then
        filelist = self.get_var_for_year(stage+'paths',year).get_file_list()

        if filedict:
            filelist = list(set(filelist) - set(filedict.keys()))
            if len(filelist) == 0:
                print(green('  --> Sample \'%s\' has all files counted, continue.' % (self.name)))
                return filedict
        missingfiledict = self.count_events_in_files(filelist, stage=stage, chunksize=10)

        if filedict and check_missing:
            if len(set(missingfiledict.keys()).intersection(set(filedict.keys())))!=0:
                raise ValueError('Trying to insert counted files, but they exist already: %s' % (missingfiledict.keys()))

        filedict.update(missingfiledict)
        self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=filedict)

        # get from json to make sure it's always ordered in the same way
        filedict = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year)

        if not filedict:
            raise ValueError('Unable to get filedict for sample %s.' % (self.name))

        return filedict



    def get_missing_tuples(self, sampleinfofolder, stage, year, tuplebasename, ntuples_expected, update_missing=True, nevents_expected_per_ntuple={}):
        self.VerifyStage(stage)

        stagetag = stage.upper()+'AOD'
        outfoldername = self.tuplepaths[year].get_path()
        filename_base = os.path.join(outfoldername, '%s_%s' % (tuplebasename, stagetag))

        # first try to read it from the json, it's a list despite the function name
        filelist_json = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        if filelist_json:
            if not update_missing:
                return filelist_json
            else:
                if len(filelist_json) == 0:
                    print(green('  --> Sample \'%s\' has no missing tuples, continue.' % (self.name)))
                    return filelist_json
                else: # check only for files still in the list of missing files in the json
                    expected_filelist = [filename_base+'_'+str(i+1)+'.root' for i in filelist_json]
                    files_and_events = self.count_events_in_files(expected_filelist, stage=stage, treename='AnalysisTree')
                    # find missing entries
                    missingfilelist = list(filter(lambda x: x not in files_and_events ,expected_filelist))
                    # find entries with 0 events
                    empty_files = dict(filter(lambda elem: elem[1] == 0,files_and_events.items())).keys()
                    # if given, check if counted number == expected number
                    # incomplete_files = dict(filter(lambda elem: elem[1] != nevents))
                    incomplete_files = []
                    for fullname in files_and_events:
                        if fullname in nevents_expected_per_ntuple:
                            if nevents_expected_per_ntuple[fullname] != files_and_events[fullname]:
                                incomplete_files.append(fullname)
                        elif nevents_expected_per_ntuple:
                            raise ValueError('Found file in target folder that was not even in list of expected files. Strange...')
                    missingfilelist = list(set(missingfilelist + empty_files + incomplete_files))
        else:
            # if it wasn't found, call the function to find the list of all expected files and check how many there are. As many tuples are expected as well
            missing_indices = findMissingRootFiles(filename_base=filename_base, maxindex=ntuples_expected, nevents_expected_per_ntuple=nevents_expected_per_ntuple)
            missingfilelist = [filename_base+'_'+str(i+1)+'.root' for i in missing_indices]

        #convert to indices
        missings = [int(name.split('_')[-1][:-5]) - 1 for name in missingfilelist]
        self.update_filedict_in_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, filedict=missings, basename='missingtuples')
        filelist_json = self.get_filedict_from_json(sampleinfofolder=sampleinfofolder, stage=stage, year=year, basename='missingtuples')
        return filelist_json


    def get_filedict_from_json(self, sampleinfofolder, stage, year, basename='filelist'):
        self.VerifyStage(stage)
        jsonname = os.path.join(sampleinfofolder, '%s_%s_%s.json' % (basename, stage, year))
        if os.path.exists(jsonname):
            with open(jsonname, 'r') as j:
                dict_in_json = safe_load(j)
            if self.name in dict_in_json.keys():
                return dict_in_json[self.name]
        return {}


    def update_filedict_in_json(self, sampleinfofolder, stage, year, filedict, basename='filelist'):
        self.VerifyStage(stage)
        jsonname = os.path.join(sampleinfofolder, '%s_%s_%s.json' % (basename, stage, year))
        dict_in_json = {}
        if os.path.exists(jsonname):
            with open(jsonname, 'r') as j:
                dict_in_json = safe_load(j)

        dict_in_json[self.name] = filedict
        with open(jsonname, 'w') as j:
            json.dump(obj=dict_in_json, fp=j, indent=2, sort_keys=True)


    def count_events_in_files(self, filelist, stage, treename='Events', ncores=10, chunksize=5, maxtries=3):
        self.VerifyStage(stage)
        print(green('  --> Going to count events in %i files' % (len(filelist))))

        commands = [('Counter_Entries %s %s' % (filename, treename), filename) for filename in filelist]
        outputs = getoutput_commands_parallel(commands=commands, max_time=30, ncores=ncores)

        if not outputs:
            print(yellow('Did you set the Grid certificate?'))
            print(commands)

        newdict = {}
        for i, o in enumerate(outputs):
            try:
                nevt = int(o[0].split('\n')[0])
                filename = o[1]
                newdict[filename] = nevt
            except Exception as e:
                print(yellow('  --> Caught exception \'%s\'. Sample \'%s\' is therefore currently missing events.' % (e, self.name)))

        print(green('  --> Successfully counted events in %i files' % (len(newdict))))
        return newdict

    def VerifyStage(self,stage):
        if stage is not 'nano' and stage is not 'mini':
            raise AttributeError('Invalid stage defined. Must be \'mini\' or \'nano\'.')


class SampleContainer():
    def __init__(self):
        self.__dict = OrderedDict()

    def has_sample(self, sample):
        return sample in self.__dict

    def get_sample(self, sample):
        if not self.has_sample(sample):
            raise AttributeError('Invalid sample for SampleContainer class.')
        return self.__dict[sample]

    def add_samples(self, samples_dict):
        if any(x in self.__dict for x in samples_dict.keys()):
            raise AttributeError('SampleContainer class already has the entry provided. Please check.')
        self.__dict.update(samples_dict)

    def __str__(self):
        print(blue('--> SampleContainer info:'))
        prettydict(self.__dict)
        return blue('--> SampleContainer end.')

    def keys(self):
        return self.__dict.keys()

    def items(self):
        return self.__dict.items()
