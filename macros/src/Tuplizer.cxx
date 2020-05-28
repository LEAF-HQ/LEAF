#include <TFile.h>
#include <TTree.h>
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include <iostream>
#include "../include/GenParticle.h"
#include "../include/Met.h"
#include <TSystem.h>

using namespace std;

int main(){

  // FWLiteEnabler::enable();
  TFile* infile = TFile::Open("root://t3dcachedb03.psi.ch:1094//pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root", "READ");




  vector<int> lqids = {9000008, 9000009};
  vector<int> xids  = {9000006, 9000007};
  vector<int> dmids = {9000005};


  Met* genmet;
  vector<GenParticle>* gps_hard;
  vector<GenParticle>* gps_final;
  vector<GenParticle>* gps_prompttaudecayprod;

  TFile* outfile = new TFile("test_macro.root", "RECREATE");
  TTree* tree = new TTree("Tree", "Tree");

  tree->Branch("GenMET", &genmet);
  TBranch* b_gps_hard  = tree->Branch("GenparticlesHard", &gps_hard);
  TBranch* b_gps_final = tree->Branch("GenparticlesFinal", &gps_final);
  TBranch* b_gps_prompttaudecayprod = tree->Branch("GenparticlesPromptTauDecayProd", &gps_prompttaudecayprod);

  fwlite::Handle<std::vector<reco::GenParticle> > handle_gps;
  fwlite::Handle<vector<reco::GenMET> >           handle_met;

  fwlite::Event event(infile);
  int idx = 0;
  for( event.toBegin(); ! event.atEnd(); ++event) {
    // cout << "+++++ NEW EVENT +++++" << endl;
    if(idx % 100 == 0) cout << "--> At event: " << idx << endl;
    handle_gps.getByLabel(event, "genParticles");
    handle_met.getByLabel(event, "genMetTrue");
    const std::vector<reco::GenMET, std::allocator<reco::GenMET>>* gm = handle_met.product();
    const std::vector<reco::GenParticle, std::allocator<reco::GenParticle>>* gps = handle_gps.product();

    gps_final = new vector<GenParticle>;
    gps_prompttaudecayprod = new vector<GenParticle>;
    gps_hard  = new vector<GenParticle>;
    genmet    = new Met;
    for(size_t i=0; i<gps->size(); i++){
      int id = fabs(gps->at(i).pdgId());

      // This selects all particles in their final form (i.e. after radiation, but before potential decay, to compare to particles from hard process)
      bool isfinal = gps->at(i).isLastCopy();

      //This selects all final-state particles (i.e. no intermediate particles that decay further)
      // bool isfinal = gps->at(i).status() == 1;
      bool ishard  = gps->at(i).isHardProcess();
      bool isprompttaudecayprod = gps->at(i).statusFlags().isPromptTauDecayProduct() && gps->at(i).status() == 1;
      bool keepfinal = false;
      if(isfinal){
        // // keep, if final particles are NP
        // for(size_t j=0; j<lqids.size(); j++){
        //   if(id == lqids[j]) keepfinal = true;
        // }
        // for(size_t j=0; j<dmids.size(); j++){
        //   if(id == dmids[j]) keepfinal = true;
        // }
        // for(size_t j=0; j<xids.size(); j++){
        //   if(id == xids[j]) keepfinal = true;
        // }

        //keep also, if final particle is b, t, tau, or nutau
        if(id == 5 || id == 6 || id == 15 || id == 16) keepfinal = true;
      }

      // this will be written out if we keep this particle
      GenParticle p;
      p.set_pt(gps->at(i).pt());
      p.set_eta(gps->at(i).eta());
      p.set_phi(gps->at(i).phi());
      p.set_m(gps->at(i).mass());
      p.set_pdgid(gps->at(i).pdgId());
      p.set_evtid(idx);

      if(keepfinal){
        gps_final->emplace_back(p);
      }
      if(ishard){
        gps_hard->emplace_back(p);
      }
      if(isprompttaudecayprod){
        gps_prompttaudecayprod->emplace_back(p);
      }
    }


    genmet->set_pt(gm->at(0).pt());
    genmet->set_phi(gm->at(0).phi());
    b_gps_final->SetAddress(&gps_final);
    b_gps_hard ->SetAddress(&gps_hard);
    b_gps_prompttaudecayprod->SetAddress(&gps_prompttaudecayprod);
    tree->Fill();
    idx ++;

    delete gps_final;
    delete gps_hard;
    delete gps_prompttaudecayprod;
    delete genmet;
  }


  tree->Write();
  outfile->Close();
}
