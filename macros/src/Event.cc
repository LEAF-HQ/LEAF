#include "include/GenlevelTool.h"
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

Event::Event(){

  genmet                          = new Met;
  genparticles_hard               = new vector<GenParticle>;
  genparticles_final              = new vector<GenParticle>;
  genparticles_prompttaudecayprod = new vector<GenParticle>;
  genjets                         = new vector<GenJet>;
}

void Event::clear(){
  delete genmet;
  delete genparticles_hard;
  delete genparticles_final;
  delete genparticles_prompttaudecayprod;
  delete genjets;
}
