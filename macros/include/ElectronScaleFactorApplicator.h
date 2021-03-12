#pragma once
#include "include/ScaleFactorApplicator.h"
#include "include/Electron.h"
#include "include/useful_functions.h"
#include "include/constants.h"
#include <TH1D.h>
#include <TH2D.h>


class ElectronScaleFactorApplicator: public ScaleFactorApplicator {
public:
  explicit ElectronScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname) : ScaleFactorApplicator(cfg, year, infilename, histname) {};
  virtual ~ElectronScaleFactorApplicator() = default;

  virtual bool process(RecoEvent & event) override;
  bool process_trigger(RecoEvent & event);


};
