#include "LQDMSearch/include/TestEvent.h"
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

TestEvent::TestEvent(){
  test = new vector<Electron>;
}

TestEvent::~TestEvent(){
  delete test;
}

void TestEvent::clear(){
  RecoEvent::clear();
  delete test;
  test = 0;
}

void TestEvent::reset(){
  RecoEvent::reset();
  delete test;
  test = new vector<Electron>;

}
