#include "../include/GenlevelTool.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include "../include/useful_functions.h"
#include "../include/GenHists.h"
#include "../include/Event.h"
#include <TH1D.h>
#include <TH2F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TMath.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

bool GenlevelTool::Process(Event & event){
  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  sort_by_pt<GenParticle>(*event.genparticles_hard);
  sort_by_pt<GenParticle>(*event.genparticles_final);
  sort_by_pt<GenParticle>(*event.genparticles_visibletaus);
  sort_by_pt<GenJet>(*event.genjets);
  histmap["input"]->fill(event);

  // cout << "GenMET: " << event.genmet->pt() << endl;
  // TLorentzVector p4suminvis = {};
  // for(size_t i=0; i<event.genparticles_finalstate_invisible->size(); i++){
  //   // if(event.genparticles_finalstate_invisible->at(i).pdgid() > 100) continue;
  //   p4suminvis += event.genparticles_finalstate_invisible->at(i).p4();
  // }
  // cout << "MET from invisible particles: " << p4suminvis.Pt() << endl;
  // cout << "MET from invisible particles: " << event.met_from_invis->pt() << endl;


  // clean jets and visible taus
  cleaner_genvistau   ->process(event);
  cleaner_genjet      ->process(event);
  cleaner_genjetvistau->process(event);
  histmap["cleaner"]->fill(event);

  if(event.genparticles_visibletaus->size() < 1) return false;
  if(event.genparticles_visibletaus->at(0).pt() < 50) return false;
  if(event.genjets->size() < 1) return false;
  if(event.genjets->at(0).pt() < 50) return false;
  histmap["objectselection"]->fill(event);



  // calculate STMET
  double st = 0;
  // double stmet = event.genmet->pt();
  double stmet = event.met_from_invis->pt();
  int njetsmax = min((size_t)2, event.genjets->size());
  int ntauvismax = min((size_t)2, event.genparticles_visibletaus->size());
  for(int i=0; i<njetsmax; i++) st += event.genjets->at(i).pt();
  for(int i=0; i<ntauvismax; i++) st += event.genparticles_visibletaus->at(i).pt();
  stmet += st;
  if(stmet < 600) return false;
  histmap["stmet"]->fill(event);



  return true;
}
