#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "Analyzer/include/Met.h"
#include "Analyzer/include/GenParticle.h"
#include "Analyzer/include/GenJet.h"

using namespace std;

// Container class for all quantities
class Event {

public:
  // Constructors, destructor
  Event(){
    weight = 1.;
  };

  Event(const Event &) = default;
  Event & operator = (const Event &) = default;
  ~Event(){};

  void clear(){
    weight = 1.;
  };
  void reset(){
    weight = 1.;
  };

  double weight;

};
