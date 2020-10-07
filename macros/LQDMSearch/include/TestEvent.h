#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/RecoEvent.h"

using namespace std;

// Container class for all quantities
class TestEvent : public RecoEvent{

public:
  // Constructors, destructor
  TestEvent();
  ~TestEvent();

  void clear();
  void reset();

  vector<Electron>* test;
};
