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
  genmet                   = new Met;
  genmet_invis             = new Met;

  GenParticle p;
  genparticles_hard        = new vector<GenParticle>;
  genparticles_final       = new vector<GenParticle>;
  genparticles_visibletaus = new vector<GenParticle>;
  genjets                  = new vector<GenJet>;
}

GenEvent::~GenEvent(){
  delete genmet;
  delete genmet_invis;
  delete genparticles_hard;
  delete genparticles_final;
  delete genparticles_visibletaus;
  delete genjets;
}

void GenEvent::clear(){
  Event::clear();
  delete genmet;
  delete genmet_invis;
  delete genparticles_hard;
  delete genparticles_final;
  delete genparticles_visibletaus;
  delete genjets;
  genmet = 0;
  genmet_invis = 0;
  genparticles_hard = 0;
  genparticles_final = 0;
  genparticles_visibletaus = 0;
  genjets = 0;
}

void GenEvent::reset(){
  Event::reset();
  delete genmet;
  delete genmet_invis;
  delete genparticles_hard;
  delete genparticles_final;
  delete genparticles_visibletaus;
  delete genjets;
  GenParticle p;
  genmet                   = new Met;
  genmet_invis             = new Met;
  genparticles_hard        = new vector<GenParticle>;
  genparticles_final       = new vector<GenParticle>;
  genparticles_visibletaus = new vector<GenParticle>;
  genjets                  = new vector<GenJet>;
}
