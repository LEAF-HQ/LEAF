#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
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
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Run.h"



#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Common/interface/RefToPtr.h"

#include "PhysicsTools/HepMCCandAlgos/interface/GenParticlesHelper.h"

#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"

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
  fwlite::Handle<double> handle_rho, handle_l1prefiring, handle_l1prefiring_up, handle_l1prefiring_down;
  fwlite::Handle< std::vector<reco::Vertex> > handle_pvs;
  fwlite::Handle< std::vector<PileupSummaryInfo> > handle_pus;
  fwlite::Handle< std::vector<reco::GenJet> > handle_genjets;
  fwlite::Handle< std::vector<reco::GenParticle> > handle_genparticles;
  fwlite::Handle< GenEventInfoProduct > handle_geninfo;
  fwlite::Handle< LHEEventProduct > handle_lhe;
  fwlite::Handle< edm::TriggerResults > handle_hltresults;
  fwlite::Handle< edm::TriggerResults > handle_metfilterresults;
  fwlite::Handle< std::vector<pat::TriggerObjectStandAlone>> handle_triggerobjects;



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
    handle_pus      .getByLabel(ev, "slimmedAddPileupInfo");
    handle_l1prefiring.getByLabel(ev, "prefiringweight", "nonPrefiringProb");
    handle_l1prefiring_up.getByLabel(ev, "prefiringweight", "nonPrefiringProbUp");
    handle_l1prefiring_down.getByLabel(ev, "prefiringweight", "nonPrefiringProbDown");
    handle_genjets.getByLabel(ev, "slimmedGenJets");
    handle_genparticles.getByLabel(ev, "prunedGenParticles");
    handle_geninfo.getByLabel(ev, "generator");
    handle_lhe.getByLabel(ev, "externalLHEProducer");
    handle_hltresults.getByLabel(ev, "TriggerResults", "", "HLT");
    TString metfilterstep = "PAT";
    if(!is_mc) metfilterstep = "RECO";
    handle_metfilterresults.getByLabel(ev, "TriggerResults", "", metfilterstep.Data());
    handle_triggerobjects.getByLabel(ev, "slimmedPatTrigger");




    const std::vector<pat::Jet, std::allocator<pat::Jet>>*           jets       = handle_jets.product();
    const std::vector<pat::Muon, std::allocator<pat::Muon>>*         muons      = handle_muons.product();
    const std::vector<pat::Electron, std::allocator<pat::Electron>>* electrons  = handle_electrons.product();
    const std::vector<pat::Tau, std::allocator<pat::Tau>>*           taus       = handle_taus.product();
    const std::vector<pat::MET, std::allocator<pat::MET>>*           mets       = handle_met.product();
    const double*                                                    rho        = handle_rho.product();
    const std::vector<reco::Vertex, std::allocator<reco::Vertex>>*   pvs        = handle_pvs.product();
    const std::vector<PileupSummaryInfo, std::allocator<PileupSummaryInfo>>* pus= handle_pus.product();
    const double*                                                   l1prefiring = handle_l1prefiring.product();
    const double*                                                l1prefiring_up = handle_l1prefiring_up.product();
    const double*                                              l1prefiring_down = handle_l1prefiring_down.product();
    const std::vector<reco::GenJet, std::allocator<reco::GenJet>>* genjets      = handle_genjets.product();
    const std::vector<reco::GenParticle, std::allocator<reco::GenParticle>>* genparticles = handle_genparticles.product();
    const GenEventInfoProduct* geninfo = handle_geninfo.product();
    const LHEEventProduct* lhe = handle_lhe.product();
    const edm::TriggerResults* hltresults = handle_hltresults.product();
    const edm::TriggerNames &hltnames = ev.triggerNames(*hltresults);
    const edm::TriggerResults* metfilterresults = handle_metfilterresults.product();
    const edm::TriggerNames &metfilternames = ev.triggerNames(*metfilterresults);
    const vector<pat::TriggerObjectStandAlone>* triggerobjects = handle_triggerobjects.product();


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
    event.weight_prefiring = *l1prefiring;
    event.weight_prefiring_up = *l1prefiring_up;
    event.weight_prefiring_down = *l1prefiring_down;


    // Do MC truth variables
    // =====================
    if(is_mc){

      // Reco-event variables based on simulation
      event.ntrueint = pus->at(0).getTrueNumInteractions();
      event.npu = 0;
      for(size_t i=0; i<pus->size(); ++i){
        if(pus->at(i).getBunchCrossing() == 0){ // intime pileup
          event.npu += pus->at(i).getPU_NumInteractions();
        }
      }

      // GenMET content
      event.genmet->set_pt(mets->at(0).genMET()->pt());
      event.genmet->set_phi(mets->at(0).genMET()->phi());

      // GenJets
      for(size_t i=0; i<genjets->size(); i++){
        GenJet gj;
        reco::GenJet minigj = genjets->at(i);
        gj.set_p4(minigj.pt(), minigj.eta(), minigj.phi(), minigj.mass());
        gj.set_n_constituents(minigj.chargedHadronMultiplicity() + minigj.neutralHadronMultiplicity() + minigj.chargedEmMultiplicity() + minigj.neutralEmMultiplicity() + minigj.muonMultiplicity());
        event.genjets->emplace_back(gj);
      }

      // GenParticles
      for(size_t i=0; i<genparticles->size(); i++){
        reco::GenParticle minigp = genparticles->at(i);
        GenParticle gp;
        gp.set_p4(minigp.pt(), minigp.eta(), minigp.phi(), minigp.mass());
        gp.set_pdgid(minigp.pdgId());
        int motherid = -1;
        if(minigp.numberOfMothers() > 0) motherid = minigp.motherRef(0).key();
        gp.set_mother_identifier(motherid);
        gp.set_identifier(i);
        gp.set_status(minigp.status());
        gp.set_statusflag(GenParticle::isPrompt, minigp.statusFlags().isPrompt());
        gp.set_statusflag(GenParticle::isDecayedLeptonHadron, minigp.statusFlags().isDecayedLeptonHadron());
        gp.set_statusflag(GenParticle::isTauDecayProduct, minigp.statusFlags().isTauDecayProduct());
        gp.set_statusflag(GenParticle::isPromptTauDecayProduct, minigp.statusFlags().isPromptTauDecayProduct());
        gp.set_statusflag(GenParticle::isDirectTauDecayProduct, minigp.statusFlags().isDirectTauDecayProduct());
        gp.set_statusflag(GenParticle::isDirectPromptTauDecayProduct, minigp.statusFlags().isDirectPromptTauDecayProduct());
        gp.set_statusflag(GenParticle::isDirectHadronDecayProduct, minigp.statusFlags().isDirectHadronDecayProduct());
        gp.set_statusflag(GenParticle::isHardProcess, minigp.statusFlags().isHardProcess());
        gp.set_statusflag(GenParticle::fromHardProcess, minigp.statusFlags().fromHardProcess());
        gp.set_statusflag(GenParticle::isHardProcessTauDecayProduct, minigp.statusFlags().isHardProcessTauDecayProduct());
        gp.set_statusflag(GenParticle::isDirectHardProcessTauDecayProduct, minigp.statusFlags().isDirectHardProcessTauDecayProduct());
        gp.set_statusflag(GenParticle::fromHardProcessBeforeFSR, minigp.statusFlags().fromHardProcessBeforeFSR());
        gp.set_statusflag(GenParticle::isFirstCopy, minigp.statusFlags().isFirstCopy());
        gp.set_statusflag(GenParticle::isLastCopy, minigp.statusFlags().isLastCopy());
        gp.set_statusflag(GenParticle::isLastCopyBeforeFSR, minigp.statusFlags().isLastCopyBeforeFSR());
        event.genparticles_all->emplace_back(gp);
      }

      // GenVisTaus
      vector<reco::GenJet> genTauJets = {};
      reco::GenParticleRefVector allStatus2Taus;
      GenParticlesHelper::findParticles(*genparticles, allStatus2Taus, 15, 2);

      for (reco::GenParticleRefVector::const_iterator iTau = allStatus2Taus.begin(); iTau != allStatus2Taus.end(); ++iTau) {
        // look for all status 1 (stable) descendents
        reco::GenParticleRefVector descendents;
        GenParticlesHelper::findDescendents(*iTau, descendents, 1);

        // CV: skip status 2 taus that radiate-off a photon
        //    --> have a status 2 tau lepton in the list of descendents
        reco::GenParticleRefVector status2TauDaughters;
        GenParticlesHelper::findDescendents(*iTau, status2TauDaughters, 2, 15);
        if (!status2TauDaughters.empty())
        continue;

        // loop on descendents, and take all except neutrinos
        math::XYZTLorentzVector sumVisMom;
        reco::Particle::Charge charge = 0;
        reco::Jet::Constituents constituents;

        for (reco::GenParticleRefVector::const_iterator igr = descendents.begin(); igr != descendents.end(); ++igr) {
          int absPdgId = abs((*igr)->pdgId());

          // skip neutrinos
          if (absPdgId == 12 || absPdgId == 14 || absPdgId == 16)
          continue;

          charge += (*igr)->charge();
          sumVisMom += (*igr)->p4();
          constituents.push_back(refToPtr(*igr));
        }

        math::XYZPoint vertex;
        reco::GenJet::Specific specific;

        reco::GenJet jet(sumVisMom, vertex, specific, constituents);

        jet.setCharge(charge);
        genTauJets.push_back(jet);
      }

      // unique_ptr<vector<reco::GenParticle>> genVisTaus;
      for (const auto& genTauJet : genTauJets) {
        std::string decayMode_string = JetMCTagUtils::genTauDecayMode(genTauJet);
        // CV: store hadronic tau decays only
        if (decayMode_string == "electron" || decayMode_string == "muon")
        continue;
        int decayMode = reco::PFTau::kNull;
        if (decayMode_string == "oneProng0Pi0")
        decayMode = reco::PFTau::kOneProng0PiZero;
        else if (decayMode_string == "oneProng1Pi0")
        decayMode = reco::PFTau::kOneProng1PiZero;
        else if (decayMode_string == "oneProng2Pi0")
        decayMode = reco::PFTau::kOneProng2PiZero;
        else if (decayMode_string == "threeProng0Pi0")
        decayMode = reco::PFTau::kThreeProng0PiZero;
        else if (decayMode_string == "threeProng1Pi0")
        decayMode = reco::PFTau::kThreeProng1PiZero;
        else
        decayMode = reco::PFTau::kRareDecayMode;

        int pdgId = (genTauJet.charge() > 0) ? -15 : +15;

        // CV: store decayMode in status flag of GenParticle object
        reco::GenParticle genVisTau(genTauJet.charge(), genTauJet.p4(), genTauJet.vertex(), pdgId, decayMode, true);

        // CV: find tau lepton "mother" particle
        for (size_t idxGenParticle = 0; idxGenParticle < genparticles->size()
        ; ++idxGenParticle) {
          const reco::GenParticle& genTau = (*genparticles)[idxGenParticle];
          if (abs(genTau.pdgId()) == 15 && genTau.status() == 2) {
            reco::Candidate::LorentzVector daughterVisP4;
            for (const reco::GenParticleRef& daughter : genTau.daughterRefVector()) {
              int abs_pdgId = abs(daughter->pdgId());
              // CV: skip neutrinos
              if (abs_pdgId == 12 || abs_pdgId == 14 || abs_pdgId == 16)
              continue;
              daughterVisP4 += daughter->p4();
            }
            double dR2 = deltaR2(daughterVisP4, genVisTau);
            if (dR2 < 1.e-4) {
              genVisTau.addMother(reco::GenParticleRef(genparticles, idxGenParticle));
              break;
            }
          }
        }

        // here the source genvistau is complete, ready to translate to LEAF format
        GenParticle gvt;
        gvt.set_p4(genVisTau.pt(), genVisTau.eta(), genVisTau.phi(), genVisTau.mass());
        gvt.set_pdgid(genVisTau.pdgId());
        int gvtmotherid = -1;
        if(genVisTau.numberOfMothers() > 0) gvtmotherid = genVisTau.motherRef(0).key();
        gvt.set_mother_identifier(gvtmotherid);
        gvt.set_status(genVisTau.status());
        event.genparticles_visibletaus->emplace_back(gvt);
      }


      // global gen info
      event.weight = geninfo->weight(); // equivalent to geninfo->weights().at(0), always returns the 0th element
      event.geninfo->set_weight(geninfo->weight());
      const gen::PdfInfo* pdf = geninfo->pdf();
      if(pdf){
        event.geninfo->set_id1(pdf->id.first);
        event.geninfo->set_id2(pdf->id.second);
        event.geninfo->set_x1(pdf->x.first);
        event.geninfo->set_x2(pdf->x.second);
        event.geninfo->set_scale_pdf(pdf->scalePDF);
        event.geninfo->set_xpdf1(pdf->xPDF.first);
        event.geninfo->set_xpdf2(pdf->xPDF.second);
      }
      else{
        event.geninfo->set_id1(-999);
        event.geninfo->set_id2(-999);
        event.geninfo->set_x1(-999);
        event.geninfo->set_x2(-999);
        event.geninfo->set_scale_pdf(-999);
        event.geninfo->set_xpdf1(-999);
        event.geninfo->set_xpdf2(-999);
      }

      event.geninfo->set_originalXWGTUP(lhe->originalXWGTUP());
      // cout << "orig: " << lhe->originalXWGTUP() << endl;
      vector<double> systweights = {};
      for(unsigned int i=0; i<lhe->weights().size(); i++){
        systweights.emplace_back(lhe->weights().at(i).wgt);
        // cout << "weight " << i << ": " <<lhe->weights().at(i).wgt << endl;
      }
      event.geninfo->set_systweights(systweights);




    }
    else{
      event.weight = 1.;
    }


    // Do MetfilterFlags
    // =================
    for(size_t i=0; i<metfilterresults->size(); ++i){
      event.flags->set(metfilternames.triggerName(i), metfilterresults->accept(i));
      // cout << "trigger name: " << metfilternames.triggerName(i) << ": " << metfilterresults->accept(i) << endl;
    }


    // Do HLT flags
    // ============
    for(size_t i=0; i<hltresults->size(); ++i){
      event.flags->set(hltnames.triggerName(i), hltresults->accept(i));
      // cout << "trigger name: " << hltnames.triggerName(i) << ": " << hltresults->accept(i) << endl;
    }


    // Do HLT objects  (these are super heavy, add only once the need arises)
    // ==============
    // for(size_t i=0; i<triggerobjects->size(); i++){
    //   pat::TriggerObjectStandAlone triggerobject = (*triggerobjects).at(i);
    //   bool fired_hlt = false;
    //   vector<TriggerObject::ID> ids = {};
    //   for(size_t j=0; j<triggerobject.filterIds().size(); j++){
    //     int id = triggerobject.filterIds()[j];
    //     if(triggerobject.filterIds()[j] > 0) fired_hlt = true; // < 0 corresponds to earlier stages, https://github.com/cms-sw/cmssw/blob/master/DataFormats/HLTReco/interface/TriggerTypeDefs.h
    //
    //     if(id == trigger::TriggerObjectType::TriggerPhoton) ids.emplace_back(TriggerObject::Photon);
    //     else if(id == trigger::TriggerObjectType::TriggerElectron) ids.emplace_back(TriggerObject::Electron);
    //     else if(id == trigger::TriggerObjectType::TriggerMuon) ids.emplace_back(TriggerObject::Muon);
    //     else if(id == trigger::TriggerObjectType::TriggerTau) ids.emplace_back(TriggerObject::Tau);
    //     else if(id == trigger::TriggerObjectType::TriggerJet) ids.emplace_back(TriggerObject::Jet);
    //     else if(id == trigger::TriggerObjectType::TriggerBJet) ids.emplace_back(TriggerObject::BJet);
    //     else if(id == trigger::TriggerObjectType::TriggerMET) ids.emplace_back(TriggerObject::MET);
    //     else if(id == trigger::TriggerObjectType::TriggerTET) ids.emplace_back(TriggerObject::ET);
    //     else if(id == trigger::TriggerObjectType::TriggerTHT) ids.emplace_back(TriggerObject::HT);
    //     else if(id == trigger::TriggerObjectType::TriggerMHT) ids.emplace_back(TriggerObject::MHT);
    //     else if(id == trigger::TriggerObjectType::TriggerTrack) ids.emplace_back(TriggerObject::Track);
    //     else ids.emplace_back(TriggerObject::Other);
    //   }
    //   if(fired_hlt){
    //     TriggerObject to;
    //     triggerobject.unpackPathNames(hltnames);
    //     vector<string> pathNamesAll  = triggerobject.pathNames(false);
    //     vector<TString> new_hltnames = {};
    //     for(const string & name : pathNamesAll) new_hltnames.emplace_back(name);
    //     to.set_hltnames(new_hltnames);
    //
    //     triggerobject.unpackFilterLabels(ev, *hltresults);
    //     vector<string> filternames = triggerobject.filterLabels();
    //     vector<TString> new_filternames = {};
    //     for(const string & name : filternames) new_filternames.emplace_back(name);
    //     to.set_filternames(new_filternames);
    //
    //     to.set_pt(triggerobject.pt());
    //     to.set_eta(triggerobject.eta());
    //     to.set_phi(triggerobject.phi());
    //     to.set_m(triggerobject.mass());
    //     to.set_charge(triggerobject.charge());
    //     event.triggerobjects->emplace_back(to);
    //   }
    // }



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
