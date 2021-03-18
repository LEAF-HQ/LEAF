#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Analyzer/include/Particle.h"

using namespace std;

// Basically a Particle with a pdgId
class FlavorParticle : public Particle {

public:
  // Constructors, destructor
  FlavorParticle(){
    m_pdgid = 0.;
  }

  int pdgid() const {return m_pdgid;};

  void set_pdgid(int x) {m_pdgid = x;};


protected:
  int m_pdgid;


};
