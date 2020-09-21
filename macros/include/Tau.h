#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Particle.h"

using namespace std;

// Basically a Particle with a pdgId
class Tau : public FlavorParticle {

public:
  // Constructors, destructor
  Tau(){
    m_charge = 0;
    m_decay_mode = 0;
    m_gen_part_flav = 0;
    m_id_deeptau_vse = 0;
    m_id_deeptau_vsmu = 0;
    m_id_deeptau_vsjet = 0;
    m_charged_iso = 0.;
    m_neutral_iso = 0.;
    m_dxy = 0.;
    m_dz = 0.;
    m_pu_corr = 0.;
    m_score_deeptau_vse = 0.;
    m_score_deeptau_vsmu = 0.;
    m_score_deeptau_vsjet = 0.;
    m_comb_iso = 0.;
    m_comb_iso_dr03 = 0.;
  }

  int charge(){return m_charge;};
  int decay_mode(){return m_decay_mode;};
  unsigned char gen_part_flav(){return m_gen_part_flav;};
  unsigned char id_deeptau_vse(){return m_id_deeptau_vse;};
  unsigned char id_deeptau_vsmu(){return m_id_deeptau_vsmu;};
  unsigned char id_deeptau_vsjet(){return m_id_deeptau_vsjet;};
  float charged_iso(){return m_charged_iso;};
  float neutral_iso(){return m_neutral_iso;};
  float dxy(){return m_dxy;};
  float dz(){return m_dz;};
  float pu_corr(){return m_pu_corr;};
  float score_deeptau_vse(){return m_score_deeptau_vse;};
  float score_deeptau_vsmu(){return m_score_deeptau_vsmu;};
  float score_deeptau_vsjet(){return m_score_deeptau_vsjet;};
  float comb_iso(){return m_comb_iso;};
  float comb_iso_dr03(){return m_comb_iso_dr03;};

  void set_charge(int x){m_charge = x;};
  void set_decay_mode(int x){m_decay_mode = x;};
  void set_gen_part_flav(unsigned char x){m_gen_part_flav = x;};
  void set_id_deeptau_vse(unsigned char x){m_id_deeptau_vse = x;};
  void set_id_deeptau_vsmu(unsigned char x){m_id_deeptau_vsmu = x;};
  void set_id_deeptau_vsjet(unsigned char x){m_id_deeptau_vsjet = x;};
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
  int m_charge;
  int m_decay_mode;
  unsigned char m_gen_part_flav;
  unsigned char m_id_deeptau_vse;
  unsigned char m_id_deeptau_vsmu;
  unsigned char m_id_deeptau_vsjet;
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
