#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/FlavorParticle.h"

// Basically a FlavorParticle with 2 PUPPI weights
class PFCandidate : public FlavorParticle {

public:
  // Constructors, destructor
  PFCandidate(){
    m_puppiweight = -1.;
    m_puppiweight_nolep = -1;
    m_caloFraction = -1;
    m_hcalFraction = -1;
    m_dz = -1;
    m_dxy = -1;
    m_dzError = -1;
    m_dxyError = -1;
    m_vertex_x = -1;
    m_vertex_y = -1;
    m_vertex_z = -1;
    m_isIsolatedChargedHadron = false;

  }

  float puppiweight() const {return m_puppiweight;};
  float puppiweight_nolep() const {return m_puppiweight_nolep;};
  float caloFraction() const {return m_caloFraction;};
  float hcalFraction() const {return m_hcalFraction;};
  float dz() const {return m_dz;};
  float dxy() const {return m_dxy;};
  float dzError() const {return m_dzError;};
  float dxyError() const {return m_dxyError;};
  float vertex_x() const {return m_vertex_x;};
  float vertex_y() const {return m_vertex_y;};
  float vertex_z() const {return m_vertex_z;};
  bool isIsolatedChargedHadron() const {return m_isIsolatedChargedHadron;};

  void set_puppiweight(float x) {m_puppiweight = x;};
  void set_puppiweight_nolep(float x) {m_puppiweight_nolep = x;};
  void set_caloFraction(float x) {m_caloFraction = x;};
  void set_hcalFraction(float x) {m_hcalFraction = x;};
  void set_dz(float x) {m_dz = x;};
  void set_dxy(float x) {m_dxy = x;};
  void set_dzError(float x) {m_dzError = x;};
  void set_dxyError(float x) {m_dxyError = x;};
  void set_vertex_x(float x) {m_vertex_x = x;};
  void set_vertex_y(float x) {m_vertex_y = x;};
  void set_vertex_z(float x) {m_vertex_z = x;};
  void set_isIsolatedChargedHadron(bool x) {m_isIsolatedChargedHadron = x;};


protected:
  float m_puppiweight, m_puppiweight_nolep;
  float m_caloFraction, m_hcalFraction;
  float m_dz, m_dxy, m_dzError, m_dxyError;
  float m_vertex_x, m_vertex_y, m_vertex_z;
  bool m_isIsolatedChargedHadron;

};
