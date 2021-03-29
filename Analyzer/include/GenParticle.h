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
    m_mother_pdgid = -1.;
  }

  int ndaughters() const {return m_ndaughters;};
  int mother_pdgid() const {return m_mother_pdgid;};

  void set_ndaughters(int x) {m_ndaughters = x;};
  void set_mother_pdgid(int x) {m_mother_pdgid = x;};


protected:
  int m_ndaughters;
  int m_mother_pdgid;


};
