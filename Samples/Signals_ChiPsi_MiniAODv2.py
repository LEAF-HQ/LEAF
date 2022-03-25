from Sample import *
from Storage import *
from SampleContainer_template import *

def Add_Signals_ChiPsi_LQLQToBTau(SampleContainer):
    samplenames = [
        'LQLQToBTau_MLQ1000_MCH100_MPS117_L1p0',
        'LQLQToBTau_MLQ1000_MCH100_MPS117_Lbest',
        'LQLQToBTau_MLQ1360_MCH100_MPS117_L1p0',
        'LQLQToBTau_MLQ1360_MCH100_MPS117_Lbest',
        'LQLQToBTau_MLQ1810_MCH100_MPS117_L1p0',
        'LQLQToBTau_MLQ1810_MCH100_MPS117_Lbest',
        'LQLQToBTau_MLQ2170_MCH100_MPS117_L1p0',
        'LQLQToBTau_MLQ2170_MCH100_MPS117_Lbest',
        'LQLQToBTau_MLQ2620_MCH100_MPS117_L1p0',
        'LQLQToBTau_MLQ2620_MCH100_MPS117_Lbest'
    ]
    for name in samplenames:
        type = 'MC'
        # name = 'LQLQToBTau_MLQ1000_MCH100_MPS117_L1p0'
        storagenames = {
            'UL17': Storage_T2PSI('/store/user/areimers/MINIAODv2/ChiPsi/' + name),
        }
        years = storagenames.keys()
        default_info = {
            'type': type,
            'minipaths':         YearDependentContainer(storagenames),
            'group':             YearDependentContainer(dict.fromkeys(years, name)),
            'nevents_das':       YearDependentContainer(),
            'nevents_generated': YearDependentContainer(),
            'nevents_weighted':  YearDependentContainer(),
        }
        modes = [['standard']]
        Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)

def Add_Signals_ChiPsi_LQLQToBTauPsiChi(SampleContainer):
    samplenames = [
        'LQLQToBTauPsiChi_MLQ1000_MCH100_MPS117_L1p0',
        'LQLQToBTauPsiChi_MLQ1000_MCH100_MPS117_Lbest',
        'LQLQToBTauPsiChi_MLQ1360_MCH100_MPS117_L1p0',
        'LQLQToBTauPsiChi_MLQ1360_MCH100_MPS117_Lbest',
        'LQLQToBTauPsiChi_MLQ1360_MCH457_MPS513_L1p0',
        'LQLQToBTauPsiChi_MLQ1360_MCH457_MPS513_Lbest',
        'LQLQToBTauPsiChi_MLQ1810_MCH100_MPS117_L1p0',
        'LQLQToBTauPsiChi_MLQ1810_MCH100_MPS117_Lbest',
        'LQLQToBTauPsiChi_MLQ1810_MCH457_MPS508_L1p0',
        'LQLQToBTauPsiChi_MLQ1810_MCH457_MPS508_Lbest',
        'LQLQToBTauPsiChi_MLQ2170_MCH100_MPS117_L1p0',
        'LQLQToBTauPsiChi_MLQ2170_MCH100_MPS117_Lbest',
        'LQLQToBTauPsiChi_MLQ2170_MCH457_MPS507_L1p0',
        'LQLQToBTauPsiChi_MLQ2170_MCH457_MPS507_Lbest',
        'LQLQToBTauPsiChi_MLQ2620_MCH100_MPS117_L1p0',
        'LQLQToBTauPsiChi_MLQ2620_MCH100_MPS117_Lbest',
        'LQLQToBTauPsiChi_MLQ2620_MCH457_MPS506_L1p0',
        'LQLQToBTauPsiChi_MLQ2620_MCH457_MPS506_Lbest'
    ]
    for name in samplenames:
        type = 'MC'
        # name = 'LQLQToBTau_MLQ1000_MCH100_MPS117_L1p0'
        storagenames = {
            'UL17': Storage_T2PSI('/store/user/areimers/MINIAODv2/ChiPsi/' + name),
        }
        years = storagenames.keys()
        default_info = {
            'type': type,
            'minipaths':         YearDependentContainer(storagenames),
            'group':             YearDependentContainer(dict.fromkeys(years, name)),
            'nevents_das':       YearDependentContainer(),
            'nevents_generated': YearDependentContainer(),
            'nevents_weighted':  YearDependentContainer(),
        }
        modes = [['standard']]
        Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)

def Add_Signals_ChiPsi_LQLQToPsiChi(SampleContainer):
    samplenames = [
        'LQLQToPsiChi_MLQ1000_MCH100_MPS117_L1p0',
        'LQLQToPsiChi_MLQ1000_MCH100_MPS117_Lbest',
        'LQLQToPsiChi_MLQ1360_MCH100_MPS117_L1p0',
        'LQLQToPsiChi_MLQ1360_MCH100_MPS117_Lbest',
        'LQLQToPsiChi_MLQ1360_MCH457_MPS513_L1p0',
        'LQLQToPsiChi_MLQ1360_MCH457_MPS513_Lbest',
        'LQLQToPsiChi_MLQ1810_MCH100_MPS117_L1p0',
        'LQLQToPsiChi_MLQ1810_MCH100_MPS117_Lbest',
        'LQLQToPsiChi_MLQ1810_MCH457_MPS508_L1p0',
        'LQLQToPsiChi_MLQ1810_MCH457_MPS508_Lbest',
        'LQLQToPsiChi_MLQ2170_MCH100_MPS117_L1p0',
        'LQLQToPsiChi_MLQ2170_MCH100_MPS117_Lbest',
        'LQLQToPsiChi_MLQ2170_MCH457_MPS507_L1p0',
        'LQLQToPsiChi_MLQ2170_MCH457_MPS507_Lbest',
        'LQLQToPsiChi_MLQ2620_MCH100_MPS117_L1p0',
        'LQLQToPsiChi_MLQ2620_MCH100_MPS117_Lbest',
        'LQLQToPsiChi_MLQ2620_MCH457_MPS506_L1p0',
        'LQLQToPsiChi_MLQ2620_MCH457_MPS506_Lbest'
    ]
    for name in samplenames:
        type = 'MC'
        # name = 'LQLQToBTau_MLQ1000_MCH100_MPS117_L1p0'
        storagenames = {
            'UL17': Storage_T2PSI('/store/user/areimers/MINIAODv2/ChiPsi/' + name),
        }
        years = storagenames.keys()
        default_info = {
            'type': type,
            'minipaths':         YearDependentContainer(storagenames),
            'group':             YearDependentContainer(dict.fromkeys(years, name)),
            'nevents_das':       YearDependentContainer(),
            'nevents_generated': YearDependentContainer(),
            'nevents_weighted':  YearDependentContainer(),
        }
        modes = [['standard']]
        Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)

def Add_Signals_ChiPsi_PsiPsiToLQChi(SampleContainer):
    samplenames = [
        'PsiPsiToLQChi_MLQ10000_MCH100_MPS117_L1p0',
        'PsiPsiToLQChi_MLQ10000_MCH2089_MPS2342_L1p0',
        'PsiPsiToLQChi_MLQ10000_MCH214_MPS244_L1p0',
        'PsiPsiToLQChi_MLQ10000_MCH457_MPS504_L1p0',
        'PsiPsiToLQChi_MLQ10000_MCH977_MPS1052_L1p0',
        'PsiPsiToLQChi_MLQ1000_MCH100_MPS117_L1p0',
        'PsiPsiToLQChi_MLQ1000_MCH2089_MPS2221_L1p0',
        'PsiPsiToLQChi_MLQ1000_MCH214_MPS244_L1p0',
        'PsiPsiToLQChi_MLQ1000_MCH457_MPS567_L1p0',
        'PsiPsiToLQChi_MLQ1000_MCH977_MPS1051_L1p0',
        'PsiPsiToLQChi_MLQ3970_MCH100_MPS117_L1p0',
        'PsiPsiToLQChi_MLQ3970_MCH2089_MPS2551_L1p0',
        'PsiPsiToLQChi_MLQ3970_MCH214_MPS244_L1p0',
        'PsiPsiToLQChi_MLQ3970_MCH457_MPS505_L1p0',
        'PsiPsiToLQChi_MLQ3970_MCH977_MPS1106_L1p0',
        'PsiPsiToLQChi_MLQ7030_MCH100_MPS117_L1p0',
        'PsiPsiToLQChi_MLQ7030_MCH2089_MPS2445_L1p0',
        'PsiPsiToLQChi_MLQ7030_MCH214_MPS244_L1p0',
        'PsiPsiToLQChi_MLQ7030_MCH457_MPS504_L1p0',
        'PsiPsiToLQChi_MLQ7030_MCH977_MPS1071_L1p0'
    ]
    for name in samplenames:
        type = 'MC'
        # name = 'LQLQToBTau_MLQ1000_MCH100_MPS117_L1p0'
        storagenames = {
            'UL17': Storage_T2PSI('/store/user/areimers/MINIAODv2/ChiPsi/' + name),
        }
        years = storagenames.keys()
        default_info = {
            'type': type,
            'minipaths':         YearDependentContainer(storagenames),
            'group':             YearDependentContainer(dict.fromkeys(years, name)),
            'nevents_das':       YearDependentContainer(),
            'nevents_generated': YearDependentContainer(),
            'nevents_weighted':  YearDependentContainer(),
        }
        modes = [['standard']]
        Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2PSI, '/store/user/areimers/NTuples/', get_common_path(), default_info)


def Add_Signals_ChiPsi(SampleContainer):
    Add_Signals_ChiPsi_LQLQToBTau(SampleContainer)
    Add_Signals_ChiPsi_LQLQToBTauPsiChi(SampleContainer)
    Add_Signals_ChiPsi_LQLQToPsiChi(SampleContainer)
    Add_Signals_ChiPsi_PsiPsiToLQChi(SampleContainer)
