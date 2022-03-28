import argparse
from yaml import safe_load
from GetDasInfo import GetDasInfo
from VBFTagger.Tuplizer.Signals_VBF import *
from utils import blue, yellow, green


def VerifyDasInfo(filename, year, stage='mini'):

    AllSamples = SampleContainer()
    Add_Signals_VBFAnalysis(AllSamples)
    # print AllSamples.keys()

    with open(filename) as f:
        stored_info = safe_load(f)
        for dataset, info in stored_info.items():
            dataset_info = AllSamples.get_sample(dataset).get_var_for_year(stage+'paths',year)
            das_path = dataset_info.path
            director = dataset_info.director
            das_info = GetDasInfo(datasets=[das_path], options=['num_event','num_file', 'list_files'])
            das_info[das_path]['list_files'] = [director+x for x in das_info[das_path]['list_files']]
            print(blue(dataset+' has '+str(das_info[das_path]['num_file'])))
            if len(info) != das_info[das_path]['num_file']:
                missing_files = list(set(das_info[das_path]['list_files'])-set(info.keys()))
                print(yellow('  --> missing: '+str(len(missing_files))))
                print(yellow('\n'.join(missing_files)))
            else: print(green('  --> All files counted.'))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--json',  '-j', action='store', dest='json',  type=str, default='Workarea/filelist_mini_UL18.json')
    parser.add_argument('--year',  '-y', action='store', dest='year',  type=str, default='UL18')
    parser.add_argument('--stage', '-s', action='store', dest='stage', type=str, default='mini')
    args = parser.parse_args()
    VerifyDasInfo(filename=args.json, year=args.year, stage=args.stage)



if __name__ == "__main__":
    main()
