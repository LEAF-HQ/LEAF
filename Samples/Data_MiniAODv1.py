from Sample import *
from Storage import *

datalist = [

    ('DATA_Tau_B', Sample(
        type='DATA',
        name='DATA_Tau_B',
        group=YearDependentContainer({'UL17': 'DATA_Tau'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/Tau/Run2017B-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Tau_B')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Tau_B.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Tau_C', Sample(
        type='DATA',
        name='DATA_Tau_C',
        group=YearDependentContainer({'UL17': 'DATA_Tau'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/Tau/Run2017C-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Tau_C')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Tau_C.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Tau_D', Sample(
        type='DATA',
        name='DATA_Tau_D',
        group=YearDependentContainer({'UL17': 'DATA_Tau'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/Tau/Run2017D-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Tau_D')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Tau_D.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Tau_E', Sample(
        type='DATA',
        name='DATA_Tau_E',
        group=YearDependentContainer({'UL17': 'DATA_Tau'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/Tau/Run2017E-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Tau_E')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Tau_E.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Tau_F', Sample(
        type='DATA',
        name='DATA_Tau_F',
        group=YearDependentContainer({'UL17': 'DATA_Tau'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/Tau/Run2017F-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Tau_F')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Tau_F.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Met_B', Sample(
        type='DATA',
        name='DATA_Met_B',
        group=YearDependentContainer({'UL17': 'DATA_Met'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/MET/Run2017B-09Aug2019_UL2017_rsb-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Met_B')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Met_B.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Met_C', Sample(
        type='DATA',
        name='DATA_Met_C',
        group=YearDependentContainer({'UL17': 'DATA_Met'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/MET/Run2017C-09Aug2019_UL2017_rsb-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Met_C')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Met_C.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Met_D', Sample(
        type='DATA',
        name='DATA_Met_D',
        group=YearDependentContainer({'UL17': 'DATA_Met'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/MET/Run2017D-09Aug2019_UL2017_rsb-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Met_D')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Met_D.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Met_E', Sample(
        type='DATA',
        name='DATA_Met_E',
        group=YearDependentContainer({'UL17': 'DATA_Met'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/MET/Run2017E-09Aug2019_UL2017_rsb-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Met_E')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Met_E.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_Met_F', Sample(
        type='DATA',
        name='DATA_Met_F',
        group=YearDependentContainer({'UL17': 'DATA_Met'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/MET/Run2017F-09Aug2019_UL2017_rsb-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_Met_F')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_Met_F.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleMuon_B', Sample(
        type='DATA',
        name='DATA_SingleMuon_B',
        group=YearDependentContainer({'UL17': 'DATA_SingleMuon'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleMuon/Run2017B-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleMuon_B')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleMuon_B.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleMuon_C', Sample(
        type='DATA',
        name='DATA_SingleMuon_C',
        group=YearDependentContainer({'UL17': 'DATA_SingleMuon'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleMuon/Run2017C-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleMuon_C')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleMuon_C.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleMuon_D', Sample(
        type='DATA',
        name='DATA_SingleMuon_D',
        group=YearDependentContainer({'UL17': 'DATA_SingleMuon'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleMuon/Run2017D-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleMuon_D')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleMuon_D.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleMuon_E', Sample(
        type='DATA',
        name='DATA_SingleMuon_E',
        group=YearDependentContainer({'UL17': 'DATA_SingleMuon'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleMuon/Run2017E-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleMuon_E')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleMuon_E.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleMuon_F', Sample(
        type='DATA',
        name='DATA_SingleMuon_F',
        group=YearDependentContainer({'UL17': 'DATA_SingleMuon'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleMuon/Run2017F-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleMuon_F')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleMuon_F.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleElectron_B', Sample(
        type='DATA',
        name='DATA_SingleElectron_B',
        group=YearDependentContainer({'UL17': 'DATA_SingleElectron'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleElectron/Run2017B-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleElectron_B')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleElectron_B.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleElectron_C', Sample(
        type='DATA',
        name='DATA_SingleElectron_C',
        group=YearDependentContainer({'UL17': 'DATA_SingleElectron'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleElectron/Run2017C-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleElectron_C')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleElectron_C.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleElectron_D', Sample(
        type='DATA',
        name='DATA_SingleElectron_D',
        group=YearDependentContainer({'UL17': 'DATA_SingleElectron'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleElectron/Run2017D-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleElectron_D')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleElectron_D.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleElectron_E', Sample(
        type='DATA',
        name='DATA_SingleElectron_E',
        group=YearDependentContainer({'UL17': 'DATA_SingleElectron'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleElectron/Run2017E-09Aug2019_UL2017-v1/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleElectron_E')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleElectron_E.xml'}),
        nevents=YearDependentContainer()
    )),

    ('DATA_SingleElectron_F', Sample(
        type='DATA',
        name='DATA_SingleElectron_F',
        group=YearDependentContainer({'UL17': 'DATA_SingleElectron'}),
        minipaths=YearDependentContainer({'UL17': Storage_DAS('/SingleElectron/Run2017F-09Aug2019_UL2017_rsb-v2/MINIAOD')}),
        tuplepaths=YearDependentContainer({'UL17': Storage_T3PSI('/store/user/areimers/UL17/Summer20/Tuples_v00_MINIAOD/DATA_SingleElectron_F')}),
        xsecs=YearDependentContainer(),
        xmlfiles=YearDependentContainer({'UL17': 'datasets/UL17/Summer20/MINIAOD/DATA_SingleElectron_F.xml'}),
        nevents=YearDependentContainer()
    ))

]
# }
