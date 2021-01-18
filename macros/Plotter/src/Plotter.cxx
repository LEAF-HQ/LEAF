#include <cmath>
#include <iostream>
#include "Plotter/include/PlottingTool.h"
#include <TString.h>

using namespace std;

int main(){

  // Greet
  // cout << "Hello from the Plotter." << endl;

  // PlottingTool Plotter_Genlevel;
  // Plotter_Genlevel.set_inpath("/work/areimers/LQDM/GENSIM/analysisfiles/");
  // Plotter_Genlevel.set_outpath("/work/areimers/LQDM/GENSIM/plots/");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToBTauPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__LQLQToPsiChi_MLQ1900_MPS475_MC1427_L1p0", "MC__PsiPsiToLQChi_MLQ1900_MPS475_MC1427_L1p0"});
  // Plotter_Genlevel.set_legends({"LQLQ#rightarrow b#tau b#tau", "LQLQ#rightarrow b#tau #psi#chi_{1}", "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}", "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"});
  // Plotter_Genlevel.set_colors({kRed+4, kRed+1, kAzure-2, kGreen-2});
  // Plotter_Genlevel.set_linestyles({1, 1, 1, 1});
  //
  // //Plotter_Genlevel.Plot(normalize, logY, SinglePDF);
  // // Plotter_Genlevel.Plot(false, true, false);       // usual
  // // Plotter_Genlevel.Plot(true, true, false);     // normalized
  // // Plotter_Genlevel.Plot(false, false, false);   // lin Y
  // // Plotter_Genlevel.Plot(true, false, false);    // lin Y normalized
  // Plotter_Genlevel.Plot(false, true, true);        // SinglePDF
  // // Plotter_Genlevel.Plot(true, true, true);         // SinglePDF normalized


  // PlottingTool Plotter_Genlevel;
  // Plotter_Genlevel.set_inpath("/work/areimers/LQDM/UL17/Genlevel/");
  // Plotter_Genlevel.set_outpath("/work/areimers/LQDM/UL17/Genlevel/plots/");
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTau_MC1214_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1000_MPS244_MC1214_L1p0", "MC__LQLQToBTau_MLQ1360_MPS244_MC1214_L1p0", "MC__LQLQToBTau_MLQ1810_MPS244_MC1214_L1p0", "MC__LQLQToBTau_MLQ2170_MPS244_MC1214_L1p0", "MC__LQLQToBTau_MLQ2620_MPS244_MC1214_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = 1.0", "M_{LQ} = 1360 GeV, #lambda = 1.0", "M_{LQ} = 1810 GeV, #lambda = 1.0", "M_{LQ} = 2170 GeV, #lambda = 1.0", "M_{LQ} = 2620 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.set_colors({kRed+4, kRed+1, kAzure-2, kOrange, kGreen-2});
  // Plotter_Genlevel.set_linestyles({1, 1, 1, 1, 1});
  // //Plotter_Genlevel.Plot(normalize, logY, SinglePDF);
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  // // Plotter_Genlevel.Plot(true, true, false);     // normalized
  // // Plotter_Genlevel.Plot(false, false, false);   // lin Y
  // // Plotter_Genlevel.Plot(true, false, false);    // lin Y normalized
  // Plotter_Genlevel.Plot(false, true, true);        // SinglePDF
  // // Plotter_Genlevel.Plot(true, true, true);         // SinglePDF normalized
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTau_MC1214_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1000_MPS244_MC1214_Lbest", "MC__LQLQToBTau_MLQ1360_MPS244_MC1214_Lbest", "MC__LQLQToBTau_MLQ1810_MPS244_MC1214_Lbest", "MC__LQLQToBTau_MLQ2170_MPS244_MC1214_Lbest", "MC__LQLQToBTau_MLQ2620_MPS244_MC1214_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = best", "M_{LQ} = 1360 GeV, #lambda = best", "M_{LQ} = 1810 GeV, #lambda = best", "M_{LQ} = 2170 GeV, #lambda = best", "M_{LQ} = 2620 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTau_MC110233_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1000_MPS11493_MC110233_L1p0", "MC__LQLQToBTau_MLQ1360_MPS11488_MC110233_L1p0", "MC__LQLQToBTau_MLQ1810_MPS11554_MC110233_L1p0", "MC__LQLQToBTau_MLQ2170_MPS11635_MC110233_L1p0", "MC__LQLQToBTau_MLQ2620_MPS11813_MC110233_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = 1.0", "M_{LQ} = 1360 GeV, #lambda = 1.0", "M_{LQ} = 1810 GeV, #lambda = 1.0", "M_{LQ} = 2170 GeV, #lambda = 1.0", "M_{LQ} = 2620 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.Plot(false, true, false);
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTau_MC110233_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTau_MLQ1000_MPS11493_MC110233_Lbest", "MC__LQLQToBTau_MLQ1360_MPS11488_MC110233_Lbest", "MC__LQLQToBTau_MLQ1810_MPS11554_MC110233_Lbest", "MC__LQLQToBTau_MLQ2170_MPS11635_MC110233_Lbest", "MC__LQLQToBTau_MLQ2620_MPS11813_MC110233_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = best", "M_{LQ} = 1360 GeV, #lambda = best", "M_{LQ} = 1810 GeV, #lambda = best", "M_{LQ} = 2170 GeV, #lambda = best", "M_{LQ} = 2620 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);
  //
  //
  //
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTauPsiChi_MC1214_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTauPsiChi_MLQ1000_MPS244_MC1214_L1p0", "MC__LQLQToBTauPsiChi_MLQ1360_MPS244_MC1214_L1p0", "MC__LQLQToBTauPsiChi_MLQ1810_MPS244_MC1214_L1p0", "MC__LQLQToBTauPsiChi_MLQ2170_MPS244_MC1214_L1p0", "MC__LQLQToBTauPsiChi_MLQ2620_MPS244_MC1214_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = 1.0", "M_{LQ} = 1360 GeV, #lambda = 1.0", "M_{LQ} = 1810 GeV, #lambda = 1.0", "M_{LQ} = 2170 GeV, #lambda = 1.0", "M_{LQ} = 2620 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToBTauPsiChi_MC1214_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToBTauPsiChi_MLQ1000_MPS244_MC1214_Lbest", "MC__LQLQToBTauPsiChi_MLQ1360_MPS244_MC1214_Lbest", "MC__LQLQToBTauPsiChi_MLQ1810_MPS244_MC1214_Lbest", "MC__LQLQToBTauPsiChi_MLQ2170_MPS244_MC1214_Lbest", "MC__LQLQToBTauPsiChi_MLQ2620_MPS244_MC1214_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = best", "M_{LQ} = 1360 GeV, #lambda = best", "M_{LQ} = 1810 GeV, #lambda = best", "M_{LQ} = 2170 GeV, #lambda = best", "M_{LQ} = 2620 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToPsiChi_MC1214_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToPsiChi_MLQ1000_MPS244_MC1214_L1p0", "MC__LQLQToPsiChi_MLQ1360_MPS244_MC1214_L1p0", "MC__LQLQToPsiChi_MLQ1810_MPS244_MC1214_L1p0", "MC__LQLQToPsiChi_MLQ2170_MPS244_MC1214_L1p0", "MC__LQLQToPsiChi_MLQ2620_MPS244_MC1214_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = 1.0", "M_{LQ} = 1360 GeV, #lambda = 1.0", "M_{LQ} = 1810 GeV, #lambda = 1.0", "M_{LQ} = 2170 GeV, #lambda = 1.0", "M_{LQ} = 2620 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("LQLQToPsiChi_MC1214_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__LQLQToPsiChi_MLQ1000_MPS244_MC1214_Lbest", "MC__LQLQToPsiChi_MLQ1360_MPS244_MC1214_Lbest", "MC__LQLQToPsiChi_MLQ1810_MPS244_MC1214_Lbest", "MC__LQLQToPsiChi_MLQ2170_MPS244_MC1214_Lbest", "MC__LQLQToPsiChi_MLQ2620_MPS244_MC1214_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{LQ} = 1000 GeV, #lambda = best", "M_{LQ} = 1360 GeV, #lambda = best", "M_{LQ} = 1810 GeV, #lambda = best", "M_{LQ} = 2170 GeV, #lambda = best", "M_{LQ} = 2620 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  //
  //
  // Plotter_Genlevel.set_outnameprefix("PsiPsiToLQChi_MLQ1000_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{#psi} = 117 GeV, #lambda = 1.0", "M_{#psi} = 244 GeV, #lambda = 1.0", "M_{#psi} = 567 GeV, #lambda = 1.0", "M_{#psi} = 1051 GeV, #lambda = 1.0", "M_{#psi} = 2221 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("PsiPsiToLQChi_MLQ1000_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_Lbest", "MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_Lbest", "MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_Lbest", "MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_Lbest", "MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{#psi} = 117 GeV, #lambda = best", "M_{#psi} = 244 GeV, #lambda = best", "M_{#psi} = 567 GeV, #lambda = best", "M_{#psi} = 1051 GeV, #lambda = best", "M_{#psi} = 2221 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("PsiPsiToLQChi_MLQ10000_L1p0_");
  // Plotter_Genlevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ10000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ10000_MPS244_MC1214_L1p0", "MC__PsiPsiToLQChi_MLQ10000_MPS504_MC1457_L1p0", "MC__PsiPsiToLQChi_MLQ10000_MPS1052_MC1977_L1p0", "MC__PsiPsiToLQChi_MLQ10000_MPS2342_MC12089_L1p0"});
  // Plotter_Genlevel.set_legends({"M_{#psi} = 117 GeV, #lambda = 1.0", "M_{#psi} = 244 GeV, #lambda = 1.0", "M_{#psi} = 504 GeV, #lambda = 1.0", "M_{#psi} = 1052 GeV, #lambda = 1.0", "M_{#psi} = 2342 GeV, #lambda = 1.0"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual
  //
  // Plotter_Genlevel.set_outnameprefix("PsiPsiToLQChi_MLQ10000_Lbest_");
  // Plotter_Genlevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ10000_MPS117_MC1100_Lbest", "MC__PsiPsiToLQChi_MLQ10000_MPS244_MC1214_Lbest", "MC__PsiPsiToLQChi_MLQ10000_MPS504_MC1457_Lbest", "MC__PsiPsiToLQChi_MLQ10000_MPS1052_MC1977_Lbest", "MC__PsiPsiToLQChi_MLQ10000_MPS2342_MC12089_Lbest"});
  // Plotter_Genlevel.set_legends({"M_{#psi} = 117 GeV, #lambda = best", "M_{#psi} = 244 GeV, #lambda = best", "M_{#psi} = 504 GeV, #lambda = best", "M_{#psi} = 1052 GeV, #lambda = best", "M_{#psi} = 2342 GeV, #lambda = best"});
  // Plotter_Genlevel.Plot(false, true, false);       // usual

  map<TString, TString> legends {
    make_pair("DATA__DATA_Tau",                                  "Data"),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau"),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", "LQLQ#rightarrow b#tau #psi#chi_{1}"),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"),
    make_pair("MC__TT",                                          "t#bar{t}"),
    make_pair("MC__ST",                                          "Single t"),
    make_pair("MC__DYJetsToLL",                                  "DY #rightarrow ll"),
    make_pair("MC__WJetsToLNu",                                  "W+jets #rightarrow l#nu")
  };

  map<TString, int> colors {
    make_pair("DATA__DATA_Tau",                                  kBlack),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", kBlack),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    kBlack),
    make_pair("MC__TT",                                          kOrange+10),
    make_pair("MC__ST",                                          kAzure-2), // kMagenta-3
    make_pair("MC__DYJetsToLL",                                  kOrange-2),
    make_pair("MC__WJetsToLNu",                                  kSpring-6)
  };

  map<TString, int> linestyles {
    make_pair("DATA__DATA_Tau",                                  0),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       1),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", 2),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     3),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    4),
    make_pair("MC__TT",                                          0),
    make_pair("MC__ST",                                          0),
    make_pair("MC__DYJetsToLL",                                  0),
    make_pair("MC__WJetsToLNu",                                  0)
  };



  PlottingTool Plotter_Recolevel;
  Plotter_Recolevel.set_inpath("/pnfs/psi.ch/cms/trivcat/store/user/areimers/LQDM/UL17/Preselection/Initial/");
  Plotter_Recolevel.set_outpath("/work/areimers/LQDM/UL17/Preselection/Initial/plots/");
  Plotter_Recolevel.set_samplenames({"DATA__DATA_Tau", "MC__ST", "MC__TT", "MC__DYJetsToLL", "MC__WJetsToLNu", "MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0", "MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", "MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0"});
  Plotter_Recolevel.set_legends(legends);
  Plotter_Recolevel.set_colors(colors);
  Plotter_Recolevel.set_linestyles(linestyles);
  Plotter_Recolevel.set_stacks({"MC__ST", "MC__DYJetsToLL", "MC__TT", "MC__WJetsToLNu"});

  // Plotter_Recolevel.Plot(normalize, logY, SinglePDF);
  Plotter_Recolevel.Plot(false, true, false);       // usual
  // Plotter_Recolevel.Plot(false, true, true);        // SinglePDF








}
