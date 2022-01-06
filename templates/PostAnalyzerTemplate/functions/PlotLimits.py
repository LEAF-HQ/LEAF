
import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
from ROOT import gROOT, TFile, TCanvas, TH1D, TTree, TGraph, TGraphAsymmErrors, kBlack, kOrange, kGreen, kRed
from array import array
from tdrstyle_all import *
import constants

def PlotLimits(self, signal_scaled_by=1., draw_observed=False, draw_theory=False):
    print green('  --> Plotting %s limits.' % ('expected' if not draw_observed else 'expected and observed'))
    # Expects all signals to belong to the same process!

    gROOT.SetBatch(1)

    #LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0
    limits_and_quantiles_per_mass = {}
    for signal in self.signals:
        parts = signal.split('_')
        signaltag = ''
        signalmass = -1
        for part in parts:
            if not self.signalmass_identifier in part:
                if signaltag == '': signaltag = part
                else: signaltag = '_'.join([signaltag, part])
            else:
                signalmass = part[len(self.signalmass_identifier):]
                break

        print signaltag, signalmass
        limits_and_quantiles_per_mass[int(signalmass)] = {}
        combinefilename = os.path.join(self.combineoutput_path, 'higgsCombine%s.AsymptoticLimits.mH%s.root' % (signaltag, signalmass))
        rootfile = TFile(combinefilename, 'READ')

        tree = rootfile.Get('limit')
        for i in range(tree.GetEntries()):
            tree.GetEntry(i)
            limits_and_quantiles_per_mass[int(signalmass)][tree.quantileExpected] = tree.limit
        rootfile.Close()

    g_expected = TGraph()
    g_68 = TGraphAsymmErrors()
    g_95 = TGraphAsymmErrors()
    npoints_expected = npoints_68 = npoints_95 = 0
    for mass in sorted(limits_and_quantiles_per_mass):
        expected = low_68 = high_68 = low_95 = high_95 = obs = -1.
        for quant in limits_and_quantiles_per_mass[mass]:
            if quant < 0: obs = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by
            elif quant < 0.0251: low_95 = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by
            elif quant < 0.161: low_68 = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by
            elif quant < 0.51: expected = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by
            elif quant < 0.85: high_68 = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by
            elif quant < 0.98: high_95 = limits_and_quantiles_per_mass[mass][quant] * signal_scaled_by

        g_expected.SetPoint(npoints_expected, mass, expected)
        g_68.SetPoint(npoints_68, mass, expected)
        g_95.SetPoint(npoints_95, mass, expected)
        g_68.SetPointError(npoints_68, 0., 0., expected-low_68, high_68-expected)
        g_95.SetPointError(npoints_95, 0., 0., expected-low_95, high_95-expected)
        npoints_expected += 1
        npoints_68 += 1
        npoints_95 += 1

    # get theory graphs -- getting theory lines from files needs to be implemented
    if draw_theory:
        pass

    yaxis_title = '#sigma (pp #rightarrow %s) [pb]' % (signaltag)
    c = tdrCanvas(canvName='c', x_min=min(limits_and_quantiles_per_mass), x_max=max(limits_and_quantiles_per_mass), y_min=1E-5, y_max=1E4, nameXaxis='M_{LQ} [GeV]', nameYaxis=yaxis_title, square=True, iPeriod=0, iPos=11)
    c.SetLogy()
    leg = tdrLeg(0.5,0.65,0.85,0.9, textSize=0.042)
    tdrHeader(leg, '95% CL upper limits')
    tdrDraw(g_95, "3 SAME", mcolor=kOrange, lcolor=kOrange, fcolor=kOrange)
    tdrDraw(g_68, "3 SAME", mcolor=kGreen+1, lcolor=kGreen+1, fcolor=kGreen+1)
    tdrDraw(g_expected, "L SAME", mcolor=kBlack, lcolor=kBlack, fcolor=kBlack, lstyle=2)
    if draw_theory: # drawing theory lines needs to be implemented
        pass
    leg.AddEntry(g_expected, 'Median expected', 'L')
    leg.AddEntry(g_68, '68% expected', 'F')
    leg.AddEntry(g_95, '95% expected', 'F')
    leg.Draw('SAME')
    if draw_theory: # adding theory lines to legend needs to be implemented
        leg_theory = tdrLeg(0.5,0.4,0.85,0.65, textSize=0.042)
        tdrHeader(leg_theory, 'Theory prediction')
        leg_theory.Draw('SAME')
    c.RedrawAxis()
    outname = os.path.join(self.plotoutput_path, 'Limits.pdf')
    c.SaveAs(outname)
    if draw_theory: # closing cross section input file needs to be implemented
        pass
