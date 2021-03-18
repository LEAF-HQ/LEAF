import os, sys
import xml.dom.minidom as minidom
import subprocess
import StringIO
import xml.sax
from copy import deepcopy

class XMLInfo:
    def __init__(self, xmlfilename):
        self.xmlfilename = xmlfilename
        command = 'xmllint --noent --dtdattr %s' % (xmlfilename)
        xmlstring = StringIO.StringIO(subprocess.check_output(command.split(' ')))
        sax_parser = xml.sax.make_parser()
        self.xmlparsed = minidom.parse(xmlstring,sax_parser)
        self.rootnode = self.xmlparsed.getElementsByTagName('Configuration')[0]
        self.configsettings = self.read_configuration_settings()
        self.submissionsettings = self.read_submission_settings()
        self.additionalvars = self.read_additional_variables()
        self.datasets = self.read_datasets()
        self.datasets_to_write = deepcopy(self.datasets) # deep copy of datasets. Modify this one.


    def get_XML_document(self):
        doc = minidom.Document()
        rootnode = doc.createElement("Configuration")

        self.write_configuration_settings(rootnode)
        self.write_submission_settings(doc, rootnode)
        self.write_datasets(doc, rootnode)
        self.write_additionalvars(doc, rootnode)
        return rootnode



    def read_configuration_settings(self):
        attributes_and_values = self.rootnode.attributes.items()
        return GroupedSettings(attributes_and_values)

    def read_submission_settings(self):
        attributes_and_values = self.rootnode.getElementsByTagName('SubmissionSettings')[0].attributes.items()
        return GroupedSettings(attributes_and_values)

    def read_additional_variables(self):
        attributes_and_values = []
        for var in self.rootnode.getElementsByTagName('AdditionalVariables')[0].getElementsByTagName('Variable'):
            tup = (var.attributes.items()[0][1], var.attributes.items()[1][1])
            attributes_and_values.append(tup)
        return GroupedSettings(attributes_and_values)

    def read_datasets(self):
        datasets = []
        for var in self.rootnode.getElementsByTagName('InputDatasets')[0].getElementsByTagName('Dataset'):
            attributes_and_values = var.attributes.items()
            infiles = []
            for child in var.getElementsByTagName('InputFile'):
                infiles.append(child.attributes.items()[0][1])
            this_dataset = InputDataset(attributes_and_values, infiles)
            datasets.append(this_dataset)
        return datasets




    def write_configuration_settings(self, rootnode):
        for attr in self.configsettings.__dict__:
            rootnode.setAttribute(attr, self.configsettings.__dict__[attr])

    def write_submission_settings(self, doc, rootnode):
        tempsettings = doc.createElement('SubmissionSettings')
        rootnode.appendChild(tempsettings)
        for attr in self.submissionsettings.__dict__:
            tempsettings.setAttribute(attr, self.submissionsettings.__dict__[attr])

    def write_datasets(self, doc, rootnode):
        tempdatasets = doc.createElement('InputDatasets')
        rootnode.appendChild(tempdatasets)
        for dataset in self.datasets_to_write:
            tempdataset = doc.createElement('Dataset')
            tempdatasets.appendChild(tempdataset)
            for attr in dataset.settings.__dict__:
                tempdataset.setAttribute(attr, dataset.settings.__dict__[attr])
            for infile in dataset.infiles:
                tempinfile = doc.createElement('InputFile')
                tempdataset.appendChild(tempinfile)
                tempinfile.setAttribute('FileName', infile)

    def write_additionalvars(self, doc, rootnode):
        tempsettings = doc.createElement('AdditionalVariables')
        rootnode.appendChild(tempsettings)
        for varname in self.additionalvars.__dict__:
            tempvar = doc.createElement('Variable')
            tempsettings.appendChild(tempvar)
            tempvar.setAttribute('Name', varname)
            tempvar.setAttribute('Value', self.additionalvars.__dict__[varname])



class GroupedSettings:
    def __init__(self, attributes_and_values):
        for tup in attributes_and_values:
            setattr(self, tup[0], tup[1])

class InputDataset:
    def __init__(self, attributes_and_values, infiles):
        self.settings = GroupedSettings(attributes_and_values)
        self.infiles  = infiles




















#
