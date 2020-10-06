#include "include/MuonIds.h"
#include "include/useful_functions.h"

using namespace std;

MuonID::MuonID(Muon::Selector sel_) : sel(sel_){}

bool MuonID::operator()(const Muon & muon, const RecoEvent & ev) const{
  return muon.get_selector(sel);
}
