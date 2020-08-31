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
#include "include/Jet.h"
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

  TTreeReaderValue<unsigned int> jet_n(reader, "nJet");
  TTreeReaderArray<float> jet_area(reader, "Jet_area");
  TTreeReaderArray<float> jet_score_CSVv2(reader, "Jet_btagCSVV2");
  TTreeReaderArray<float> jet_score_DeepB(reader, "Jet_btagDeepB");
  TTreeReaderArray<float> jet_score_qgl(reader, "Jet_qgl");
  TTreeReaderArray<float> jet_ch_em_efrac(reader, "Jet_chEmEF");
  TTreeReaderArray<float> jet_ch_had_efrac(reader, "Jet_chHEF");
  TTreeReaderArray<float> jet_ne_em_efrac(reader, "Jet_neEmEF");
  TTreeReaderArray<float> jet_ne_had_efrac(reader, "Jet_neHEF");
  TTreeReaderArray<float> jet_mu_efrac(reader, "Jet_muEF");
  TTreeReaderArray<int>   jet_jet_id(reader, "Jet_jetId");
  TTreeReaderArray<int>   jet_pu_id(reader, "Jet_puId");
  TTreeReaderArray<float> jet_raw_factor(reader, "Jet_rawFactor");
  TTreeReaderArray<float> jet_muon_sub_raw_factor(reader, "Jet_muonSubtrFactor");
  TTreeReaderArray<int>   jet_parton_flavor(reader, "Jet_partonFlavour");
  TTreeReaderArray<int>   jet_hadron_flavor(reader, "Jet_hadronFlavour");
  TTreeReaderArray<int>   jet_n_constituents(reader, "Jet_nConstituents");
  TTreeReaderArray<int>   jet_n_muons(reader, "Jet_nMuons");
  TTreeReaderArray<int>   jet_n_electrons(reader, "Jet_nElectrons");
  TTreeReaderArray<float> jet_pt(reader, "Jet_pt");
  TTreeReaderArray<float> jet_eta(reader, "Jet_eta");
  TTreeReaderArray<float> jet_phi(reader, "Jet_phi");
  TTreeReaderArray<float> jet_mass(reader, "Jet_mass");


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
      bool is_hard = ((flag_ishard&status_flag) == flag_ishard);
      bool is_final = ((flag_isfinal&status_flag) == flag_isfinal);
      bool keepfinal = false;
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
      }
      if(is_hard){
        event.genparticles_hard->emplace_back(gp);
      }

      // find the visible parts of the taus from the hard process
      if (id == 15 && is_final){
        TLorentzVector p4_vis;
        for(size_t j=0; j<*genparticle_n; j++){
          if(fabs(genparticle_pdgId[j]) == 12 || fabs(genparticle_pdgId[j]) == 14 || fabs(genparticle_pdgId[j]) == 16) continue;
          int thisstatusflag = genparticle_statusFlags[j];
          //                  is_fromhardtau                             &&        is_finalstate
          if(((flag_isfromhardtau&thisstatusflag) == flag_isfromhardtau) && (genparticle_status[j] == 1)){

            // check if this stable particle comes from this tau or another one. Go backwards in the chain.
            unsigned int checkidx = genparticle_idxmother[j];
            while(fabs(genparticle_pdgId[checkidx]) != 15){
              checkidx = genparticle_idxmother[checkidx];
            }
            // if arriving here, particle j indeed comes from this tau.
            if(checkidx == i){
              TLorentzVector v;
              v.SetPtEtaPhiM(genparticle_pt[j], genparticle_eta[j], genparticle_phi[j], genparticle_mass[j]);
              p4_vis += v;
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

    // Do Jets
    // =======
    for(size_t i=0; i<*jet_n; i++){
      Jet j;
      j.set_area(jet_area[i]);
      j.set_score_CSVv2(jet_score_CSVv2[i]);
      j.set_score_DeepB(jet_score_DeepB[i]);
      j.set_score_qgl(jet_score_qgl[i]);
      j.set_ch_em_efrac(jet_ch_em_efrac[i]);
      j.set_ch_had_efrac(jet_ch_had_efrac[i]);
      j.set_ne_em_efrac(jet_ne_em_efrac[i]);
      j.set_ne_had_efrac(jet_ne_had_efrac[i]);
      j.set_mu_efrac(jet_mu_efrac[i]);
      j.set_jet_id(jet_jet_id[i]);
      j.set_pu_id(jet_pu_id[i]);
      j.set_raw_factor(jet_raw_factor[i]);
      j.set_muon_sub_raw_factor(jet_muon_sub_raw_factor[i]);
      j.set_parton_flavor(jet_parton_flavor[i]);
      j.set_hadron_flavor(jet_hadron_flavor[i]);
      j.set_n_constituents(jet_n_constituents[i]);
      j.set_n_muons(jet_n_muons[i]);
      j.set_n_electrons(jet_n_electrons[i]);
      j.set_pt(jet_pt[i]);
      j.set_eta(jet_eta[i]);
      j.set_phi(jet_phi[i]);
      j.set_m(jet_mass[i]);      
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
