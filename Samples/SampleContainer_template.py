from Sample import *
from Storage import *

'''
Define template to store ntuple info
'''

def get_common_path():
    return 'Summer20/MINIAODv2/NTuples_v02/'

def get_storage_path(prefix, year, common_path, mode, sample_name):
    return os.path.join(prefix, year, common_path, mode, sample_name)

def Add_Generic_Sample(SampleContainer, sample_name, modes, years, storage, ntuple_folder_base, common_path, default_info):

    for mode in modes:
        mode_name = '_plus_'.join(mode)
        default_info['name']       = sample_name+'_'+mode_name
        default_info['tuplepaths'] = YearDependentContainer(dict((year,storage(get_storage_path(ntuple_folder_base,  year, common_path, mode_name, sample_name))       ) for year in years))
        default_info['xmlfiles']   = YearDependentContainer(dict((year,          get_storage_path('Analyzer/datasets/', year, common_path, mode_name, sample_name)+'.xml') for year in years))
        default_info['contents']   = YearDependentContainer(dict.fromkeys(years, mode))
        SampleContainer.add_samples({sample_name+'_'+mode_name: Sample(**default_info)})


def Add_MC(SampleContainer, sample_name, group_name, nevents_das, DAS_Names, modes):
    years = DAS_Names.keys()
    default_info = {
        'type': 'MC', 'minipaths': YearDependentContainer(dict((k, Storage_DAS(v)) for k, v in DAS_Names.items())),
        'group': YearDependentContainer(dict.fromkeys(years, group_name)),
        'xsecs':             YearDependentContainer(dict((y, nevents_das[y]['xsecs']) for y in years)),
        'nevents_das':       YearDependentContainer(dict((y, nevents_das[y]['das']) for y in years)),
        'nevents_generated': YearDependentContainer(dict((y, nevents_das[y]['generated']) for y in years)),
        'nevents_weighted':  YearDependentContainer(dict((y, nevents_das[y]['weighted']) for y in years)),
    }
    Add_Generic_Sample(SampleContainer, sample_name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


def TransformDasName_Dummy(name,sample,year,run):
    return name

def Add_Data(SampleContainer, sample_name, group_name, nevents_das, DAS_Names, modes, transform=TransformDasName_Dummy):
    year_run_map= dict((k, sorted(v['das'].keys())) for k, v in nevents_das.items())
    runs = sorted(list(set(sum(year_run_map.values(), []))))
    for run in runs:
        name = sample_name+'_Run'+run
        das_names = dict((k, Storage_DAS(transform(name=v,sample=sample_name,year=k,run=run))) for k, v in DAS_Names.items() if run in year_run_map[k])
        if len(das_names)==0: continue
        years = sorted(das_names.keys())
        default_info = {
            'type': 'DATA', 'minipaths': YearDependentContainer(das_names),
            'group': YearDependentContainer(dict.fromkeys(years, group_name)),
            'nevents_das':       YearDependentContainer(dict((y, nevents_das[y]['das'][run]) for y in years)),
            'nevents_generated': YearDependentContainer(dict((y, nevents_das[y]['generated'][run]) for y in years)),
            'nevents_weighted':  YearDependentContainer(dict((y, nevents_das[y]['generated'][run]) for y in years)),
        }
        Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


'''
Example of usage

modes = [['standard']]

def Add_DY(SampleContainer):
    sample_name = 'DYJetsToLL_M-50'
    DAS_Names = {
        'UL18': '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM',
        }
    nevents_das={
        'UL18':{'das':196626007,'generated':-1,'weighted':-1},
    }
    Add_MC(SampleContainer, sample_name,nevents_das, DAS_Names,modes)


def Add_Data_SingleMuon(SampleContainer):
    sample_name = 'SingleMuon'
    nevents_das={
        'UL18':{'A':241596817, 'B':119918017, 'C':110032072, 'D':513884680,},
    }
    DAS_Names = {
        'UL18': '/SingleMuon/Run2018RUN-UL2018_MiniAODv2_GT36-v1/MINIAOD',
        }
    Add_Data(SampleContainer, sample_name, nevents_das, DAS_Names,modes, transform=GetDasName)

'''
