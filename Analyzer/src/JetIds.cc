#include "LEAF/Analyzer/include/JetIds.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"

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
  if(m_wp == JetBTag::DeepJet_Loose) pass = (jet.score_DeepFlavB() > 0.0532);
  else if(m_wp == JetBTag::DeepJet_Medium) pass = (jet.score_DeepFlavB() > 0.3040);
  else if(m_wp == JetBTag::DeepJet_Tight) pass = (jet.score_DeepFlavB() > 0.7476);
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


GenJetLeptonOverlapID::GenJetLeptonOverlapID(double dr_) : m_dr(dr_){}

bool GenJetLeptonOverlapID::operator()(const GenJet & jet, const GenEvent & ev) const{
  for(const GenParticle& part: *ev.genparticles_pruned){
    if (! isLeptonic(part.pdgid())) continue;
    if(deltaR(jet, part) < m_dr) return false;
  }

  return true;
}
