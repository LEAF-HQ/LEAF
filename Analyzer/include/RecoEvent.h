#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/GenEvent.h"
#include "LEAF/Analyzer/include/GenInfo.h"
#include "LEAF/Analyzer/include/Flags.h"
#include "LEAF/Analyzer/include/Met.h"
#include "LEAF/Analyzer/include/Jet.h"
#include "LEAF/Analyzer/include/Tau.h"
#include "LEAF/Analyzer/include/Muon.h"
#include "LEAF/Analyzer/include/Electron.h"
#include "LEAF/Analyzer/include/TriggerObject.h"
#include "LEAF/Analyzer/include/PFCandidate.h"
#include "LEAF/Analyzer/include/constants.h"

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
    jets_ak4chs = new vector<Jet>;
    jets_ak4puppi = new vector<Jet>;
    jets_ak8puppi = new vector<Jet>;
    taus = new vector<Tau>;
    muons = new vector<Muon>;
    electrons = new vector<Electron>;
    pfcands = new vector<PFCandidate>;
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
    delete jets_ak4chs;
    delete jets_ak4puppi;
    delete jets_ak8puppi;
    delete taus;
    delete muons;
    delete electrons;
    delete pfcands;
  }

  void clear(){
    GenEvent::clear();
    delete geninfo;
    delete flags;
    delete met;
    delete rawmet;
    delete triggerobjects;
    delete jets_ak4chs;
    delete jets_ak4puppi;
    delete jets_ak8puppi;
    delete taus;
    delete muons;
    delete electrons;
    delete pfcands;
    geninfo = 0;
    flags = 0;
    met = 0;
    rawmet = 0;
    triggerobjects = 0;
    jets_ak4chs = 0;
    jets_ak4puppi = 0;
    jets_ak8puppi = 0;
    taus = 0;
    muons = 0;
    electrons = 0;
    pfcands = 0;
  }

  void reset(){
    GenEvent::reset();
    delete geninfo;
    delete flags;
    delete met;
    delete rawmet;
    delete triggerobjects;
    delete jets_ak4chs;
    delete jets_ak4puppi;
    delete jets_ak8puppi;
    delete taus;
    delete muons;
    delete electrons;
    delete pfcands;
    geninfo = new GenInfo;
    flags = new Flags;
    met = new Met;
    rawmet = new Met;
    triggerobjects = new vector<TriggerObject>;
    jets_ak4chs = new vector<Jet>;
    jets_ak4puppi = new vector<Jet>;
    jets_ak8puppi = new vector<Jet>;
    taus = new vector<Tau>;
    muons = new vector<Muon>;
    electrons = new vector<Electron>;
    pfcands = new vector<PFCandidate>;
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
    for (const auto [period, numbermap] : Year2Run2Runnumber.at((string)year)){
      if(RecoEvent::run >= numbermap.at("min") && RecoEvent::run <= numbermap.at("max")) return period;
    }
    throw runtime_error("Event has invalid run number (not in run_number_map in constants.h) and therefore cannot be assigned a run-period");
  }

  GenInfo* geninfo; //
  Flags* flags; //
  Met* met; //
  Met* rawmet; //
  vector<TriggerObject>* triggerobjects; //
  vector<Jet>* jets_ak4chs;//
  vector<Jet>* jets_ak4puppi;//
  vector<Jet>* jets_ak8puppi;//
  vector<Tau>* taus; //
  vector<Muon>* muons; //
  vector<Electron>* electrons; //
  vector<PFCandidate>* pfcands; //
  bool is_data;//
  unsigned int run, lumiblock;//
  int npv, npv_good; //
  int npu; //
  float rho; //
  float ntrueint, weight_prefiring, weight_prefiring_up, weight_prefiring_down; //
  ULong64_t number;//
};
