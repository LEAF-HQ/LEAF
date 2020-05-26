#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "../include/PlottingTool.h"
#include "../include/useful_functions.h"

using namespace std;

PlottingTool::PlottingTool(bool debug_) : debug(debug_){

  base_path_analysisfiles = "/work/areimers/LQDM/GENSIM/analysisfiles/";
  base_path_plots         = "/work/areimers/LQDM/GENSIM/plots/";
  // samples_genlevel        = {"LQDM_MLQ600_MX220_MDM200_L1p0", "LQDM_MLQ900_MX385_MDM350_L1p0", "LQDM_MLQ1200_MX550_MDM500_L1p0", "LQDM_MLQ1600_MX770_MDM600_L1p0", "LQDM_MLQ2000_MX990_MDM900_L1p0"};
  samples_genlevel        = {"LQDM_MLQ700_MX275_MDM250_L1p0", "LQDM_MLQ1000_MX440_MDM400_L1p0", "LQDM_MLQ1300_MX605_MDM550_L1p0", "LQDM_MLQ1600_MX770_MDM700_L1p0", "LQDM_MLQ1900_MX935_MDM850_L1p0"};
  // labels_genlevel         = {"M_{LQ} = 600 GeV, M_{DM} = 200 GeV", "M_{LQ} = 900 GeV, M_{DM} = 350 GeV", "M_{LQ} = 1200 GeV, M_{DM} = 500 GeV", "M_{LQ} = 1600 GeV, M_{DM} = 600 GeV", "M_{LQ} = 2000 GeV, M_{DM} = 900 GeV"};
  labels_genlevel         = {"M_{LQ} = 700 GeV", "M_{LQ} = 1000 GeV", "M_{LQ} = 1300 GeV", "M_{LQ} = 1600 GeV", "M_{LQ} = 1900 GeV"};
  linecolors_genlevel     = {kRed+4, kRed+1, kAzure-2, kGreen-2, kOrange};
  linestyles_genlevel     = {1, 1, 1, 1, 1};
}
