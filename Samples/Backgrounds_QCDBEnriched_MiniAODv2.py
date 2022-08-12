from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_QCDBEnriched(SampleContainer):

    type = 'MC'
    name = 'QCDBEnriched_HT100to200'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT100to200_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 1.259e+06}),
        'nevents_das':       YearDependentContainer({'UL17': 30667858}),
        'nevents_generated': YearDependentContainer({'UL17': 30667858.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 1618367.90902}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT200to300'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT200to300_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 1.098e+05}),
        'nevents_das':       YearDependentContainer({'UL17': 15085476}),
        'nevents_generated': YearDependentContainer({'UL17': 15085476.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 853416.50006}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT300to500'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT300to500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 2.739e+04}),
        'nevents_das':       YearDependentContainer({'UL17': 14259151}),
        'nevents_generated': YearDependentContainer({'UL17': 14259151.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 850612.409102}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT500to700'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT500to700_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 3.037e+03}),
        'nevents_das':       YearDependentContainer({'UL17': 5969789}),
        'nevents_generated': YearDependentContainer({'UL17': 5969789.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 375543.909047}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT700to1000'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT700to1000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 7.188e+02}),
        'nevents_das':       YearDependentContainer({'UL17': 4892427}),
        'nevents_generated': YearDependentContainer({'UL17': 4892427.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 318460.181824}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT1000to1500'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT1000to1500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 1.384e+02}),
        'nevents_das':       YearDependentContainer({'UL17': 1642413}),
        'nevents_generated': YearDependentContainer({'UL17': 1642413.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 110586.09092}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT1500to2000'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT1500to2000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 1.455e+01}),
        'nevents_das':       YearDependentContainer({'UL17': 1263823}),
        'nevents_generated': YearDependentContainer({'UL17': 1263823.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 88006.77274}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)



    name = 'QCDBEnriched_HT2000toInf'
    storagenames = {
        'UL17': Storage_DAS('/QCD_HT2000toInf_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDBEnriched'}),
        'xsecs':             YearDependentContainer({'UL17': 3.127}),
        'nevents_das':       YearDependentContainer({'UL17': 1293056}),
        'nevents_generated': YearDependentContainer({'UL17': 1293056.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 92390.2272934}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
