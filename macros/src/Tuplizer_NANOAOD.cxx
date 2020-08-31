#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#include "include/RecoEvent.h"
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
  cout << green << "--> Output file will be:  " << outfilename << reset << endl;
  TFile* infile = TFile::Open(infilename, "READ");

  const vector<int> npids = get_npids();
  RecoEvent event;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");
  tree->Branch("Event", &event);

  TTreeReader reader("Events", infile);
  TTreeReaderValue<float> genmet_pt (reader, "GenMET_pt");
  TTreeReaderValue<float> genmet_phi(reader, "GenMET_phi");

  TTreeReaderValue<unsigned int> genjet_n(reader, "nGenJet");
  TTreeReaderArray<float> genjet_pt(reader, "GenJet_pt");
  TTreeReaderArray<float> genjet_eta(reader, "GenJet_eta");
  TTreeReaderArray<float> genjet_phi(reader, "GenJet_phi");
  TTreeReaderArray<float> genjet_mass(reader, "GenJet_mass");

  TTreeReaderValue<unsigned int> genparticle_n(reader, "nGenPart");
  TTreeReaderArray<float> genparticle_pt(reader, "GenPart_pt");
  TTreeReaderArray<float> genparticle_eta(reader, "GenPart_eta");
  TTreeReaderArray<float> genparticle_phi(reader, "GenPart_phi");
  TTreeReaderArray<float> genparticle_mass(reader, "GenPart_mass");
  TTreeReaderArray<int> genparticle_pdgId(reader, "GenPart_pdgId");
  TTreeReaderArray<int> genparticle_statusFlags(reader, "GenPart_statusFlags");
  TTreeReaderArray<int> genparticle_status(reader, "GenPart_status");
  TTreeReaderArray<int> genparticle_idxmother(reader, "GenPart_genPartIdxMother");

  TTreeReaderValue<float> genWeight (reader, "genWeight");

  TTreeReaderValue<float> met_pt (reader, "MET_pt");
  TTreeReaderValue<float> met_phi (reader, "MET_phi");

  int idx = 0;
  while (reader.Next()) {
    // cout << "+++++++++++++ NEW EVENT" << endl;
    if(((idx+1) % 500 == 0) || idx == 0) cout << green << "    --> At event: " << idx+1 << reset << endl;

    // Do GenMET
    // =========

    event.genmet->set_pt(*genmet_pt);
    event.genmet->set_phi(*genmet_phi);

    // Do GenJets
    // ==========

    for(size_t i=0; i<*genjet_n; i++){
      GenJet gj;
      gj.set_p4(genjet_pt[i], genjet_eta[i], genjet_phi[i], genjet_mass[i]);

      // // remove NP particles that have been clustered into a jet from the jet. Only happens for DM.
      // for(size_t j=0; j<gjs->at(i).getGenConstituents().size(); j++){
      //   int id = abs(gjs->at(i).getGenConstituents().at(j)->pdgId());
      //   for(size_t k=0; k<npids.size(); k++){
      //     if(id == npids[k]){
      //
      //       //Get NP 4-momentum
      //       GenParticle np;
      //       np.set_p4(gjs->at(i).getGenConstituents().at(j)->pt(), gjs->at(i).getGenConstituents().at(j)->eta(), gjs->at(i).getGenConstituents().at(j)->phi(), gjs->at(i).getGenConstituents().at(j)->mass());
      //
      //       //Remove np 4-momentum
      //       gj.set_p4(gj.p4() - np.p4());
      //       n_const_removed++;
      //     }
      //   }
      // }

      // save only genjets with at least 10 GeV (NanoAOD cut) and |eta| < 5
      if(gj.pt() < 10. || fabs(gj.eta()) > 5.) continue;
      event.genjets->emplace_back(gj);
    }

    // Do GenParticles
    // ===============

    int flag_ishard = pow(2, 7);
    int flag_isfinal = pow(2, 13);
    int flag_isfromhardtau = pow(2, 9); //isHardProcessTauDecayProduct in https://github.com/cms-sw/cmssw/blob/master/DataFormats/HepMCCandidate/interface/GenStatusFlags.h
    for(size_t i=0; i<*genparticle_n; i++){
      int id = fabs(genparticle_pdgId[i]);
      int status_flag = genparticle_statusFlags[i];
      // cout << "int status flag: " << status_flag << endl;
      // cout << "bin status flag: " << std::bitset<32>(status_flag).to_string() << endl;
      // cout << "bin (128):       " << std::bitset<32>(128).to_string() << endl;
      bool is_hard = ((flag_ishard&status_flag) == flag_ishard);
      bool is_final = ((flag_isfinal&status_flag) == flag_isfinal);
      bool keepfinal = false;
      // bool is_finalstate = (genparticle_status[i] == 1);
      // bool is_fromhardtau = ((flag_isfromhardtau&status_flag) == flag_isfromhardtau);
      GenParticle gp;
      gp.set_p4(genjet_pt[i], genjet_eta[i], genjet_phi[i], genjet_mass[i]);
      gp.set_pdgid(genparticle_pdgId[i]);

      if(is_final){
        //keep, if final particle is b, t, tau, or nutau
        for(size_t j=0; j<npids.size(); j++){
          if(id == npids[j]) keepfinal = true;
        }
        if(id == 5 || id == 6 || id == 15 || id == 16) keepfinal = true;
      }
      if(keepfinal){
        event.genparticles_final->emplace_back(gp);
        // if(gp.eta() > 10) cout << "Final particle, id: " << id << ", eta: " << gp.eta() << ", pt: " << gp.pt() << endl;
      }
      if(is_hard){
        event.genparticles_hard->emplace_back(gp);
      }

      // find the visible parts of the taus from the hard process
      if (id == 15 && is_final){
        // cout << "found tau with index " << i << endl;
        TLorentzVector p4_vis;
        for(size_t j=0; j<*genparticle_n; j++){
          if(fabs(genparticle_pdgId[j]) == 12 || fabs(genparticle_pdgId[j]) == 14 || fabs(genparticle_pdgId[j]) == 16) continue;
          int thisstatusflag = genparticle_statusFlags[j];
          // if(is_fromhardtau && is_finalstate){
          if(((flag_isfromhardtau&thisstatusflag) == flag_isfromhardtau) && (genparticle_status[j] == 1)){

            // check if this stable particle comes from this tau or another one. Go backwards in the chain.
            unsigned int checkidx = genparticle_idxmother[j];
            while(fabs(genparticle_pdgId[checkidx]) != 15){
              checkidx = genparticle_idxmother[checkidx];
            }
            // cout << "Genparticle " << j << " belongs to tau with index " << checkidx << endl;
            // in this case, particle j indeed comes from this tau.
            if(checkidx == i){
              // cout << "genparticle " << j << " (id = " << fabs(genparticle_pdgId[j]) << ") belongs to this tau!" << endl;
              TLorentzVector v;
              v.SetPtEtaPhiM(genparticle_pt[j], genparticle_eta[j], genparticle_phi[j], genparticle_mass[j]);
              // cout << "with pt: " << v.Pt() << endl;
              p4_vis += v;
              // cout << "new visible pt: " << p4_vis.Pt() << endl;
            }

          }
        }
        GenParticle taudau_vis;
        taudau_vis.set_p4(p4_vis);
        taudau_vis.set_pdgid(genparticle_pdgId[i]);
        event.genparticles_visibletaus->emplace_back(taudau_vis);
      }

    }

    // Do Genweight
    // ============
    event.weight = *genWeight;

    // Do MET
    // ======
    event.met->set_pt(*met_pt);
    event.met->set_phi(*met_phi);

    tree->Fill();
    event.reset();
    idx++;
  }

  event.clear();
  tree->Write();
  outfile->Close();
  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
