#include "Analyzer/include/MuonScaleFactorApplicator.h"

using namespace std;



bool MuonScaleFactorApplicator::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Muon & mu : *event.muons){
    set_bin(fabs(mu.eta()), mu.pt());
    double sf = get_scalefactor();
    // double unc = get_uncertainty();
    event.weight *= sf;
    // cout << "scalefactor: " << sf << ", uncertainty: " << unc << endl;

  }
  return true;

}


bool MuonScaleFactorApplicator::process_trigger(RecoEvent & event){
  if(event.is_data) return true;
  if(event.muons->size() < 1) return true;

  set_bin(event.muons->at(0).pt(), fabs(event.muons->at(0).eta()));
  double sf = get_scalefactor();
  // double unc = get_uncertainty();
  event.weight *= sf;
  return true;

}
