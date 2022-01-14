#!/usr/bin/env python
"""
DBS 3 Client Example.   This script is called

python GetDasNevents.py '/*/*Fall13-POST*/GEN-SIM'

"""

import argparse, pprint
from collections import OrderedDict
import CRABClient
from dbs.apis.dbsClient import DbsApi

def GetDasNevents(datasets, options):
    url = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader'
    api = DbsApi(url = url)
    outputDataSets = OrderedDict((dict_['dataset'], '') for dataset in datasets for dict_ in api.listDatasets(dataset = dataset))
    for dataset in outputDataSets:
        reply = api.listBlockSummaries(dataset = dataset)
        outputDataSets[dataset] = dict(filter(lambda elem: elem[0] in options, reply[0].items()))
    return outputDataSets


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("datasets", nargs="+", default=[])
    parser.add_argument("--options", nargs="+", default=['num_event'])

    args = parser.parse_args()
    outputDataSets = GetDasNevents(datasets=args.datasets, options=args.options)
    for dataset, info in outputDataSets.items():
        print(dataset, info)



if __name__ == "__main__":
    main()
