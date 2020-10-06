#include "include/TauIds.h"
#include "include/useful_functions.h"

using namespace std;

TauID::TauID(Tau::Selector sel_) : sel(sel_){}

bool TauID::operator()(const Tau & tau, const RecoEvent & ev) const{
  return tau.get_selector(sel);
}
