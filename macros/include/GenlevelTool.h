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

class GenlevelTool {

public:
  // Constructors, destructor
  GenlevelTool(const Config & cfg);
  ~GenlevelTool() = default;

  // Base functions
  void SetupModules();
  void SetupHistograms();
  void LoopEvents();
  void LoopEvents(const Config & cfg);
  void WriteOutput(const Config & cfg);

  // This is called for each event, do the analysis here
  bool Process(Event & event);


private:

  // For internal use, do not touch
  std::unique_ptr<TFile> simple_file;
  int nevt;
  Event event;
  vector<string> histfolders;
  map<TString, unique_ptr<GenHists>> histmap;


  // Modules used in the analysis
  GenJetId      genjet_id;
  GenParticleId genvistau_id;
  double        mindr_genjet_tauvis;

  unique_ptr<GenJetCleaner>       cleaner_genjet;
  unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;







};
