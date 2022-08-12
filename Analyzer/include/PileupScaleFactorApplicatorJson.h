#pragma once
#include "LEAF/Analyzer/include/ScaleFactorApplicatorJson.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class PileupScaleFactorApplicatorJson: public ScaleFactorApplicatorJson {
public:
  explicit PileupScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname);
  virtual ~PileupScaleFactorApplicatorJson() = default;

  virtual bool process(RecoEvent & event) override;

private:
  bool m_doubleunc = false;

};
