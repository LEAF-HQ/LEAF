#include "LEAF/Analyzer/include/ElectronIds.h"
#include "LEAF/Analyzer/include/useful_functions.h"

using namespace std;

ElectronID::ElectronID(Electron::Selector sel_) : sel(sel_){}
bool ElectronID::operator()(const Electron & electron, const RecoEvent & ev) const{
  return electron.get_selector(sel);
}


ElectronIPID::ElectronIPID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool ElectronIPID::operator()(const Electron & electron, const RecoEvent & ev) const{
  float d = sqrt(electron.dxy()*electron.dxy() + electron.dz()*electron.dz());
  return (d >= dmin && (d < dmax || dmax < 0));
}

ElectronDxyID::ElectronDxyID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool ElectronDxyID::operator()(const Electron & electron, const RecoEvent & ev) const{
  float d = fabs(electron.dxy());
  return (d >= dmin && (d < dmax || dmax < 0));
}

ElectronDzID::ElectronDzID(float dmin_, float dmax_) : dmin(dmin_), dmax(dmax_){}
bool ElectronDzID::operator()(const Electron & electron, const RecoEvent & ev) const{
  float d = fabs(electron.dz());
  return (d >= dmin && (d < dmax || dmax < 0));
}


ElectronDetectorHolesID::ElectronDetectorHolesID(){}

bool ElectronDetectorHolesID::operator()(const Electron & electron, const RecoEvent & ev) const{
  float eta = fabs(electron.eta());
  return (eta <= etagap_min || eta>=etagap_max);
}

ElectronIso::ElectronIso(float dmin_, std::string isoname_) : min_iso(dmin_), isolation_name(isoname_){}
bool ElectronIso::operator()(const Electron & elec, const RecoEvent & ev) const{
  double iso = 100;
  try
    {
      

      if(isolation_name == "iso_rel_03") iso = elec.iso_rel_03();
      else if(isolation_name == "iso_rel_03_charged") iso = elec.iso_rel_03_charged();
      else throw std::invalid_argument("Isolation name not valid.");
    }

    catch (std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
  
  return iso < min_iso;
}