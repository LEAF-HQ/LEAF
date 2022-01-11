#include "LEAF/Analyzer/include/BJetHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/JetIds.h"
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

BJetHists::BJetHists(TString dir_) : BaseHists(dir_){

  hnbjetlooses = book<TH1D>("nbjetslooses", ";N_{bjets loose}; Events / bin", 11, -0.5, 10.5);
  hbjetloosept = book<TH1D>("bjetloosept", ";p_{T}^{bjets loose} [GeV]; Events / bin", 50, 0, 1500);
  hbjetlooseeta = book<TH1D>("bjetlooseeta", ";#eta^{bjets loose};Events / bin", 100, -5., 5.);
  hbjetloosephi = book<TH1D>("bjetloosephi", ";#phi^{bjets loose};Events / bin", 70, -3.5, 3.5);
  hbjetloosemass = book<TH1D>("bjetloosemass", ";m^{bjets loose} [GeV];Events / bin", 50, 0, 1500);
  hbjetlooseenergy = book<TH1D>("bjetlooseenergy", ";E^{bjets loose} [GeV];Events / bin", 50, 0, 1500);
  hbjetloosehadronflavor = book<TH1D>("bjetloosehadronflavor", ";hadronflavor bjets loose;Events / bin", 43, -21.5, 21.5);
  hbjetloosepartonflavor = book<TH1D>("bjetloosepartonflavor", ";partonflavor bjets loose;Events / bin", 43, -21.5, 21.5);
  hbjetloosedeepb = book<TH1D>("bjetloosedeepb", ";Deepbjet score (all bjets loose);Events / bin", 50, 0, 1);
  hbjetloosedrminele = book<TH1D>("bjetloosedrminele", ";#DeltaR_{min} (bjetloose, e);Events / bin", 100, 0, 5);
  hbjetloosedrminmuon = book<TH1D>("bjetloosedrminmuon", ";#DeltaR_{min} (bjetloose, #mu);Events / bin", 100, 0, 5);
  hbjetloosedrmintau = book<TH1D>("bjetloosedrmintau", ";#DeltaR_{min} (bjetloose, #tau);Events / bin", 100, 0, 5);
  hbjetloose1pt = book<TH1D>("bjetloose1pt", ";p_{T}^{bjetloose 1} [GeV]; Events / bin", 50, 0, 1500);
  hbjetloose1eta = book<TH1D>("bjetloose1eta", ";#eta^{bjetloose 1};Events / bin", 100, -5., 5.);
  hbjetloose1phi = book<TH1D>("bjetloose1phi", ";#phi^{bjetloose 1};Events / bin", 70, -3.5, 3.5);
  hbjetloose1mass = book<TH1D>("bjetloose1mass", ";m^{bjetloose 1} [GeV];Events / bin", 50, 0, 1500);
  hbjetloose1energy = book<TH1D>("bjetloose1energy", ";E^{bjetloose 1} [GeV];Events / bin", 50, 0, 1500);
  hbjetloose1hadronflavor = book<TH1D>("bjetloose1hadronflavor", ";hadronflavor bjetloose 1;Events / bin", 43, -21.5, 21.5);
  hbjetloose1partonflavor = book<TH1D>("bjetloose1partonflavor", ";partonflavor bjetloose 1;Events / bin", 43, -21.5, 21.5);
  hbjetloose1deepb = book<TH1D>("bjetloose1deepb", ";Deepbjet score (bjetloose 1);Events / bin", 50, 0, 1);
  hbjetloose1drminele = book<TH1D>("bjetloose1drminele", ";#DeltaR_{min} (bjetloose1, e);Events / bin", 100, 0, 5);
  hbjetloose1drminmuon = book<TH1D>("bjetloose1drminmuon", ";#DeltaR_{min} (bjetloose1, #mu);Events / bin", 100, 0, 5);
  hbjetloose1drmintau = book<TH1D>("bjetloose1drmintau", ";#DeltaR_{min} (bjetloose1, #tau);Events / bin", 100, 0, 5);
  hnnotbjetlooses = book<TH1D>("nnotbjetslooses", ";N_{notbjets loose}; Events / bin", 11, -0.5, 10.5);
  hnotbjetloosept = book<TH1D>("notbjetloosept", ";p_{T}^{notbjets loose} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjetlooseeta = book<TH1D>("notbjetlooseeta", ";#eta^{notbjets loose};Events / bin", 100, -5., 5.);
  hnotbjetloosephi = book<TH1D>("notbjetloosephi", ";#phi^{notbjets loose};Events / bin", 70, -3.5, 3.5);
  hnotbjetloosemass = book<TH1D>("notbjetloosemass", ";m^{notbjets loose} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetlooseenergy = book<TH1D>("notbjetlooseenergy", ";E^{notbjets loose} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetloosehadronflavor = book<TH1D>("notbjetloosehadronflavor", ";hadronflavor notbjets loose;Events / bin", 43, -21.5, 21.5);
  hnotbjetloosepartonflavor = book<TH1D>("notbjetloosepartonflavor", ";partonflavor notbjets loose;Events / bin", 43, -21.5, 21.5);
  hnotbjetloosedeepb = book<TH1D>("notbjetloosedeepb", ";Deepbjet score (all notbjets loose);Events / bin", 50, 0, 1);
  hnotbjetloosedrminele = book<TH1D>("notbjetloosedrminele", ";#DeltaR_{min} (notbjetloose, e);Events / bin", 100, 0, 5);
  hnotbjetloosedrminmuon = book<TH1D>("notbjetloosedrminmuon", ";#DeltaR_{min} (notbjetloose, #mu);Events / bin", 100, 0, 5);
  hnotbjetloosedrmintau = book<TH1D>("notbjetloosedrmintau", ";#DeltaR_{min} (notbjetloose, #tau);Events / bin", 100, 0, 5);
  hnotbjetloose1pt = book<TH1D>("notbjetloose1pt", ";p_{T}^{notbjetloose 1} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjetloose1eta = book<TH1D>("notbjetloose1eta", ";#eta^{notbjetloose 1};Events / bin", 100, -5., 5.);
  hnotbjetloose1phi = book<TH1D>("notbjetloose1phi", ";#phi^{notbjetloose 1};Events / bin", 70, -3.5, 3.5);
  hnotbjetloose1mass = book<TH1D>("notbjetloose1mass", ";m^{notbjetloose 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetloose1energy = book<TH1D>("notbjetloose1energy", ";E^{notbjetloose 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetloose1hadronflavor = book<TH1D>("notbjetloose1hadronflavor", ";hadronflavor notbjetloose 1;Events / bin", 43, -21.5, 21.5);
  hnotbjetloose1partonflavor = book<TH1D>("notbjetloose1partonflavor", ";partonflavor notbjetloose 1;Events / bin", 43, -21.5, 21.5);
  hnotbjetloose1deepb = book<TH1D>("notbjetloose1deepb", ";Deepbjet score (notbjetloose 1);Events / bin", 50, 0, 1);
  hnotbjetloose1drminele = book<TH1D>("notbjetloose1drminele", ";#DeltaR_{min} (notbjetloose1, e);Events / bin", 100, 0, 5);
  hnotbjetloose1drminmuon = book<TH1D>("notbjetloose1drminmuon", ";#DeltaR_{min} (notbjetloose1, #mu);Events / bin", 100, 0, 5);
  hnotbjetloose1drmintau = book<TH1D>("notbjetloose1drmintau", ";#DeltaR_{min} (notbjetloose1, #tau);Events / bin", 100, 0, 5);

  hnbjetmediums = book<TH1D>("nbjetsmediums", ";N_{bjets medium}; Events / bin", 11, -0.5, 10.5);
  hbjetmediumpt = book<TH1D>("bjetmediumpt", ";p_{T}^{bjets medium} [GeV]; Events / bin", 50, 0, 1500);
  hbjetmediumeta = book<TH1D>("bjetmediumeta", ";#eta^{bjets medium};Events / bin", 100, -5., 5.);
  hbjetmediumphi = book<TH1D>("bjetmediumphi", ";#phi^{bjets medium};Events / bin", 70, -3.5, 3.5);
  hbjetmediummass = book<TH1D>("bjetmediummass", ";m^{bjets medium} [GeV];Events / bin", 50, 0, 1500);
  hbjetmediumenergy = book<TH1D>("bjetmediumenergy", ";E^{bjets medium} [GeV];Events / bin", 50, 0, 1500);
  hbjetmediumhadronflavor = book<TH1D>("bjetmediumhadronflavor", ";hadronflavor bjets medium;Events / bin", 43, -21.5, 21.5);
  hbjetmediumpartonflavor = book<TH1D>("bjetmediumpartonflavor", ";partonflavor bjets medium;Events / bin", 43, -21.5, 21.5);
  hbjetmediumdeepb = book<TH1D>("bjetmediumdeepb", ";Deepbjet score (all bjets medium);Events / bin", 50, 0, 1);
  hbjetmediumdrminele = book<TH1D>("bjetmediumdrminele", ";#DeltaR_{min} (bjetmedium, e);Events / bin", 100, 0, 5);
  hbjetmediumdrminmuon = book<TH1D>("bjetmediumdrminmuon", ";#DeltaR_{min} (bjetmedium, #mu);Events / bin", 100, 0, 5);
  hbjetmediumdrmintau = book<TH1D>("bjetmediumdrmintau", ";#DeltaR_{min} (bjetmedium, #tau);Events / bin", 100, 0, 5);
  hbjetmedium1pt = book<TH1D>("bjetmedium1pt", ";p_{T}^{bjetmedium 1} [GeV]; Events / bin", 50, 0, 1500);
  hbjetmedium1eta = book<TH1D>("bjetmedium1eta", ";#eta^{bjetmedium 1};Events / bin", 100, -5., 5.);
  hbjetmedium1phi = book<TH1D>("bjetmedium1phi", ";#phi^{bjetmedium 1};Events / bin", 70, -3.5, 3.5);
  hbjetmedium1mass = book<TH1D>("bjetmedium1mass", ";m^{bjetmedium 1} [GeV];Events / bin", 50, 0, 1500);
  hbjetmedium1energy = book<TH1D>("bjetmedium1energy", ";E^{bjetmedium 1} [GeV];Events / bin", 50, 0, 1500);
  hbjetmedium1hadronflavor = book<TH1D>("bjetmedium1hadronflavor", ";hadronflavor bjetmedium 1;Events / bin", 43, -21.5, 21.5);
  hbjetmedium1partonflavor = book<TH1D>("bjetmedium1partonflavor", ";partonflavor bjetmedium 1;Events / bin", 43, -21.5, 21.5);
  hbjetmedium1deepb = book<TH1D>("bjetmedium1deepb", ";Deepbjet score (bjetmedium 1);Events / bin", 50, 0, 1);
  hbjetmedium1drminele = book<TH1D>("bjetmedium1drminele", ";#DeltaR_{min} (bjetmedium1, e);Events / bin", 100, 0, 5);
  hbjetmedium1drminmuon = book<TH1D>("bjetmedium1drminmuon", ";#DeltaR_{min} (bjetmedium1, #mu);Events / bin", 100, 0, 5);
  hbjetmedium1drmintau = book<TH1D>("bjetmedium1drmintau", ";#DeltaR_{min} (bjetmedium1, #tau);Events / bin", 100, 0, 5);
  hnnotbjetmediums = book<TH1D>("nnotbjetsmediums", ";N_{notbjets medium}; Events / bin", 11, -0.5, 10.5);
  hnotbjetmediumpt = book<TH1D>("notbjetmediumpt", ";p_{T}^{notbjets medium} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjetmediumeta = book<TH1D>("notbjetmediumeta", ";#eta^{notbjets medium};Events / bin", 100, -5., 5.);
  hnotbjetmediumphi = book<TH1D>("notbjetmediumphi", ";#phi^{notbjets medium};Events / bin", 70, -3.5, 3.5);
  hnotbjetmediummass = book<TH1D>("notbjetmediummass", ";m^{notbjets medium} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetmediumenergy = book<TH1D>("notbjetmediumenergy", ";E^{notbjets medium} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetmediumhadronflavor = book<TH1D>("notbjetmediumhadronflavor", ";hadronflavor notbjets medium;Events / bin", 43, -21.5, 21.5);
  hnotbjetmediumpartonflavor = book<TH1D>("notbjetmediumpartonflavor", ";partonflavor notbjets medium;Events / bin", 43, -21.5, 21.5);
  hnotbjetmediumdeepb = book<TH1D>("notbjetmediumdeepb", ";Deepbjet score (all notbjets medium);Events / bin", 50, 0, 1);
  hnotbjetmediumdrminele = book<TH1D>("notbjetmediumdrminele", ";#DeltaR_{min} (notbjetmedium, e);Events / bin", 100, 0, 5);
  hnotbjetmediumdrminmuon = book<TH1D>("notbjetmediumdrminmuon", ";#DeltaR_{min} (notbjetmedium, #mu);Events / bin", 100, 0, 5);
  hnotbjetmediumdrmintau = book<TH1D>("notbjetmediumdrmintau", ";#DeltaR_{min} (notbjetmedium, #tau);Events / bin", 100, 0, 5);
  hnotbjetmedium1pt = book<TH1D>("notbjetmedium1pt", ";p_{T}^{notbjetmedium 1} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjetmedium1eta = book<TH1D>("notbjetmedium1eta", ";#eta^{notbjetmedium 1};Events / bin", 100, -5., 5.);
  hnotbjetmedium1phi = book<TH1D>("notbjetmedium1phi", ";#phi^{notbjetmedium 1};Events / bin", 70, -3.5, 3.5);
  hnotbjetmedium1mass = book<TH1D>("notbjetmedium1mass", ";m^{notbjetmedium 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetmedium1energy = book<TH1D>("notbjetmedium1energy", ";E^{notbjetmedium 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjetmedium1hadronflavor = book<TH1D>("notbjetmedium1hadronflavor", ";hadronflavor notbjetmedium 1;Events / bin", 43, -21.5, 21.5);
  hnotbjetmedium1partonflavor = book<TH1D>("notbjetmedium1partonflavor", ";partonflavor notbjetmedium 1;Events / bin", 43, -21.5, 21.5);
  hnotbjetmedium1deepb = book<TH1D>("notbjetmedium1deepb", ";Deepbjet score (notbjetmedium 1);Events / bin", 50, 0, 1);
  hnotbjetmedium1drminele = book<TH1D>("notbjetmedium1drminele", ";#DeltaR_{min} (notbjetmedium1, e);Events / bin", 100, 0, 5);
  hnotbjetmedium1drminmuon = book<TH1D>("notbjetmedium1drminmuon", ";#DeltaR_{min} (notbjetmedium1, #mu);Events / bin", 100, 0, 5);
  hnotbjetmedium1drmintau = book<TH1D>("notbjetmedium1drmintau", ";#DeltaR_{min} (notbjetmedium1, #tau);Events / bin", 100, 0, 5);

  hnbjettights = book<TH1D>("nbjetstights", ";N_{bjets tight}; Events / bin", 11, -0.5, 10.5);
  hbjettightpt = book<TH1D>("bjettightpt", ";p_{T}^{bjets tight} [GeV]; Events / bin", 50, 0, 1500);
  hbjettighteta = book<TH1D>("bjettighteta", ";#eta^{bjets tight};Events / bin", 100, -5., 5.);
  hbjettightphi = book<TH1D>("bjettightphi", ";#phi^{bjets tight};Events / bin", 70, -3.5, 3.5);
  hbjettightmass = book<TH1D>("bjettightmass", ";m^{bjets tight} [GeV];Events / bin", 50, 0, 1500);
  hbjettightenergy = book<TH1D>("bjettightenergy", ";E^{bjets tight} [GeV];Events / bin", 50, 0, 1500);
  hbjettighthadronflavor = book<TH1D>("bjettighthadronflavor", ";hadronflavor bjets tight;Events / bin", 43, -21.5, 21.5);
  hbjettightpartonflavor = book<TH1D>("bjettightpartonflavor", ";partonflavor bjets tight;Events / bin", 43, -21.5, 21.5);
  hbjettightdeepb = book<TH1D>("bjettightdeepb", ";Deepbjet score (all bjets tight);Events / bin", 50, 0, 1);
  hbjettightdrminele = book<TH1D>("bjettightdrminele", ";#DeltaR_{min} (bjettight, e);Events / bin", 100, 0, 5);
  hbjettightdrminmuon = book<TH1D>("bjettightdrminmuon", ";#DeltaR_{min} (bjettight, #mu);Events / bin", 100, 0, 5);
  hbjettightdrmintau = book<TH1D>("bjettightdrmintau", ";#DeltaR_{min} (bjettight, #tau);Events / bin", 100, 0, 5);
  hbjettight1pt = book<TH1D>("bjettight1pt", ";p_{T}^{bjettight 1} [GeV]; Events / bin", 50, 0, 1500);
  hbjettight1eta = book<TH1D>("bjettight1eta", ";#eta^{bjettight 1};Events / bin", 100, -5., 5.);
  hbjettight1phi = book<TH1D>("bjettight1phi", ";#phi^{bjettight 1};Events / bin", 70, -3.5, 3.5);
  hbjettight1mass = book<TH1D>("bjettight1mass", ";m^{bjettight 1} [GeV];Events / bin", 50, 0, 1500);
  hbjettight1energy = book<TH1D>("bjettight1energy", ";E^{bjettight 1} [GeV];Events / bin", 50, 0, 1500);
  hbjettight1hadronflavor = book<TH1D>("bjettight1hadronflavor", ";hadronflavor bjettight 1;Events / bin", 43, -21.5, 21.5);
  hbjettight1partonflavor = book<TH1D>("bjettight1partonflavor", ";partonflavor bjettight 1;Events / bin", 43, -21.5, 21.5);
  hbjettight1deepb = book<TH1D>("bjettight1deepb", ";Deepbjet score (bjettight 1);Events / bin", 50, 0, 1);
  hbjettight1drminele = book<TH1D>("bjettight1drminele", ";#DeltaR_{min} (bjettight1, e);Events / bin", 100, 0, 5);
  hbjettight1drminmuon = book<TH1D>("bjettight1drminmuon", ";#DeltaR_{min} (bjettight1, #mu);Events / bin", 100, 0, 5);
  hbjettight1drmintau = book<TH1D>("bjettight1drmintau", ";#DeltaR_{min} (bjettight1, #tau);Events / bin", 100, 0, 5);
  hnnotbjettights = book<TH1D>("nnotbjetstights", ";N_{notbjets tight}; Events / bin", 11, -0.5, 10.5);
  hnotbjettightpt = book<TH1D>("notbjettightpt", ";p_{T}^{notbjets tight} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjettighteta = book<TH1D>("notbjettighteta", ";#eta^{notbjets tight};Events / bin", 100, -5., 5.);
  hnotbjettightphi = book<TH1D>("notbjettightphi", ";#phi^{notbjets tight};Events / bin", 70, -3.5, 3.5);
  hnotbjettightmass = book<TH1D>("notbjettightmass", ";m^{notbjets tight} [GeV];Events / bin", 50, 0, 1500);
  hnotbjettightenergy = book<TH1D>("notbjettightenergy", ";E^{notbjets tight} [GeV];Events / bin", 50, 0, 1500);
  hnotbjettighthadronflavor = book<TH1D>("notbjettighthadronflavor", ";hadronflavor notbjets tight;Events / bin", 43, -21.5, 21.5);
  hnotbjettightpartonflavor = book<TH1D>("notbjettightpartonflavor", ";partonflavor notbjets tight;Events / bin", 43, -21.5, 21.5);
  hnotbjettightdeepb = book<TH1D>("notbjettightdeepb", ";Deepbjet score (all notbjets tight);Events / bin", 50, 0, 1);
  hnotbjettightdrminele = book<TH1D>("notbjettightdrminele", ";#DeltaR_{min} (notbjettight, e);Events / bin", 100, 0, 5);
  hnotbjettightdrminmuon = book<TH1D>("notbjettightdrminmuon", ";#DeltaR_{min} (notbjettight, #mu);Events / bin", 100, 0, 5);
  hnotbjettightdrmintau = book<TH1D>("notbjettightdrmintau", ";#DeltaR_{min} (notbjettight, #tau);Events / bin", 100, 0, 5);
  hnotbjettight1pt = book<TH1D>("notbjettight1pt", ";p_{T}^{notbjettight 1} [GeV]; Events / bin", 50, 0, 1500);
  hnotbjettight1eta = book<TH1D>("notbjettight1eta", ";#eta^{notbjettight 1};Events / bin", 100, -5., 5.);
  hnotbjettight1phi = book<TH1D>("notbjettight1phi", ";#phi^{notbjettight 1};Events / bin", 70, -3.5, 3.5);
  hnotbjettight1mass = book<TH1D>("notbjettight1mass", ";m^{notbjettight 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjettight1energy = book<TH1D>("notbjettight1energy", ";E^{notbjettight 1} [GeV];Events / bin", 50, 0, 1500);
  hnotbjettight1hadronflavor = book<TH1D>("notbjettight1hadronflavor", ";hadronflavor notbjettight 1;Events / bin", 43, -21.5, 21.5);
  hnotbjettight1partonflavor = book<TH1D>("notbjettight1partonflavor", ";partonflavor notbjettight 1;Events / bin", 43, -21.5, 21.5);
  hnotbjettight1deepb = book<TH1D>("notbjettight1deepb", ";Deepbjet score (notbjettight 1);Events / bin", 50, 0, 1);
  hnotbjettight1drminele = book<TH1D>("notbjettight1drminele", ";#DeltaR_{min} (notbjettight1, e);Events / bin", 100, 0, 5);
  hnotbjettight1drminmuon = book<TH1D>("notbjettight1drminmuon", ";#DeltaR_{min} (notbjettight1, #mu);Events / bin", 100, 0, 5);
  hnotbjettight1drmintau = book<TH1D>("notbjettight1drmintau", ";#DeltaR_{min} (notbjettight1, #tau);Events / bin", 100, 0, 5);

}

void BJetHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t njets = event.jets->size();
  size_t ndeepbloose = 0;
  size_t ndeepbmedium = 0;
  size_t ndeepbtight = 0;
  for(size_t i=0; i<njets; i++){
    Jet j = event.jets->at(i);
    double dRmin_ele  = 999.;
    double dRmin_muon = 999.;
    double dRmin_tau  = 999.;
    for(size_t k=0; k<event.electrons->size(); k++){
      dRmin_ele = min(dRmin_ele, deltaR(j, event.electrons->at(k)));
    }
    for(size_t k=0; k<event.muons->size(); k++){
      dRmin_muon = min(dRmin_muon, deltaR(j, event.muons->at(k)));
    }
    for(size_t k=0; k<event.taus->size(); k++){
      dRmin_tau = min(dRmin_tau, deltaR(j, event.taus->at(k)));
    }
    ID<Jet> deepb_loose = JetBTag(JetBTag::DeepCSV_Loose);
    ID<Jet> deepb_medium = JetBTag(JetBTag::DeepCSV_Medium);
    ID<Jet> deepb_tight = JetBTag(JetBTag::DeepCSV_Tight);
    bool is_loose = deepb_loose(j, event);
    bool is_medium = deepb_medium(j, event);
    bool is_tight = deepb_tight(j, event);

    if(is_loose){
      ndeepbloose++;

      hbjetloosept->Fill(j.pt(), weight);
      hbjetlooseeta->Fill(j.eta(), weight);
      hbjetloosephi->Fill(j.phi(), weight);
      hbjetloosemass->Fill(j.m(), weight);
      hbjetlooseenergy->Fill(j.e(), weight);
      hbjetloosehadronflavor->Fill(j.hadron_flavor(), weight);
      hbjetloosepartonflavor->Fill(j.parton_flavor(), weight);
      hbjetloosedeepb->Fill(j.score_DeepB(), weight);
      hbjetloosedrminele->Fill(dRmin_ele, weight);
      hbjetloosedrminmuon->Fill(dRmin_muon, weight);
      hbjetloosedrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hbjetloose1pt->Fill(j.pt(), weight);
        hbjetloose1eta->Fill(j.eta(), weight);
        hbjetloose1phi->Fill(j.phi(), weight);
        hbjetloose1mass->Fill(j.m(), weight);
        hbjetloose1energy->Fill(j.e(), weight);
        hbjetloose1hadronflavor->Fill(j.hadron_flavor(), weight);
        hbjetloose1partonflavor->Fill(j.parton_flavor(), weight);
        hbjetloose1deepb->Fill(j.score_DeepB(), weight);
        hbjetloose1drminele->Fill(dRmin_ele, weight);
        hbjetloose1drminmuon->Fill(dRmin_muon, weight);
        hbjetloose1drmintau->Fill(dRmin_tau, weight);
      }
    }
    else{
      hnotbjetloosept->Fill(j.pt(), weight);
      hnotbjetlooseeta->Fill(j.eta(), weight);
      hnotbjetloosephi->Fill(j.phi(), weight);
      hnotbjetloosemass->Fill(j.m(), weight);
      hnotbjetlooseenergy->Fill(j.e(), weight);
      hnotbjetloosehadronflavor->Fill(j.hadron_flavor(), weight);
      hnotbjetloosepartonflavor->Fill(j.parton_flavor(), weight);
      hnotbjetloosedeepb->Fill(j.score_DeepB(), weight);
      hnotbjetloosedrminele->Fill(dRmin_ele, weight);
      hnotbjetloosedrminmuon->Fill(dRmin_muon, weight);
      hnotbjetloosedrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hnotbjetloose1pt->Fill(j.pt(), weight);
        hnotbjetloose1eta->Fill(j.eta(), weight);
        hnotbjetloose1phi->Fill(j.phi(), weight);
        hnotbjetloose1mass->Fill(j.m(), weight);
        hnotbjetloose1energy->Fill(j.e(), weight);
        hnotbjetloose1hadronflavor->Fill(j.hadron_flavor(), weight);
        hnotbjetloose1partonflavor->Fill(j.parton_flavor(), weight);
        hnotbjetloose1deepb->Fill(j.score_DeepB(), weight);
        hnotbjetloose1drminele->Fill(dRmin_ele, weight);
        hnotbjetloose1drminmuon->Fill(dRmin_muon, weight);
        hnotbjetloose1drmintau->Fill(dRmin_tau, weight);
      }
    }


    if(is_medium){
      ndeepbmedium++;

      hbjetmediumpt->Fill(j.pt(), weight);
      hbjetmediumeta->Fill(j.eta(), weight);
      hbjetmediumphi->Fill(j.phi(), weight);
      hbjetmediummass->Fill(j.m(), weight);
      hbjetmediumenergy->Fill(j.e(), weight);
      hbjetmediumhadronflavor->Fill(j.hadron_flavor(), weight);
      hbjetmediumpartonflavor->Fill(j.parton_flavor(), weight);
      hbjetmediumdeepb->Fill(j.score_DeepB(), weight);
      hbjetmediumdrminele->Fill(dRmin_ele, weight);
      hbjetmediumdrminmuon->Fill(dRmin_muon, weight);
      hbjetmediumdrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hbjetmedium1pt->Fill(j.pt(), weight);
        hbjetmedium1eta->Fill(j.eta(), weight);
        hbjetmedium1phi->Fill(j.phi(), weight);
        hbjetmedium1mass->Fill(j.m(), weight);
        hbjetmedium1energy->Fill(j.e(), weight);
        hbjetmedium1hadronflavor->Fill(j.hadron_flavor(), weight);
        hbjetmedium1partonflavor->Fill(j.parton_flavor(), weight);
        hbjetmedium1deepb->Fill(j.score_DeepB(), weight);
        hbjetmedium1drminele->Fill(dRmin_ele, weight);
        hbjetmedium1drminmuon->Fill(dRmin_muon, weight);
        hbjetmedium1drmintau->Fill(dRmin_tau, weight);
      }
    }
    else{
      hnotbjetmediumpt->Fill(j.pt(), weight);
      hnotbjetmediumeta->Fill(j.eta(), weight);
      hnotbjetmediumphi->Fill(j.phi(), weight);
      hnotbjetmediummass->Fill(j.m(), weight);
      hnotbjetmediumenergy->Fill(j.e(), weight);
      hnotbjetmediumhadronflavor->Fill(j.hadron_flavor(), weight);
      hnotbjetmediumpartonflavor->Fill(j.parton_flavor(), weight);
      hnotbjetmediumdeepb->Fill(j.score_DeepB(), weight);
      hnotbjetmediumdrminele->Fill(dRmin_ele, weight);
      hnotbjetmediumdrminmuon->Fill(dRmin_muon, weight);
      hnotbjetmediumdrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hnotbjetmedium1pt->Fill(j.pt(), weight);
        hnotbjetmedium1eta->Fill(j.eta(), weight);
        hnotbjetmedium1phi->Fill(j.phi(), weight);
        hnotbjetmedium1mass->Fill(j.m(), weight);
        hnotbjetmedium1energy->Fill(j.e(), weight);
        hnotbjetmedium1hadronflavor->Fill(j.hadron_flavor(), weight);
        hnotbjetmedium1partonflavor->Fill(j.parton_flavor(), weight);
        hnotbjetmedium1deepb->Fill(j.score_DeepB(), weight);
        hnotbjetmedium1drminele->Fill(dRmin_ele, weight);
        hnotbjetmedium1drminmuon->Fill(dRmin_muon, weight);
        hnotbjetmedium1drmintau->Fill(dRmin_tau, weight);
      }
    }


    if(is_tight){
      ndeepbtight++;

      hbjettightpt->Fill(j.pt(), weight);
      hbjettighteta->Fill(j.eta(), weight);
      hbjettightphi->Fill(j.phi(), weight);
      hbjettightmass->Fill(j.m(), weight);
      hbjettightenergy->Fill(j.e(), weight);
      hbjettighthadronflavor->Fill(j.hadron_flavor(), weight);
      hbjettightpartonflavor->Fill(j.parton_flavor(), weight);
      hbjettightdeepb->Fill(j.score_DeepB(), weight);
      hbjettightdrminele->Fill(dRmin_ele, weight);
      hbjettightdrminmuon->Fill(dRmin_muon, weight);
      hbjettightdrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hbjettight1pt->Fill(j.pt(), weight);
        hbjettight1eta->Fill(j.eta(), weight);
        hbjettight1phi->Fill(j.phi(), weight);
        hbjettight1mass->Fill(j.m(), weight);
        hbjettight1energy->Fill(j.e(), weight);
        hbjettight1hadronflavor->Fill(j.hadron_flavor(), weight);
        hbjettight1partonflavor->Fill(j.parton_flavor(), weight);
        hbjettight1deepb->Fill(j.score_DeepB(), weight);
        hbjettight1drminele->Fill(dRmin_ele, weight);
        hbjettight1drminmuon->Fill(dRmin_muon, weight);
        hbjettight1drmintau->Fill(dRmin_tau, weight);
      }
    }
    else{
      hnotbjettightpt->Fill(j.pt(), weight);
      hnotbjettighteta->Fill(j.eta(), weight);
      hnotbjettightphi->Fill(j.phi(), weight);
      hnotbjettightmass->Fill(j.m(), weight);
      hnotbjettightenergy->Fill(j.e(), weight);
      hnotbjettighthadronflavor->Fill(j.hadron_flavor(), weight);
      hnotbjettightpartonflavor->Fill(j.parton_flavor(), weight);
      hnotbjettightdeepb->Fill(j.score_DeepB(), weight);
      hnotbjettightdrminele->Fill(dRmin_ele, weight);
      hnotbjettightdrminmuon->Fill(dRmin_muon, weight);
      hnotbjettightdrmintau->Fill(dRmin_tau, weight);
      if(i==0){
        hnotbjettight1pt->Fill(j.pt(), weight);
        hnotbjettight1eta->Fill(j.eta(), weight);
        hnotbjettight1phi->Fill(j.phi(), weight);
        hnotbjettight1mass->Fill(j.m(), weight);
        hnotbjettight1energy->Fill(j.e(), weight);
        hnotbjettight1hadronflavor->Fill(j.hadron_flavor(), weight);
        hnotbjettight1partonflavor->Fill(j.parton_flavor(), weight);
        hnotbjettight1deepb->Fill(j.score_DeepB(), weight);
        hnotbjettight1drminele->Fill(dRmin_ele, weight);
        hnotbjettight1drminmuon->Fill(dRmin_muon, weight);
        hnotbjettight1drmintau->Fill(dRmin_tau, weight);
      }
    }


  } // end of jet loop

  hnbjetlooses->Fill(ndeepbloose, weight);
  hnbjetmediums->Fill(ndeepbmedium, weight);
  hnbjettights->Fill(ndeepbtight, weight);

  hnnotbjetlooses->Fill(njets - ndeepbloose, weight);
  hnnotbjetmediums->Fill(njets - ndeepbmedium, weight);
  hnnotbjettights->Fill(njets - ndeepbtight, weight);



}
