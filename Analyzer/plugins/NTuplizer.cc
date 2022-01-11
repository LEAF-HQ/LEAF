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


  edm::EDGetTokenT<std::vector<pat::Muon>> token_muons;
  edm::EDGetTokenT<std::vector<pat::MET>> token_mets;
  edm::EDGetTokenT<std::vector<reco::Vertex>> token_primary_vertices;
  edm::EDGetTokenT<double> token_rho, token_l1prefiring, token_l1prefiring_up, token_l1prefiring_down;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > token_pus;


  TString outfilename;
  bool is_mc;


  TFile *outfile;
  TTree *tree;
  RecoEvent event;

};

NTuplizer::NTuplizer(const edm::ParameterSet& iConfig){

  outfilename = (TString)iConfig.getParameter<std::string>("outfilename");
  is_mc       = iConfig.getParameter<bool>("is_mc");
  if(outfilename != ""){
    outfile = new TFile(outfilename, "RECREATE");
    outfile->cd();
    tree = new TTree("AnalysisTree", "AnalysisTree");
    tree->Branch("Events", &event);
  }

  token_muons            = consumes<std::vector<pat::Muon>>   (iConfig.getParameter<edm::InputTag>("muons"));
  token_mets             = consumes<std::vector<pat::MET>>    (iConfig.getParameter<edm::InputTag>("MET"));
  token_primary_vertices = consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("primary_vertices"));
  token_rho              = consumes<double>(iConfig.getParameter<edm::InputTag>("rho"));
  token_l1prefiring      = consumes<double>(iConfig.getParameter<edm::InputTag>("l1prefiring"));
  token_l1prefiring_up   = consumes<double>(iConfig.getParameter<edm::InputTag>("l1prefiring_up"));
  token_l1prefiring_down = consumes<double>(iConfig.getParameter<edm::InputTag>("l1prefiring_down"));
  token_pus              = consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileup"));

}

bool NTuplizer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){

  edm::Handle<std::vector<pat::Muon>> muons;
  iEvent.getByToken(token_muons, muons);

  edm::Handle<std::vector<pat::MET>> mets;
  iEvent.getByToken(token_mets, mets);

  edm::Handle<std::vector<reco::Vertex>> pvs;
  iEvent.getByToken(token_primary_vertices, pvs);

  edm::Handle<double> rho;
  iEvent.getByToken(token_rho, rho);

  edm::Handle<double> l1prefiring, l1prefiring_up, l1prefiring_down;
  iEvent.getByToken(token_l1prefiring, l1prefiring);
  iEvent.getByToken(token_l1prefiring_up, l1prefiring_up);
  iEvent.getByToken(token_l1prefiring_down, l1prefiring_down);

  edm::Handle<std::vector<PileupSummaryInfo>> pus;
  if(is_mc){
    iEvent.getByToken(token_pus, pus);
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
    // for(size_t i=0; i<genjets->size(); i++){
    //   GenJet gj;
    //   reco::GenJet minigj = genjets->at(i);
    //   gj.set_p4(minigj.pt(), minigj.eta(), minigj.phi(), minigj.mass());
    //   gj.set_n_constituents(minigj.chargedHadronMultiplicity() + minigj.neutralHadronMultiplicity() + minigj.chargedEmMultiplicity() + minigj.neutralEmMultiplicity() + minigj.muonMultiplicity());
    //   event.genjets->emplace_back(gj);
    // }

    // GenParticles
    // for(size_t i=0; i<genparticles->size(); i++){
    //   reco::GenParticle minigp = genparticles->at(i);
    //   GenParticle gp;
    //   gp.set_p4(minigp.pt(), minigp.eta(), minigp.phi(), minigp.mass());
    //   gp.set_pdgid(minigp.pdgId());
    //   gp.set_charge(minigp.charge());
    //   int motherid = -1;
    //   if(minigp.numberOfMothers() > 0) motherid = minigp.motherRef(0).key();
    //   gp.set_mother_identifier(motherid);
    //   gp.set_identifier(i);
    //   gp.set_status(minigp.status());
    //   gp.set_statusflag(GenParticle::isPrompt, minigp.statusFlags().isPrompt());
    //   gp.set_statusflag(GenParticle::isDecayedLeptonHadron, minigp.statusFlags().isDecayedLeptonHadron());
    //   gp.set_statusflag(GenParticle::isTauDecayProduct, minigp.statusFlags().isTauDecayProduct());
    //   gp.set_statusflag(GenParticle::isPromptTauDecayProduct, minigp.statusFlags().isPromptTauDecayProduct());
    //   gp.set_statusflag(GenParticle::isDirectTauDecayProduct, minigp.statusFlags().isDirectTauDecayProduct());
    //   gp.set_statusflag(GenParticle::isDirectPromptTauDecayProduct, minigp.statusFlags().isDirectPromptTauDecayProduct());
    //   gp.set_statusflag(GenParticle::isDirectHadronDecayProduct, minigp.statusFlags().isDirectHadronDecayProduct());
    //   gp.set_statusflag(GenParticle::isHardProcess, minigp.statusFlags().isHardProcess());
    //   gp.set_statusflag(GenParticle::fromHardProcess, minigp.statusFlags().fromHardProcess());
    //   gp.set_statusflag(GenParticle::isHardProcessTauDecayProduct, minigp.statusFlags().isHardProcessTauDecayProduct());
    //   gp.set_statusflag(GenParticle::isDirectHardProcessTauDecayProduct, minigp.statusFlags().isDirectHardProcessTauDecayProduct());
    //   gp.set_statusflag(GenParticle::fromHardProcessBeforeFSR, minigp.statusFlags().fromHardProcessBeforeFSR());
    //   gp.set_statusflag(GenParticle::isFirstCopy, minigp.statusFlags().isFirstCopy());
    //   gp.set_statusflag(GenParticle::isLastCopy, minigp.statusFlags().isLastCopy());
    //   gp.set_statusflag(GenParticle::isLastCopyBeforeFSR, minigp.statusFlags().isLastCopyBeforeFSR());
    //   event.genparticles_all->emplace_back(gp);
    // }

    // GenVisTaus
    // vector<reco::GenJet> genTauJets = {};
    // reco::GenParticleRefVector allStatus2Taus;
    // GenParticlesHelper::findParticles(*genparticles, allStatus2Taus, 15, 2);
    //
    // for (reco::GenParticleRefVector::const_iterator iTau = allStatus2Taus.begin(); iTau != allStatus2Taus.end(); ++iTau) {
    //   // look for all status 1 (stable) descendents
    //   reco::GenParticleRefVector descendents;
    //   GenParticlesHelper::findDescendents(*iTau, descendents, 1);
    //
    //   // CV: skip status 2 taus that radiate-off a photon
    //   //    --> have a status 2 tau lepton in the list of descendents
    //   reco::GenParticleRefVector status2TauDaughters;
    //   GenParticlesHelper::findDescendents(*iTau, status2TauDaughters, 2, 15);
    //   if (!status2TauDaughters.empty())
    //   continue;
    //
    //   // loop on descendents, and take all except neutrinos
    //   math::XYZTLorentzVector sumVisMom;
    //   reco::Particle::Charge charge = 0;
    //   reco::Jet::Constituents constituents;
    //
    //   for (reco::GenParticleRefVector::const_iterator igr = descendents.begin(); igr != descendents.end(); ++igr) {
    //     int absPdgId = abs((*igr)->pdgId());
    //
    //     // skip neutrinos
    //     if (absPdgId == 12 || absPdgId == 14 || absPdgId == 16)
    //     continue;
    //
    //     charge += (*igr)->charge();
    //     sumVisMom += (*igr)->p4();
    //     constituents.push_back(refToPtr(*igr));
    //   }
    //
    //   math::XYZPoint vertex;
    //   reco::GenJet::Specific specific;
    //
    //   reco::GenJet jet(sumVisMom, vertex, specific, constituents);
    //
    //   jet.setCharge(charge);
    //   genTauJets.push_back(jet);
    // }

    // for (const auto& genTauJet : genTauJets) {
    //   std::string decayMode_string = JetMCTagUtils::genTauDecayMode(genTauJet);
    //   // CV: store hadronic tau decays only
    //   if (decayMode_string == "electron" || decayMode_string == "muon")
    //   continue;
    //   int decayMode = reco::PFTau::kNull;
    //   if (decayMode_string == "oneProng0Pi0")
    //   decayMode = reco::PFTau::kOneProng0PiZero;
    //   else if (decayMode_string == "oneProng1Pi0")
    //   decayMode = reco::PFTau::kOneProng1PiZero;
    //   else if (decayMode_string == "oneProng2Pi0")
    //   decayMode = reco::PFTau::kOneProng2PiZero;
    //   else if (decayMode_string == "threeProng0Pi0")
    //   decayMode = reco::PFTau::kThreeProng0PiZero;
    //   else if (decayMode_string == "threeProng1Pi0")
    //   decayMode = reco::PFTau::kThreeProng1PiZero;
    //   else
    //   decayMode = reco::PFTau::kRareDecayMode;
    //
    //   int pdgId = (genTauJet.charge() > 0) ? -15 : +15;
    //
    //   // CV: store decayMode in status flag of GenParticle object
    //   reco::GenParticle genVisTau(genTauJet.charge(), genTauJet.p4(), genTauJet.vertex(), pdgId, decayMode, true);
    //
    //   // CV: find tau lepton "mother" particle
    //   for (size_t idxGenParticle = 0; idxGenParticle < genparticles->size(); ++idxGenParticle) {
    //     const reco::GenParticle& genTau = (*genparticles)[idxGenParticle];
    //     if (abs(genTau.pdgId()) == 15 && genTau.status() == 2) {
    //       reco::Candidate::LorentzVector daughterVisP4;
    //       for (const reco::GenParticleRef& daughter : genTau.daughterRefVector()) {
    //         int abs_pdgId = abs(daughter->pdgId());
    //         // CV: skip neutrinos
    //         if (abs_pdgId == 12 || abs_pdgId == 14 || abs_pdgId == 16)
    //         continue;
    //         daughterVisP4 += daughter->p4();
    //       }
    //       double dR2 = deltaR2(daughterVisP4, genVisTau);
    //       if (dR2 < 1.e-4) {
    //         genVisTau.addMother(reco::GenParticleRef(genparticles, idxGenParticle));
    //         break;
    //       }
    //     }
    //   }
    //
    // reco_genvistaus.emplace_back(genVisTau);
    // here the source genvistau is complete, ready to translate to LEAF format
    // GenParticle gvt;
    // gvt.set_p4(genVisTau.pt(), genVisTau.eta(), genVisTau.phi(), genVisTau.mass());
    // gvt.set_pdgid(genVisTau.pdgId());
    // int gvtmotherid = -1;
    // if(genVisTau.numberOfMothers() > 0) gvtmotherid = genVisTau.motherRef(0).key();
    // gvt.set_mother_identifier(gvtmotherid);
    // gvt.set_status(genVisTau.status());
    // event.genparticles_visibletaus->emplace_back(gvt);
    // }


    // global gen info
    // event.weight = geninfo->weight(); // equivalent to geninfo->weights().at(0), always returns the 0th element
    // event.geninfo->set_weight(geninfo->weight());
    // const gen::PdfInfo* pdf = geninfo->pdf();
    // if(pdf){
    //   event.geninfo->set_id1(pdf->id.first);
    //   event.geninfo->set_id2(pdf->id.second);
    //   event.geninfo->set_x1(pdf->x.first);
    //   event.geninfo->set_x2(pdf->x.second);
    //   event.geninfo->set_scale_pdf(pdf->scalePDF);
    //   event.geninfo->set_xpdf1(pdf->xPDF.first);
    //   event.geninfo->set_xpdf2(pdf->xPDF.second);
    // }
    // else{
    //   event.geninfo->set_id1(-999);
    //   event.geninfo->set_id2(-999);
    //   event.geninfo->set_x1(-999);
    //   event.geninfo->set_x2(-999);
    //   event.geninfo->set_scale_pdf(-999);
    //   event.geninfo->set_xpdf1(-999);
    //   event.geninfo->set_xpdf2(-999);
    // }
    //
    // vector<double> systweights = {};
    // if(has_lhe){
    //   event.geninfo->set_originalXWGTUP(lhe->originalXWGTUP());
    //   for(unsigned int i=0; i<lhe->weights().size(); i++){
    //     systweights.emplace_back(lhe->weights().at(i).wgt);
    //   }
    // }
    // event.geninfo->set_systweights(systweights);
  }
  else{
    event.weight = 1.;
  }






  tree->Fill();

  return true;
}


void NTuplizer::endJob(){
  if(outfile && tree){
    outfile->cd();
    outfile->Write();
    outfile->Close();
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(NTuplizer);
