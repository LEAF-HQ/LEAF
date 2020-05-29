#include "../include/GenlevelTool.h"
#include "../include/GenHists.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include <TH1F.h>
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

GenHists::GenHists(TString dir_) : dir(dir_){

  nlq = book<TH1F>("nlq", ";N_{LQ}; Events / bin", 6, -0.5, 5.5);
  nx = book<TH1F>("nx", ";N_{X}; Events / bin", 6, -0.5, 5.5);
  ndm = book<TH1F>("ndm", ";N_{DM}; Events / bin", 6, -0.5, 5.5);
  njets = book<TH1F>("njets", ";N_{jets}; Events / bin", 11, -0.5, 10.5);
  nb = book<TH1F>("nb", ";N_{b}; Events / bin", 6, -0.5, 5.5);
  nbcut = book<TH1F>("nbcut", ";N_{b}^{cut}; Events / bin", 6, -0.5, 5.5);
  nbcut50 = book<TH1F>("nbcut50", ";N_{b}^{cut 50}; Events / bin", 6, -0.5, 5.5);
  ntau = book<TH1F>("ntau", ";N_{#tau}; Events / bin", 6, -0.5, 5.5);
  ntaucut = book<TH1F>("ntaucut", ";N_{#tau}^{cut}; Events / bin", 6, -0.5, 5.5);
  ntaucut50 = book<TH1F>("ntaucut50", ";N_{#tau}^{cut 50}; Events / bin", 6, -0.5, 5.5);
  ntaucut_vis = book<TH1F>("ntaucut_vis", ";N_{vis. #tau}^{cut}; Events / bin", 6, -0.5, 5.5);
  ntaucut50_vis = book<TH1F>("ntaucut50_vis", ";N_{vis. #tau}^{cut 50}; Events / bin", 6, -0.5, 5.5);
  mlq1 = book<TH1F>("mlq1", ";M_{LQ 1} [GeV]; Events / bin", 300, 0, 3000);
  mlq2 = book<TH1F>("mlq2", ";M_{LQ 2} [GeV]; Events / bin", 300, 0, 3000);
  mx = book<TH1F>("mx", ";M_{X} [GeV]; Events / bin", 300, 0, 3000);
  mdm1 = book<TH1F>("mdm1", ";M_{DM 1} [GeV]; Events / bin", 300, 0, 3000);
  mdm2 = book<TH1F>("mdm2", ";M_{DM 2} [GeV]; Events / bin", 300, 0, 3000);
  ptlq1 = book<TH1F>("ptlq1", ";p_{T}^{LQ 1} [GeV]; Events / bin", 300, 0, 3000);
  ptlq2 = book<TH1F>("ptlq2", ";p_{T}^{LQ 2} [GeV]; Events / bin", 300, 0, 3000);
  ptx = book<TH1F>("ptx", ";p_{T}^{X} [GeV]; Events / bin", 300, 0, 3000);
  ptdm1 = book<TH1F>("ptdm1", ";p_{T}^{DM 1} [GeV]; Events / bin", 300, 0, 3000);
  ptdm2 = book<TH1F>("ptdm2", ";p_{T}^{DM 2} [GeV]; Events / bin", 300, 0, 3000);
  etalq1 = book<TH1F>("etalq1", ";#eta_{LQ 1}; Events / bin", 60, -3.5, 3.5);
  etalq2 = book<TH1F>("etalq2", ";#eta_{LQ 2}; Events / bin", 60, -3.5, 3.5);
  etax = book<TH1F>("etax", ";#eta_{X}; Events / bin", 60, -3.5, 3.5);
  etadm1 = book<TH1F>("etadm1", ";#eta_{DM 1}; Events / bin", 60, -3.5, 3.5);
  etadm2 = book<TH1F>("etadm2", ";#eta_{DM 2}; Events / bin", 60, -3.5, 3.5);
  philq1 = book<TH1F>("philq1", ";#phi_{LQ 1}; Events / bin", 60, -3.5, 3.5);
  philq2 = book<TH1F>("philq2", ";#phi_{LQ 2}; Events / bin", 60, -3.5, 3.5);
  phix = book<TH1F>("phix", ";#phi_{X}; Events / bin", 60, -3.5, 3.5);
  phidm1 = book<TH1F>("phidm1", ";#phi_{DM 1}; Events / bin", 60, -3.5, 3.5);
  phidm2 = book<TH1F>("phidm2", ";#phi_{DM 2}; Events / bin", 60, -3.5, 3.5);
  ptjet1 = book<TH1F>("ptjet1", ";p_{T}^{jet 1} [GeV]; Events / bin", 300, 0, 3000);
  ptjet2 = book<TH1F>("ptjet2", ";p_{T}^{jet 2} [GeV]; Events / bin", 300, 0, 3000);
  ptjet3 = book<TH1F>("ptjet3", ";p_{T}^{jet 3} [GeV]; Events / bin", 300, 0, 3000);
  ptb1 = book<TH1F>("ptb1", ";p_{T}^{b 1} [GeV]; Events / bin", 300, 0, 3000);
  ptb2 = book<TH1F>("ptb2", ";p_{T}^{b 2} [GeV]; Events / bin", 300, 0, 3000);
  pttau1 = book<TH1F>("pttau1", ";p_{T}^{#tau 1} [GeV]; Events / bin", 300, 0, 3000);
  pttau2 = book<TH1F>("pttau2", ";p_{T}^{#tau 2} [GeV]; Events / bin", 300, 0, 3000);
  pttauvis1 = book<TH1F>("pttauvis1", ";p_{T}^{vis. #tau 1} [GeV]; Events / bin", 300, 0, 3000);
  pttauvis2 = book<TH1F>("pttauvis2", ";p_{T}^{vis. #tau 2} [GeV]; Events / bin", 300, 0, 3000);
  etajet1 = book<TH1F>("etajet1", ";#eta_{jet 1}; Events / bin", 60, -3.5, 3.5);
  etajet2 = book<TH1F>("etajet2", ";#eta_{jet 2}; Events / bin", 60, -3.5, 3.5);
  etajet3 = book<TH1F>("etajet3", ";#eta_{jet 3}; Events / bin", 60, -3.5, 3.5);
  etab1 = book<TH1F>("etab1", ";#eta_{b 1}; Events / bin", 60, -3.5, 3.5);
  etab2 = book<TH1F>("etab2", ";#eta_{b 2}; Events / bin", 60, -3.5, 3.5);
  etatau1 = book<TH1F>("etatau1", ";#eta_{#tau 1}; Events / bin", 60, -3.5, 3.5);
  etatau2 = book<TH1F>("etatau2", ";#eta_{#tau 2}; Events / bin", 60, -3.5, 3.5);
  etatauvis1 = book<TH1F>("etatauvis1", ";#eta_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5);
  etatauvis2 = book<TH1F>("etatauvis2", ";#eta_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5);
  phijet1 = book<TH1F>("phijet1", ";#phi_{jet 1}; Events / bin", 60, -3.5, 3.5);
  phijet2 = book<TH1F>("phijet2", ";#phi_{jet 2}; Events / bin", 60, -3.5, 3.5);
  phijet3 = book<TH1F>("phijet3", ";#phi_{jet 3}; Events / bin", 60, -3.5, 3.5);
  phib1 = book<TH1F>("phib1", ";#phi_{b 1}; Events / bin", 60, -3.5, 3.5);
  phib2 = book<TH1F>("phib2", ";#phi_{b 2}; Events / bin", 60, -3.5, 3.5);
  phitau1 = book<TH1F>("phitau1", ";#phi_{#tau 1}; Events / bin", 60, -3.5, 3.5);
  phitau2 = book<TH1F>("phitau2", ";#phi_{#tau 2}; Events / bin", 60, -3.5, 3.5);
  phitauvis1 = book<TH1F>("phitauvis1", ";#phi_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5);
  phitauvis2 = book<TH1F>("phitauvis2", ";#phi_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5);
  mjet1 = book<TH1F>("mjet1", ";M_{jet 1} [GeV]; Events / bin", 300, 0, 3000);
  mjet2 = book<TH1F>("mjet2", ";M_{jet 2} [GeV]; Events / bin", 300, 0, 3000);
  mjet3 = book<TH1F>("mjet3", ";M_{jet 3} [GeV]; Events / bin", 300, 0, 3000);
  mb1 = book<TH1F>("mb1", ";M_{b 1} [GeV]; Events / bin", 300, 0, 3000);
  mb2 = book<TH1F>("mb2", ";M_{b 2} [GeV]; Events / bin", 300, 0, 3000);
  mtau1 = book<TH1F>("mtau1", ";M_{#tau 1} [GeV]; Events / bin", 300, 0, 3000);
  mtau2 = book<TH1F>("mtau2", ";M_{#tau 2} [GeV]; Events / bin", 300, 0, 3000);
  mtauvis1 = book<TH1F>("mtauvis1", ";M_{vis. #tau 1} [GeV]; Events / bin", 300, 0, 3000);
  mtauvis2 = book<TH1F>("mtauvis2", ";M_{vis. #tau 2} [GeV]; Events / bin", 300, 0, 3000);
  ptmet = book<TH1F>("ptmet", ";E_{T}^{miss} [GeV]; Events / bin", 300, 0, 3000);
  phimet = book<TH1F>("phimet", ";#phi(E_{T}^{miss}); Events / bin", 60, -3.5, 3.5);
  st = book<TH1F>("st", ";S_{T} [GeV]; Events / bin", 300, 0, 3000);
  stmet = book<TH1F>("stmet", ";S_{T}^{MET} [GeV]; Events / bin", 300, 0, 3000);

}

void GenHists::fill(const Event & event){

  // double weight = event.weight;
  // cout << "st: " << event.st << endl;

  // hists["nlq"]->Fill(event.nlq, weight);
  // hists["nx"]->Fill(event.nx, weight);
  // hists["ndm"]->Fill(event.ndm, weight);
  // hists["njets"]->Fill(event.njets, weight);
  // hists["nb"]->Fill(event.nb, weight);
  // hists["nbcut"]->Fill(event.nbcut, weight);
  // hists["nbcut50"]->Fill(event.nbcut50, weight);
  // hists["ntau"]->Fill(event.ntau, weight);
  // hists["ntaucut"]->Fill(event.ntaucut, weight);
  // hists["ntaucut50"]->Fill(event.ntaucut50, weight);
  // hists["ntaucut_vis"]->Fill(event.ntaucut_vis, weight);
  // hists["ntaucut50_vis"]->Fill(event.ntaucut50_vis, weight);
  // hists["mlq1"]->Fill(event.mlq1, weight);
  // hists["mlq2"]->Fill(event.mlq2, weight);
  // hists["mx"]->Fill(event.mx, weight);
  // hists["mdm1"]->Fill(event.mdm1, weight);
  // hists["mdm2"]->Fill(event.mdm2, weight);
  // hists["ptlq1"]->Fill(event.ptlq1, weight);
  // hists["ptlq2"]->Fill(event.ptlq2, weight);
  // hists["ptx"]->Fill(event.ptx, weight);
  // hists["ptdm1"]->Fill(event.ptdm1, weight);
  // hists["ptdm2"]->Fill(event.ptdm2, weight);
  // hists["etalq1"]->Fill(event.etalq1, weight);
  // hists["etalq2"]->Fill(event.etalq2, weight);
  // hists["etax"]->Fill(event.etax, weight);
  // hists["etadm1"]->Fill(event.etadm1, weight);
  // hists["etadm2"]->Fill(event.etadm2, weight);
  // hists["philq1"]->Fill(event.philq1, weight);
  // hists["philq2"]->Fill(event.philq2, weight);
  // hists["phix"]->Fill(event.phix, weight);
  // hists["phidm1"]->Fill(event.phidm1, weight);
  // hists["phidm2"]->Fill(event.phidm2, weight);
  // hists["ptjet1"]->Fill(event.ptjet1, weight);
  // hists["ptjet2"]->Fill(event.ptjet2, weight);
  // hists["ptjet3"]->Fill(event.ptjet3, weight);
  // hists["ptb1"]->Fill(event.ptb1, weight);
  // hists["ptb2"]->Fill(event.ptb2, weight);
  // hists["pttau1"]->Fill(event.pttau1, weight);
  // hists["pttau2"]->Fill(event.pttau2, weight);
  // hists["pttauvis1"]->Fill(event.pttauvis1, weight);
  // hists["pttauvis2"]->Fill(event.pttauvis2, weight);
  // hists["etajet1"]->Fill(event.etajet1, weight);
  // hists["etajet2"]->Fill(event.etajet2, weight);
  // hists["etajet3"]->Fill(event.etajet3, weight);
  // hists["etab1"]->Fill(event.etab1, weight);
  // hists["etab2"]->Fill(event.etab2, weight);
  // hists["etatau1"]->Fill(event.etatau1, weight);
  // hists["etatau2"]->Fill(event.etatau2, weight);
  // hists["etatauvis1"]->Fill(event.etatauvis1, weight);
  // hists["etatauvis2"]->Fill(event.etatauvis2, weight);
  // hists["phijet1"]->Fill(event.phijet1, weight);
  // hists["phijet2"]->Fill(event.phijet2, weight);
  // hists["phijet3"]->Fill(event.phijet3, weight);
  // hists["phib1"]->Fill(event.phib1, weight);
  // hists["phib2"]->Fill(event.phib2, weight);
  // hists["phitau1"]->Fill(event.phitau1, weight);
  // hists["phitau2"]->Fill(event.phitau2, weight);
  // hists["phitauvis1"]->Fill(event.phitauvis1, weight);
  // hists["phitauvis2"]->Fill(event.phitauvis2, weight);
  // hists["mjet1"]->Fill(event.mjet1, weight);
  // hists["mjet2"]->Fill(event.mjet2, weight);
  // hists["mjet3"]->Fill(event.mjet3, weight);
  // hists["mb1"]->Fill(event.mb1, weight);
  // hists["mb2"]->Fill(event.mb2, weight);
  // hists["mtau1"]->Fill(event.mtau1, weight);
  // hists["mtau2"]->Fill(event.mtau2, weight);
  // hists["mtauvis1"]->Fill(event.mtauvis1, weight);
  // hists["mtauvis2"]->Fill(event.mtauvis2, weight);
  // hists["ptmet"]->Fill(event.ptmet, weight);
  // hists["phimet"]->Fill(event.phimet, weight);
  // hists["st"]->Fill(event.st, weight);
  // hists["stmet"]->Fill(event.stmet, weight);
}


void GenHists::save(TFile* outfile){
  outfile->cd();
  outfile->mkdir(dir);
  outfile->cd(dir);
  for(const auto & m : hists) m.second->Write();
}
