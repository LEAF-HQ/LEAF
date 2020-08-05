#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "include/Met.h"
#include "include/GenParticle.h"
#include "include/GenJet.h"

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

  Met* genmet;
  Met* genmet_invis;
  vector<GenParticle>* genparticles_hard;
  vector<GenParticle>* genparticles_final;
  vector<GenParticle>* genparticles_visibletaus;
  vector<GenJet>* genjets;
  double weight;

};
