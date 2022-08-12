#pragma once
#include "LEAF/Analyzer/include/ScaleFactorApplicatorJson.h"
#include "LEAF/Analyzer/include/Electron.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class ElectronScaleFactorApplicatorJson: public ScaleFactorApplicatorJson {
public:
  explicit ElectronScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname, TString wp);
  virtual ~ElectronScaleFactorApplicatorJson() = default;

  virtual bool process(RecoEvent & event) override;
  // bool process_trigger(RecoEvent & event);

private:
  TString m_wp;
  double m_pt_min = 10.;
  bool m_doubleunc = false;

};
