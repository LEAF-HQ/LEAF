#include <cmath>
#include <iostream>
#include "include/PlottingTool.h"
#include "include/constants.h"
#include <TString.h>

using namespace std;

int main(){

  // Greet
  cout << "Hello from the Plotter." << endl;

  PlottingTool Plotter_Genlevel;
  Plotter_Genlevel.set_inpath("/work/areimers/LQDM/GENSIM/analysisfiles/");
  Plotter_Genlevel.set_outpath("/work/areimers/LQDM/GENSIM/plots/");
  Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0"});
  Plotter_Genlevel.set_legends({"LQLQ#rightarrow b#tau b#tau", "LQLQ#rightarrow b#tau #psi#chi_{1}", "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}", "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"});
  Plotter_Genlevel.set_linecolors({kRed+4, kRed+1, kAzure-2, kGreen-2});
  Plotter_Genlevel.set_linestyles({1, 1, 1, 1});

  //Plotter_Genlevel.Plot(normalize, logY, SinglePDF);
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  // Plotter_Genlevel.Plot(true, true, false);     // normalized
  // Plotter_Genlevel.Plot(false, false, false);   // lin Y
  // Plotter_Genlevel.Plot(true, false, false);    // lin Y normalized
  Plotter_Genlevel.Plot(false, true, true);        // SinglePDF
  // Plotter_Genlevel.Plot(true, true, true);         // SinglePDF normalized





  PlottingTool Plotter_Recolevel;
  Plotter_Recolevel.set_inpath("/work/areimers/LQDM/UL17/Preselection/");
  Plotter_Recolevel.set_outpath("/work/areimers/LQDM/UL17/Preselection/plots/");
  Plotter_Recolevel.set_samplenames({"MC__LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0"});
  Plotter_Recolevel.set_legends({"LQLQ#rightarrow b#tau b#tau", "LQLQ#rightarrow b#tau #psi#chi_{1}", "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}", "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"});
  Plotter_Recolevel.set_linecolors({kRed+4, kRed+1, kAzure-2, kGreen-2});
  Plotter_Recolevel.set_linestyles({1, 1, 1, 1});

  //Plotter_Recolevel.Plot(normalize, logY, SinglePDF);
  // Plotter_Recolevel.Plot(false, true, false);       // usual
  // Plotter_Recolevel.Plot(true, true, false);     // normalized
  // Plotter_Recolevel.Plot(false, false, false);   // lin Y
  // Plotter_Recolevel.Plot(true, false, false);    // lin Y normalized
  // Plotter_Recolevel.Plot(false, true, true);        // SinglePDF
  // Plotter_Recolevel.Plot(true, true, true);         // SinglePDF normalized








}
