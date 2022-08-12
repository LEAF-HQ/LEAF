#include "LEAF/Analyzer/include/TauScaleFactorApplicatorJson.h"

using namespace std;

TauScaleFactorApplicatorJson::TauScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname, TString wp) : ScaleFactorApplicatorJson(cfg, year, infilename, sfname), m_wp(wp) {};

bool TauScaleFactorApplicatorJson::process(RecoEvent & event){
  if(event.is_data) return true;

  for(Tau & tau : *event.taus){
    double abseta = fabs(tau.eta());
    if(abseta > m_abseta_max){
      abseta = m_abseta_max;
      m_doubleunc = true;
    }

    double pt = tau.pt();
    if(pt < m_pt_min){
      pt = m_pt_min;
      m_doubleunc = true;
    }

    int genmatch = tau.gen_part_flav();
    if(genmatch < 0) genmatch = 0;


    double sf = 1.;
    if(m_sfname == "DeepTau2017v2p1VSjet") sf = m_correction->evaluate({pt, tau.decay_mode(), genmatch, m_wp.Data(), "nom", "pt"});
    else if(m_sfname == "DeepTau2017v2p1VSe" || m_sfname == "DeepTau2017v2p1VSmu") sf = m_correction->evaluate({abseta, genmatch, m_wp.Data(), "nom"});
    else throw runtime_error("In TauScaleFactorApplicatorJson::process(): unsupported sfname used.");
    event.weight *= sf;

  }

  return true;
}
