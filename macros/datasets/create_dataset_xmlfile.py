#! /usr/bin/env python

# Adapted from the UHH2 framework: https://github.com/UHH2/UHH2/blob/RunII_102X_v2/scripts/create-dataset-xmlfile

import sys, glob, ROOT
from utils import green, yellow

def main():
    datasets = {
    'MC_LQDM_MLQ1000_MX440_MDM400_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1000_MX440_MDM400_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1100_MX495_MDM450_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1100_MX495_MDM450_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1200_MX550_MDM500_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1200_MX550_MDM500_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1300_MX605_MDM550_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1300_MX605_MDM550_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1400_MX660_MDM600_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1500_MX715_MDM650_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1500_MX715_MDM650_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1600_MX770_MDM700_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1600_MX770_MDM700_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1700_MX825_MDM750_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1700_MX825_MDM750_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1800_MX880_MDM800_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1800_MX880_MDM800_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ1900_MX935_MDM850_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ1900_MX935_MDM850_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ2000_MX990_MDM900_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ2000_MX990_MDM900_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ600_MX220_MDM200_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ600_MX220_MDM200_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ700_MX275_MDM250_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ700_MX275_MDM250_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ800_MX330_MDM300_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ800_MX330_MDM300_L1p0/Tuples_GENSIM_*.root',
    'MC_LQDM_MLQ900_MX385_MDM350_L1p0.xml': '/pnfs/psi.ch/cms/trivcat/store/user/areimers/UL17/Tuples_GENSIM/LQDM/LQDM_MLQ900_MX385_MDM350_L1p0/Tuples_GENSIM_*.root'
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
        # out.write('<InputFile FileName="%s"/>\n' % filename)
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
