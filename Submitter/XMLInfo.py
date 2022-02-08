import os, sys, parse
import xml.dom.minidom as minidom
import subprocess
import StringIO
import xml.sax
from copy import deepcopy

class XMLInfo:
    def __init__(self, xmlfilename):
        self.xmlfilename = xmlfilename
        with open(self.xmlfilename) as f_:
            self.config_info = f_.readlines()[0:2]
            self.config_name = parse.compile('<!DOCTYPE {} "" "{ConfigName}"[{}').parse(self.config_info[1])['ConfigName']
            self.config_info = ''.join(self.config_info)+']>\n'
        command = 'xmllint --noent --dtdattr %s' % (xmlfilename)
        xmlstring = StringIO.StringIO(subprocess.check_output(command.split(' ')))
        sax_parser = xml.sax.make_parser()
        self.xmlparsed = minidom.parse(xmlstring,sax_parser)
        self.rootnode = self.xmlparsed.getElementsByTagName(self.config_name.strip(".dtd"))[0]
        self.configsettings = self.read_configuration_settings()
        self.submissionsettings = self.read_submission_settings()
        self.additionalvars = self.read_additional_variables()
        self.additionalinputs = self.read_additional_inputs()
        self.datasets = self.read_datasets(parentnode=self.rootnode.getElementsByTagName('InputDatasets')[0])
        self.datasets_to_write = deepcopy(self.datasets) # deep copy of datasets. Modify this one.


    def get_XML_document(self):
        doc = minidom.Document()
        rootnode = doc.createElement(self.config_name.strip(".dtd"))

        self.write_configuration_settings(rootnode)
        self.write_submission_settings(doc, rootnode)
        self.write_datasets(doc, rootnode)
        self.write_additional_inputs(doc, rootnode)
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

    def read_datasets(self, parentnode, datasetnodename='Dataset'):
        datasets = []
        for var in parentnode.getElementsByTagName(datasetnodename):
            attributes_and_values = var.attributes.items()
            infiles = []
            for child in var.getElementsByTagName('InputFile'):
                infiles.append(child.attributes.items()[0][1])
            this_dataset = InputDataset(attributes_and_values, infiles)
            datasets.append(this_dataset)
        return datasets

    def read_additional_inputs(self):
        additional_inputs = []
        if len(self.rootnode.getElementsByTagName('AdditionalInputs')) == 0:
            return additional_inputs
        for addinputnode in self.rootnode.getElementsByTagName('AdditionalInputs')[0].getElementsByTagName('AdditionalInput'):
            datasets = self.read_datasets(parentnode=addinputnode, datasetnodename='AdditionalDataset')
            collections = []
            for coll in addinputnode.getElementsByTagName('Collection'):
                collections.append(GroupedSettings(coll.attributes.items()))

            this_addinput = AdditionalInput(datasets=datasets, collections=collections)
            additional_inputs.append(this_addinput)
        return additional_inputs





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

    def write_additional_inputs(self, doc, rootnode):
        if len(self.additionalinputs) == 0:
            return
        addinputs = doc.createElement('AdditionalInputs')
        rootnode.appendChild(addinputs)
        for addinput in self.additionalinputs:

            # make sure to take only additional inputs with the same name as the main input
            necessary_additional_datasets = [ds for ds in addinput.datasets if ds.settings.Name in [dstowrite.settings.Name for dstowrite in self.datasets_to_write]]

            # also make sure that the year is the same between all (main, additional) datasets with the same name
            necessary_additional_datasets_same_year = [ads for ads in necessary_additional_datasets if ads.settings.Year in [ds.settings.Year for ds in self.datasets_to_write if ads.settings.Name == ds.settings.Name]]
            if not len(necessary_additional_datasets_same_year) == len(self.datasets_to_write):
                if len(necessary_additional_datasets_same_year) == 0:
                    continue
                else:
                    raise ValueError('Datasets in AdditionalInput are not equally many as the datasets_to_write for this job. Please check.')

            tempaddinput = doc.createElement('AdditionalInput')
            addinputs.appendChild(tempaddinput)
            for dataset in necessary_additional_datasets_same_year:
                tempdataset = doc.createElement('AdditionalDataset')
                tempaddinput.appendChild(tempdataset)
                for attr in dataset.settings.__dict__:
                    tempdataset.setAttribute(attr, dataset.settings.__dict__[attr])
                for infile in dataset.infiles:
                    tempinfile = doc.createElement('InputFile')
                    tempdataset.appendChild(tempinfile)
                    tempinfile.setAttribute('FileName', infile)
            for collection in [c for c in addinput.collections]:
                tempcollection = doc.createElement('Collection')
                tempaddinput.appendChild(tempcollection)
                for attr in collection.__dict__:
                    tempcollection.setAttribute(attr, collection.__dict__[attr])

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

    def hasValue(self, name):
        return hasattr(self, name)

    def getValue(self, name):
        return getattr(self, name)

    def setValue(self, name, value):
        setattr(self, name, value)

class InputDataset:
    def __init__(self, attributes_and_values, infiles):
        self.settings = GroupedSettings(attributes_and_values)
        self.infiles  = infiles


class AdditionalInput:
    def __init__(self, datasets, collections):
        self.datasets = datasets
        self.collections  = collections




















#
