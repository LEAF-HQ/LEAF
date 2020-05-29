#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "classes.h"
// #include <memory>

using namespace std;

// Container class for all quantities
class Event {

public:
  // Constructors, destructor
  Event();
  Event(const Event &) = default;
  Event & operator = (const Event &) = default;
  ~Event() = default;

  void clear();

  Met* genmet;
  vector<GenParticle>* genparticles_hard;
  vector<GenParticle>* genparticles_final;
  vector<GenParticle>* genparticles_prompttaudecayprod;
  vector<GenJet>*      genjets;

  double weight;

};
