#include "Analyzer/include/FlagSelection.h"

using namespace std;


FlagSelection::FlagSelection(const Config & cfg, TString flagname_) : flagname(flagname_){}

bool FlagSelection::passes(RecoEvent & event){

  if(flagname.Contains("*")){
    string s_flagname = flagname.Data();
    TString flagname_nowildcard = flagname;

    if(flagname_nowildcard(s_flagname.size() - 1) == TString("*")){
      flagname_nowildcard = flagname_nowildcard(0,s_flagname.size() - 1);
    }

    if(flagname_nowildcard.Contains("*")) throw runtime_error("FlagSelection::passes(): Wildcard is only allowed in the very end of the flag name.");

    if(event.flags->has_prefix(flagname_nowildcard)){
      return event.flags->get_prefix(flagname_nowildcard);
    }
    return false;

  }
  else{
    if(!event.flags->has(flagname)) return false;
    return event.flags->get(flagname);
  }
}
