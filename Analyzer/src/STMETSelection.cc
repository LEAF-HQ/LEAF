#include "Analyzer/include/STMETSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


STMETSelection::STMETSelection(const Config & cfg, double min_, double max_) : min(min_), max(max_){}

bool STMETSelection::passes(RecoEvent & event){

  double stmet = event.met->pt();
  for (Jet & jet : *event.jets) stmet += jet.pt();
  for (Electron & e : *event.electrons) stmet += e.pt();
  for (Muon & mu : *event.muons) stmet += mu.pt();
  for (Tau & tau : *event.taus) stmet += tau.pt();

  return(stmet >= min && (stmet < max || max == -1));
}
