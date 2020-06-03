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

class GenlevelTool {

public:
  // Constructors, destructor
  GenlevelTool(double MLQ_, double MX_, double MDM_, double lambda_, bool debug_ = false);
  GenlevelTool(const GenlevelTool &) = default;
  GenlevelTool & operator = (const GenlevelTool &) = default;
  ~GenlevelTool() = default;

  // Base functions
  void SetupModules();
  void SetupHistograms();
  void LoopEvents();

  // This is called for each event, do the analysis here
  bool Process(Event & event);


private:

  // For internal use, do not touch
  TString base_path_gensimtuples, base_path_crosssections, base_path_analysisfiles, base_path_out;
  double MLQ, MX, MDM, lambda;
  bool debug;
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
