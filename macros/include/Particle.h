#pragma once

#include <TLorentzVector.h>


// using namespace std;

// Container class for all quantities
class Particle {

public:
  // Constructors, destructor
  Particle() = default;
  Particle(const Particle &) = default;
  Particle & operator = (const Particle &) = default;
  ~Particle() = default;

  double pt()  const {return m_pt;};
  double eta() const {return m_eta;};
  double phi() const {return m_phi;};
  double m()   const {return m_m;};
  TLorentzVector p4() const{
    TLorentzVector p;
    p.SetPtEtaPhiM(m_pt, m_eta, m_phi, m_m);
    return p;
  }

  void set_pt(double x) {m_pt = x;};
  void set_eta(double x){m_eta = x;};
  void set_phi(double x){m_phi = x;};
  void set_m(double x)  {m_m = x;};
  void set_p4(TLorentzVector p){
    m_pt  = p.Pt();
    m_eta = p.Eta();
    m_phi = p.Phi();
    m_m   = p.M();
  };
  void set_p4(double pt, double eta, double phi, double m){
    m_pt  = pt;
    m_eta = eta;
    m_phi = phi;
    m_m   = m;
  };


protected:
  double m_pt = -1.;
  double m_eta = -1.;
  double m_phi = -1.;
  double m_m = -1.;

};
