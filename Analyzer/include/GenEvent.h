#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "Analyzer/include/Met.h"
#include "Analyzer/include/GenParticle.h"
#include "Analyzer/include/GenJet.h"
#include "Analyzer/include/Event.h"

using namespace std;

// Container class for all quantities
class GenEvent : public Event{

public:
  // Constructors, destructor
  GenEvent(){
    genmet                   = new Met;
    GenParticle p;
    genparticles_visibletaus = new vector<GenParticle>;
    genparticles_all         = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }
  ~GenEvent(){
    delete genmet;
    delete genparticles_visibletaus;
    delete genparticles_all;
    delete genjets;
  };

  void clear(){
    Event::clear();
    delete genmet;
    delete genparticles_visibletaus;
    delete genparticles_all;
    delete genjets;
    genmet = 0;
    genparticles_visibletaus = 0;
    genparticles_all = 0;
    genjets = 0;
  }
  void reset(){
    Event::reset();
    delete genmet;
    delete genparticles_visibletaus;
    delete genparticles_all;
    delete genjets;
    GenParticle p;
    genmet                   = new Met;
    genparticles_visibletaus = new vector<GenParticle>;
    genparticles_all         = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }

  Met* genmet;
  vector<GenParticle>* genparticles_visibletaus;
  vector<GenParticle>* genparticles_all;
  vector<GenJet>* genjets;
};
