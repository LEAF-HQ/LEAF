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
  Event event;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");
  tree->Branch("Event", &event);

  TTreeReader reader("Events", infile);
  TTreeReaderValue<float> genmet_pt (reader, "GenMET_pt");
  TTreeReaderValue<float> genmet_phi(reader, "GenMET_phi");
  TTreeReaderValue<float> genWeight (reader, "genWeight");

  int idx = 0;
  while (reader.Next()) {
    if(((idx+1) % 500 == 0) || idx == 0) cout << green << "    --> At event: " << idx+1 << reset << endl;
    
    event.genmet->set_pt(*genmet_pt);
    event.genmet->set_phi(*genmet_phi);
    event.weight = *genWeight;

    tree->Fill();
    event.reset();
    idx++;
  }

  event.clear();
  tree->Write();
  outfile->Close();
  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
