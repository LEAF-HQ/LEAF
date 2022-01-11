#include "LEAF/Analyzer/include/LumiWeightApplicator.h"


LumiWeightApplicator::LumiWeightApplicator(const Config& cfg){
  m_targetlumi = cfg.target_lumi();
  m_datasetlumi = cfg.dataset_lumi();
}


bool LumiWeightApplicator::process(RecoEvent& event) {
  if(event.is_data) return true;

  event.weight *= m_targetlumi / m_datasetlumi;
  return true;
}
