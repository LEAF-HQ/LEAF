#include "LEAF/Analyzer/include/NTauSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


NTauSelection::NTauSelection(const Config & cfg, int nmin_, int nmax_) : nmin(nmin_), nmax(nmax_){}
NTauSelection::NTauSelection(const Config & cfg, int nmin_, int nmax_, ID<Tau> id_) : nmin(nmin_), nmax(nmax_), id(id_){}

bool NTauSelection::passes(RecoEvent & event){
  int selected = 0;
  if(id){
    for (Tau & tau : *event.taus){
      if(id(tau, event)) selected++;
    }
  }
  else selected = event.taus->size();

  return(selected >= nmin && (selected <= nmax || nmax == -1));
}
