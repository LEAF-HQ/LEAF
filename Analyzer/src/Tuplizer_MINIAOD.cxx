#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/CLHEP/interface/Migration.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/GenInfo.h"
#include "Analyzer/include/Flags.h"
#include "Analyzer/include/Met.h"
#include "Analyzer/include/TriggerObject.h"
#include "Analyzer/include/Particle.h"
#include "Analyzer/include/GenParticle.h"
#include "Analyzer/include/GenJet.h"
#include "Analyzer/include/Jet.h"
#include "Analyzer/include/useful_functions.h"
#include "Analyzer/include/constants.h"

using namespace std;

// Example usage:
//
// Tuplizer_MINIAOD /pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root /scratch/areimers/Tuples/LQDM/GENSIM/test.root


// TLorentzVector p4sumvis(vector<GenParticle> particles);
// vector<reco::GenParticle> finalDaughters(reco::GenParticle particle, vector<reco::GenParticle> daus);

// template class std::vector<GenParticle>;

int main(int argc, char* argv[]){


  if(argc != 6) throw runtime_error("Expected exactly five arguments. Usage: Tuplizer_MINIAOD <type> <infilename> <outfilename> <idx_start> <idx_stop>");
  TString type = (TString)argv[1];
  if(!(type == "MC" || type == "DATA")) throw runtime_error("Invalid event type specified, can be 'MC' or 'DATA'.");
  string inarg  = argv[2];
  string outarg = argv[3];
  string s_idx_start = argv[4]; // start including this idx
  string s_idx_stop = argv[5]; // stop BEFORE processing this idx
  int idx_start = stoi(s_idx_start);
  int idx_stop = stoi(s_idx_stop);

  bool is_mc = false;
  if(type == "MC") is_mc = true;
  TString infilename = (TString)inarg;
  TString outfilename = (TString)outarg;
  cout << green << "--> Tuplizing input file: " << infilename << reset << endl;
  cout << green << "--> Output file will be:  " << outfilename << reset << endl;
  TFile* infile = TFile::Open(infilename, "READ");

  const vector<int> npids = get_npids();
  RecoEvent event;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");
  tree->Branch("Events", &event);

  // int n_total = ((TTree*)infile->Get("Events"))->GetEntries();
  // cout << green << "--> Total number of events to be processed: " << n_total << reset << endl;

  // TTreeReader reader("Events", infile);

  fwlite::Handle<std::vector<pat::Jet> > handle_jets;
  fwlite::Handle<std::vector<pat::Muon>> handle_muons;
  fwlite::Handle<std::vector<pat::Electron>> handle_electrons;
  fwlite::Handle<std::vector<pat::Tau>> handle_taus;
  fwlite::Handle<std::vector<pat::MET>> handle_met;


  fwlite::Event ev(infile);

  int idx = 0;
  // while (reader.Next()) {

  for( ev.toBegin(); ! ev.atEnd(); ++ev) {


    handle_jets     .getByLabel(ev, "slimmedJets");
    handle_muons    .getByLabel(ev, "slimmedMuons");
    handle_electrons.getByLabel(ev, "slimmedElectrons");
    handle_taus     .getByLabel(ev, "slimmedTaus");
    handle_met      .getByLabel(ev, "slimmedMet");
    const std::vector<pat::Jet, std::allocator<pat::Jet>>*           jets       = handle_jets.product();
    const std::vector<pat::Muon, std::allocator<pat::Muon>>*         muons      = handle_muons.product();
    const std::vector<pat::Electron, std::allocator<pat::Electron>>* electrons  = handle_electrons.product();
    const std::vector<pat::Tau, std::allocator<pat::Tau>>*           taus       = handle_taus.product();
    const std::vector<pat::MET, std::allocator<pat::MET>>*           mets       = handle_met.product();
    if(idx < idx_start){
      idx++;
      continue;
    }
    if(idx >= idx_stop) break;
    // cout << "+++++++++++++ NEW EVENT" << endl;
    if(((idx+1) % 1000 == 0) || idx == 0) cout << green << "    --> At event: " << idx-idx_start+1 << reset << endl;
    event.is_data = !is_mc;
    if(is_mc){

      // event.weight = genweight;
    }
    else{
      event.weight = 1.;
    }


    for(size_t i=0; i<jets->size(); i++){
      cout << "pt of jet " << i << ": " << jets->at(i).pt() << endl;
    }













    // tree->Fill();
    event.reset();
    idx++;
  }

  event.clear();
  // tree->OptimizeBaskets();
  tree->Write();
  outfile->Close();

  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
