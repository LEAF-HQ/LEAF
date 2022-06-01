#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/Particle.h"

// Basically a Particle with a pdgId
class Jet : public Particle {

public:
  // Constructors, destructor
  Jet(){
    m_area = -1.;
    m_score_CSVv2 = -1.;
    m_score_DeepB = -1.;
    m_score_DeepFlavB = -1.;
    m_score_qgl = -1.;
    m_ch_had_efrac = -1.;
    m_ne_had_efrac = -1.;
    m_muo_efrac = -1.;
    m_ele_efrac = -1.;
    m_pho_efrac = -1.;
    m_hf_had_efrac = -1.;
    m_hf_em_efrac = -1.;
    m_jet_id = -1;
    m_pu_id = -1;
    m_raw_factor = -1.;
    m_L1_factor = -1.;
    m_parton_flavor = 0;
    m_hadron_flavor = 0;
    m_n_constituents = -1;
    m_n_muons = -1;
    m_n_electrons = -1;
  }

  float area() const {return m_area;};
  float score_CSVv2() const {return m_score_CSVv2;};
  float score_DeepB() const {return m_score_DeepB;};
  float score_DeepFlavB() const {return m_score_DeepFlavB;};
  float score_qgl() const {return m_score_qgl;};
  float ch_had_efrac() const {return m_ch_had_efrac;};
  float ne_had_efrac() const {return m_ne_had_efrac;};
  float muo_efrac() const {return m_muo_efrac;};
  float ele_efrac() const {return m_ele_efrac;};
  float pho_efrac() const {return m_pho_efrac;};
  float hf_had_efrac() const {return m_hf_had_efrac;};
  float hf_em_efrac() const {return m_hf_em_efrac;};
  float ne_em_efrac() const {return m_pho_efrac + m_hf_em_efrac;};            // central electrons (HF electrons would be HF EM) [deprecated in CMSSW, custom-defined in LEAF]
  float ch_em_efrac() const {return m_ele_efrac;};                            // photons + HF electromagnetic [deprecated in CMSSW, custom-defined in LEAF]
  float had_efrac() const {return m_ne_had_efrac + m_ch_had_efrac;};          // all hadrons (charged + neutral) [custom-defined in LEAF]
  float em_efrac() const {return m_pho_efrac + m_hf_em_efrac + m_ele_efrac;}; // all EM (charged + neutral) [custom-defined in LEAF]
  int jet_id() const {return m_jet_id;};
  int pu_id() const {return m_pu_id;};
  float raw_factor() const {return m_raw_factor;};
  float L1_factor() const {return m_L1_factor;};
  int parton_flavor() const {return m_parton_flavor;};
  int hadron_flavor() const {return m_hadron_flavor;};
  int n_constituents() const {return m_n_constituents;};
  int n_muons() const {return m_n_muons;};
  int n_electrons() const {return m_n_electrons;};
  int identifier() const {return m_identifier;};

  void set_area(float x){m_area = x;};
  void set_score_CSVv2(float x){m_score_CSVv2 = x;};
  void set_score_DeepB(float x){m_score_DeepB = x;};
  void set_score_DeepFlavB(float x){m_score_DeepFlavB = x;};
  void set_score_qgl(float x){m_score_qgl = x;};
  void set_ch_had_efrac(float x){m_ch_had_efrac = x;};
  void set_ne_had_efrac(float x){m_ne_had_efrac = x;};
  void set_muo_efrac(float x){m_muo_efrac = x;};
  void set_ele_efrac(float x){m_ele_efrac = x;};
  void set_pho_efrac(float x){m_pho_efrac = x;};
  void set_hf_had_efrac(float x){m_hf_had_efrac = x;};
  void set_hf_em_efrac(float x){m_hf_em_efrac = x;};
  void set_jet_id(int x){m_jet_id = x;};
  void set_pu_id(int x){m_pu_id = x;};
  void set_L1_factor(float x){m_L1_factor = x;};
  void set_raw_factor(float x){m_raw_factor = x;};
  void set_parton_flavor(int x){m_parton_flavor = x;};
  void set_hadron_flavor(int x){m_hadron_flavor = x;};
  void set_n_constituents(int x){m_n_constituents = x;};
  void set_n_muons(int x){m_n_muons = x;};
  void set_n_electrons(int x){m_n_electrons = x;};
  void set_identifier(int x){m_identifier = x;};



protected:
  float m_area;
  float m_score_CSVv2;
  float m_score_DeepB;
  float m_score_DeepFlavB;
  float m_score_qgl;
  float m_ne_had_efrac; // neutral hadrons (central + HF [central is not stored anywhere])
  float m_ch_had_efrac; // central charged hadrons (non-central have unknown charge)
  float m_muo_efrac;    // muons
  float m_ele_efrac;    // electrons
  float m_pho_efrac;    // photons
  float m_hf_had_efrac; // HF hadrons (not needed for total sum, it is already included in ne_had_efrac)
  float m_hf_em_efrac;  // HF electromagnetic
  int   m_jet_id;
  int   m_pu_id; // 80X (2016) training
  float m_raw_factor; // = Factor to get to raw pT = (raw pt)/(corr pt)
  float m_L1_factor; // = Factor to get from raw to L1
  int m_parton_flavor;
  int m_hadron_flavor;
  int m_n_constituents;
  int m_n_muons;
  int m_n_electrons;
  int m_identifier;




};
