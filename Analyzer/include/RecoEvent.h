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
