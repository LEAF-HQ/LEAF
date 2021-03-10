#include "include/FlagSelection.h"

using namespace std;


FlagSelection::FlagSelection(const Config & cfg, TString flagname_) : flagname(flagname_){}

bool FlagSelection::passes(RecoEvent & event){

  return event.flags->get(flagname);

}
