from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Data_MET(SampleContainer):

    type = 'DATA'
    name = 'DATA_MET_RunB'
    storagenames = {
        'UL17': Storage_DAS('/MET/Run2017B-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_MET')),
        'nevents_das':       YearDependentContainer({'UL17': 51623474}),
        'nevents_generated': YearDependentContainer({'UL17': 51623474.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_MET_RunC'
    storagenames = {
        'UL17': Storage_DAS('/MET/Run2017C-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_MET')),
        'nevents_das':       YearDependentContainer({'UL17': 115906496}),
        'nevents_generated': YearDependentContainer({'UL17': 115906496.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_MET_RunD'
    storagenames = {
        'UL17': Storage_DAS('/MET/Run2017D-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_MET')),
        'nevents_das':       YearDependentContainer({'UL17': 20075033}),
        'nevents_generated': YearDependentContainer({'UL17': 20075033.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_MET_RunE'
    storagenames = {
        'UL17': Storage_DAS('/MET/Run2017E-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_MET')),
        'nevents_das':       YearDependentContainer({'UL17': 71418865}),
        'nevents_generated': YearDependentContainer({'UL17': 71418865.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_MET_RunF'
    storagenames = {
        'UL17': Storage_DAS('/MET/Run2017F-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_MET')),
        'nevents_das':       YearDependentContainer({'UL17': 177521562}),
        'nevents_generated': YearDependentContainer({'UL17': 177521562.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
