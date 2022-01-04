#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "FlavorParticle.h"

using namespace std;

class Muon : public FlavorParticle {

public:

  enum Selector{
    Global,
    PF,
    Tracker,
    Standalone,
    Good,

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
    IDMvaLowPtLoose,
    IDMvaLowPtMedium,
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

  /*
  CLASSIFICATION: For each RECO Muon, match to SIM particle, and then:
  - If the SIM is not a Muon, label as Punchthrough (1) except if it is an electron or positron (11)
  - If the SIM is a Muon, then look at it's provenance.
  A) the SIM muon is also a GEN muon, whose parent is NOT A HADRON AND NOT A TAU
  -> classify as "primary" (13).
  B) the SIM muon is also a GEN muon, whose parent is HEAVY FLAVOURED HADRON OR A TAU
  -> classify as "heavy quark" (3) or "tau" (15)
  C) classify as "light flavour/decay" (2)
  In any case, if the TP is not preferentially matched back to the same RECO muon,
  label as Ghost (flip the classification)
  */
  enum SimType{
    Unknown                     = 999,
    NotMatched                  = 0,
    MatchedPunchthrough         = 1,
    MatchedElectron             = 11,
    MatchedTau                  = 15,
    MatchedPrimaryMuon          = 13,
    MatchedHeavyQuark           = 3,
    MatchedLightQuark           = 2,
    GhostPunchthrough           = -1,
    GhostElectron               = -11,
    GhostTau                    = -15,
    GhostPrimaryMuon            = -13,
    GhostHeavyQuark             = -3,
    GhostLightQuark             = -2

  };

  Muon(){
    m_selector_bits = 0;
    m_gen_part_flav = GenPartFlav::Other;
    m_sim_type = SimType::Unknown;
    m_charge = 0;
    m_dxy = -1;
    m_dz = -1;
    m_d0 = -1;
    m_edxy = -1;
    m_edz = -1;
    m_ed0 = -1;
    m_iso_rel_04 = -1;
    m_iso_rel_03 = -1;
    m_iso_rel_03_charged = -1;
    m_pt_err = -1;
    m_iso_tk = -1;
    m_sumchpt = -1.;
    m_sumnhet = -1.;
    m_sumphpt = -1.;
    m_sumpupt = -1.;
    m_tunep_pt = -1;
    m_tunep_pt_err = -1;
    m_tunep_eta = -1;
    m_tunep_phi = -1;
    m_tunep_numberOfValidMuonHits = -1;

    m_globalTrack_normalizedChi2 = -1;
    m_globalTrack_numberOfValidMuonHits = -1;
    m_numberOfMatchedStations = -1;
    m_expectedNnumberOfMatchedStations = -1;
    m_numberOfMatchedRPCLayers = -1;
    m_innerTrack_trackerLayersWithMeasurement = -1;
    m_innerTrack_numberOfValidPixelHits = -1;
    m_innerTrack_validFraction = -1;
    m_combinedQuality_chi2LocalPosition = -1;
    m_combinedQuality_trkKink = -1;
    m_segmentCompatibility = -1;
    m_innerTrack_isHighQuality = false;
    m_stationMask = -1;
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
  const SimType sim_type() const {return m_sim_type;};
  const int sim_pdgid() const {return m_sim_pdgid;};
  const int sim_mother_pdgid() const {return m_sim_mother_pdgid;};
  const int sim_heaviestmother_flav() const {return m_sim_heaviestmother_flav;};
  const int jetidx() const {return m_jetidx;};
  const float dxy() const {return m_dxy;};
  const float dz() const {return m_dz;};
  const float d0() const {return m_d0;};
  const float edxy() const {return m_edxy;};
  const float edz() const {return m_edz;};
  const float ed0() const {return m_ed0;};
  const float iso_rel_04() const {return m_iso_rel_04;};
  const float iso_rel_03() const {return m_iso_rel_03;};
  const float iso_rel_03_charged() const {return m_iso_rel_03_charged;};
  const float pt_err() const {return m_pt_err;};
  const float iso_tk() const {return m_iso_tk;};
  const float sumchpt() const {return m_sumchpt;};
  const float sumnhet() const {return m_sumnhet;};
  const float sumphpt() const {return m_sumphpt;};
  const float sumpupt() const {return m_sumpupt;};
  const float tunep_pt() const {return m_tunep_pt;};
  const float tunep_pt_err() const {return m_tunep_pt_err;};
  const float tunep_eta() const {return m_tunep_eta;};
  const float tunep_phi() const {return m_tunep_phi;};
  const int tunep_numberOfValidMuonHits() const {return m_tunep_numberOfValidMuonHits;};
  const float globalTrack_normalizedChi2() const {return m_globalTrack_normalizedChi2;};
  const int globalTrack_numberOfValidMuonHits() const {return m_globalTrack_numberOfValidMuonHits;};
  const int numberOfMatchedStations() const {return m_numberOfMatchedStations;};
  const int expectedNnumberOfMatchedStations() const {return m_expectedNnumberOfMatchedStations;};
  const int set_numberOfMatchedRPCLayers() const {return m_numberOfMatchedRPCLayers;};
  const int innerTrack_trackerLayersWithMeasurement() const {return m_innerTrack_trackerLayersWithMeasurement;};
  const int innerTrack_numberOfValidPixelHits() const {return m_innerTrack_numberOfValidPixelHits;};
  const float innerTrack_validFraction() const {return m_innerTrack_validFraction;};
  const float combinedQuality_chi2LocalPosition() const {return m_combinedQuality_chi2LocalPosition;};
  const float combinedQuality_trkKink() const {return m_combinedQuality_trkKink;};
  const float segmentCompatibility() const {return m_segmentCompatibility;};
  const bool innerTrack_isHighQuality() const {return m_innerTrack_isHighQuality;};
  const int stationMask() const {return m_stationMask;};


  void set_selector_bits(uint64_t x){m_selector_bits = x;};
  void set_gen_part_flav(GenPartFlav x){m_gen_part_flav = x;};
  void set_sim_type(SimType x){m_sim_type = x;};
  void set_sim_pdgid(int x){m_sim_pdgid = x;};
  void set_sim_mother_pdgid(int x){m_sim_mother_pdgid = x;};
  void set_sim_heaviestmother_flav(int x){m_sim_heaviestmother_flav = x;};
  void set_jetidx(int x){m_jetidx = x;};
  void set_dxy(float x){m_dxy = x;};
  void set_dz(float x){m_dz = x;};
  void set_d0(float x){m_d0 = x;};
  void set_edxy(float x){m_edxy = x;};
  void set_edz(float x){m_edz = x;};
  void set_ed0(float x){m_ed0 = x;};
  void set_iso_rel_04(float x){m_iso_rel_04 = x;};
  void set_iso_rel_03(float x){m_iso_rel_03 = x;};
  void set_iso_rel_03_charged(float x){m_iso_rel_03_charged = x;};
  void set_pt_err(float x){m_pt_err = x;};
  void set_iso_tk(float x){m_iso_tk = x;};
  void set_sumchpt(float x){m_sumchpt = x;};
  void set_sumnhet(float x){m_sumnhet = x;};
  void set_sumphpt(float x){m_sumphpt = x;};
  void set_sumpupt(float x){m_sumpupt = x;};
  void set_tunep_pt(float x){m_tunep_pt = x;};
  void set_tunep_pt_err(float x){m_tunep_pt_err = x;};
  void set_tunep_eta(float x){m_tunep_eta = x;};
  void set_tunep_phi(float x){m_tunep_phi = x;};
  void set_tunep_numberOfValidMuonHits(int x){m_tunep_numberOfValidMuonHits = x;};

  void set_globalTrack_normalizedChi2(float x){m_globalTrack_normalizedChi2 = x;};
  void set_globalTrack_numberOfValidMuonHits(int x){m_globalTrack_numberOfValidMuonHits = x;};
  void set_numberOfMatchedStations(int x){m_numberOfMatchedStations = x;};
  void set_expectedNnumberOfMatchedStations(int x){m_expectedNnumberOfMatchedStations = x;};
  void set_numberOfMatchedRPCLayers(int x){m_numberOfMatchedRPCLayers = x;};
  void set_innerTrack_trackerLayersWithMeasurement(int x){m_innerTrack_trackerLayersWithMeasurement = x;};
  void set_innerTrack_numberOfValidPixelHits(int x){m_innerTrack_numberOfValidPixelHits = x;};
  void set_innerTrack_validFraction(float x){m_innerTrack_validFraction = x;};
  void set_combinedQuality_chi2LocalPosition(float x){m_combinedQuality_chi2LocalPosition = x;};
  void set_combinedQuality_trkKink(float x){m_combinedQuality_trkKink = x;};
  void set_segmentCompatibility(float x){m_segmentCompatibility = x;};
  void set_innerTrack_isHighQuality(bool x){m_innerTrack_isHighQuality = x;};
  void set_stationMask(int x){m_stationMask = x;};

protected:
  uint64_t m_selector_bits;
  GenPartFlav m_gen_part_flav;
  SimType m_sim_type;
  int m_sim_pdgid;
  int m_sim_mother_pdgid;
  int m_sim_heaviestmother_flav;
  int m_jetidx;
  float m_dxy;
  float m_dz;
  float m_d0;
  float m_edxy;
  float m_edz;
  float m_ed0;
  float m_iso_rel_04;
  float m_iso_rel_03;
  float m_iso_rel_03_charged;
  float m_pt_err;
  float m_iso_tk;

  // PFiso components (dR < 0.4)
  float m_sumchpt;
  float m_sumnhet;
  float m_sumphpt;
  float m_sumpupt;

  // TuneP track variables
  float m_tunep_pt;
  float m_tunep_pt_err;
  float m_tunep_eta;
  float m_tunep_phi;
  int m_tunep_numberOfValidMuonHits;

  // variables used in IDs
  float m_globalTrack_normalizedChi2;
  int m_globalTrack_numberOfValidMuonHits;
  int m_numberOfMatchedStations;
  int m_expectedNnumberOfMatchedStations;
  int m_numberOfMatchedRPCLayers;
  int m_innerTrack_trackerLayersWithMeasurement;
  int m_innerTrack_numberOfValidPixelHits;
  float m_innerTrack_validFraction;
  float m_combinedQuality_chi2LocalPosition;
  float m_combinedQuality_trkKink;
  float m_segmentCompatibility;
  bool m_innerTrack_isHighQuality;
  int m_stationMask;







};
