#include "include/GenEvent.h"
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

GenEvent::GenEvent(){
  test                     = 1.;
}

GenEvent::~GenEvent(){

}

void GenEvent::clear(){
  Event::clear();
  test  = 1.;
}

void GenEvent::reset(){
  Event::reset();
  test                     = 1.;
}
