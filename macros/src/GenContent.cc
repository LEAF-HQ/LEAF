#include "include/GenContent.h"
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

GenContent::GenContent(){

  genmet                          = new Met;
  met_from_invis                  = new Met;
  genparticles_hard               = new vector<GenParticle>(0);
  // genparticles_final              = new vector<GenParticle>;
  // genparticles_visibletaus        = new vector<GenParticle>;
  // genjets                         = new vector<GenJet>;
  clear();
}

GenContent::~GenContent(){
  cout << "deleting GenContent" << endl;
  delete genmet;
  delete met_from_invis;
  delete genparticles_hard;
  // delete genparticles_final;
  // delete genparticles_visibletaus;
  // delete genjets;
  cout << "done deleting GenContent" << endl;
}

void GenContent::clear(){
  cout << "clearing" << endl;
  // genmet = 0;
  // met_from_invis = 0;
  genparticles_hard = 0;
  // genparticles_final = 0;
  // genparticles_visibletaus = 0;
  // genjets = 0;
}
