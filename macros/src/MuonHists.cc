#include "include/MuonHists.h"
// #include "include/cosmetics.h"
#include "include/constants.h"
#include "include/useful_functions.h"
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
  hmuonpt = book<TH1D>("muonpt", ";p_{T}^{#mu} [GeV]; Events / bin", 150, 0, 3000);
  hmuoneta = book<TH1D>("muoneta", ";#eta^{#mu};Events / bin", 100, -5., 5.);
  hmuonphi = book<TH1D>("muonphi", ";#phi^{#mu};Events / bin", 70, -3.5, 3.5);
  hmuonmass = book<TH1D>("muonmass", ";m^{#mu} [GeV];Events / bin", 150, 0, 3000);
  hmuonenergy = book<TH1D>("muonenergy", ";E^{#mu} [GeV];Events / bin", 150, 0, 3000);
  hmuon1pt = book<TH1D>("muon1pt", ";p_{T}^{#mu 1} [GeV]; Events / bin", 150, 0, 3000);
  hmuon1eta = book<TH1D>("muon1eta", ";#eta^{#mu 1};Events / bin", 100, -5., 5.);
  hmuon1phi = book<TH1D>("muon1phi", ";#phi^{#mu 1};Events / bin", 70, -3.5, 3.5);
  hmuon1mass = book<TH1D>("muon1mass", ";m^{#mu 1} [GeV];Events / bin", 150, 0, 3000);
  hmuon1energy = book<TH1D>("muon1energy", ";E^{#mu 1} [GeV];Events / bin", 150, 0, 3000);
  hmuon2pt = book<TH1D>("muon2pt", ";p_{T}^{#mu 2} [GeV]; Events / bin", 150, 0, 3000);
  hmuon2eta = book<TH1D>("muon2eta", ";#eta^{#mu 2};Events / bin", 100, -5., 5.);
  hmuon2phi = book<TH1D>("muon2phi", ";#phi^{#mu 2};Events / bin", 70, -3.5, 3.5);
  hmuon2mass = book<TH1D>("muon2mass", ";m^{#mu 2} [GeV];Events / bin", 150, 0, 3000);
  hmuon2energy = book<TH1D>("muon2energy", ";E^{#mu 2} [GeV];Events / bin", 150, 0, 3000);
  hmuon3pt = book<TH1D>("muon3pt", ";p_{T}^{#mu 3} [GeV]; Events / bin", 150, 0, 3000);
  hmuon3eta = book<TH1D>("muon3eta", ";#eta^{#mu 3};Events / bin", 100, -5., 5.);
  hmuon3phi = book<TH1D>("muon3phi", ";#phi^{#mu 3};Events / bin", 70, -3.5, 3.5);
  hmuon3mass = book<TH1D>("muon3mass", ";m^{#mu 3} [GeV];Events / bin", 150, 0, 3000);
  hmuon3energy = book<TH1D>("muon3energy", ";E^{#mu 3} [GeV];Events / bin", 150, 0, 3000);
  hmuon4pt = book<TH1D>("muon4pt", ";p_{T}^{#mu 4} [GeV]; Events / bin", 150, 0, 3000);
  hmuon4eta = book<TH1D>("muon4eta", ";#eta^{#mu 4};Events / bin", 100, -5., 5.);
  hmuon4phi = book<TH1D>("muon4phi", ";#phi^{#mu 4};Events / bin", 70, -3.5, 3.5);
  hmuon4mass = book<TH1D>("muon4mass", ";m^{#mu 4} [GeV];Events / bin", 150, 0, 3000);
  hmuon4energy = book<TH1D>("muon4energy", ";E^{#mu 4} [GeV];Events / bin", 150, 0, 3000);

}

void MuonHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t nmuons = event.muons->size();
  for(size_t i=0; i<nmuons; i++){
    Muon m = event.muons->at(i);

      hmuonpt->Fill(m.pt(), weight);
      hmuoneta->Fill(m.eta(), weight);
      hmuonphi->Fill(m.phi(), weight);
      hmuonmass->Fill(m.m(), weight);
      hmuonenergy->Fill(m.e(), weight);

    if(i==0){
      hmuon1pt->Fill(m.pt(), weight);
      hmuon1eta->Fill(m.eta(), weight);
      hmuon1phi->Fill(m.phi(), weight);
      hmuon1mass->Fill(m.m(), weight);
      hmuon1energy->Fill(m.e(), weight);
    }
    else if(i==1){
      hmuon2pt->Fill(m.pt(), weight);
      hmuon2eta->Fill(m.eta(), weight);
      hmuon2phi->Fill(m.phi(), weight);
      hmuon2mass->Fill(m.m(), weight);
      hmuon2energy->Fill(m.e(), weight);
    }
    else if(i==2){
      hmuon3pt->Fill(m.pt(), weight);
      hmuon3eta->Fill(m.eta(), weight);
      hmuon3phi->Fill(m.phi(), weight);
      hmuon3mass->Fill(m.m(), weight);
      hmuon3energy->Fill(m.e(), weight);
    }
    else if(i==3){
      hmuon4pt->Fill(m.pt(), weight);
      hmuon4eta->Fill(m.eta(), weight);
      hmuon4phi->Fill(m.phi(), weight);
      hmuon4mass->Fill(m.m(), weight);
      hmuon4energy->Fill(m.e(), weight);
    }
    else break;
  }
  hnmuons->Fill(nmuons, weight);
}
