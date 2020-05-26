#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Particle.h"

using namespace std;

// Basically a particle with a PDG ID
class GenParticle : public Particle {

public:
  // Constructors, destructor
  GenParticle() = default;
  GenParticle(const GenParticle &) = default;
  GenParticle & operator = (const GenParticle &) = default;
  ~GenParticle() = default;

  int pdgid() const {return m_pdgid;};

  void set_pdgid(int x) {m_pdgid = x;};


protected:
  int m_pdgid = -1;

};
