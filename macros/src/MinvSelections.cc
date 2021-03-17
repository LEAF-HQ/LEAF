#include "include/MinvSelections.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


MemuSelection::MemuSelection(const Config & cfg, int mmin_, int mmax_) : mmin(mmin_), mmax(mmax_){}

bool MemuSelection::passes(RecoEvent & event){

  bool pass = false;

  //select events where at least one combination of e and mu fulfills the selection
  for(size_t i=0; i<event.muons->size(); i++){
    for(size_t j=0; j<event.electrons->size(); j++){
      double m = (event.muons->at(i).p4() + event.electrons->at(j).p4()).M();
      if ( m >= mmin && (m <= mmax || mmax < 0)) pass = true;
    }
  }

  return pass;
}


MetauSelection::MetauSelection(const Config & cfg, int mmin_, int mmax_) : mmin(mmin_), mmax(mmax_){}
bool MetauSelection::passes(RecoEvent & event){

  bool pass = false;

  //select events where at least one combination of e and mu fulfills the selection
  for(size_t i=0; i<event.taus->size(); i++){
    for(size_t j=0; j<event.electrons->size(); j++){
      double m = (event.taus->at(i).p4() + event.electrons->at(j).p4()).M();
      if ( m >= mmin && (m <= mmax || mmax < 0)) pass = true;
    }
  }

  return pass;
}


MmutauSelection::MmutauSelection(const Config & cfg, int mmin_, int mmax_) : mmin(mmin_), mmax(mmax_){}
bool MmutauSelection::passes(RecoEvent & event){

  bool pass = false;

  //select events where at least one combination of e and mu fulfills the selection
  for(size_t i=0; i<event.taus->size(); i++){
    for(size_t j=0; j<event.muons->size(); j++){
      double m = (event.taus->at(i).p4() + event.muons->at(j).p4()).M();
      if ( m >= mmin && (m <= mmax || mmax < 0)) pass = true;
    }
  }

  return pass;
}


MtautauSelection::MtautauSelection(const Config & cfg, int mmin_, int mmax_) : mmin(mmin_), mmax(mmax_){}
bool MtautauSelection::passes(RecoEvent & event){

  bool pass = false;

  //select events where at least one combination of e and mu fulfills the selection
  for(size_t i=0; i<event.taus->size(); i++){
    for(size_t j=0; j<event.taus->size(); j++){
      if(j <= i) continue;
      double m = (event.taus->at(i).p4() + event.taus->at(j).p4()).M();
      if ( m >= mmin && (m <= mmax || mmax < 0)) pass = true;
    }
  }

  return pass;
}
