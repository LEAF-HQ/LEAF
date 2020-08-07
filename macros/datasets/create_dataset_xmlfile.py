#! /usr/bin/env python

# Adapted from the UHH2 framework: https://github.com/UHH2/UHH2/blob/RunII_102X_v2/scripts/create-dataset-xmlfile

import sys, glob, ROOT
from utils import green, yellow

def main():
    datasets = {

    'LQLQToBTau_MLQ1000_MPS574_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTau_MLQ1000_MPS574_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTau_MLQ1900_MPS1064_MC1794_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTau_MLQ1900_MPS1064_MC1794_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTauPsiChi_MLQ1000_MPS574_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTauPsiChi_MLQ1000_MPS574_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToPsiChi_MLQ1900_MPS1064_MC1794_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToPsiChi_MLQ1900_MPS1064_MC1794_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTauPsiChi_MLQ1900_MPS1064_MC1794_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTauPsiChi_MLQ1900_MPS1064_MC1794_L1p0/Tuples_GENSIM_*.root',
    'LQLQToPsiChi_MLQ1000_MPS574_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToPsiChi_MLQ1000_MPS574_MC1427_L1p0/Tuples_GENSIM_*.root',
    'LQLQToBTau_MLQ1000_MPS983_MC1912_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQLQToBTau_MLQ1000_MPS983_MC1912_L1p0/Tuples_GENSIM_*.root',
    'PsiPsiToLQChi_MLQ1000_MPS574_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/PsiPsiToLQChi_MLQ1000_MPS574_MC1427_L1p0/Tuples_GENSIM_*.root',
    'PsiPsiToLQChi_MLQ1000_MPS983_MC1912_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/PsiPsiToLQChi_MLQ1000_MPS983_MC1912_L1p0/Tuples_GENSIM_*.root',
    'PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0/Tuples_GENSIM_*.root',
    'PsiPsiToLQChi_MLQ1900_MPS1064_MC1794_L1p0.xml' : '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/PsiPsiToLQChi_MLQ1900_MPS1064_MC1794_L1p0/Tuples_GENSIM_*.root'
    }

    for outfilename in datasets.keys():
        print green('--> Using pattern %s to create xml-file %s' % (datasets[outfilename], outfilename))
        create_single_xmlfile(datasets[outfilename], outfilename)


def create_single_xmlfile(inputfilepattern, outputfilename):
    out = open(outputfilename, 'w')
    l = glob.glob(inputfilepattern)
    print green("    --> Found %d files matching inputfilepattern" % len(l))
    l.sort()
    nevents = 0
    for filename in l:
        f = ROOT.TFile(filename)
        if f.Get('AnalysisTree').GetEntriesFast() > 0:
            out.write('<InputFile FileName="%s"/>\n' % filename)
            nevents += f.Get('AnalysisTree').GetEntries()
        else:
            print yellow('No events found in file \'%s\'.' % filename)
        f.Close()
    out.write('<!-- Weighted number of events: %d -->\n' % nevents)
    out.close()





if __name__ == '__main__':
    main()
