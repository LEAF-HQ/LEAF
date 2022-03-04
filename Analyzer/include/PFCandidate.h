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
    m_puppiweight_nolep = -1.;
    m_calo_frac = -1.;
    m_hcal_frac = -1.;
    m_dz = -1.;
    m_dxy = -1.;
    m_dz_err = -1.;
    m_dxy_err = -1.;
    m_vertex_x = -1.;
    m_vertex_y = -1.;
    m_vertex_z = -1.;
    m_jetidx = -1;
    m_is_iso_ch_had = false;

  }

  float puppiweight() const {return m_puppiweight;};
  float puppiweight_nolep() const {return m_puppiweight_nolep;};
  float calo_frac() const {return m_calo_frac;};
  float hcal_frac() const {return m_hcal_frac;};
  float dz() const {return m_dz;};
  float dxy() const {return m_dxy;};
  float dz_err() const {return m_dz_err;};
  float dxy_err() const {return m_dxy_err;};
  float vertex_x() const {return m_vertex_x;};
  float vertex_y() const {return m_vertex_y;};
  float vertex_z() const {return m_vertex_z;};
  bool is_iso_ch_had() const {return m_is_iso_ch_had;};
  int jetidx() const {return m_jetidx;};

  void set_puppiweight(float x) {m_puppiweight = x;};
  void set_puppiweight_nolep(float x) {m_puppiweight_nolep = x;};
  void set_calo_frac(float x) {m_calo_frac = x;};
  void set_hcal_frac(float x) {m_hcal_frac = x;};
  void set_dz(float x) {m_dz = x;};
  void set_dxy(float x) {m_dxy = x;};
  void set_dz_err(float x) {m_dz_err = x;};
  void set_dxy_err(float x) {m_dxy_err = x;};
  void set_vertex_x(float x) {m_vertex_x = x;};
  void set_vertex_y(float x) {m_vertex_y = x;};
  void set_vertex_z(float x) {m_vertex_z = x;};
  void set_is_iso_ch_had(bool x) {m_is_iso_ch_had = x;};
  void set_jetidx(int x){m_jetidx = x;};

protected:
  float m_puppiweight, m_puppiweight_nolep;
  float m_calo_frac, m_hcal_frac;
  float m_dz, m_dxy, m_dz_err, m_dxy_err;
  float m_vertex_x, m_vertex_y, m_vertex_z;
  bool m_is_iso_ch_had;
  int m_jetidx;

};
