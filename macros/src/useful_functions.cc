#include "../include/GenlevelTool.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include <TH1D.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

TString lambstr(double lambda){
  ostringstream ss;
  ss << fixed << setprecision(1) << lambda;
  string s(ss.str());
  TString result = s;
  result = result.ReplaceAll(".", "p");
  return result;
}

TString get_samplename(double mlq, double mx, double mdm, double lambda){
  TString result = "MLQ";
  result += mlq;
  result += "_MX";
  result += mx;
  result += "_MDM";
  result += mdm;
  result += "_L";
  result += lambstr(lambda);
  return result;
}

map<TString, unique_ptr<TH1F>> setup_histmap(){
  map<TString, unique_ptr<TH1F>> histograms;
  TString name = "nlq";
  histograms[name].reset(new TH1F(name, ";N_{LQ}; Events / bin", 6, -0.5, 5.5));
  name = "nx";
  histograms[name].reset(new TH1F(name, ";N_{X}; Events / bin", 6, -0.5, 5.5));
  name = "ndm";
  histograms[name].reset(new TH1F(name, ";N_{DM}; Events / bin", 6, -0.5, 5.5));
  name = "njets";
  histograms[name].reset(new TH1F(name, ";N_{jets}; Events / bin", 11, -0.5, 10.5));
  name = "nb";
  histograms[name].reset(new TH1F(name, ";N_{b}; Events / bin", 6, -0.5, 5.5));
  name = "nbcut";
  histograms[name].reset(new TH1F(name, ";N_{b}^{cut}; Events / bin", 6, -0.5, 5.5));
  name = "nbcut50";
  histograms[name].reset(new TH1F(name, ";N_{b}^{cut 50}; Events / bin", 6, -0.5, 5.5));
  name = "ntau";
  histograms[name].reset(new TH1F(name, ";N_{#tau}; Events / bin", 6, -0.5, 5.5));
  name = "ntaucut";
  histograms[name].reset(new TH1F(name, ";N_{#tau}^{cut}; Events / bin", 6, -0.5, 5.5));
  name = "ntaucut50";
  histograms[name].reset(new TH1F(name, ";N_{#tau}^{cut 50}; Events / bin", 6, -0.5, 5.5));
  name = "ntaucut_vis";
  histograms[name].reset(new TH1F(name, ";N_{vis. #tau}^{cut}; Events / bin", 6, -0.5, 5.5));
  name = "ntaucut50_vis";
  histograms[name].reset(new TH1F(name, ";N_{vis. #tau}^{cut 50}; Events / bin", 6, -0.5, 5.5));
  name = "nbcut";
  histograms[name].reset(new TH1F(name, ";N_{b}^{cut}; Events / bin", 6, -0.5, 5.5));
  name = "nbcut50";
  histograms[name].reset(new TH1F(name, ";N_{b}^{cut 50}; Events / bin", 6, -0.5, 5.5));


  name = "mlq1";
  histograms[name].reset(new TH1F(name, ";M_{LQ 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mlq2";
  histograms[name].reset(new TH1F(name, ";M_{LQ 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "mx";
  histograms[name].reset(new TH1F(name, ";M_{X} [GeV]; Events / bin", 300, 0, 3000));
  name = "mdm1";
  histograms[name].reset(new TH1F(name, ";M_{DM 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mdm2";
  histograms[name].reset(new TH1F(name, ";M_{DM 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptlq1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{LQ 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptlq2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{LQ 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptx";
  histograms[name].reset(new TH1F(name, ";p_{T}^{X} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptdm1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{DM 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptdm2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{DM 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "etalq1";
  histograms[name].reset(new TH1F(name, ";#eta_{LQ 1}; Events / bin", 60, -3.5, 3.5));
  name = "etalq2";
  histograms[name].reset(new TH1F(name, ";#eta_{LQ 2}; Events / bin", 60, -3.5, 3.5));
  name = "etax";
  histograms[name].reset(new TH1F(name, ";#eta_{X}; Events / bin", 60, -3.5, 3.5));
  name = "etadm1";
  histograms[name].reset(new TH1F(name, ";#eta_{DM 1}; Events / bin", 60, -3.5, 3.5));
  name = "etadm2";
  histograms[name].reset(new TH1F(name, ";#eta_{DM 2}; Events / bin", 60, -3.5, 3.5));
  name = "philq1";
  histograms[name].reset(new TH1F(name, ";#phi_{LQ 1}; Events / bin", 60, -3.5, 3.5));
  name = "philq2";
  histograms[name].reset(new TH1F(name, ";#phi_{LQ 2}; Events / bin", 60, -3.5, 3.5));
  name = "phix";
  histograms[name].reset(new TH1F(name, ";#phi_{X}; Events / bin", 60, -3.5, 3.5));
  name = "phidm1";
  histograms[name].reset(new TH1F(name, ";#phi_{DM 1}; Events / bin", 60, -3.5, 3.5));
  name = "phidm2";
  histograms[name].reset(new TH1F(name, ";#phi_{DM 2}; Events / bin", 60, -3.5, 3.5));


  name = "ptjet1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{jet 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptjet2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{jet 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptjet3";
  histograms[name].reset(new TH1F(name, ";p_{T}^{jet 3} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptb1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{b 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "ptb2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{b 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "pttau1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{#tau 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "pttau2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{#tau 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "pttauvis1";
  histograms[name].reset(new TH1F(name, ";p_{T}^{vis. #tau 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "pttauvis2";
  histograms[name].reset(new TH1F(name, ";p_{T}^{vis. #tau 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "etajet1";
  histograms[name].reset(new TH1F(name, ";#eta_{jet 1}; Events / bin", 60, -3.5, 3.5));
  name = "etajet2";
  histograms[name].reset(new TH1F(name, ";#eta_{jet 2}; Events / bin", 60, -3.5, 3.5));
  name = "etajet3";
  histograms[name].reset(new TH1F(name, ";#eta_{jet 3}; Events / bin", 60, -3.5, 3.5));
  name = "etab1";
  histograms[name].reset(new TH1F(name, ";#eta_{b 1}; Events / bin", 60, -3.5, 3.5));
  name = "etab2";
  histograms[name].reset(new TH1F(name, ";#eta_{b 2}; Events / bin", 60, -3.5, 3.5));
  name = "etatau1";
  histograms[name].reset(new TH1F(name, ";#eta_{#tau 1}; Events / bin", 60, -3.5, 3.5));
  name = "etatau2";
  histograms[name].reset(new TH1F(name, ";#eta_{#tau 2}; Events / bin", 60, -3.5, 3.5));
  name = "etatauvis1";
  histograms[name].reset(new TH1F(name, ";#eta_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5));
  name = "etatauvis2";
  histograms[name].reset(new TH1F(name, ";#eta_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5));
  name = "phijet1";
  histograms[name].reset(new TH1F(name, ";#phi_{jet 1}; Events / bin", 60, -3.5, 3.5));
  name = "phijet2";
  histograms[name].reset(new TH1F(name, ";#phi_{jet 2}; Events / bin", 60, -3.5, 3.5));
  name = "phijet3";
  histograms[name].reset(new TH1F(name, ";#phi_{jet 3}; Events / bin", 60, -3.5, 3.5));
  name = "phib1";
  histograms[name].reset(new TH1F(name, ";#phi_{b 1}; Events / bin", 60, -3.5, 3.5));
  name = "phib2";
  histograms[name].reset(new TH1F(name, ";#phi_{b 2}; Events / bin", 60, -3.5, 3.5));
  name = "phitau1";
  histograms[name].reset(new TH1F(name, ";#phi_{#tau 1}; Events / bin", 60, -3.5, 3.5));
  name = "phitau2";
  histograms[name].reset(new TH1F(name, ";#phi_{#tau 2}; Events / bin", 60, -3.5, 3.5));
  name = "phitauvis1";
  histograms[name].reset(new TH1F(name, ";#phi_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5));
  name = "phitauvis2";
  histograms[name].reset(new TH1F(name, ";#phi_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5));
  name = "mjet1";
  histograms[name].reset(new TH1F(name, ";M_{jet 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mjet2";
  histograms[name].reset(new TH1F(name, ";M_{jet 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "mjet3";
  histograms[name].reset(new TH1F(name, ";M_{jet 3} [GeV]; Events / bin", 300, 0, 3000));
  name = "mb1";
  histograms[name].reset(new TH1F(name, ";M_{b 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mb2";
  histograms[name].reset(new TH1F(name, ";M_{b 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "mtau1";
  histograms[name].reset(new TH1F(name, ";M_{#tau 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mtau2";
  histograms[name].reset(new TH1F(name, ";M_{#tau 2} [GeV]; Events / bin", 300, 0, 3000));
  name = "mtauvis1";
  histograms[name].reset(new TH1F(name, ";M_{vis. #tau 1} [GeV]; Events / bin", 300, 0, 3000));
  name = "mtauvis2";
  histograms[name].reset(new TH1F(name, ";M_{vis. #tau 2} [GeV]; Events / bin", 300, 0, 3000));

  name = "ptmet";
  histograms[name].reset(new TH1F(name, ";E_{T}^{miss} [GeV]; Events / bin", 300, 0, 3000));
  name = "phimet";
  histograms[name].reset(new TH1F(name, ";#phi(E_{T}^{miss}); Events / bin", 60, -3.5, 3.5));
  name = "st";
  histograms[name].reset(new TH1F(name, ";S_{T} [GeV]; Events / bin", 300, 0, 3000));
  name = "stmet";
  histograms[name].reset(new TH1F(name, ";S_{T}^{MET} [GeV]; Events / bin", 300, 0, 3000));

  return histograms;
}
