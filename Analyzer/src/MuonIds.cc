#include "Analyzer/include/MuonIds.h"
#include "Analyzer/include/useful_functions.h"

using namespace std;

MuonID::MuonID(Muon::Selector sel_) : sel(sel_){}
bool MuonID::operator()(const Muon & muon, const RecoEvent & ev) const{
  return muon.get_selector(sel);
}

MuonIPID::MuonIPID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool MuonIPID::operator()(const Muon & muon, const RecoEvent & ev) const{
  float d = sqrt(muon.dxy()*muon.dxy() + muon.dz()*muon.dz());
  return (d >= dmin && (d < dmax || dmax < 0));
}
