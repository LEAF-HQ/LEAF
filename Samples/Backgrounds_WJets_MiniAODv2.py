from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_WJets(SampleContainer):

    type = 'MC'
    name = 'WJetsToLNu_Inclusive'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 53590.000000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT70To100'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 1273.000000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT100To200'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 1255.000000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT200To400'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 336.400000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT400To600'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 45.250000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT600To800'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 10.990000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT800To1200'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 4.924000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT1200To2500'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer({'UL17': 1.157000 * 1.21}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'WJetsToLNu_HT2500ToInf'
    storagenames = {
        'UL17': Storage_DAS('/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'WJets'}),
        'xsecs':             YearDependentContainer(),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
