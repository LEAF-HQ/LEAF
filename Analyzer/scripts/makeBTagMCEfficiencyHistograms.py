#!/usr/bin/env python

import os, glob, sys, math, time, argparse
import ROOT
from ROOT import TFile, TTree, TH2D



def main():
    parser = argparse.ArgumentParser(description='Program that takes as an argument a pattern of LEAF rootfiles (* wildcards work) enclosed by quotation marks ("<pattern>") and creates a rootfile with the MC b-tagging efficiencies. Assumes the b-tagging MC efficiency histogram folder inside the root files is called "BTaggingMCEfficiencies".')
    parser.add_argument('--input',  '-i', required=True, type=str, help='Name of the json converted to a .txt file')
    parser.add_argument('--output', '-o', type=str, help='Name of the output .root file. Default is "BTaggingMCEfficiencies.root"')

    args = parser.parse_args()
    infilepattern  = os.path.abspath(args.input)
    outfilename = os.path.abspath(args.output) if args.output is not None else 'BTaggingMCEfficiencies.root'

    infilenames = glob.glob(infilepattern)
    foldername = 'BTaggingMCEfficiencies'

    btag_histo_names = ['b_passing', 'b_total', 'c_passing', 'c_total', 'udsg_passing', 'udsg_total']

    merged_histograms = []
    for idx, infilename in enumerate(infilenames):
        infile = TFile(infilename, 'READ')
        for idx_hist, name in enumerate(btag_histo_names):
            histname = foldername + '/' + name
            if idx == 0:
                hist = infile.Get(histname)
                merged_histograms.append(hist)
                hist.SetDirectory(0)
                # if idx_hist == 5: print 'number of new entries:', hist.GetEntries()
            else:
                merged_histograms[idx_hist].Add(infile.Get(histname))
                thishist = infile.Get(histname)
                # if idx_hist == 5: print 'number of new entries:', thishist.GetEntries()
        # print 'number of entries merged:', merged_histograms[5].GetEntries()
    # print merged_histograms

    outfile = TFile(outfilename, 'RECREATE')
    # outhists = []
    for idx, name in enumerate(btag_histo_names):
        if 'passing' in name:
            num = merged_histograms[idx]
            for hist in merged_histograms:
                if hist.GetName() == num.GetName().replace('passing', 'total'):
                    den = hist
            print num.GetBinContent(4,1), den.GetBinContent(4,1)
            num.Divide(den)
            print num.GetBinContent(4,1)
            num.SetName(num.GetName().replace('passing', 'efficiency'))
            num.Write()
    outfile.Close()













if __name__ == '__main__':
    main()
