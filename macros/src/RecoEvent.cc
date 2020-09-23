#include "include/RecoEvent.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include <TH1D.h>
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

RecoEvent::RecoEvent(){
  met = new Met;
  jets = new vector<Jet>;
  taus = new vector<Tau>;
  muons = new vector<Muon>;
  electrons = new vector<Electron>;
}

RecoEvent::~RecoEvent(){
  delete met;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
}

void RecoEvent::clear(){
  Event::clear();
  delete met;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
  met = 0;
  jets = 0;
  taus = 0;
  muons = 0;
  electrons = 0;
}

void RecoEvent::reset(){
  Event::reset();
  delete met;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
  met = new Met;
  jets = new vector<Jet>;
  taus = new vector<Tau>;
  muons = new vector<Muon>;
  electrons = new vector<Electron>;
}
