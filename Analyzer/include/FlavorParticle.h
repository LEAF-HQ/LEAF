#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Analyzer/include/Particle.h"

using namespace std;

// Basically a Particle with a pdgId and a charge
class FlavorParticle : public Particle {

public:
  // Constructors, destructor
  FlavorParticle(){
    m_pdgid = 0;
    m_charge = -99.;
  }

  int pdgid() const {return m_pdgid;};
  float charge() const {return m_charge;};

  void set_pdgid(int x) {m_pdgid = x;};
  void set_charge(float x) {m_charge = x;};


protected:
  int m_pdgid;
  float m_charge;


};
