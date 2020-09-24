#include "include/JetIds.h"
#include "include/useful_functions.h"

using namespace std;

JetID::JetID(wp wp_) : m_wp(wp_){}

bool JetID::operator()(const Jet & jet, const RecoEvent & ev) const{
  bool pass = false;
  if(m_wp == WP_TIGHT){
    pass = (jet.jet_id() >= 4);
  }
  else throw runtime_error("In JetID::operator(): Invalid WP specified.");

  return pass;
}
