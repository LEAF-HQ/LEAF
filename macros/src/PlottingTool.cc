#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/PlottingTool.h"
#include "include/useful_functions.h"

using namespace std;

PlottingTool::PlottingTool(bool debug_) : debug(debug_){

  base_path_analysisfiles = "/work/areimers/LQDM/GENSIM/analysisfiles/";
  base_path_plots         = "/work/areimers/LQDM/GENSIM/plots/";
  samples_genlevel        = {"MC__LQDM_MLQ700_MX275_MDM250_L1p0", "MC__LQDM_MLQ1000_MX440_MDM400_L1p0", "MC__LQDM_MLQ1300_MX605_MDM550_L1p0", "MC__LQDM_MLQ1600_MX770_MDM700_L1p0", "MC__LQDM_MLQ1900_MX935_MDM850_L1p0"};
  labels_genlevel         = {"M_{LQ} = 700 GeV", "M_{LQ} = 1000 GeV", "M_{LQ} = 1300 GeV", "M_{LQ} = 1600 GeV", "M_{LQ} = 1900 GeV"};
  linecolors_genlevel     = {kRed+4, kRed+1, kAzure-2, kGreen-2, kOrange};
  linestyles_genlevel     = {1, 1, 1, 1, 1};
}
