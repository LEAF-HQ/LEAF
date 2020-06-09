#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "include/Event.h"
#include "include/GenHists.h"
#include "include/CleaningModules.h"
#include "include/Config.h"
#include "include/BaseTool.h"

class GenlevelTool : public BaseTool {

public:
  // Constructors, destructor
  GenlevelTool(const Config & cfg);
  ~GenlevelTool() = default;
  virtual bool Process(Event & event) override;


private:

  // Modules used in the analysis
  GenJetId      genjet_id;
  GenParticleId genvistau_id;
  double        mindr_genjet_tauvis;

  unique_ptr<GenJetCleaner>       cleaner_genjet;
  unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;







};
