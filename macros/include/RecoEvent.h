#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/GenEvent.h"
#include "include/GenInfo.h"
#include "include/Flags.h"
#include "include/Met.h"
#include "include/Jet.h"
#include "include/Tau.h"
#include "include/Muon.h"
#include "include/Electron.h"
#include "include/TriggerObject.h"

using namespace std;

// Container class for all quantities
class RecoEvent : public GenEvent{

public:
  // Constructors, destructor
  RecoEvent();
  ~RecoEvent();

  void clear();
  void reset();
  TString get_runperiod(TString year);

  GenInfo* geninfo;
  Flags* flags;
  Met* met;
  Met* rawmet;
  vector<TriggerObject>* triggerobjects;
  vector<Jet>* jets;
  vector<Tau>* taus;
  vector<Muon>* muons;
  vector<Electron>* electrons;
  bool is_data;
  unsigned int run, lumiblock;
  int npv, npv_good, npu;
  float rho, ntrueint, weight_prefiring, weight_prefiring_up, weight_prefiring_down;
  ULong64_t number;
};
