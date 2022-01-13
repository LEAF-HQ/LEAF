#include "LEAF/Analyzer/include/METSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


METSelection::METSelection(const Config & cfg, float min_, float max_) : min(min_), max(max_){}

bool METSelection::passes(RecoEvent & event){

  float met = event.met->pt();
  return(met >= min && (met <= max || max == -1.));
}
