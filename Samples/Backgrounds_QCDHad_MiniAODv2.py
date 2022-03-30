from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Backgrounds_QCDHad(SampleContainer):

    type = 'MC'
    name = 'QCD_Pt_15to30'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 1245000000.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 19742000}),
        'nevents_generated': YearDependentContainer({'UL17': 19658000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 19658000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_30to50'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 105800000.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 19829000}),
        'nevents_generated': YearDependentContainer({'UL17': 19829000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 19829000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_50to80'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 15560000.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 19997000}),
        'nevents_generated': YearDependentContainer({'UL17': 19997000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 19997000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_80to120'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 2319000.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 29403000}),
        'nevents_generated': YearDependentContainer({'UL17': 29403000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 29406324.5708}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_120to170'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 403500.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 28896000}),
        'nevents_generated': YearDependentContainer({'UL17': 22944000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 22944281.041}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_170to300'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 102600.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 29811000}),
        'nevents_generated': YearDependentContainer({'UL17': 29064000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 29064000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_300to470'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 6760.000000}),
        'nevents_das':       YearDependentContainer({'UL17': 55690000}),
        'nevents_generated': YearDependentContainer({'UL17': 42592000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 42676006.7038}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_470to600'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 545.900000}),
        'nevents_das':       YearDependentContainer({'UL17': 50885000}),
        'nevents_generated': YearDependentContainer({'UL17': 43622000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 43622143.0906}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_600to800'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 154.700000}),
        'nevents_das':       YearDependentContainer({'UL17': 67379000}),
        'nevents_generated': YearDependentContainer({'UL17': 62651000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 62651001.4941}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_800to1000'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 25.950000}),
        'nevents_das':       YearDependentContainer({'UL17': 36890000}),
        'nevents_generated': YearDependentContainer({'UL17': 30641000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 30641000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_1000to1400'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 7.398000}),
        'nevents_das':       YearDependentContainer({'UL17': 19781000}),
        'nevents_generated': YearDependentContainer({'UL17': 19556000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 19556000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_1400to1800'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 0.642300}),
        'nevents_das':       YearDependentContainer({'UL17': 10994000}),
        'nevents_generated': YearDependentContainer({'UL17': 10994000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 10994000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_1800to2400'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 0.086710}),
        'nevents_das':       YearDependentContainer({'UL17': 5488000}),
        'nevents_generated': YearDependentContainer({'UL17': 5488000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 5488000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_2400to3200'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 0.005193}),
        'nevents_das':       YearDependentContainer({'UL17': 2997000}),
        'nevents_generated': YearDependentContainer({'UL17': 2757000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 2757000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


    name = 'QCD_Pt_3200toInf'
    storagenames = {
        'UL17': Storage_DAS('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'),
    }
    years = storagenames.keys()
    default_info = {
        'type': type,
        'minipaths':         YearDependentContainer(storagenames),
        'group':             YearDependentContainer({'UL17': 'QCDHad'}),
        'xsecs':             YearDependentContainer({'UL17': 0.000134}),
        'nevents_das':       YearDependentContainer({'UL17': 1000000}),
        'nevents_generated': YearDependentContainer({'UL17': 970000.0}),
        'nevents_weighted':  YearDependentContainer({'UL17': 970000.0}),
    }
    modes = [['standard']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)
