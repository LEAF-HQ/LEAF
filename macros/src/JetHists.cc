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
  hjet1pt = book<TH1D>("jet1pt", ";p_{T}^{jet 1} [GeV]; Events / bin", 150, 0, 3000);
  hjet1eta = book<TH1D>("jet1eta", ";#eta^{jet 1};Events / bin", 100, -5., 5.);
  hjet1phi = book<TH1D>("jet1phi", ";#phi^{jet 1};Events / bin", 70, -3.5, 3.5);
  hjet1mass = book<TH1D>("jet1mass", ";m^{jet 1} [GeV];Events / bin", 150, 0, 3000);
  hjet1energy = book<TH1D>("jet1energy", ";E^{jet 1} [GeV];Events / bin", 150, 0, 3000);
  hjet2pt = book<TH1D>("jet2pt", ";p_{T}^{jet 2} [GeV]; Events / bin", 150, 0, 3000);
  hjet2eta = book<TH1D>("jet2eta", ";#eta^{jet 2};Events / bin", 100, -5., 5.);
  hjet2phi = book<TH1D>("jet2phi", ";#phi^{jet 2};Events / bin", 70, -3.5, 3.5);
  hjet2mass = book<TH1D>("jet2mass", ";m^{jet 2} [GeV];Events / bin", 150, 0, 3000);
  hjet2energy = book<TH1D>("jet2energy", ";E^{jet 2} [GeV];Events / bin", 150, 0, 3000);
  hjet3pt = book<TH1D>("jet3pt", ";p_{T}^{jet 3} [GeV]; Events / bin", 150, 0, 3000);
  hjet3eta = book<TH1D>("jet3eta", ";#eta^{jet 3};Events / bin", 100, -5., 5.);
  hjet3phi = book<TH1D>("jet3phi", ";#phi^{jet 3};Events / bin", 70, -3.5, 3.5);
  hjet3mass = book<TH1D>("jet3mass", ";m^{jet 3} [GeV];Events / bin", 150, 0, 3000);
  hjet3energy = book<TH1D>("jet3energy", ";E^{jet 3} [GeV];Events / bin", 150, 0, 3000);
  hjet4pt = book<TH1D>("jet4pt", ";p_{T}^{jet 4} [GeV]; Events / bin", 150, 0, 3000);
  hjet4eta = book<TH1D>("jet4eta", ";#eta^{jet 4};Events / bin", 100, -5., 5.);
  hjet4phi = book<TH1D>("jet4phi", ";#phi^{jet 4};Events / bin", 70, -3.5, 3.5);
  hjet4mass = book<TH1D>("jet4mass", ";m^{jet 4} [GeV];Events / bin", 150, 0, 3000);
  hjet4energy = book<TH1D>("jet4energy", ";E^{jet 4} [GeV];Events / bin", 150, 0, 3000);
  hjet5pt = book<TH1D>("jet5pt", ";p_{T}^{jet 5} [GeV]; Events / bin", 150, 0, 3000);
  hjet5eta = book<TH1D>("jet5eta", ";#eta^{jet 5};Events / bin", 100, -5., 5.);
  hjet5phi = book<TH1D>("jet5phi", ";#phi^{jet 5};Events / bin", 70, -3.5, 3.5);
  hjet5mass = book<TH1D>("jet5mass", ";m^{jet 5} [GeV];Events / bin", 150, 0, 3000);
  hjet5energy = book<TH1D>("jet5energy", ";E^{jet 5} [GeV];Events / bin", 150, 0, 3000);

}

void JetHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t njets = event.jets->size();
  for(size_t i=0; i<njets; i++){
    Jet j = event.jets->at(i);

    if(i==0){
      hjet1pt->Fill(j.pt(), weight);
      hjet1eta->Fill(j.eta(), weight);
      hjet1phi->Fill(j.phi(), weight);
      hjet1mass->Fill(j.m(), weight);
      hjet1energy->Fill(j.e(), weight);
    }
    else if(i==1){
      hjet2pt->Fill(j.pt(), weight);
      hjet2eta->Fill(j.eta(), weight);
      hjet2phi->Fill(j.phi(), weight);
      hjet2mass->Fill(j.m(), weight);
      hjet2energy->Fill(j.e(), weight);
    }
    else if(i==2){
      hjet3pt->Fill(j.pt(), weight);
      hjet3eta->Fill(j.eta(), weight);
      hjet3phi->Fill(j.phi(), weight);
      hjet3mass->Fill(j.m(), weight);
      hjet3energy->Fill(j.e(), weight);
    }
    else if(i==3){
      hjet4pt->Fill(j.pt(), weight);
      hjet4eta->Fill(j.eta(), weight);
      hjet4phi->Fill(j.phi(), weight);
      hjet4mass->Fill(j.m(), weight);
      hjet4energy->Fill(j.e(), weight);
    }
    else if(i==4){
      hjet5pt->Fill(j.pt(), weight);
      hjet5eta->Fill(j.eta(), weight);
      hjet5phi->Fill(j.phi(), weight);
      hjet5mass->Fill(j.m(), weight);
      hjet5energy->Fill(j.e(), weight);
    }
    else break;
  }
  hnjets->Fill(njets, weight);
}
