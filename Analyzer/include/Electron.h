#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/FlavorParticle.h"

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
    m_jetidx = -1;
    m_selector_bits = 0;
    // m_id_bitmap = -1;
    m_lost_hits = -1;
    m_conv_veto = 0;
    m_is_pf = 0;
    // m_delta_eta_sc = 0;

    m_sumchpt = -1.;
    m_sumnhet = -1.;
    m_sumphpt = -1.;
    m_sumpupt = -1.;

    m_dphi_in = -999;
    m_deta_in_seed = -999;
    m_pt_err = -1;
    m_phi_err = -1;
    m_eta_err = -1;
    m_eta_sc = -1;
    m_phi_sc = -1;
    m_e_sc = -1;
    m_dxy = -1;
    m_dz = -1;
    m_d0 = -1;
    m_dxy_err = -1;
    m_dz_err = -1;
    m_d0_err = -1;
    m_ea = -1;
    m_einv_minus_pinv = -1;
    m_h_over_e = -1;
    m_iso_rel_03 = -1;
    m_iso_rel_03_charged = -1;
    m_sigma_ietaieta = -1;
  }

  bool get_selector(Selector i) const {
    return (m_selector_bits & (uint64_t(1) << static_cast<uint64_t>(i)));
  }

  void set_selector(Selector i, bool value) {
    if(value) m_selector_bits |=   uint64_t(1) << static_cast<uint64_t>(i);
    else      m_selector_bits &= ~(uint64_t(1) << static_cast<uint64_t>(i));
  }

  uint64_t selector_bits() const {return m_selector_bits;};
  int jetidx() const {return m_jetidx;};
  int lost_hits() const {return m_lost_hits;};
  bool conv_veto() const {return m_conv_veto;};
  bool is_pf() const {return m_is_pf;};

  float sumchpt() const {return m_sumchpt;};
  float sumnhet() const {return m_sumnhet;};
  float sumphpt() const {return m_sumphpt;};
  float sumpupt() const {return m_sumpupt;};

  float dphi_in() const {return m_dphi_in;};
  float deta_in_seed() const {return m_deta_in_seed;};
  float pt_err() const {return m_pt_err;};
  float phi_err() const {return m_phi_err;};
  float eta_err() const {return m_eta_err;};
  float eta_sc() const {return m_eta_sc;};
  float phi_sc() const {return m_phi_sc;};
  float e_sc() const {return m_e_sc;};
  float dxy() const {return m_dxy;};
  float dz() const {return m_dz;};
  float d0() const {return m_d0;};
  float dxy_err() const {return m_dxy_err;};
  float dz_err() const {return m_dz_err;};
  float d0_err() const {return m_d0_err;};
  float ea() const {return m_ea;};
  float einv_minus_pinv() const {return m_einv_minus_pinv;};
  float h_over_e() const {return m_h_over_e;};
  float iso_rel_03() const {return m_iso_rel_03;};
  float iso_rel_03_charged() const {return m_iso_rel_03_charged;};
  float sigma_ietaieta() const {return m_sigma_ietaieta;};

  void set_selector_bits(uint64_t x){m_selector_bits = x;};
  void set_jetidx(int x){m_jetidx = x;};
  void set_lost_hits(int x){m_lost_hits = x;};
  void set_conv_veto(bool x){m_conv_veto = x;};
  void set_is_pf(bool x){m_is_pf = x;};

  void set_sumchpt(float x){m_sumchpt = x;};
  void set_sumnhet(float x){m_sumnhet = x;};
  void set_sumphpt(float x){m_sumphpt = x;};
  void set_sumpupt(float x){m_sumpupt = x;};

  void set_dphi_in(float x){m_dphi_in = x;};
  void set_deta_in_seed(float x){m_deta_in_seed = x;};
  void set_pt_err(float x){m_pt_err = x;};
  void set_phi_err(float x){m_phi_err = x;};
  void set_eta_err(float x){m_eta_err = x;};
  void set_eta_sc(float x){m_eta_sc = x;};
  void set_phi_sc(float x){m_phi_sc = x;};
  void set_e_sc(float x){m_e_sc = x;};
  void set_einv_minus_pinv(float x){m_einv_minus_pinv = x;};
  void set_h_over_e(float x){m_h_over_e = x;};
  void set_dxy(float x){m_dxy = x;};
  void set_dz(float x){m_dz = x;};
  void set_d0(float x){m_d0 = x;};
  void set_dxy_err(float x){m_dxy_err = x;};
  void set_dz_err(float x){m_dz_err = x;};
  void set_d0_err(float x){m_d0_err = x;};
  void set_ea(float x){m_ea = x;};
  void set_iso_rel_03(float x){m_iso_rel_03 = x;}; // with ea*rho correction
  void set_iso_rel_03_charged(float x){m_iso_rel_03_charged = x;};
  void set_sigma_ietaieta(float x){m_sigma_ietaieta = x;};

protected:
  uint64_t m_selector_bits;
  int m_jetidx;
  int m_lost_hits;
  bool m_conv_veto;
  bool m_is_pf;

  // PFiso components (dR < 0.3) (for muons it's 0.4) -- this is used in the cut-based IDs
  float m_sumchpt;
  float m_sumnhet;
  float m_sumphpt;
  float m_sumpupt;

  float m_dphi_in;
  float m_deta_in_seed;
  float m_pt_err;
  float m_phi_err;
  float m_eta_err;
  float m_eta_sc;
  float m_phi_sc;
  float m_e_sc;
  float m_dxy;
  float m_dz;
  float m_d0;
  float m_dxy_err;
  float m_dz_err;
  float m_d0_err;
  float m_ea;
  float m_einv_minus_pinv;
  float m_h_over_e;
  float m_iso_rel_03;
  float m_iso_rel_03_charged;
  float m_sigma_ietaieta;
};
