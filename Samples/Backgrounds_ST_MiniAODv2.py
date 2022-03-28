from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_ST(SampleContainer):

    type = 'MC'
    name = 'ST_tch_ele'
    storagenames = {
        'UL17': Storage_DAS('/ST_t-channel_eleDecays_TuneCP5_13TeV-comphep-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 24.780000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ST_tch_mu'
    storagenames = {
        'UL17': Storage_DAS('/ST_t-channel_muDecays_TuneCP5_13TeV-comphep-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 24.770000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ST_tch_tau'
    storagenames = {
        'UL17': Storage_DAS('/ST_t-channel_tauDecays_TuneCP5_13TeV-comphep-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 24.760000}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ST_sch'
    storagenames = {
        'UL17': Storage_DAS('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 3.36}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ST_tW_top'
    storagenames = {
        'UL17': Storage_DAS('/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 71.7*0.5*0.546}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'ST_tW_antitop'
    storagenames = {
        'UL17': Storage_DAS('/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'ST'}),
        'xsecs':             YearDependentContainer({'UL17': 71.7*0.5*0.546}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
