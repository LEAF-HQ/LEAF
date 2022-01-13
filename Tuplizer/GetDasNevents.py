#!/usr/bin/env python
"""
DBS 3 Client Example.   This script is called

python GetDasNevents.py '/*/*Fall13-POST*/GEN-SIM'

"""

import  sys
import CRABClient
from dbs.apis.dbsClient import DbsApi

def GetDasNevents(dataset, options=['num_event']): #num_file
    url = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader'
    api = DbsApi(url = url)
    outputDataSets = api.listDatasets(dataset = dataset)
    for dataset in outputDataSets:
        inp = dataset['dataset']
        reply =  api.listBlockSummaries(dataset = inp)
        reply = dict(filter(lambda elem: elem[0] in options, reply[0].items()))
        print (inp, reply)


def main():
    args = sys.argv[1:]
    data = args[0]
    GetDasNevents(data)


if __name__ == "__main__":
    main()
