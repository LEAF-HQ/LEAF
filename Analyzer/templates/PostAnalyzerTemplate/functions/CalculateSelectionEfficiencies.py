
import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
import ROOT
from ROOT import gROOT, TFile, TCanvas, TLatex, TH1D, TTree, TGraph, TGraphAsymmErrors, kBlack, kOrange, kGreen, kRed, kAzure, kViolet, TGraphAsymmErrors, kFullCircle, kOpenCircle, kError
from tdrstyle_all import *

def CalculateSelectionEfficiencies(self, num_and_denom, signals, backgrounds):
    print green('  --> Producing selection efficiencies.')
    gROOT.SetBatch(1)
    ROOT.gErrorIgnoreLevel = kError
    setTDRStyle()

    processes = signals + backgrounds

    graphs = OrderedDict()
    for proc in processes:
        infilename = os.path.join(self.inputpath, 'MC__'+proc+'.root')
        infile = TFile(infilename, 'READ')

        h_pass = TH1D('h_num', ';;Selection efficiency', len(num_and_denom), 0, len(num_and_denom))
        h_total = TH1D('h_denom', ';;Selection efficiency', len(num_and_denom), 0, len(num_and_denom))
        for i, (n, d) in enumerate(num_and_denom):
            h_pass.GetXaxis().SetBinLabel(i+1,n)
            h_total.GetXaxis().SetBinLabel(i+1,n)

        histname = 'sumweights'
        for i, (num, denom) in enumerate(num_and_denom):
            histfoldername_num = '_'.join([num, 'General'])
            histfoldername_denom = '_'.join([denom, 'General'])
            h_num = infile.Get(os.path.join(histfoldername_num, histname))
            h_denom = infile.Get(os.path.join(histfoldername_denom, histname))
            h_pass.SetBinContent(i+1, float(h_num.GetBinContent(1)))
            h_total.SetBinContent(i+1, float(h_denom.GetBinContent(1)))
            h_pass.SetBinError(i+1, float(h_num.GetBinError(1)))
            h_total.SetBinError(i+1, float(h_denom.GetBinError(1)))

        g = h_pass.Clone('ratio')
        g.SetDirectory(0)
        g.Divide(h_total)
        graphs[proc] = g

    c = TCanvas('c', 'c', 50, 50, 600, 600)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)
    c.SetTopMargin(0.05)
    c.SetBottomMargin(0.14)
    c.SetLeftMargin(0.16)
    c.SetRightMargin(0.07)

    haxis = graphs[graphs.keys()[0]]
    haxis.SetMaximum(1.2)
    haxis.SetMinimum(0.)
    haxis.Draw('AXIS')
    legend = tdrLeg(0.45,0.65,0.95,0.9, textSize=0.025)
    for i, proc in enumerate(graphs):
        legtext = legends[proc]
        lstyle = 1
        tdrDraw(graphs[proc], "E", marker=kFullCircle, mcolor=self.samples[proc].color, lcolor=self.samples[proc].color, fstyle=0, lstyle=self.samples[proc].linestyle)
        legend.AddEntry(graphs[proc], self.samples[proc].legendtext, 'LP')

    plotoutname = 'SelectionEfficiencies.pdf'
    c.SaveAs(os.path.join(self.plotoutput_path, plotoutname))

    haxis.SetMaximum(1E2)
    haxis.SetMinimum(1E-4)
    c.SetLogy()
    c.SaveAs(os.path.join(self.plotoutput_path, plotoutname.replace('.pdf', '_logy.pdf')))




#
