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
    GenParticle p;
    genparticles_fromHP      = new vector<GenParticle>;
    genparticles_all         = new vector<GenParticle>;
    genparticles_visibletaus = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }
  ~GenEvent(){
    delete genmet;
    delete genparticles_fromHP;
    delete genparticles_all;
    delete genparticles_visibletaus;
    delete genjets;
  };

  void clear(){
    Event::clear();
    delete genmet;
    delete genparticles_fromHP;
    delete genparticles_all;
    delete genparticles_visibletaus;
    delete genjets;
    genmet = 0;
    genparticles_fromHP = 0;
    genparticles_all = 0;
    genparticles_visibletaus = 0;
    genjets = 0;
  }
  void reset(){
    Event::reset();
    delete genmet;
    delete genparticles_fromHP;
    delete genparticles_all;
    delete genparticles_visibletaus;
    delete genjets;
    GenParticle p;
    genmet                   = new Met;
    genparticles_fromHP      = new vector<GenParticle>;
    genparticles_all         = new vector<GenParticle>;
    genparticles_visibletaus = new vector<GenParticle>;
    genjets                  = new vector<GenJet>;
  }

  Met* genmet;
  vector<GenParticle>* genparticles_fromHP;
  vector<GenParticle>* genparticles_all;
  vector<GenParticle>* genparticles_visibletaus;
  vector<GenJet>* genjets;
};
