#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/Met.h"
#include "LEAF/Analyzer/include/GenParticle.h"
#include "LEAF/Analyzer/include/GenJet.h"

// Container class for all quantities
class Event {

public:
  // Constructors, destructor
  Event(){
    weight = 1.;
    year = "";
  };

  Event(const Event &) = default;
  Event & operator = (const Event &) = default;
  ~Event(){};

  void clear(){
    weight = 1.;
    year = "";
  };
  void reset(){
    weight = 1.;
    year = "";
  };

  double weight;
  TString year;

};
