#include "LEAF/Analyzer/include/NElectronSelection.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


NElectronSelection::NElectronSelection(const Config & cfg, int nmin_, int nmax_) : nmin(nmin_), nmax(nmax_){}
NElectronSelection::NElectronSelection(const Config & cfg, int nmin_, int nmax_, ID<Electron> id_) : nmin(nmin_), nmax(nmax_), id(id_){}

bool NElectronSelection::passes(RecoEvent & event){
  int selected = 0;
  if(id){
    for (Electron & ele : *event.electrons){
      if(id(ele, event)) selected++;
    }
  }
  else selected = event.electrons->size();

  return(selected >= nmin && (selected <= nmax || nmax == -1));
}
