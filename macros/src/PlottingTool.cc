#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/PlottingTool.h"
#include "include/useful_functions.h"

using namespace std;

PlottingTool::PlottingTool(bool debug_) : debug(debug_){

  // base_path_analysisfiles = "/work/areimers/LQDM/GENSIM/analysisfiles/";
  // base_path_plots         = "/work/areimers/LQDM/GENSIM/plots/";
  // samples_genlevel        = {"MC__LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0"};
  // labels_genlevel         = {"LQLQ#rightarrow b#tau b#tau", "LQLQ#rightarrow b#tau #psi#chi_{1}", "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}", "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"};
  // linecolors_genlevel     = {kRed+4, kRed+1, kAzure-2, kGreen-2};
  // linestyles_genlevel     = {1, 1, 1, 1};

  // linecolors_genlevel     = {kRed+4, kRed+1, kAzure-2, kGreen-2, kOrange};
  // linestyles_genlevel     = {1, 1, 1, 1, 1};
}
