from Sample import *
from Storage import *
from SampleContainer_template import *


def Add_Backgrounds_ZJetsToNuNu(SampleContainer):

    type = 'MC'
    name = 'ZJetsToNuNu_HT100To200'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 265.900000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 18983897}),
        'nevents_generated': YearDependentContainer({'UL17': 18983897.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 18983897.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT200To400'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 72.990000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 17349597}),
        'nevents_generated': YearDependentContainer({'UL17': 17349597.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 17349597.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT400To600'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 9.937000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 13963690}),
        'nevents_generated': YearDependentContainer({'UL17': 13963690.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 13963690.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT600To800'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 2.410000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 4418971}),
        'nevents_generated': YearDependentContainer({'UL17': 4418971.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 4418971.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT800To1200'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 1.079000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 1513585}),
        'nevents_generated': YearDependentContainer({'UL17': 1513585.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 1513585.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT1200To2500'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 0.252100 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 267125}),
        'nevents_generated': YearDependentContainer({'UL17': 267125.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 267125.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ZJetsToNuNu_HT2500ToInf'
    storagenames = {
        'UL17': Storage_DAS('/ZJetsToNuNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ZJetsNuNu'}),
        'xsecs':             YearDependentContainer({'UL17': 0.005633 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 176201}),
        'nevents_generated': YearDependentContainer({'UL17': 176201.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 176201.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
