import os, shutil, parse
from XMLInfo import *
from utils import *


class CreateConfigFilesBase:
    def __init__(self, xmlfilename, xmlfilepath, years, AllSamples):
        self.years       = years
        self.xmlfilepath = xmlfilepath
        self.xmlfilename = os.path.join(self.xmlfilepath,xmlfilename.split('/')[-1])
        outdir = os.path.join(self.xmlfilepath,"workdir_"+self.xmlfilename.split('/')[-1].strip("Config.xml"))
        os.system('mkdir -p '+outdir)
        self.outfilename = os.path.join(outdir, self.xmlfilename.split('/')[-1])
        with open(self.xmlfilename) as f_:
            ConfigName = parse.compile('<!DOCTYPE {} "" "{ConfigName}"[{}').parse(f_.readlines()[1])['ConfigName']
        shutil.copy(os.path.join(self.xmlfilepath,ConfigName), outdir)
        needToCopyConfig = not self.xmlfilepath in os.getcwd() and not os.getcwd() in self.outfilename
        if needToCopyConfig:
            shutil.copy(os.path.join(self.xmlfilepath,ConfigName), os.getcwd())
        self.xmlinfo = XMLInfo(self.xmlfilename)
        if needToCopyConfig:
            os.remove(os.path.join(os.getcwd(),ConfigName))
        self.settings_list = ['configsettings','submissionsettings','additionalvars']
        self.sample_info = ['name','type','group','xsecs','nevents_weighted', 'xmlfiles', 'contents']
        self.GetDatasetsInfo(AllSamples)
        self.expand_entities = False


    def GetDatasetsInfo(self, AllSamples):
        self.dataset_infos = {}
        for ds in self.xmlinfo.datasets_to_write:
            dataset_name = getattr(ds.settings,'Name')
            sample = AllSamples.get_sample(dataset_name)
            for year in self.years:
                for info in self.sample_info:
                    self.dataset_infos.setdefault(dataset_name, {}).setdefault(year, {}).setdefault(info,sample.get_var_for_year(info,year))
                    if self.dataset_infos[dataset_name][year][info] is None and info != 'xsecs':
                        print(yellow('--> Config does not support the following input. %s dataset has the %s variable of year = %s set to None' %(dataset_name, info, year)))
        for addinput in self.xmlinfo.additionalinputs:
            for ds in addinput.datasets:
                for collection in addinput.collections:
                    dataset_name = getattr(ds.settings,'Name').replace('standard',getattr(collection,'BranchName'))
                    sample = AllSamples.get_sample(dataset_name)
                    for year in self.years:
                        for info in self.sample_info:
                            self.dataset_infos.setdefault(dataset_name, {}).setdefault(year, {}).setdefault(info,sample.get_var_for_year(info,year))

    def modifyConfigAttribute(self, name, value):
        for att in self.settings_list:
            if getattr(self.xmlinfo, att).hasValue(name):
                getattr(self.xmlinfo, att).setValue(name, str(value))


    def modifyDatasetsAttributes(self, year):
        for ds in self.xmlinfo.datasets_to_write:
            dataset_name = getattr(ds.settings,'Name')
            ds.infiles = []
            if self.expand_entities:
                if len(self.xmlinfo.additionalinputs):
                    print(yellow('Operation not supported yet'))
                with open(os.path.join(self.leaf_path,self.dataset_infos[dataset_name][year]['xmlfiles']), 'r') as f_:
                    format_line = parse.compile('<InputFile FileName="{inputfile}"/>\n')
                    ds.infiles = [ format_line.parse(line)['inputfile'] for line in f_.readlines() if format_line.parse(line) is not None ]
            if self.dataset_infos[dataset_name][year]['type'].upper() == 'DATA':
                lumi = '1.'
            elif self.dataset_infos[dataset_name][year]['type'].upper() == 'MC' and self.dataset_infos[dataset_name][year]['xsecs'] is not None:
                lumi = str(float(self.dataset_infos[dataset_name][year]['nevents_weighted']) / float(self.dataset_infos[dataset_name][year]['xsecs']))
            elif self.dataset_infos[dataset_name][year]['type'].upper() == 'MC' and self.dataset_infos[dataset_name][year]['nevents_weighted'] is not None:
                # normalize to 1 pb
                lumi = str(float(self.dataset_infos[dataset_name][year]['nevents_weighted']))
            else:
                errorString = '--> This sample does not have a correct set of inputs:'
                for var in self.sample_info:
                    errorString += ('%s = %s' %(var, year))
                raise  RuntimeError(red(errorString))

            newName = self.dataset_infos[dataset_name][year]['name']+"_"+year
            setattr(ds.settings, 'Name',  newName)
            setattr(ds.settings, 'Type',  self.dataset_infos[dataset_name][year]['type'])
            setattr(ds.settings, 'Group', self.dataset_infos[dataset_name][year]['group'])
            setattr(ds.settings, 'Year',  year)
            setattr(ds.settings, 'Lumi',  lumi)

            for addinput in self.xmlinfo.additionalinputs:
                for ds_add in addinput.datasets:
                    if not ds_add.settings.Name == dataset_name:
                        continue
                    setattr(ds_add.settings, 'Name', newName)
                    setattr(ds_add.settings, 'Year', year)

    def AddEntityInLine(self, xmlOutput, name, value, condition):
        return '\n'.join([x.replace('/>', '> &'+value+'; </'+condition+'> ') if ('Name="'+name+'"' in x and '<'+condition in x) else x for x in xmlOutput.split('\n')])

    def AddSystemEntity(self, ds_name, year):
        entity = '<!ENTITY {} SYSTEM "{}" >\n'.format(ds_name, os.path.join(self.leaf_path,self.dataset_infos[ds_name.strip("_"+year)][year]['xmlfiles']))
        self.xmlinfo.config_info = ''.join([self.xmlinfo.config_info.split(']>')[0],entity])+'\n]>\n'

    def write_single_xml(self, year):
        outfilename = self.outfilename.replace('.xml','_'+year+'.xml')
        xmlOutput = self.xmlinfo.get_XML_document().toprettyxml()
        if 'None' in str(xmlOutput):
            print(yellow('--> Config file still contains \'None\' values. Please check.'))
            return
        if not self.expand_entities:
            for ds in self.xmlinfo.datasets_to_write:
                ds_name = getattr(ds.settings,'Name')
                self.AddSystemEntity(ds_name, year)
                xmlOutput = self.AddEntityInLine(xmlOutput, ds_name, ds_name, condition='Dataset')
                for addinput in self.xmlinfo.additionalinputs:
                    for ds_add in addinput.datasets:
                        if ds_name != ds_add.settings.Name:
                            continue
                        for collection in addinput.collections:
                            ds_name_coll = ds_name.replace('standard',getattr(collection,'BranchName'))
                            self.AddSystemEntity(ds_name_coll, year)
                            xmlOutput = self.AddEntityInLine(xmlOutput, ds_name, ds_name_coll, condition='AdditionalDataset')
        with open(outfilename, 'wr') as f:
            print(green('--> Creating new config: %s' %(outfilename)))
            f.write(self.xmlinfo.config_info)
            f.write(xmlOutput)

    def modifySpecificSettings(self, year):
        pass

    def modifyAllSettings(self):
        for year in self.years:
            self.modifyDatasetsAttributes(year=year)
            self.modifyConfigAttribute('OutputDirectory', self.xmlinfo.configsettings.getValue('OutputDirectory').replace('Year',year))
            self.modifySpecificSettings(year)
            self.write_single_xml(year)
