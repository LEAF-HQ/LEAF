#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include "include/Event.h"
#include "include/Met.h"
#include "include/Particle.h"
#include "include/GenParticle.h"
#include "include/GenJet.h"
#include "include/useful_functions.h"
#include "include/constants.h"

using namespace std;

// Example usage:
//
// Tuplizer_NANOAOD /pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root /scratch/areimers/Tuples/LQDM/GENSIM/test.root


// TLorentzVector p4sumvis(vector<GenParticle> particles);
// vector<reco::GenParticle> finalDaughters(reco::GenParticle particle, vector<reco::GenParticle> daus);


int main(int argc, char* argv[]){


  if(argc != 3) throw runtime_error("Expected exactly two arguments. Usage: Tuplizer_NANOAOD <infilename> <outfilename>");
  string inarg  = argv[1];
  string outarg = argv[2];

  TString infilename = (TString)inarg;
  TString outfilename = (TString)outarg;
  cout << green << "--> Tuplizing input file: " << infilename << reset << endl;
  cout << green << "--> Output file will be: " << outfilename << reset << endl;
  TFile* infile = TFile::Open(infilename, "READ");

  // const vector<int> npids = get_npids();
  Event* event;
  Met* met;
  Met* genmet_invis;
  double weight;
  vector<GenParticle>* gps_hard;
  vector<GenParticle>* gps_final;
  vector<GenParticle>* gps_tauvis;
  vector<GenJet>*      genjets;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");
  tree->Branch("Event", &event);

  TTreeReader reader("Events", infile);
  TTreeReaderValue<float> met_pt(reader, "MET_pt");
  TTreeReaderValue<float> met_phi(reader, "MET_phi");
  TTreeReaderValue<float> genWeight(reader, "genWeight");

  int idx = 0;
  while (reader.Next()) {
    if(((idx+1) % 500 == 0) || idx == 0) cout << green << "    --> At event: " << idx+1 << reset << endl;
    cout << "new event " << endl;

    // GenParticle gp_dummy;
    gps_hard     = new vector<GenParticle>;
    gps_final    = new vector<GenParticle>;
    gps_tauvis   = new vector<GenParticle>;
    genjets      = new vector<GenJet>;
    met          = new Met;
    genmet_invis = new Met;
    event        = new Event;
    weight       = 1.;
    cout << "after 'new'" << endl;

    // gps_hard->emplace_back(gp_dummy);
    // gps_hard->emplace_back(gp_dummy);
    met->set_pt(*met_pt);
    met->set_phi(*met_phi);
    // genmet_invis->set_pt(*met_pt);
    // genmet_invis->set_phi(*met_phi);
    // weight = *genWeight;
    // met.set_pt(*met_pt);
    // cout << "after setting met pt " << endl;
    // met.set_phi(*met_phi);
    // genmet_invis.set_pt(*met_pt);
    // genmet_invis.set_phi(*met_phi);
    // weight = *genWeight;
    // cout << "after setting members" << endl;
    //
    event->genmet = met;
    event->genmet_invis = genmet_invis;
    event->genparticles_hard = gps_hard;
    event->genparticles_final = gps_final;
    event->genparticles_visibletaus = gps_tauvis;
    event->genjets = genjets;
    event->weight = weight;
    tree->Fill();
    idx ++;
    // delete gps_final;
    // delete gps_hard;
    // delete gps_tauvis;
    // delete met;
    // delete genmet_invis;
    // delete genjets;
    event->clear();
    cout << "Done with one event" << endl;
  }


  tree->Write();
  outfile->Close();
  delete event;
  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
