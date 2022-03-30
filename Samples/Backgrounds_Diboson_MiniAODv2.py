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
        'xsecs':             YearDependentContainer({'UL17': 12.178}),
        'nevents_das':       YearDependentContainer({'UL17': 7098000}),
        'nevents_generated': YearDependentContainer({'UL17': 7098000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 78687950.4184}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WZ_2Q2L'
    storagenames = {
        'UL17': Storage_DAS('/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer({'UL17': 5.595}),
        'nevents_das':       YearDependentContainer({'UL17': 29091996}),
        'nevents_generated': YearDependentContainer({'UL17': 29091996.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 279011957.776}),
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
        'xsecs':             YearDependentContainer({'UL17': 4.4297}),
        'nevents_das':       YearDependentContainer({'UL17': 1994000}),
        'nevents_generated': YearDependentContainer({'UL17': 1994000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 9298956.9674}),
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
        'xsecs':             YearDependentContainer({'UL17': 0.564}),
        'nevents_das':       YearDependentContainer({'UL17': 40839000}),
        'nevents_generated': YearDependentContainer({'UL17': 40839000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 39767479.3951}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZZ_2Q2L'
    storagenames = {
        'UL17': Storage_DAS('/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'VV'}),
        'xsecs':             YearDependentContainer({'UL17': 3.22}),
        'nevents_das':       YearDependentContainer({'UL17': 29521496}),
        'nevents_generated': YearDependentContainer({'UL17': 29521496.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 162895522.458}),
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
        'xsecs':             YearDependentContainer({'UL17': 1.256}), #1.256?
        'nevents_das':       YearDependentContainer({'UL17': 41708429}),
        'nevents_generated': YearDependentContainer({'UL17': 41708429.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 577305398.684}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
