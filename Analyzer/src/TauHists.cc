#include "Analyzer/include/TauHists.h"
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

TauHists::TauHists(TString dir_) : BaseHists(dir_){

  hntaus = book<TH1D>("ntaus", ";N_{#tau}; Events / bin", 11, -0.5, 10.5);
  htaupt = book<TH1D>("taupt", ";p_{T}^{#tau} [GeV]; Events / bin", 50, 0, 1500);
  htaupt_rebin = book<TH1D>("taupt_rebin", ";p_{T}^{#tau} [GeV]; Events / bin", 50, 0, 200);
  htaupt_rebin2 = book<TH1D>("taupt_rebin2", ";p_{T}^{#tau} [GeV]; Events / bin", 50, 0, 50);
  htaueta = book<TH1D>("taueta", ";#eta^{#tau};Events / bin", 100, -5., 5.);
  htauphi = book<TH1D>("tauphi", ";#phi^{#tau};Events / bin", 70, -3.5, 3.5);
  htaumass = book<TH1D>("taumass", ";m^{#tau} [GeV];Events / bin", 50, 0, 1500);
  htauenergy = book<TH1D>("tauenergy", ";E^{#tau} [GeV];Events / bin", 50, 0, 1500);
  htauiso = book<TH1D>("tauiso", ";Iso^{#tau} [GeV];Events / bin", 100, 0, 1);
  htaudecaymode = book<TH1D>("taudecaymode", ";#tau decay mode;Events / bin", 12, -0.5, 11.5);
  htauorigin = book<TH1D>("tauorigin", ";#tau origin;Events / bin", 6, -0.5, 5.5);
  htaudxy = book<TH1D>("taudxy", ";#tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaudz = book<TH1D>("taudz", ";#tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaud = book<TH1D>("taud", ";#tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaugendrmin = book<TH1D>("taugendrmin", ";#DeltaR(#tau_{h}, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htaugenstatus = book<TH1D>("taugenstatus", ";Status of matched vis. gen. #tau_{h};Events / bin", 16, -0.5, 15.5);

  hntausmatched = book<TH1D>("ntausmatched", ";N_{gen-matched #tau_{h}}; Events / bin", 11, -0.5, 10.5);
  htaumatchedpt = book<TH1D>("taumatchedpt", ";p_{T}^{gen-matched #tau_{h}} [GeV]; Events / bin", 50, 0, 1500);
  htaumatchedpt_rebin = book<TH1D>("taumatchedpt_rebin", ";p_{T}^{gen-matched #tau} [GeV]; Events / bin", 50, 0, 200);
  htaumatchedpt_rebin2 = book<TH1D>("taumatchedpt_rebin2", ";p_{T}^{gen-matched #tau} [GeV]; Events / bin", 50, 0, 50);
  htaumatchedeta = book<TH1D>("taumatchedeta", ";#eta^{gen-matched #tau_{h}};Events / bin", 100, -5., 5.);
  htaumatchedphi = book<TH1D>("taumatchedphi", ";#phi^{gen-matched #tau_{h}};Events / bin", 70, -3.5, 3.5);
  htaumatchedmass = book<TH1D>("taumatchedmass", ";m^{gen-matched #tau_{h}} [GeV];Events / bin", 50, 0, 1500);
  htaumatchedenergy = book<TH1D>("taumatchedenergy", ";E^{gen-matched #tau_{h}} [GeV];Events / bin", 50, 0, 1500);
  htaumatchediso = book<TH1D>("taumatchediso", ";Iso^{gen-matched #tau} [GeV];Events / bin", 100, 0, 1);
  htaumatcheddecaymode = book<TH1D>("taumatcheddecaymode", ";gen-matched #tau decay mode;Events / bin", 12, -0.5, 11.5);
  htaumatchedorigin = book<TH1D>("taumatchedorigin", ";gen-matched #tau origin;Events / bin", 6, -0.5, 5.5);
  htaumatcheddxy = book<TH1D>("taumatcheddxy", ";gen-matched #tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaumatcheddz = book<TH1D>("taumatcheddz", ";gen-matched #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaumatchedd = book<TH1D>("taumatchedd", ";gen-matched #tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htaumatchedgendrmin = book<TH1D>("taumatchedgendrmin", ";#DeltaR(gen-matched #tau_{h}, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htaumatchedgenstatus = book<TH1D>("taumatchedgenstatus", ";Status of matched vis. gen. gen-matched #tau_{h};Events / bin", 16, -0.5, 15.5);

  hntausunmatched = book<TH1D>("ntausunmatched", ";N_{unmatched #tau_{h}}; Events / bin", 11, -0.5, 10.5);
  htauunmatchedpt = book<TH1D>("tauunmatchedpt", ";p_{T}^{unmatched #tau_{h}} [GeV]; Events / bin", 50, 0, 1500);
  htauunmatchedpt_rebin = book<TH1D>("tauunmatchedpt_rebin", ";p_{T}^{unmatched #tau_{h}} [GeV]; Events / bin", 50, 0, 200);
  htauunmatchedpt_rebin2 = book<TH1D>("tauunmatchedpt_rebin2", ";p_{T}^{unmatched #tau_{h}} [GeV]; Events / bin", 50, 0, 50);
  htauunmatchedeta = book<TH1D>("tauunmatchedeta", ";#eta^{unmatched #tau_{h}};Events / bin", 100, -5., 5.);
  htauunmatchedphi = book<TH1D>("tauunmatchedphi", ";#phi^{unmatched #tau_{h}};Events / bin", 70, -3.5, 3.5);
  htauunmatchedmass = book<TH1D>("tauunmatchedmass", ";m^{unmatched #tau_{h}} [GeV];Events / bin", 50, 0, 1500);
  htauunmatchedenergy = book<TH1D>("tauunmatchedenergy", ";E^{unmatched #tau_{h}} [GeV];Events / bin", 50, 0, 1500);
  htauunmatchediso = book<TH1D>("tauunmatchediso", ";Iso^{unmatched #tau} [GeV];Events / bin", 100, 0, 1);
  htauunmatcheddecaymode = book<TH1D>("tauunmatcheddecaymode", ";unmatched #tau decay mode;Events / bin", 12, -0.5, 11.5);
  htauunmatchedorigin = book<TH1D>("tauunmatchedorigin", ";unmatched #tau origin;Events / bin", 6, -0.5, 5.5);
  htauunmatcheddxy = book<TH1D>("tauunmatcheddxy", ";unmatched #tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htauunmatcheddz = book<TH1D>("tauunmatcheddz", ";unmatched #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htauunmatchedd = book<TH1D>("tauunmatchedd", ";unmatched #tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htauunmatchedgendrmin = book<TH1D>("tauunmatchedgendrmin", ";#DeltaR(unmatched #tau_{h}, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htauunmatchedgenstatus = book<TH1D>("tauunmatchedgenstatus", ";Status of matched vis. gen. #tau_{h};Events / bin", 16, -0.5, 15.5);

  htau1pt = book<TH1D>("tau1pt", ";p_{T}^{#tau 1} [GeV]; Events / bin", 50, 0, 1500);
  htau1pt_rebin = book<TH1D>("tau1pt_rebin", ";p_{T}^{#tau 1} [GeV]; Events / bin", 50, 0, 200);
  htau1pt_rebin2 = book<TH1D>("tau1pt_rebin2", ";p_{T}^{#tau 1} [GeV]; Events / bin", 50, 0, 50);
  htau1eta = book<TH1D>("tau1eta", ";#eta^{#tau 1};Events / bin", 100, -5., 5.);
  htau1phi = book<TH1D>("tau1phi", ";#phi^{#tau 1};Events / bin", 70, -3.5, 3.5);
  htau1mass = book<TH1D>("tau1mass", ";m^{#tau 1} [GeV];Events / bin", 50, 0, 1500);
  htau1energy = book<TH1D>("tau1energy", ";E^{#tau 1} [GeV];Events / bin", 50, 0, 1500);
  htau1iso = book<TH1D>("tau1iso", ";Iso^{#tau 1} [GeV];Events / bin", 100, 0, 1);
  htau1decaymode = book<TH1D>("tau1decaymode", ";#tau 1 decay mode;Events / bin", 12, -0.5, 11.5);
  htau1origin = book<TH1D>("tau1origin", ";#tau 1 origin;Events / bin", 6, -0.5, 5.5);
  htau1dxy = book<TH1D>("tau1dxy", ";#tau 1 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau1dz = book<TH1D>("tau1dz", ";#tau 1 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau1d = book<TH1D>("tau1d", ";#tau 1 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau1gendrmin = book<TH1D>("tau1gendrmin", ";#DeltaR(#tau_{h} 1, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htau1genstatus = book<TH1D>("tau1genstatus", ";Status of matched vis. gen. #tau_{h} 1;Events / bin", 16, -0.5, 15.5);

  htau2pt = book<TH1D>("tau2pt", ";p_{T}^{#tau 2} [GeV]; Events / bin", 50, 0, 1500);
  htau2pt_rebin = book<TH1D>("tau2pt_rebin", ";p_{T}^{#tau 2} [GeV]; Events / bin", 50, 0, 200);
  htau2pt_rebin2 = book<TH1D>("tau2pt_rebin2", ";p_{T}^{#tau 2} [GeV]; Events / bin", 50, 0, 50);
  htau2eta = book<TH1D>("tau2eta", ";#eta^{#tau 2};Events / bin", 100, -5., 5.);
  htau2phi = book<TH1D>("tau2phi", ";#phi^{#tau 2};Events / bin", 70, -3.5, 3.5);
  htau2mass = book<TH1D>("tau2mass", ";m^{#tau 2} [GeV];Events / bin", 50, 0, 1500);
  htau2energy = book<TH1D>("tau2energy", ";E^{#tau 2} [GeV];Events / bin", 50, 0, 1500);
  htau2iso = book<TH1D>("tau2iso", ";Iso^{#tau 2} [GeV];Events / bin", 100, 0, 1);
  htau2decaymode = book<TH1D>("tau2decaymode", ";#tau 2 decay mode;Events / bin", 12, -0.5, 11.5);
  htau2origin = book<TH1D>("tau2origin", ";#tau 2 origin;Events / bin", 6, -0.5, 5.5);
  htau2dxy = book<TH1D>("tau2dxy", ";#tau 2 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau2dz = book<TH1D>("tau2dz", ";#tau 2 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau2d = book<TH1D>("tau2d", ";#tau 2 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau2gendrmin = book<TH1D>("tau2gendrmin", ";#DeltaR(#tau_{h} 2, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htau2genstatus = book<TH1D>("tau2genstatus", ";Status of matched vis. gen. #tau_{h} 2;Events / bin", 16, -0.5, 15.5);

  htau3pt = book<TH1D>("tau3pt", ";p_{T}^{#tau 3} [GeV]; Events / bin", 50, 0, 1500);
  htau3pt_rebin = book<TH1D>("tau3pt_rebin", ";p_{T}^{#tau 3} [GeV]; Events / bin", 50, 0, 200);
  htau3pt_rebin2 = book<TH1D>("tau3pt_rebin2", ";p_{T}^{#tau 3} [GeV]; Events / bin", 50, 0, 50);
  htau3eta = book<TH1D>("tau3eta", ";#eta^{#tau 3};Events / bin", 100, -5., 5.);
  htau3phi = book<TH1D>("tau3phi", ";#phi^{#tau 3};Events / bin", 70, -3.5, 3.5);
  htau3mass = book<TH1D>("tau3mass", ";m^{#tau 3} [GeV];Events / bin", 50, 0, 1500);
  htau3energy = book<TH1D>("tau3energy", ";E^{#tau 3} [GeV];Events / bin", 50, 0, 1500);
  htau3iso = book<TH1D>("tau3iso", ";Iso^{#tau 3} [GeV];Events / bin", 100, 0, 1);
  htau3decaymode = book<TH1D>("tau3decaymode", ";#tau 3 decay mode;Events / bin", 12, -0.5, 11.5);
  htau3origin = book<TH1D>("tau3origin", ";#tau 3 origin;Events / bin", 6, -0.5, 5.5);
  htau3dxy = book<TH1D>("tau3dxy", ";#tau 3 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau3dz = book<TH1D>("tau3dz", ";#tau 3 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau3d = book<TH1D>("tau3d", ";#tau 3 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau3gendrmin = book<TH1D>("tau3gendrmin", ";#DeltaR(#tau_{h} 3, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htau3genstatus = book<TH1D>("tau3genstatus", ";Status of matched vis. gen. #tau_{h} 3;Events / bin", 16, -0.5, 15.5);

  htau4pt = book<TH1D>("tau4pt", ";p_{T}^{#tau 4} [GeV]; Events / bin", 50, 0, 1500);
  htau4pt_rebin = book<TH1D>("tau4pt_rebin", ";p_{T}^{#tau 4} [GeV]; Events / bin", 50, 0, 200);
  htau4pt_rebin2 = book<TH1D>("tau4pt_rebin2", ";p_{T}^{#tau 4} [GeV]; Events / bin", 50, 0, 50);
  htau4eta = book<TH1D>("tau4eta", ";#eta^{#tau 4};Events / bin", 100, -5., 5.);
  htau4phi = book<TH1D>("tau4phi", ";#phi^{#tau 4};Events / bin", 70, -3.5, 3.5);
  htau4mass = book<TH1D>("tau4mass", ";m^{#tau 4} [GeV];Events / bin", 50, 0, 1500);
  htau4energy = book<TH1D>("tau4energy", ";E^{#tau 4} [GeV];Events / bin", 50, 0, 1500);
  htau4iso = book<TH1D>("tau4iso", ";Iso^{#tau 4} [GeV];Events / bin", 100, 0, 1);
  htau4decaymode = book<TH1D>("tau4decaymode", ";#tau 4 decay mode;Events / bin", 12, -0.5, 11.5);
  htau4origin = book<TH1D>("tau4origin", ";#tau 4 origin;Events / bin", 6, -0.5, 5.5);
  htau4dxy = book<TH1D>("tau4dxy", ";#tau 4 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau4dz = book<TH1D>("tau4dz", ";#tau 4 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau4d = book<TH1D>("tau4d", ";#tau 4 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  htau4gendrmin = book<TH1D>("tau4gendrmin", ";#DeltaR(#tau_{h} 4, closest vis. gen #tau_{h});Events / bin", 60, 0, 3);
  htau4genstatus = book<TH1D>("tau4genstatus", ";Status of matched vis. gen. #tau_{h} 4;Events / bin", 16, -0.5, 15.5);

}

void TauHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t ntaus = event.taus->size();
  size_t nmatched = 0;
  size_t nunmatched = 0;
  for(size_t i=0; i<ntaus; i++){
    Tau t = event.taus->at(i);
    float gendr_min = 99999.;
    int gen_status = false;
    for(const auto & gp : *event.genparticles_visibletaus){
      float dr = deltaR(t, gp);
      if(dr < gendr_min){
        gendr_min = dr;
        if(gendr_min < 0.2) gen_status = gp.status();
      }
    }

    float d_pv = sqrt(t.dxy()*t.dxy() + t.dz()*t.dz());

    if(gendr_min < 0.2) {
      nmatched++;
      htaumatchedpt->Fill(t.pt(), weight);
      htaumatchedpt_rebin->Fill(t.pt(), weight);
      htaumatchedpt_rebin2->Fill(t.pt(), weight);
      htaumatchedeta->Fill(t.eta(), weight);
      htaumatchedphi->Fill(t.phi(), weight);
      htaumatchedmass->Fill(t.m(), weight);
      htaumatchedenergy->Fill(t.e(), weight);
      htaumatchediso->Fill(t.comb_iso(), weight);
      htaumatcheddecaymode->Fill(t.decay_mode(), weight);
      htaumatchedorigin->Fill((int)t.gen_part_flav(), weight);
      htaumatcheddxy->Fill(t.dxy(), weight);
      htaumatcheddz->Fill(t.dz(), weight);
      htaumatchedd->Fill(d_pv, weight);
      htaumatchedgendrmin->Fill(gendr_min, weight);
      htaumatchedgenstatus->Fill(gen_status, weight);
    }
    else{
      nunmatched++;
      htauunmatchedpt->Fill(t.pt(), weight);
      htauunmatchedpt_rebin->Fill(t.pt(), weight);
      htauunmatchedpt_rebin2->Fill(t.pt(), weight);
      htauunmatchedeta->Fill(t.eta(), weight);
      htauunmatchedphi->Fill(t.phi(), weight);
      htauunmatchedmass->Fill(t.m(), weight);
      htauunmatchedenergy->Fill(t.e(), weight);
      htauunmatchediso->Fill(t.comb_iso(), weight);
      htauunmatcheddecaymode->Fill(t.decay_mode(), weight);
      htauunmatchedorigin->Fill((int)t.gen_part_flav(), weight);
      htauunmatcheddxy->Fill(t.dxy(), weight);
      htauunmatcheddz->Fill(t.dz(), weight);
      htauunmatchedd->Fill(d_pv, weight);
      htauunmatchedgendrmin->Fill(gendr_min, weight);
      htauunmatchedgenstatus->Fill(gen_status, weight);
    }

    htaupt->Fill(t.pt(), weight);
    htaupt_rebin->Fill(t.pt(), weight);
    htaupt_rebin2->Fill(t.pt(), weight);
    htaueta->Fill(t.eta(), weight);
    htauphi->Fill(t.phi(), weight);
    htaumass->Fill(t.m(), weight);
    htauenergy->Fill(t.e(), weight);
    htauiso->Fill(t.comb_iso(), weight);
    htaudecaymode->Fill(t.decay_mode(), weight);
    htauorigin->Fill((int)t.gen_part_flav(), weight);
    htaudxy->Fill(t.dxy(), weight);
    htaudz->Fill(t.dz(), weight);
    htaud->Fill(d_pv, weight);
    htaugendrmin->Fill(gendr_min, weight);
    htaugenstatus->Fill(gen_status, weight);

    if(i==0){
      htau1pt->Fill(t.pt(), weight);
      htau1pt_rebin->Fill(t.pt(), weight);
      htau1pt_rebin2->Fill(t.pt(), weight);
      htau1eta->Fill(t.eta(), weight);
      htau1phi->Fill(t.phi(), weight);
      htau1mass->Fill(t.m(), weight);
      htau1energy->Fill(t.e(), weight);
      htau1iso->Fill(t.comb_iso(), weight);
      htau1decaymode->Fill(t.decay_mode(), weight);
      htau1origin->Fill((int)t.gen_part_flav(), weight);
      htau1dxy->Fill(t.dxy(), weight);
      htau1dz->Fill(t.dz(), weight);
      htau1d->Fill(d_pv, weight);
      htau1gendrmin->Fill(gendr_min, weight);
      htau1genstatus->Fill(gen_status, weight);
    }
    else if(i==1){
      htau2pt->Fill(t.pt(), weight);
      htau2pt_rebin->Fill(t.pt(), weight);
      htau2pt_rebin2->Fill(t.pt(), weight);
      htau2eta->Fill(t.eta(), weight);
      htau2phi->Fill(t.phi(), weight);
      htau2mass->Fill(t.m(), weight);
      htau2energy->Fill(t.e(), weight);
      htau2iso->Fill(t.comb_iso(), weight);
      htau2decaymode->Fill(t.decay_mode(), weight);
      htau2origin->Fill((int)t.gen_part_flav(), weight);
      htau2dxy->Fill(t.dxy(), weight);
      htau2dz->Fill(t.dz(), weight);
      htau2d->Fill(d_pv, weight);
      htau2gendrmin->Fill(gendr_min, weight);
      htau2genstatus->Fill(gen_status, weight);
    }
    else if(i==2){
      htau3pt->Fill(t.pt(), weight);
      htau3pt_rebin->Fill(t.pt(), weight);
      htau3pt_rebin2->Fill(t.pt(), weight);
      htau3eta->Fill(t.eta(), weight);
      htau3phi->Fill(t.phi(), weight);
      htau3mass->Fill(t.m(), weight);
      htau3energy->Fill(t.e(), weight);
      htau3iso->Fill(t.comb_iso(), weight);
      htau3decaymode->Fill(t.decay_mode(), weight);
      htau3origin->Fill((int)t.gen_part_flav(), weight);
      htau3dxy->Fill(t.dxy(), weight);
      htau3dz->Fill(t.dz(), weight);
      htau3d->Fill(d_pv, weight);
      htau3gendrmin->Fill(gendr_min, weight);
      htau3genstatus->Fill(gen_status, weight);
    }
    else if(i==3){
      htau4pt->Fill(t.pt(), weight);
      htau4pt_rebin->Fill(t.pt(), weight);
      htau4pt_rebin2->Fill(t.pt(), weight);
      htau4eta->Fill(t.eta(), weight);
      htau4phi->Fill(t.phi(), weight);
      htau4mass->Fill(t.m(), weight);
      htau4energy->Fill(t.e(), weight);
      htau4iso->Fill(t.comb_iso(), weight);
      htau4decaymode->Fill(t.decay_mode(), weight);
      htau4origin->Fill((int)t.gen_part_flav(), weight);
      htau4dxy->Fill(t.dxy(), weight);
      htau4dz->Fill(t.dz(), weight);
      htau4d->Fill(d_pv, weight);
      htau4gendrmin->Fill(gendr_min, weight);
      htau4genstatus->Fill(gen_status, weight);
    }
  }
  hntaus->Fill(ntaus, weight);
  hntausmatched->Fill(nmatched, weight);
  hntausunmatched->Fill(nunmatched, weight);
}
