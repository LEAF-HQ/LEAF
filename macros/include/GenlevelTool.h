#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "../include/Event.h"
#include "../include/GenHists.h"
#include "../include/CleaningModules.h"

class GenlevelTool {

public:

  // Constructors, destructor
  GenlevelTool(double MLQ_, double MX_, double MDM_, double lambda_, bool debug_ = false);
  GenlevelTool(const GenlevelTool &) = default;
  GenlevelTool & operator = (const GenlevelTool &) = default;
  ~GenlevelTool() = default;
  void SetupModules();
  void SetupHistograms();
  void LoopEvents();
  void Process(Event & event);

  // Main functions
  // void PlotVariables(bool singlePDF = false, bool normalize = false);


private:
  TString base_path_gensimtuples, base_path_crosssections, base_path_analysisfiles, base_path_out;
  // TString base_path_plots;
  double MLQ, MX, MDM, lambda;
  bool debug;
  std::unique_ptr<TFile> simple_file;
  int nevt;
  Event event;
  map<TString, unique_ptr<GenHists>> histmap;


  unique_ptr<GenJetCleaner> cleaner_genjet;
  GenJetId genjet_id;







};
