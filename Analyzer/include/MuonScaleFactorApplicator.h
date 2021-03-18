#pragma once
#include "Analyzer/include/ScaleFactorApplicator.h"
#include "Analyzer/include/Muon.h"
#include "Analyzer/include/useful_functions.h"
#include "Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class MuonScaleFactorApplicator: public ScaleFactorApplicator {
public:
  explicit MuonScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname) : ScaleFactorApplicator(cfg, year, infilename, histname) {};
  virtual ~MuonScaleFactorApplicator() = default;

  virtual bool process(RecoEvent & event) override;
  bool process_trigger(RecoEvent & event);


};
