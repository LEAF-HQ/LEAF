#pragma once
#include "Analyzer/include/ScaleFactorApplicator.h"
#include "Analyzer/include/Electron.h"
#include "Analyzer/include/useful_functions.h"
#include "Analyzer/include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class ElectronScaleFactorApplicator: public ScaleFactorApplicator {
public:
  explicit ElectronScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname) : ScaleFactorApplicator(cfg, year, infilename, histname) {};
  virtual ~ElectronScaleFactorApplicator() = default;

  virtual bool process(RecoEvent & event) override;
  bool process_trigger(RecoEvent & event);


};
