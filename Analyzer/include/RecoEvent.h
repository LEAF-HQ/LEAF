#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "Analyzer/include/GenEvent.h"
#include "Analyzer/include/GenInfo.h"
#include "Analyzer/include/Flags.h"
#include "Analyzer/include/Met.h"
#include "Analyzer/include/Jet.h"
#include "Analyzer/include/Tau.h"
#include "Analyzer/include/Muon.h"
#include "Analyzer/include/Electron.h"
#include "Analyzer/include/TriggerObject.h"
#include "Analyzer/include/constants.h"

using namespace std;

// Container class for all quantities
class RecoEvent : public GenEvent{

public:
  // Constructors, destructor
  RecoEvent(){
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

  ~RecoEvent(){
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

  void clear(){
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

  void reset(){
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

  TString get_runperiod(TString year){
    if(!RecoEvent::is_data) return "MC";
    for (const auto [numbers, period] : run_number_map.at(year)){
      if(RecoEvent::run >= numbers.first && RecoEvent::run <= numbers.second) return period;
    }
    throw runtime_error("Event has invalid run number (not in run_number_map in constants.h) and therefore cannot be assigned a run-period");
  }

  GenInfo* geninfo; //
  Flags* flags; //
  Met* met; //
  Met* rawmet; //
  vector<TriggerObject>* triggerobjects; //
  vector<Jet>* jets;//
  vector<Tau>* taus; //
  vector<Muon>* muons; //
  vector<Electron>* electrons; //
  bool is_data;//
  unsigned int run, lumiblock;//
  int npv, npv_good; //
  int npu; //
  float rho; //
  float ntrueint, weight_prefiring, weight_prefiring_up, weight_prefiring_down; //
  ULong64_t number;//
};
