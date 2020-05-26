#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Particle.h"

using namespace std;

// Container class for all quantities
class GenJet : public Particle {

public:
  // Constructors, destructor
  GenJet() = default;
  GenJet(const GenJet &) = default;
  GenJet & operator = (const GenJet &) = default;
  ~GenJet() = default;

};
