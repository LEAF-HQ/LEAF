#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
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
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#pragma GCC diagnostic pop

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
  fwlite::Handle<double> handle_rho;
  fwlite::Handle< std::vector<reco::Vertex> > handle_pvs;


  fwlite::Event ev(infile);

  int idx = 0;
  for( ev.toBegin(); ! ev.atEnd(); ++ev) {


    handle_jets     .getByLabel(ev, "slimmedJets");
    handle_muons    .getByLabel(ev, "slimmedMuons");
    handle_electrons.getByLabel(ev, "slimmedElectrons");
    handle_taus     .getByLabel(ev, "slimmedTaus");
    handle_met      .getByLabel(ev, "slimmedMETs");
    handle_rho      .getByLabel(ev, "fixedGridRhoFastjetAll");
    handle_pvs      .getByLabel(ev, "offlineSlimmedPrimaryVertices");

    const std::vector<pat::Jet, std::allocator<pat::Jet>>*           jets       = handle_jets.product();
    const std::vector<pat::Muon, std::allocator<pat::Muon>>*         muons      = handle_muons.product();
    const std::vector<pat::Electron, std::allocator<pat::Electron>>* electrons  = handle_electrons.product();
    const std::vector<pat::Tau, std::allocator<pat::Tau>>*           taus       = handle_taus.product();
    const std::vector<pat::MET, std::allocator<pat::MET>>*           mets       = handle_met.product();
    const double*                                                    rho        = handle_rho.product();
    const std::vector<reco::Vertex, std::allocator<reco::Vertex>>*   pvs        = handle_pvs.product();
    if(idx < idx_start){
      idx++;
      continue;
    }
    if(idx >= idx_stop) break;
    // cout << "+++++++++++++ NEW EVENT" << endl;
    if(((idx+1) % 1000 == 0) || idx == 0) cout << green << "    --> At event: " << idx-idx_start+1 << reset << endl;



    // Do general event-based variables
    // ================================

    event.is_data = !is_mc;
    event.run = ev.id().run();
    event.number = ev.id().event();
    event.lumiblock = ev.luminosityBlock();
    event.rho = *rho;
    event.npv = pvs->size();
    int n_goodpvs = 0;
    for(size_t i=0; i<pvs->size(); i++){
      reco::Vertex pv = pvs->at(i);
      if(!pv.isFake() && pv.ndof() > 4 && fabs(pv.z()) < 24 && pv.position().rho() <= 2) n_goodpvs++;
    }
    event.npv_good = n_goodpvs;

    if(is_mc){

      // event.weight = genweight;
    }
    else{
      event.weight = 1.;
    }


    // Do MET
    // ======
    event.met->set_pt(mets->at(0).pt());
    event.met->set_phi(mets->at(0).phi());

    // Do raw MET
    // ==========
    event.rawmet->set_pt(mets->at(0).uncorPt());
    event.rawmet->set_phi(mets->at(0).uncorPhi());


    // Do Jets
    // =======

    for(size_t i=0; i<jets->size(); i++){
      pat::Jet patjet = jets->at(i);
      Jet j;

      j.set_pt(patjet.pt());
      j.set_eta(patjet.eta());
      j.set_phi(patjet.phi());
      j.set_m(patjet.mass());
      if(is_mc){
        j.set_parton_flavor(patjet.partonFlavour());
        j.set_hadron_flavor(patjet.hadronFlavour());
      }
      j.set_n_constituents(patjet.chargedMultiplicity()+patjet.neutralMultiplicity());
      j.set_area(patjet.jetArea());
      j.set_identifier(i); // to keep track of leptons associated to this jet
      j.set_ne_em_efrac (patjet.neutralEmEnergyFraction());
      j.set_ne_had_efrac (patjet.neutralHadronEnergyFraction());
      j.set_ch_em_efrac (patjet.chargedEmEnergyFraction());
      j.set_ch_had_efrac (patjet.chargedHadronEnergyFraction());
      j.set_mu_efrac (patjet.muonEnergyFraction());
      j.set_n_muons (patjet.muonMultiplicity());
      j.set_n_electrons (patjet.electronMultiplicity());
      j.set_raw_factor(patjet.jecFactor("Uncorrected"));
      j.set_L1_factor(patjet.correctedJet("L1FastJet").pt() / patjet.correctedJet("Uncorrected").pt());

      j.set_score_CSVv2(patjet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
      j.set_score_DeepB(patjet.bDiscriminator("pfDeepCSVJetTags:probb") + patjet.bDiscriminator("pfDeepCSVJetTags:probb"));
      j.set_score_DeepFlavB(patjet.bDiscriminator("pfDeepFlavourJetTags:probb") + patjet.bDiscriminator("pfDeepFlavourJetTags:probbb") + patjet.bDiscriminator("pfDeepFlavourJetTags:problepb"));
      j.set_pu_id(patjet.userInt("pileupJetId:fullId"));
      j.set_score_qgl(patjet.userFloat("QGTagger:qgLikelihood"));

      // Calculate JetID on the fly
      float NHF  = patjet.neutralHadronEnergyFraction();
      float NEMF = patjet.neutralEmEnergyFraction();
      float CHF  = patjet.chargedHadronEnergyFraction();
      float MUF  = patjet.muonEnergyFraction();
      float CEMF = patjet.chargedEmEnergyFraction();
      int NumConst = patjet.chargedMultiplicity()+patjet.neutralMultiplicity();
      int NumNeutralParticles = patjet.neutralMultiplicity();
      int CHM = patjet.chargedMultiplicity();
      bool pass_tight = false;
      bool pass_tight_lepveto = false;
      if(fabs(patjet.eta()) <= 2.6){
        pass_tight = (NHF < 0.9 && NEMF < 0.9 && NumConst > 1 && CHF > 0 && CHM > 0);
        pass_tight_lepveto = (pass_tight && MUF < 0.8 && CEMF < 0.8);
      }
      else if(fabs(patjet.eta()) <= 2.7){
        pass_tight = (NHF < 0.9 && NEMF < 0.99 && CHM > 0);
        pass_tight_lepveto = (pass_tight && MUF < 0.8 && CEMF < 0.8);
      }
      else if(fabs(patjet.eta()) <= 3.0){
        pass_tight = (NEMF > 0.01 && NEMF < 0.99 && NumNeutralParticles > 1);
        pass_tight_lepveto = pass_tight;
      }
      else if(fabs(patjet.eta()) <= 5.0){
        pass_tight = (NHF > 0.2 && NEMF < 0.9 && NumNeutralParticles > 10);
        pass_tight_lepveto = pass_tight;
      }

      // NanoAOD-style
      j.set_jet_id(pass_tight*2 + pass_tight_lepveto*4);
      event.jets->emplace_back(j);
    }













    tree->Fill();
    event.reset();
    idx++;
  }

  event.clear();
  tree->Write();
  outfile->Close();

  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
