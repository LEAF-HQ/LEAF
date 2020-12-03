from Sample import *
from Storage import *

samples = {

    'TTToSemiLeptonic': Sample(
        type='MC',
        name='TTToSemiLeptonic',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_NANOAOD/TTToSemiLeptonic')}),
        xsecs=YearDependentContainer({'2017': 364.31, '2018': 364.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToSemiLeptonic.xml'}),
        nevents=YearDependentContainer()
    ),

    'TTTo2L2Nu': Sample(
        type='MC',
        name='TTTo2L2Nu',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_NANOAOD/TTTo2L2Nu')}),
        xsecs=YearDependentContainer({'2017': 87.33, '2018': 87.33}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTTo2L2Nu.xml'}),
        nevents=YearDependentContainer()
    ),

    'TTToHadronic': Sample(
        type='MC',
        name='TTToHadronic',
        nanopaths=YearDependentContainer({'2017': Storage_DAS('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v4/NANOAODSIM')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_NANOAOD/TTToHadronic')}),
        xsecs=YearDependentContainer({'2017': 380.11, '2018': 380.11}),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/TTToHadronic.xml'}),
        nevents=YearDependentContainer()
    ),

    'LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0': Sample(
        type='MC',
        name='LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0',
        nanopaths=YearDependentContainer({'2017': Storage_T2PSI('/pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/FLAT/LQDM/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0')}),
        tuplepaths=YearDependentContainer({'2017': Storage_T3PSI('/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_NANOAOD/LQDM/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'2017': 'datasets/UL17/Recolevel/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0.xml'}),
        nevents=YearDependentContainer()
    ),
}

# samples['TTToSemiLeptonic'].get_info('2017')
# print samples['TTToSemiLeptonic'].get_var_for_year('xsecs', '2017')
# print samples['TTToSemiLeptonic'].get_var_for_year('nanopaths', '2017')
# print samples['TTToSemiLeptonic'].get_var_for_year('tuplepaths', '2017')
# print samples['LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0'].tuplepaths['2017'].filelist
# store = Storage_DAS('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAOD-106X_mc2017_realistic_v6-v2/NANOAODSIM')
# print store.filelist
# store = Storage_T2PSI('/pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/FLAT/LQDM/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0')
# print store.filelist
# store = Storage_T3PSI('/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_NANOAOD/LQDM/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0')
# print store.filelist
