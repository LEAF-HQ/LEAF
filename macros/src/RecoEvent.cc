#include "include/RecoEvent.h"
#include "include/Event.h"
#include "include/cosmetics.h"
#include "include/constants.h"
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

RecoEvent::RecoEvent(){
  met = new Met;
  jets = new vector<Jet>;
}

RecoEvent::~RecoEvent(){
  delete met;
  delete jets;
}

void RecoEvent::clear(){
  Event::clear();
  delete met;
  delete jets;
  met = 0;
  jets = 0;
}

void RecoEvent::reset(){
  Event::reset();
  delete met;
  delete jets;
  met = new Met;
  jets = new vector<Jet>;
}
