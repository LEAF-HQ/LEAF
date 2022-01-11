#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class ScaleFactorApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit ScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname);
  virtual ~ScaleFactorApplicator() = default;

  // virtual bool process(RecoEvent & event){};
  void load_histogram(TString year, TString infilename, TString histname);
  void reset();
  int find_bin(double val, TAxis* axis);
  void set_bin(double val);
  void set_bin(double valx, double valy);
  double get_scalefactor();
  double get_uncertainty();

protected:

  unique_ptr<TFile> m_infile;
  unique_ptr<TH1D> m_hist_1d;
  unique_ptr<TH2D> m_hist_2d;

  bool m_is_2d;
  double m_factor_uncertainty;
  int m_bin_x;
  int m_bin_y;

};
