#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>
#include "LEAF/Analyzer/correctionlib_python2/correctionlib/include/correction.h"


class ScaleFactorApplicatorJson: public AnalysisModule<RecoEvent> {
public:
  explicit ScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname);
  virtual ~ScaleFactorApplicatorJson() = default;

protected:

  TString m_year, m_sfname;
  correction::Correction::Ref m_correction;

};
