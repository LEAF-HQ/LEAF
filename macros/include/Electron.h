#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "FlavorParticle.h"

using namespace std;

// Basically a Particle with a pdgId
class Electron : public FlavorParticle {

public:

  enum Selector{
    IDCutBasedVeto,
    IDCutBasedLoose,
    IDCutBasedMedium,
    IDCutBasedTight,
    IDCutBasedHEEP,
    IDMVAIsoLoose,
    IDMVAIsoEff90,
    IDMVAIsoEff80,
    IDMVANonIsoLoose,
    IDMVANonIsoEff90,
    IDMVANonIsoEff80
  };

  Electron(){
    m_charge = 0;
    m_selector_bits = 0;
    m_id_bitmap = 0;
    m_lost_hits = 0;
    m_conv_veto = 0;
    m_is_pf = 0;
    m_delta_eta_sc = 0;
    m_dxy = 0;
    m_dz = 0;
    m_einv_minus_pinv = 0;
    m_h_over_e = 0;
    m_ip_3d = 0;
    m_iso_rel_03 = 0;
    m_iso_rel_03_charged = 0;
    m_sigma_ietaieta = 0;
  }

  bool get_selector(Selector i) const {
    return (m_selector_bits & (uint64_t(1) << static_cast<uint64_t>(i)));
  }

  void set_selector(Selector i, bool value) {
    if(value) m_selector_bits |=   uint64_t(1) << static_cast<uint64_t>(i);
    else      m_selector_bits &= ~(uint64_t(1) << static_cast<uint64_t>(i));
  }

  uint64_t selector_bits(){return m_selector_bits;};
  int charge(){return m_charge;};
  int id_bitmap(){return m_id_bitmap;};
  int lost_hits(){return m_lost_hits;};
  bool conv_veto(){return m_conv_veto;};
  bool is_pf(){return m_is_pf;};
  float delta_eta_sc(){return m_delta_eta_sc;};
  float dxy(){return m_dxy;};
  float dz(){return m_dz;};
  float einv_minus_pinv(){return m_einv_minus_pinv;};
  float h_over_e(){return m_h_over_e;};
  float ip_3d(){return m_ip_3d;};
  float iso_rel_03(){return m_iso_rel_03;};
  float iso_rel_03_charged(){return m_iso_rel_03_charged;};
  float sigma_ietaieta(){return m_sigma_ietaieta;};

  void set_selector_bits(uint64_t x){m_selector_bits = x;};
  void set_charge(int x){m_charge = x;};
  void set_id_bitmap(int x){m_id_bitmap = x;};
  void set_lost_hits(int x){m_lost_hits = x;};
  void set_conv_veto(bool x){m_conv_veto = x;};
  void set_is_pf(bool x){m_is_pf = x;};
  void set_delta_eta_sc(float x){m_delta_eta_sc = x;};
  void set_dxy(float x){m_dxy = x;};
  void set_dz(float x){m_dz = x;};
  void set_einv_minus_pinv(float x){m_einv_minus_pinv = x;};
  void set_h_over_e(float x){m_h_over_e = x;};
  void set_ip_3d(float x){m_ip_3d = x;};
  void set_iso_rel_03(float x){m_iso_rel_03 = x;};
  void set_iso_rel_03_charged(float x){m_iso_rel_03_charged = x;};
  void set_sigma_ietaieta(float x){m_sigma_ietaieta = x;};

protected:
  uint64_t m_selector_bits;
  int m_charge;
  int m_id_bitmap;
  int m_lost_hits;
  bool m_conv_veto;
  bool m_is_pf;
  float m_delta_eta_sc;
  float m_dxy;
  float m_dz;
  float m_einv_minus_pinv;
  float m_h_over_e;
  float m_ip_3d;
  float m_iso_rel_03;
  float m_iso_rel_03_charged;
  float m_sigma_ietaieta;
};
