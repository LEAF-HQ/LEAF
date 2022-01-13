#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/Particle.h"

using namespace std;

// Container class for all quantities
class GenJet : public Particle {

public:
  // Constructors, destructor
  GenJet() = default;
  GenJet(const GenJet &) = default;
  GenJet & operator = (const GenJet &) = default;
  ~GenJet() = default;

  int n_constituents() const {return m_n_constituents;};

  void set_n_constituents(int x){m_n_constituents = x;};

protected:
  int m_n_constituents = -1;

};
