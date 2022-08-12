#include "LEAF/Analyzer/include/METFilterSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;

// list of filters from here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
METFilterSelection::METFilterSelection(const Config & cfg, TString year){

  // define filters to be applied
  if(year == "UL17" || year == "UL18"){
    metfilternames = {"Flag_goodVertices", "Flag_globalSuperTightHalo2016Filter", "Flag_HBHENoiseFilter", "Flag_HBHENoiseIsoFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter", "Flag_BadPFMuonFilter", "Flag_BadPFMuonDzFilter", "Flag_eeBadScFilter", "Flag_ecalBadCalibFilter"};
  }
  else if(year.Contains("UL16")){
    metfilternames = {"Flag_goodVertices", "Flag_globalSuperTightHalo2016Filter", "Flag_HBHENoiseFilter", "Flag_HBHENoiseIsoFilter", "EcalDeadCellTriggerPrimitiveFilter", "Flag_BadPFMuonFilter", "Flag_BadPFMuonDzFilter", "Flag_eeBadScFilter"};
  }
  else throw runtime_error("In METFilterSelection::METFilterSelection(): Invalid year specified in constructor.");


  // set up vector of FlagSelection elements
  for(TString filtername : metfilternames){
    unique_ptr<FlagSelection> sel;
    sel.reset(new FlagSelection(cfg, filtername));
    flag_selections.emplace_back(move(sel));
  }

}

bool METFilterSelection::passes(RecoEvent & event){

  for(size_t i=0; i<flag_selections.size(); i++){
    if(!flag_selections[i]->passes(event)) return false;
  }

  return true;
}
