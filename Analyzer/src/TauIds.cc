#include "Analyzer/include/TauIds.h"
#include "Analyzer/include/useful_functions.h"

using namespace std;

TauID::TauID(Tau::Selector sel_) : sel(sel_){}

bool TauID::operator()(const Tau & tau, const RecoEvent & ev) const{
  return tau.get_selector(sel);
}


TauDecaymodeID::TauDecaymodeID(std::vector<int> decaymodes_) : decaymodes(decaymodes_){}

bool TauDecaymodeID::operator()(const Tau & tau, const RecoEvent & ev) const{

  bool pass = false;
  if ( find(decaymodes.begin(), decaymodes.end(), tau.decay_mode()) != decaymodes.end() ) {
      pass = true;
  }

  return pass;
}


TauDecaymodeVetoID::TauDecaymodeVetoID(std::vector<int> decaymodes_) : decaymodes(decaymodes_){}

bool TauDecaymodeVetoID::operator()(const Tau & tau, const RecoEvent & ev) const{

  bool pass = true;
  if ( find(decaymodes.begin(), decaymodes.end(), tau.decay_mode()) != decaymodes.end() ) {
      pass = false;
  }

  return pass;
}
