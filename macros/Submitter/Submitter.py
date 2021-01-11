import os, sys, math
from XMLInfo import *
from utils import *
from shutil import copy
from copy import deepcopy


class Submitter:
    def __init__(self, xmlfilename):
        self.xmlinfo = XMLInfo(xmlfilename)

        path_parts_local = [item for item in self.xmlinfo.xmlfilename.split('/')[:-1]]
        self.configdir = os.path.join('/', *path_parts_local)

        path_parts_local.append('workdir_%s' % (self.xmlinfo.xmlfilename.split('/')[-1][:-4]))
        self.workdir_local = os.path.join('/', *path_parts_local)

        path_parts_remote = [item for item in self.xmlinfo.configsettings.OutputDirectory.split('/')]
        path_parts_remote.append('workdir_%s' % (self.xmlinfo.xmlfilename.split('/')[-1][:-4]))
        self.workdir_remote = os.path.join('/', *path_parts_remote)



    def Divide(self):
        print green('--> Diving and preparing job')

        # First create local and remote (potentially T3) workdir. Inside, create folders for each sample to store the small XML and root files
        self.create_local_workdir()
        self.create_remote_workdir()
        self.divide_xml_files()

























    # smaller functions to keep main part clean


    def create_local_workdir(self):
        """ Create workdir + 1 subdir per sample for Submitter in the local config/ directory on the same level as the XML file """

        ensureDirectory(self.workdir_local)
        for dataset in self.xmlinfo.datasets:
            samplename = dataset.settings.Name
            ensureDirectory(os.path.join(self.workdir_local, samplename))

            # copy .dtd file
            copy(os.path.join(self.configdir, 'Configuration.dtd'), os.path.join(self.workdir_local, samplename))
        print green('  --> Created local workdir \'%s\'' % (self.workdir_local))


    def create_remote_workdir(self):
        """ Create workdir + 1 subdir per sample for Submitter in the remote target directory """

        ensureDirectory(self.workdir_remote)
        for dataset in self.xmlinfo.datasets:
            samplename = dataset.settings.Name
            ensureDirectory(os.path.join(self.workdir_remote, samplename))
        print green('  --> Created remote workdir \'%s\'' % (self.workdir_remote))

    def divide_xml_files(self):
        """ From the main XML file, create a number of smaller ones, one per job to be submitted and divided by sample. """

        # check how to split jobs
        is_filesplit  = False
        if int(self.xmlinfo.submissionsettings.FilesPerJob) > 0: is_filesplit = True
        is_eventsplit = False
        if int(self.xmlinfo.submissionsettings.EventsPerJob) > 0: is_eventsplit = True

        if (not is_filesplit and not is_eventsplit) or (is_filesplit and is_eventsplit):
            raise ValueError(red('In the XML file, either both or neither of "EventsPerJob" and "FilesPerJob" is >0. This is not supported, please choose one of the two options to split jobs.'))

        # handle filesplit
        if is_filesplit:
            datasets = self.xmlinfo.datasets
            for dataset in datasets:
                nfiles = len(dataset.infiles)
                nfiles_per_job = int(self.xmlinfo.submissionsettings.FilesPerJob)
                njobs = int(math.ceil(nfiles/float(nfiles_per_job)))
                for i in range(njobs):
                    self.write_single_xml(datasetname=dataset.settings.Name, index=i+1, nfiles_per_job=nfiles_per_job)

        # handle eventsplit
        else:
            datasets = self.xmlinfo.datasets
            for dataset in datasets:
                nevents = -1.
                #now read number of events per tree. Make it a separate function in a different file such that it can also be used for hadd'ing







    def write_single_xml(self, datasetname, index, nfiles_per_job=-1, nevents_skip=-1, nevents_max=0):

        if nfiles_per_job <= 0 and (nevents_skip < 0 and nevents_max == 0):
            raise ValueError(red('It seems like the new XML files should be written neither in filesplit nor eventsplit mode. Exit.'))
        if nfiles_per_job > 0 and (nevents_skip >= 0 or nevents_max != 0):
            raise ValueError(red('It seems like the new XML files should be written both in filesplit and eventsplit mode. Exit.'))


        # print green('  --> Writing XML file for job no %i of dataset %s' % (index, datasetname))
        outfilename = os.path.join(self.workdir_local, datasetname, '%s_%i.xml' % (datasetname, index))
        newxml = deepcopy(self.xmlinfo)

        # throw away all other datasets but the one we specified as a parameter here
        datasets_new = []
        for dataset in newxml.datasets:
            if dataset.settings.Name == datasetname:
                newxml.datasets = [dataset]
                break


        # filesplit mode
        if nfiles_per_job > 0:

            # remove most infiles from the one dataset selected above: keep only those we want in this small xml file
            fileindex_start = (index-1) * nfiles_per_job
            fileindex_stop  = fileindex_start + nfiles_per_job
            newxml.datasets[0].infiles = newxml.datasets[0].infiles[fileindex_start:fileindex_stop]

        # eventsplit mode
        else:

            # only need to specify nevents_max and _skip in the xml file
            newxml.configsettings.NEventsSkip = nevents_skip
            newxml.configsettings.NEventsMax  = nevents_max




        outputlines = newxml.get_XML_document().toprettyxml()
        print outputlines




















#
