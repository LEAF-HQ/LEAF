#include "LEAF/Analyzer/include/MuonIds.h"
#include "LEAF/Analyzer/include/useful_functions.h"

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


MuonDxyID::MuonDxyID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool MuonDxyID::operator()(const Muon & muon, const RecoEvent & ev) const{
  float d = fabs(muon.dxy());
  return (d >= dmin && (d < dmax || dmax < 0));
}

MuonDzID::MuonDzID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool MuonDzID::operator()(const Muon & muon, const RecoEvent & ev) const{
  float d = fabs(muon.dz());
  return (d >= dmin && (d < dmax || dmax < 0));
}

MuonIso::MuonIso(float dmin_, std::string isoname_) : min_iso(dmin_), isolation_name(isoname_){}
bool MuonIso::operator()(const Muon & muon, const RecoEvent & ev) const{
  double iso = 100;
  try
    {
      if(isolation_name == "iso_rel_04") iso = muon.iso_rel_04();
      else if(isolation_name == "iso_rel_03") iso = muon.iso_rel_03();
      else if(isolation_name == "iso_rel_03_charged") iso = muon.iso_rel_03_charged();
      else if(isolation_name == "iso_tk") iso = muon.iso_tk();
      else throw std::invalid_argument("Isolation name not valid.");
    }

    catch (std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
  
  return iso < min_iso;
}