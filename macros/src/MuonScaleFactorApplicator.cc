#include "include/MuonScaleFactorApplicator.h"

using namespace std;



bool MuonScaleFactorApplicator::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Muon & mu : *event.muons){
    reset();
    set_bin(fabs(mu.eta()), mu.pt());
    double sf = get_scalefactor();
    // double unc = get_uncertainty();
    event.weight *= sf;
    // cout << "scalefactor: " << sf << ", uncertainty: " << unc << endl;

  }
  return true;

}
