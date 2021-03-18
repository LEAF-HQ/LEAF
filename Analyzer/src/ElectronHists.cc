#include "Analyzer/include/ElectronHists.h"
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

ElectronHists::ElectronHists(TString dir_) : BaseHists(dir_){

  hnelectrons = book<TH1D>("nelectrons", ";N_{e}; Events / bin", 11, -0.5, 10.5);
  helectronpt = book<TH1D>("electronpt", ";p_{T}^{e} [GeV]; Events / bin", 50, 0, 1500);
  helectroneta = book<TH1D>("electroneta", ";#eta^{e};Events / bin", 100, -5., 5.);
  helectronphi = book<TH1D>("electronphi", ";#phi^{e};Events / bin", 70, -3.5, 3.5);
  helectronmass = book<TH1D>("electronmass", ";m^{e} [GeV];Events / bin", 50, 0, 1500);
  helectronenergy = book<TH1D>("electronenergy", ";E^{e} [GeV];Events / bin", 50, 0, 1500);
  helectron1pt = book<TH1D>("electron1pt", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 1500);
  helectron1eta = book<TH1D>("electron1eta", ";#eta^{e 1};Events / bin", 100, -5., 5.);
  helectron1phi = book<TH1D>("electron1phi", ";#phi^{e 1};Events / bin", 70, -3.5, 3.5);
  helectron1mass = book<TH1D>("electron1mass", ";m^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron1energy = book<TH1D>("electron1energy", ";E^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron2pt = book<TH1D>("electron2pt", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 1500);
  helectron2eta = book<TH1D>("electron2eta", ";#eta^{e 2};Events / bin", 100, -5., 5.);
  helectron2phi = book<TH1D>("electron2phi", ";#phi^{e 2};Events / bin", 70, -3.5, 3.5);
  helectron2mass = book<TH1D>("electron2mass", ";m^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron2energy = book<TH1D>("electron2energy", ";E^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron3pt = book<TH1D>("electron3pt", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 1500);
  helectron3eta = book<TH1D>("electron3eta", ";#eta^{e 3};Events / bin", 100, -5., 5.);
  helectron3phi = book<TH1D>("electron3phi", ";#phi^{e 3};Events / bin", 70, -3.5, 3.5);
  helectron3mass = book<TH1D>("electron3mass", ";m^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron3energy = book<TH1D>("electron3energy", ";E^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron4pt = book<TH1D>("electron4pt", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 1500);
  helectron4eta = book<TH1D>("electron4eta", ";#eta^{e 4};Events / bin", 100, -5., 5.);
  helectron4phi = book<TH1D>("electron4phi", ";#phi^{e 4};Events / bin", 70, -3.5, 3.5);
  helectron4mass = book<TH1D>("electron4mass", ";m^{e 4} [GeV];Events / bin", 50, 0, 1500);
  helectron4energy = book<TH1D>("electron4energy", ";E^{e 4} [GeV];Events / bin", 50, 0, 1500);

}

void ElectronHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t nelectrons = event.electrons->size();
  for(size_t i=0; i<nelectrons; i++){
    Electron e = event.electrons->at(i);

    helectronpt->Fill(e.pt(), weight);
    helectroneta->Fill(e.eta(), weight);
    helectronphi->Fill(e.phi(), weight);
    helectronmass->Fill(e.m(), weight);
    helectronenergy->Fill(e.e(), weight);

    if(i==0){
      helectron1pt->Fill(e.pt(), weight);
      helectron1eta->Fill(e.eta(), weight);
      helectron1phi->Fill(e.phi(), weight);
      helectron1mass->Fill(e.m(), weight);
      helectron1energy->Fill(e.e(), weight);
    }
    else if(i==1){
      helectron2pt->Fill(e.pt(), weight);
      helectron2eta->Fill(e.eta(), weight);
      helectron2phi->Fill(e.phi(), weight);
      helectron2mass->Fill(e.m(), weight);
      helectron2energy->Fill(e.e(), weight);
    }
    else if(i==2){
      helectron3pt->Fill(e.pt(), weight);
      helectron3eta->Fill(e.eta(), weight);
      helectron3phi->Fill(e.phi(), weight);
      helectron3mass->Fill(e.m(), weight);
      helectron3energy->Fill(e.e(), weight);
    }
    else if(i==3){
      helectron4pt->Fill(e.pt(), weight);
      helectron4eta->Fill(e.eta(), weight);
      helectron4phi->Fill(e.phi(), weight);
      helectron4mass->Fill(e.m(), weight);
      helectron4energy->Fill(e.e(), weight);
    }
  }
  hnelectrons->Fill(nelectrons, weight);
}
