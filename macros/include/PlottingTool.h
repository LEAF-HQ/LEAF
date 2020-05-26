#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "../include/Event.h"
#include "../include/GenHists.h"

class PlottingTool {

public:

  // Constructors, destructor
  PlottingTool(bool debug_ = false);
  PlottingTool(const PlottingTool &) = default;
  PlottingTool & operator = (const PlottingTool &) = default;
  ~PlottingTool() = default;

  // Main functions
  void PlotGenlevel(bool normalize = false, bool logy = true, bool singlePDF = false);


private:
  TString base_path_analysisfiles, base_path_plots;
  vector<TString> samples_genlevel, labels_genlevel;
  vector<int> linecolors_genlevel, linestyles_genlevel;
  bool debug;




};
