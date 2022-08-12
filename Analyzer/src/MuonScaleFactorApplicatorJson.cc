#include "LEAF/Analyzer/include/MuonScaleFactorApplicatorJson.h"

using namespace std;

MuonScaleFactorApplicatorJson::MuonScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname) : ScaleFactorApplicatorJson(cfg, year, infilename, sfname) {};

bool MuonScaleFactorApplicatorJson::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Muon & mu : *event.muons){
    double abseta = fabs(mu.eta());
    if(abseta > m_abseta_max){
      abseta = m_abseta_max;
      m_doubleunc = true;
    }

    double pt = mu.pt();
    if(pt < m_pt_min){
      pt = m_pt_min;
      m_doubleunc = true;
    }

    double sf = m_correction->evaluate({m_year.Data(), abseta, pt, "sf"});
    event.weight *= sf;

  }
  
  return true;
}
