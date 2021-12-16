#include <cmath>
#include <iostream>
#include "Plotter/include/PlottingTool.h"
#include <TString.h>

using namespace std;

int main(){

  map<TString, TString> legends {
    make_pair("DATA__DATA_Tau",                                  "Data (#tau)"),
    make_pair("DATA__DATA_SingleMuon",                           "Data (#mu)"),
    make_pair("DATA__DATA_SingleElectron",                       "Data (e)"),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau (1 TeV)"),
    make_pair("MC__LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau (1.36 TeV)"),
    make_pair("MC__LQLQToBTau_MLQ1810_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau (1.81 TeV)"),
    make_pair("MC__LQLQToBTau_MLQ2620_MPS117_MC1100_L1p0",       "LQLQ#rightarrow b#tau b#tau (2.62 TeV)"),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", "LQLQ#rightarrow b#tau #psi#chi_{1}"),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     "LQLQ#rightarrow #psi#chi_{1} #psi#chi_{1}"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1} (0.12 TeV)"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0",    "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1} (0.24 TeV)"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0",    "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1} (0.58 TeV)"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0",   "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1} (1.05 TeV)"),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0",  "#psi#psi#rightarrow LQ#chi_{1} LQ#chi_{1} (2.22 TeV)"),
    make_pair("MC__QCD_Had",                                     "QCD"),
    make_pair("MC__TT",                                          "t#bar{t}"),
    make_pair("MC__VV",                                          "VV"),
    make_pair("MC__ST",                                          "Single t"),
    make_pair("MC__DYJets",                                      "DY #rightarrow ll"),
    make_pair("MC__WJets",                                       "W+jets #rightarrow l#nu")
  };

  map<TString, int> colors {
    make_pair("DATA__DATA_Tau",                                  kBlack),
    make_pair("DATA__DATA_SingleMuon",                           kBlack),
    make_pair("DATA__DATA_SingleElectron",                       kBlack),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTau_MLQ1810_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTau_MLQ2620_MPS117_MC1100_L1p0",       kBlack),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", kBlack),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0",    kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0",    kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0",   kBlack),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0",  kBlack),
    make_pair("MC__QCD_Had",                                     kCyan-3),
    make_pair("MC__TT",                                          kOrange+10),
    make_pair("MC__VV",                                          kViolet),
    make_pair("MC__ST",                                          kAzure-2),
    make_pair("MC__DYJets",                                      kOrange-2),
    make_pair("MC__WJets",                                       kSpring-6)
  };

  map<TString, int> linestyles {
    make_pair("DATA__DATA_Tau",                                  0),
    make_pair("DATA__DATA_SingleMuon",                           0),
    make_pair("DATA__DATA_SingleElectron",                       0),
    make_pair("MC__LQLQToBTau_MLQ1000_MPS117_MC1100_L1p0",       1),
    make_pair("MC__LQLQToBTau_MLQ1360_MPS117_MC1100_L1p0",       2),
    make_pair("MC__LQLQToBTau_MLQ1810_MPS117_MC1100_L1p0",       3),
    make_pair("MC__LQLQToBTau_MLQ2620_MPS117_MC1100_L1p0",       4),
    make_pair("MC__LQLQToBTauPsiChi_MLQ1000_MPS117_MC1100_L1p0", 2),
    make_pair("MC__LQLQToPsiChi_MLQ1000_MPS117_MC1100_L1p0",     3),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0",    4),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0",    5),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0",    3),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0",   2),
    make_pair("MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0",  1),
    make_pair("MC__QCD_Had",                                     0),
    make_pair("MC__VV",                                          0),
    make_pair("MC__TT",                                          0),
    make_pair("MC__ST",                                          0),
    make_pair("MC__DYJets",                                      0),
    make_pair("MC__WJets",                                       0)
  };



  PlottingTool Plotter_Recolevel;

  // colors["MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0"] =   kRed+4;
  // colors["MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0"] =   kRed+1;
  // colors["MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0"] =   kAzure-2;
  // colors["MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0"] =  kOrange;
  // colors["MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"] = kGreen-2;
  //
  // linestyles["MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0"] =   0;
  // linestyles["MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0"] =   0;
  // linestyles["MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0"] =   0;
  // linestyles["MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0"] =  0;
  // linestyles["MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"] = 0;
  //
  // // TString foldername = "LQDM/2017/Studies/PsiPsi_LeptonIDEfficiencies/";
  // // TString foldername = "LQDM/2017/Preselection/PsiPsi_02LessTriggers/";
  // TString foldername = "LQDM/2017/Preselection/PsiPsi_muon/";
  //
  //
  // Plotter_Recolevel.set_inpath("/pnfs/psi.ch/cms/trivcat/store/user/areimers/"+foldername);
  // Plotter_Recolevel.set_outpath("/work/areimers/"+foldername+"plots/distributions/");
  // Plotter_Recolevel.set_lumitext("41.5 fb^{-1} (13 TeV)");
  // Plotter_Recolevel.set_outnameprefix("PsiPsi_");
  //
  // Plotter_Recolevel.set_samplenames({"MC__ST", "MC__TT", "MC__DYJets", "MC__WJets", "MC__QCD_Had", "MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"});
  // // Plotter_Recolevel.set_samplenames({"MC__PsiPsiToLQChi_MLQ1000_MPS117_MC1100_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS244_MC1214_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS1051_MC1977_L1p0", "MC__PsiPsiToLQChi_MLQ1000_MPS2221_MC12089_L1p0"});
  // Plotter_Recolevel.set_stacks({"MC__ST", "MC__QCD_Had", "MC__DYJets", "MC__TT", "MC__WJets"});
  // Plotter_Recolevel.set_legends(legends);
  // Plotter_Recolevel.set_colors(colors);
  // Plotter_Recolevel.set_linestyles(linestyles);
  //
  // // // Plotter_Recolevel.Plot(blind, normalize, logY, SinglePDF);
  // Plotter_Recolevel.Plot(true, false, true, false);       // usual
  // // Plotter_Recolevel.Plot(true, false, true, true);        // SinglePDF

  colors["MC__LQTChannelTauNu_MLQ1000_MPS117_MC1100_L1p0"] = kRed+4;
  colors["MC__LQTChannelTauNu_MLQ1360_MPS117_MC1100_L1p0"] = kRed+1;
  colors["MC__LQTChannelTauNu_MLQ1810_MPS117_MC1100_L1p0"] = kAzure-2;
  colors["MC__LQTChannelTauNu_MLQ2170_MPS117_MC1100_L1p0"] = kOrange;
  colors["MC__LQTChannelTauNu_MLQ2980_MPS117_MC1100_L1p0"] = kGreen-2;
  colors["MC__LQTChannelTauNu_DynamicScale_MLQ1000_MPS117_MC1100_L1p0"] = kRed+4;
  colors["MC__LQTChannelTauNu_DynamicScale_MLQ1360_MPS117_MC1100_L1p0"] = kRed+1;
  colors["MC__LQTChannelTauNu_DynamicScale_MLQ1810_MPS117_MC1100_L1p0"] = kAzure-2;
  colors["MC__LQTChannelTauNu_DynamicScale_MLQ2170_MPS117_MC1100_L1p0"] = kOrange;
  colors["MC__LQTChannelTauNu_DynamicScale_MLQ2980_MPS117_MC1100_L1p0"] = kGreen-2;
  colors["MC__LQTChannelTauMu_MLQ1000_MPS117_MC1100_L1p0"] = kRed+4;
  colors["MC__LQTChannelTauMu_MLQ1360_MPS117_MC1100_L1p0"] = kRed+1;
  colors["MC__LQTChannelTauMu_MLQ1810_MPS117_MC1100_L1p0"] = kAzure-2;
  colors["MC__LQTChannelTauMu_MLQ2170_MPS117_MC1100_L1p0"] = kOrange;
  colors["MC__LQTChannelTauMu_MLQ2980_MPS117_MC1100_L1p0"] = kGreen-2;


  linestyles["MC__LQTChannelTauNu_MLQ1000_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_MLQ1360_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_MLQ1810_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_MLQ2170_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_MLQ2980_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_DynamicScale_MLQ1000_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_DynamicScale_MLQ1360_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_DynamicScale_MLQ1810_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_DynamicScale_MLQ2170_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauNu_DynamicScale_MLQ2980_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauMu_MLQ1000_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauMu_MLQ1360_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauMu_MLQ1810_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauMu_MLQ2170_MPS117_MC1100_L1p0"] = 0;
  linestyles["MC__LQTChannelTauMu_MLQ2980_MPS117_MC1100_L1p0"] = 0;


  legends["MC__LQTChannelTauNu_MLQ1000_MPS117_MC1100_L1p0"] = "t-ch. #tau#nu (M_{LQ} = 1.00 TeV)";
  legends["MC__LQTChannelTauNu_MLQ1360_MPS117_MC1100_L1p0"] = "t-ch. #tau#nu (M_{LQ} = 1.36 TeV)";
  legends["MC__LQTChannelTauNu_MLQ1810_MPS117_MC1100_L1p0"] = "t-ch. #tau#nu (M_{LQ} = 1.81 TeV)";
  legends["MC__LQTChannelTauNu_MLQ2170_MPS117_MC1100_L1p0"] = "t-ch. #tau#nu (M_{LQ} = 2.17 TeV)";
  legends["MC__LQTChannelTauNu_MLQ2980_MPS117_MC1100_L1p0"] = "t-ch. #tau#nu (M_{LQ} = 2.98 TeV)";
  legends["MC__LQTChannelTauNu_DynamicScale_MLQ1000_MPS117_MC1100_L1p0"] = "t-ch. LQ #rightarrow #tau#nu (1.00 TeV)";
  legends["MC__LQTChannelTauNu_DynamicScale_MLQ1360_MPS117_MC1100_L1p0"] = "t-ch. LQ #rightarrow #tau#nu (1.36 TeV)";
  legends["MC__LQTChannelTauNu_DynamicScale_MLQ1810_MPS117_MC1100_L1p0"] = "t-ch. LQ #rightarrow #tau#nu (1.81 TeV)";
  legends["MC__LQTChannelTauNu_DynamicScale_MLQ2170_MPS117_MC1100_L1p0"] = "t-ch. LQ #rightarrow #tau#nu (2.17 TeV)";
  legends["MC__LQTChannelTauNu_DynamicScale_MLQ2980_MPS117_MC1100_L1p0"] = "t-ch. LQ #rightarrow #tau#nu (2.98 TeV)";
  legends["MC__LQTChannelTauMu_MLQ1000_MPS117_MC1100_L1p0"] = "t-ch. #tau#mu (M_{LQ} = 1.00 TeV)";
  legends["MC__LQTChannelTauMu_MLQ1360_MPS117_MC1100_L1p0"] = "t-ch. #tau#mu (M_{LQ} = 1.36 TeV)";
  legends["MC__LQTChannelTauMu_MLQ1810_MPS117_MC1100_L1p0"] = "t-ch. #tau#mu (M_{LQ} = 1.81 TeV)";
  legends["MC__LQTChannelTauMu_MLQ2170_MPS117_MC1100_L1p0"] = "t-ch. #tau#mu (M_{LQ} = 2.17 TeV)";
  legends["MC__LQTChannelTauMu_MLQ2980_MPS117_MC1100_L1p0"] = "t-ch. #tau#mu (M_{LQ} = 2.98 TeV)";

  // TString foldername = "LQDM/2017/Studies/PsiPsi_LeptonIDEfficiencies/";
  // TString foldername = "LQDM/2017/Preselection/PsiPsi_02LessTriggers/";
  // TString foldername = "LQDM/2017/Preselection/TChannelTauNu_tau/";
  // TString foldername = "LQDM/2017/Fullselection/TChannelTauNu_tau/";
  TString foldername = "LQDM/2017/Fullselection/TChannelTauNu_wprime_tau/";
  // TString foldername = "LQDM/2017/Preselection/TChannelTauNu_muon/";
  // TString foldername = "LQDM/2017/Fullselection/TChannelTauNu_muon/";
  // TString foldername = "LQDM/2017/Fullselection/TChannelTauNu_muon_opt/";
  // TString foldername = "LQDM/2017/Fullselection/TChannelTauNu_muon_wprime/";


  Plotter_Recolevel.set_inpath("/pnfs/psi.ch/cms/trivcat/store/user/areimers/"+foldername);
  Plotter_Recolevel.set_outpath("/work/areimers/"+foldername+"plots/distributions/");
  Plotter_Recolevel.set_lumitext("41.5 fb^{-1} (13 TeV)");
  Plotter_Recolevel.set_outnameprefix("LQTChannelTauNu_DynamicScale_");

  Plotter_Recolevel.set_samplenames({"MC__VV", "MC__ST", "MC__TT", "MC__DYJets", "MC__WJets", "MC__QCD_Had", "MC__LQTChannelTauNu_DynamicScale_MLQ1000_MPS117_MC1100_L1p0", "MC__LQTChannelTauNu_DynamicScale_MLQ1360_MPS117_MC1100_L1p0", "MC__LQTChannelTauNu_DynamicScale_MLQ1810_MPS117_MC1100_L1p0", "MC__LQTChannelTauNu_DynamicScale_MLQ2170_MPS117_MC1100_L1p0", "MC__LQTChannelTauNu_DynamicScale_MLQ2980_MPS117_MC1100_L1p0"});
  Plotter_Recolevel.set_stacks({"MC__ST", "MC__QCD_Had", "MC__VV", "MC__DYJets", "MC__TT", "MC__WJets"});
  Plotter_Recolevel.set_legends(legends);
  Plotter_Recolevel.set_colors(colors);
  Plotter_Recolevel.set_linestyles(linestyles);

  // // Plotter_Recolevel.Plot(blind, normalize, logY, SinglePDF);
  Plotter_Recolevel.Plot(true, false, true, false);      // usual
  // Plotter_Recolevel.Plot(true, true, true, false);       // norm
  // Plotter_Recolevel.Plot(true, false, true, true);       // SinglePDF
  // Plotter_Recolevel.Plot(true, true, true, true);        // SinglePDF norm


  // Plotter_Recolevel.set_outnameprefix("HLTCheck_LQTChannelTauMu_");
  // Plotter_Recolevel.set_samplenames({"MC__LQTChannelTauMu_MLQ1000_MPS117_MC1100_L1p0", "MC__LQTChannelTauMu_MLQ1360_MPS117_MC1100_L1p0", "MC__LQTChannelTauMu_MLQ1810_MPS117_MC1100_L1p0", "MC__LQTChannelTauMu_MLQ2170_MPS117_MC1100_L1p0", "MC__LQTChannelTauMu_MLQ2980_MPS117_MC1100_L1p0"});
  // // Plotter_Recolevel.Plot(blind, normalize, logY, SinglePDF);
  // Plotter_Recolevel.Plot(true, false, true, false);      // usual
  // Plotter_Recolevel.Plot(true, true, true, false);       // norm
  // Plotter_Recolevel.Plot(true, false, true, true);       // SinglePDF
  // Plotter_Recolevel.Plot(true, true, true, true);        // SinglePDF norm






}
