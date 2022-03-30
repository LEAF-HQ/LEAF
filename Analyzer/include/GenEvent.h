#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/Met.h"
#include "LEAF/Analyzer/include/GenParticle.h"
#include "LEAF/Analyzer/include/GenJet.h"
#include "LEAF/Analyzer/include/Event.h"

using namespace std;

// Container class for all quantities
class GenEvent : public Event{

public:
  // Constructors, destructor
  GenEvent(){
    genmet                   = new Met;
    genparticles_pruned      = new vector<GenParticle>;
    genparticles_stable      = new vector<GenParticle>;
    genparticles_visibletaus = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }
  ~GenEvent(){
    delete genmet;
    delete genparticles_pruned;
    delete genparticles_stable;
    delete genparticles_visibletaus;
    delete genjets;
  };

  void clear(){
    Event::clear();
    delete genmet;
    delete genparticles_pruned;
    delete genparticles_stable;
    delete genparticles_visibletaus;
    delete genjets;
    genmet = 0;
    genparticles_pruned = 0;
    genparticles_stable = 0;
    genparticles_visibletaus = 0;
    genjets = 0;
  }
  void reset(){
    Event::reset();
    delete genmet;
    delete genparticles_pruned;
    delete genparticles_stable;
    delete genparticles_visibletaus;
    delete genjets;
    genmet                   = new Met;
    genparticles_pruned      = new vector<GenParticle>;
    genparticles_stable      = new vector<GenParticle>;
    genparticles_visibletaus = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }

  Met* genmet;
  vector<GenParticle>* genparticles_pruned;
  vector<GenParticle>* genparticles_stable;
  vector<GenParticle>* genparticles_visibletaus;
  vector<GenJet>* genjets;
};
