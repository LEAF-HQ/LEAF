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
  return d >= dmin && (d < dmax || dmax < 0);
}
