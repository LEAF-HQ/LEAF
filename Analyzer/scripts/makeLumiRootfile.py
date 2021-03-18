#!/usr/bin/env python

import os, sys, math, time, argparse
import json
from yaml import safe_load
import ROOT
from ROOT import TFile, TTree
from array import array
from utils import green as green


# Usage: ./makeLumiRootfile.py -i <JSON_FILE_NAME.txt> (-o <OUTFILENAME.root>)
# If no outfilename is give, it will be the same as the infilename, but with '.txt' replaced by '.root'.

def main():
    parser = argparse.ArgumentParser(description='Program that takes as an argument the json -->.txt<-- file and makes a root file out of it, which can be used with the main framework.')
    parser.add_argument('--input', '-i' , required=True, type=str, help='Name of the json converted to a .txt file')
    parser.add_argument('--output', '-o', type=str, help='Name of the target .root file')

    args = parser.parse_args()
    infilename  = os.path.abspath(args.input)
    if not infilename.endswith('.txt'):
        raise ValueError('Infilename does not end with .txt')
    outfilename = os.path.abspath(args.output) if args.output is not None else '.root'.join(infilename.rsplit('.txt', 1))

    with open(infilename, 'r') as f:
        dict_in_json = safe_load(f)

    outfile = TFile(outfilename, 'RECREATE')
    outtree = TTree("LumiTree","LumiTree")
    t_run     = array('i',[0])
    t_lb_low  = array('i',[0])
    t_lb_high = array('i',[0])

    outtree.Branch("run",     t_run,     'run number/i')
    outtree.Branch("lb_low",  t_lb_low,  'lumi block low number (including this one)/i')
    outtree.Branch("lb_high", t_lb_high, 'lumi block high number (including this one)/i')
    runs = dict_in_json.keys()
    for run in dict_in_json:
        parts = dict_in_json[run]
        # print parts
        for lumiblocks in parts:
            t_run[0]     = int(run)
            t_lb_low[0]  = int(lumiblocks[0])
            t_lb_high[0] = int(lumiblocks[1])
            outtree.Fill()
            # for lb in range(lumiblocks[0], lumiblocks[1]+1):
            #     t_run[0] = int(run)
            #     t_lb[0]  = int(lb)
            #     outtree.Fill()
                # print 'filled: (%i, %i)' % (int(run), int(lb))

    outfile.Write()
    outfile.Close()
    print green('--> Successfully created lumifile \'%s\'' % (outfilename))



if __name__ == '__main__':
    main()
