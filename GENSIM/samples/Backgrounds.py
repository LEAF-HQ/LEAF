from Sample import *
from Storage import *

backgrounds = {


    'TTToSemiLeptonic': Sample(
        type='MC',
        name='TTToSemiLeptonic',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/TTToSemiLeptonic')}),
        xsecs=YearDependentContainer({'2017': 364.31, '2018': 364.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToSemiLeptonic.xml'}),
        nevents=YearDependentContainer({'2017': 114058500})
    ),

    'TTTo2L2Nu': Sample(
        type='MC',
        name='TTTo2L2Nu',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/TTTo2L2Nu')}),
        xsecs=YearDependentContainer({'2017': 87.33, '2018': 87.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTTo2L2Nu.xml'}),
        nevents=YearDependentContainer({'2017': 59485100})
    ),

    'TTToHadronic': Sample(
        type='MC',
        name='TTToHadronic',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v4/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/TTToHadronic')}),
        xsecs=YearDependentContainer({'2017': 380.11, '2018': 380.11}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToHadronic.xml'}),
        nevents=YearDependentContainer({'2017': 129706300})
    ),

    'WJetsToLNu': Sample(
        type='MC',
        name='WJetsToLNu',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/WJetsToLNu')}),
        xsecs=YearDependentContainer({'2016': 61526.7, '2017': 61526.7, '2018': 61526.7}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/WJetsToLNu.xml'}),
        nevents=YearDependentContainer({'2017': 87614760})
    ),

    'DYJetsToLL': Sample(
        type='MC',
        name='DYJetsToLL',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/DYJetsToLL')}),
        xsecs=YearDependentContainer({'2016': 6077.22, '2017': 6077.22, '2018': 6077.22}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/DYJetsToLL.xml'}),
        nevents=YearDependentContainer({'2017': 202861676})
    ),

    'ST_tch_top': Sample(
        type='MC',
        name='ST_tch_top',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/ST_tch_top')}),
        xsecs=YearDependentContainer({'2017': 136.02}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tch_top.xml'}),
        nevents=YearDependentContainer({'2017': 5206600})
    ),

    'ST_tch_antitop': Sample(
        type='MC',
        name='ST_tch_antitop',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/ST_tch_antitop')}),
        xsecs=YearDependentContainer({'2017': 80.95}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tch_antitop.xml'}),
        nevents=YearDependentContainer({'2017': 9801734})
    ),

    'ST_sch': Sample(
        type='MC',
        name='ST_sch',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/ST_sch')}),
        xsecs=YearDependentContainer({'2017': 3.36}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_sch.xml'}),
        nevents=YearDependentContainer({'2017': 19050000})
    ),

    'ST_tW_top': Sample(
        type='MC',
        name='ST_tW_top',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/ST_tW_top')}),
        xsecs=YearDependentContainer({'2016': 71.7*0.5*0.546, '2017': 71.7*0.5*0.546, '2018': 71.7*0.5*0.546}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tW_top.xml'}),
        nevents=YearDependentContainer({'2017': 10041965})
    ),

    'ST_tW_antitop': Sample(
        type='MC',
        name='ST_tW_antitop',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/ST_tW_antitop')}),
        xsecs=YearDependentContainer({'2016': 71.7*0.5*0.546, '2017': 71.7*0.5*0.546, '2018': 71.7*0.5*0.546}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tW_antitop.xml'}),
        nevents=YearDependentContainer({'2017': 9191369})
    ),

    'QCD_Pt_15to30': Sample(
        type='MC',
        name='QCD_Pt_15to30',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_15to30')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_15to30.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_30to50': Sample(
        type='MC',
        name='QCD_Pt_30to50',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_30to50')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_30to50.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_50to80': Sample(
        type='MC',
        name='QCD_Pt_50to80',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_50to80')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_50to80.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_80to120': Sample(
        type='MC',
        name='QCD_Pt_80to120',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_80to120')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_80to120.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_120to170': Sample(
        type='MC',
        name='QCD_Pt_120to170',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_120to170')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_120to170.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_170to300': Sample(
        type='MC',
        name='QCD_Pt_170to300',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_170to300')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_170to300.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_300to470': Sample(
        type='MC',
        name='QCD_Pt_300to470',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_300to470')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_300to470.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_470to600': Sample(
        type='MC',
        name='QCD_Pt_470to600',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_470to600')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_470to600.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_600to800': Sample(
        type='MC',
        name='QCD_Pt_600to800',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_600to800')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_600to800.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_800to1000': Sample(
        type='MC',
        name='QCD_Pt_800to1000',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_800to1000')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_800to1000.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_1000to1400': Sample(
        type='MC',
        name='QCD_Pt_1000to1400',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_1000to1400')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1000to1400.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_1400to1800': Sample(
        type='MC',
        name='QCD_Pt_1400to1800',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_1400to1800')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1400to1800.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_1800to2400': Sample(
        type='MC',
        name='QCD_Pt_1800to2400',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_1800to2400')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1800to2400.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_2400to3200': Sample(
        type='MC',
        name='QCD_Pt_2400to3200',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_2400to3200')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_2400to3200.xml'}),
        nevents=YearDependentContainer()
    ),

    'QCD_Pt_3200toInf': Sample(
        type='MC',
        name='QCD_Pt_3200toInf',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_NANOAOD/QCD_Pt_3200toInf')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_3200toInf.xml'}),
        nevents=YearDependentContainer()
    ),
}
