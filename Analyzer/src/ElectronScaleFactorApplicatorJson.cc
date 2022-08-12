#include "LEAF/Analyzer/include/ElectronScaleFactorApplicatorJson.h"

using namespace std;

ElectronScaleFactorApplicatorJson::ElectronScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname, TString wp) : ScaleFactorApplicatorJson(cfg, year, infilename, sfname), m_wp(wp) {

  if(m_year.Contains("_UL")) m_year.ReplaceAll("_UL", "");

};

bool ElectronScaleFactorApplicatorJson::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Electron & ele : *event.electrons){
    double eta = ele.eta();
    double pt = ele.pt();
    if(pt < m_pt_min){
      pt = m_pt_min;
      m_doubleunc = true;
    }

    TString wp_to_apply = m_wp;
    if(wp_to_apply == "reco"){
      if(pt < 20) wp_to_apply = "RecoBelow20";
      else        wp_to_apply = "RecoAbove20";
    }
    
    double sf = m_correction->evaluate({m_year.Data(), "sf", wp_to_apply.Data(), eta, pt});
    event.weight *= sf;
  }

  return true;
}
