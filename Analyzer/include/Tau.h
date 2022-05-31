#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Particle.h"

class Tau : public FlavorParticle {

public:

  enum Selector{
    DeepTauVsJetVVVLoose,
    DeepTauVsJetVVLoose,
    DeepTauVsJetVLoose,
    DeepTauVsJetLoose,
    DeepTauVsJetMedium,
    DeepTauVsJetTight,
    DeepTauVsJetVTight,
    DeepTauVsJetVVTight,
    DeepTauVsEleVVVLoose,
    DeepTauVsEleVVLoose,
    DeepTauVsEleVLoose,
    DeepTauVsEleLoose,
    DeepTauVsEleMedium,
    DeepTauVsEleTight,
    DeepTauVsEleVTight,
    DeepTauVsEleVVTight,
    DeepTauVsMuVLoose,
    DeepTauVsMuLoose,
    DeepTauVsMuMedium,
    DeepTauVsMuTight
  };


  // Constructors, destructor
  Tau(){
    m_selector_bits = 0;
    m_jetidx = -1;
    m_decay_mode = 0;
    m_gen_part_flav = -1;
    m_charged_iso = -1.;
    m_neutral_iso = -1.;
    m_dxy = -1.;
    m_dz = -1.;
    m_pu_corr = -1.;
    m_score_deeptau_vse = -1.;
    m_score_deeptau_vsmu = -1.;
    m_score_deeptau_vsjet = -1.;
    m_comb_iso = -1.;
    m_comb_iso_dr03 = -1.;
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
  int decay_mode() const {return m_decay_mode;};
  int gen_part_flav() const {return m_gen_part_flav;};
  float charged_iso() const {return m_charged_iso;};
  float neutral_iso() const {return m_neutral_iso;};
  float dxy() const {return m_dxy;};
  float dz() const {return m_dz;};
  float pu_corr() const {return m_pu_corr;};
  float score_deeptau_vse() const {return m_score_deeptau_vse;};
  float score_deeptau_vsmu() const {return m_score_deeptau_vsmu;};
  float score_deeptau_vsjet() const {return m_score_deeptau_vsjet;};
  float comb_iso() const {return m_comb_iso;};
  float comb_iso_dr03() const {return m_comb_iso_dr03;};

  void set_selector_bits(uint64_t x){m_selector_bits = x;};
  void set_jetidx(int x){m_jetidx = x;};
  void set_decay_mode(int x){m_decay_mode = x;};
  void set_gen_part_flav(int x){m_gen_part_flav = x;};
  void set_charged_iso(float x){m_charged_iso = x;};
  void set_neutral_iso(float x){m_neutral_iso = x;};
  void set_dxy(float x){m_dxy = x;};
  void set_dz(float x){m_dz = x;};
  void set_pu_corr(float x){m_pu_corr = x;};
  void set_score_deeptau_vse(float x){m_score_deeptau_vse = x;};
  void set_score_deeptau_vsmu(float x){m_score_deeptau_vsmu = x;};
  void set_score_deeptau_vsjet(float x){m_score_deeptau_vsjet = x;};
  void set_comb_iso(float x){m_comb_iso = x;};
  void set_comb_iso_dr03(float x){m_comb_iso_dr03 = x;};


protected:
  uint64_t m_selector_bits;
  int m_jetidx;
  int m_decay_mode;
  int m_gen_part_flav;
  float m_charged_iso;
  float m_neutral_iso;
  float m_dxy;
  float m_dz;
  float m_pu_corr;
  float m_score_deeptau_vse;
  float m_score_deeptau_vsmu;
  float m_score_deeptau_vsjet;
  float m_comb_iso;
  float m_comb_iso_dr03;




};
