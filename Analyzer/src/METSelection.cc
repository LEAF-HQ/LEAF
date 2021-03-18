#include "Analyzer/include/METSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


METSelection::METSelection(const Config & cfg, double min_, double max_) : min(min_), max(max_){}

bool METSelection::passes(RecoEvent & event){

  double met = event.met->pt();

  return(met >= min && (met < max || max == -1));
}
