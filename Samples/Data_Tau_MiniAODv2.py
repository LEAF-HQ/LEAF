from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Data_Tau(SampleContainer):

    type = 'DATA'
    name = 'DATA_Tau_RunB'
    storagenames = {
        'UL17': Storage_DAS('/Tau/Run2017B-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_Tau')),
        'nevents_das':       YearDependentContainer({'UL17': 38158216}),
        'nevents_generated': YearDependentContainer({'UL17': 38158216.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_Tau_RunC'
    storagenames = {
        'UL17': Storage_DAS('/Tau/Run2017C-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_Tau')),
        'nevents_das':       YearDependentContainer({'UL17': 55416425}),
        'nevents_generated': YearDependentContainer({'UL17': 55416425.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_Tau_RunD'
    storagenames = {
        'UL17': Storage_DAS('/Tau/Run2017D-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_Tau')),
        'nevents_das':       YearDependentContainer({'UL17': 20530776}),
        'nevents_generated': YearDependentContainer({'UL17': 20530776.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_Tau_RunE'
    storagenames = {
        'UL17': Storage_DAS('/Tau/Run2017E-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_Tau')),
        'nevents_das':       YearDependentContainer({'UL17': 44411467}),
        'nevents_generated': YearDependentContainer({'UL17': 44316628.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DATA_Tau_RunF'
    storagenames = {
        'UL17': Storage_DAS('/Tau/Run2017F-UL2017_MiniAODv2-v1/MINIAOD'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'DATA_Tau')),
        'nevents_das':       YearDependentContainer({'UL17': 88502118}),
        'nevents_generated': YearDependentContainer({'UL17': 81378838.0})
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
