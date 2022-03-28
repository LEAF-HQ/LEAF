from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_TT(SampleContainer):

    type = 'MC'
    name = 'TTToSemiLeptonic'
    storagenames = {
        'UL17': Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'TT')),
        'xsecs':             YearDependentContainer({'UL17': 364.31}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'TTTo2L2Nu'
    storagenames = {
        'UL17': Storage_DAS('/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'TT')),
        'xsecs':             YearDependentContainer({'UL17': 87.33}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'TTToHadronic'
    storagenames = {
        'UL17': Storage_DAS('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer(dict.fromkeys(years, 'TT')),
        'xsecs':             YearDependentContainer({'UL17': 380.11}),
        'nevents_das':       YearDependentContainer(),
        'nevents_generated': YearDependentContainer(),
        'nevents_weighted':  YearDependentContainer(),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
