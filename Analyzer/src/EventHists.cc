#include "Analyzer/include/EventHists.h"
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

EventHists::EventHists(TString dir_) : BaseHists(dir_){

  hmetpt = book<TH1D>("metpt", ";p_{T}^{miss} [GeV]; Events / bin", 150, 0, 3000);
  hmetphi = book<TH1D>("metphi", ";#phi(p_{T}^{miss}); Events / bin", 70, -3.5, 3.5);
  hisdata = book<TH1D>("isdata", ";is data?; Events / bin", 2, -0.5, 1.5);
  hnpv = book<TH1D>("npv", ";N^{PV}; Events / bin", 101, -0.5, 100.5);
  hnpv_good = book<TH1D>("npv_good", ";N^{good PV}; Events / bin", 101, -0.5, 100.5);
  hnpu = book<TH1D>("npu", ";N^{PU}; Events / bin", 101, -0.5, 100.5);
  hntrueint = book<TH1D>("ntrueint", ";N^{true int.}; Events / bin", 101, -0.5, 100.5);

  hweight_prefiring = book<TH1D>("weight_prefiring", ";Prefiring weight; Events / bin", 400, 0., 2.);
  hweight_prefiring_up = book<TH1D>("weight_prefiring_up", ";Prefiring weight up; Events / bin", 400, 0., 2.);
  hweight_prefiring_down = book<TH1D>("weight_prefiring_down", ";Prefiring weight down; Events / bin", 400, 0., 2.);

  hweight = book<TH1D>("weight", ";Event weight; Gen. events / bin", 1000, 0., 5.);
  hsumweights = book<TH1D>("sumweights", ";;Sum of event weights", 1, 0.5, 1.5);

}

void EventHists::fill(const RecoEvent & event){
  double weight = event.weight;

  hmetpt->Fill(event.met->pt(), weight);
  hmetphi->Fill(event.met->phi(), weight);

  hisdata->Fill(event.is_data, weight);
  hnpv->Fill(event.npv, weight);
  hnpv_good->Fill(event.npv_good, weight);
  hnpu->Fill(event.npu, weight);
  hntrueint->Fill(event.ntrueint, weight);

  hweight_prefiring->Fill(event.weight_prefiring, weight);
  hweight_prefiring_up->Fill(event.weight_prefiring_up, weight);
  hweight_prefiring_down->Fill(event.weight_prefiring_down, weight);

  hweight->Fill(weight, 1);
  hsumweights->Fill(1, weight);
}
