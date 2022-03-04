#include "LEAF/Analyzer/include/NJetSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


NJetSelection::NJetSelection(const Config & cfg, int nmin_, int nmax_) : nmin(nmin_), nmax(nmax_){}
NJetSelection::NJetSelection(const Config & cfg, int nmin_, int nmax_, ID<Jet> id_) : nmin(nmin_), nmax(nmax_), id(id_){}

bool NJetSelection::passes(RecoEvent & event){
  int selected = 0;
  if(id){
    for (Jet & jet : *event.jets_ak4chs){
      if(id(jet, event)) selected++;
    }
  }
  else selected = event.jets_ak4chs->size();

  return(selected >= nmin && (selected <= nmax || nmax == -1));
}
