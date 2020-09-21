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

  // AK4 CHS jets
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

  // Taus
  TTreeReaderValue<unsigned int> tau_n(reader, "nTau");
  TTreeReaderArray<int> tau_charge(reader, "Tau_charge");
  TTreeReaderArray<int> tau_decay_mode(reader, "Tau_decayMode");
  TTreeReaderArray<unsigned char> tau_gen_part_flav(reader, "Tau_genPartFlav");
  TTreeReaderArray<unsigned char> tau_id_deeptau_vse(reader, "Tau_idDeepTau2017v2p1VSe");
  TTreeReaderArray<unsigned char> tau_id_deeptau_vsmu(reader, "Tau_idDeepTau2017v2p1VSmu");
  TTreeReaderArray<unsigned char> tau_id_deeptau_vsjet(reader, "Tau_idDeepTau2017v2p1VSjet");
  TTreeReaderArray<float> tau_charged_iso(reader, "Tau_chargedIso");
  TTreeReaderArray<float> tau_neutral_iso(reader, "Tau_neutralIso");
  TTreeReaderArray<float> tau_dxy(reader, "Tau_dxy");
  TTreeReaderArray<float> tau_dz(reader, "Tau_dz");
  TTreeReaderArray<float> tau_pu_corr(reader, "Tau_puCorr");
  TTreeReaderArray<float> tau_score_deeptau_vse(reader, "Tau_rawDeepTau2017v2p1VSe");
  TTreeReaderArray<float> tau_score_deeptau_vsmu(reader, "Tau_rawDeepTau2017v2p1VSmu");
  TTreeReaderArray<float> tau_score_deeptau_vsjet(reader, "Tau_rawDeepTau2017v2p1VSjet");
  TTreeReaderArray<float> tau_comb_iso(reader, "Tau_rawIso");
  TTreeReaderArray<float> tau_comb_iso_dr03(reader, "Tau_rawIsodR03");
  TTreeReaderArray<float> tau_pt(reader, "Tau_pt");
  TTreeReaderArray<float> tau_eta(reader, "Tau_eta");
  TTreeReaderArray<float> tau_phi(reader, "Tau_phi");
  TTreeReaderArray<float> tau_mass(reader, "Tau_mass");

  // Muons
  TTreeReaderValue<unsigned int> muon_n(reader, "nMuon");
  TTreeReaderArray<bool>  muon_is_global(reader, "Muon_isGlobal");
  TTreeReaderArray<bool>  muon_is_pf(reader, "Muon_isPFcand");
  TTreeReaderArray<bool>  muon_is_tracker(reader, "Muon_isTracker");
  TTreeReaderArray<int>   muon_charge(reader, "Muon_charge");
  TTreeReaderArray<int>   muon_pdgid(reader, "Muon_pdgId");
  TTreeReaderArray<float> muon_dxy(reader, "Muon_dxy");
  TTreeReaderArray<float> muon_dz(reader, "Muon_dz");
  TTreeReaderArray<float> muon_iso_mini(reader, "Muon_miniPFRelIso_all");
  TTreeReaderArray<float> muon_iso_mini_charged(reader, "Muon_miniPFRelIso_chg");
  TTreeReaderArray<float> muon_iso_rel_04(reader, "Muon_pfRelIso04_all");
  TTreeReaderArray<float> muon_iso_rel_03(reader, "Muon_pfRelIso03_all");
  TTreeReaderArray<float> muon_iso_rel_03_charged(reader, "Muon_pfRelIso03_chg");
  TTreeReaderArray<float> muon_pt_err(reader, "Muon_ptErr");
  TTreeReaderArray<float> muon_iso_tk(reader, "Muon_tkRelIso");
  TTreeReaderArray<float> muon_pt_rel_tunep(reader, "Muon_tunepRelPt");
  TTreeReaderArray<float> muon_pt(reader,   "Muon_pt");
  TTreeReaderArray<float> muon_eta(reader,  "Muon_eta");
  TTreeReaderArray<float> muon_phi(reader,  "Muon_phi");
  TTreeReaderArray<float> muon_mass(reader, "Muon_mass");

  // get all muon IDs for "uint64_t m_selector_bits"
  TTreeReaderArray<unsigned char> muon_high_pt_id(reader, "Muon_highPtId");
  TTreeReaderArray<unsigned char> muon_mva_id(reader, "Muon_mvaId");
  TTreeReaderArray<bool> muon_loose_id(reader, "Muon_looseId");
  TTreeReaderArray<bool> muon_medium_id(reader, "Muon_mediumId");
  TTreeReaderArray<bool> muon_medium_prompt_id(reader, "Muon_mediumPromptId");
  TTreeReaderArray<bool> muon_tight_id(reader, "Muon_tightId");
  TTreeReaderArray<bool> muon_trigger_id_loose(reader, "Muon_triggerIdLoose");
  TTreeReaderArray<bool> muon_soft_id(reader, "Muon_softId");
  TTreeReaderArray<bool> muon_soft_mva_id(reader, "Muon_softMvaId");
  TTreeReaderArray<unsigned char> muon_mini_iso(reader, "Muon_miniIsoId");
  TTreeReaderArray<unsigned char> muon_multi_iso(reader, "Muon_multiIsoId");
  TTreeReaderArray<unsigned char> muon_pf_iso(reader, "Muon_pfIsoId");
  TTreeReaderArray<unsigned char> muon_puppi_iso(reader, "Muon_puppiIsoId");
  TTreeReaderArray<unsigned char> muon_tk_iso(reader, "Muon_tkIsoId");

  // for gen_part_flav
  TTreeReaderArray<unsigned char> muon_gen_part_flav(reader, "Muon_genPartFlav");




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

    // Do Taus
    // =======
    for(size_t i=0; i<*tau_n; i++){
      Tau t;

      t.set_charge(tau_charge[i]);
      t.set_decay_mode(tau_decay_mode[i]);
      t.set_gen_part_flav(tau_gen_part_flav[i]);
      t.set_id_deeptau_vse(tau_id_deeptau_vse[i]);
      t.set_id_deeptau_vsmu(tau_id_deeptau_vsmu[i]);
      t.set_id_deeptau_vsjet(tau_id_deeptau_vsjet[i]);
      t.set_charged_iso(tau_charged_iso[i]);
      t.set_neutral_iso(tau_neutral_iso[i]);
      t.set_dxy(tau_dxy[i]);
      t.set_dz(tau_dz[i]);
      t.set_pu_corr(tau_pu_corr[i]);
      t.set_score_deeptau_vse(tau_score_deeptau_vse[i]);
      t.set_score_deeptau_vsmu(tau_score_deeptau_vsmu[i]);
      t.set_score_deeptau_vsjet(tau_score_deeptau_vsjet[i]);
      t.set_comb_iso(tau_comb_iso[i]);
      t.set_comb_iso_dr03(tau_comb_iso_dr03[i]);
      t.set_pt(tau_pt[i]);
      t.set_eta(tau_eta[i]);
      t.set_phi(tau_phi[i]);
      t.set_m(tau_mass[i]);
      event.taus->emplace_back(t);
    }

    // Do Muons
    // =======
    for(size_t i=0; i<*muon_n; i++){
      Muon m;

      m.set_is_global(muon_is_global[i]);
      m.set_is_pf(muon_is_pf[i]);
      m.set_is_tracker(muon_is_tracker[i]);
      m.set_charge(muon_charge[i]);
      m.set_pdgid(muon_pdgid[i]);
      m.set_dxy(muon_dxy[i]);
      m.set_dz(muon_dz[i]);
      m.set_iso_mini(muon_iso_mini[i]);
      m.set_iso_mini_charged(muon_iso_mini_charged[i]);
      m.set_iso_rel_04(muon_iso_rel_04[i]);
      m.set_iso_rel_03(muon_iso_rel_03[i]);
      m.set_iso_rel_03_charged(muon_iso_rel_03_charged[i]);
      m.set_pt_err(muon_pt_err[i]);
      m.set_iso_tk(muon_iso_tk[i]);
      m.set_pt_rel_tunep(muon_pt_rel_tunep[i]);
      m.set_pt(muon_pt[i]);
      m.set_eta(muon_eta[i]);
      m.set_phi(muon_phi[i]);
      m.set_m(muon_mass[i]);

      //set ID bits
      m.set_selector(Muon::IDCutBasedGlobalHighPt, (muon_high_pt_id[i] == 2));
      m.set_selector(Muon::IDCutBasedTrackerHighPt, (muon_high_pt_id[i] == 1));
      m.set_selector(Muon::IDMvaSoft, (muon_soft_mva_id[i]));
      m.set_selector(Muon::IDMvaLoose, (muon_mva_id[i] == 1));
      m.set_selector(Muon::IDMvaMedium, (muon_mva_id[i] == 2));
      m.set_selector(Muon::IDMvaTight, (muon_mva_id[i] == 3));
      m.set_selector(Muon::IDMvaVTight, (muon_mva_id[i] == 4));
      m.set_selector(Muon::IDMvaVVTight, (muon_mva_id[i] == 5));
      m.set_selector(Muon::IDCutBasedSoft, (muon_soft_id[i]));
      m.set_selector(Muon::IDCutBasedLoose, (muon_loose_id[i]));
      m.set_selector(Muon::IDCutBasedMedium, (muon_medium_id[i]));
      m.set_selector(Muon::IDCutBasedMediumPrompt, (muon_medium_prompt_id[i]));
      m.set_selector(Muon::IDCutBasedTight, (muon_tight_id[i]));
      m.set_selector(Muon::IDTriggerLoose, (muon_trigger_id_loose[i]));

      m.set_selector(Muon::IsoMultiLoose, (muon_multi_iso[i] == 1));
      m.set_selector(Muon::IsoMultiMedium, (muon_multi_iso[i] == 2));
      m.set_selector(Muon::IsoPFVLoose, (muon_pf_iso[i] == 1));
      m.set_selector(Muon::IsoPFLoose, (muon_pf_iso[i] == 2));
      m.set_selector(Muon::IsoPFMedium, (muon_pf_iso[i] == 3));
      m.set_selector(Muon::IsoPFTight, (muon_pf_iso[i] == 4));
      m.set_selector(Muon::IsoPFVTight, (muon_pf_iso[i] == 5));
      m.set_selector(Muon::IsoPFVVTight, (muon_pf_iso[i] == 6));
      m.set_selector(Muon::IsoTkLoose, (muon_tk_iso[i] == 1));
      m.set_selector(Muon::IsoTkTight, (muon_tk_iso[i] == 2));
      m.set_selector(Muon::IsoPuppiLoose, (muon_puppi_iso[i] == 1));
      m.set_selector(Muon::IsoPuppiMedium, (muon_puppi_iso[i] == 2));
      m.set_selector(Muon::IsoPuppiTight, (muon_puppi_iso[i] == 3));
      m.set_selector(Muon::IsoMiniLoose, (muon_mini_iso[i] == 1));
      m.set_selector(Muon::IsoMiniMedium, (muon_mini_iso[i] == 2));
      m.set_selector(Muon::IsoMiniTight, (muon_mini_iso[i] == 3));
      m.set_selector(Muon::IsoMiniVTight, (muon_mini_iso[i] == 4));

      //gen_part_flav
      m.set_gen_part_flav((Muon::GenPartFlav)muon_gen_part_flav[i]);

      event.muons->emplace_back(m);
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
