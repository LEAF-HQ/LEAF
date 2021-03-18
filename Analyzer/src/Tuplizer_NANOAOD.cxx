#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
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
// Tuplizer_NANOAOD /pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root /scratch/areimers/Tuples/LQDM/GENSIM/test.root


// TLorentzVector p4sumvis(vector<GenParticle> particles);
// vector<reco::GenParticle> finalDaughters(reco::GenParticle particle, vector<reco::GenParticle> daus);

// template class std::vector<GenParticle>;

int main(int argc, char* argv[]){


  if(argc != 6) throw runtime_error("Expected exactly five arguments. Usage: Tuplizer_NANOAOD <type> <infilename> <outfilename> <idx_start> <idx_stop>");
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

  TTreeReader reader("Events", infile);
  TString varname = "MET_pt"; //dummy for data
  if(is_mc) varname = "GenMET_pt";
  TTreeReaderValue<float> genmet_pt(reader, varname);
  if(is_mc) varname = "GenMET_phi";
  TTreeReaderValue<float> genmet_phi(reader, varname);

  varname = "nJet"; //dummy
  if(is_mc) varname = "nGenJet";
  TTreeReaderValue<unsigned int> genjet_n(reader, varname);
  varname = "MET_pt"; //dummy for data
  if(is_mc) varname = "GenJet_pt";
  TTreeReaderArray<float> genjet_pt(reader, varname);
  if(is_mc) varname = "GenJet_eta";
  TTreeReaderArray<float> genjet_eta(reader, varname);
  if(is_mc) varname = "GenJet_phi";
  TTreeReaderArray<float> genjet_phi(reader, varname);
  if(is_mc) varname = "GenJet_mass";
  TTreeReaderArray<float> genjet_mass(reader, varname);


  varname = "nJet"; //dummy
  if(is_mc) varname = "nGenPart";
  TTreeReaderValue<unsigned int> genparticle_n(reader, varname);
  varname = "MET_pt"; //dummy
  if(is_mc) varname = "GenPart_pt";
  TTreeReaderArray<float> genparticle_pt(reader, varname);
  if(is_mc) varname = "GenPart_eta";
  TTreeReaderArray<float> genparticle_eta(reader, varname);
  if(is_mc) varname = "GenPart_phi";
  TTreeReaderArray<float> genparticle_phi(reader, varname);
  if(is_mc) varname = "GenPart_mass";
  TTreeReaderArray<float> genparticle_mass(reader, varname);
  varname = "Jet_jetId"; //dummys
  if(is_mc) varname = "GenPart_pdgId";
  TTreeReaderArray<int> genparticle_pdgId(reader, varname);
  if(is_mc) varname = "GenPart_statusFlags";
  TTreeReaderArray<int> genparticle_statusFlags(reader, varname);
  if(is_mc) varname = "GenPart_status";
  TTreeReaderArray<int> genparticle_status(reader, varname);
  if(is_mc) varname = "GenPart_genPartIdxMother";
  TTreeReaderArray<int> genparticle_idxmother(reader, varname);

  varname = "MET_pt"; //dummy for data
  if(is_mc) varname = "genWeight";
  TTreeReaderValue<float> genWeight (reader, varname);

  TTreeReaderValue<float> rho(reader, "fixedGridRhoFastjetAll");
  varname = "L1PreFiringWeight_Nom";
  TTreeReaderValue<float> weight_prefiring(reader, varname);
  varname = "L1PreFiringWeight_Up";
  TTreeReaderValue<float> weight_prefiring_up(reader, varname);
  varname = "L1PreFiringWeight_Dn";
  TTreeReaderValue<float> weight_prefiring_down(reader, varname);
  TTreeReaderValue<unsigned int> run(reader, "run");
  TTreeReaderValue<unsigned int> lumiblock(reader, "luminosityBlock");
  TTreeReaderValue<ULong64_t> number(reader, "event");
  TTreeReaderValue<int> npv(reader, "PV_npvs");
  TTreeReaderValue<int> npv_good(reader, "PV_npvsGood");
  varname = "PV_npvs";
  if(is_mc) varname = "Pileup_nPU";
  TTreeReaderValue<int> npu(reader, varname);
  varname = "fixedGridRhoFastjetAll";
  if(is_mc) varname = "Pileup_nTrueInt";
  TTreeReaderValue<float> ntrueint(reader, varname);

  // GenInfo
  TBranch* br_lhe = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("LHEWeight_originalXWGTUP");
  bool exists_lhe;
  if(br_lhe && is_mc) exists_lhe = true;
  else                exists_lhe = false;
  if(exists_lhe) varname = "LHEWeight_originalXWGTUP";
  TTreeReaderValue<float> geninfo_originalXWGTUP(reader, varname);
  if(exists_lhe) varname = "LHEScaleWeight";
  TTreeReaderArray<float> geninfo_systweights_scale(reader, varname);
  if(exists_lhe) varname = "LHEPdfWeight";
  TTreeReaderArray<float> geninfo_systweights_pdf(reader, varname);
  if(is_mc) varname = "Generator_weight";
  TTreeReaderValue<float> geninfo_weight(reader, varname);
  if(is_mc) varname = "Generator_binvar";
  TTreeReaderValue<float> geninfo_binvar(reader, varname);
  if(is_mc) varname = "Generator_scalePDF";
  TTreeReaderValue<float> geninfo_scale_pdf(reader, varname);
  if(is_mc) varname = "Generator_x1";
  TTreeReaderValue<float> geninfo_x1(reader, varname);
  if(is_mc) varname = "Generator_x2";
  TTreeReaderValue<float> geninfo_x2(reader, varname);
  if(is_mc) varname = "Generator_xpdf1";
  TTreeReaderValue<float> geninfo_xpdf1(reader, varname);
  if(is_mc) varname = "Generator_xpdf2";
  TTreeReaderValue<float> geninfo_xpdf2(reader, varname);
  varname = "PV_npvs";
  if(is_mc) varname = "Generator_id1";
  TTreeReaderValue<int>   geninfo_id1(reader, varname);
  if(is_mc) varname = "Generator_id2";
  TTreeReaderValue<int>   geninfo_id2(reader, varname);
  varname = "run";
  if(exists_lhe) varname = "nLHEPdfWeight";
  TTreeReaderValue<unsigned int> geninfo_n_systweights_pdf(reader, varname);
  if(exists_lhe) varname = "nLHEScaleWeight";
  TTreeReaderValue<unsigned int> geninfo_n_systweights_scale(reader, varname);

  // Flags
  TTreeReaderValue<bool> Flag_BadChargedCandidateFilter(reader, "Flag_BadChargedCandidateFilter");
  TTreeReaderValue<bool> Flag_BadChargedCandidateSummer16Filter(reader, "Flag_BadChargedCandidateSummer16Filter");
  TTreeReaderValue<bool> Flag_BadPFMuonFilter(reader, "Flag_BadPFMuonFilter");
  TTreeReaderValue<bool> Flag_BadPFMuonSummer16Filter(reader, "Flag_BadPFMuonSummer16Filter");
  TTreeReaderValue<bool> Flag_CSCTightHalo2015Filter(reader, "Flag_CSCTightHalo2015Filter");
  TTreeReaderValue<bool> Flag_CSCTightHaloFilter(reader, "Flag_CSCTightHaloFilter");
  TTreeReaderValue<bool> Flag_CSCTightHaloTrkMuUnvetoFilter(reader, "Flag_CSCTightHaloTrkMuUnvetoFilter");
  TTreeReaderValue<bool> Flag_EcalDeadCellBoundaryEnergyFilter(reader, "Flag_EcalDeadCellBoundaryEnergyFilter");
  TTreeReaderValue<bool> Flag_EcalDeadCellTriggerPrimitiveFilter(reader, "Flag_EcalDeadCellTriggerPrimitiveFilter");
  TTreeReaderValue<bool> Flag_HBHENoiseFilter(reader, "Flag_HBHENoiseFilter");
  TTreeReaderValue<bool> Flag_HBHENoiseIsoFilter(reader, "Flag_HBHENoiseIsoFilter");
  TTreeReaderValue<bool> Flag_HcalStripHaloFilter(reader, "Flag_HcalStripHaloFilter");
  TTreeReaderValue<bool> Flag_METFilters(reader, "Flag_METFilters");
  TTreeReaderValue<bool> Flag_chargedHadronTrackResolutionFilter(reader, "Flag_chargedHadronTrackResolutionFilter");
  TTreeReaderValue<bool> Flag_ecalBadCalibFilter(reader, "Flag_ecalBadCalibFilter");
  TTreeReaderValue<bool> Flag_ecalLaserCorrFilter(reader, "Flag_ecalLaserCorrFilter");
  TTreeReaderValue<bool> Flag_eeBadScFilter(reader, "Flag_eeBadScFilter");
  TTreeReaderValue<bool> Flag_globalSuperTightHalo2016Filter(reader, "Flag_globalSuperTightHalo2016Filter");
  TTreeReaderValue<bool> Flag_globalTightHalo2016Filter(reader, "Flag_globalTightHalo2016Filter");
  TTreeReaderValue<bool> Flag_goodVertices(reader, "Flag_goodVertices");
  TTreeReaderValue<bool> Flag_hcalLaserEventFilter(reader, "Flag_hcalLaserEventFilter");
  TTreeReaderValue<bool> Flag_muonBadTrackFilter(reader, "Flag_muonBadTrackFilter");
  TTreeReaderValue<bool> Flag_trkPOGFilters(reader, "Flag_trkPOGFilters");
  TTreeReaderValue<bool> Flag_trkPOG_logErrorTooManyClusters(reader, "Flag_trkPOG_logErrorTooManyClusters");
  TTreeReaderValue<bool> Flag_trkPOG_manystripclus53X(reader, "Flag_trkPOG_manystripclus53X");
  TTreeReaderValue<bool> Flag_trkPOG_toomanystripclus53X(reader, "Flag_trkPOG_toomanystripclus53X");

  // HLT
  TTreeReaderValue<bool> HLT_Ele27_WPTight_Gsf(reader, "HLT_Ele27_WPTight_Gsf");

  TBranch* br1 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_Ele32_WPTight_Gsf");
  bool exists_HLT_Ele32_WPTight_Gsf = true;
  if(br1) exists_HLT_Ele32_WPTight_Gsf = true;
  else   exists_HLT_Ele32_WPTight_Gsf = false;
  varname = "HLT_Ele32_WPTight_Gsf";
  if(!exists_HLT_Ele32_WPTight_Gsf) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_Ele32_WPTight_Gsf(reader, varname);

  TTreeReaderValue<bool> HLT_Ele35_WPTight_Gsf(reader, "HLT_Ele35_WPTight_Gsf");

  TBranch* br2 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_Ele115_CaloIdVT_GsfTrkIdT");
  bool exists_HLT_Ele115_CaloIdVT_GsfTrkIdT = true;
  if(br2) exists_HLT_Ele115_CaloIdVT_GsfTrkIdT = true;
  else   exists_HLT_Ele115_CaloIdVT_GsfTrkIdT = false;
  varname = "HLT_Ele115_CaloIdVT_GsfTrkIdT";
  if(!exists_HLT_Ele115_CaloIdVT_GsfTrkIdT) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_Ele115_CaloIdVT_GsfTrkIdT(reader, varname);

  TTreeReaderValue<bool> HLT_Photon200(reader, "HLT_Photon200");
  TTreeReaderValue<bool> HLT_Photon175(reader, "HLT_Photon175");
  TTreeReaderValue<bool> HLT_IsoMu24(reader, "HLT_IsoMu24");
  TTreeReaderValue<bool> HLT_IsoMu27(reader, "HLT_IsoMu27");
  TTreeReaderValue<bool> HLT_Mu50(reader, "HLT_Mu50");

  TBranch* br3 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_TkMu100");
  bool exists_HLT_TkMu100 = true;
  if(br3) exists_HLT_TkMu100 = true;
  else   exists_HLT_TkMu100 = false;
  varname = "HLT_TkMu100";
  if(!exists_HLT_TkMu100) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_TkMu100(reader, varname);



  TBranch* br4 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_OldMu100");
  bool exists_HLT_OldMu100 = true;
  if(br4) exists_HLT_OldMu100 = true;
  else    exists_HLT_OldMu100 = false;
  if(!exists_HLT_OldMu100) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_OldMu100(reader, varname);

  TTreeReaderValue<bool> HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg(reader, "HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg(reader, "HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg(reader, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg(reader, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg(reader, "HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg(reader, "HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg(reader, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg");
  TTreeReaderValue<bool> HLT_PFMET110_PFMHT110_IDTight(reader, "HLT_PFMET110_PFMHT110_IDTight");
  TTreeReaderValue<bool> HLT_PFMET120_PFMHT120_IDTight(reader, "HLT_PFMET120_PFMHT120_IDTight");
  TTreeReaderValue<bool> HLT_PFMET130_PFMHT130_IDTight(reader, "HLT_PFMET130_PFMHT130_IDTight");
  TTreeReaderValue<bool> HLT_PFMET140_PFMHT140_IDTight(reader, "HLT_PFMET140_PFMHT140_IDTight");
  TTreeReaderValue<bool> HLT_PFMETNoMu110_PFMHTNoMu110_IDTight(reader, "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight");
  TTreeReaderValue<bool> HLT_PFMETNoMu120_PFMHTNoMu120_IDTight(reader, "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight");

  TBranch* br5 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight");
  bool exists_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight = true;
  if(br5) exists_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight = true;
  else   exists_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight = false;
  varname = "HLT_PFMETNoMu130_PFMHTNoMu130_IDTight";
  if(!exists_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_PFMETNoMu130_PFMHTNoMu130_IDTight(reader, varname);

  TBranch* br6 = (TBranch*)((TTree*)infile->Get("Events"))->GetListOfBranches()->FindObject("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight");
  bool exists_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight = true;
  if(br6) exists_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight = true;
  else   exists_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight = false;
  varname = "HLT_PFMETNoMu140_PFMHTNoMu140_IDTight";
  if(!exists_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight) varname = "Flag_BadChargedCandidateFilter";
  TTreeReaderValue<bool> HLT_PFMETNoMu140_PFMHTNoMu140_IDTight(reader, varname);

  TTreeReaderValue<bool> HLT_PFMETTypeOne110_PFMHT110_IDTight(reader, "HLT_PFMETTypeOne110_PFMHT110_IDTight");
  TTreeReaderValue<bool> HLT_PFMETTypeOne120_PFMHT120_IDTight(reader, "HLT_PFMETTypeOne120_PFMHT120_IDTight");
  TTreeReaderValue<bool> HLT_PFMETTypeOne130_PFMHT130_IDTight(reader, "HLT_PFMETTypeOne130_PFMHT130_IDTight");
  TTreeReaderValue<bool> HLT_PFMETTypeOne140_PFMHT140_IDTight(reader, "HLT_PFMETTypeOne140_PFMHT140_IDTight");

  // MET
  TTreeReaderValue<float> met_pt  (reader, "MET_pt");
  TTreeReaderValue<float> met_phi (reader, "MET_phi");

  // raw MET
  TTreeReaderValue<float> rawmet_pt  (reader, "RawMET_pt");
  TTreeReaderValue<float> rawmet_phi (reader, "RawMET_phi");

  // Trigger Objects
  TTreeReaderValue<unsigned int> trigobj_n(reader, "nTrigObj");
  TTreeReaderArray<int> trigobj_id(reader, "TrigObj_id");
  TTreeReaderArray<int> trigobj_filter_bits(reader, "TrigObj_filterBits");
  TTreeReaderArray<float> trigobj_pt(reader, "TrigObj_pt");
  TTreeReaderArray<float> trigobj_eta(reader, "TrigObj_eta");
  TTreeReaderArray<float> trigobj_phi(reader, "TrigObj_phi");
  TTreeReaderArray<float> trigobj_l1pt(reader, "TrigObj_l1pt");
  TTreeReaderArray<float> trigobj_l1pt2(reader, "TrigObj_l1pt_2");
  TTreeReaderArray<int> trigobj_l1iso(reader, "TrigObj_l1iso");
  TTreeReaderArray<int> trigobj_l1charge(reader, "TrigObj_l1charge");
  TTreeReaderArray<float> trigobj_l2pt(reader, "TrigObj_l2pt");

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
  varname = "Jet_jetId";
  if(is_mc) varname = "Jet_partonFlavour";
  TTreeReaderArray<int>   jet_parton_flavor(reader, varname);
  if(is_mc) varname = "Jet_hadronFlavour";
  TTreeReaderArray<int>   jet_hadron_flavor(reader, varname);
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
  varname = "Tau_idDeepTau2017v2p1VSe";
  if(is_mc) varname = "Tau_genPartFlav";
  TTreeReaderArray<unsigned char> tau_gen_part_flav(reader, varname);
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
  TTreeReaderArray<int>   muon_jetidx(reader, "Muon_jetIdx");
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
  varname = "Muon_miniIsoId";
  if(is_mc) varname = "Muon_genPartFlav";
  TTreeReaderArray<unsigned char> muon_gen_part_flav(reader, varname);

  // Electrons
  TTreeReaderValue<unsigned int> electron_n(reader, "nElectron");
  TTreeReaderArray<int> electron_jetidx(reader, "Electron_jetIdx");
  TTreeReaderArray<int> electron_charge(reader, "Electron_charge");
  TTreeReaderArray<int> electron_id_bitmap(reader, "Electron_vidNestedWPBitmap");
  TTreeReaderArray<unsigned char> electron_lost_hits(reader, "Electron_lostHits");
  TTreeReaderArray<bool> electron_conv_veto(reader, "Electron_convVeto");
  TTreeReaderArray<bool> electron_is_pf(reader, "Electron_isPFcand");
  TTreeReaderArray<float> electron_delta_eta_sc(reader, "Electron_deltaEtaSC");
  TTreeReaderArray<float> electron_dxy(reader, "Electron_dxy");
  TTreeReaderArray<float> electron_dz(reader, "Electron_dz");
  TTreeReaderArray<float> electron_einv_minus_pinv(reader, "Electron_eInvMinusPInv");
  TTreeReaderArray<float> electron_h_over_e(reader, "Electron_hoe");
  TTreeReaderArray<float> electron_ip_3d(reader, "Electron_ip3d");
  TTreeReaderArray<float> electron_iso_rel_03(reader, "Electron_pfRelIso03_all");
  TTreeReaderArray<float> electron_iso_rel_03_charged(reader, "Electron_pfRelIso03_all");
  TTreeReaderArray<float> electron_sigma_ietaieta(reader, "Electron_sieie");
  TTreeReaderArray<float> electron_pt(reader,   "Electron_pt");
  TTreeReaderArray<float> electron_eta(reader,  "Electron_eta");
  TTreeReaderArray<float> electron_phi(reader,  "Electron_phi");
  TTreeReaderArray<float> electron_mass(reader, "Electron_mass");
  // uint64_t m_selector_bits
  TTreeReaderArray<int> electron_cut_based_id(reader, "Electron_cutBased");
  TTreeReaderArray<bool> electron_heep_id(reader, "Electron_cutBased_HEEP");
  TTreeReaderArray<bool> electron_mva_id_iso_loose(reader, "Electron_mvaFall17V2Iso_WPL");
  TTreeReaderArray<bool> electron_mva_id_iso_90(reader, "Electron_mvaFall17V2Iso_WP90");
  TTreeReaderArray<bool> electron_mva_id_iso_80(reader, "Electron_mvaFall17V2Iso_WP80");
  TTreeReaderArray<bool> electron_mva_id_noniso_loose(reader, "Electron_mvaFall17V2noIso_WPL");
  TTreeReaderArray<bool> electron_mva_id_noniso_90(reader, "Electron_mvaFall17V2noIso_WP90");
  TTreeReaderArray<bool> electron_mva_id_noniso_80(reader, "Electron_mvaFall17V2noIso_WP80");




  int idx = 0;
  while (reader.Next()) {
    if(idx < idx_start){
      idx++;
      continue;
    }
    if(idx >= idx_stop) break;
    // cout << "+++++++++++++ NEW EVENT" << endl;
    if(((idx+1) % 1000 == 0) || idx == 0) cout << green << "    --> At event: " << idx-idx_start+1 << reset << endl;
    event.is_data = !is_mc;
    if(is_mc){
      // Do GenMET
      // =========
      event.genmet->set_pt(*genmet_pt);
      event.genmet->set_phi(*genmet_phi);

      // Do GenJets
      // ==========
      for(size_t i=0; i<*genjet_n; i++){
        GenJet gj;
        gj.set_p4(genjet_pt[i], genjet_eta[i], genjet_phi[i], genjet_mass[i]);

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
          // event.genevent->genparticles_final->emplace_back(gp);
        }
        if(is_hard){
          event.genparticles_hard->emplace_back(gp);
          // event.genevent->genparticles_hard->emplace_back(gp);
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
    }
    else{
      event.weight = 1.;
    }

    // Do general event-based variables
    // ================================
    event.rho = *rho;
    event.run = *run;
    event.lumiblock = *lumiblock;
    event.number = *number;
    event.npv = *npv;
    event.npv_good = *npv_good;
    event.weight_prefiring = *weight_prefiring;
    event.weight_prefiring_up = *weight_prefiring_up;
    event.weight_prefiring_down = *weight_prefiring_down;
    if(is_mc){
      event.npu = *npu;
      event.ntrueint = *ntrueint;
    }


    // Do GenInfo
    // ==========
    if(is_mc){
      if(exists_lhe){
        vector<float> vector_systweights_pdf = {};
        for(size_t i=0; i<*geninfo_n_systweights_pdf; i++){
          vector_systweights_pdf.emplace_back(geninfo_systweights_pdf[i]);
        }
        event.geninfo->set_systweights_pdf(vector_systweights_pdf);

        vector<float> vector_systweights_scale = {};
        for(size_t i=0; i<*geninfo_n_systweights_scale; i++){
          vector_systweights_scale.emplace_back(geninfo_systweights_scale[i]);
        }
        event.geninfo->set_systweights_scale(vector_systweights_scale);
        event.geninfo->set_originalXWGTUP(*geninfo_originalXWGTUP);
      }

      event.geninfo->set_binvar(*geninfo_binvar);
      event.geninfo->set_id1(*geninfo_id1);
      event.geninfo->set_id2(*geninfo_id2);
      event.geninfo->set_scale_pdf(*geninfo_scale_pdf);
      event.geninfo->set_weight(*geninfo_weight);
      event.geninfo->set_x1(*geninfo_x1);
      event.geninfo->set_x2(*geninfo_x2);
      event.geninfo->set_xpdf1(*geninfo_xpdf1);
      event.geninfo->set_xpdf2(*geninfo_xpdf2);
    }


    // Do HLT flags
    // ============
    event.flags->set("Flag_BadChargedCandidateFilter", *Flag_BadChargedCandidateFilter);
    event.flags->set("Flag_BadChargedCandidateSummer16Filter", *Flag_BadChargedCandidateSummer16Filter);
    event.flags->set("Flag_BadPFMuonFilter", *Flag_BadPFMuonFilter);
    event.flags->set("Flag_BadPFMuonSummer16Filter", *Flag_BadPFMuonSummer16Filter);
    event.flags->set("Flag_CSCTightHalo2015Filter", *Flag_CSCTightHalo2015Filter);
    event.flags->set("Flag_CSCTightHaloFilter", *Flag_CSCTightHaloFilter);
    event.flags->set("Flag_CSCTightHaloTrkMuUnvetoFilter", *Flag_CSCTightHaloTrkMuUnvetoFilter);
    event.flags->set("Flag_EcalDeadCellBoundaryEnergyFilter", *Flag_EcalDeadCellBoundaryEnergyFilter);
    event.flags->set("Flag_EcalDeadCellTriggerPrimitiveFilter", *Flag_EcalDeadCellTriggerPrimitiveFilter);
    event.flags->set("Flag_HBHENoiseFilter", *Flag_HBHENoiseFilter);
    event.flags->set("Flag_HBHENoiseIsoFilter", *Flag_HBHENoiseIsoFilter);
    event.flags->set("Flag_HcalStripHaloFilter", *Flag_HcalStripHaloFilter);
    event.flags->set("Flag_METFilters", *Flag_METFilters);
    event.flags->set("Flag_chargedHadronTrackResolutionFilter", *Flag_chargedHadronTrackResolutionFilter);
    event.flags->set("Flag_ecalBadCalibFilter", *Flag_ecalBadCalibFilter);
    event.flags->set("Flag_ecalLaserCorrFilter", *Flag_ecalLaserCorrFilter);
    event.flags->set("Flag_eeBadScFilter", *Flag_eeBadScFilter);
    event.flags->set("Flag_globalSuperTightHalo2016Filter", *Flag_globalSuperTightHalo2016Filter);
    event.flags->set("Flag_globalTightHalo2016Filter", *Flag_globalTightHalo2016Filter);
    event.flags->set("Flag_goodVertices", *Flag_goodVertices);
    event.flags->set("Flag_hcalLaserEventFilter", *Flag_hcalLaserEventFilter);
    event.flags->set("Flag_muonBadTrackFilter", *Flag_muonBadTrackFilter);
    event.flags->set("Flag_trkPOGFilters", *Flag_trkPOGFilters);
    event.flags->set("Flag_trkPOG_logErrorTooManyClusters", *Flag_trkPOG_logErrorTooManyClusters);
    event.flags->set("Flag_trkPOG_manystripclus53X", *Flag_trkPOG_manystripclus53X);
    event.flags->set("Flag_trkPOG_toomanystripclus53X", *Flag_trkPOG_toomanystripclus53X);

    event.flags->set("HLT_Ele27_WPTight_Gsf", *HLT_Ele27_WPTight_Gsf);
    if(exists_HLT_Ele32_WPTight_Gsf){
      event.flags->set("HLT_Ele32_WPTight_Gsf", *HLT_Ele32_WPTight_Gsf);
    }
    // else{
    //   event.flags->set("HLT_Ele32_WPTight_Gsf", false);
    // }

    event.flags->set("HLT_Ele35_WPTight_Gsf", *HLT_Ele35_WPTight_Gsf);

    // event.flags->set("HLT_Ele32_WPTight_Gsf", *HLT_Ele32_WPTight_Gsf);
    if(exists_HLT_Ele115_CaloIdVT_GsfTrkIdT){
      event.flags->set("HLT_Ele115_CaloIdVT_GsfTrkIdT", *HLT_Ele115_CaloIdVT_GsfTrkIdT);
    }
    // else{
    //   event.flags->set("HLT_Ele115_CaloIdVT_GsfTrkIdT", false);
    // }
    event.flags->set("HLT_Photon200", *HLT_Photon200);
    event.flags->set("HLT_Photon175", *HLT_Photon175);
    event.flags->set("HLT_IsoMu24", *HLT_IsoMu24);
    event.flags->set("HLT_IsoMu27", *HLT_IsoMu27);
    event.flags->set("HLT_Mu50", *HLT_Mu50);

    if(exists_HLT_TkMu100){
      event.flags->set("HLT_TkMu100", *HLT_TkMu100);
    }
    // else{
    //   event.flags->set("HLT_TkMu100", false);
    // }

    if(exists_HLT_OldMu100){
      event.flags->set("HLT_OldMu100", *HLT_OldMu100);
    }
    // else{
    //   event.flags->set("HLT_OldMu100", false);
    // }
    event.flags->set("HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", *HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg", *HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg);
    event.flags->set("HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", *HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg", *HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg);
    event.flags->set("HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", *HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg", *HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg);
    event.flags->set("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", *HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg", *HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg);
    event.flags->set("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", *HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg", *HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg);
    event.flags->set("HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", *HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);
    event.flags->set("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg", *HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg);
    event.flags->set("HLT_PFMET110_PFMHT110_IDTight", *HLT_PFMET110_PFMHT110_IDTight);
    event.flags->set("HLT_PFMET120_PFMHT120_IDTight", *HLT_PFMET120_PFMHT120_IDTight);
    event.flags->set("HLT_PFMET130_PFMHT130_IDTight", *HLT_PFMET130_PFMHT130_IDTight);
    event.flags->set("HLT_PFMET140_PFMHT140_IDTight", *HLT_PFMET140_PFMHT140_IDTight);
    event.flags->set("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight", *HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
    event.flags->set("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", *HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);

    if(exists_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight){
      event.flags->set("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight", *HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
    }

    if(exists_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight){
      event.flags->set("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight", *HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
    }
    event.flags->set("HLT_PFMETTypeOne110_PFMHT110_IDTight", *HLT_PFMETTypeOne110_PFMHT110_IDTight);
    event.flags->set("HLT_PFMETTypeOne120_PFMHT120_IDTight", *HLT_PFMETTypeOne120_PFMHT120_IDTight);
    event.flags->set("HLT_PFMETTypeOne130_PFMHT130_IDTight", *HLT_PFMETTypeOne130_PFMHT130_IDTight);
    event.flags->set("HLT_PFMETTypeOne140_PFMHT140_IDTight", *HLT_PFMETTypeOne140_PFMHT140_IDTight);






    // Do MET
    // ======
    event.met->set_pt(*met_pt);
    event.met->set_phi(*met_phi);

    // Do raw MET
    // ======
    event.rawmet->set_pt(*rawmet_pt);
    event.rawmet->set_phi(*rawmet_phi);

    // Do Trigger Objects
    // ==================
    for(size_t i=0; i<*trigobj_n; i++){
      TriggerObject t;

      t.set_id((TriggerObject::ID)trigobj_id[i]);
      t.set_filter_bits(trigobj_filter_bits[i]);
      t.set_pt(trigobj_pt[i]);
      t.set_eta(trigobj_eta[i]);
      t.set_phi(trigobj_phi[i]);
      t.set_l1pt(trigobj_l1pt[i]);
      t.set_l1pt2(trigobj_l1pt2[i]);
      t.set_l1iso(trigobj_l1iso[i]);
      t.set_l1charge(trigobj_l1charge[i]);
      t.set_l2pt(trigobj_l2pt[i]);

      event.triggerobjects->emplace_back(t);
    }

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
      j.set_raw_factor(1 - jet_raw_factor[i]); // NanoAOD: raw_factor = 1 - (factor_to_get_back_to_raw) <--> custom tuples: raw_factor = (factor_to_get_back_to_raw)
      j.set_muon_sub_raw_factor(jet_muon_sub_raw_factor[i]);
      if(is_mc){
        j.set_parton_flavor(jet_parton_flavor[i]);
        j.set_hadron_flavor(jet_hadron_flavor[i]);
      }
      j.set_n_constituents(jet_n_constituents[i]);
      j.set_n_muons(jet_n_muons[i]);
      j.set_n_electrons(jet_n_electrons[i]);
      j.set_identifier(i); // to keep track of leptons associated to this jet
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

      //set ID bits
      t.set_selector(Tau::DeepTauVsJetVVVLoose, (tau_id_deeptau_vsjet[i] >= 1));
      t.set_selector(Tau::DeepTauVsJetVVLoose, (tau_id_deeptau_vsjet[i] >= 2));
      t.set_selector(Tau::DeepTauVsJetVLoose, (tau_id_deeptau_vsjet[i] >= 4));
      t.set_selector(Tau::DeepTauVsJetLoose, (tau_id_deeptau_vsjet[i] >= 8));
      t.set_selector(Tau::DeepTauVsJetMedium, (tau_id_deeptau_vsjet[i] >= 16));
      t.set_selector(Tau::DeepTauVsJetTight, (tau_id_deeptau_vsjet[i] >= 32));
      t.set_selector(Tau::DeepTauVsJetVTight, (tau_id_deeptau_vsjet[i] >= 64));
      t.set_selector(Tau::DeepTauVsJetVVTight, (tau_id_deeptau_vsjet[i] >= 128));
      t.set_selector(Tau::DeepTauVsEleVVVLoose, (tau_id_deeptau_vse[i] >= 1));
      t.set_selector(Tau::DeepTauVsEleVVLoose, (tau_id_deeptau_vse[i] >= 2));
      t.set_selector(Tau::DeepTauVsEleVLoose, (tau_id_deeptau_vse[i] >= 4));
      t.set_selector(Tau::DeepTauVsEleLoose, (tau_id_deeptau_vse[i] >= 8));
      t.set_selector(Tau::DeepTauVsEleMedium, (tau_id_deeptau_vse[i] >= 16));
      t.set_selector(Tau::DeepTauVsEleTight, (tau_id_deeptau_vse[i] >= 32));
      t.set_selector(Tau::DeepTauVsEleVTight, (tau_id_deeptau_vse[i] >= 64));
      t.set_selector(Tau::DeepTauVsEleVVTight, (tau_id_deeptau_vse[i] >= 128));
      t.set_selector(Tau::DeepTauVsMuVLoose, (tau_id_deeptau_vsmu[i] >= 1));
      t.set_selector(Tau::DeepTauVsMuLoose, (tau_id_deeptau_vsmu[i] >= 2));
      t.set_selector(Tau::DeepTauVsMuMedium, (tau_id_deeptau_vsmu[i] >= 4));
      t.set_selector(Tau::DeepTauVsMuTight, (tau_id_deeptau_vsmu[i] >= 8));

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
      m.set_jetidx(muon_jetidx[i]);
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
      m.set_selector(Muon::IDCutBasedGlobalHighPt, (muon_high_pt_id[i] >= 2));
      m.set_selector(Muon::IDCutBasedTrackerHighPt, (muon_high_pt_id[i] >= 1));
      m.set_selector(Muon::IDMvaSoft, (muon_soft_mva_id[i]));
      m.set_selector(Muon::IDMvaLoose, (muon_mva_id[i] >= 1));
      m.set_selector(Muon::IDMvaMedium, (muon_mva_id[i] >= 2));
      m.set_selector(Muon::IDMvaTight, (muon_mva_id[i] >= 3));
      m.set_selector(Muon::IDMvaVTight, (muon_mva_id[i] >= 4));
      m.set_selector(Muon::IDMvaVVTight, (muon_mva_id[i] >= 5));
      m.set_selector(Muon::IDCutBasedSoft, (muon_soft_id[i]));
      m.set_selector(Muon::IDCutBasedLoose, (muon_loose_id[i]));
      m.set_selector(Muon::IDCutBasedMedium, (muon_medium_id[i]));
      m.set_selector(Muon::IDCutBasedMediumPrompt, (muon_medium_prompt_id[i]));
      m.set_selector(Muon::IDCutBasedTight, (muon_tight_id[i]));
      m.set_selector(Muon::IDTriggerLoose, (muon_trigger_id_loose[i]));

      m.set_selector(Muon::IsoMultiLoose, (muon_multi_iso[i] >= 1));
      m.set_selector(Muon::IsoMultiMedium, (muon_multi_iso[i] >= 2));
      m.set_selector(Muon::IsoPFVLoose, (muon_pf_iso[i] >= 1));
      m.set_selector(Muon::IsoPFLoose, (muon_pf_iso[i] >= 2));
      m.set_selector(Muon::IsoPFMedium, (muon_pf_iso[i] >= 3));
      m.set_selector(Muon::IsoPFTight, (muon_pf_iso[i] >= 4));
      m.set_selector(Muon::IsoPFVTight, (muon_pf_iso[i] >= 5));
      m.set_selector(Muon::IsoPFVVTight, (muon_pf_iso[i] >= 6));
      m.set_selector(Muon::IsoTkLoose, (muon_tk_iso[i] >= 1));
      m.set_selector(Muon::IsoTkTight, (muon_tk_iso[i] >= 2));
      m.set_selector(Muon::IsoPuppiLoose, (muon_puppi_iso[i] >= 1));
      m.set_selector(Muon::IsoPuppiMedium, (muon_puppi_iso[i] >= 2));
      m.set_selector(Muon::IsoPuppiTight, (muon_puppi_iso[i] >= 3));
      m.set_selector(Muon::IsoMiniLoose, (muon_mini_iso[i] >= 1));
      m.set_selector(Muon::IsoMiniMedium, (muon_mini_iso[i] >= 2));
      m.set_selector(Muon::IsoMiniTight, (muon_mini_iso[i] >= 3));
      m.set_selector(Muon::IsoMiniVTight, (muon_mini_iso[i] >= 4));

      //gen_part_flav
      m.set_gen_part_flav((Muon::GenPartFlav)muon_gen_part_flav[i]);

      event.muons->emplace_back(m);
    }


    // Do Electrons
    // ============
    for(size_t i=0; i<*electron_n; i++){
      Electron e;

      e.set_jetidx(electron_jetidx[i]);
      e.set_charge(electron_charge[i]);
      e.set_id_bitmap(electron_id_bitmap[i]);
      e.set_lost_hits(electron_lost_hits[i]);
      e.set_conv_veto(electron_conv_veto[i]);
      e.set_is_pf(electron_is_pf[i]);
      e.set_delta_eta_sc(electron_delta_eta_sc[i]);
      e.set_dxy(electron_dxy[i]);
      e.set_dz(electron_dz[i]);
      e.set_einv_minus_pinv(electron_einv_minus_pinv[i]);
      e.set_h_over_e(electron_h_over_e[i]);
      e.set_ip_3d(electron_ip_3d[i]);
      e.set_iso_rel_03(electron_iso_rel_03[i]);
      e.set_iso_rel_03_charged(electron_iso_rel_03_charged[i]);
      e.set_sigma_ietaieta(electron_sigma_ietaieta[i]);
      e.set_pt(electron_pt[i]);
      e.set_eta(electron_eta[i]);
      e.set_phi(electron_phi[i]);
      e.set_m(electron_mass[i]);

      // set ID bits
      e.set_selector(Electron::IDCutBasedVeto, (electron_cut_based_id[i] >= 1));
      e.set_selector(Electron::IDCutBasedLoose, (electron_cut_based_id[i] >= 2));
      e.set_selector(Electron::IDCutBasedMedium, (electron_cut_based_id[i] >= 3));
      e.set_selector(Electron::IDCutBasedTight, (electron_cut_based_id[i] >= 4));
      e.set_selector(Electron::IDCutBasedHEEP, electron_heep_id[i]);
      e.set_selector(Electron::IDMVAIsoLoose, electron_mva_id_iso_loose[i]);
      e.set_selector(Electron::IDMVAIsoEff90, electron_mva_id_iso_90[i]);
      e.set_selector(Electron::IDMVAIsoEff80, electron_mva_id_iso_80[i]);
      e.set_selector(Electron::IDMVANonIsoLoose, electron_mva_id_noniso_loose[i]);
      e.set_selector(Electron::IDMVANonIsoEff90, electron_mva_id_noniso_90[i]);
      e.set_selector(Electron::IDMVANonIsoEff80, electron_mva_id_noniso_80[i]);


      event.electrons->emplace_back(e);
    }



    tree->Fill();
    event.reset();
    idx++;
  }

  event.clear();
  // tree->OptimizeBaskets();
  tree->Write();
  outfile->Close();

  cout << green << "--> Successfully finished tuplization." << reset << endl;
}
