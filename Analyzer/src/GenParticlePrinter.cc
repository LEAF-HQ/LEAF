#include "LEAF/Analyzer/include/GenParticlePrinter.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


GenParticlePrinter::GenParticlePrinter(const Config & cfg,bool do_allgenparticles_): do_allgenparticles(do_allgenparticles_) {}

bool GenParticlePrinter::process(RecoEvent & event){
  if(event.is_data) return false;

  if (do_allgenparticles) genparticles = event.genparticles_stable;
  else genparticles = event.genparticles_pruned;

  cout << "     +=====================+" << endl;
  cout << "     |     GenParticles    |" << endl;
  cout << "     +=====================+" << endl << endl;

  cout << "Number, Identifier, pdgId, mother, pt, eta" << endl;
  cout << "------------------------------------------" << endl;

  for(size_t i=0; i<genparticles->size(); i++){
    int correct_idx = -1;
    for(size_t j=0; j<genparticles->size(); j++){
      if(genparticles->at(j).identifier() == (int)i){
        correct_idx = j;
        break;
      }
    }
    GenParticle gp = genparticles->at(correct_idx);

    // now find mother using the identifier again
    int motherpdgid = -1;
    for(size_t j=0; j<genparticles->size(); j++){
      if(genparticles->at(j).identifier() == gp.mother_identifier()){
        motherpdgid = genparticles->at(j).pdgid();
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
