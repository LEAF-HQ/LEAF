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
  htaueta = book<TH1D>("taueta", ";#eta^{#tau};Events / bin", 100, -5., 5.);
  htauphi = book<TH1D>("tauphi", ";#phi^{#tau};Events / bin", 70, -3.5, 3.5);
  htaumass = book<TH1D>("taumass", ";m^{#tau} [GeV];Events / bin", 50, 0, 1500);
  htauenergy = book<TH1D>("tauenergy", ";E^{#tau 1} [GeV];Events / bin", 50, 0, 1500);
  htau1pt = book<TH1D>("tau1pt", ";p_{T}^{#tau 1} [GeV]; Events / bin", 50, 0, 1500);
  htau1eta = book<TH1D>("tau1eta", ";#eta^{#tau 1};Events / bin", 100, -5., 5.);
  htau1phi = book<TH1D>("tau1phi", ";#phi^{#tau 1};Events / bin", 70, -3.5, 3.5);
  htau1mass = book<TH1D>("tau1mass", ";m^{#tau 1} [GeV];Events / bin", 50, 0, 1500);
  htau1energy = book<TH1D>("tau1energy", ";E^{#tau 1} [GeV];Events / bin", 50, 0, 1500);
  htau2pt = book<TH1D>("tau2pt", ";p_{T}^{#tau 2} [GeV]; Events / bin", 50, 0, 1500);
  htau2eta = book<TH1D>("tau2eta", ";#eta^{#tau 2};Events / bin", 100, -5., 5.);
  htau2phi = book<TH1D>("tau2phi", ";#phi^{#tau 2};Events / bin", 70, -3.5, 3.5);
  htau2mass = book<TH1D>("tau2mass", ";m^{#tau 2} [GeV];Events / bin", 50, 0, 1500);
  htau2energy = book<TH1D>("tau2energy", ";E^{#tau 2} [GeV];Events / bin", 50, 0, 1500);
  htau3pt = book<TH1D>("tau3pt", ";p_{T}^{#tau 3} [GeV]; Events / bin", 50, 0, 1500);
  htau3eta = book<TH1D>("tau3eta", ";#eta^{#tau 3};Events / bin", 100, -5., 5.);
  htau3phi = book<TH1D>("tau3phi", ";#phi^{#tau 3};Events / bin", 70, -3.5, 3.5);
  htau3mass = book<TH1D>("tau3mass", ";m^{#tau 3} [GeV];Events / bin", 50, 0, 1500);
  htau3energy = book<TH1D>("tau3energy", ";E^{#tau 3} [GeV];Events / bin", 50, 0, 1500);
  htau4pt = book<TH1D>("tau4pt", ";p_{T}^{#tau 4} [GeV]; Events / bin", 50, 0, 1500);
  htau4eta = book<TH1D>("tau4eta", ";#eta^{#tau 4};Events / bin", 100, -5., 5.);
  htau4phi = book<TH1D>("tau4phi", ";#phi^{#tau 4};Events / bin", 70, -3.5, 3.5);
  htau4mass = book<TH1D>("tau4mass", ";m^{#tau 4} [GeV];Events / bin", 50, 0, 1500);
  htau4energy = book<TH1D>("tau4energy", ";E^{#tau 4} [GeV];Events / bin", 50, 0, 1500);

}

void TauHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t ntaus = event.taus->size();
  for(size_t i=0; i<ntaus; i++){
    Tau t = event.taus->at(i);

    htaupt->Fill(t.pt(), weight);
    htaueta->Fill(t.eta(), weight);
    htauphi->Fill(t.phi(), weight);
    htaumass->Fill(t.m(), weight);
    htauenergy->Fill(t.e(), weight);

    if(i==0){
      htau1pt->Fill(t.pt(), weight);
      htau1eta->Fill(t.eta(), weight);
      htau1phi->Fill(t.phi(), weight);
      htau1mass->Fill(t.m(), weight);
      htau1energy->Fill(t.e(), weight);
    }
    else if(i==1){
      htau2pt->Fill(t.pt(), weight);
      htau2eta->Fill(t.eta(), weight);
      htau2phi->Fill(t.phi(), weight);
      htau2mass->Fill(t.m(), weight);
      htau2energy->Fill(t.e(), weight);
    }
    else if(i==2){
      htau3pt->Fill(t.pt(), weight);
      htau3eta->Fill(t.eta(), weight);
      htau3phi->Fill(t.phi(), weight);
      htau3mass->Fill(t.m(), weight);
      htau3energy->Fill(t.e(), weight);
    }
    else if(i==3){
      htau4pt->Fill(t.pt(), weight);
      htau4eta->Fill(t.eta(), weight);
      htau4phi->Fill(t.phi(), weight);
      htau4mass->Fill(t.m(), weight);
      htau4energy->Fill(t.e(), weight);
    }
  }
  hntaus->Fill(ntaus, weight);
}
