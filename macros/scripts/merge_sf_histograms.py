import os, sys
import subprocess
import time
import ROOT
from ROOT import kError, TFile, TGraphAsymmErrors, Double, TH2D
import array

infolder = '/work/areimers/LEAF/macros/data/2017'
graphname = 'ScaleFactors'
# outfilename = 'ElectronTRIGGER.root'
# infilenames = ['ElectronTriggerScaleFactors_eta_ele_binned_official_pt30to200_withsyst.root', 'ElectronTriggerScaleFactors_eta_ele_binned_official_pt200toInf.root'] #HAVE TO BE ORDERED
# xaxislabel = '#eta^{e}'
# yaxislabel = 'p_{T}^{e} [GeV]'
# y_bins = [30, 200, 500]
outfilename = 'MuonTRIGGER.root'
infilenames = ['MuonTriggerScaleFactors_pt_mu_binned_official_eta0to0p9_withsyst.root', 'MuonTriggerScaleFactors_pt_mu_binned_official_eta0p9to1p2_withsyst.root', 'MuonTriggerScaleFactors_pt_mu_binned_official_eta1p2to2p1_withsyst.root', 'MuonTriggerScaleFactors_pt_mu_binned_official_rebin_eta2p1to2p4_withsyst.root'] #HAVE TO BE ORDERED
xaxislabel = 'p_{T}^{#mu} [GeV]'
yaxislabel = '#eta^{#mu}'
y_bins = [0, 0.9, 1.2, 2.1, 2.4]

infiles = []
for name in infilenames:
    infile = TFile(os.path.join(infolder, name), 'READ')
    infiles.append(infile)

graphs = []
x_bins = []
sfs = []
errs = []
for i, f in enumerate(infiles):
    sfs.append({})
    errs.append({})
    graph = f.Get(graphname)
    graphs.append(graph)
    for point in range(graph.GetN()):
        x = ROOT.Double(0.)
        y = ROOT.Double(0.)
        graph.GetPoint(point, x, y)
        xerrhi = graph.GetErrorXhigh(point)
        xerrlo = graph.GetErrorXlow(point)
        yerr = max(graph.GetErrorYhigh(point), graph.GetErrorYlow(point))
        binedgelo = x - xerrlo
        binedgehi = x + xerrhi
        if not binedgelo in x_bins: x_bins.append(binedgelo)
        if not binedgehi in x_bins: x_bins.append(binedgehi)
        sfs[i][(binedgelo, binedgehi)] = y
        errs[i][(binedgelo, binedgehi)] = yerr


if len(y_bins) is not (len(graphs)+1): raise ValueError('Incoherent number of graphs and y-bins')
print sorted(x_bins)
outhist = TH2D('ScaleFactors', 'Merged scale factors;%s;%s;scale factor'%(xaxislabel, yaxislabel), len(x_bins)-1, array.array('d', sorted(x_bins)), len(y_bins)-1, array.array('d', y_bins))
for i in range(len(sfs)):
    ybin = i+1
    for (xlo, xhi) in sfs[i]:
        sf = sfs[i][(xlo, xhi)]
        err = errs[i][(xlo, xhi)]
        for finebin in range(outhist.GetNbinsX()):
            if outhist.GetXaxis().GetBinLowEdge(finebin+1) >= xlo and outhist.GetXaxis().GetBinUpEdge(finebin+1) <= xhi:
                # print 'filling', xlo, xhi, outhist.GetXaxis().GetBinLowEdge(finebin+1), outhist.GetXaxis().GetBinUpEdge(finebin+1), sf, err
                outhist.SetBinContent(finebin+1, ybin, sf)
                outhist.SetBinError(finebin+1, ybin, err)

outfile = TFile(os.path.join(infolder, outfilename), 'RECREATE')
outhist.Write()
outfile.Close()
