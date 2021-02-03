#include "include/RecoEvent.h"
// #include "include/cosmetics.h"
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
  geninfo = new GenInfo;
  flags = new Flags;
  met = new Met;
  rawmet = new Met;
  triggerobjects = new vector<TriggerObject>;
  jets = new vector<Jet>;
  taus = new vector<Tau>;
  muons = new vector<Muon>;
  electrons = new vector<Electron>;
  is_data = false;
  run = -1;
  lumiblock = -1;
  npv = -1;
  npv_good = -1;
  npu = -1;
  ntrueint = -1.;
  number = -1;
  weight_prefiring = -1.;
  weight_prefiring_up = -1.;
  weight_prefiring_down = -1.;
}

RecoEvent::~RecoEvent(){
  delete geninfo;
  delete flags;
  delete met;
  delete rawmet;
  delete triggerobjects;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
}

TString RecoEvent::get_runperiod(TString year){
  if(!RecoEvent::is_data) return "MC";
  for (const auto& [numbers, period] : run_number_map.at(year)){
    if(RecoEvent::run >= numbers.first && RecoEvent::run <= numbers.second) return period;
  }
  throw runtime_error("Event has invalid run number (not in run_number_map in constants.h) and therefore cannot be assigned a run-period");
}

void RecoEvent::clear(){
  GenEvent::clear();
  delete geninfo;
  delete flags;
  delete met;
  delete rawmet;
  delete triggerobjects;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
  geninfo = 0;
  flags = 0;
  met = 0;
  rawmet = 0;
  triggerobjects = 0;
  jets = 0;
  taus = 0;
  muons = 0;
  electrons = 0;
}

void RecoEvent::reset(){
  GenEvent::reset();
  delete geninfo;
  delete flags;
  delete met;
  delete rawmet;
  delete triggerobjects;
  delete jets;
  delete taus;
  delete muons;
  delete electrons;
  geninfo = new GenInfo;
  flags = new Flags;
  met = new Met;
  rawmet = new Met;
  triggerobjects = new vector<TriggerObject>;
  jets = new vector<Jet>;
  taus = new vector<Tau>;
  muons = new vector<Muon>;
  electrons = new vector<Electron>;
  is_data = false;
  run = -1;
  lumiblock = -1;
  npv = -1;
  npv_good = -1;
  npu = -1;
  ntrueint = -1.;
  number = -1;
  weight_prefiring = -1.;
  weight_prefiring_up = -1.;
  weight_prefiring_down = -1.;

}
