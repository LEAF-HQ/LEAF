#include "include/BaseHists.h"
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

BaseHists::BaseHists(TString dir_){
  dir = dir_;
}



void BaseHists::save(TFile* outfile){
  outfile->cd();
  outfile->mkdir(dir);
  outfile->cd(dir);

  for(const auto & m : hists){
    m.second->Write();
  }
}
