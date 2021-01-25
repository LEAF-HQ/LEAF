#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

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
  void set_samplenames(std::vector<TString> s){ samples = s;};
  void set_legends(std::map<TString, TString> s){ labels = s;};
  void set_colors(std::map<TString, int> s){ colors = s;};
  void set_linestyles(std::map<TString, int> s){ linestyles = s;};
  void set_stacks(std::vector<TString> s){ stacks = s;};
  void set_numerator(TString s){ numerator = s;};
  void set_debug(bool s){ debug = s;};




private:
  TString base_path_analysisfiles, base_path_plots;
  TString prefix_plots = "";
  TString numerator = "";
  std::vector<TString> samples, stacks;
  std::map<TString, TString> labels;
  std::map<TString, int> colors, linestyles;
  bool debug;




};
