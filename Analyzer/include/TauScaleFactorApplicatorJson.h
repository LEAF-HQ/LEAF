#pragma once
#include "LEAF/Analyzer/include/ScaleFactorApplicatorJson.h"
#include "LEAF/Analyzer/include/Tau.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class TauScaleFactorApplicatorJson: public ScaleFactorApplicatorJson {
public:
  explicit TauScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname, TString wp);
  virtual ~TauScaleFactorApplicatorJson() = default;

  virtual bool process(RecoEvent & event) override;
  bool process_trigger(RecoEvent & event);

private:
  TString m_wp;
  double m_pt_min = 20.;
  double m_abseta_max = 2.3;
  bool m_doubleunc = false;

};
