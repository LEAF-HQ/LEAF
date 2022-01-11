#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "LEAF/Plotter/include/PlottingTool.h"
#include "LEAF/Plotter/include/PlotterConfig.h"
#include "LEAF/Analyzer/include/useful_functions.h"

using namespace std;

PlottingTool::PlottingTool(const PlotterConfig cfg, bool debug_) : debug(debug_){

  std::vector<TString> samples, stacks;
  std::map<TString, TString> labels;
  std::map<TString, int> colors, linestyles;

  base_path_analysisfiles = cfg.input_directory();
  base_path_plots         = cfg.output_directory();
  prefix_plots            = cfg.prefix();
  lumitext                = cfg.lumitext();
  numerator               = cfg.numerator();
  datasets                = cfg.datasets();

  blind = cfg.blind();
  logY = cfg.logY();
  normalize = cfg.normalize();
  singlePDF = cfg.singlePDF();

}
