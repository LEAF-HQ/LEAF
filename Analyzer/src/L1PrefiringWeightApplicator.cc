#include "LEAF/Analyzer/include/L1PrefiringWeightApplicator.h"


L1PrefiringWeightApplicator::L1PrefiringWeightApplicator(){}

bool L1PrefiringWeightApplicator::process(RecoEvent& event) {
  if(event.is_data) return true;

  event.weight *= event.weight_prefiring;
  return true;
}
