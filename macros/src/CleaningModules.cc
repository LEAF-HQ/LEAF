#include "include/CleaningModules.h"
#include "include/useful_functions.h"

using namespace std;

GenJetCleaner::GenJetCleaner(const GenJetId & id_): id(id_) {}
bool GenJetCleaner::process(Event & event){
  clean_collection(event.genjets, event, id);
  return true;
}

JetCleaner::JetCleaner(const JetId & id_): id(id_) {}
bool JetCleaner::process(RecoEvent & event){
  clean_collection(event.jets, event, id);
  return true;
}

MuonCleaner::MuonCleaner(const MuonId & id_): id(id_) {}
bool MuonCleaner::process(RecoEvent & event){
  clean_collection(event.muons, event, id);
  return true;
}

ElectronCleaner::ElectronCleaner(const ElectronId & id_): id(id_) {}
bool ElectronCleaner::process(RecoEvent & event){
  clean_collection(event.electrons, event, id);
  return true;
}

TauCleaner::TauCleaner(const TauId & id_): id(id_) {}
bool TauCleaner::process(RecoEvent & event){
  clean_collection(event.taus, event, id);
  return true;
}

GenJetVisTauCleaner::GenJetVisTauCleaner(const double & mindr_): mindr(mindr_) {}
bool GenJetVisTauCleaner::process(Event & event){

  // throw away jets, that are closer than mindR to any visible tau
  vector<GenJet> cleaned_jets;
  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet gj = event.genjets->at(i);
    bool keep = true;
    for(size_t j=0; j<event.genparticles_visibletaus->size(); j++){
      GenParticle gt = event.genparticles_visibletaus->at(j);
      if(deltaR(gj, gt) < mindr){
        keep = false;
        break;
      }
    }
    if(keep) cleaned_jets.emplace_back(gj);
  }
  swap(cleaned_jets, *event.genjets);
  return true;
}

GenVisTauCleaner::GenVisTauCleaner(const GenParticleId & id_): id(id_) {}
bool GenVisTauCleaner::process(Event & event){
  clean_collection(event.genparticles_visibletaus, event, id);
  return true;
}
