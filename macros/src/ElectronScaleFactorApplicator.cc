#include "include/ElectronScaleFactorApplicator.h"

using namespace std;



bool ElectronScaleFactorApplicator::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Electron & ele : *event.electrons){
    reset();
    set_bin(ele.eta(), ele.pt());
    double sf = get_scalefactor();
    // double unc = get_uncertainty();
    event.weight *= sf;
    // cout << "scalefactor: " << sf << ", uncertainty: " << unc << endl;

  }
  return true;

}
