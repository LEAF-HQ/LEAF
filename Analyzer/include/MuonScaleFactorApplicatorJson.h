#pragma once
#include "LEAF/Analyzer/include/ScaleFactorApplicatorJson.h"
#include "LEAF/Analyzer/include/Electron.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class MuonScaleFactorApplicatorJson: public ScaleFactorApplicatorJson {
public:
  explicit MuonScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname);
  virtual ~MuonScaleFactorApplicatorJson() = default;

  virtual bool process(RecoEvent & event) override;
  bool process_trigger(RecoEvent & event);

private:
  double m_pt_min = 15.;
  double m_abseta_max = 2.4;
  bool m_doubleunc = false;

};
