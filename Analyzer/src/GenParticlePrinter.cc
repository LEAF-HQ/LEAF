#include "LEAF/Analyzer/include/GenParticlePrinter.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


GenParticlePrinter::GenParticlePrinter(const Config & cfg){}

bool GenParticlePrinter::process(RecoEvent & event){
  if(event.is_data) return false;

  cout << "     +=====================+" << endl;
  cout << "     |     GenParticles    |" << endl;
  cout << "     +=====================+" << endl << endl;

  cout << "Number, Identifier, pdgId, mother, pt, eta" << endl;
  cout << "------------------------------------------" << endl;

  for(size_t i=0; i<event.genparticles_all->size(); i++){
    int correct_idx = -1;
    for(size_t j=0; j<event.genparticles_all->size(); j++){
      if(event.genparticles_all->at(j).identifier() == (int)i){
        correct_idx = j;
        break;
      }
    }
    GenParticle gp = event.genparticles_all->at(correct_idx);

    // now find mother using the identifier again
    int motherpdgid = -1;
    for(size_t j=0; j<event.genparticles_all->size(); j++){
      if(event.genparticles_all->at(j).identifier() == gp.mother_identifier()){
        motherpdgid = event.genparticles_all->at(j).pdgid();
        break;
      }
    }

    // if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;
    if(abs(gp.pdgid()) > 30) continue;
    cout << i << "  ,  " << gp.identifier() << "  ,  " << gp.pdgid() << "  ,  " << gp.mother_identifier() << " (pdgid: " << motherpdgid << ") ,  " << gp.pt() << "  ,  " << gp.eta() << endl;
  }
  cout << endl << endl << endl << endl;
  return true;

}
