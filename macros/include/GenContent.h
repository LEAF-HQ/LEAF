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
class GenContent {

public:
  // Constructors, destructor
  GenContent();
  GenContent(const GenContent &) = default;
  GenContent & operator = (const GenContent &) = default;
  ~GenContent();

  void clear();

  Met* genmet;
  Met* met_from_invis;
  vector<GenParticle>* genparticles_hard;
  vector<GenParticle>* genparticles_final;
  vector<GenParticle>* genparticles_visibletaus;
  vector<GenJet>*      genjets;


};
