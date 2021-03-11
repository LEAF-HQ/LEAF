#pragma once
#include "include/AnalysisModule.h"
#include "include/Config.h"
#include "include/useful_functions.h"
#include "include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class ScaleFactorApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit ScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname);
  virtual ~ScaleFactorApplicator() = default;

  virtual bool process(RecoEvent & event){};
  void load_histogram(TString year, TString infilename, TString histname);
  // void find_bin_x(double val);
  // void find_bin_y(double val);
  int find_bin(double val, TAxis* axis);

protected:

  unique_ptr<TFile> m_infile;
  unique_ptr<TH1D> m_hist_1d;
  unique_ptr<TH2D> m_hist_2d;
  bool m_is_2d;
  double m_factor_uncertainty = 1.;
  int m_bin_x = -1;
  int m_bin_y = -1;

};
