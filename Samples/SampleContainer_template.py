from Sample import *
from Storage import *

def XML_path(year):
    return 'Analyzer/datasets/'+year+'/Summer20/MINIAOD/'
    # return 'Analyzer/datasets/year/Summer20/MINIAODv2/NTuples_v01/'

def storage_path(folder, year, mode, name):
    return os.path.join(folder,year,mode,name)

def get_xml(xml_name, year):
    return os.path.join(XML_path(year), xml_name)+'.xml'

def Add_Generic_Sample(SampleContainer, name, modes, years, storage, folder, default_info):
    to_add = []
    for var in ['name', 'group', 'tuplepaths', 'xmlfiles', 'contents']:
        if not var in default_info: to_add.append(var)

    for mode in modes:
        if 'name' in to_add:
            default_info['name'] = name+'_'+mode
        if 'group' in to_add:
            default_info['group'] = YearDependentContainer(dict.fromkeys(years, name))
        if 'xsecs' in to_add:
            default_info['xsecs'] = YearDependentContainer()
        if 'tuplepaths' in to_add:
            default_info['tuplepaths'] = YearDependentContainer(dict((year,storage(storage_path(folder, year, mode, name))) for year in years))
        if 'xmlfiles' in to_add:
            default_info['xmlfiles'] = YearDependentContainer(dict((year,get_xml(name+'_'+mode, year)) for year in years))
        if 'contents' in to_add:
            default_info['contents'] = YearDependentContainer(dict.fromkeys(years, mode.split('_plus_')))

        SampleContainer.add_samples({name+'_'+mode: Sample(**default_info)})
