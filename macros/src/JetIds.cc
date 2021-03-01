#include "include/JetIds.h"
#include "include/useful_functions.h"

using namespace std;

JetID::JetID(wp wp_) : m_wp(wp_){}

bool JetID::operator()(const Jet & jet, const RecoEvent & ev) const{
  bool pass = false;
  if(m_wp == JetID::WP_TIGHT){
    pass = (jet.jet_id() >= 4);
  }
  else throw runtime_error("In JetID::operator(): Invalid WP specified.");

  return pass;
}

JetPUID::JetPUID(wp wp_) : m_wp(wp_){}

bool JetPUID::operator()(const Jet & jet, const RecoEvent & ev) const{
  bool pass = false;
  if(jet.pt() < 50){
    if(m_wp == JetPUID::WP_TIGHT){
      pass = (jet.pu_id() >= 7);
    }
    else throw runtime_error("In JetPUID::operator(): Invalid WP specified.");
  }
  else{ //PU ID only applied to jets with pt < 50
    pass = true;
  }

  return pass;
}


JetBTag::JetBTag(wp wp_) : m_wp(wp_){}

bool JetBTag::operator()(const Jet & jet, const RecoEvent & ev) const{
  bool pass = false;
  if(m_wp == JetBTag::DeepCSV_Loose) pass = (jet.score_DeepB() > 0.1355);
  else if(m_wp == JetBTag::DeepCSV_Medium) pass = (jet.score_DeepB() > 0.4506);
  else if(m_wp == JetBTag::DeepCSV_Tight) pass = (jet.score_DeepB() > 0.7738);
  else throw runtime_error("In JetBTag::operator(): Invalid WP specified.");

  return pass;
}

JetTauOverlapID::JetTauOverlapID(double dr_) : m_dr(dr_){}

bool JetTauOverlapID::operator()(const Jet & jet, const RecoEvent & ev) const{
  bool pass = true;
  for(size_t i=0; i<ev.taus->size(); i++){
    if(deltaR(jet, ev.taus->at(i)) < m_dr) pass = false;
  }

  return pass;
}

JetLeptonOverlapID::JetLeptonOverlapID(double dr_) : m_dr(dr_){}

bool JetLeptonOverlapID::operator()(const Jet & jet, const RecoEvent & ev) const{
  for(size_t i=0; i<ev.electrons->size(); i++){
    if(deltaR(jet, ev.electrons->at(i)) < m_dr) return false;
  }
  for(size_t i=0; i<ev.muons->size(); i++){
    if(deltaR(jet, ev.muons->at(i)) < m_dr) return false;
  }

  return true;
}
