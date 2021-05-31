#include "Analyzer/include/MuonHists.h"
// #include "Analyzer/include/cosmetics.h"
#include "Analyzer/include/constants.h"
#include "Analyzer/include/useful_functions.h"
#include <TH1F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

MuonHists::MuonHists(TString dir_) : BaseHists(dir_){

  hnmuons = book<TH1D>("nmuons", ";N_{#mu}; Events / bin", 11, -0.5, 10.5);
  hmuonpt = book<TH1D>("muonpt", ";p_{T}^{#mu} [GeV]; Events / bin", 50, 0, 1500);
  hmuonpt_rebin = book<TH1D>("muonpt_rebin", ";p_{T}^{#mu} [GeV]; Events / bin", 50, 0, 200);
  hmuonpt_rebin2 = book<TH1D>("muonpt_rebin2", ";p_{T}^{#mu} [GeV]; Events / bin", 50, 0, 50);
  hmuoneta = book<TH1D>("muoneta", ";#eta^{#mu};Events / bin", 100, -5., 5.);
  hmuonphi = book<TH1D>("muonphi", ";#phi^{#mu};Events / bin", 70, -3.5, 3.5);
  hmuonmass = book<TH1D>("muonmass", ";m^{#mu} [GeV];Events / bin", 50, 0, 1500);
  hmuonenergy = book<TH1D>("muonenergy", ";E^{#mu} [GeV];Events / bin", 50, 0, 1500);
  hmuonpfiso = book<TH1D>("muonpfiso", ";Iso_{PF}^{#mu};Events / bin", 100, 0, 1);
  // hmuonminiiso = book<TH1D>("muonminiiso", ";Iso_{mini}^{#mu};Events / bin", 100, 0, 1);
  hmuondxy = book<TH1D>("muondxy", ";#mu d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuondz = book<TH1D>("muondz", ";#mu d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuond = book<TH1D>("muond", ";#mu d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon_dxy_vs_dz = book<TH2D>("muon_dxy_vs_dz", ";#mu d_{xy} wrt. PV [cm];#mu d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  hmuongendrmin = book<TH1D>("muongendrmin", ";#DeltaR(#mu, closest gen #mu);Events / bin", 60, 0, 3);
  hmuongenorigin = book<TH1D>("muongenorigin", ";#mu -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuongenflav = book<TH1D>("muongenflav", ";#mu gen flavor;Events / bin", 16, -0.5, 15.5);
  hnmuonsgenfromtau = book<TH1D>("nmuonsgenfromtau", ";Number of #mu from #tau decay; Events / bin", 11, -0.5, 10.5);
  hnmuonsgenfromhadron = book<TH1D>("nmuonsgenfromhadron", ";Number of #mu from hadron decay; Events / bin", 11, -0.5, 10.5);
  hnmuonsgenfromelse = book<TH1D>("nmuonsgenfromelse", ";Number of #mu from other decay; Events / bin", 11, -0.5, 10.5);
  hnmuonsgenunmatched = book<TH1D>("nmuonsgenunmatched", ";Number of unmatched #mu; Events / bin", 11, -0.5, 10.5);

  hmuonclosestorigin = book<TH1D>("muonclosestorigin", ";closest #mu -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuonclosestd = book<TH1D>("muonclosestd", ";closest #mu d [cm]; Events / bin", 250, 0, 0.5);


  hnmuonsfromtau = book<TH1D>("nmuonsfromtau", ";N_{#mu from #tau}; Events / bin", 11, -0.5, 10.5);
  hmuonfromtaupt = book<TH1D>("muonfromtaupt", ";p_{T}^{#mu from #tau} [GeV]; Events / bin", 50, 0, 1500);
  hmuonfromtaupt_rebin = book<TH1D>("muonfromtaupt_rebin", ";p_{T}^{#mu from #tau} [GeV]; Events / bin", 50, 0, 200);
  hmuonfromtaupt_rebin2 = book<TH1D>("muonfromtaupt_rebin2", ";p_{T}^{#mu from #tau} [GeV]; Events / bin", 50, 0, 50);
  hmuonfromtaueta = book<TH1D>("muonfromtaueta", ";#eta^{#mu from #tau};Events / bin", 100, -5., 5.);
  hmuonfromtauphi = book<TH1D>("muonfromtauphi", ";#phi^{#mu from #tau};Events / bin", 70, -3.5, 3.5);
  hmuonfromtaumass = book<TH1D>("muonfromtaumass", ";m^{#mu from #tau} [GeV];Events / bin", 50, 0, 1500);
  hmuonfromtauenergy = book<TH1D>("muonfromtauenergy", ";E^{#mu from #tau} [GeV];Events / bin", 50, 0, 1500);
  hmuonfromtaupfiso = book<TH1D>("muonfromtaupfiso", ";Iso_{PF}^{#mu from #tau};Events / bin", 100, 0, 1);
  hmuonfromtaudxy = book<TH1D>("muonfromtaudxy", ";#mu from #tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromtaudz = book<TH1D>("muonfromtaudz", ";#mu from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromtaud = book<TH1D>("muonfromtaud", ";#mu from #tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromtau_dxy_vs_dz = book<TH2D>("muonfromtau_dxy_vs_dz", ";#mu from #tau d_{xy} wrt. PV [cm];#mu from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  hmuonfromtaugendrmin = book<TH1D>("muonfromtaugendrmin", ";#DeltaR(#mu from #tau, closest gen #mu);Events / bin", 60, 0, 3);

  hnmuonsfromhad = book<TH1D>("nmuonsfromhad", ";N_{#mu from had.}; Events / bin", 11, -0.5, 10.5);
  hmuonfromhadpt = book<TH1D>("muonfromhadpt", ";p_{T}^{#mu from had.} [GeV]; Events / bin", 50, 0, 1500);
  hmuonfromhadpt_rebin = book<TH1D>("muonfromhadpt_rebin", ";p_{T}^{#mu from had.} [GeV]; Events / bin", 50, 0, 200);
  hmuonfromhadpt_rebin2 = book<TH1D>("muonfromhadpt_rebin2", ";p_{T}^{#mu from had.} [GeV]; Events / bin", 50, 0, 50);
  hmuonfromhadeta = book<TH1D>("muonfromhadeta", ";#eta^{#mu from had.};Events / bin", 100, -5., 5.);
  hmuonfromhadphi = book<TH1D>("muonfromhadphi", ";#phi^{#mu from had.};Events / bin", 70, -3.5, 3.5);
  hmuonfromhadmass = book<TH1D>("muonfromhadmass", ";m^{#mu from had.} [GeV];Events / bin", 50, 0, 1500);
  hmuonfromhadenergy = book<TH1D>("muonfromhadenergy", ";E^{#mu from had.} [GeV];Events / bin", 50, 0, 1500);
  hmuonfromhadpfiso = book<TH1D>("muonfromhadpfiso", ";Iso_{PF}^{#mu not from #tau};Events / bin", 100, 0, 1);
  hmuonfromhaddxy = book<TH1D>("muonfromhaddxy", ";#mu from had. d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromhaddz = book<TH1D>("muonfromhaddz", ";#mu from had. d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromhadd = book<TH1D>("muonfromhadd", ";#mu from had. d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonfromhad_dxy_vs_dz = book<TH2D>("muonfromhad_dxy_vs_dz", ";#mu from had. d_{xy} wrt. PV [cm];#mu from had. d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  hmuonfromhadgendrmin = book<TH1D>("muonfromhadgendrmin", ";#DeltaR(#mu from had., closest gen #mu);Events / bin", 60, 0, 3);

  hnmuonsunmatched = book<TH1D>("nmuonsunmatched", ";N_{#mu unmatched}; Events / bin", 11, -0.5, 10.5);
  hmuonunmatchedpt = book<TH1D>("muonunmatchedpt", ";p_{T}^{#mu unmatched} [GeV]; Events / bin", 50, 0, 1500);
  hmuonunmatchedpt_rebin = book<TH1D>("muonunmatchedpt_rebin", ";p_{T}^{#mu unmatched} [GeV]; Events / bin", 50, 0, 200);
  hmuonunmatchedpt_rebin2 = book<TH1D>("muonunmatchedpt_rebin2", ";p_{T}^{#mu unmatched} [GeV]; Events / bin", 50, 0, 50);
  hmuonunmatchedeta = book<TH1D>("muonunmatchedeta", ";#eta^{#mu unmatched};Events / bin", 100, -5., 5.);
  hmuonunmatchedphi = book<TH1D>("muonunmatchedphi", ";#phi^{#mu unmatched};Events / bin", 70, -3.5, 3.5);
  hmuonunmatchedmass = book<TH1D>("muonunmatchedmass", ";m^{#mu unmatched} [GeV];Events / bin", 50, 0, 1500);
  hmuonunmatchedenergy = book<TH1D>("muonunmatchedenergy", ";E^{#mu unmatched} [GeV];Events / bin", 50, 0, 1500);
  hmuonunmatchedpfiso = book<TH1D>("muonunmatchedpfiso", ";Iso_{PF}^{#mu unmatched};Events / bin", 100, 0, 1);
  hmuonunmatcheddxy = book<TH1D>("muonunmatcheddxy", ";#mu unmatched d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonunmatcheddz = book<TH1D>("muonunmatcheddz", ";#mu unmatched d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonunmatchedd = book<TH1D>("muonunmatchedd", ";#mu unmatched d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuonunmatched_dxy_vs_dz = book<TH2D>("muonunmatched_dxy_vs_dz", ";#mu unmatched d_{xy} wrt. PV [cm];#mu unmatched d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  hmuonunmatchedgendrmin = book<TH1D>("muonunmatchedgendrmin", ";#DeltaR(#mu unmatched, closest gen #mu);Events / bin", 60, 0, 3);

  hmuon1pt = book<TH1D>("muon1pt", ";p_{T}^{#mu 1} [GeV]; Events / bin", 50, 0, 1500);
  hmuon1pt_rebin = book<TH1D>("muon1pt_rebin", ";p_{T}^{#mu 1} [GeV]; Events / bin", 50, 0, 200);
  hmuon1pt_rebin2 = book<TH1D>("muon1pt_rebin2", ";p_{T}^{#mu 1} [GeV]; Events / bin", 50, 0, 50);
  hmuon1eta = book<TH1D>("muon1eta", ";#eta^{#mu 1};Events / bin", 100, -5., 5.);
  hmuon1phi = book<TH1D>("muon1phi", ";#phi^{#mu 1};Events / bin", 70, -3.5, 3.5);
  hmuon1mass = book<TH1D>("muon1mass", ";m^{#mu 1} [GeV];Events / bin", 50, 0, 1500);
  hmuon1energy = book<TH1D>("muon1energy", ";E^{#mu 1} [GeV];Events / bin", 50, 0, 1500);
  hmuon1pfiso = book<TH1D>("muon1pfiso", ";Iso_{PF}^{#mu 1};Events / bin", 100, 0, 1);
  hmuon1dxy = book<TH1D>("muon1dxy", ";#mu 1 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon1dz = book<TH1D>("muon1dz", ";#mu 1 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon1d = book<TH1D>("muon1d", ";#mu 1 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon1gendrmin = book<TH1D>("muon1gendrmin", ";#DeltaR(#mu 1, closest gen #mu);Events / bin", 60, 0, 3);
  hmuon1genorigin = book<TH1D>("muon1genorigin", ";#mu 1 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuon1genflav = book<TH1D>("muon1genflav", ";#mu 1 gen flavor;Events / bin", 16, -0.5, 15.5);

  hmuon2pt = book<TH1D>("muon2pt", ";p_{T}^{#mu 2} [GeV]; Events / bin", 50, 0, 1500);
  hmuon2pt_rebin = book<TH1D>("muon2pt_rebin", ";p_{T}^{#mu 2} [GeV]; Events / bin", 50, 0, 200);
  hmuon2pt_rebin2 = book<TH1D>("muon2pt_rebin2", ";p_{T}^{#mu 2} [GeV]; Events / bin", 50, 0, 50);
  hmuon2eta = book<TH1D>("muon2eta", ";#eta^{#mu 2};Events / bin", 100, -5., 5.);
  hmuon2phi = book<TH1D>("muon2phi", ";#phi^{#mu 2};Events / bin", 70, -3.5, 3.5);
  hmuon2mass = book<TH1D>("muon2mass", ";m^{#mu 2} [GeV];Events / bin", 50, 0, 1500);
  hmuon2energy = book<TH1D>("muon2energy", ";E^{#mu 2} [GeV];Events / bin", 50, 0, 1500);
  hmuon2pfiso = book<TH1D>("muon2pfiso", ";Iso_{PF}^{#mu 2};Events / bin", 100, 0, 1);
  hmuon2dxy = book<TH1D>("muon2dxy", ";#mu 2 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon2dz = book<TH1D>("muon2dz", ";#mu 2 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon2d = book<TH1D>("muon2d", ";#mu 2 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon2gendrmin = book<TH1D>("muon2gendrmin", ";#DeltaR(#mu 2, closest gen #mu);Events / bin", 60, 0, 3);
  hmuon2genorigin = book<TH1D>("muon2genorigin", ";#mu 2 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuon2genflav = book<TH1D>("muon2genflav", ";#mu 2 gen flavor;Events / bin", 16, -0.5, 15.5);

  hmuon3pt = book<TH1D>("muon3pt", ";p_{T}^{#mu 3} [GeV]; Events / bin", 50, 0, 1500);
  hmuon3pt_rebin = book<TH1D>("muon3pt_rebin", ";p_{T}^{#mu 3} [GeV]; Events / bin", 50, 0, 200);
  hmuon3pt_rebin2 = book<TH1D>("muon3pt_rebin2", ";p_{T}^{#mu 3} [GeV]; Events / bin", 50, 0, 50);
  hmuon3eta = book<TH1D>("muon3eta", ";#eta^{#mu 3};Events / bin", 100, -5., 5.);
  hmuon3phi = book<TH1D>("muon3phi", ";#phi^{#mu 3};Events / bin", 70, -3.5, 3.5);
  hmuon3mass = book<TH1D>("muon3mass", ";m^{#mu 3} [GeV];Events / bin", 50, 0, 1500);
  hmuon3energy = book<TH1D>("muon3energy", ";E^{#mu 3} [GeV];Events / bin", 50, 0, 1500);
  hmuon3pfiso = book<TH1D>("muon3pfiso", ";Iso_{PF}^{#mu 3};Events / bin", 100, 0, 1);
  hmuon3dxy = book<TH1D>("muon3dxy", ";#mu 3 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon3dz = book<TH1D>("muon3dz", ";#mu 3 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon3d = book<TH1D>("muon3d", ";#mu 3 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon3gendrmin = book<TH1D>("muon3gendrmin", ";#DeltaR(#mu 3, closest gen #mu);Events / bin", 60, 0, 3);
  hmuon3genorigin = book<TH1D>("muon3genorigin", ";#mu 3 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuon3genflav = book<TH1D>("muon3genflav", ";#mu 3 gen flavor;Events / bin", 16, -0.5, 15.5);

  hmuon4pt = book<TH1D>("muon4pt", ";p_{T}^{#mu 4} [GeV]; Events / bin", 50, 0, 1500);
  hmuon4pt_rebin = book<TH1D>("muon4pt_rebin", ";p_{T}^{#mu 4} [GeV]; Events / bin", 50, 0, 200);
  hmuon4pt_rebin2 = book<TH1D>("muon4pt_rebin2", ";p_{T}^{#mu 4} [GeV]; Events / bin", 50, 0, 50);
  hmuon4eta = book<TH1D>("muon4eta", ";#eta^{#mu 4};Events / bin", 100, -5., 5.);
  hmuon4phi = book<TH1D>("muon4phi", ";#phi^{#mu 4};Events / bin", 70, -3.5, 3.5);
  hmuon4mass = book<TH1D>("muon4mass", ";m^{#mu 4} [GeV];Events / bin", 50, 0, 1500);
  hmuon4energy = book<TH1D>("muon4energy", ";E^{#mu 4} [GeV];Events / bin", 50, 0, 1500);
  hmuon4pfiso = book<TH1D>("muon4pfiso", ";Iso_{PF}^{#mu 4};Events / bin", 100, 0, 1);
  hmuon4dxy = book<TH1D>("muon4dxy", ";#mu 4 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon4dz = book<TH1D>("muon4dz", ";#mu 4 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon4d = book<TH1D>("muon4d", ";#mu 4 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  hmuon4gendrmin = book<TH1D>("muon4gendrmin", ";#DeltaR(#mu 4, closest gen #mu);Events / bin", 60, 0, 3);
  hmuon4genorigin = book<TH1D>("muon4genorigin", ";#mu 4 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hmuon4genflav = book<TH1D>("muon4genflav", ";#mu 4 gen flavor;Events / bin", 16, -0.5, 15.5);

}

void MuonHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through muons
  // ====================


  size_t nmuons = event.muons->size();
  size_t nfromtau = 0;
  size_t nfromhadron = 0;
  size_t nfromelse = 0;
  size_t nunmatched = 0;

  double d_max = 999999.;
  int gen_origin_closest = -1;
  for(size_t i=0; i<nmuons; i++){
    Muon m = event.muons->at(i);
    float gendr_min = 99999.;
    int gen_origin = -1;
    for(const auto & gp : *event.genparticles_all){
      if(abs(gp.pdgid()) != 13) continue;
      if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;
      float dr = deltaR(m, gp);
      if(dr < gendr_min){
        gendr_min = dr;
        if(gendr_min < 0.2){ // these are updated only for better matches than the previous closest match
          if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)) gen_origin = 1;
          else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)) gen_origin = 2;
          else gen_origin = 0;
        }
      }
    }
    if(gen_origin == 1) nfromtau++;
    else if (gen_origin == 2) nfromhadron++;
    else if (gen_origin == 0) nfromelse++;
    else if (gen_origin == -1) nunmatched++;

    if(m.d0() < d_max){
      d_max = m.d0();
      gen_origin_closest = gen_origin;
    }


    hmuonpt->Fill(m.pt(), weight);
    hmuonpt_rebin->Fill(m.pt(), weight);
    hmuonpt_rebin2->Fill(m.pt(), weight);
    hmuoneta->Fill(m.eta(), weight);
    hmuonphi->Fill(m.phi(), weight);
    hmuonmass->Fill(m.m(), weight);
    hmuonenergy->Fill(m.e(), weight);
    hmuonpfiso->Fill(m.iso_rel_04(), weight);
    hmuondxy->Fill(m.dxy(), weight);
    hmuondz->Fill(m.dz(), weight);
    hmuond->Fill(m.d0(), weight);
    hmuon_dxy_vs_dz->Fill(m.dxy(), m.dz(), weight);
    hmuongendrmin->Fill(gendr_min, weight);
    hmuongenorigin->Fill(gen_origin, weight);
    hmuongenflav->Fill(m.gen_part_flav(), weight);

    if(gen_origin == 1){
      hmuonfromtaupt->Fill(m.pt(), weight);
      hmuonfromtaupt_rebin->Fill(m.pt(), weight);
      hmuonfromtaupt_rebin2->Fill(m.pt(), weight);
      hmuonfromtaueta->Fill(m.eta(), weight);
      hmuonfromtauphi->Fill(m.phi(), weight);
      hmuonfromtaumass->Fill(m.m(), weight);
      hmuonfromtauenergy->Fill(m.e(), weight);
      hmuonfromtaupfiso->Fill(m.iso_rel_04(), weight);
      hmuonfromtaudxy->Fill(m.dxy(), weight);
      hmuonfromtaudz->Fill(m.dz(), weight);
      hmuonfromtaud->Fill(m.d0(), weight);
      hmuonfromtau_dxy_vs_dz->Fill(m.dxy(), m.dz(), weight);
      hmuonfromtaugendrmin->Fill(gendr_min, weight);
    }
    else if(gen_origin == 2){
      hmuonfromhadpt->Fill(m.pt(), weight);
      hmuonfromhadpt_rebin->Fill(m.pt(), weight);
      hmuonfromhadpt_rebin2->Fill(m.pt(), weight);
      hmuonfromhadeta->Fill(m.eta(), weight);
      hmuonfromhadphi->Fill(m.phi(), weight);
      hmuonfromhadmass->Fill(m.m(), weight);
      hmuonfromhadenergy->Fill(m.e(), weight);
      hmuonfromhadpfiso->Fill(m.iso_rel_04(), weight);
      hmuonfromhaddxy->Fill(m.dxy(), weight);
      hmuonfromhaddz->Fill(m.dz(), weight);
      hmuonfromhadd->Fill(m.d0(), weight);
      hmuonfromhad_dxy_vs_dz->Fill(m.dxy(), m.dz(), weight);
      hmuonfromhadgendrmin->Fill(gendr_min, weight);
    }
    else if(gen_origin == -1){
      hmuonunmatchedpt->Fill(m.pt(), weight);
      hmuonunmatchedpt_rebin->Fill(m.pt(), weight);
      hmuonunmatchedpt_rebin2->Fill(m.pt(), weight);
      hmuonunmatchedeta->Fill(m.eta(), weight);
      hmuonunmatchedphi->Fill(m.phi(), weight);
      hmuonunmatchedmass->Fill(m.m(), weight);
      hmuonunmatchedenergy->Fill(m.e(), weight);
      hmuonunmatchedpfiso->Fill(m.iso_rel_04(), weight);
      hmuonunmatcheddxy->Fill(m.dxy(), weight);
      hmuonunmatcheddz->Fill(m.dz(), weight);
      hmuonunmatchedd->Fill(m.d0(), weight);
      hmuonunmatched_dxy_vs_dz->Fill(m.dxy(), m.dz(), weight);
      hmuonunmatchedgendrmin->Fill(gendr_min, weight);
    }

    if(i==0){
      hmuon1pt->Fill(m.pt(), weight);
      hmuon1pt_rebin->Fill(m.pt(), weight);
      hmuon1pt_rebin2->Fill(m.pt(), weight);
      hmuon1eta->Fill(m.eta(), weight);
      hmuon1phi->Fill(m.phi(), weight);
      hmuon1mass->Fill(m.m(), weight);
      hmuon1energy->Fill(m.e(), weight);
      hmuon1pfiso->Fill(m.iso_rel_04(), weight);
      hmuon1dxy->Fill(m.dxy(), weight);
      hmuon1dz->Fill(m.dz(), weight);
      hmuon1d->Fill(m.d0(), weight);
      hmuon1gendrmin->Fill(gendr_min, weight);
      hmuon1genorigin->Fill(gen_origin, weight);
      hmuon1genflav->Fill(m.gen_part_flav(), weight);
    }
    else if(i==1){
      hmuon2pt->Fill(m.pt(), weight);
      hmuon2pt_rebin->Fill(m.pt(), weight);
      hmuon2pt_rebin2->Fill(m.pt(), weight);
      hmuon2eta->Fill(m.eta(), weight);
      hmuon2phi->Fill(m.phi(), weight);
      hmuon2mass->Fill(m.m(), weight);
      hmuon2energy->Fill(m.e(), weight);
      hmuon2pfiso->Fill(m.iso_rel_04(), weight);
      hmuon2dxy->Fill(m.dxy(), weight);
      hmuon2dz->Fill(m.dz(), weight);
      hmuon2d->Fill(m.d0(), weight);
      hmuon2gendrmin->Fill(gendr_min, weight);
      hmuon2genorigin->Fill(gen_origin, weight);
      hmuon2genflav->Fill(m.gen_part_flav(), weight);
    }
    else if(i==2){
      hmuon3pt->Fill(m.pt(), weight);
      hmuon3pt_rebin->Fill(m.pt(), weight);
      hmuon3pt_rebin2->Fill(m.pt(), weight);
      hmuon3eta->Fill(m.eta(), weight);
      hmuon3phi->Fill(m.phi(), weight);
      hmuon3mass->Fill(m.m(), weight);
      hmuon3energy->Fill(m.e(), weight);
      hmuon3pfiso->Fill(m.iso_rel_04(), weight);
      hmuon3dxy->Fill(m.dxy(), weight);
      hmuon3dz->Fill(m.dz(), weight);
      hmuon3d->Fill(m.d0(), weight);
      hmuon3gendrmin->Fill(gendr_min, weight);
      hmuon3genorigin->Fill(gen_origin, weight);
      hmuon3genflav->Fill(m.gen_part_flav(), weight);
    }
    else if(i==3){
      hmuon4pt->Fill(m.pt(), weight);
      hmuon4pt_rebin->Fill(m.pt(), weight);
      hmuon4pt_rebin2->Fill(m.pt(), weight);
      hmuon4eta->Fill(m.eta(), weight);
      hmuon4phi->Fill(m.phi(), weight);
      hmuon4mass->Fill(m.m(), weight);
      hmuon4energy->Fill(m.e(), weight);
      hmuon4pfiso->Fill(m.iso_rel_04(), weight);
      hmuon4dxy->Fill(m.dxy(), weight);
      hmuon4dz->Fill(m.dz(), weight);
      hmuon4d->Fill(m.d0(), weight);
      hmuon4gendrmin->Fill(gendr_min, weight);
      hmuon4genorigin->Fill(gen_origin, weight);
      hmuon4genflav->Fill(m.gen_part_flav(), weight);
    }
  }
  hnmuons->Fill(nmuons, weight);
  hnmuonsfromtau->Fill(nfromtau, weight);
  hnmuonsfromhad->Fill(nfromhadron, weight);
  hnmuonsunmatched->Fill(nunmatched, weight);
  hnmuonsgenfromtau->Fill(nfromtau, weight);
  hnmuonsgenfromhadron->Fill(nfromhadron, weight);
  hnmuonsgenfromelse->Fill(nfromelse, weight);
  hnmuonsgenunmatched->Fill(nunmatched, weight);

  hmuonclosestorigin->Fill(gen_origin_closest, weight);
  hmuonclosestd->Fill(d_max, weight);
}
