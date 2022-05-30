from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Data_SingleElectron(SampleContainer):

    type = 'DATA'
    name = 'DATA_SingleElectron_RunB'
    storagenames = {
        'UL17': Storage_DAS('/SingleElectron/Run2017B-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_SingleElectron')),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer()
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_SingleElectron_RunC'
    storagenames = {
        'UL17': Storage_DAS('/SingleElectron/Run2017C-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_SingleElectron')),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer()
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_SingleElectron_RunD'
    storagenames = {
        'UL17': Storage_DAS('/SingleElectron/Run2017D-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_SingleElectron')),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer()
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_SingleElectron_RunE'
    storagenames = {
        'UL17': Storage_DAS('/SingleElectron/Run2017E-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_SingleElectron')),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer()
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_SingleElectron_RunF'
    storagenames = {
        'UL17': Storage_DAS('/SingleElectron/Run2017F-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_SingleElectron')),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer()
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
