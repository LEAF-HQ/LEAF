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
    make_pair("DATA__DATA_Tau",                                  "Data (#tau)"),
    make_pair("DATA__DATA_SingleMuon",                           "Data (#mu)"),
    make_pair("DATA__DATA_SingleElectron",                       "Data (e)"),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau"),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", "LQLQ#rightarrow b#tau #psi#chi_{1}"),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1}"),
    make_pair("MC__QCD_Had",                                     "QCD"),
    make_pair("MC__TT",                                          "t#bar{t}"),
    make_pair("MC__ST",                                          "Single t"),
    make_pair("MC__DYJets",                                      "DY #rightarrow ll"),
    make_pair("MC__WJets",                                       "W+jets #rightarrow l#nu")
  };

  map<TString, int> colors {
    make_pair("DATA__DATA_Tau",                                  kBlack),
    make_pair("DATA__DATA_SingleMuon",                           kBlack),
    make_pair("DATA__DATA_SingleElectron",                       kBlack),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", kBlack),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    kBlack),
    make_pair("MC__QCD_Had",                                     kCyan-3),
    make_pair("MC__TT",                                          kOrange+10),
    make_pair("MC__ST",                                          kAzure-2), // kMagenta-3
    make_pair("MC__DYJets",                                      kOrange-2),
    make_pair("MC__WJets",                                       kSpring-6)
  };

  map<TString, int> linestyles {
    make_pair("DATA__DATA_Tau",                                  0),
    make_pair("DATA__DATA_SingleMuon",                           0),
    make_pair("DATA__DATA_SingleElectron",                       0),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       1),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", 2),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     3),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    4),
    make_pair("MC__QCD_Had",                                     0),
    make_pair("MC__TT",                                          0),
    make_pair("MC__ST",                                          0),
    make_pair("MC__DYJets",                                      0),
    make_pair("MC__WJets",                                       0)
  };



  PlottingTool Plotter_Recolevel;
  // Plotter_Recolevel.set_inpath("/pnfs/psi.ch/cms/trivcat/store/user/areimers/LQDM/UL17/Preselection/EleMuJet/");
  // Plotter_Recolevel.set_outpath("/work/areimers/LQDM/UL17/Preselection/EleMuJet/plots/");
  Plotter_Recolevel.set_inpath("/pnfs/psi.ch/cms/trivcat/store/user/areimers/LQDM/UL17/Fullselection/ElTau_MuTau_ElMu/");
  Plotter_Recolevel.set_outpath("/work/areimers/LQDM/UL17/Fullselection/ElTau_MuTau_ElMu/");
  Plotter_Recolevel.set_samplenames({"DATA__DATA_SingleMuon", "MC__ST", "MC__QCD_Had", "MC__TT", "MC__DYJets", "MC__WJets", "MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0", "MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", "MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0"});
  Plotter_Recolevel.set_legends(legends);
  Plotter_Recolevel.set_colors(colors);
  Plotter_Recolevel.set_linestyles(linestyles);
  Plotter_Recolevel.set_stacks({"MC__ST", "MC__QCD_Had", "MC__DYJets", "MC__TT", "MC__WJets"});
  Plotter_Recolevel.set_numerator("DATA__DATA_SingleMuon");

  // Plotter_Recolevel.Plot(normalize, logY, SinglePDF);
  Plotter_Recolevel.Plot(false, true, false);       // usual
  // Plotter_Recolevel.Plot(false, true, true);        // SinglePDF



  // Plotter_Recolevel.set_outnameprefix("LQLQToBTau_MC1100_Lbest_");
  // Plotter_Recolevel.set_samplenames({"MC__LQLQToBTau_MLQ1000_MPS117_MC1100_Lbest", "MC__LQLQToBTau_MLQ1360_MPS117_MC1100_Lbest", "MC__LQLQToBTau_MLQ1810_MPS117_MC1100_Lbest", "MC__LQLQToBTau_MLQ2170_MPS117_MC1100_Lbest", "MC__LQLQToBTau_MLQ2620_MPS117_MC1100_Lbest"});
  // Plotter_Recolevel.set_legends({{"MC__LQLQToBTau_MLQ1000_MPS117_MC1100_Lbest","M_{LQ} = 1000 GeV, #lambda = best"}, {"MC__LQLQToBTau_MLQ1360_MPS117_MC1100_Lbest","M_{LQ} = 1360 GeV, #lambda = best"}, {"MC__LQLQToBTau_MLQ1810_MPS117_MC1100_Lbest","M_{LQ} = 1810 GeV, #lambda = best"}, {"MC__LQLQToBTau_MLQ2170_MPS117_MC1100_Lbest","M_{LQ} = 2170 GeV, #lambda = best"}, {"MC__LQLQToBTau_MLQ2620_MPS117_MC1100_Lbest","M_{LQ} = 2620 GeV, #lambda = best"}});
  // Plotter_Recolevel.set_linestyles({{"MC__LQLQToBTau_MLQ1000_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTau_MLQ1360_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTau_MLQ1810_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTau_MLQ2170_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTau_MLQ2620_MPS117_MC1100_Lbest",0}});
  // Plotter_Recolevel.set_colors({{"MC__LQLQToBTau_MLQ1000_MPS117_MC1100_Lbest",kRed+4}, {"MC__LQLQToBTau_MLQ1360_MPS117_MC1100_Lbest",kRed+1}, {"MC__LQLQToBTau_MLQ1810_MPS117_MC1100_Lbest",kAzure-2}, {"MC__LQLQToBTau_MLQ2170_MPS117_MC1100_Lbest",kOrange}, {"MC__LQLQToBTau_MLQ2620_MPS117_MC1100_Lbest",kGreen-2}});
  // // Plotter_Recolevel.Plot(false, true, true);       // SinglePDF
  //
  //
  //
  // Plotter_Recolevel.set_outnameprefix("LQLQToBTauPsiChi_MC1100_Lbest_");
  // Plotter_Recolevel.set_samplenames({"MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_Lbest", "MC__LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_Lbest", "MC__LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest", "MC__LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_Lbest", "MC__LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_Lbest"});
  // Plotter_Recolevel.set_legends({{"MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_Lbest","M_{LQ} = 1000 GeV, #lambda = best"}, {"MC__LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_Lbest","M_{LQ} = 1360 GeV, #lambda = best"}, {"MC__LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest","M_{LQ} = 1810 GeV, #lambda = best"}, {"MC__LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_Lbest","M_{LQ} = 2170 GeV, #lambda = best"}, {"MC__LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_Lbest","M_{LQ} = 2620 GeV, #lambda = best"}});
  // Plotter_Recolevel.set_linestyles({{"MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_Lbest",0}, {"MC__LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_Lbest",0}});
  // Plotter_Recolevel.set_colors({{"MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_Lbest",kRed+4}, {"MC__LQLQToBTauPsiChi_MLQ1360_MPS117_MC1100_Lbest",kRed+1}, {"MC__LQLQToBTauPsiChi_MLQ1810_MPS117_MC1100_Lbest",kAzure-2}, {"MC__LQLQToBTauPsiChi_MLQ2170_MPS117_MC1100_Lbest",kOrange}, {"MC__LQLQToBTauPsiChi_MLQ2620_MPS117_MC1100_Lbest",kGreen-2}});
  // // Plotter_Recolevel.Plot(false, true, true);       // SinglePDF
  //
  //
  // Plotter_Recolevel.set_outnameprefix("LQLQToPsiChi_MC1100_Lbest_");
  // Plotter_Recolevel.set_samplenames({"MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_Lbest", "MC__LQLQToPsiChi_MLQ1360_MPS117_MC1100_Lbest", "MC__LQLQToPsiChi_MLQ1810_MPS117_MC1100_Lbest", "MC__LQLQToPsiChi_MLQ2170_MPS117_MC1100_L1p0", "MC__LQLQToPsiChi_MLQ2620_MPS117_MC1100_Lbest"});
  // Plotter_Recolevel.set_legends({{"MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_Lbest","M_{LQ} = 1000 GeV, #lambda = best"}, {"MC__LQLQToPsiChi_MLQ1360_MPS117_MC1100_Lbest","M_{LQ} = 1360 GeV, #lambda = best"}, {"MC__LQLQToPsiChi_MLQ1810_MPS117_MC1100_Lbest","M_{LQ} = 1810 GeV, #lambda = best"}, {"MC__LQLQToPsiChi_MLQ2170_MPS117_MC1100_L1p0","M_{LQ} = 2170 GeV, #lambda = best"}, {"MC__LQLQToPsiChi_MLQ2620_MPS117_MC1100_Lbest","M_{LQ} = 2620 GeV, #lambda = best"}});
  // Plotter_Recolevel.set_linestyles({{"MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_Lbest",0}, {"MC__LQLQToPsiChi_MLQ1360_MPS117_MC1100_Lbest",0}, {"MC__LQLQToPsiChi_MLQ1810_MPS117_MC1100_Lbest",0}, {"MC__LQLQToPsiChi_MLQ2170_MPS117_MC1100_Lbest",0}, {"MC__LQLQToPsiChi_MLQ2620_MPS117_MC1100_Lbest",0}});
  // Plotter_Recolevel.set_colors({{"MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_Lbest",kRed+4}, {"MC__LQLQToPsiChi_MLQ1360_MPS117_MC1100_Lbest",kRed+1}, {"MC__LQLQToPsiChi_MLQ1810_MPS117_MC1100_Lbest",kAzure-2}, {"MC__LQLQToPsiChi_MLQ2170_MPS117_MC1100_Lbest",kOrange}, {"MC__LQLQToPsiChi_MLQ2620_MPS117_MC1100_Lbest",kGreen-2}});
  // // Plotter_Recolevel.Plot(false, true, true);       // SinglePDF
  //
  //
  // Plotter_Recolevel.set_outnameprefix("PsiPsiToLQChi_MLQ1000_L1p0_");
  // Plotter_Recolevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"});
  // Plotter_Recolevel.set_legends({{"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0","M_{#psi} = 117 GeV, #lambda = 1.0"}, {"MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0","M_{#psi} = 244 GeV, #lambda = 1.0"}, {"MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0","M_{#psi} = 567 GeV, #lambda = 1.0"}, {"MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0","M_{#psi} = 1051 GeV, #lambda = 1.0"}, {"MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0","M_{#psi} = 2221 GeV, #lambda = 1.0"}});
  // Plotter_Recolevel.set_linestyles({{"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",0}, {"MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0",0}, {"MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0",0}, {"MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0",0}, {"MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0",0}});
  // Plotter_Recolevel.set_colors({{"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",kRed+4}, {"MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0",kRed+1}, {"MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0",kAzure-2}, {"MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0",kOrange}, {"MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0",kGreen-2}});
  // // Plotter_Recolevel.Plot(false, true, true);       // SinglePDF




}
