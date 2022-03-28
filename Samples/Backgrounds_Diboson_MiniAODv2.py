from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_Diboson(SampleContainer):

    type = 'MC'
    name = 'WW_2L2Nu'
    storagenames = {
        'UL17': Storage_DAS('/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer({'UL17': 11.090000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WZ_2Q2L'
    storagenames = {
        'UL17': Storage_DAS(' Dataset: /WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer(),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WZ_3LNu'
    storagenames = {
        'UL17': Storage_DAS('/WZTo3LNu_mllmin4p0_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer(),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZZ_2L2Nu'
    storagenames = {
        'UL17': Storage_DAS('/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer({'UL17': 0.973800}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZZ_2Q2L'
    storagenames = {
        'UL17': Storage_DAS('ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer(),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZZ_4L'
    storagenames = {
        'UL17': Storage_DAS('/ZZTo4L_M-1toInf_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer({'UL17': 13.810000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
