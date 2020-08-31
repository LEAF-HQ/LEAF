#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/Event.h"
#include "include/Jet.h"

using namespace std;

// Container class for all quantities
class RecoEvent : public Event{

public:
  // Constructors, destructor
  RecoEvent();
  ~RecoEvent();

  void clear();
  void reset();

  Met* met;
  vector<Jet>* jets;
};
