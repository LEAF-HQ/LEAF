#include "include/NMuonSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


NMuonSelection::NMuonSelection(const Config & cfg, int nmin_, int nmax_) : nmin(nmin_), nmax(nmax_){}
NMuonSelection::NMuonSelection(const Config & cfg, int nmin_, int nmax_, ID<Muon> id_) : nmin(nmin_), nmax(nmax_), id(id_){}

bool NMuonSelection::passes(RecoEvent & event){
  int selected = 0;
  if(id){
    for (Muon & muo : *event.muons){
      if(id(muo, event)) selected++;
    }
  }
  else selected = event.muons->size();

  return(selected >= nmin && (selected <= nmax || nmax == -1));
}
