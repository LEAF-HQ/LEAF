#include <TFile.h>
#include <TTree.h>
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include <iostream>
#include "include/GenParticle.h"
#include "include/GenJet.h"
#include "include/Met.h"
#include "include/useful_functions.h"
#include "include/constants.h"
#include <TSystem.h>

using namespace std;

// Example usage:
//
// ./Tuplize /pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root /scratch/areimers/Tuples/LQDM/GENSIM/test.root


int main(int argc, char* argv[]){

  if(argc != 3) throw runtime_error("Expected exactly two arguments. Usage: ./main <infilename> <outfilename>");
  TString director = "root://t3dcachedb03.psi.ch:1094/";
  string inarg  = argv[1];
  string outarg = argv[2];

  TString infilename = (TString)inarg;
  TString outfilename = (TString)outarg;
  if (inarg.rfind("/pnfs", 0) == 0) infilename = director+infilename;


  // TString infilename = "/pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root";
  // TString outfilename = "/scratch/areimers/Tuples/LQDM/GENSIM/test.root";

  TFile* infile = TFile::Open(infilename, "READ");

  const vector<int> npids = get_npids();
  Met* genmet;
  vector<GenParticle>* gps_hard;
  vector<GenParticle>* gps_final;
  vector<GenParticle>* gps_prompttaudecayprod;
  vector<GenJet>*      genjets;

  TFile* outfile = new TFile(outfilename, "RECREATE");
  TTree* tree = new TTree("AnalysisTree", "AnalysisTree");

  tree->Branch("GenMET", &genmet);
  TBranch* b_gps_hard  = tree->Branch("GenparticlesHard", &gps_hard);
  TBranch* b_gps_final = tree->Branch("GenparticlesFinal", &gps_final);
  TBranch* b_gps_prompttaudecayprod = tree->Branch("GenparticlesPromptTauDecayProd", &gps_prompttaudecayprod);
  TBranch* b_genjets   = tree->Branch("GenJets", &genjets);

  fwlite::Handle<std::vector<reco::GenParticle> > handle_gps;
  fwlite::Handle<vector<reco::GenMET> >           handle_met;
  fwlite::Handle<vector<reco::GenJet> >           handle_genjets;


  fwlite::Event event(infile);
  int idx = 0;
  for( event.toBegin(); ! event.atEnd(); ++event) {
    if(((idx+1) % 1000 == 0) || idx == 0) cout << green << "    --> At event: " << idx+1 << reset << endl;
    handle_gps    .getByLabel(event, "genParticles");
    handle_met    .getByLabel(event, "genMetTrue");
    handle_genjets.getByLabel(event, "ak4GenJets");
    const std::vector<reco::GenMET, std::allocator<reco::GenMET>>*           gm  = handle_met.product();
    const std::vector<reco::GenParticle, std::allocator<reco::GenParticle>>* gps = handle_gps.product();
    const std::vector<reco::GenJet, std::allocator<reco::GenJet>>*           gjs = handle_genjets.product();

    gps_final              = new vector<GenParticle>;
    gps_prompttaudecayprod = new vector<GenParticle>;
    gps_hard               = new vector<GenParticle>;
    genjets                = new vector<GenJet>;
    genmet                 = new Met;


    // Do GenParticles
    // ===============

    for(size_t i=0; i<gps->size(); i++){
      int id = fabs(gps->at(i).pdgId());

      // This selects all particles in their final form (i.e. after radiation, but before potential decay, to compare to particles from hard process)
      bool isfinal = gps->at(i).isLastCopy();

      //This selects all final-state particles (i.e. no intermediate particles that decay further)
      bool ishard  = gps->at(i).isHardProcess();
      bool isprompttaudecayprod = gps->at(i).statusFlags().isPromptTauDecayProduct() && gps->at(i).status() == 1;
      bool keepfinal = false;
      if(isfinal){
        //keep, if final particle is b, t, tau, or nutau
        if(id == 5 || id == 6 || id == 15 || id == 16) keepfinal = true;
      }

      // this will be written out if we keep this particle
      GenParticle p;
      p.set_pt(gps->at(i).pt());
      p.set_eta(gps->at(i).eta());
      p.set_phi(gps->at(i).phi());
      p.set_m(gps->at(i).mass());
      p.set_pdgid(gps->at(i).pdgId());

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


    // Do GenJets
    // ==========

    for(size_t i=0; i<gjs->size(); i++){

      GenJet gj;
      gj.set_p4(gjs->at(i).pt(), gjs->at(i).eta(), gjs->at(i).phi(), gjs->at(i).mass());
      gj.set_n_constituents(gjs->at(i).getGenConstituents().size());

      // remove NP particles that have been clustered into a jet from the jet. Only happens for DM.
      for(size_t j=0; j<gjs->at(i).getGenConstituents().size(); j++){
        int id = abs(gjs->at(i).getGenConstituents().at(j)->pdgId());
        for(size_t k=0; k<npids.size(); k++){
          if(id == npids[k]){

            //Get NP 4-momentum
            GenParticle np;
            np.set_p4(gjs->at(i).getGenConstituents().at(j)->pt(), gjs->at(i).getGenConstituents().at(j)->eta(), gjs->at(i).getGenConstituents().at(j)->phi(), gjs->at(i).getGenConstituents().at(j)->mass());

            //Remove np 4-momentum
            gj.set_p4(gj.p4() - np.p4());
          }
        }
      }

      // save only genjets with at least 5GeV and |eta| < 5
      if(gj.pt() < 5 || fabs(gj.eta()) > 5.) continue;
      genjets->emplace_back(gj);
    }


    // Do GenMET
    // =========

    genmet->set_pt(gm->at(0).pt());
    genmet->set_phi(gm->at(0).phi());




    b_gps_final             ->SetAddress(&gps_final);
    b_gps_hard              ->SetAddress(&gps_hard);
    b_gps_prompttaudecayprod->SetAddress(&gps_prompttaudecayprod);
    b_genjets               ->SetAddress(&genjets);
    tree->Fill();
    idx ++;

    delete gps_final;
    delete gps_hard;
    delete gps_prompttaudecayprod;
    delete genmet;
    delete genjets;
  }


  tree->Write();
  outfile->Close();
}
