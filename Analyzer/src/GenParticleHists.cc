#include "Analyzer/include/GenParticleHists.h"
#include "Analyzer/include/constants.h"
#include "Analyzer/include/useful_functions.h"
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

GenParticleHists::GenParticleHists(TString dir_) : BaseHists(dir_){

  hngentaus = book<TH1D>("ngentaus", ";N_{gen #tau}; Events / bin", 6, -0.5, 5.5);
  hptgentau1 = book<TH1D>("ptgentau1", ";p_{T}^{gen #tau 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgentau2 = book<TH1D>("ptgentau2", ";p_{T}^{gen #tau 2} [GeV]; Events / bin", 40, 0, 1200);
  vector<double> bins_rebin = {0,3,6,9,12,15,18,21,24,27,30,40,50,75,100,150,200,250, 300,350,400,450,500,600,700,800,900,1000};
  hptgentau1_rebin = book<TH1D>("ptgentau1_rebin", ";p_{T}^{gen #tau 1} [GeV]; Events / bin", bins_rebin.size()-1, bins_rebin.data());
  hptgentau2_rebin = book<TH1D>("ptgentau2_rebin", ";p_{T}^{gen #tau 2} [GeV]; Events / bin", bins_rebin.size()-1, bins_rebin.data());
  vector<double> bins_rebin2 = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000, 1010, 1020, 1030, 1040, 1050, 1060, 1070, 1080, 1090, 1100, 1110, 1120, 1130, 1140, 1150, 1160, 1170, 1180, 1190};
  hptgentau1_rebin2 = book<TH1D>("ptgentau1_rebin2", ";p_{T}^{gen #tau 1} [GeV]; Events / bin", bins_rebin2.size()-1, bins_rebin2.data());
  hptgentau2_rebin2 = book<TH1D>("ptgentau2_rebin2", ";p_{T}^{gen #tau 2} [GeV]; Events / bin", bins_rebin2.size()-1, bins_rebin2.data());
  hptgentau1_rebin3 = book<TH1D>("ptgentau1_rebin3", ";p_{T}^{gen #tau 1} [GeV]; Events / bin", 120, 0, 1200);
  hptgentau2_rebin3 = book<TH1D>("ptgentau2_rebin3", ";p_{T}^{gen #tau 2} [GeV]; Events / bin", 120, 0, 1200);

}

void GenParticleHists::fill(const RecoEvent & event){
  if(event.is_data) return;
  double weight = event.weight;

  // loop through hard genparticles
  double pt_tau1 = 0;
  double pt_tau2 = 0;
  int n_gentaus = 0;
  for(const GenParticle & gp : *event.genparticles_hard){
    int id = abs(gp.pdgid());
    if(id != 15) continue;
    n_gentaus++;
    if(gp.pt() > pt_tau1){
      pt_tau2 = pt_tau1;
      pt_tau1 = gp.pt();
    }
    else if(gp.pt() > pt_tau2) pt_tau2 = gp.pt();
  }

  hngentaus->Fill(n_gentaus, weight);
  hptgentau1->Fill(pt_tau1, weight);
  hptgentau2->Fill(pt_tau2, weight);
  hptgentau1_rebin->Fill(pt_tau1, weight);
  hptgentau2_rebin->Fill(pt_tau2, weight);
  hptgentau1_rebin2->Fill(pt_tau1, weight);
  hptgentau2_rebin2->Fill(pt_tau2, weight);
  hptgentau1_rebin3->Fill(pt_tau1, weight);
  hptgentau2_rebin3->Fill(pt_tau2, weight);


}
