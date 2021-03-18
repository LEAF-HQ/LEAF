#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Analyzer/include/FlavorParticle.h"

using namespace std;

// Basically a FlavorParticle with a number of daughters
class GenParticle : public FlavorParticle {

public:
  // Constructors, destructor
  GenParticle(){
    m_ndaughters = -1.;
  }

  int ndaughters() const {return m_ndaughters;};

  void set_ndaughters(int x) {m_ndaughters = x;};


protected:
  int m_ndaughters;


};
