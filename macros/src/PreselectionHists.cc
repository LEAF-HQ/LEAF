#include "include/PreselectionHists.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include "include/useful_functions.h"
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

PreselectionHists::PreselectionHists(TString dir_) : BaseHists(dir_){

  hnjets = book<TH1F>("njets", ";N_{jets}; Events / bin", 11, -0.5, 10.5);
  hsumweights = book<TH1F>("sumweights", ";bincontent = sum of event weights; Events / bin", 1, 0.5, 1.5);

}

void PreselectionHists::fill(const RecoEvent & event){
  double weight = event.weight;


  hnjets->Fill(event.jets->size(), weight);
  cout << "Filled hnjets with value " << event.jets->size() << endl;
  hsumweights->Fill(1, weight);
}
