from Sample import *
from Storage import *

'''
Define template to store ntuple info
'''

def get_common_path():
    return 'Summer20/MINIAODv2/NTuples_v01/'

def get_storage_path(prefix, year, common_path, mode, sample_name):
    return os.path.join(prefix, year, common_path, mode, sample_name)

def Add_Generic_Sample(SampleContainer, sample_name, modes, years, storage, ntuple_folder_base, common_path, default_info):

    for mode in modes:
        mode_name = '_plus_'.join(mode)
        default_info['name'] = sample_name+'_'+mode_name
        default_info['tuplepaths'] = YearDependentContainer(dict((year,storage(get_storage_path(ntuple_folder_base,  year, common_path, mode_name, sample_name))       ) for year in years))
        default_info['xmlfiles'] = YearDependentContainer(dict((year,          get_storage_path('Analyzer/datasets/', year, common_path, mode_name, sample_name)+'.xml') for year in years))
        default_info['contents'] = YearDependentContainer(dict.fromkeys(years, mode))
        SampleContainer.add_samples({sample_name+'_'+mode_name: Sample(**default_info)})



'''
Example of usage


def Add_Signals_VBF(SampleContainer):
    type = 'MC'
    name = 'VBF_HToZZTo4L_M125'
    DAS_Names = {
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL18': 1000}),
        'nevents_generated': YearDependentContainer({'UL18': 1000}),
        'nevents_weighted':  YearDependentContainer({'UL18': 1000}),
    }
    modes = [['standard'],['pfcands'], ['extrajets'], ['allgenparticles'], ['standard','extrajets']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


'''
