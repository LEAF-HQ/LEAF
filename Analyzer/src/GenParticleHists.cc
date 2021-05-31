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
  hdrgenditau = book<TH1D>("drgenditau", ";#DeltaR(gen #tau i, gen #tau j); Events / bin", 200, 0, 10);
  hdphigenditau = book<TH1D>("dphigenditau", ";#Delta#Phi(gen #tau i, gen #tau j); Events / bin", 35, 0, 3.5);
  hdetagenditau = book<TH1D>("detagenditau", ";#Delta#eta(gen #tau i, gen #tau j); Events / bin", 100, 0, 10);
  hdrgentaumu = book<TH1D>("drgentaumu", ";#DeltaR(gen #tau i, #mu j); Events / bin", 200, 0, 10);
  hdphigentaumu = book<TH1D>("dphigentaumu", ";#Delta#Phi(gen #tau i, #mu j); Events / bin", 35, 0, 3.5);
  hdetagentaumu = book<TH1D>("detagentaumu", ";#Delta#eta(gen #tau i, #mu j); Events / bin", 100, 0, 10);
  hdrgentaue = book<TH1D>("drgentaue", ";#DeltaR(gen #tau i, e j); Events / bin", 200, 0, 10);
  hdphigentaue = book<TH1D>("dphigentaue", ";#Delta#Phi(gen #tau i, e j); Events / bin", 35, 0, 3.5);
  hdetagentaue = book<TH1D>("detagentaue", ";#Delta#eta(gen #tau i, e j); Events / bin", 100, 0, 10);


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
  hgenvistaudecaymode = book<TH1D>("genvistaudecaymode", ";vis. #tau decaymode ; Events / bin", 16, -0.5, 15.5);
  hptgenvistau1 = book<TH1D>("ptgenvistau1", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau1_rebin = book<TH1D>("ptgenvistau1_rebin", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau1_rebin2 = book<TH1D>("ptgenvistau1_rebin2", ";p_{T}^{gen vis. #tau 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenvistau1matched = book<TH1D>("ptgenvistau1matched", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau1matched_rebin = book<TH1D>("ptgenvistau1matched_rebin", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau1matched_rebin2 = book<TH1D>("ptgenvistau1matched_rebin2", ";p_{T}^{gen and matched vis. #tau 1} [GeV]; Events / bin", 50, 0, 50);
  hdrmintau1 = book<TH1D>("drmintau1", ";#DeltaR(gen vis. #tau 1, reco #tau) [GeV]; Events / bin", 60, 0, 3);
  hgenvistau1decaymode = book<TH1D>("genvistau1decaymode", ";vis. #tau 1 decaymode ; Events / bin", 16, -0.5, 15.5);
  hptgenvistau2 = book<TH1D>("ptgenvistau2", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau2_rebin = book<TH1D>("ptgenvistau2_rebin", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau2_rebin2 = book<TH1D>("ptgenvistau2_rebin2", ";p_{T}^{gen vis. #tau 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenvistau2matched = book<TH1D>("ptgenvistau2matched", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenvistau2matched_rebin = book<TH1D>("ptgenvistau2matched_rebin", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenvistau2matched_rebin2 = book<TH1D>("ptgenvistau2matched_rebin2", ";p_{T}^{gen and matched vis. #tau 2} [GeV]; Events / bin", 50, 0, 50);
  hdrmintau2 = book<TH1D>("drmintau2", ";#DeltaR(gen vis. #tau 2, reco #tau) [GeV]; Events / bin", 60, 0, 3);
  hgenvistau2decaymode = book<TH1D>("genvistau2decaymode", ";vis. #tau 2 decaymode ; Events / bin", 16, -0.5, 15.5);
  hdrgenvisditau = book<TH1D>("drgenvisditau", ";#DeltaR(gen vis. #tau i, gen vis. #tau j); Events / bin", 200, 0, 10);
  hdphigenvisditau = book<TH1D>("dphigenvisditau", ";#Delta#Phi(gen vis. #tau i, gen vis. #tau j); Events / bin", 35, 0, 3.5);
  hdetagenvisditau = book<TH1D>("detagenvisditau", ";#Delta#eta(gen vis. #tau i, gen vis. #tau j); Events / bin", 100, 0, 10);
  hdrgenvistaumu = book<TH1D>("drgenvistaumu", ";#DeltaR(gen vis. #tau i, #mu j); Events / bin", 200, 0, 10);
  hdphigenvistaumu = book<TH1D>("dphigenvistaumu", ";#Delta#Phi(gen vis. #tau i, #mu j); Events / bin", 35, 0, 3.5);
  hdetagenvistaumu = book<TH1D>("detagenvistaumu", ";#Delta#eta(gen vis. #tau i, #mu j); Events / bin", 100, 0, 10);
  hdrgenvistaue = book<TH1D>("drgenvistaue", ";#DeltaR(gen vis. #tau i, e j); Events / bin", 200, 0, 10);
  hdphigenvistaue = book<TH1D>("dphigenvistaue", ";#Delta#Phi(gen vis. #tau i, e j); Events / bin", 35, 0, 3.5);
  hdetagenvistaue = book<TH1D>("detagenvistaue", ";#Delta#eta(gen vis. #tau i, e j); Events / bin", 100, 0, 10);


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
  hdrgendimu = book<TH1D>("drgendimu", ";#DeltaR(gen #mu i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigendimu = book<TH1D>("dphigendimu", ";#Delta#Phi(gen #mu i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagendimu = book<TH1D>("detagendimu", ";#Delta#eta(gen #mu i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenmuvistau = book<TH1D>("drgenmuvistau", ";#DeltaR(gen #mu i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenmuvistau = book<TH1D>("dphigenmuvistau", ";#Delta#Phi(gen #mu i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenmuvistau = book<TH1D>("detagenmuvistau", ";#Delta#eta(gen #mu i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenmue = book<TH1D>("drgenmue", ";#DeltaR(gen #mu i, gen e j); Events / bin", 200, 0, 10);
  hdphigenmue = book<TH1D>("dphigenmue", ";#Delta#Phi(gen #mu i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenmue = book<TH1D>("detagenmue", ";#Delta#eta(gen #mu i, gen e j); Events / bin", 100, 0, 10);

  hgenmusfromtautotal = book<TH1D>("genmusfromtautotal", ";binc = N_{gen #mu from #tau}; Events / bin", 1, -0.5, 0.5);
  hgenmusfromtaumatched = book<TH1D>("genmusfromtaumatched", ";binc = N_{matched gen #mu from #tau}; Events / bin", 1, -0.5, 0.5);
  hptgenmufromtau = book<TH1D>("ptgenmufromtau", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromtau_rebin = book<TH1D>("ptgenmufromtau_rebin", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromtau_rebin2 = book<TH1D>("ptgenmufromtau_rebin2", ";p_{T}^{gen #mu from #tau} [GeV]; Events / bin", 50, 0, 50);
  hptgenmufromtaumatched = book<TH1D>("ptgenmufromtaumatched", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromtaumatched_rebin = book<TH1D>("ptgenmufromtaumatched_rebin", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromtaumatched_rebin2 = book<TH1D>("ptgenmufromtaumatched_rebin2", ";p_{T}^{gen and matched #mu from #tau} [GeV]; Events / bin", 50, 0, 50);
  hdrgendimufromtau = book<TH1D>("drgendimufromtau", ";#DeltaR(gen #mu from #tau i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigendimufromtau = book<TH1D>("dphigendimufromtau", ";#Delta#Phi(gen #mu from #tau i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagendimufromtau = book<TH1D>("detagendimufromtau", ";#Delta#eta(gen #mu from #tau i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenmufromtauvistau = book<TH1D>("drgenmufromtauvistau", ";#DeltaR(gen #mu from #tau i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenmufromtauvistau = book<TH1D>("dphigenmufromtauvistau", ";#Delta#Phi(gen #mu from #tau i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenmufromtauvistau = book<TH1D>("detagenmufromtauvistau", ";#Delta#eta(gen #mu from #tau i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenmufromtaue = book<TH1D>("drgenmufromtaue", ";#DeltaR(gen #mu from #tau i, gen e j); Events / bin", 200, 0, 10);
  hdphigenmufromtaue = book<TH1D>("dphigenmufromtaue", ";#Delta#Phi(gen #mu from #tau i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenmufromtaue = book<TH1D>("detagenmufromtaue", ";#Delta#eta(gen #mu from #tau i, gen e j); Events / bin", 100, 0, 10);

  hgenmusfromhadtotal = book<TH1D>("genmusfromhadtotal", ";binc = N_{gen #mu from had}; Events / bin", 1, -0.5, 0.5);
  hgenmusfromhadmatched = book<TH1D>("genmusfromhadmatched", ";binc = N_{matched gen #mu from had}; Events / bin", 1, -0.5, 0.5);
  hptgenmufromhad = book<TH1D>("ptgenmufromhad", ";p_{T}^{gen #mu from had} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromhad_rebin = book<TH1D>("ptgenmufromhad_rebin", ";p_{T}^{gen #mu from had} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromhad_rebin2 = book<TH1D>("ptgenmufromhad_rebin2", ";p_{T}^{gen #mu from had} [GeV]; Events / bin", 50, 0, 50);
  hptgenmufromhadmatched = book<TH1D>("ptgenmufromhadmatched", ";p_{T}^{gen and matched #mu from had} [GeV]; Events / bin", 40, 0, 1200);
  hptgenmufromhadmatched_rebin = book<TH1D>("ptgenmufromhadmatched_rebin", ";p_{T}^{gen and matched #mu from had} [GeV]; Events / bin", 50, 0, 200);
  hptgenmufromhadmatched_rebin2 = book<TH1D>("ptgenmufromhadmatched_rebin2", ";p_{T}^{gen and matched #mu from had} [GeV]; Events / bin", 50, 0, 50);
  hdrgendimufromhad = book<TH1D>("drgendimufromhad", ";#DeltaR(gen #mu from had i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigendimufromhad = book<TH1D>("dphigendimufromhad", ";#Delta#Phi(gen #mu from had i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagendimufromhad = book<TH1D>("detagendimufromhad", ";#Delta#eta(gen #mu from had i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenmufromhadvistau = book<TH1D>("drgenmufromhadvistau", ";#DeltaR(gen #mu from had i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenmufromhadvistau = book<TH1D>("dphigenmufromhadvistau", ";#Delta#Phi(gen #mu from had i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenmufromhadvistau = book<TH1D>("detagenmufromhadvistau", ";#Delta#eta(gen #mu from had i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenmufromhade = book<TH1D>("drgenmufromhade", ";#DeltaR(gen #mu from had i, gen e j); Events / bin", 200, 0, 10);
  hdphigenmufromhade = book<TH1D>("dphigenmufromhade", ";#Delta#Phi(gen #mu from had i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenmufromhade = book<TH1D>("detagenmufromhade", ";#Delta#eta(gen #mu from had i, gen e j); Events / bin", 100, 0, 10);




  hngenels = book<TH1D>("ngenels", ";N_{gen e}; Events / bin", 11, -0.5, 10.5);
  hngenelsmatched = book<TH1D>("ngenelsmatched", ";N_{matched gen e}; Events / bin", 11, -0.5, 10.5);
  hgenelstotal = book<TH1D>("genelstotal", ";binc = total N_{gen e}; Events / bin", 1, -0.5, 0.5);
  hgenelsmatched = book<TH1D>("genelsmatched", ";binc = total N_{matched gen e}; Events / bin", 1, -0.5, 0.5);
  hptgenel = book<TH1D>("ptgenel", ";p_{T}^{gen e} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel_rebin = book<TH1D>("ptgenel_rebin", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 200);
  hptgenel_rebin2 = book<TH1D>("ptgenel_rebin2", ";p_{T}^{gen e} [GeV]; Events / bin", 50, 0, 50);
  hptgenelmatched = book<TH1D>("ptgenelmatched", ";p_{T}^{gen and matched e} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelmatched_rebin = book<TH1D>("ptgenelmatched_rebin", ";p_{T}^{gen and matched e} [GeV]; Events / bin", 50, 0, 200);
  hptgenelmatched_rebin2 = book<TH1D>("ptgenelmatched_rebin2", ";p_{T}^{gen and matched e} [GeV]; Events / bin", 50, 0, 50);
  hdrminel = book<TH1D>("drminel", ";#DeltaR(gen e, reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenelorigin = book<TH1D>("genelorigin", ";e -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenel1 = book<TH1D>("ptgenel1", ";p_{T}^{gen e 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel1_rebin = book<TH1D>("ptgenel1_rebin", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenel1_rebin2 = book<TH1D>("ptgenel1_rebin2", ";p_{T}^{gen e 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenel1matched = book<TH1D>("ptgenel1matched", ";p_{T}^{gen and matched e 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel1matched_rebin = book<TH1D>("ptgenel1matched_rebin", ";p_{T}^{gen and matched e 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenel1matched_rebin2 = book<TH1D>("ptgenel1matched_rebin2", ";p_{T}^{gen and matched e 1} [GeV]; Events / bin", 50, 0, 50);
  hdrminel1 = book<TH1D>("drminel1", ";#DeltaR(gen e 1, closest reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenel1origin = book<TH1D>("genel1origin", ";e 1 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenel2 = book<TH1D>("ptgenel2", ";p_{T}^{gen e 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel2_rebin = book<TH1D>("ptgenel2_rebin", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenel2_rebin2 = book<TH1D>("ptgenel2_rebin2", ";p_{T}^{gen e 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenel2matched = book<TH1D>("ptgenel2matched", ";p_{T}^{gen and matched e 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenel2matched_rebin = book<TH1D>("ptgenel2matched_rebin", ";p_{T}^{gen and matched e 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenel2matched_rebin2 = book<TH1D>("ptgenel2matched_rebin2", ";p_{T}^{gen and matched e 2} [GeV]; Events / bin", 50, 0, 50);
  hdrminel2 = book<TH1D>("drminel2", ";#DeltaR(gen e 2, closest reco e) [GeV]; Events / bin", 60, 0, 3);
  hgenel2origin = book<TH1D>("genel2origin", ";e 2 -- 1: from hard #tau, 2: from hadron, 0: else ; Events / bin", 3, -0.5, 2.5);
  hdrgendie = book<TH1D>("drgendie", ";#DeltaR(gen e i, gen e j); Events / bin", 200, 0, 10);
  hdphigendie = book<TH1D>("dphigendie", ";#Delta#Phi(gen e i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagendie = book<TH1D>("detagendie", ";#Delta#eta(gen e i, gen e j); Events / bin", 100, 0, 10);
  hdrgenevistau = book<TH1D>("drgenevistau", ";#DeltaR(gen e i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenevistau = book<TH1D>("dphigenevistau", ";#Delta#Phi(gen e i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenevistau = book<TH1D>("detagenevistau", ";#Delta#eta(gen e i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenemu = book<TH1D>("drgenemu", ";#DeltaR(gen e i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenemu = book<TH1D>("dphigenemu", ";#Delta#Phi(gen e i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenemu = book<TH1D>("detagenemu", ";#Delta#eta(gen e i, gen #mu j); Events / bin", 100, 0, 10);

  hgenelsfromtautotal = book<TH1D>("genelsfromtautotal", ";binc = total N_{gen e from #tau}; Events / bin", 1, -0.5, 0.5);
  hgenelsfromtaumatched = book<TH1D>("genelsfromtaumatched", ";binc = total N_{matched gen e from #tau}; Events / bin", 1, -0.5, 0.5);
  hptgenelfromtau = book<TH1D>("ptgenelfromtau", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromtau_rebin = book<TH1D>("ptgenelfromtau_rebin", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromtau_rebin2 = book<TH1D>("ptgenelfromtau_rebin2", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 50);
  hptgenelfromtaumatched = book<TH1D>("ptgenelfromtaumatched", ";p_{T}^{gen and matched e from #tau} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromtaumatched_rebin = book<TH1D>("ptgenelfromtaumatched_rebin", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromtaumatched_rebin2 = book<TH1D>("ptgenelfromtaumatched_rebin2", ";p_{T}^{gen e from #tau} [GeV]; Events / bin", 50, 0, 50);
  hdrgendiefromtau = book<TH1D>("drgendiefromtau", ";#DeltaR(gen #e from #tau i, gen e j); Events / bin", 200, 0, 10);
  hdphigendiefromtau = book<TH1D>("dphigendiefromtau", ";#Delta#Phi(gen e from #tau i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagendiefromtau = book<TH1D>("detagendiefromtau", ";#Delta#eta(gen e from #tau i, gen e j); Events / bin", 100, 0, 10);
  hdrgenefromtauvistau = book<TH1D>("drgenefromtauvistau", ";#DeltaR(gen e from #tau i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenefromtauvistau = book<TH1D>("dphigenefromtauvistau", ";#Delta#Phi(gen e from #tau i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenefromtauvistau = book<TH1D>("detagenefromtauvistau", ";#Delta#eta(gen e from #tau i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenefromtaumu = book<TH1D>("drgenefromtaumu", ";#DeltaR(gen e from #tau i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenefromtaumu = book<TH1D>("dphigenefromtaumu", ";#Delta#Phi(gen e from #tau i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenefromtaumu = book<TH1D>("detagenefromtaumu", ";#Delta#eta(gen e from #tau i, gen #mu j); Events / bin", 100, 0, 10);

  hgenelsfromhadtotal = book<TH1D>("genelsfromhadtotal", ";binc = total N_{gen e from had}; Events / bin", 1, -0.5, 0.5);
  hgenelsfromhadmatched = book<TH1D>("genelsfromhadmatched", ";binc = total N_{matched gen e from had}; Events / bin", 1, -0.5, 0.5);
  hptgenelfromhad = book<TH1D>("ptgenelfromhad", ";p_{T}^{gen e from had} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromhad_rebin = book<TH1D>("ptgenelfromhad_rebin", ";p_{T}^{gen e from had} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromhad_rebin2 = book<TH1D>("ptgenelfromhad_rebin2", ";p_{T}^{gen e from had} [GeV]; Events / bin", 50, 0, 50);
  hptgenelfromhadmatched = book<TH1D>("ptgenelfromhadmatched", ";p_{T}^{gen and matched e from had} [GeV]; Events / bin", 40, 0, 1200);
  hptgenelfromhadmatched_rebin = book<TH1D>("ptgenelfromhadmatched_rebin", ";p_{T}^{gen e from had} [GeV]; Events / bin", 50, 0, 200);
  hptgenelfromhadmatched_rebin2 = book<TH1D>("ptgenelfromhadmatched_rebin2", ";p_{T}^{gen e from had} [GeV]; Events / bin", 50, 0, 50);
  hdrgendiefromhad = book<TH1D>("drgendiefromhad", ";#DeltaR(gen e from had i, gen e j); Events / bin", 200, 0, 10);
  hdphigendiefromhad = book<TH1D>("dphigendiefromhad", ";#Delta#Phi(gen e from had i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagendiefromhad = book<TH1D>("detagendiefromhad", ";#Delta#eta(gen e from had i, gen e j); Events / bin", 100, 0, 10);
  hdrgenefromhadvistau = book<TH1D>("drgenefromhadvistau", ";#DeltaR(gen e from had i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenefromhadvistau = book<TH1D>("dphigenefromhadvistau", ";#Delta#Phi(gen e from had i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenefromhadvistau = book<TH1D>("detagenefromhadvistau", ";#Delta#eta(gen e from had i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenefromhadmu = book<TH1D>("drgenefromhadmu", ";#DeltaR(gen e from had i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenefromhadmu = book<TH1D>("dphigenefromhadmu", ";#Delta#Phi(gen e from had i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenefromhadmu = book<TH1D>("detagenefromhadmu", ";#Delta#eta(gen e from had i, gen #mu j); Events / bin", 100, 0, 10);




  hngenbs = book<TH1D>("ngenbs", ";N_{gen b}; Events / bin", 11, -0.5, 10.5);
  hngenbsmatched = book<TH1D>("ngenbsmatched", ";N_{matched gen b}; Events / bin", 11, -0.5, 10.5);
  hgenbstotal = book<TH1D>("genbstotal", ";binc = total N_{gen b}; Events / bin", 1, -0.5, 0.5);
  hgenbsmatched = book<TH1D>("genbsmatched", ";binc = total N_{matched gen b}; Events / bin", 1, -0.5, 0.5);
  hptgenb = book<TH1D>("ptgenb", ";p_{T}^{gen b} [GeV]; Events / bin", 40, 0, 1200);
  hptgenb_rebin = book<TH1D>("ptgenb_rebin", ";p_{T}^{gen b} [GeV]; Events / bin", 50, 0, 200);
  hptgenb_rebin2 = book<TH1D>("ptgenb_rebin2", ";p_{T}^{gen b} [GeV]; Events / bin", 50, 0, 50);
  hptgenbmatched = book<TH1D>("ptgenbmatched", ";p_{T}^{gen and matched b} [GeV]; Events / bin", 40, 0, 1200);
  hptgenbmatched_rebin = book<TH1D>("ptgenbmatched_rebin", ";p_{T}^{gen and matched b} [GeV]; Events / bin", 50, 0, 200);
  hptgenbmatched_rebin2 = book<TH1D>("ptgenbmatched_rebin2", ";p_{T}^{gen and matched b} [GeV]; Events / bin", 50, 0, 50);
  hdrminb = book<TH1D>("drminb", ";#DeltaR(gen b, reco jet) [GeV]; Events / bin", 60, 0, 3);
  hgenborigin = book<TH1D>("genborigin", ";b -- 1: is hard proc., 2: from hard proc., 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenb1 = book<TH1D>("ptgenb1", ";p_{T}^{gen b 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenb1_rebin = book<TH1D>("ptgenb1_rebin", ";p_{T}^{gen b 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenb1_rebin2 = book<TH1D>("ptgenb1_rebin2", ";p_{T}^{gen b 1} [GeV]; Events / bin", 50, 0, 50);
  hptgenb1matched = book<TH1D>("ptgenb1matched", ";p_{T}^{gen and matched b 1} [GeV]; Events / bin", 40, 0, 1200);
  hptgenb1matched_rebin = book<TH1D>("ptgenb1matched_rebin", ";p_{T}^{gen and matched b 1} [GeV]; Events / bin", 50, 0, 200);
  hptgenb1matched_rebin2 = book<TH1D>("ptgenb1matched_rebin2", ";p_{T}^{gen and matched b 1} [GeV]; Events / bin", 50, 0, 50);
  hdrminb1 = book<TH1D>("drminb1", ";#DeltaR(gen b 1, closest reco jet) [GeV]; Events / bin", 60, 0, 3);
  hgenb1origin = book<TH1D>("genb1origin", ";b 1 -- 1: is hard proc., 2: from hard proc., 0: else ; Events / bin", 3, -0.5, 2.5);
  hptgenb2 = book<TH1D>("ptgenb2", ";p_{T}^{gen b 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenb2_rebin = book<TH1D>("ptgenb2_rebin", ";p_{T}^{gen b 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenb2_rebin2 = book<TH1D>("ptgenb2_rebin2", ";p_{T}^{gen b 2} [GeV]; Events / bin", 50, 0, 50);
  hptgenb2matched = book<TH1D>("ptgenb2matched", ";p_{T}^{gen and matched b 2} [GeV]; Events / bin", 40, 0, 1200);
  hptgenb2matched_rebin = book<TH1D>("ptgenb2matched_rebin", ";p_{T}^{gen and matched b 2} [GeV]; Events / bin", 50, 0, 200);
  hptgenb2matched_rebin2 = book<TH1D>("ptgenb2matched_rebin2", ";p_{T}^{gen and matched b 2} [GeV]; Events / bin", 50, 0, 50);
  hdrminb2 = book<TH1D>("drminb2", ";#DeltaR(gen b 2, closest reco jet) [GeV]; Events / bin", 60, 0, 3);
  hgenb2origin = book<TH1D>("genb2origin", ";b 2 -- 1: is hard proc., 2: from hard proc., 0: else ; Events / bin", 3, -0.5, 2.5);
  hdrgendib = book<TH1D>("drgendib", ";#DeltaR(gen b i, gen b j); Events / bin", 200, 0, 10);
  hdphigendib = book<TH1D>("dphigendib", ";#Delta#Phi(gen b i, gen b j); Events / bin", 35, 0, 3.5);
  hdetagendib = book<TH1D>("detagendib", ";#Delta#eta(gen b i, gen b j); Events / bin", 100, 0, 10);
  hdrgenbvistau = book<TH1D>("drgenbvistau", ";#DeltaR(gen b i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenbvistau = book<TH1D>("dphigenbvistau", ";#Delta#Phi(gen b i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenbvistau = book<TH1D>("detagenbvistau", ";#Delta#eta(gen b i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenbmu = book<TH1D>("drgenbmu", ";#DeltaR(gen b i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenbmu = book<TH1D>("dphigenbmu", ";#Delta#Phi(gen b i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenbmu = book<TH1D>("detagenbmu", ";#Delta#eta(gen b i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenbe = book<TH1D>("drgenbe", ";#DeltaR(gen b i, gen e j); Events / bin", 200, 0, 10);
  hdphigenbe = book<TH1D>("dphigenbe", ";#Delta#Phi(gen b i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenbe = book<TH1D>("detagenbe", ";#Delta#eta(gen b i, gen e j); Events / bin", 100, 0, 10);

  hgenbsfromhardtotal = book<TH1D>("genbsfromhardtotal", ";binc = total N_{gen b from hard proc.}; Events / bin", 1, -0.5, 0.5);
  hgenbsfromhardmatched = book<TH1D>("genbsfromhardmatched", ";binc = total N_{matched gen b from hard proc.}; Events / bin", 1, -0.5, 0.5);
  hptgenbfromhard = book<TH1D>("ptgenbfromhard", ";p_{T}^{gen b from hard proc.} [GeV]; Events / bin", 40, 0, 1200);
  hptgenbfromhard_rebin = book<TH1D>("ptgenbfromhard_rebin", ";p_{T}^{gen b from hard proc.} [GeV]; Events / bin", 50, 0, 200);
  hptgenbfromhard_rebin2 = book<TH1D>("ptgenbfromhard_rebin2", ";p_{T}^{gen b from hard proc.} [GeV]; Events / bin", 50, 0, 50);
  hptgenbfromhardmatched = book<TH1D>("ptgenbfromhardmatched", ";p_{T}^{gen and matched b from hard proc.} [GeV]; Events / bin", 40, 0, 1200);
  hptgenbfromhardmatched_rebin = book<TH1D>("ptgenbfromhardmatched_rebin", ";p_{T}^{gen b from hard proc.} [GeV]; Events / bin", 50, 0, 200);
  hptgenbfromhardmatched_rebin2 = book<TH1D>("ptgenbfromhardmatched_rebin2", ";p_{T}^{gen b from hard proc.} [GeV]; Events / bin", 50, 0, 50);
  hdrgendibfromhard = book<TH1D>("drgendibfromhard", ";#DeltaR(gen b from hard proc. i, gen b from hard proc. j); Events / bin", 200, 0, 10);
  hdphigendibfromhard = book<TH1D>("dphigendibfromhard", ";#Delta#Phi(gen b from hard proc. i, gen b from hard proc. j); Events / bin", 35, 0, 3.5);
  hdetagendibfromhard = book<TH1D>("detagendibfromhard", ";#Delta#eta(gen b from hard proc. i, gen b from hard proc. j); Events / bin", 100, 0, 10);
  hdrgenbfromhardvistau = book<TH1D>("drgenbfromhardvistau", ";#DeltaR(gen b from hard proc. i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenbfromhardvistau = book<TH1D>("dphigenbfromhardvistau", ";#Delta#Phi(gen b from hard proc. i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenbfromhardvistau = book<TH1D>("detagenbfromhardvistau", ";#Delta#eta(gen b from hard proc. i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenbfromhardmu = book<TH1D>("drgenbfromhardmu", ";#DeltaR(gen b from hard proc. i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenbfromhardmu = book<TH1D>("dphigenbfromhardmu", ";#Delta#Phi(gen b from hard proc. i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenbfromhardmu = book<TH1D>("detagenbfromhardmu", ";#Delta#eta(gen b from hard proc. i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenbfromharde = book<TH1D>("drgenbfromharde", ";#DeltaR(gen b from hard proc. i, gen e j); Events / bin", 200, 0, 10);
  hdphigenbfromharde = book<TH1D>("dphigenbfromharde", ";#Delta#Phi(gen b from hard proc. i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenbfromharde = book<TH1D>("detagenbfromharde", ";#Delta#eta(gen b from hard proc. i, gen e j); Events / bin", 100, 0, 10);

  hgenbsnotfromhardtotal = book<TH1D>("genbsnotfromhardtotal", ";binc = total N_{gen b not from hard proc.}; Events / bin", 1, -0.5, 0.5);
  hgenbsnotfromhardmatched = book<TH1D>("genbsnotfromhardmatched", ";binc = total N_{matched gen b not from hard proc.}; Events / bin", 1, -0.5, 0.5);
  hptgenbnotfromhard = book<TH1D>("ptgenbnotfromhard", ";p_{T}^{gen b not from hard proc.} [GeV]; Events / bin", 40, 0, 1200);
  hptgenbnotfromhard_rebin = book<TH1D>("ptgenbnotfromhard_rebin", ";p_{T}^{gen b not from hard proc.} [GeV]; Events / bin", 50, 0, 200);
  hptgenbnotfromhard_rebin2 = book<TH1D>("ptgenbnotfromhard_rebin2", ";p_{T}^{gen b not from hard proc.} [GeV]; Events / bin", 50, 0, 50);
  hptgenbnotfromhardmatched = book<TH1D>("ptgenbnotfromhardmatched", ";p_{T}^{gen and matched b not from hard proc.} [GeV]; Events / bin", 40, 0, 1200);
  hptgenbnotfromhardmatched_rebin = book<TH1D>("ptgenbnotfromhardmatched_rebin", ";p_{T}^{gen b not from hard proc.} [GeV]; Events / bin", 50, 0, 200);
  hptgenbnotfromhardmatched_rebin2 = book<TH1D>("ptgenbnotfromhardmatched_rebin2", ";p_{T}^{gen b not from hard proc.} [GeV]; Events / bin", 50, 0, 50);
  hdrgendibnotfromhard = book<TH1D>("drgendibnotfromhard", ";#DeltaR(gen b not from hard proc. i, gen b not from hard proc. j); Events / bin", 200, 0, 10);
  hdphigendibnotfromhard = book<TH1D>("dphigendibnotfromhard", ";#Delta#Phi(gen b not from hard proc. i, gen b not from hard proc. j); Events / bin", 35, 0, 3.5);
  hdetagendibnotfromhard = book<TH1D>("detagendibnotfromhard", ";#Delta#eta(gen b not from hard proc. i, gen b not from hard proc. j); Events / bin", 100, 0, 10);
  hdrgenbnotfromhardvistau = book<TH1D>("drgenbnotfromhardvistau", ";#DeltaR(gen b not from hard proc. i, gen vis #tau j); Events / bin", 200, 0, 10);
  hdphigenbnotfromhardvistau = book<TH1D>("dphigenbnotfromhardvistau", ";#Delta#Phi(gen b not from hard proc. i, gen vis #tau j); Events / bin", 35, 0, 3.5);
  hdetagenbnotfromhardvistau = book<TH1D>("detagenbnotfromhardvistau", ";#Delta#eta(gen b not from hard proc. i, gen vis #tau j); Events / bin", 100, 0, 10);
  hdrgenbnotfromhardmu = book<TH1D>("drgenbnotfromhardmu", ";#DeltaR(gen b not from hard proc. i, gen #mu j); Events / bin", 200, 0, 10);
  hdphigenbnotfromhardmu = book<TH1D>("dphigenbnotfromhardmu", ";#Delta#Phi(gen b not from hard proc. i, gen #mu j); Events / bin", 35, 0, 3.5);
  hdetagenbnotfromhardmu = book<TH1D>("detagenbnotfromhardmu", ";#Delta#eta(gen b not from hard proc. i, gen #mu j); Events / bin", 100, 0, 10);
  hdrgenbnotfromharde = book<TH1D>("drgenbnotfromharde", ";#DeltaR(gen b not from hard proc. i, gen e j); Events / bin", 200, 0, 10);
  hdphigenbnotfromharde = book<TH1D>("dphigenbnotfromharde", ";#Delta#Phi(gen b not from hard proc. i, gen e j); Events / bin", 35, 0, 3.5);
  hdetagenbnotfromharde = book<TH1D>("detagenbnotfromharde", ";#Delta#eta(gen b not from hard proc. i, gen e j); Events / bin", 100, 0, 10);


  // gen b's

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
    for(size_t i=idx_gvt+1; i<event.genparticles_visibletaus->size(); i++){
      hdrgenvisditau->Fill(deltaR(gvt, event.genparticles_visibletaus->at(i)), weight);
      hdphigenvisditau->Fill(deltaPhi(gvt, event.genparticles_visibletaus->at(i)), weight);
      hdetagenvisditau->Fill(deltaEta(gvt, event.genparticles_visibletaus->at(i)), weight);
    }
    for(size_t i=0; i<event.genparticles_all->size(); i++){
      GenParticle gpmu = event.genparticles_all->at(i);
      if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
      hdrgenvistaumu->Fill(deltaR(gvt, gpmu), weight);
      hdphigenvistaumu->Fill(deltaPhi(gvt, gpmu), weight);
      hdetagenvistaumu->Fill(deltaEta(gvt, gpmu), weight);
    }

    for(size_t i=0; i<event.genparticles_all->size(); i++){
      GenParticle gpe = event.genparticles_all->at(i);
      if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
      hdrgenvistaue->Fill(deltaR(gvt, gpe), weight);
      hdphigenvistaue->Fill(deltaPhi(gvt, gpe), weight);
      hdetagenvistaue->Fill(deltaEta(gvt, gpe), weight);
    }

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
  int n_genbs = 0;
  int n_genbsmatched = 0;
  int gpidx = -1;
  for(const GenParticle & gp : *event.genparticles_all){
    gpidx++;
    // cout << "GenParticle at index " << gpidx << " with ID " << gp.pdgid() << ". "
    int id = abs(gp.pdgid());
    if(id != 11 && id != 13 && id != 15 && id != 5) continue;
    if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;
    // if((id == 5) && !gp.get_statusflag(GenParticle::isFirstCopy)) continue;

    if(id == 15){ // taus
      n_gentaus++;
      if(gp.pt() > pt_tau1){
        pt_tau2 = pt_tau1;
        pt_tau1 = gp.pt();
      }
      else if(gp.pt() > pt_tau2) pt_tau2 = gp.pt();

      for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
        GenParticle gptau = event.genparticles_all->at(i);
        if (abs(gptau.pdgid()) != 15 || !gptau.get_statusflag(GenParticle::isLastCopy)) continue;
        hdrgenditau->Fill(deltaR(gp, gptau), weight);
        hdphigenditau->Fill(deltaPhi(gp, gptau), weight);
        hdetagenditau->Fill(deltaEta(gp, gptau), weight);
      }
      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpmu = event.genparticles_all->at(i);
        if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgentaumu->Fill(deltaR(gp, gpmu), weight);
        hdphigentaumu->Fill(deltaPhi(gp, gpmu), weight);
        hdetagentaumu->Fill(deltaEta(gp, gpmu), weight);
      }

      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpe = event.genparticles_all->at(i);
        if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgentaue->Fill(deltaR(gp, gpe), weight);
        hdphigentaue->Fill(deltaPhi(gp, gpe), weight);
        hdetagentaue->Fill(deltaEta(gp, gpe), weight);
      }
    }
    else if(id == 13){ // muons
      n_genmus++;
      hgenmustotal->Fill(0., weight);

      for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
        GenParticle gpmu = event.genparticles_all->at(i);
        if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
        hdrgendimu->Fill(deltaR(gp, gpmu), weight);
        hdphigendimu->Fill(deltaPhi(gp, gpmu), weight);
        hdetagendimu->Fill(deltaEta(gp, gpmu), weight);
      }

      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpe = event.genparticles_all->at(i);
        if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgenmue->Fill(deltaR(gp, gpe), weight);
        hdphigenmue->Fill(deltaPhi(gp, gpe), weight);
        hdetagenmue->Fill(deltaEta(gp, gpe), weight);
      }

      for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
        GenParticle gvt = event.genparticles_visibletaus->at(i);
        hdrgenmuvistau->Fill(deltaR(gp, gvt), weight);
        hdphigenmuvistau->Fill(deltaPhi(gp, gvt), weight);
        hdetagenmuvistau->Fill(deltaEta(gp, gvt), weight);
      }

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

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgendimufromtau->Fill(deltaR(gp, gpmu), weight);
          hdphigendimufromtau->Fill(deltaPhi(gp, gpmu), weight);
          hdetagendimufromtau->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenmufromtaue->Fill(deltaR(gp, gpe), weight);
          hdphigenmufromtaue->Fill(deltaPhi(gp, gpe), weight);
          hdetagenmufromtaue->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenmufromtauvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenmufromtauvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenmufromtauvistau->Fill(deltaEta(gp, gvt), weight);
        }


        if(dr_min < 0.2 && dr_min > 0.){
          hgenmusfromtaumatched->Fill(0., weight);
          hptgenmufromtaumatched->Fill(gp.pt(), weight);
          hptgenmufromtaumatched_rebin->Fill(gp.pt(), weight);
          hptgenmufromtaumatched_rebin2->Fill(gp.pt(), weight);
        }
      }
      else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)){
        hgenmusfromhadtotal->Fill(0., weight);
        hptgenmufromhad->Fill(gp.pt(), weight);
        hptgenmufromhad_rebin->Fill(gp.pt(), weight);
        hptgenmufromhad_rebin2->Fill(gp.pt(), weight);

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgendimufromhad->Fill(deltaR(gp, gpmu), weight);
          hdphigendimufromhad->Fill(deltaPhi(gp, gpmu), weight);
          hdetagendimufromhad->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenmufromhade->Fill(deltaR(gp, gpe), weight);
          hdphigenmufromhade->Fill(deltaPhi(gp, gpe), weight);
          hdetagenmufromhade->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenmufromhadvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenmufromhadvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenmufromhadvistau->Fill(deltaEta(gp, gvt), weight);
        }

        if(dr_min < 0.2 && dr_min > 0.){
          hgenmusfromhadmatched->Fill(0., weight);
          hptgenmufromhadmatched->Fill(gp.pt(), weight);
          hptgenmufromhadmatched_rebin->Fill(gp.pt(), weight);
          hptgenmufromhadmatched_rebin2->Fill(gp.pt(), weight);
        }
      }

      hptgenmu->Fill(gp.pt(), weight);
      hptgenmu_rebin->Fill(gp.pt(), weight);
      hptgenmu_rebin2->Fill(gp.pt(), weight);
      if(dr_min < 0.2 && dr_min > 0.){
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
        if(dr_min < 0.2 && dr_min > 0.){
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
        if(dr_min < 0.2 && dr_min > 0.){
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

      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpmu = event.genparticles_all->at(i);
        if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgenemu->Fill(deltaR(gp, gpmu), weight);
        hdphigenemu->Fill(deltaPhi(gp, gpmu), weight);
        hdetagenemu->Fill(deltaEta(gp, gpmu), weight);
      }

      for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
        GenParticle gpe = event.genparticles_all->at(i);
        if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
        hdrgendie->Fill(deltaR(gp, gpe), weight);
        hdphigendie->Fill(deltaPhi(gp, gpe), weight);
        hdetagendie->Fill(deltaEta(gp, gpe), weight);
      }

      for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
        GenParticle gvt = event.genparticles_visibletaus->at(i);
        hdrgenevistau->Fill(deltaR(gp, gvt), weight);
        hdphigenevistau->Fill(deltaPhi(gp, gvt), weight);
        hdetagenevistau->Fill(deltaEta(gp, gvt), weight);
      }

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

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenefromtaumu->Fill(deltaR(gp, gpmu), weight);
          hdphigenefromtaumu->Fill(deltaPhi(gp, gpmu), weight);
          hdetagenefromtaumu->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgendiefromtau->Fill(deltaR(gp, gpe), weight);
          hdphigendiefromtau->Fill(deltaPhi(gp, gpe), weight);
          hdetagendiefromtau->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenefromtauvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenefromtauvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenefromtauvistau->Fill(deltaEta(gp, gvt), weight);
        }

        if(dr_min < 0.2 && dr_min > 0.){
          hgenelsfromtaumatched->Fill(0., weight);
          hptgenelfromtaumatched->Fill(gp.pt(), weight);
          hptgenelfromtaumatched_rebin->Fill(gp.pt(), weight);
          hptgenelfromtaumatched_rebin2->Fill(gp.pt(), weight);
        }
      }
      else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)){
        hgenelsfromhadtotal->Fill(0., weight);
        hptgenelfromhad->Fill(gp.pt(), weight);
        hptgenelfromhad_rebin->Fill(gp.pt(), weight);
        hptgenelfromhad_rebin2->Fill(gp.pt(), weight);

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgendiefromhad->Fill(deltaR(gp, gpmu), weight);
          hdphigendiefromhad->Fill(deltaPhi(gp, gpmu), weight);
          hdetagendiefromhad->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenefromhadmu->Fill(deltaR(gp, gpe), weight);
          hdphigenefromhadmu->Fill(deltaPhi(gp, gpe), weight);
          hdetagenefromhadmu->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenefromhadvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenefromhadvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenefromhadvistau->Fill(deltaEta(gp, gvt), weight);
        }

        if(dr_min < 0.2 && dr_min > 0.){
          hgenelsfromhadmatched->Fill(0., weight);
          hptgenelfromhadmatched->Fill(gp.pt(), weight);
          hptgenelfromhadmatched_rebin->Fill(gp.pt(), weight);
          hptgenelfromhadmatched_rebin2->Fill(gp.pt(), weight);
        }
      }

      hptgenel->Fill(gp.pt(), weight);
      hptgenel_rebin->Fill(gp.pt(), weight);
      hptgenel_rebin2->Fill(gp.pt(), weight);
      if(dr_min < 0.2 && dr_min > 0.){
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
        if(dr_min < 0.2 && dr_min > 0.){
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
        if(dr_min < 0.2 && dr_min > 0.){
          hptgenel2matched->Fill(gp.pt(), weight);
          hptgenel2matched_rebin->Fill(gp.pt(), weight);
          hptgenel2matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminel2->Fill(dr_min, weight);
        hgenel2origin->Fill(origin, weight);
      }
    }
    else if(id == 5){ // b quarks
      n_genbs++;
      hgenbstotal->Fill(0., weight);

      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpmu = event.genparticles_all->at(i);
        if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgenbmu->Fill(deltaR(gp, gpmu), weight);
        hdphigenbmu->Fill(deltaPhi(gp, gpmu), weight);
        hdetagenbmu->Fill(deltaEta(gp, gpmu), weight);
      }

      for(size_t i=0; i<event.genparticles_all->size(); i++){
        GenParticle gpe = event.genparticles_all->at(i);
        if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
        if (i == gpidx) continue;
        hdrgenbe->Fill(deltaR(gp, gpe), weight);
        hdphigenbe->Fill(deltaPhi(gp, gpe), weight);
        hdetagenbe->Fill(deltaEta(gp, gpe), weight);
      }

      for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
        GenParticle gvt = event.genparticles_visibletaus->at(i);
        hdrgenbvistau->Fill(deltaR(gp, gvt), weight);
        hdphigenbvistau->Fill(deltaPhi(gp, gvt), weight);
        hdetagenbvistau->Fill(deltaEta(gp, gvt), weight);
      }

      for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
        GenParticle gpb = event.genparticles_all->at(i);
        if (abs(gpb.pdgid()) != 5 || !gpb.get_statusflag(GenParticle::isLastCopy)) continue;
        hdrgendib->Fill(deltaR(gp, gpb), weight);
        hdphigendib->Fill(deltaPhi(gp, gpb), weight);
        hdetagendib->Fill(deltaEta(gp, gpb), weight);
      }



      const Jet* closest_jet = closestParticle(gp, *event.jets);
      float dr_min = -1.;
      if(closest_jet != nullptr) dr_min = deltaR(gp, *closest_jet);
      int origin = 0.;
      if(gp.get_statusflag(GenParticle::fromHardProcess)){
        origin = 1.;
      }
      else origin = 2.;

        if(gp.get_statusflag(GenParticle::fromHardProcess)){
        hgenbsfromhardtotal->Fill(0., weight);
        hptgenbfromhard->Fill(gp.pt(), weight);
        hptgenbfromhard_rebin->Fill(gp.pt(), weight);
        hptgenbfromhard_rebin2->Fill(gp.pt(), weight);

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenbfromhardmu->Fill(deltaR(gp, gpmu), weight);
          hdphigenbfromhardmu->Fill(deltaPhi(gp, gpmu), weight);
          hdetagenbfromhardmu->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenbfromharde->Fill(deltaR(gp, gpe), weight);
          hdphigenbfromharde->Fill(deltaPhi(gp, gpe), weight);
          hdetagenbfromharde->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenbfromhardvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenbfromhardvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenbfromhardvistau->Fill(deltaEta(gp, gvt), weight);
        }

        for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
          GenParticle gpb = event.genparticles_all->at(i);
          if (abs(gpb.pdgid()) != 5 || !gpb.get_statusflag(GenParticle::isLastCopy) || !gpb.get_statusflag(GenParticle::fromHardProcess)) continue;
          hdrgendibfromhard->Fill(deltaR(gp, gpb), weight);
          hdphigendibfromhard->Fill(deltaPhi(gp, gpb), weight);
          hdetagendibfromhard->Fill(deltaEta(gp, gpb), weight);
        }

        if(dr_min < 0.4 && dr_min > 0.){
          hgenbsfromhardmatched->Fill(0., weight);
          hptgenbfromhardmatched->Fill(gp.pt(), weight);
          hptgenbfromhardmatched_rebin->Fill(gp.pt(), weight);
          hptgenbfromhardmatched_rebin2->Fill(gp.pt(), weight);
        }
      }
      else{
        hgenbsnotfromhardtotal->Fill(0., weight);
        hptgenbnotfromhard->Fill(gp.pt(), weight);
        hptgenbnotfromhard_rebin->Fill(gp.pt(), weight);
        hptgenbnotfromhard_rebin2->Fill(gp.pt(), weight);

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpmu = event.genparticles_all->at(i);
          if (abs(gpmu.pdgid()) != 13 || !gpmu.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenbnotfromhardmu->Fill(deltaR(gp, gpmu), weight);
          hdphigenbnotfromhardmu->Fill(deltaPhi(gp, gpmu), weight);
          hdetagenbnotfromhardmu->Fill(deltaEta(gp, gpmu), weight);
        }

        for(size_t i=0; i<event.genparticles_all->size(); i++){
          GenParticle gpe = event.genparticles_all->at(i);
          if (abs(gpe.pdgid()) != 11 || !gpe.get_statusflag(GenParticle::isLastCopy)) continue;
          if (i == gpidx) continue;
          hdrgenbnotfromharde->Fill(deltaR(gp, gpe), weight);
          hdphigenbnotfromharde->Fill(deltaPhi(gp, gpe), weight);
          hdetagenbnotfromharde->Fill(deltaEta(gp, gpe), weight);
        }

        for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
          GenParticle gvt = event.genparticles_visibletaus->at(i);
          hdrgenbnotfromhardvistau->Fill(deltaR(gp, gvt), weight);
          hdphigenbnotfromhardvistau->Fill(deltaPhi(gp, gvt), weight);
          hdetagenbnotfromhardvistau->Fill(deltaEta(gp, gvt), weight);
        }

        for(size_t i=gpidx+1; i<event.genparticles_all->size(); i++){
          GenParticle gpb = event.genparticles_all->at(i);
          if (abs(gpb.pdgid()) != 5 || !gpb.get_statusflag(GenParticle::isLastCopy) || gpb.get_statusflag(GenParticle::fromHardProcess)) continue;
          hdrgendibnotfromhard->Fill(deltaR(gp, gpb), weight);
          hdphigendibnotfromhard->Fill(deltaPhi(gp, gpb), weight);
          hdetagendibnotfromhard->Fill(deltaEta(gp, gpb), weight);
        }

        if(dr_min < 0.4 && dr_min > 0.){
          hgenbsnotfromhardmatched->Fill(0., weight);
          hptgenbnotfromhardmatched->Fill(gp.pt(), weight);
          hptgenbnotfromhardmatched_rebin->Fill(gp.pt(), weight);
          hptgenbnotfromhardmatched_rebin2->Fill(gp.pt(), weight);
        }
      }

      hptgenb->Fill(gp.pt(), weight);
      hptgenb_rebin->Fill(gp.pt(), weight);
      hptgenb_rebin2->Fill(gp.pt(), weight);
      if(dr_min < 0.4 && dr_min > 0.){
        n_genbsmatched++;
        hgenbsmatched->Fill(0., weight);
        hptgenbmatched->Fill(gp.pt(), weight);
        hptgenbmatched_rebin->Fill(gp.pt(), weight);
        hptgenbmatched_rebin2->Fill(gp.pt(), weight);
      }
      hdrminb->Fill(dr_min, weight);
      hgenborigin->Fill(origin, weight);

      if(n_genbs == 1){
        hptgenb1->Fill(gp.pt(), weight);
        hptgenb1_rebin->Fill(gp.pt(), weight);
        hptgenb1_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.4 && dr_min > 0.){
          hptgenb1matched->Fill(gp.pt(), weight);
          hptgenb1matched_rebin->Fill(gp.pt(), weight);
          hptgenb1matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminb1->Fill(dr_min, weight);
        hgenb1origin->Fill(origin, weight);
      }
      else if(n_genbs == 2){
        hptgenb2->Fill(gp.pt(), weight);
        hptgenb2_rebin->Fill(gp.pt(), weight);
        hptgenb2_rebin2->Fill(gp.pt(), weight);
        if(dr_min < 0.4 && dr_min > 0.){
          hptgenb2matched->Fill(gp.pt(), weight);
          hptgenb2matched_rebin->Fill(gp.pt(), weight);
          hptgenb2matched_rebin2->Fill(gp.pt(), weight);
        }
        hdrminb2->Fill(dr_min, weight);
        hgenb2origin->Fill(origin, weight);
      }

    }

  }

  hngenmus->Fill(n_genmus, weight);
  hngenmusmatched->Fill(n_genmusmatched, weight);
  hngenels->Fill(n_genels, weight);
  hngenelsmatched->Fill(n_genelsmatched, weight);
  hngenbs->Fill(n_genbs, weight);
  hngenbsmatched->Fill(n_genbsmatched, weight);

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
