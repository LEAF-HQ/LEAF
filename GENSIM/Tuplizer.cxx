#include <TFile.h>
#include <TTree.h>
#include "DataFormats/FWLite/interface/Handle.h"
#include <iostream>
#include "../macros/include/Particle.h"


void Tuplizer(){

  gSystem->Load("libFWCoreFWLite.so");
  FWLiteEnabler::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");
  gSystem->Load("AutoDict_Particle_cxx.so");
  gSystem->Load("AutoDict_vector_Particle__cxx.so");

  // TFile* infile = new TFile("/scratch/areimers/ForYogesh/ScalarLQ_Pair_M800_L1p0/GENSIM_1.root", "READ");
  TFile* infile = TFile::Open("root://t3dcachedb03.psi.ch:1094//pnfs/psi.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/LQDM_MLQ1400_MX660_MDM600_L1p0/GENSIM_1.root", "READ");
  std::cout << "Success!" << std::endl;




  vector<int> lqids = {9000008, 9000009};
  vector<int> xids  = {9000006, 9000007};
  vector<int> dmids = {9000005};


  double ptmet;
  vector<Particle>* v_gps;
  // vector<double> v_gps;
  Particle ptcl;

  TFile* outfile = new TFile("test_macro.root", "RECREATE");
  TTree* tree = new TTree("Tree", "Tree");
  TBranch* b_ptmet = tree->Branch("ptmet", &ptmet, "ptmet/D");
  TBranch* b_gps   = tree->Branch("v_gps", &v_gps);
  TBranch* b_ptcl  = tree->Branch("ptcl", &ptcl);


  fwlite::Handle<std::vector<reco::GenParticle> > handle_gps;
  fwlite::Handle<vector<reco::GenMET> >           handle_met;

  fwlite::Event event(infile);
  int idx = 0;
  for( event.toBegin(); ! event.atEnd(); ++event) {
    if(idx % 100 == 0) cout << "--> At event: " << idx << endl;
    handle_gps.getByLabel(event, "genParticles");
    handle_met.getByLabel(event, "genMetTrue");

    // vector<reco::GenMET>* met = handle_met.product();
    const std::vector<reco::GenMET, std::allocator<reco::GenMET>>* met = handle_met.product();
    const std::vector<reco::GenParticle, std::allocator<reco::GenParticle>>* gps = handle_gps.product();
    // v_gps = {};
    v_gps = new vector<Particle>;
    for(size_t i=0; i<gps->size(); i++){
      // int id = fabs(gps->at(i).pdgId());
      // bool keep = false;
      // for(size_t j=0; j<lqids.size(); j++){
      //   if(id == lqids[j]) keep = true;
      // }
      // if(keep){
      if(i == 10) break;
      Particle p;
      p.set_pt(gps->at(i).pt());
      p.set_eta(gps->at(i).eta());
      p.set_phi(gps->at(i).phi());
      p.set_m(gps->at(i).mass());
      p.set_evtid(idx);
      if(idx%2==0) v_gps->emplace_back(p);
      else{
        v_gps->emplace_back(p);
        v_gps->emplace_back(p);
      }
      // }
    }

    ptcl.set_pt(gps->at(0).pt());
    ptcl.set_eta(gps->at(0).eta());
    ptcl.set_phi(gps->at(0).phi());
    ptcl.set_m(gps->at(0).mass());
    ptcl.set_evtid(idx);



    ptmet = met->at(0).pt();
    b_gps->SetAddress(&v_gps);
    tree->Fill();
    idx ++;

    // v_gps.clear();
    delete v_gps;
  }


  tree->Write();
  outfile->Close();






}
