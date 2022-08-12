#include "LEAF/Analyzer/include/PileupScaleFactorApplicatorJson.h"

using namespace std;

PileupScaleFactorApplicatorJson::PileupScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname) : ScaleFactorApplicatorJson(cfg, year, infilename, sfname) {};

bool PileupScaleFactorApplicatorJson::process(RecoEvent & event){
  if(event.is_data) return true;

  float n = event.ntrueint;

  double sf = m_correction->evaluate({n, "nominal"});
  event.weight *= sf;

  return true;
}
