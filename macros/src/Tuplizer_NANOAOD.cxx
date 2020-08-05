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
  GenContent* gencontent;
  cout << "after creation" << endl;
  Met* met;
  Met* met_from_invis;
  double weight;
  vector<GenParticle>* gps_hard;
  vector<GenParticle>* gps_final;
  vector<GenParticle>* gps_tauvis;
  vector<GenJet>*      genjets;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");

  tree->Branch("Event", &event);
  // tree->Branch("Event", &gencontent);


  TTreeReader reader("Events", infile);
  TTreeReaderValue<float> met_pt(reader, "MET_pt");
  TTreeReaderValue<float> met_phi(reader, "MET_phi");
  TTreeReaderValue<float> genWeight(reader, "genWeight");

  int idx = 0;
  while (reader.Next()) {
    if(((idx+1) % 500 == 0) || idx == 0) cout << green << "    --> At event: " << idx+1 << reset << endl;
    cout << "new event " << endl;

    // Met met;
    // Met met_from_invis;
    // double weight;
    // vector<GenParticle> gps_hard;
    // vector<GenParticle> gps_final;
    // vector<GenParticle> gps_tauvis;
    // vector<GenJet>      genjets;


    // GenParticle gp_dummy;
    gps_hard               = new vector<GenParticle>;
    gps_final              = new vector<GenParticle>;
    gps_tauvis             = new vector<GenParticle>;
    genjets                = new vector<GenJet>;
    met                    = new Met;
    met_from_invis         = new Met;
    gencontent             = new GenContent;
    event                  = new Event;
    weight                 = 1.;
    cout << "after 'new'" << endl;

    // gps_hard->emplace_back(gp_dummy);
    // gps_hard->emplace_back(gp_dummy);
    met->set_pt(*met_pt);
    met->set_phi(*met_phi);
    // met_from_invis->set_pt(*met_pt);
    // met_from_invis->set_phi(*met_phi);
    // weight = *genWeight;
    // met.set_pt(*met_pt);
    // cout << "after setting met pt " << endl;
    // met.set_phi(*met_phi);
    // met_from_invis.set_pt(*met_pt);
    // met_from_invis.set_phi(*met_phi);
    // weight = *genWeight;
    // cout << "after setting members" << endl;
    //
    // // gencontent->genmet = met;
    // // gencontent->met_from_invis = met_from_invis;
    // // gencontent->genparticles_hard = gps_hard;
    // // gencontent->genparticles_final = gps_final;
    // // gencontent->genparticles_visibletaus = gps_tauvis;
    // // gencontent->genjets = genjets;
    gencontent->genmet = met;
    gencontent->met_from_invis = met_from_invis;
    gencontent->genparticles_hard = gps_hard;
    gencontent->genparticles_final = gps_final;
    gencontent->genparticles_visibletaus = gps_tauvis;
    gencontent->genjets = genjets;
    // cout << "after setting gencontent" << endl;
    //
    event->gencontent = gencontent;
    event->weight = weight;
    cout << "after setting event->weight" << endl;
    tree->Fill();
    cout << "after filling tree" << endl;
    idx ++;
    cout << "before delete" << endl;
    // delete gps_final;
    // delete gps_hard;
    // delete gps_tauvis;
    // delete met;
    // delete met_from_invis;
    // delete genjets;
    // delete gencontent;
    cout << "Done with one event" << endl;
  }


  tree->Write();
  outfile->Close();
  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
