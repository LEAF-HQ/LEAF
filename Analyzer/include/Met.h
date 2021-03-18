#pragma once

#include <TLorentzVector.h>



// Container class for MET
class Met {

public:
  // Constructors, destructor
  Met() = default;
  Met(const Met &) = default;
  Met & operator = (const Met &) = default;
  ~Met() = default;

  double pt()  const {return m_pt;};
  double phi() const {return m_phi;};
  TLorentzVector p4(){
   TLorentzVector met;
   met.SetPtEtaPhiM(m_pt, 0, m_phi, 0);
   return met;
}

  void set_pt(double x) {m_pt = x;};
  void set_phi(double x){m_phi = x;};


protected:
  double m_pt  = -1.;
  double m_phi = -1.;

};
