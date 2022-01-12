// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// new includes
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"  // edm::Handle

// for vertexing
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"

#include "TrackingTools/IPTools/interface/IPTools.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/MuonReco/interface/MuonQuality.h"

#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "PhysicsTools/HepMCCandAlgos/interface/GenParticlesHelper.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"
#include "PhysicsTools/NanoAOD/interface/MatchingUtils.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

#include "LEAF/Analyzer/include/RecoEvent.h"

#include <math.h>
#include <TMath.h>
#include <TTree.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <algorithm>  // std::sort, std::swap
#include <iostream>  // std::cout, std::endl
#include <string>

class NTuplizer : public edm::EDFilter {
public:
  explicit NTuplizer(const edm::ParameterSet&);

private:
  virtual bool filter(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;


  edm::EDGetTokenT<std::vector<pat::Muon>>         token_muons;
  edm::EDGetTokenT<std::vector<pat::Jet>>          token_jets;
  edm::EDGetTokenT<std::vector<pat::Electron>>     token_electrons;
  edm::EDGetTokenT<std::vector<pat::Tau>>          token_taus;
  edm::EDGetTokenT<std::vector<pat::MET>>          token_mets;
  edm::EDGetTokenT<std::vector<reco::Vertex>>      token_primary_vertices;
  edm::EDGetTokenT<double>                         token_rho, token_l1prefiring, token_l1prefiring_up, token_l1prefiring_down;
  edm::EDGetTokenT<edm::TriggerResults>            token_hltresults;
  edm::EDGetTokenT<edm::TriggerResults>            token_metfilterresults;
  edm::EDGetTokenT<std::vector<pat::TriggerObjectStandAlone>> token_triggerobjects;
  edm::EDGetTokenT<std::vector<pat::PackedCandidate>> token_pfcands;

  edm::EDGetTokenT<std::vector<PileupSummaryInfo>> token_pus;
  edm::EDGetTokenT<std::vector<reco::GenJet>>      token_genjets;
  edm::EDGetTokenT<std::vector<reco::GenParticle>> token_genparticles;
  edm::EDGetTokenT<GenEventInfoProduct>            token_geninfo;
  edm::EDGetTokenT<LHEEventProduct>                token_lhe;






  TString outfilename;
  bool is_mc, do_triggerobjects, do_pfcands;


  TFile *outfile;
  TTree *tree;
  RecoEvent event;

};

NTuplizer::NTuplizer(const edm::ParameterSet& iConfig){

  outfilename = (TString)iConfig.getParameter<std::string>("outfilename");
  is_mc       = iConfig.getParameter<bool>("is_mc");
  do_triggerobjects = iConfig.getParameter<bool>("do_triggerobjects");
  do_pfcands = iConfig.getParameter<bool>("do_pfcands");

  if(outfilename != ""){
    outfile = new TFile(outfilename, "RECREATE");
    outfile->cd();
    tree = new TTree("AnalysisTree", "AnalysisTree");
    tree->Branch("Events", &event);
  }

  token_muons            = consumes<std::vector<pat::Muon>>     (iConfig.getParameter<edm::InputTag>("muons"));
  token_jets             = consumes<std::vector<pat::Jet>>      (iConfig.getParameter<edm::InputTag>("ak4jets"));
  token_electrons        = consumes<std::vector<pat::Electron>> (iConfig.getParameter<edm::InputTag>("electrons"));
  token_taus             = consumes<std::vector<pat::Tau>>      (iConfig.getParameter<edm::InputTag>("taus"));
  token_mets             = consumes<std::vector<pat::MET>>      (iConfig.getParameter<edm::InputTag>("met"));
  token_primary_vertices = consumes<std::vector<reco::Vertex>>  (iConfig.getParameter<edm::InputTag>("primary_vertices"));
  token_rho              = consumes<double>                     (iConfig.getParameter<edm::InputTag>("rho"));
  token_l1prefiring      = consumes<double>                     (iConfig.getParameter<edm::InputTag>("l1prefiring"));
  token_l1prefiring_up   = consumes<double>                     (iConfig.getParameter<edm::InputTag>("l1prefiring_up"));
  token_l1prefiring_down = consumes<double>                     (iConfig.getParameter<edm::InputTag>("l1prefiring_down"));
  token_hltresults       = consumes<edm::TriggerResults>        (iConfig.getParameter<edm::InputTag>("hltresults"));
  token_metfilterresults = consumes<edm::TriggerResults>        (iConfig.getParameter<edm::InputTag>("metfilterresults"));
  if(do_triggerobjects){
    token_triggerobjects = consumes<std::vector<pat::TriggerObjectStandAlone>> (iConfig.getParameter<edm::InputTag>("triggerobjects"));
  }
  if(do_pfcands){
    token_pfcands        = consumes<std::vector<pat::PackedCandidate>> (iConfig.getParameter<edm::InputTag>("pfcands"));
  }

  token_pus              = consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileup"));
  token_genjets          = consumes<std::vector<reco::GenJet>>(iConfig.getParameter<edm::InputTag>("genjets"));
  token_genparticles     = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genparticles")) ;
  token_geninfo          = consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("geninfo")) ;
  token_lhe              = consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("lhe")) ;

}

bool NTuplizer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){


  // declare handles
  edm::Handle<std::vector<pat::Muon>> muons;
  edm::Handle<std::vector<pat::Jet>> jets;
  edm::Handle<std::vector<pat::Electron>> electrons;
  edm::Handle<std::vector<pat::Tau>> taus;
  edm::Handle<std::vector<pat::MET>> mets;
  edm::Handle<std::vector<reco::Vertex>> pvs;
  edm::Handle<double> rho, l1prefiring, l1prefiring_up, l1prefiring_down;
  edm::Handle<edm::TriggerResults> hltresults;
  edm::Handle<edm::TriggerResults> metfilterresults;
  edm::Handle<std::vector<pat::TriggerObjectStandAlone>> triggerobjects;
  edm::Handle<std::vector<pat::PackedCandidate>> pfcands;

  edm::Handle<std::vector<PileupSummaryInfo>> pus;
  edm::Handle<std::vector<reco::GenJet>> genjets;
  edm::Handle<std::vector<reco::GenParticle>> genparticles;
  edm::Handle<GenEventInfoProduct> geninfo;
  edm::Handle<LHEEventProduct> lhe;

  // fill handles through the tokens
  iEvent.getByToken(token_muons, muons);
  iEvent.getByToken(token_jets, jets);
  iEvent.getByToken(token_electrons, electrons);
  iEvent.getByToken(token_taus, taus);
  iEvent.getByToken(token_mets, mets);
  iEvent.getByToken(token_primary_vertices, pvs);
  iEvent.getByToken(token_rho, rho);
  iEvent.getByToken(token_l1prefiring, l1prefiring);
  iEvent.getByToken(token_l1prefiring_up, l1prefiring_up);
  iEvent.getByToken(token_l1prefiring_down, l1prefiring_down);
  iEvent.getByToken(token_hltresults, hltresults);
  const edm::TriggerNames &hltnames = iEvent.triggerNames(*hltresults);
  iEvent.getByToken(token_metfilterresults, metfilterresults);
  const edm::TriggerNames &metfilternames = iEvent.triggerNames(*metfilterresults);
  if(do_triggerobjects){
    iEvent.getByToken(token_triggerobjects, triggerobjects);
  }
  if(do_pfcands){
    iEvent.getByToken(token_pfcands, pfcands);
  }

  bool has_lhe = is_mc;
  if(is_mc){
    iEvent.getByToken(token_pus, pus);
    iEvent.getByToken(token_genjets, genjets);
    iEvent.getByToken(token_genparticles, genparticles);
    iEvent.getByToken(token_geninfo, geninfo);
    try{
      iEvent.getByToken(token_lhe, lhe);
    }
    catch(...){
      has_lhe = false;
    }
  }


  // Do general event-based variables
  // ================================

  event.is_data = !is_mc;
  event.run = iEvent.id().run();
  event.number = iEvent.id().event();
  event.lumiblock = iEvent.luminosityBlock();
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
  vector<reco::GenParticle> reco_genvistaus = {};
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
      gp.set_charge(minigp.charge());
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
      for (size_t idxGenParticle = 0; idxGenParticle < genparticles->size(); ++idxGenParticle) {
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

      reco_genvistaus.emplace_back(genVisTau);
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

    vector<double> systweights = {};
    if(has_lhe){
      event.geninfo->set_originalXWGTUP(lhe->originalXWGTUP());
      for(unsigned int i=0; i<lhe->weights().size(); i++){
        systweights.emplace_back(lhe->weights().at(i).wgt);
      }
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
  if(do_triggerobjects){
    for(size_t i=0; i<triggerobjects->size(); i++){
      pat::TriggerObjectStandAlone triggerobject = (*triggerobjects).at(i);
      bool fired_hlt = false;
      vector<TriggerObject::ID> ids = {};
      for(size_t j=0; j<triggerobject.filterIds().size(); j++){
        int id = triggerobject.filterIds()[j];
        if(triggerobject.filterIds()[j] > 0) fired_hlt = true; // < 0 corresponds to earlier stages, https://github.com/cms-sw/cmssw/blob/master/DataFormats/HLTReco/interface/TriggerTypeDefs.h

        if(id == trigger::TriggerObjectType::TriggerPhoton) ids.emplace_back(TriggerObject::Photon);
        else if(id == trigger::TriggerObjectType::TriggerElectron) ids.emplace_back(TriggerObject::Electron);
        else if(id == trigger::TriggerObjectType::TriggerMuon) ids.emplace_back(TriggerObject::Muon);
        else if(id == trigger::TriggerObjectType::TriggerTau) ids.emplace_back(TriggerObject::Tau);
        else if(id == trigger::TriggerObjectType::TriggerJet) ids.emplace_back(TriggerObject::Jet);
        else if(id == trigger::TriggerObjectType::TriggerBJet) ids.emplace_back(TriggerObject::BJet);
        else if(id == trigger::TriggerObjectType::TriggerMET) ids.emplace_back(TriggerObject::MET);
        else if(id == trigger::TriggerObjectType::TriggerTET) ids.emplace_back(TriggerObject::ET);
        else if(id == trigger::TriggerObjectType::TriggerTHT) ids.emplace_back(TriggerObject::HT);
        else if(id == trigger::TriggerObjectType::TriggerMHT) ids.emplace_back(TriggerObject::MHT);
        else if(id == trigger::TriggerObjectType::TriggerTrack) ids.emplace_back(TriggerObject::Track);
        else ids.emplace_back(TriggerObject::Other);
      }
      if(fired_hlt){
        TriggerObject to;
        triggerobject.unpackPathNames(hltnames);
        vector<string> pathNamesAll  = triggerobject.pathNames(false);
        vector<TString> new_hltnames = {};
        for(const string & name : pathNamesAll) new_hltnames.emplace_back(name);
        to.set_hltnames(new_hltnames);

        triggerobject.unpackFilterLabels(iEvent, *hltresults);
        vector<string> filternames = triggerobject.filterLabels();
        vector<TString> new_filternames = {};
        for(const string & name : filternames) new_filternames.emplace_back(name);
        to.set_filternames(new_filternames);

        to.set_pt(triggerobject.pt());
        to.set_eta(triggerobject.eta());
        to.set_phi(triggerobject.phi());
        to.set_m(triggerobject.mass());
        to.set_charge(triggerobject.charge());
        event.triggerobjects->emplace_back(to);
      }
    }
  }


  // Do PF candidates
  // ================
  if(do_pfcands){
    for(size_t i=0; i<pfcands->size(); i++){
      pat::PackedCandidate patcand = pfcands->at(i);
      PFCandidate p;
      p.set_pt(patcand.pt());
      p.set_eta(patcand.eta());
      p.set_phi(patcand.phi());
      p.set_m(patcand.mass());
      p.set_charge(patcand.charge());
      p.set_pdgid(patcand.pdgId());
      p.set_puppiweight(patcand.puppiWeight());
      p.set_puppiweight_nolep(patcand.puppiWeightNoLep());

      event.pfcands->emplace_back(p);
    }
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
    if(!jets->at(i).isPFJet()) continue;
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


  // Do Muons
  // =======
  for(size_t i=0; i<muons->size(); i++){
    pat::Muon patmu = muons->at(i);
    Muon m;

    m.set_charge(patmu.charge());
    m.set_pt(patmu.pt());
    m.set_eta(patmu.eta());
    m.set_phi(patmu.phi());
    m.set_m(patmu.mass());
    m.set_selector(Muon::Global    , patmu.isGlobalMuon());
    m.set_selector(Muon::PF        , patmu.isPFMuon());
    m.set_selector(Muon::Tracker   , patmu.isTrackerMuon());
    m.set_selector(Muon::Standalone, patmu.isStandAloneMuon());
    m.set_selector(Muon::Good, muon::isGoodMuon(patmu, muon::TMOneStationTight));

    int jetidx = -1;
    for (unsigned int j=0; j<jets->size(); j++) { // from here: https://github.com/cms-sw/cmssw/blob/6d2f66057131baacc2fcbdd203588c41c885b42c/PhysicsTools/NanoAOD/plugins/LeptonJetVarProducer.cc#L108#L121
      pat::Jet jet = jets->at(j);
      if (matchByCommonSourceCandidatePtr(patmu, jet)) {
        jetidx = j;
        break;
      }
    }
    m.set_jetidx(jetidx);
    m.set_pdgid(patmu.pdgId());
    m.set_dxy(fabs(patmu.dB(pat::Muon::PV2D)));
    m.set_dz(fabs(patmu.dB(pat::Muon::PVDZ)));
    m.set_d0(fabs(patmu.dB(pat::Muon::PV3D)));
    m.set_edxy(patmu.edB(pat::Muon::PV2D));
    m.set_edz(patmu.edB(pat::Muon::PVDZ));
    m.set_ed0(patmu.edB(pat::Muon::PV3D));

    if(patmu.tunePMuonBestTrack().isNonnull()){
      edm::Ref<std::vector<reco::Track> > tunePtrack = patmu.tunePMuonBestTrack();
      m.set_tunep_pt(tunePtrack->pt());
      m.set_tunep_pt_err(tunePtrack->ptError());
      m.set_tunep_eta(tunePtrack->eta());
      m.set_tunep_phi(tunePtrack->phi());
      m.set_tunep_numberOfValidMuonHits(tunePtrack->hitPattern().numberOfValidMuonHits());
      m.set_iso_tk(patmu.isolationR03().sumPt/tunePtrack->pt());
    }
    m.set_pt_err(patmu.bestTrack()->ptError());

    // m.set_iso_mini(muon_iso_mini[i]);
    // m.set_iso_mini_charged(muon_iso_mini_charged[i]);
    m.set_iso_rel_03((patmu.pfIsolationR03().sumChargedHadronPt + max(patmu.pfIsolationR03().sumNeutralHadronEt + patmu.pfIsolationR03().sumPhotonEt - patmu.pfIsolationR03().sumPUPt/2,float(0.0)))/patmu.pt());
    m.set_iso_rel_04((patmu.pfIsolationR04().sumChargedHadronPt + max(patmu.pfIsolationR04().sumNeutralHadronEt + patmu.pfIsolationR04().sumPhotonEt - patmu.pfIsolationR04().sumPUPt/2,float(0.0)))/patmu.pt());
    m.set_iso_rel_03_charged(patmu.pfIsolationR03().sumChargedHadronPt/patmu.pt());
    m.set_sumchpt(patmu.pfIsolationR04().sumChargedHadronPt);
    m.set_sumnhet(patmu.pfIsolationR04().sumNeutralHadronEt);
    m.set_sumphpt(patmu.pfIsolationR04().sumPhotonEt);
    m.set_sumpupt(patmu.pfIsolationR04().sumPUPt);
    //
    // //set ID bits
    m.set_selector(Muon::IDCutBasedLoose, patmu.passed(reco::Muon::CutBasedIdLoose));
    m.set_selector(Muon::IDCutBasedMedium, patmu.passed(reco::Muon::CutBasedIdMedium));
    m.set_selector(Muon::IDCutBasedMediumPrompt, patmu.passed(reco::Muon::CutBasedIdMediumPrompt));
    m.set_selector(Muon::IDCutBasedTight, patmu.passed(reco::Muon::CutBasedIdTight));
    m.set_selector(Muon::IDCutBasedGlobalHighPt, patmu.passed(reco::Muon::CutBasedIdGlobalHighPt));
    m.set_selector(Muon::IDCutBasedTrackerHighPt, patmu.passed(reco::Muon::CutBasedIdTrkHighPt));
    m.set_selector(Muon::IDCutBasedSoft, patmu.passed(reco::Muon::SoftCutBasedId));
    m.set_selector(Muon::IDMvaSoft, patmu.passed(reco::Muon::SoftMvaId));
    m.set_selector(Muon::IDMvaLoose, patmu.passed(reco::Muon::MvaLoose));
    m.set_selector(Muon::IDMvaMedium, patmu.passed(reco::Muon::MvaMedium));
    m.set_selector(Muon::IDMvaTight, patmu.passed(reco::Muon::MvaTight));
    m.set_selector(Muon::IDMvaVTight, patmu.passed(reco::Muon::MvaVTight));
    m.set_selector(Muon::IDMvaVVTight, patmu.passed(reco::Muon::MvaVVTight));
    m.set_selector(Muon::IDMvaLowPtLoose, patmu.passed(reco::Muon::LowPtMvaLoose));
    m.set_selector(Muon::IDMvaLowPtMedium, patmu.passed(reco::Muon::LowPtMvaMedium));
    m.set_selector(Muon::IDTriggerLoose, patmu.passed(reco::Muon::TriggerIdLoose));

    m.set_selector(Muon::IsoMultiLoose  , patmu.passed(reco::Muon::MultiIsoLoose));
    m.set_selector(Muon::IsoMultiMedium      , patmu.passed(reco::Muon::MultiIsoMedium));
    m.set_selector(Muon::IsoPFVLoose  , patmu.passed(reco::Muon::PFIsoVeryLoose));
    m.set_selector(Muon::IsoPFLoose      , patmu.passed(reco::Muon::PFIsoLoose));
    m.set_selector(Muon::IsoPFMedium     , patmu.passed(reco::Muon::PFIsoMedium));
    m.set_selector(Muon::IsoPFTight      , patmu.passed(reco::Muon::PFIsoTight));
    m.set_selector(Muon::IsoPFVTight  , patmu.passed(reco::Muon::PFIsoVeryTight));
    m.set_selector(Muon::IsoPFVVTight  , patmu.passed(reco::Muon::PFIsoVeryVeryTight));
    m.set_selector(Muon::IsoTkLoose      , patmu.passed(reco::Muon::TkIsoLoose));
    m.set_selector(Muon::IsoTkTight      , patmu.passed(reco::Muon::TkIsoTight));
    m.set_selector(Muon::IsoMiniLoose    , patmu.passed(reco::Muon::MiniIsoLoose));
    m.set_selector(Muon::IsoMiniMedium   , patmu.passed(reco::Muon::MiniIsoMedium));
    m.set_selector(Muon::IsoMiniTight    , patmu.passed(reco::Muon::MiniIsoTight));
    m.set_selector(Muon::IsoMiniVTight, patmu.passed(reco::Muon::MiniIsoVeryTight));
    m.set_selector(Muon::IsoPuppiLoose   , patmu.passed(reco::Muon::PuppiIsoLoose));
    m.set_selector(Muon::IsoPuppiMedium    , patmu.passed(reco::Muon::PuppiIsoMedium));
    m.set_selector(Muon::IsoPuppiTight, patmu.passed(reco::Muon::PuppiIsoTight));

    m.set_globalTrack_normalizedChi2       ( patmu.globalTrack().isNonnull() ? patmu.globalTrack()->normalizedChi2() : -999.);
    m.set_globalTrack_numberOfValidMuonHits( patmu.globalTrack().isNonnull() ? patmu.globalTrack()->hitPattern().numberOfValidMuonHits() : -1);
    m.set_numberOfMatchedStations(patmu.numberOfMatchedStations());
    m.set_expectedNnumberOfMatchedStations(patmu.expectedNnumberOfMatchedStations());
    m.set_numberOfMatchedRPCLayers(patmu.numberOfMatchedRPCLayers());
    m.set_innerTrack_trackerLayersWithMeasurement(patmu.innerTrack().isNonnull() ? patmu.innerTrack()->hitPattern().trackerLayersWithMeasurement() : -1);
    m.set_innerTrack_numberOfValidPixelHits      (patmu.innerTrack().isNonnull() ? patmu.innerTrack()->hitPattern().numberOfValidPixelHits() : -1);
    m.set_innerTrack_validFraction               (patmu.innerTrack().isNonnull() ? patmu.innerTrack()->validFraction() : -999.);
    m.set_combinedQuality_chi2LocalPosition(patmu.combinedQuality().chi2LocalPosition);
    m.set_combinedQuality_trkKink          (patmu.combinedQuality().trkKink);
    m.set_segmentCompatibility(muon::segmentCompatibility(patmu));
    m.set_innerTrack_isHighQuality(patmu.innerTrack().isNonnull() ? patmu.innerTrack()->quality(reco::TrackBase::highPurity) : false);
    m.set_stationMask(patmu.stationMask());

    Muon::GenPartFlav genpartflav = (Muon::GenPartFlav)patmu.simFlavour();
    if(genpartflav == 13) genpartflav = Muon::GenPartFlav::Prompt;
    m.set_gen_part_flav(genpartflav);

    if(patmu.simType() == reco::NotMatched)                       m.set_sim_type(Muon::SimType::NotMatched);
    else if(patmu.simType() == reco::MatchedPunchthrough)         m.set_sim_type(Muon::SimType::MatchedPunchthrough);
    else if(patmu.simType() == reco::MatchedElectron)             m.set_sim_type(Muon::SimType::MatchedElectron);
    else if(patmu.simType() == reco::MatchedPrimaryMuon)          m.set_sim_type(Muon::SimType::MatchedPrimaryMuon);
    else if(patmu.simType() == reco::MatchedMuonFromLightFlavour) m.set_sim_type(Muon::SimType::MatchedLightQuark);
    else if(patmu.simType() == reco::GhostPunchthrough)           m.set_sim_type(Muon::SimType::GhostPunchthrough);
    else if(patmu.simType() == reco::GhostElectron)               m.set_sim_type(Muon::SimType::GhostElectron);
    else if(patmu.simType() == reco::GhostPrimaryMuon)            m.set_sim_type(Muon::SimType::GhostPrimaryMuon);
    else if(patmu.simType() == reco::GhostMuonFromLightFlavour)   m.set_sim_type(Muon::SimType::GhostLightQuark);
    else if(patmu.simType() == reco::MatchedMuonFromHeavyFlavour){
      if(patmu.simExtType() == reco::MatchedMuonFromTau)          m.set_sim_type(Muon::SimType::MatchedTau);
      else                                                         m.set_sim_type(Muon::SimType::MatchedHeavyQuark);
    }
    else if(patmu.simType() == reco::GhostMuonFromHeavyFlavour){
      if(patmu.simExtType() == reco::GhostMuonFromTau)            m.set_sim_type(Muon::SimType::GhostTau);
      else                                                         m.set_sim_type(Muon::SimType::GhostHeavyQuark);
    }
    else                                                           m.set_sim_type(Muon::SimType::Unknown);

    m.set_sim_pdgid(patmu.simPdgId());
    m.set_sim_mother_pdgid(patmu.simMotherPdgId());
    m.set_sim_heaviestmother_flav(patmu.simHeaviestMotherFlavour());


    event.muons->emplace_back(m);
  }



  // Do Electrons
  // ============

  // get effective area file
  TString CMSSWPATH = (TString)getenv("CMSSW_RELEASE_BASE");
  TString effarea_file = CMSSWPATH + "/src/RecoEgamma/ElectronIdentification/data/Fall17/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt";
  EffectiveAreas effareas(effarea_file.Data());

  // loop over electrons
  for(size_t i=0; i<electrons->size(); i++){
    pat::Electron patele = electrons->at(i);
    Electron e;

    int jetidx = -1;
    for (size_t j=0; j<jets->size(); j++) { // from here: https://github.com/cms-sw/cmssw/blob/6d2f66057131baacc2fcbdd203588c41c885b42c/PhysicsTools/NanoAOD/plugins/LeptonJetVarProducer.cc#L108#L121
      pat::Jet jet = jets->at(j);
      if (matchByCommonSourceCandidatePtr(patele, jet)) {
        jetidx = j;
        break;
      }
    }
    e.set_jetidx(jetidx);
    e.set_charge(patele.charge());
    e.set_pdgid(patele.pdgId());
    e.set_pt(patele.pt());
    e.set_eta(patele.eta());
    e.set_phi(patele.phi());
    e.set_m(patele.mass());

    e.set_pt_err(patele.gsfTrack()->ptError());
    e.set_eta_err(patele.gsfTrack()->etaError());
    e.set_phi_err(patele.gsfTrack()->phiError());


    e.set_dxy(fabs(patele.dB(pat::Electron::PV2D)));
    e.set_dz(fabs(patele.dB(pat::Electron::PVDZ)));
    e.set_d0(fabs(patele.dB(pat::Electron::PV3D)));
    e.set_edxy(patele.edB(pat::Electron::PV2D));
    e.set_edz(patele.edB(pat::Electron::PVDZ));
    e.set_ed0(patele.edB(pat::Electron::PV3D));

    e.set_lost_hits(patele.gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS));
    e.set_conv_veto(patele.passConversionVeto());
    e.set_is_pf(patele.pfCandidateRef().isNonnull());
    e.set_eta_sc(patele.superCluster()->eta());
    e.set_phi_sc(patele.superCluster()->phi());
    e.set_e_sc(patele.superCluster()->energy());
    e.set_einv_minus_pinv((1-patele.eSuperClusterOverP())/patele.ecalEnergy());
    e.set_h_over_e(patele.hadronicOverEm());
    e.set_sigma_ietaieta(patele.full5x5_sigmaIetaIeta());

    float ea = effareas.getEffectiveArea(fabs(patele.superCluster()->eta()));
    e.set_ea(ea);
    reco::GsfElectron::PflowIsolationVariables pfiso = patele.pfIsolationVariables();
    e.set_sumnhet(pfiso.sumNeutralHadronEt);
    e.set_sumchpt(pfiso.sumChargedHadronPt);
    e.set_sumphpt(pfiso.sumPhotonEt);
    e.set_sumpupt(pfiso.sumPUPt);
    float iso = pfiso.sumChargedHadronPt + max(0., pfiso.sumNeutralHadronEt + pfiso.sumPhotonEt - (*rho)*ea);
    e.set_iso_rel_03(iso/patele.pt());
    e.set_iso_rel_03_charged(pfiso.sumChargedHadronPt/patele.pt());

    if(patele.superCluster().isNonnull() && patele.superCluster()->seed().isNonnull()) e.set_deta_in_seed(patele.deltaEtaSuperClusterTrackAtVtx() - patele.superCluster()->eta() + patele.superCluster()->seed()->eta());
    else e.set_deta_in_seed(-999);
    e.set_dphi_in(patele.deltaPhiSuperClusterTrackAtVtx());



    // set ID bits
    e.set_selector(Electron::IDCutBasedVeto, patele.electronID("cutBasedElectronID-Fall17-94X-V2-veto"));
    e.set_selector(Electron::IDCutBasedLoose, patele.electronID("cutBasedElectronID-Fall17-94X-V2-loose"));
    e.set_selector(Electron::IDCutBasedMedium, patele.electronID("cutBasedElectronID-Fall17-94X-V2-medium"));
    e.set_selector(Electron::IDCutBasedTight, patele.electronID("cutBasedElectronID-Fall17-94X-V2-tight"));
    e.set_selector(Electron::IDCutBasedHEEP, patele.electronID("heepElectronID-HEEPV70"));
    e.set_selector(Electron::IDMVAIsoLoose, patele.electronID("mvaEleID-Fall17-iso-V2-wpLoose"));
    e.set_selector(Electron::IDMVAIsoEff90, patele.electronID("mvaEleID-Fall17-iso-V2-wp90"));
    e.set_selector(Electron::IDMVAIsoEff80, patele.electronID("mvaEleID-Fall17-iso-V2-wp80"));
    e.set_selector(Electron::IDMVANonIsoLoose, patele.electronID("mvaEleID-Fall17-noIso-V2-wpLoose"));
    e.set_selector(Electron::IDMVANonIsoEff90, patele.electronID("mvaEleID-Fall17-noIso-V2-wp90"));
    e.set_selector(Electron::IDMVANonIsoEff80, patele.electronID("mvaEleID-Fall17-noIso-V2-wp80"));


    event.electrons->emplace_back(e);

  }



  // Do Taus
  // =======
  // loop over taus
  for(size_t i=0; i<taus->size(); i++){
    pat::Tau pattau = taus->at(i);
    Tau t;

    int jetidx = -1;
    for (size_t j=0; j<jets->size(); j++) { // from here: https://github.com/cms-sw/cmssw/blob/6d2f66057131baacc2fcbdd203588c41c885b42c/PhysicsTools/NanoAOD/plugins/LeptonJetVarProducer.cc#L108#L121
      pat::Jet jet = jets->at(j);
      if (matchByCommonSourceCandidatePtr(pattau, jet)) {
        jetidx = j;
        break;
      }
    }
    t.set_jetidx(jetidx);
    t.set_charge(pattau.charge());
    t.set_pdgid(pattau.pdgId());
    t.set_pt(pattau.pt());
    t.set_eta(pattau.eta());
    t.set_phi(pattau.phi());
    t.set_m(pattau.mass());

    t.set_decay_mode(pattau.decayMode());
    t.set_charged_iso(pattau.tauID("chargedIsoPtSum"));
    t.set_neutral_iso(pattau.tauID("neutralIsoPtSum"));
    t.set_pu_corr(pattau.tauID("puCorrPtSum"));
    const reco::CandidatePtr& leadingPFCharged = pattau.leadChargedHadrCand();
    if (leadingPFCharged.isNonnull()) {
      const pat::PackedCandidate* packedCandPtr = dynamic_cast<const pat::PackedCandidate*>(leadingPFCharged.get());
      if (packedCandPtr != nullptr) {
        const reco::Track* track = packedCandPtr->bestTrack();
        if (track != nullptr) {
          t.set_dxy(fabs(track->dxy()));
          t.set_dz(fabs(track->dz()));
        }
      }

    }
    t.set_score_deeptau_vse(pattau.tauID("byDeepTau2017v2p1VSeraw")); // needs to become v2p1 once added to tuples
    t.set_score_deeptau_vsmu(pattau.tauID("byDeepTau2017v2p1VSmuraw")); // needs to become v2p1 once added to tuples
    t.set_score_deeptau_vsjet(pattau.tauID("byDeepTau2017v2p1VSjetraw")); // needs to become v2p1 once added to tuples
    t.set_comb_iso(pattau.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits"));
    t.set_comb_iso_dr03((pattau.tauID("chargedIsoPtSumdR03")+max(0.,pattau.tauID("neutralIsoPtSumdR03")-0.072*pattau.tauID("puCorrPtSum"))));

    int gen_part_flav = -1;
    if(is_mc){
      // match to gen-e, gen-mu, and genvistaus
      int idx_match_lep = -1;
      float min_dr_lep = 99999;
      for(size_t j=0; j<genparticles->size(); j++){
        reco::GenParticle minigp = genparticles->at(j);
        int gpid = abs(minigp.pdgId());
        if(!(gpid == 11 || gpid == 13)) continue;

        float dr = deltaR(pattau, minigp);
        if(dr < min_dr_lep){
          min_dr_lep = dr;
          if(dr < 0.3) idx_match_lep = j;
        }
      }

      int idx_match_gvt = 0;
      float min_dr_gvt = 99999;
      for(size_t j=0; j<reco_genvistaus.size(); j++){
        reco::GenParticle genvistau = reco_genvistaus.at(j);

        float dr = deltaR(pattau, genvistau);
        if(dr < min_dr_gvt){
          min_dr_gvt = dr;
          if(dr < 0.3) idx_match_gvt = j;
        }
      }

      // define gen part flav as in: https://github.com/cms-sw/cmssw/blob/master/PhysicsTools/NanoAOD/plugins/CandMCMatchTableProducer.cc#L178#L190
      if(idx_match_lep > 0 && genparticles->at(idx_match_lep).statusFlags().isPrompt() && abs(genparticles->at(idx_match_lep).pdgId()) == 11) gen_part_flav = 1;
      else if(idx_match_lep > 0 && genparticles->at(idx_match_lep).statusFlags().isPrompt() && abs(genparticles->at(idx_match_lep).pdgId()) == 13) gen_part_flav = 2;
      else if(idx_match_lep > 0 && genparticles->at(idx_match_lep).isDirectPromptTauDecayProductFinalState() && abs(genparticles->at(idx_match_lep).pdgId()) == 11) gen_part_flav = 3;
      else if(idx_match_lep > 0 && genparticles->at(idx_match_lep).isDirectPromptTauDecayProductFinalState() && abs(genparticles->at(idx_match_lep).pdgId()) == 13) gen_part_flav = 4;
      else if(idx_match_gvt > 0) gen_part_flav = 5;

    }
    t.set_gen_part_flav(gen_part_flav);

    //set ID bits
    t.set_selector(Tau::DeepTauVsJetVVVLoose, pattau.tauID("byVVVLooseDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetVVLoose, pattau.tauID("byVVLooseDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetVLoose, pattau.tauID("byVLooseDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetLoose, pattau.tauID("byLooseDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetMedium, pattau.tauID("byMediumDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetTight, pattau.tauID("byTightDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetVTight, pattau.tauID("byVTightDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsJetVVTight, pattau.tauID("byVVTightDeepTau2017v2p1VSjet"));
    t.set_selector(Tau::DeepTauVsEleVVVLoose, pattau.tauID("byVVVLooseDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleVVLoose, pattau.tauID("byVVLooseDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleVLoose, pattau.tauID("byVLooseDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleLoose, pattau.tauID("byLooseDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleMedium, pattau.tauID("byMediumDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleTight, pattau.tauID("byTightDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleVTight, pattau.tauID("byVTightDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsEleVVTight, pattau.tauID("byVVTightDeepTau2017v2p1VSe"));
    t.set_selector(Tau::DeepTauVsMuVLoose, pattau.tauID("byVLooseDeepTau2017v2p1VSmu"));
    t.set_selector(Tau::DeepTauVsMuLoose, pattau.tauID("byLooseDeepTau2017v2p1VSmu"));
    t.set_selector(Tau::DeepTauVsMuMedium, pattau.tauID("byMediumDeepTau2017v2p1VSmu"));
    t.set_selector(Tau::DeepTauVsMuTight, pattau.tauID("byTightDeepTau2017v2p1VSmu"));



    event.taus->emplace_back(t);
  }




  tree->Fill();
  event.reset();

  return true;
}


void NTuplizer::endJob(){
  event.clear();
  if(outfile && tree){
    outfile->cd();
    outfile->Write();
    outfile->Close();
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(NTuplizer);
