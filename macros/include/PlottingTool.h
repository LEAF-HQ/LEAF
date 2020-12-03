#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "include/Event.h"

class PlottingTool {

public:

  // Constructors, destructor
  PlottingTool(bool debug_ = false);
  PlottingTool(const PlottingTool &) = default;
  PlottingTool & operator = (const PlottingTool &) = default;
  ~PlottingTool() = default;

  // Main functions
  void Plot(bool normalize = false, bool logy = true, bool singlePDF = false);

  void set_inpath(TString s){ base_path_analysisfiles = s;};
  void set_outpath(TString s){ base_path_plots = s;};
  void set_outnameprefix(TString s){ prefix_plots = s;};
  void set_samplenames(vector<TString> s){ samples_genlevel = s;};
  void set_legends(vector<TString> s){ labels_genlevel = s;};
  void set_linecolors(vector<int> s){ linecolors_genlevel = s;};
  void set_linestyles(vector<int> s){ linestyles_genlevel = s;};
  void set_debug(bool s){ debug = s;};




private:
  TString base_path_analysisfiles, base_path_plots;
  TString prefix_plots = "";
  vector<TString> samples_genlevel, labels_genlevel;
  vector<int> linecolors_genlevel, linestyles_genlevel;
  bool debug;




};
