#! /usr/bin/env python
# Author: Yuta Takahashi
# Description: converts GENSIM sample to a simplified format for generator-level analysis
# http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
# ./convertGENSIM.py /pnfs/psi.ch/cms/trivcat/store/user/ineuteli/samples/SLQ-s_M-1000_MGP_GENSIM/*GENSIM*.root -o checkGENSIM/SLQ-s_M-1000_MGP_LOPDF_CP2_GENSIM_simple2.root -n 100
# ./convertGENSIM.py /pnfs/psi.ch/cms/trivcat/store/user/ineuteli/samples/SLQ-s_M-1000_MGonly_GENSIM/*GENSIM*.root -o checkGENSIM/SLQ-s_M-1000_MGonly_LOPDF_CP2_GENSIM_simple2.root -n 100
import time
start = time.time()
import os, sys, glob, copy, math
from math import log, ceil, exp
import ROOT; ROOT.PyConfig.IgnoreCommandLineOptions = True
from ROOT import TFile, TH1F, TTree, gStyle, TH2F, TList, TObject, TObjArray
from DataFormats.FWLite import Events, Handle
import numpy as num
from utils import *
from array import array

from argparse import ArgumentParser
usage = """Converts GENSIM sample to a simplified format for generator-level analysis."""
parser = ArgumentParser(prog="fragment_GS", description=usage, epilog="Success!")
parser.add_argument('infiles',         nargs='*',
                    metavar='INFILE',  help="signal to generate events for" )
parser.add_argument('-o', '--out',     dest='outfile', type=str, default=None, action='store',
                    metavar='OUTFILE', help="output file" )
parser.add_argument('-n', '--nmax',    dest='Nmax', type=int, default=-1, action='store',
                                       help="number of event to be generated in each job" )
args      = parser.parse_args()

gStyle.SetOptStat(11111)
decaydict = { 'ele': 0, 'muon': 1, 'tau': 2 }

# root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_1.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_2.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_3.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_4.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_5.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_6.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_7.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_8.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_9.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_10.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_11.root root://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQTChannel/LQTChannelTauNu_CP2_M3000/GENSIM_12.root

def main():

  # SETTING
  director  = 'root://t3dcachedb.psi.ch:1094/'
  indir     = "/pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM"
  Nmax      = args.Nmax
  infileset = [ ]

  # USER FILES
  if args.infiles:
    infiles = [director+f if f.startswith('/pnfs/psi.ch/cms') else f for f in args.infiles]
    if args.outfile:
      outfile = args.outfile
    else:
      print red('No outfile specified, abort.')
      raise ValueError()
    infileset.append(("User input",infiles,outfile))
  else:
    raise IOError("No input given to run on.")

  # CONVERT
  for title, infiles, outfile in infileset:
    print ">>> %s"%bold(title)
    print ">>>   input files:"
    for file in infiles:
      print ">>>     %s"%(file)
    print ">>>   output file: %s"%(outfile)
    convertGENSIM(infiles,outfile,Nmax=Nmax)
    print ">>> "

  print ">>>   done in in %s"%(formatTime(time.time()-start))


def convertGENSIM(infiles,outfilename,Nmax=-1):
  """Loop over GENSIM events and save custom trees."""
  start1 = time.time()

  lqids = [9000008, 9000009]
  xids  = [9000006, 9000007]
  dmids = [9000005]

  print ">>>   loading files..."
  events  = Events(infiles)
  outfile = TFile(outfilename, 'RECREATE')

  print ">>>   creating trees and branches..."
  tree_event  = TTree('event',   'event')
  tree_jet    = TTree('jet',     'jet')
  tree_jet_raw= TTree('jet_raw', 'jet_raw')

  # EVENT
  tree_event.addBranch('nbgen',          'i')
  tree_event.addBranch('nbcut',          'i')
  tree_event.addBranch('nbcut50',        'i')
  tree_event.addBranch('njet',           'i')
  tree_event.addBranch('ntau',           'i')
  tree_event.addBranch('ntaucut',        'i')
  tree_event.addBranch('ntaucut50',      'i')
  tree_event.addBranch('ntaucut_vis',    'i')
  tree_event.addBranch('ntaucut50_vis',  'i')
  tree_event.addBranch('nlq',            'i')
  tree_event.addBranch('ndm',            'i')
  tree_event.addBranch('nx',             'i')
  tree_event.addBranch('met_pt',         'f')
  tree_event.addBranch('met_phi',        'f')
  tree_event.addBranch('jet1_mass',      'f')
  tree_event.addBranch('jet2_mass',      'f')
  tree_event.addBranch('jet3_mass',      'f')
  tree_event.addBranch('jet1_pt',        'f')
  tree_event.addBranch('jet2_pt',        'f')
  tree_event.addBranch('jet3_pt',        'f')
  tree_event.addBranch('jet1_eta',       'f')
  tree_event.addBranch('jet2_eta',       'f')
  tree_event.addBranch('jet3_eta',       'f')
  tree_event.addBranch('jet1_phi',       'f')
  tree_event.addBranch('jet2_phi',       'f')
  tree_event.addBranch('jet3_phi',       'f')
  tree_event.addBranch('sumjet',         'f')
  tree_event.addBranch('dphi_jj',        'f')
  tree_event.addBranch('deta_jj',        'f')
  tree_event.addBranch('dr_jj',          'f')
  tree_event.addBranch('mjj',            'f')
  tree_event.addBranch('lq1_mass',       'f')
  tree_event.addBranch('lq2_mass',       'f')
  tree_event.addBranch('lq1_pt',         'f')
  tree_event.addBranch('lq2_pt',         'f')
  tree_event.addBranch('lq1_eta',        'f')
  tree_event.addBranch('lq2_eta',        'f')
  tree_event.addBranch('lq1_phi',        'f')
  tree_event.addBranch('lq2_phi',        'f')
  tree_event.addBranch('dm1_mass',       'f')
  tree_event.addBranch('dm2_mass',       'f')
  tree_event.addBranch('dm1_pt',         'f')
  tree_event.addBranch('dm2_pt',         'f')
  tree_event.addBranch('dm1_eta',        'f')
  tree_event.addBranch('dm2_eta',        'f')
  tree_event.addBranch('dm1_phi',        'f')
  tree_event.addBranch('dm2_phi',        'f')
  tree_event.addBranch('b1_mass',        'f')
  tree_event.addBranch('b2_mass',        'f')
  tree_event.addBranch('b1_pt',          'f')
  tree_event.addBranch('b2_pt',          'f')
  tree_event.addBranch('b1_eta',         'f')
  tree_event.addBranch('b2_eta',         'f')
  tree_event.addBranch('b1_phi',         'f')
  tree_event.addBranch('b2_phi',         'f')
  tree_event.addBranch('x_mass',         'f')
  tree_event.addBranch('x_pt',           'f')
  tree_event.addBranch('x_eta',          'f')
  tree_event.addBranch('x_phi',          'f')
  tree_event.addBranch('m_lqlq',         'f')
  tree_event.addBranch('tau1_mass',      'f')
  tree_event.addBranch('tau2_mass',      'f')
  tree_event.addBranch('tau1_pt',        'f')
  tree_event.addBranch('tau2_pt',        'f')
  tree_event.addBranch('tau1_eta',       'f')
  tree_event.addBranch('tau2_eta',       'f')
  tree_event.addBranch('tau1_phi',       'f')
  tree_event.addBranch('tau2_phi',       'f')
  tree_event.addBranch('tau1_y',         'f')
  tree_event.addBranch('tau2_y',         'f')
  tree_event.addBranch('tau1_massvis',   'f')
  tree_event.addBranch('tau2_massvis',   'f')
  tree_event.addBranch('tau1_ptvis',     'f')
  tree_event.addBranch('tau2_ptvis',     'f')
  tree_event.addBranch('tau1_etavis',    'f')
  tree_event.addBranch('tau2_etavis',    'f')
  tree_event.addBranch('tau1_phivis',    'f')
  tree_event.addBranch('tau2_phivis',    'f')
  tree_event.addBranch('ditau_dy',       'f')
  tree_event.addBranch('ditau_chi',      'f')
  tree_event.addBranch('m_tauvis1_jet1', 'f')
  tree_event.addBranch('st',             'f') # scalar sum pT
  tree_event.addBranch('st_met',         'f') # scalar sum pT with MET
  # tree_event.addBranch('jets_pt'  ,      'f', standard=False)
  # tree_event.addBranch('jets_eta' ,      'f', standard=False)
  # tree_event.addBranch('jets_phi' ,      'f', standard=False)
  # tree_event.addBranch('jets_mass',      'f', standard=False)

  tree_event.addBranch('weight',         'f')
  tree_event.addBranch('event_id',       'i')
  tree_event.addBranch('qscale',         'f')

  # JETS raw
  tree_jet_raw.addBranch('mass',             'f')
  tree_jet_raw.addBranch('pt',               'f')
  tree_jet_raw.addBranch('eta',              'f')
  tree_jet_raw.addBranch('phi',              'f')
  tree_jet_raw.addBranch('weight',           'f')
  tree_jet_raw.addBranch('event_id',         'i')

  # JETS cleaned
  tree_jet.addBranch('mass',             'f')
  tree_jet.addBranch('pt',               'f')
  tree_jet.addBranch('eta',              'f')
  tree_jet.addBranch('phi',              'f')
  tree_jet.addBranch('weight',           'f')
  tree_jet.addBranch('event_id',         'i')

  handle_gps,    label_gps    = Handle('std::vector<reco::GenParticle>'), 'genParticles'
  handle_jets,   label_jets   = Handle('std::vector<reco::GenJet>'), 'ak4GenJets'
  handle_met,    label_met    = Handle('vector<reco::GenMET>'), 'genMetTrue'
  handle_weight, label_weight = Handle('GenEventInfoProduct'), 'generator'

  evtid = 0
  sec_per_evt = 0.023 # seconds per event
  Ntot = Nmax if Nmax>0 else events.size()
  print ">>>   start processing %d events, ETA %s..."%(Ntot,formatTimeShort(sec_per_evt*Ntot))
  step = stepsize(Ntot)
  start_proc = time.time()

  # LOOP OVER EVENTS
  for event in events:
      # print ' --- NEW EVENT'
      # print '='*30
      # print evtid
      if Nmax>0 and evtid>=Nmax: break
      if evtid>0 and evtid%step==0: print ">>>     processed %4s/%d events, ETA %s"%(evtid,Ntot,ETA(start_proc,evtid+1,Ntot))
      evtid += 1
      tree_event.event_id[0] = evtid

      event.getByLabel(label_gps,handle_gps)
      gps = handle_gps.product()

      event.getByLabel(label_jets,handle_jets)
      jets = handle_jets.product()

      event.getByLabel(label_met,handle_met)
      met = handle_met.product()

      event.getByLabel(label_weight,handle_weight)
      gweight = handle_weight.product()
      weight = gweight.weight()
      qscale = gweight.qScale()

      # GEN PARTICLES
      gps_final    = [p for p in gps if isFinal(p) and abs(p.pdgId()) in [5,6,15,16]+lqids + dmids + xids]
      gps_mother   = [p for p in gps_final if abs(p.pdgId()) in lqids and p.status()>60]
      gps_mother   .sort(key=lambda p: p.pt(), reverse=True)
      gps_dm       = [p for p in gps_final if abs(p.pdgId()) in dmids]
      gps_dm       .sort(key=lambda p: p.pt(), reverse=True)
      gps_x        = [p for p in gps_final if abs(p.pdgId()) in xids]
      gps_x        .sort(key=lambda p: p.pt(), reverse=True)

      gps_bgen     = [p for p in gps_final if abs(p.pdgId())==5 and p.status()==71]
      gps_bgen     .sort(key=lambda p: p.pt(), reverse=True)
      gps_bfromNP  = [p for p in gps if abs(p.pdgId())==5 and abs(p.mother(0).pdgId()) in lqids+dmids+xids]
      gps_bfromNP  .sort(key=lambda p: p.pt(), reverse=True)
      gps_bcut     = [p for p in gps_bgen  if p.pt()>20 and abs(p.eta())<2.5]
      gps_bcut50   = [p for p in gps_bgen  if p.pt()>50 and abs(p.eta())<2.5]

      gps_tau      = [p for p in gps_final if abs(p.pdgId())==15 and p.status()==2]
      gps_tau      .sort(key=lambda p: p.pt(), reverse=True)
      gps_taufromLQ= [p for p in gps if abs(p.pdgId())==15 and abs(p.mother(0).pdgId()) in lqids]
      gps_taufromLQ.sort(key=lambda p: p.pt(), reverse=True)
      gps_taucut   = [p for p in gps_tau   if p.pt()>20 and abs(p.eta())<2.5]
      gps_taucut50 = [p for p in gps_tau   if p.pt()>50 and abs(p.eta())<2.5]

      gps_tau_vis = []
      gps_taucut_vis = []
      gps_taucut50_vis = []
      # find taus that survive ptvis > 20 and >50 cuts
      for p in gps_tau:
        while p.status()!=2 :
          p = p.daughter(0)
        findau = finalDaughters(p, [])
        tauvisp4 = p4sumvis(findau)
        thisptvis = tauvisp4.pt()
        thisetavis = tauvisp4.eta()
        gps_tau_vis.append(tauvisp4)
        if thisptvis > 20 and abs(thisetavis) < 2.5: gps_taucut_vis.append(tauvisp4)
        if thisptvis > 50 and abs(thisetavis) < 2.5: gps_taucut50_vis.append(tauvisp4)
      gps_tau_vis     .sort(key=lambda p: p.pt(), reverse=True)
      gps_taucut_vis  .sort(key=lambda p: p.pt(), reverse=True)
      gps_taucut50_vis.sort(key=lambda p: p.pt(), reverse=True)


      # if not len(gps_bgen) == 2:
      #   print 'len, gps_mother = ', len(gps_mother)
      #   print 'number of b\'s: %i' % len(gps_bgen)
      #   print 'number of b\'s from NP decays: %i' % len(gps_bfromNP)
      #   if len(gps_mother) > 0:
      #     print '=' * 15 + ' NEW EVENT' + '='*15
      #     printDecayChain(gps_mother)
      #   continue

      # # REMOVE TOP QUARK if its final daughter is also in the list
      # for top in gps_tgen[:]:
      #   dau = top
      #   while abs(dau.daughter(0).pdgId())==6:
      #     dau = dau.daughter(0)
      #   if dau!=top and dau in gps_tgen:
      #     gps_tgen.remove(top)

      # # write raw jets to tree
      # jets_pt = []
      # jets_eta = []
      # jets_phi = []
      # jets_mass = []
      # for jet in jets:
        # jets_pt.append(jet.pt())
      #   jets_eta.append(jet.eta())
      #   jets_phi.append(jet.phi())
      #   jets_mass.append(jet.mass())
      # tree_event.jets_pt[0]   = jets_pt
      # tree_event.jets_pt[0]   = jets_pt
      # tree_event.jets_eta[0]  = jets_eta
      # tree_event.jets_phi[0]  = jets_phi
      # tree_event.jets_mass[0] = jets_mass

      # write raw jets to a tree
      for jet in jets:
        tree_jet_raw.mass[0]     = jet.mass()
        tree_jet_raw.pt[0]       = jet.pt()
        tree_jet_raw.eta[0]      = jet.eta()
        tree_jet_raw.phi[0]      = jet.phi()
        tree_jet_raw.weight[0]   = weight
        tree_jet_raw.event_id[0] = evtid
        tree_jet_raw.Fill()

      # REMOVE JET-LEPTON OVERLAP
      jets, dummy = cleanObjectCollection(jets,gps_tau_vis,dRmin=0.4)
      # print 'now cleaning from DM, now:  %f' % (len(jets))
      jets, dummy = cleanObjectCollection(jets,gps_dm,dRmin=0.4, mfrac=-1.)
      # print 'after cleaning from DM, now: %f' % (len(jets))
      jets        .sort(key=lambda p: p.pt(), reverse=True)
      njets  = 0
      sumjet = 0
      jets30  = [ ]

      for jet in jets:
        if jet.pt()>30 and abs(jet.eta())<5:
          sumjet            += jet.pt()
          njets             += 1
          tree_jet.mass[0]   = jet.mass()
          tree_jet.pt[0]     = jet.pt()
          tree_jet.eta[0]    = jet.eta()
          tree_jet.phi[0]    = jet.phi()
          tree_jet.weight[0] = weight
          tree_jet.event_id[0] = evtid
          tree_jet.Fill()
          jets30.append(jet)

      # MULTIPLICITIES
      tree_event.nlq[0]           = len(gps_mother)
      tree_event.ndm[0]           = len(gps_dm)
      tree_event.nx[0]            = len(gps_x)
      tree_event.nbcut[0]         = len(gps_bcut)
      tree_event.nbcut50[0]       = len(gps_bcut50)
      tree_event.nbgen[0]         = len(gps_bgen)
      tree_event.njet[0]          = njets
      tree_event.ntau[0]          = len(gps_tau)
      tree_event.ntaucut[0]       = len(gps_taucut)
      tree_event.ntaucut50[0]     = len(gps_taucut50)
      tree_event.ntaucut_vis[0]   = len(gps_taucut_vis)
      tree_event.ntaucut50_vis[0] = len(gps_taucut50_vis)

      # JETS
      tree_event.met_pt[0]      = met[0].pt()
      tree_event.met_phi[0]     = met[0].phi()
      tree_event.sumjet[0]      = sumjet
      if len(jets30) >= 2:
          tree_event.jet1_mass[0]  = jets30[0].mass()
          tree_event.jet2_mass[0]  = jets30[1].mass()
          tree_event.jet1_pt[0]    = jets30[0].pt()
          tree_event.jet2_pt[0]    = jets30[1].pt()
          tree_event.jet1_eta[0]   = jets30[0].eta()
          tree_event.jet2_eta[0]   = jets30[1].eta()
          tree_event.jet1_phi[0]   = jets30[0].phi()
          tree_event.jet2_phi[0]   = jets30[1].phi()
          if len(jets30) >= 3:
              tree_event.jet3_mass[0]  = jets30[2].mass()
              tree_event.jet3_pt[0]    = jets30[2].pt()
              tree_event.jet3_eta[0]   = jets30[2].eta()
              tree_event.jet3_phi[0]   = jets30[2].phi()
          else:
              tree_event.jet3_mass[0]  = -1.
              tree_event.jet3_pt[0]    = -1.
              tree_event.jet3_eta[0]   = -9.
              tree_event.jet3_phi[0]   = -9.
          tree_event.dphi_jj[0]    = deltaPhi(jets30[0].phi(), jets30[1].phi())
          tree_event.deta_jj[0]    = jets30[0].eta() - jets30[1].eta()
          tree_event.dr_jj[0]      = deltaR(jets30[0].eta(),jets30[0].phi(),jets30[1].eta(),jets30[1].phi())
          dijetp4                  = jets30[0].p4() + jets30[1].p4()
          tree_event.mjj[0]        = dijetp4.M()
      elif len(jets30) == 1:
          tree_event.jet1_mass[0]  = jets30[0].mass()
          tree_event.jet2_mass[0]  = -1.
          tree_event.jet3_mass[0]  = -1.
          tree_event.jet1_pt[0]    = jets30[0].pt()
          tree_event.jet2_pt[0]    = -1.
          tree_event.jet3_pt[0]    = -1.
          tree_event.jet1_eta[0]   = jets30[0].eta()
          tree_event.jet2_eta[0]   = -9.
          tree_event.jet3_eta[0]   = -9.
          tree_event.jet1_phi[0]   = jets30[0].phi()
          tree_event.jet2_phi[0]   = -9.
          tree_event.jet3_phi[0]   = -9.
          tree_event.dphi_jj[0]    = -9.
          tree_event.deta_jj[0]    = -9.
          tree_event.dr_jj[0]      = -1.
          tree_event.mjj[0]        = -1.
      else:
          tree_event.jet1_mass[0]  = -1.
          tree_event.jet2_mass[0]  = -1.
          tree_event.jet3_mass[0]  = -1.
          tree_event.jet1_pt[0]    = -1.
          tree_event.jet2_pt[0]    = -1.
          tree_event.jet3_pt[0]    = -1.
          tree_event.jet1_eta[0]   = -9.
          tree_event.jet2_eta[0]   = -9.
          tree_event.jet3_eta[0]   = -9.
          tree_event.jet1_phi[0]   = -9.
          tree_event.jet2_phi[0]   = -9.
          tree_event.jet3_phi[0]   = -9.
          tree_event.dphi_jj[0]    = -9.
          tree_event.deta_jj[0]    = -9.
          tree_event.dr_jj[0]      = -1.
          tree_event.mjj[0]        = -1.

      if len(gps_bgen) >= 2:
        tree_event.b1_mass[0]= gps_bgen[0].mass()
        tree_event.b1_pt[0]  = gps_bgen[0].pt()
        tree_event.b1_eta[0] = gps_bgen[0].eta()
        tree_event.b1_phi[0] = gps_bgen[0].phi()
        tree_event.b2_mass[0]= gps_bgen[1].mass()
        tree_event.b2_pt[0]  = gps_bgen[1].pt()
        tree_event.b2_eta[0] = gps_bgen[1].eta()
        tree_event.b2_phi[0] = gps_bgen[1].phi()
      elif len(gps_bgen) == 1:
        tree_event.b1_mass[0]= gps_bgen[0].mass()
        tree_event.b1_pt[0]  = gps_bgen[0].pt()
        tree_event.b1_eta[0] = gps_bgen[0].eta()
        tree_event.b1_phi[0] = gps_bgen[0].phi()
        tree_event.b2_mass[0]= -1.
        tree_event.b2_pt[0]  = -1.
        tree_event.b2_eta[0] = -9.
        tree_event.b2_phi[0] = -9.
      else:
        tree_event.b1_mass[0]= -1.
        tree_event.b1_pt[0]  = -1.
        tree_event.b1_eta[0] = -9.
        tree_event.b1_phi[0] = -9.
        tree_event.b2_mass[0]= -1.
        tree_event.b2_pt[0]  = -1.
        tree_event.b2_eta[0] = -9.
        tree_event.b2_phi[0] = -9.

      # SCALAR SUM PT
      if len(gps_tau_vis)>=1 and len(gps_bcut)>=1:
        st = 0
        for tauvis in gps_tau_vis[:2]:
          st += tauvis.pt()
        for b in gps_bcut:
          st += b.pt()
        stmet = st + met[0].pt()
      else:
        st    = -1
        stmet = -1

      if len(gps_tau) >=2 :
        tree_event.tau1_mass[0]    = gps_tau[0].mass()
        tree_event.tau2_mass[0]    = gps_tau[1].mass()
        tree_event.tau1_pt[0]      = gps_tau[0].pt()
        tree_event.tau2_pt[0]      = gps_tau[1].pt()
        tree_event.tau1_eta[0]     = gps_tau[0].eta()
        tree_event.tau2_eta[0]     = gps_tau[1].eta()
        tree_event.tau1_phi[0]     = gps_tau[0].phi()
        tree_event.tau2_phi[0]     = gps_tau[1].phi()
        tree_event.tau1_y[0]       = gps_tau[0].p4().Rapidity()
        tree_event.tau2_y[0]       = gps_tau[1].p4().Rapidity()
        tree_event.tau1_massvis[0] = gps_tau_vis[0].mass()
        tree_event.tau2_massvis[0] = gps_tau_vis[1].mass()
        tree_event.tau1_ptvis[0]   = gps_tau_vis[0].pt()
        tree_event.tau2_ptvis[0]   = gps_tau_vis[1].pt()
        tree_event.tau1_etavis[0]  = gps_tau_vis[0].eta()
        tree_event.tau2_etavis[0]  = gps_tau_vis[1].eta()
        tree_event.tau1_phivis[0]  = gps_tau_vis[0].phi()
        tree_event.tau2_phivis[0]  = gps_tau_vis[1].phi()
        dy = abs(gps_tau[0].p4().Rapidity() - gps_tau[1].p4().Rapidity())
        tree_event.ditau_dy[0]     = dy
        tree_event.ditau_chi[0]    = exp(dy)
      elif len(gps_tau) == 1:
        tree_event.tau1_mass[0]    = gps_tau[0].mass()
        tree_event.tau2_mass[0]    = -1.
        tree_event.tau1_pt[0]      = gps_tau[0].pt()
        tree_event.tau2_pt[0]      = -1.
        tree_event.tau1_eta[0]     = gps_tau[0].eta()
        tree_event.tau2_eta[0]     = -9.
        tree_event.tau1_phi[0]     = gps_tau[0].phi()
        tree_event.tau2_phi[0]     = -9.
        tree_event.tau1_y[0]       = gps_tau[0].p4().Rapidity()
        tree_event.tau2_y[0]       = -9.
        tree_event.tau1_massvis[0] = gps_tau_vis[0].mass()
        tree_event.tau2_massvis[0] = -1.
        tree_event.tau1_ptvis[0]   = gps_tau_vis[0].pt()
        tree_event.tau2_ptvis[0]   = -1.
        tree_event.tau1_etavis[0]  = gps_tau_vis[0].eta()
        tree_event.tau2_etavis[0]  = -9.
        tree_event.tau1_phivis[0]  = gps_tau_vis[0].phi()
        tree_event.tau2_phivis[0]  = -9.
        tree_event.ditau_dy[0]     = -9.
        tree_event.ditau_chi[0]    = -1.
      else:
        tree_event.tau1_mass[0]    = -1.
        tree_event.tau2_mass[0]    = -1.
        tree_event.tau1_pt[0]      = -1.
        tree_event.tau2_pt[0]      = -1.
        tree_event.tau1_eta[0]     = -9.
        tree_event.tau2_eta[0]     = -9.
        tree_event.tau1_phi[0]     = -9.
        tree_event.tau2_phi[0]     = -9.
        tree_event.tau1_y[0]       = -9.
        tree_event.tau2_y[0]       = -9.
        tree_event.tau1_massvis[0] = -1.
        tree_event.tau2_massvis[0] = -1.
        tree_event.tau1_ptvis[0]   = -1.
        tree_event.tau2_ptvis[0]   = -1.
        tree_event.tau1_etavis[0]  = -9.
        tree_event.tau2_etavis[0]  = -9.
        tree_event.tau1_phivis[0]  = -9.
        tree_event.tau2_phivis[0]  = -9.
        tree_event.ditau_dy[0]     = -9.
        tree_event.ditau_chi[0]    = -1.

      tree_event.st[0]             = st
      tree_event.st_met[0]         = stmet

      # M (tauvis1, jet1)
      if len(gps_tau) >= 1 and len(jets30) >= 1:
        tree_event.m_tauvis1_jet1[0] = (gps_tau[0].p4() + jets30[0].p4()).M()
      else:
        tree_event.m_tauvis1_jet1[0] = -1.


      tree_event.weight[0] = weight
      tree_event.qscale[0] = qscale

      if len(gps_mother)==1:
        tree_event.lq1_mass[0]  = gps_mother[0].mass()
        tree_event.lq2_mass[0]  = -1.
        tree_event.lq1_pt[0]    = gps_mother[0].pt()
        tree_event.lq2_pt[0]    = -1.
        tree_event.lq1_eta[0]   = gps_mother[0].eta()
        tree_event.lq2_eta[0]   = -9.
        tree_event.lq1_phi[0]   = gps_mother[0].phi()
        tree_event.lq2_phi[0]   = -9.
        tree_event.m_lqlq[0]    = -1.
      elif len(gps_mother)>=2:
        tree_event.lq1_mass[0]  = gps_mother[0].mass()
        tree_event.lq2_mass[0]  = gps_mother[1].mass()
        tree_event.lq1_pt[0]    = gps_mother[0].pt()
        tree_event.lq2_pt[0]    = gps_mother[1].pt()
        tree_event.lq1_eta[0]   = gps_mother[0].eta()
        tree_event.lq2_eta[0]   = gps_mother[1].eta()
        tree_event.lq1_phi[0]   = gps_mother[0].phi()
        tree_event.lq2_phi[0]   = gps_mother[1].phi()
        dilqp4                  = gps_mother[0].p4() + gps_mother[1].p4()
        tree_event.m_lqlq[0]    = dilqp4.M()
      else:
        tree_event.lq1_mass[0]  = -1.
        tree_event.lq2_mass[0]  = -1.
        tree_event.lq1_pt[0]    = -1.
        tree_event.lq2_pt[0]    = -1.
        tree_event.lq1_eta[0]   = -9.
        tree_event.lq2_eta[0]   = -9.
        tree_event.lq1_phi[0]   = -9.
        tree_event.lq2_phi[0]   = -9.
        tree_event.m_lqlq[0]    = -1.

      if len(gps_dm) == 1:
        tree_event.dm1_mass[0]  = gps_dm[0].mass()
        tree_event.dm2_mass[0]  = -1.
        tree_event.dm1_pt[0]    = gps_dm[0].pt()
        tree_event.dm2_pt[0]    = -1.
        tree_event.dm1_eta[0]   = gps_dm[0].eta()
        tree_event.dm2_eta[0]   = -9.
        tree_event.dm1_phi[0]   = gps_dm[0].phi()
        tree_event.dm2_phi[0]   = -9.
      elif len(gps_dm)>=2:
        tree_event.dm1_mass[0]  = gps_dm[0].mass()
        tree_event.dm2_mass[0]  = gps_dm[1].mass()
        tree_event.dm1_pt[0]    = gps_dm[0].pt()
        tree_event.dm2_pt[0]    = gps_dm[1].pt()
        tree_event.dm1_eta[0]   = gps_dm[0].eta()
        tree_event.dm2_eta[0]   = gps_dm[1].eta()
        tree_event.dm1_phi[0]   = gps_dm[0].phi()
        tree_event.dm2_phi[0]   = gps_dm[1].phi()
      else:
        tree_event.dm1_mass[0]  = -1.
        tree_event.dm2_mass[0]  = -1.
        tree_event.dm1_pt[0]    = -1.
        tree_event.dm2_pt[0]    = -1.
        tree_event.dm1_eta[0]   = -9.
        tree_event.dm2_eta[0]   = -9.
        tree_event.dm1_phi[0]   = -9.
        tree_event.dm2_phi[0]   = -9.



      if len(gps_x) == 1:
        tree_event.x_mass[0]  = gps_x[0].mass()
        tree_event.x_pt[0]    = gps_x[0].pt()
        tree_event.x_eta[0]   = gps_x[0].eta()
        tree_event.x_phi[0]   = gps_x[0].phi()
      else:
        tree_event.x_mass[0]  = -1.
        tree_event.x_pt[0]    = -1.
        tree_event.x_eta[0]   = -9.
        tree_event.x_phi[0]   = -9.
      tree_event.Fill()

  print ">>>   processed %4s events in %s"%(evtid,formatTime(time.time()-start_proc))
  print ">>>   writing to output file %s..."%(outfilename)
  outfile.Write()
  outfile.Close()
  print ">>>   done in in %s"%(formatTime(time.time()-start1))


root_dtype = {
  float: 'D',  int: 'I',  bool: 'O',
  'f':   'D',  'i': 'I',  '?':  'O',  'b': 'b', }

def addBranch(self, name, dtype='f', default=None, standard=True):
   """Add branch with a given name, and create an array of the same name as address."""
   if hasattr(self,name):
     print "ERROR! TreeProducerCommon.addBranch: Branch of name '%s' already exists!"%(name)
     exit(1)
   if isinstance(dtype,str):
     if dtype.lower()=='f': # 'f' is only a 'float32', and 'F' is a 'complex64', which do not work for filling float branches
       dtype = float        # float is a 'float64' ('f8')
     elif dtype.lower()=='i': # 'i' is only a 'int32'
       dtype = int            # int is a 'int64' ('i8')
   if standard:
     setattr(self,name,num.zeros(1,dtype=dtype))
     self.Branch(name, getattr(self,name), '%s/%s'%(name,root_dtype[dtype]))
     if default!=None:
       getattr(self,name)[0] = default
   else:
     l = array('f', [0.])
     setattr(self,name,TObjArray(l))
     # self.Branch(name, getattr(self, name))
     print type(getattr(self, name))
     self.Branch(getattr(self, name))
TTree.addBranch = addBranch

def p4sumvis(particles):
  #import pdb; pdb.set_trace()
  visparticles = copy.deepcopy([p for p in particles if abs(p.pdgId()) not in [12, 14, 16]])
  p4 = visparticles[-1].p4() if particles else 0.
  visparticles.pop()
  for p in visparticles:
      p4 += p.p4()
  return p4

def finalDaughters(particle, daughters):
  """Fills daughters with all the daughters of particle recursively."""
  if particle.numberOfDaughters()==0:
    daughters.append(particle)
  else:
    foundDaughter = False
    for i in range( particle.numberOfDaughters() ):
      dau = particle.daughter(i)
      if dau.status()>=1:
        daughters = finalDaughters( dau, daughters )
        foundDaughter = True
    if not foundDaughter:
      daughters.append(particle)
  return daughters

def tauDecayMode(tau):
  unstable = True
  dm = 'tau'
  final_daughter = tau
  while unstable:
    nod = tau.numberOfDaughters()
    for i in range(nod):
      dau = tau.daughter(i)
      if abs(dau.pdgId())==11 and dau.status()==1:
        dm = 'ele'
        final_daughter = dau
        unstable = False
        break
      elif abs(dau.pdgId())==13 and dau.status()==1:
        dm = 'muon'
        final_daughter = dau
        unstable = False
        break
      elif abs(dau.pdgId())==15: #taus may do bremsstrahlung
        dm = 'tau'
        final_daughter = dau
        tau = dau # check its daughters
        break
      elif abs(dau.pdgId()) not in (12, 14, 16):
        unstable = False
        break
  return dm

def diTauDecayMode(decay1,decay2):
  if decay1=='ele' and decay2=='ele':
    return 5, 'ee'
  elif decay1=='muon' and decay2=='muon':
    return 3, 'mm'
  elif (decay1=='ele' and decay2=='muon') or (decay1=='muon' and decay2=='ele'):
    return 4, 'em'
  elif (decay1=='tau' and decay2=='ele') or (decay1=='ele' and decay2=='tau'):
    return 2, 'et'
  elif (decay1=='tau' and decay2=='muon') or (decay1=='muon' and decay2=='tau'):
    return 1, 'mt'
  elif decay1=='tau' and decay2=='tau':
    return 0, 'tt'
  else:
    return -1, 'anything'

def deltaR(eta1, phi1, eta2, phi2):
  deta = eta1 - eta2
  dphi = deltaPhi(phi1, phi2)
  return math.sqrt(deta*deta+dphi*dphi)

def deltaPhi(phi1, phi2):
  """Computes delta phi, handling periodic limit conditions."""
  res = phi1 - phi2
  while res > math.pi:
    res -= 2*math.pi
  while res<-math.pi:
    res += 2*math.pi
  return res

def cleanObjectCollection(objects, masks, dRmin, mfrac=-1.):
  """Masks objects using a deltaR cut."""
  if len(objects)==0 or len(masks)==0:
    return objects, []
  cleanObjects = [ ]
  dirtyObjects = [ ]
  for object in objects:
    overlap = False
    for mask in masks:
        dR = deltaR(object.eta(),object.phi(),mask.eta(),mask.phi())
        if dR<dRmin:
          if mfrac < 0:
            overlap = True
            break
          else:
            if object.mass() > (1.-mfrac)*mask.mass() and object.mass() <(1.+mfrac)*mask.mass():
              overlap = True
              break
    if overlap:
      dirtyObjects.append(object)
    else:
      cleanObjects.append(object)

  # print 'in cleaner: have %i cleaned objects and %i dirty objects.' % (len(cleanObjects), len(dirtyObjects))
  return cleanObjects, dirtyObjects

def isFinal(p):
  # check if one daughter is final and has same PID, then it's not final
  return not (p.numberOfDaughters()==1 and p.daughter(0).pdgId()==p.pdgId())

def isFinalM(p):
  #print p.numberOfDaughters(), p.daughter(0).pdgId(), p.pdgId(), p.status()
  #return p.numberOfDaughters()==3
  return not (p.numberOfDaughters()==3 and p.daughter(0).pdgId()==p.pdgId())

def printParticle(p):
  string = "Particle with pdId %9d: status=%2d, pt=%7.2f, eta=%5.2f, phi=%5.2f, final=%5s"%(p.pdgId(),p.status(),p.pt(),p.eta(),p.phi(),isFinal(p))
  if p.numberOfMothers()>=2:
    string += ", mothers %s, %s"%(p.mother(0).pdgId(),p.mother(1).pdgId())
  elif p.numberOfMothers()==1:
    string += ", mother %s"%(p.mother(0).pdgId())
  if p.numberOfDaughters()>=2:
    string += ", daughters %s, %s"%(p.daughter(0).pdgId(),p.daughter(1).pdgId())
  elif p.numberOfDaughters()==1:
    string += ", daughter %s"%(p.daughter(0).pdgId())
  print string

def printDecayChain(mothers):
  for m in mothers:
    daus   = []
    gdaus  = []
    ggdaus = []
    print '='*10 + ' New mother:'
    printParticle(m)
    for d_idx in range(m.numberOfDaughters()):
      d = m.daughter(d_idx)
      daus.append(d)
      # printParticle(d)
    print '-'*10 + ' Daughters:'
    for d in daus:
      printParticle(d)
      for g_idx in range(d.numberOfDaughters()):
        g = d.daughter(g_idx)
        gdaus.append(g)
    print '-'*10 + ' Grand daughters:'
    for g in gdaus:
      printParticle(g)
      for gg_idx in range(g.numberOfDaughters()):
        gg = g.daughter(gg_idx)
        ggdaus.append(gg)
    print '-'*10 + ' Great grand daughters:'
    for gg in ggdaus:
      printParticle(gg)




  for g_idx in range(d.numberOfDaughters()):
    g = d.daughter(g_idx)
    printParticle(g)
    for gg_idx in range(d.numberOfDaughters()):
      gg = d.daughter(gg_idx)
      printParticle(gg)

def formatTime(seconds):
  minutes, seconds = divmod(seconds, 60)
  hours,   minutes = divmod(minutes, 60)
  if   hours:   return "%d hours, %d minutes and %.3g seconds"%(hours,minutes,seconds)
  elif minutes: return "%d minutes and %.3g seconds"%(minutes,seconds)
  return "%.3g seconds"%(seconds)

def formatTimeShort(seconds):
  minutes, seconds = divmod(seconds, 60)
  hours,   minutes = divmod(minutes, 60)
  return "%02d:%02d:%02d"%(hours,minutes,seconds)

def bold(string):
  return "\033[1m%s\033[0m"%(string)

def ETA(start,iJob,nJobs):
  return formatTimeShort((time.time()-start)*(nJobs-iJob)/iJob)

def stepsize(total):
  return min(max(10**(ceil(log(total,10))-1),20),100)

def ensureDir(dir):
  if not os.path.exists(dir):
    os.makedirs(dir)
    print ">>> made directory %s\n>>>"%(dir)
  return dir

class Jet:
  """A simple jet information container class"""
  pt   = -1.
  eta  = -9.
  phi  = -9.
  mass = -1.
  def __init__(self, pt, eta, phi, mass):
    self.pt   = pt
    self.eta  = eta
    self.phi  = phi
    self.mass = mass



if __name__=='__main__':
  print ">>> "
  main()
  print ">>> done\n"
