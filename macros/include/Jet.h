#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Particle.h"

using namespace std;

// Basically a Particle with a pdgId
class Jet : public Particle {

public:
  // Constructors, destructor
  Jet(){
    m_area = -1.;
    m_score_CSVv2 = -1.;
    m_score_DeepB = -1.;
    m_score_qgl = -1.;
    m_ch_em_efrac = -1.;
    m_ch_had_efrac = -1.;
    m_ne_em_efrac = -1.;
    m_ne_had_efrac = -1.;
    m_mu_efrac = -1.;
    m_jet_id = -1;
    m_pu_id = -1;
    m_raw_factor = -1.;
    m_muon_sub_raw_factor = -1.;
    m_parton_flavor = 0;
    m_hadron_flavor = 0;
    m_n_constituents = -1;
    m_n_muons = -1;
    m_n_electrons = -1;
  }

float area(){return m_area;};
float score_CSVv2(){return m_score_CSVv2;};
float score_DeepB(){return m_score_DeepB;};
float score_qgl(){return m_score_qgl;};
float ch_em_efrac(){return m_ch_em_efrac;};
float ch_had_efrac(){return m_ch_had_efrac;};
float ne_em_efrac(){return m_ne_em_efrac;};
float ne_had_efrac(){return m_ne_had_efrac;};
float mu_efrac(){return m_mu_efrac;};
int jet_id(){return m_jet_id;};
int pu_id(){return m_pu_id;};
float raw_factor(){return m_raw_factor;};
float muon_sub_raw_factor(){return m_muon_sub_raw_factor;};
int parton_flavor(){return m_parton_flavor;};
int hadron_flavor(){return m_hadron_flavor;};
int n_constituents(){return m_n_constituents;};
int n_muons(){return m_n_muons;};
int n_electrons(){return m_n_electrons;};

void set_area(float x){m_area = x;};
void set_score_CSVv2(float x){m_score_CSVv2 = x;};
void set_score_DeepB(float x){m_score_DeepB = x;};
void set_score_qgl(float x){m_score_qgl = x;};
void set_ch_em_efrac(float x){m_ch_em_efrac = x;};
void set_ch_had_efrac(float x){m_ch_had_efrac = x;};
void set_ne_em_efrac(float x){m_ne_em_efrac = x;};
void set_ne_had_efrac(float x){m_ne_had_efrac = x;};
void set_mu_efrac(float x){m_mu_efrac = x;};
void set_jet_id(int x){m_jet_id = x;};
void set_pu_id(int x){m_pu_id = x;};
void set_raw_factor(float x){m_raw_factor = x;};
void set_muon_sub_raw_factor(float x){m_muon_sub_raw_factor = x;};
void set_parton_flavor(int x){m_parton_flavor = x;};
void set_hadron_flavor(int x){m_hadron_flavor = x;};
void set_n_constituents(int x){m_n_constituents = x;};
void set_n_muons(int x){m_n_muons = x;};
void set_n_electrons(int x){m_n_electrons = x;};



protected:
  float m_area;
  float m_score_CSVv2;
  float m_score_DeepB;
  float m_score_qgl;
  float m_ch_em_efrac;
  float m_ch_had_efrac;
  float m_ne_em_efrac;
  float m_ne_had_efrac;
  float m_mu_efrac;
  int   m_jet_id;
  int   m_pu_id; // 80X (2016) training
  float m_raw_factor; // = 1 - (Factor to get to raw pT) = 1 - (raw pt)/(corr pt)
  float m_muon_sub_raw_factor; // = 1 - (muon-subtracted raw pt)/(raw pt)
  int m_parton_flavor;
  int m_hadron_flavor;
  int m_n_constituents;
  int m_n_muons;
  int m_n_electrons;




};
