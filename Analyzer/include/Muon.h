#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "FlavorParticle.h"

using namespace std;

// Basically a Particle with a pdgId
class Muon : public FlavorParticle {

public:

  enum Selector{
    IDCutBasedGlobalHighPt,
    IDCutBasedTrackerHighPt,
    IDCutBasedSoft,
    IDCutBasedLoose,
    IDCutBasedMedium,
    IDCutBasedMediumPrompt,
    IDCutBasedTight,
    IDMvaSoft,
    IDMvaLoose,
    IDMvaMedium,
    IDMvaTight,
    IDMvaVTight,
    IDMvaVVTight,
    IDTriggerLoose,

    IsoMultiLoose,
    IsoMultiMedium,
    IsoPFVLoose,
    IsoPFLoose,
    IsoPFMedium,
    IsoPFTight,
    IsoPFVTight,
    IsoPFVVTight,
    IsoTkLoose,
    IsoTkTight,
    IsoPuppiLoose,
    IsoPuppiMedium,
    IsoPuppiTight,
    IsoMiniLoose,
    IsoMiniMedium,
    IsoMiniTight,
    IsoMiniVTight
  };

  enum GenPartFlav{
    Unmatched = 0,
    Prompt    = 1,
    FromPromptTau = 15,
    FromB     = 5,
    FromC     = 4,
    Other     = 3
  };

  Muon(){
    m_charge = 0;
    m_selector_bits = 0;
    m_gen_part_flav = Other;
    m_is_global = 0;
    m_is_pf = 0;
    m_is_tracker = 0;
    m_charge = 0;
    m_dxy = 0;
    m_dz = 0;
    m_iso_mini = 0;
    m_iso_mini_charged = 0;
    m_iso_rel_04 = 0;
    m_iso_rel_03 = 0;
    m_iso_rel_03_charged = 0;
    m_pt_err = 0;
    m_iso_tk = 0;
    m_pt_rel_tunep = 0;
  }

  bool get_selector(Selector i) const {
    return (m_selector_bits & (uint64_t(1) << static_cast<uint64_t>(i)));
  }

  void set_selector(Selector i, bool value) {
    if(value) m_selector_bits |=   uint64_t(1) << static_cast<uint64_t>(i);
    else      m_selector_bits &= ~(uint64_t(1) << static_cast<uint64_t>(i));
  }

  const uint64_t selector_bits() const {return m_selector_bits;};
  const GenPartFlav gen_part_flav() const {return m_gen_part_flav;};
  const bool is_global() const {return m_is_global;};
  const bool is_pf() const {return m_is_pf;};
  const bool is_tracker() const {return m_is_tracker;};
  const int charge() const {return m_charge;};
  const int jetidx() const {return m_jetidx;};
  const float dxy() const {return m_dxy;};
  const float dz() const {return m_dz;};
  const float iso_mini() const {return m_iso_mini;};
  const float iso_mini_charged() const {return m_iso_mini_charged;};
  const float iso_rel_04() const {return m_iso_rel_04;};
  const float iso_rel_03() const {return m_iso_rel_03;};
  const float iso_rel_03_charged() const {return m_iso_rel_03_charged;};
  const float pt_err() const {return m_pt_err;};
  const float iso_tk() const {return m_iso_tk;};
  const float pt_rel_tunep() const {return m_pt_rel_tunep;};

  void set_selector_bits(uint64_t x){m_selector_bits = x;};
  void set_gen_part_flav(GenPartFlav x){m_gen_part_flav = x;};
  void set_is_global(bool x){m_is_global = x;};
  void set_is_pf(bool x){m_is_pf = x;};
  void set_is_tracker(bool x){m_is_tracker = x;};
  void set_charge(int x){m_charge = x;};
  void set_jetidx(int x){m_jetidx = x;};
  void set_dxy(float x){m_dxy = x;};
  void set_dz(float x){m_dz = x;};
  void set_iso_mini(float x){m_iso_mini = x;};
  void set_iso_mini_charged(float x){m_iso_mini_charged = x;};
  void set_iso_rel_04(float x){m_iso_rel_04 = x;};
  void set_iso_rel_03(float x){m_iso_rel_03 = x;};
  void set_iso_rel_03_charged(float x){m_iso_rel_03_charged = x;};
  void set_pt_err(float x){m_pt_err = x;};
  void set_iso_tk(float x){m_iso_tk = x;};
  void set_pt_rel_tunep(float x){m_pt_rel_tunep = x;};

protected:
  uint64_t m_selector_bits;
  GenPartFlav m_gen_part_flav;
  bool m_is_global;
  bool m_is_pf;
  bool m_is_tracker;
  int m_charge;
  int m_jetidx;
  float m_dxy;
  float m_dz;
  float m_iso_mini;
  float m_iso_mini_charged;
  float m_iso_rel_04;
  float m_iso_rel_03;
  float m_iso_rel_03_charged;
  float m_pt_err;
  float m_iso_tk;
  float m_pt_rel_tunep;







};
