#include "include/JetHists.h"
#include "include/cosmetics.h"
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

JetHists::JetHists(TString dir_) : BaseHists(dir_){

  hnjets = book<TH1D>("njets", ";N_{jets}; Events / bin", 11, -0.5, 10.5);
  hjetpt = book<TH1D>("jetpt", ";p_{T}^{jets} [GeV]; Events / bin", 150, 0, 3000);
  hjeteta = book<TH1D>("jeteta", ";#eta^{jets};Events / bin", 100, -5., 5.);
  hjetphi = book<TH1D>("jetphi", ";#phi^{jets};Events / bin", 70, -3.5, 3.5);
  hjetmass = book<TH1D>("jetmass", ";m^{jets} [GeV];Events / bin", 150, 0, 3000);
  hjetenergy = book<TH1D>("jetenergy", ";E^{jets} [GeV];Events / bin", 150, 0, 3000);
  hjetdrminele = book<TH1D>("hjetdrminele", ";#DeltaR_{min} (jet, e);Events / bin", 100, 0, 5);
  hjetdrminmuon = book<TH1D>("hjetdrminmuon", ";#DeltaR_{min} (jet, #mu);Events / bin", 100, 0, 5);
  hjetdrmintau = book<TH1D>("hjetdrmintau", ";#DeltaR_{min} (jet, #tau);Events / bin", 100, 0, 5);
  hjet1pt = book<TH1D>("jet1pt", ";p_{T}^{jet 1} [GeV]; Events / bin", 150, 0, 3000);
  hjet1eta = book<TH1D>("jet1eta", ";#eta^{jet 1};Events / bin", 100, -5., 5.);
  hjet1phi = book<TH1D>("jet1phi", ";#phi^{jet 1};Events / bin", 70, -3.5, 3.5);
  hjet1mass = book<TH1D>("jet1mass", ";m^{jet 1} [GeV];Events / bin", 150, 0, 3000);
  hjet1energy = book<TH1D>("jet1energy", ";E^{jet 1} [GeV];Events / bin", 150, 0, 3000);
  hjet1drminele = book<TH1D>("hjet1drminele", ";#DeltaR_{min} (jet1, e);Events / bin", 100, 0, 5);
  hjet1drminmuon = book<TH1D>("hjet1drminmuon", ";#DeltaR_{min} (jet1, #mu);Events / bin", 100, 0, 5);
  hjet1drmintau = book<TH1D>("hjet1drmintau", ";#DeltaR_{min} (jet1, #tau);Events / bin", 100, 0, 5);
  hjet2pt = book<TH1D>("jet2pt", ";p_{T}^{jet 2} [GeV]; Events / bin", 150, 0, 3000);
  hjet2eta = book<TH1D>("jet2eta", ";#eta^{jet 2};Events / bin", 100, -5., 5.);
  hjet2phi = book<TH1D>("jet2phi", ";#phi^{jet 2};Events / bin", 70, -3.5, 3.5);
  hjet2mass = book<TH1D>("jet2mass", ";m^{jet 2} [GeV];Events / bin", 150, 0, 3000);
  hjet2energy = book<TH1D>("jet2energy", ";E^{jet 2} [GeV];Events / bin", 150, 0, 3000);
  hjet2drminele = book<TH1D>("hjet2drminele", ";#DeltaR_{min} (jet2, e);Events / bin", 100, 0, 5);
  hjet2drminmuon = book<TH1D>("hjet2drminmuon", ";#DeltaR_{min} (jet2, #mu);Events / bin", 100, 0, 5);
  hjet2drmintau = book<TH1D>("hjet2drmintau", ";#DeltaR_{min} (jet2, #tau);Events / bin", 100, 0, 5);
  hjet3pt = book<TH1D>("jet3pt", ";p_{T}^{jet 3} [GeV]; Events / bin", 150, 0, 3000);
  hjet3eta = book<TH1D>("jet3eta", ";#eta^{jet 3};Events / bin", 100, -5., 5.);
  hjet3phi = book<TH1D>("jet3phi", ";#phi^{jet 3};Events / bin", 70, -3.5, 3.5);
  hjet3mass = book<TH1D>("jet3mass", ";m^{jet 3} [GeV];Events / bin", 150, 0, 3000);
  hjet3energy = book<TH1D>("jet3energy", ";E^{jet 3} [GeV];Events / bin", 150, 0, 3000);
  hjet3drminele = book<TH1D>("hjet3drminele", ";#DeltaR_{min} (jet3, e);Events / bin", 100, 0, 5);
  hjet3drminmuon = book<TH1D>("hjet3drminmuon", ";#DeltaR_{min} (jet3, #mu);Events / bin", 100, 0, 5);
  hjet3drmintau = book<TH1D>("hjet3drmintau", ";#DeltaR_{min} (jet3, #tau);Events / bin", 100, 0, 5);
  hjet4pt = book<TH1D>("jet4pt", ";p_{T}^{jet 4} [GeV]; Events / bin", 150, 0, 3000);
  hjet4eta = book<TH1D>("jet4eta", ";#eta^{jet 4};Events / bin", 100, -5., 5.);
  hjet4phi = book<TH1D>("jet4phi", ";#phi^{jet 4};Events / bin", 70, -3.5, 3.5);
  hjet4mass = book<TH1D>("jet4mass", ";m^{jet 4} [GeV];Events / bin", 150, 0, 3000);
  hjet4energy = book<TH1D>("jet4energy", ";E^{jet 4} [GeV];Events / bin", 150, 0, 3000);
  hjet4drminele = book<TH1D>("hjet4drminele", ";#DeltaR_{min} (jet4, e);Events / bin", 100, 0, 5);
  hjet4drminmuon = book<TH1D>("hjet4drminmuon", ";#DeltaR_{min} (jet4, #mu);Events / bin", 100, 0, 5);
  hjet4drmintau = book<TH1D>("hjet4drmintau", ";#DeltaR_{min} (jet4, #tau);Events / bin", 100, 0, 5);
  hjet5pt = book<TH1D>("jet5pt", ";p_{T}^{jet 5} [GeV]; Events / bin", 150, 0, 3000);
  hjet5eta = book<TH1D>("jet5eta", ";#eta^{jet 5};Events / bin", 100, -5., 5.);
  hjet5phi = book<TH1D>("jet5phi", ";#phi^{jet 5};Events / bin", 70, -3.5, 3.5);
  hjet5mass = book<TH1D>("jet5mass", ";m^{jet 5} [GeV];Events / bin", 150, 0, 3000);
  hjet5energy = book<TH1D>("jet5energy", ";E^{jet 5} [GeV];Events / bin", 150, 0, 3000);
  hjet5drminele = book<TH1D>("hjet5drminele", ";#DeltaR_{min} (jet5, e);Events / bin", 100, 0, 5);
  hjet5drminmuon = book<TH1D>("hjet5drminmuon", ";#DeltaR_{min} (jet5, #mu);Events / bin", 100, 0, 5);
  hjet5drmintau = book<TH1D>("hjet5drmintau", ";#DeltaR_{min} (jet5, #tau);Events / bin", 100, 0, 5);

}

void JetHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t njets = event.jets->size();
  for(size_t i=0; i<njets; i++){
    Jet j = event.jets->at(i);
    double dRmin_ele  = 999.;
    double dRmin_muon = 999.;
    double dRmin_tau  = 999.;
    for(size_t k=0; k<event.electrons->size(); k++){
      dRmin_ele = min(dRmin_ele, deltaR(j, event.electrons->at(k)));
    }
    for(size_t k=0; k<event.muons->size(); k++){
      dRmin_muon = min(dRmin_muon, deltaR(j, event.muons->at(k)));
    }
    for(size_t k=0; k<event.taus->size(); k++){
      dRmin_tau = min(dRmin_tau, deltaR(j, event.taus->at(k)));
    }

    hjetpt->Fill(j.pt(), weight);
    hjeteta->Fill(j.eta(), weight);
    hjetphi->Fill(j.phi(), weight);
    hjetmass->Fill(j.m(), weight);
    hjetenergy->Fill(j.e(), weight);
    hjetdrminele->Fill(dRmin_ele, weight);
    hjetdrminmuon->Fill(dRmin_muon, weight);
    hjetdrmintau->Fill(dRmin_tau, weight);

    if(i==0){
      hjet1pt->Fill(j.pt(), weight);
      hjet1eta->Fill(j.eta(), weight);
      hjet1phi->Fill(j.phi(), weight);
      hjet1mass->Fill(j.m(), weight);
      hjet1energy->Fill(j.e(), weight);
      hjet1drminele->Fill(dRmin_ele, weight);
      hjet1drminmuon->Fill(dRmin_muon, weight);
      hjet1drmintau->Fill(dRmin_tau, weight);
    }
    else if(i==1){
      hjet2pt->Fill(j.pt(), weight);
      hjet2eta->Fill(j.eta(), weight);
      hjet2phi->Fill(j.phi(), weight);
      hjet2mass->Fill(j.m(), weight);
      hjet2energy->Fill(j.e(), weight);
      hjet2drminele->Fill(dRmin_ele, weight);
      hjet2drminmuon->Fill(dRmin_muon, weight);
      hjet2drmintau->Fill(dRmin_tau, weight);
    }
    else if(i==2){
      hjet3pt->Fill(j.pt(), weight);
      hjet3eta->Fill(j.eta(), weight);
      hjet3phi->Fill(j.phi(), weight);
      hjet3mass->Fill(j.m(), weight);
      hjet3energy->Fill(j.e(), weight);
      hjet3drminele->Fill(dRmin_ele, weight);
      hjet3drminmuon->Fill(dRmin_muon, weight);
      hjet3drmintau->Fill(dRmin_tau, weight);
    }
    else if(i==3){
      hjet4pt->Fill(j.pt(), weight);
      hjet4eta->Fill(j.eta(), weight);
      hjet4phi->Fill(j.phi(), weight);
      hjet4mass->Fill(j.m(), weight);
      hjet4energy->Fill(j.e(), weight);
      hjet4drminele->Fill(dRmin_ele, weight);
      hjet4drminmuon->Fill(dRmin_muon, weight);
      hjet4drmintau->Fill(dRmin_tau, weight);
    }
    else if(i==4){
      hjet5pt->Fill(j.pt(), weight);
      hjet5eta->Fill(j.eta(), weight);
      hjet5phi->Fill(j.phi(), weight);
      hjet5mass->Fill(j.m(), weight);
      hjet5energy->Fill(j.e(), weight);
      hjet5drminele->Fill(dRmin_ele, weight);
      hjet5drminmuon->Fill(dRmin_muon, weight);
      hjet5drmintau->Fill(dRmin_tau, weight);
    }
    else break;
  }
  hnjets->Fill(njets, weight);
}
