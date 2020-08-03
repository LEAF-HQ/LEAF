#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
// #include "classes.h"
#include "include/GenContent.h"

using namespace std;

// Container class for all quantities
class Event {

public:
  // Constructors, destructor
  Event();
  Event(const Event &) = default;
  Event & operator = (const Event &) = default;
  ~Event();

  void clear();
  
  GenContent* gencontent;
  double weight;

};
