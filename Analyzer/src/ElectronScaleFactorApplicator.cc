#include "Analyzer/include/ElectronScaleFactorApplicator.h"

using namespace std;



bool ElectronScaleFactorApplicator::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Electron & ele : *event.electrons){
    set_bin(ele.eta(), ele.pt());
    double sf = get_scalefactor();
    // double unc = get_uncertainty();
    event.weight *= sf;
    // cout << "scalefactor: " << sf << ", uncertainty: " << unc << endl;

  }
  return true;

}


bool ElectronScaleFactorApplicator::process_trigger(RecoEvent & event){
  if(event.is_data) return true;
  if(event.electrons->size() < 1) return true;

  set_bin(fabs(event.electrons->at(0).eta()), event.electrons->at(0).pt());
  double sf = get_scalefactor();
  // double unc = get_uncertainty();
  event.weight *= sf;
  return true;

}
