#include "include/ElectronIds.h"
#include "include/useful_functions.h"

using namespace std;

ElectronID::ElectronID(Electron::Selector sel_) : sel(sel_){}

bool ElectronID::operator()(const Electron & electron, const RecoEvent & ev) const{
  return electron.get_selector(sel);
}
