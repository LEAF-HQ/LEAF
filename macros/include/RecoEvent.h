#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/GenEvent.h"
#include "include/Met.h"
#include "include/Jet.h"
#include "include/Tau.h"
#include "include/Muon.h"
#include "include/Electron.h"

using namespace std;

// Container class for all quantities
class RecoEvent : public GenEvent{

public:
  // Constructors, destructor
  RecoEvent();
  ~RecoEvent();

  void clear();
  void reset();

  Met* met;
  vector<Jet>* jets;
  vector<Tau>* taus;
  vector<Muon>* muons;
  vector<Electron>* electrons;
};
