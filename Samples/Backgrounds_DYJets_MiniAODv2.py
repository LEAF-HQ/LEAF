from Sample import *
from Storage import *
from SampleContainer_template import *


def Add_Backgrounds_DYJets(SampleContainer):

    type = 'MC'
    name = 'DYJetsToLL_M10To50_Inclusive'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 15900.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 68480179}),
        'nevents_generated': YearDependentContainer({'UL17': 68480179.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 68480179.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_Inclusive'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 5352.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 103344974}),
        'nevents_generated': YearDependentContainer({'UL17': 103290685.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 103205839.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT70To100'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 139.500000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 12205958}),
        'nevents_generated': YearDependentContainer({'UL17': 12205958.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 12205958.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT100To200'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 140.400000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 18955253}),
        'nevents_generated': YearDependentContainer({'UL17': 18955253.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 18702259.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT200To400'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 38.360000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 12513057}),
        'nevents_generated': YearDependentContainer({'UL17': 12513057.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 12513057.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT400To600'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 5.222000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 5543804}),
        'nevents_generated': YearDependentContainer({'UL17': 5543804.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 5543804.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT600To800'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 1.264000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 5278417}),
        'nevents_generated': YearDependentContainer({'UL17': 5278417.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 5278417.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT800To1200'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 0.568500 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 4506887}),
        'nevents_generated': YearDependentContainer({'UL17': 4506887.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 4506887.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT1200To2500'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 0.133000 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 4802716}),
        'nevents_generated': YearDependentContainer({'UL17': 4802716.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 4802716.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'DYJetsToLL_M50_HT2500ToInf'
    storagenames = {
        'UL17': Storage_DAS('/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'DYJets'}),
        'xsecs':             YearDependentContainer({'UL17': 0.002981 * 1.23}),
        'nevents_das':       YearDependentContainer({'UL17': 1480047}),
        'nevents_generated': YearDependentContainer({'UL17': 1480047.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 1480047.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
