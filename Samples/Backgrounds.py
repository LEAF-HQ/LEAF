from Sample import *
from Storage import *
from collections import OrderedDict


# backgrounds = {
# backgrounds = OrderedDict()

# def populate_backgrounds(dict):

# List of tuples ('samplename', sample itself) to be inserted orderly into an OrderedDict
backgroundlist = [
    ('TTToSemiLeptonic', Sample(
        type='MC',
        name='TTToSemiLeptonic',
        group=YearDependentContainer({'2017': 'TT'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/TTToSemiLeptonic')}),
        xsecs=YearDependentContainer({'2017': 364.31, '2018': 364.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToSemiLeptonic.xml'}),
        nevents=YearDependentContainer({'2017': 34186693988.4})
    )),

    ('TTTo2L2Nu', Sample(
        type='MC',
        name='TTTo2L2Nu',
        group=YearDependentContainer({'2017': 'TT'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/TTTo2L2Nu')}),
        xsecs=YearDependentContainer({'2017': 87.33, '2018': 87.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTTo2L2Nu.xml'}),
        nevents=YearDependentContainer({'2017': 4546025475.14})
    )),

    ('TTToHadronic', Sample(
        type='MC',
        name='TTToHadronic',
        group=YearDependentContainer({'2017': 'TT'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v4/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/TTToHadronic')}),
        xsecs=YearDependentContainer({'2017': 380.11, '2018': 380.11}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToHadronic.xml'}),
        nevents=YearDependentContainer({'2017': 40716588155.1})
    )),

    ('WJetsToLNu', Sample(
        type='MC',
        name='WJetsToLNu',
        group=YearDependentContainer({'2017': 'WJets'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/WJetsToLNu')}),
        xsecs=YearDependentContainer({'2016': 61526.7, '2017': 61526.7, '2018': 61526.7}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/WJetsToLNu.xml'}),
        nevents=YearDependentContainer({'2017': 10460319012573.9})
    )),

    ('DYJetsToLL', Sample(
        type='MC',
        name='DYJetsToLL',
        group=YearDependentContainer({'2017': 'DYJets'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/DYJetsToLL')}),
        xsecs=YearDependentContainer({'2016': 6077.22, '2017': 6077.22, '2018': 6077.22}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/DYJetsToLL.xml'}),
        nevents=YearDependentContainer({'2017': 3587107524771.56})
    )),

    ('ST_tch_top', Sample(
        type='MC',
        name='ST_tch_top',
        group=YearDependentContainer({'2017': 'ST'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/ST_tch_top')}),
        xsecs=YearDependentContainer({'2017': 136.02}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tch_top.xml'}),
        nevents=YearDependentContainer({'2017': 645038376.222})
    )),

    ('ST_tch_antitop', Sample(
        type='MC',
        name='ST_tch_antitop',
        group=YearDependentContainer({'2017': 'ST'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/ST_tch_antitop')}),
        xsecs=YearDependentContainer({'2017': 80.95}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tch_antitop.xml'}),
        nevents=YearDependentContainer({'2017': 265124230.528})
    )),

    ('ST_sch', Sample(
        type='MC',
        name='ST_sch',
        group=YearDependentContainer({'2017': 'ST'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/ST_sch')}),
        xsecs=YearDependentContainer({'2017': 3.36}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_sch.xml'}),
        nevents=YearDependentContainer({'2017': 70465636.8369})
    )),

    ('ST_tW_top', Sample(
        type='MC',
        name='ST_tW_top',
        group=YearDependentContainer({'2017': 'ST'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/ST_tW_top')}),
        xsecs=YearDependentContainer({'2016': 71.7*0.5*0.546, '2017': 71.7*0.5*0.546, '2018': 71.7*0.5*0.546}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tW_top.xml'}),
        nevents=YearDependentContainer({'2017': 317284040.768})
    )),

    ('ST_tW_antitop', Sample(
        type='MC',
        name='ST_tW_antitop',
        group=YearDependentContainer({'2017': 'ST'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/ST_tW_antitop')}),
        xsecs=YearDependentContainer({'2016': 71.7*0.5*0.546, '2017': 71.7*0.5*0.546, '2018': 71.7*0.5*0.546}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/ST_tW_antitop.xml'}),
        nevents=YearDependentContainer({'2017': 281043961.18})
    )),

    ('QCD_Pt_15to30', Sample(
        type='MC',
        name='QCD_Pt_15to30',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_15to30')}),
        xsecs=YearDependentContainer({'2017': 1234000000.000000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_15to30.xml'}),
        nevents=YearDependentContainer({'2017': 19997400.0})
    )),

    ('QCD_Pt_30to50', Sample(
        type='MC',
        name='QCD_Pt_30to50',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_30to50')}),
        xsecs=YearDependentContainer({'2017': 105800000.000000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_30to50.xml'}),
        nevents=YearDependentContainer({'2017': 18644665.0})
    )),

    ('QCD_Pt_50to80', Sample(
        type='MC',
        name='QCD_Pt_50to80',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_50to80')}),
        xsecs=YearDependentContainer({'2017': 15560000.000000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_50to80.xml'}),
        nevents=YearDependentContainer({'2017': 19861600.0})
    )),

    ('QCD_Pt_80to120', Sample(
        type='MC',
        name='QCD_Pt_80to120',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_80to120')}),
        xsecs=YearDependentContainer({'2017': 2317000.000000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_80to120.xml'}),
        nevents=YearDependentContainer({'2017': 28323678.2942})
    )),

    ('QCD_Pt_120to170', Sample(
        type='MC',
        name='QCD_Pt_120to170',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_120to170')}),
        xsecs=YearDependentContainer({'2017': 403700.000000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_120to170.xml'}),
        nevents=YearDependentContainer({'2017': 29951728.8323})
    )),

    ('QCD_Pt_170to300', Sample(
        type='MC',
        name='QCD_Pt_170to300',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_170to300')}),
        xsecs=YearDependentContainer({'2017': 103700}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_170to300.xml'}),
        nevents=YearDependentContainer({'2017': 29522100.0})
    )),

    ('QCD_Pt_300to470', Sample(
        type='MC',
        name='QCD_Pt_300to470',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_300to470')}),
        xsecs=YearDependentContainer({'2017': 6764}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_300to470.xml'}),
        nevents=YearDependentContainer({'2017': 57322609.9805})
    )),

    ('QCD_Pt_470to600', Sample(
        type='MC',
        name='QCD_Pt_470to600',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_470to600')}),
        xsecs=YearDependentContainer({'2017': 546.100000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_470to600.xml'}),
        nevents=YearDependentContainer({'2017': 27554288.7192})
    )),

    ('QCD_Pt_600to800', Sample(
        type='MC',
        name='QCD_Pt_600to800',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_600to800')}),
        xsecs=YearDependentContainer({'2017': 154.900000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_600to800.xml'}),
        nevents=YearDependentContainer({'2017': 63674201.5438})
    )),

    ('QCD_Pt_800to1000', Sample(
        type='MC',
        name='QCD_Pt_800to1000',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_800to1000')}),
        xsecs=YearDependentContainer({'2017': 25.970000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_800to1000.xml'}),
        nevents=YearDependentContainer({'2017': 37253325.0})
    )),

    ('QCD_Pt_1000to1400', Sample(
        type='MC',
        name='QCD_Pt_1000to1400',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_1000to1400')}),
        xsecs=YearDependentContainer({'2017': 7.398000}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1000to1400.xml'}),
        nevents=YearDependentContainer({'2017': 19967700.0})
    )),

    ('QCD_Pt_1400to1800', Sample(
        type='MC',
        name='QCD_Pt_1400to1800',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_1400to1800')}),
        xsecs=YearDependentContainer({'2017': 0.6502}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1400to1800.xml'}),
        nevents=YearDependentContainer({'2017': 5434800.0})
    )),

    ('QCD_Pt_1800to2400', Sample(
        type='MC',
        name='QCD_Pt_1800to2400',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_1800to2400')}),
        xsecs=YearDependentContainer({'2017': 0.086710}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_1800to2400.xml'}),
        nevents=YearDependentContainer({'2017': 2768951.0})
    )),

    ('QCD_Pt_2400to3200', Sample(
        type='MC',
        name='QCD_Pt_2400to3200',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_2400to3200')}),
        xsecs=YearDependentContainer({'2017': 0.005193}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_2400to3200.xml'}),
        nevents=YearDependentContainer({'2017': 1910408.0})
    )),

    ('QCD_Pt_3200toInf', Sample(
        type='MC',
        name='QCD_Pt_3200toInf',
        group=YearDependentContainer({'2017': 'QCD_Had'}),
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM')}),
        minipaths=YearDependentContainer({'2017': Storage_DAS('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/store/user/areimers/UL17/Tuples_v02_NANOAOD/QCD_Pt_3200toInf')}),
        xsecs=YearDependentContainer({'2017': 0.000134}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/QCD_Pt_3200toInf.xml'}),
        nevents=YearDependentContainer({'2017': 800000.0})
    )),
]
    # }
