#!/usr/bin/env python
"""
DBS 3 Client Example.   This script is called

python GetDasInfo.py '/*/*Fall13-POST*/GEN-SIM'

"""

import argparse, pprint
from collections import OrderedDict
import CRABClient
from dbs.apis.dbsClient import DbsApi

def GetDasInfo(datasets, options):
    url = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader'
    api = DbsApi(url = url)
    outputDataSets = OrderedDict((dict_['dataset'], '') for dataset in datasets for dict_ in api.listDatasets(dataset = dataset))
    for dataset in outputDataSets:
        reply = api.listBlockSummaries(dataset = dataset)
        outputDataSets[dataset] = dict(filter(lambda elem: elem[0] in options, reply[0].items()))
        if 'list_files' in options:
            outputDataSets[dataset]['list_files'] = [file['logical_file_name'] for file in api.listFiles(dataset=dataset)]
    return outputDataSets


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("datasets", nargs="+", default=[])
    parser.add_argument("--options", nargs="+", default=['num_event'])

    args = parser.parse_args()
    outputDataSets = GetDasInfo(datasets=args.datasets, options=args.options)
    for dataset, info in outputDataSets.items():
        print(dataset, info)



if __name__ == "__main__":
    main()
