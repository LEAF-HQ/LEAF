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

  hngentaus = book<TH1D>("ngentaus", ";N_{gen #tau}; Events / bin", 11, -0.5, 10.5);
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
  hptgentau1_rebin4 = book<TH1D>("ptgentau1_rebin4", ";p_{T}^{gen #tau 1} [GeV]; Events / bin", 50, 0, 200);
  hptgentau2_rebin4 = book<TH1D>("ptgentau2_rebin4", ";p_{T}^{gen #tau 2} [GeV]; Events / bin", 50, 0, 200);


  hngenvistaus = book<TH1D>("ngenvistaus", ";N_{gen vis. #tau}; Events / bin", 11, -0.5, 10.5);
  hngenvistausmatched = book<TH1D>("ngenvistausmatched", ";N_{matched gen vis. #tau}; Events / bin", 11, -0.5, 10.5);
  hgenvistaustotal = book<TH1D>("genvistaustotal", ";binc = total N_{gen vis. #tau}; Events / bin", 1, -0.5, 0.5);
  hgenvistausmatched = book<TH1D>("genvistausmatched", ";binc = total N_{matched gen vis. #tau}; Events / bin", 1, -0.5, 0.5);
  hptgenvistau = book<TH1D>("ptgenvistau", ";p_{T}^{gen vis. #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau_rebin = book<TH1D>("ptgenvistau_rebin", ";p_{T}^{gen vis. #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau_rebin2 = book<TH1D>("ptgenvistau_rebin2", ";p_{T}^{gen vis. #tau} [GeV]; Events / bin", 50, 0, 50);
  hptgenvistaumatched = book<TH1D>("ptgenvistaumatched", ";p_{T}^{gen and matched vis. #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistaumatched_rebin = book<TH1D>("ptgenvistaumatched_rebin", ";p_{T}^{gen and matched vis. #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistaumatched_rebin2 = book<TH1D>("ptgenvistaumatched_rebin2", ";p_{T}^{gen and matched vis. #tau} [GeV]; Events / bin", 50, 0, 50);
  hdrmintau = book<TH1D>("drmintau", ";#DeltaR(gen vis. #tau, reco #tau) [GeV]; Events / bin", 60, 0, 3);
  hgenvistaudecaymode = book<TH1D>("genvistaustatus", ";vis. #tau decaymode ; Events / bin", 16, -0.5, 15.5);
  hptgenvistau1 = book<TH1D>("ptgenvistau1", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau1_rebin = book<TH1D>("ptgenvistau1_rebin", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau1_rebin2 = book<TH1D>("ptgenvistau1_rebin2", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenvistau1matched = book<TH1D>("ptgenvistau1matched", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau1matched_rebin = book<TH1D>("ptgenvistau1matched_rebin", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau1matched_rebin2 = book<TH1D>("ptgenvistau1matched_rebin2", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 50, 0, 50);
  hdrmintau1 = book<TH1D>("drmintau1", ";#DeltaR(gen vis. #tau 1, reco #tau) [GeV]; Events / bin", 60, 0, 3);
  hgenvistau1decaymode = book<TH1D>("genvistau1status", ";vis. #tau 1 decaymode ; Events / bin", 3, -0.5, 2.5);
  hptgenvistau2 = book<TH1D>("ptgenvistau2", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau2_rebin = book<TH1D>("ptgenvistau2_rebin", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau2_rebin2 = book<TH1D>("ptgenvistau2_rebin2", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenvistau2matched = book<TH1D>("ptgenvistau2matched", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau2matched_rebin = book<TH1D>("ptgenvistau2matched_rebin", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau2matched_rebin2 = book<TH1D>("ptgenvistau2matched_rebin2", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 50, 0, 50);
  hdrmintau2 = book<TH1D>("drmintau2", ";#DeltaR(gen vis. #tau 2, reco #tau) [GeV]; Events / bin", 60, 0, 3);
  hgenvistau2decaymode = book<TH1D>("genvistau2status", ";vis. #tau 2 decaymode ; Events / bin", 3, -0.5, 2.5);


  hngenmus = book<TH1D>("ngenmus", ";N_{gen #mu}; Events / bin", 11, -0.5, 10.5);
  hngenmusmatched = book<TH1D>("ngenmusmatched", ";N_{matched gen #mu}; Events / bin", 11, -0.5, 10.5);
  hgenmustotal = book<TH1D>("genmustotal", ";binc = total N_{gen #mu}; Events / bin", 1, -0.5, 0.5);
  hgenmusmatched = book<TH1D>("genmusmatched", ";binc = total N_{matched gen #mu}; Events / bin", 1, -0.5, 0.5);
  hptgenmu = book<TH1D>("ptgenmu", ";p_{T}^{gen #mu} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmu_rebin = book<TH1D>("ptgenmu_rebin", ";p_{T}^{gen #mu} [GeV]; Events / bin", 50, 0, 200);
  hptgenmu_rebin2 = book<TH1D>("ptgenmu_rebin2", ";p_{T}^{gen #mu} [GeV]; Events / bin", 50, 0, 50);
  hptgenmumatched = book<TH1D>("ptgenmumatched", ";p_{T}^{gen and matched #mu} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmumatched_rebin = book<TH1D>("ptgenmumatched_rebin", ";p_{T}^{gen and matched #mu} [GeV]; Events / bin", 50, 0, 200);
  hptgenmumatched_rebin2 = book<TH1D>("ptgenmumatched_rebin2", ";p_{T}^{gen and matched #mu} [GeV]; Events / bin", 50, 0, 50);
  hdrminmu = book<TH1D>("drminmu", ";#DeltaR(gen #mu, reco #mu) [GeV]; Events / bin", 60, 0, 3);
  hgenmuorigin = book<TH1D>("genmuorigin", ";#mu -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenmu1 = book<TH1D>("ptgenmu1", ";p_{T}^{gen #mu 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmu1_rebin = book<TH1D>("ptgenmu1_rebin", ";p_{T}^{gen #mu 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenmu1_rebin2 = book<TH1D>("ptgenmu1_rebin2", ";p_{T}^{gen #mu 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenmu1matched = book<TH1D>("ptgenmu1matched", ";p_{T}^{gen and matched #mu 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmu1matched_rebin = book<TH1D>("ptgenmu1matched_rebin", ";p_{T}^{gen and matched #mu 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenmu1matched_rebin2 = book<TH1D>("ptgenmu1matched_rebin2", ";p_{T}^{gen and matched #mu 1} [GeV]; Events / bin", 50, 0, 50);
  hdrminmu1 = book<TH1D>("drminmu1", ";#DeltaR(gen #mu 1, reco #mu) [GeV]; Events / bin", 60, 0, 3);
  hgenmu1origin = book<TH1D>("genmu1origin", ";#mu 1 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenmu2 = book<TH1D>("ptgenmu2", ";p_{T}^{gen #mu 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmu2_rebin = book<TH1D>("ptgenmu2_rebin", ";p_{T}^{gen #mu 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenmu2_rebin2 = book<TH1D>("ptgenmu2_rebin2", ";p_{T}^{gen #mu 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenmu2matched = book<TH1D>("ptgenmu2matched", ";p_{T}^{gen and matched #mu 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmu2matched_rebin = book<TH1D>("ptgenmu2matched_rebin", ";p_{T}^{gen and matched #mu 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenmu2matched_rebin2 = book<TH1D>("ptgenmu2matched_rebin2", ";p_{T}^{gen and matched #mu 2} [GeV]; Events / bin", 50, 0, 50);
  hdrminmu2 = book<TH1D>("drminmu2", ";#DeltaR(gen #mu 2, reco #mu) [GeV]; Events / bin", 60, 0, 3);
  hgenmu2origin = book<TH1D>("genmu2origin", ";#mu 2 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);

  hgenmusfromtautotal = book<TH1D>("genmusfromtautotal", ";binc = N_{gen #mu from #tau}; Events / bin", 1, -0.5, 0.5);
  hgenmusfromtaumatched = book<TH1D>("genmusfromtaumatched", ";binc = N_{matched gen #mu from #tau}; Events / bin", 1, -0.5, 0.5);
  hptgenmufromtau = book<TH1D>("ptgenmufromtau", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromtau_rebin = book<TH1D>("ptgenmufromtau_rebin", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromtau_rebin2 = book<TH1D>("ptgenmufromtau_rebin2", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 50, 0, 50);
  hptgenmufromtaumatched = book<TH1D>("ptgenmufromtaumatched", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromtaumatched_rebin = book<TH1D>("ptgenmufromtaumatched_rebin", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromtaumatched_rebin2 = book<TH1D>("ptgenmufromtaumatched_rebin2", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 50, 0, 50);




  hngenels = book<TH1D>("ngenels", ";N_{gen e}; Events / bin", 11, -0.5, 10.5);
  hngenelsmatched = book<TH1D>("ngenelsmatched", ";N_{matched gen e}; Events / bin", 11, -0.5, 10.5);
  hgenelstotal = book<TH1D>("genelstotal", ";binc = total N_{gen e}; Events / bin", 1, -0.5, 0.5);
  hgenelsmatched = book<TH1D>("genelsmatched", ";binc = total N_{matched gen e}; Events / bin", 1, -0.5, 0.5);
  hptgenel = book<TH1D>("ptgenel", ";p_{T}^{gen e} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel_rebin = book<TH1D>("ptgenel_rebin", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 200);
  hptgenel_rebin2 = book<TH1D>("ptgenel_rebin2", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 50);
  hptgenelmatched = book<TH1D>("ptgenelmatched", ";p_{T}^{gen and matched e} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelmatched_rebin = book<TH1D>("ptgenelmatched_rebin", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 200);
  hptgenelmatched_rebin2 = book<TH1D>("ptgenelmatched_rebin2", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 50);
  hdrminel = book<TH1D>("drminel", ";#DeltaR(gen e, reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenelorigin = book<TH1D>("genelorigin", ";e -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenel1 = book<TH1D>("ptgenel1", ";p_{T}^{gen e 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel1_rebin = book<TH1D>("ptgenel1_rebin", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenel1_rebin2 = book<TH1D>("ptgenel1_rebin2", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenel1matched = book<TH1D>("ptgenel1matched", ";p_{T}^{gen and matched e 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel1matched_rebin = book<TH1D>("ptgenel1matched_rebin", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenel1matched_rebin2 = book<TH1D>("ptgenel1matched_rebin2", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 50);
  hdrminel1 = book<TH1D>("drminel1", ";#DeltaR(gen e 1, closest reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenel1origin = book<TH1D>("genel1origin", ";e 1 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenel2 = book<TH1D>("ptgenel2", ";p_{T}^{gen e 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel2_rebin = book<TH1D>("ptgenel2_rebin", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenel2_rebin2 = book<TH1D>("ptgenel2_rebin2", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenel2matched = book<TH1D>("ptgenel2matched", ";p_{T}^{gen and matched e 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel2matched_rebin = book<TH1D>("ptgenel2matched_rebin", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenel2matched_rebin2 = book<TH1D>("ptgenel2matched_rebin2", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 50);
  hdrminel2 = book<TH1D>("drminel2", ";#DeltaR(gen e 2, closest reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenel2origin = book<TH1D>("genel2origin", ";e 2 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);

  hgenelsfromtautotal = book<TH1D>("genelsfromtautotal", ";binc = total N_{gen e from #tau}; Events / bin", 1, -0.5, 0.5);
  hgenelsfromtaumatched = book<TH1D>("genelsfromtaumatched", ";binc = total N_{matched gen e from #tau}; Events / bin", 1, -0.5, 0.5);
  hptgenelfromtau = book<TH1D>("ptgenelfromtau", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromtau_rebin = book<TH1D>("ptgenelfromtau_rebin", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromtau_rebin2 = book<TH1D>("ptgenelfromtau_rebin2", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 50);
  hptgenelfromtaumatched = book<TH1D>("ptgenelfromtaumatched", ";p_{T}^{gen and matched e from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromtaumatched_rebin = book<TH1D>("ptgenelfromtaumatched_rebin", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromtaumatched_rebin2 = book<TH1D>("ptgenelfromtaumatched_rebin2", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 50);

}

void GenParticleHists::fill(const RecoEvent & event){
  if(event.is_data) return;
  double weight = event.weight;

  // loop through gen vis. taus
  int idx_gvt = 0;
  int n_genvistausmatched = 0;
  for(const GenParticle & gvt : *event.genparticles_visibletaus){

    auto closest_tau = closestParticle(gvt, *event.taus);
    float dr_min = -1.;
    if(closest_tau != nullptr) dr_min = deltaR(gvt, *closest_tau);

    hgenvistaustotal->Fill(0., weight);
    hptgenvistau->Fill(gvt.pt(), weight);
    hptgenvistau_rebin->Fill(gvt.pt(), weight);
    hptgenvistau_rebin2->Fill(gvt.pt(), weight);
    if(dr_min < 0.1 && dr_min > 0.){
      n_genvistausmatched ++;
      hgenvistausmatched->Fill(0., weight);
      hptgenvistaumatched->Fill(gvt.pt(), weight);
      hptgenvistaumatched_rebin->Fill(gvt.pt(), weight);
      hptgenvistaumatched_rebin2->Fill(gvt.pt(), weight);
    }
    hgenvistaudecaymode->Fill(gvt.status(), weight);
    hdrmintau->Fill(dr_min, weight);

    if(idx_gvt == 0){
      hptgenvistau1->Fill(gvt.pt(), weight);
      hptgenvistau1_rebin->Fill(gvt.pt(), weight);
      hptgenvistau1_rebin2->Fill(gvt.pt(), weight);
      if(dr_min < 0.1 && dr_min > 0.){
        hptgenvistau1matched->Fill(gvt.pt(), weight);
        hptgenvistau1matched_rebin->Fill(gvt.pt(), weight);
        hptgenvistau1matched_rebin2->Fill(gvt.pt(), weight);
      }
      hgenvistau1decaymode->Fill(gvt.status(), weight);
      hdrmintau1->Fill(dr_min, weight);
    }
    else if(idx_gvt == 1){
      hptgenvistau2->Fill(gvt.pt(), weight);
      hptgenvistau2_rebin->Fill(gvt.pt(), weight);
      hptgenvistau2_rebin2->Fill(gvt.pt(), weight);
      if(dr_min < 0.1 && dr_min > 0.){
        hptgenvistau2matched->Fill(gvt.pt(), weight);
        hptgenvistau2matched_rebin->Fill(gvt.pt(), weight);
        hptgenvistau2matched_rebin2->Fill(gvt.pt(), weight);
      }
      hgenvistau2decaymode->Fill(gvt.status(), weight);
      hdrmintau2->Fill(dr_min, weight);
    }
    idx_gvt++;
  }
  hngenvistaus->Fill(event.genparticles_visibletaus->size(), weight);
  hngenvistausmatched->Fill(n_genvistausmatched, weight);


  // loop through all hard genparticles
  double pt_tau1 = 0;
  double pt_tau2 = 0;
  int n_gentaus = 0;
  int n_genmus = 0;
  int n_genmusmatched = 0;
  int n_genels = 0;
  int n_genelsmatched = 0;
  for(const GenParticle & gp : *event.genparticles_all){

    int id = abs(gp.pdgid());
    if(id != 11 && id != 13 && id != 15) continue;
    if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;

    if(id == 15){ // taus
      n_gentaus++;
      if(gp.pt() > pt_tau1){
        pt_tau2 = pt_tau1;
        pt_tau1 = gp.pt();
      }
      else if(gp.pt() > pt_tau2) pt_tau2 = gp.pt();
    }
    else if(id == 13){ // muons
      n_genmus++;
      hgenmustotal->Fill(0., weight);

      auto closest_mu = closestParticle(gp, *event.muons);
      float dr_min = -1.;
      if(closest_mu != nullptr) dr_min = deltaR(gp, *closest_mu);
      int origin = 0.;
      if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)) origin = 1.;
      else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)) origin = 2.;

      if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)){
        hgenmusfromtautotal->Fill(0., weight);
        hptgenmufromtau->Fill(gp.pt(), weight);
        hptgenmufromtau_rebin->Fill(gp.pt(), weight);
        hptgenmufromtau_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hgenmusfromtaumatched->Fill(0., weight);
          hptgenmufromtaumatched->Fill(gp.pt(), weight);
          hptgenmufromtaumatched_rebin->Fill(gp.pt(), weight);
          hptgenmufromtaumatched_rebin2->Fill(gp.pt(), weight);
        }
      }

      hptgenmu->Fill(gp.pt(), weight);
      hptgenmu_rebin->Fill(gp.pt(), weight);
      hptgenmu_rebin2->Fill(gp.pt(), weight);
      if(dr_min < 0.1 && dr_min > 0.){
        n_genmusmatched++;
        hgenmusmatched->Fill(0., weight);
        hptgenmumatched->Fill(gp.pt(), weight);
        hptgenmumatched_rebin->Fill(gp.pt(), weight);
        hptgenmumatched_rebin2->Fill(gp.pt(), weight);
      }
      hdrminmu->Fill(dr_min, weight);
      hgenmuorigin->Fill(origin, weight);

      if(n_genmus == 1){
        hptgenmu1->Fill(gp.pt(), weight);
        hptgenmu1_rebin->Fill(gp.pt(), weight);
        hptgenmu1_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hptgenmu1matched->Fill(gp.pt(), weight);
          hptgenmu1matched_rebin->Fill(gp.pt(), weight);
          hptgenmu1matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminmu1->Fill(dr_min, weight);
        hgenmu1origin->Fill(origin, weight);
      }
      else if(n_genmus == 2){
        hptgenmu2->Fill(gp.pt(), weight);
        hptgenmu2_rebin->Fill(gp.pt(), weight);
        hptgenmu2_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hptgenmu2matched->Fill(gp.pt(), weight);
          hptgenmu2matched_rebin->Fill(gp.pt(), weight);
          hptgenmu2matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminmu2->Fill(dr_min, weight);
        hgenmu2origin->Fill(origin, weight);
      }
    }
    else if(id == 11){ // electrons
      n_genels++;
      hgenelstotal->Fill(0., weight);

      const Electron* closest_el = closestParticle(gp, *event.electrons);
      float dr_min = -1.;
      if(closest_el != nullptr) dr_min = deltaR(gp, *closest_el);
      int origin = 0.;
      if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)) origin = 1.;
      else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)) origin = 2.;

      if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)){
        hgenelsfromtautotal->Fill(0., weight);
        hptgenelfromtau->Fill(gp.pt(), weight);
        hptgenelfromtau_rebin->Fill(gp.pt(), weight);
        hptgenelfromtau_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hgenelsfromtaumatched->Fill(0., weight);
          hptgenelfromtaumatched->Fill(gp.pt(), weight);
          hptgenelfromtaumatched_rebin->Fill(gp.pt(), weight);
          hptgenelfromtaumatched_rebin2->Fill(gp.pt(), weight);
        }
      }

      hptgenel->Fill(gp.pt(), weight);
      hptgenel_rebin->Fill(gp.pt(), weight);
      hptgenel_rebin2->Fill(gp.pt(), weight);
      if(dr_min < 0.1 && dr_min > 0.){
        n_genelsmatched++;
        hgenelsmatched->Fill(0., weight);
        hptgenelmatched->Fill(gp.pt(), weight);
        hptgenelmatched_rebin->Fill(gp.pt(), weight);
        hptgenelmatched_rebin2->Fill(gp.pt(), weight);
      }
      hdrminel->Fill(dr_min, weight);
      hgenelorigin->Fill(origin, weight);

      if(n_genels == 1){
        hptgenel1->Fill(gp.pt(), weight);
        hptgenel1_rebin->Fill(gp.pt(), weight);
        hptgenel1_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hptgenel1matched->Fill(gp.pt(), weight);
          hptgenel1matched_rebin->Fill(gp.pt(), weight);
          hptgenel1matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminel1->Fill(dr_min, weight);
        hgenel1origin->Fill(origin, weight);
      }
      else if(n_genels == 2){
        hptgenel2->Fill(gp.pt(), weight);
        hptgenel2_rebin->Fill(gp.pt(), weight);
        hptgenel2_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.1 && dr_min > 0.){
          hptgenel2matched->Fill(gp.pt(), weight);
          hptgenel2matched_rebin->Fill(gp.pt(), weight);
          hptgenel2matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminel2->Fill(dr_min, weight);
        hgenel2origin->Fill(origin, weight);
      }
    }

  }

  hngenmus->Fill(n_genmus, weight);
  hngenmusmatched->Fill(n_genmusmatched, weight);
  hngenels->Fill(n_genels, weight);
  hngenelsmatched->Fill(n_genelsmatched, weight);

  hngentaus->Fill(n_gentaus, weight);
  hptgentau1->Fill(pt_tau1, weight);
  hptgentau2->Fill(pt_tau2, weight);
  hptgentau1_rebin->Fill(pt_tau1, weight);
  hptgentau2_rebin->Fill(pt_tau2, weight);
  hptgentau1_rebin2->Fill(pt_tau1, weight);
  hptgentau2_rebin2->Fill(pt_tau2, weight);
  hptgentau1_rebin3->Fill(pt_tau1, weight);
  hptgentau2_rebin3->Fill(pt_tau2, weight);
  hptgentau1_rebin4->Fill(pt_tau1, weight);
  hptgentau2_rebin4->Fill(pt_tau2, weight);


}
