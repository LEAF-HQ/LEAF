#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Analyzer/include/FlavorParticle.h"

// Basically a FlavorParticle with 2 PUPPI weights
class PFCandidate : public FlavorParticle {

public:
  // Constructors, destructor
  PFCandidate(){
    m_puppiweight = -1.;
    m_puppiweight_nolep = -1.;
  }

  float puppiweight() const {return m_puppiweight;};
  float puppiweight_nolep() const {return m_puppiweight_nolep;};

  void set_puppiweight(float x) {m_puppiweight = x;};
  void set_puppiweight_nolep(float x) {m_puppiweight_nolep = x;};


protected:
  float m_puppiweight, m_puppiweight_nolep;


};
