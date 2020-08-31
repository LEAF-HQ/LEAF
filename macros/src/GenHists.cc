#include "include/GenHists.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include "include/useful_functions.h"
#include <TH1F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

GenHists::GenHists(TString dir_) : BaseHists(dir_){

  hnlq = book<TH1F>("nlq", ";N_{LQ}; Events / bin", 6, -0.5, 5.5);
  hnpsi = book<TH1F>("npsi", ";N_{#psi}; Events / bin", 6, -0.5, 5.5);
  hnchi = book<TH1F>("nchi", ";N_{#chi}; Events / bin", 6, -0.5, 5.5);
  hnjets = book<TH1F>("njets", ";N_{jets}; Events / bin", 11, -0.5, 10.5);
  hnbhard = book<TH1F>("nbhard", ";N_{hard b}; Events / bin", 6, -0.5, 5.5);
  hntauhard = book<TH1F>("ntauhard", ";N_{hard #tau}; Events / bin", 6, -0.5, 5.5);
  hntauvis = book<TH1F>("ntauvis", ";N_{vis. #tau}; Events / bin", 6, -0.5, 5.5);
  hmlq1 = book<TH1F>("mlq1", ";M_{LQ 1} [GeV]; Events / bin", 300, 0, 3000);
  hmlq2 = book<TH1F>("mlq2", ";M_{LQ 2} [GeV]; Events / bin", 300, 0, 3000);
  hmpsi1 = book<TH1F>("mpsi1", ";M_{#psi 1} [GeV]; Events / bin", 300, 0, 3000);
  hmpsi2 = book<TH1F>("mpsi2", ";M_{#psi 2} [GeV]; Events / bin", 300, 0, 3000);
  hmchi1 = book<TH1F>("mchi1", ";M_{#chi 1} [GeV]; Events / bin", 300, 0, 3000);
  hmchi2 = book<TH1F>("mchi2", ";M_{#chi 2} [GeV]; Events / bin", 300, 0, 3000);
  hptlq1 = book<TH1F>("ptlq1", ";p_{T}^{LQ 1} [GeV]; Events / bin", 300, 0, 3000);
  hptlq2 = book<TH1F>("ptlq2", ";p_{T}^{LQ 2} [GeV]; Events / bin", 300, 0, 3000);
  hptpsi1 = book<TH1F>("ptpsi1", ";p_{T}^{#psi 1} [GeV]; Events / bin", 300, 0, 3000);
  hptpsi2 = book<TH1F>("ptpsi2", ";p_{T}^{#psi 2} [GeV]; Events / bin", 300, 0, 3000);
  hptchi1 = book<TH1F>("ptchi1", ";p_{T}^{#chi 1} [GeV]; Events / bin", 300, 0, 3000);
  hptchi2 = book<TH1F>("ptchi2", ";p_{T}^{#chi 2} [GeV]; Events / bin", 300, 0, 3000);
  hetalq1 = book<TH1F>("etalq1", ";#eta_{LQ 1}; Events / bin", 60, -3.5, 3.5);
  hetalq2 = book<TH1F>("etalq2", ";#eta_{LQ 2}; Events / bin", 60, -3.5, 3.5);
  hetapsi1 = book<TH1F>("etapsi1", ";#eta_{#psi 1}; Events / bin", 60, -3.5, 3.5);
  hetapsi2 = book<TH1F>("etapsi2", ";#eta_{#psi 2}; Events / bin", 60, -3.5, 3.5);
  hetachi1 = book<TH1F>("etachi1", ";#eta_{#chi 1}; Events / bin", 60, -3.5, 3.5);
  hetachi2 = book<TH1F>("etachi2", ";#eta_{#chi 2}; Events / bin", 60, -3.5, 3.5);
  hphilq1 = book<TH1F>("philq1", ";#phi_{LQ 1}; Events / bin", 60, -3.5, 3.5);
  hphilq2 = book<TH1F>("philq2", ";#phi_{LQ 2}; Events / bin", 60, -3.5, 3.5);
  hphipsi1 = book<TH1F>("phipsi1", ";#phi_{#psi 1}; Events / bin", 60, -3.5, 3.5);
  hphipsi2 = book<TH1F>("phipsi2", ";#phi_{#psi 2}; Events / bin", 60, -3.5, 3.5);
  hphichi1 = book<TH1F>("phichi1", ";#phi_{#chi 1}; Events / bin", 60, -3.5, 3.5);
  hphichi2 = book<TH1F>("phichi2", ";#phi_{#chi 2}; Events / bin", 60, -3.5, 3.5);

  hptjet1 = book<TH1F>("ptjet1", ";p_{T}^{jet 1} [GeV]; Events / bin", 300, 0, 3000);
  hptjet2 = book<TH1F>("ptjet2", ";p_{T}^{jet 2} [GeV]; Events / bin", 300, 0, 3000);
  hptjet3 = book<TH1F>("ptjet3", ";p_{T}^{jet 3} [GeV]; Events / bin", 300, 0, 3000);
  hptbhard1 = book<TH1F>("ptbhard1", ";p_{T}^{b 1} [GeV]; Events / bin", 300, 0, 3000);
  hptbhard2 = book<TH1F>("ptbhard2", ";p_{T}^{b 2} [GeV]; Events / bin", 300, 0, 3000);
  hpttauhard1 = book<TH1F>("pttauhard1", ";p_{T}^{#tau 1} [GeV]; Events / bin", 300, 0, 3000);
  hpttauhard2 = book<TH1F>("pttauhard2", ";p_{T}^{#tau 2} [GeV]; Events / bin", 300, 0, 3000);
  hpttauvis1 = book<TH1F>("pttauvis1", ";p_{T}^{vis. #tau 1} [GeV]; Events / bin", 300, 0, 3000);
  hpttauvis2 = book<TH1F>("pttauvis2", ";p_{T}^{vis. #tau 2} [GeV]; Events / bin", 300, 0, 3000);
  hetajet1 = book<TH1F>("etajet1", ";#eta_{jet 1}; Events / bin", 60, -3.5, 3.5);
  hetajet2 = book<TH1F>("etajet2", ";#eta_{jet 2}; Events / bin", 60, -3.5, 3.5);
  hetajet3 = book<TH1F>("etajet3", ";#eta_{jet 3}; Events / bin", 60, -3.5, 3.5);
  hetabhard1 = book<TH1F>("etabhard1", ";#eta_{b 1}; Events / bin", 60, -3.5, 3.5);
  hetabhard2 = book<TH1F>("etabhard2", ";#eta_{b 2}; Events / bin", 60, -3.5, 3.5);
  hetatauhard1 = book<TH1F>("etatauhard1", ";#eta_{#tau 1}; Events / bin", 60, -3.5, 3.5);
  hetatauhard2 = book<TH1F>("etatauhard2", ";#eta_{#tau 2}; Events / bin", 60, -3.5, 3.5);
  hetatauvis1 = book<TH1F>("etatauvis1", ";#eta_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5);
  hetatauvis2 = book<TH1F>("etatauvis2", ";#eta_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5);
  hphijet1 = book<TH1F>("phijet1", ";#phi_{jet 1}; Events / bin", 60, -3.5, 3.5);
  hphijet2 = book<TH1F>("phijet2", ";#phi_{jet 2}; Events / bin", 60, -3.5, 3.5);
  hphijet3 = book<TH1F>("phijet3", ";#phi_{jet 3}; Events / bin", 60, -3.5, 3.5);
  hphibhard1 = book<TH1F>("phibhard1", ";#phi_{b 1}; Events / bin", 60, -3.5, 3.5);
  hphibhard2 = book<TH1F>("phibhard2", ";#phi_{b 2}; Events / bin", 60, -3.5, 3.5);
  hphitauhard1 = book<TH1F>("phitauhard1", ";#phi_{#tau 1}; Events / bin", 60, -3.5, 3.5);
  hphitauhard2 = book<TH1F>("phitauhard2", ";#phi_{#tau 2}; Events / bin", 60, -3.5, 3.5);
  hphitauvis1 = book<TH1F>("phitauvis1", ";#phi_{vis. #tau 1}; Events / bin", 60, -3.5, 3.5);
  hphitauvis2 = book<TH1F>("phitauvis2", ";#phi_{vis. #tau 2}; Events / bin", 60, -3.5, 3.5);
  hmjet1 = book<TH1F>("mjet1", ";M_{jet 1} [GeV]; Events / bin", 50, 0, 500);
  hmjet2 = book<TH1F>("mjet2", ";M_{jet 2} [GeV]; Events / bin", 50, 0, 500);
  hmjet3 = book<TH1F>("mjet3", ";M_{jet 3} [GeV]; Events / bin", 50, 0, 500);
  hmbhard1 = book<TH1F>("mbhard1", ";M_{b 1} [GeV]; Events / bin", 20, 0, 10);
  hmbhard2 = book<TH1F>("mbhard2", ";M_{b 2} [GeV]; Events / bin", 20, 0, 10);
  hmtauhard1 = book<TH1F>("mtauhard1", ";M_{#tau 1} [GeV]; Events / bin", 20, 0, 5);
  hmtauhard2 = book<TH1F>("mtauhard2", ";M_{#tau 2} [GeV]; Events / bin", 20, 0, 5);
  hmtauvis1 = book<TH1F>("mtauvis1", ";M_{vis. #tau 1} [GeV]; Events / bin", 20, 0, 5);
  hmtauvis2 = book<TH1F>("mtauvis2", ";M_{vis. #tau 2} [GeV]; Events / bin", 20, 0, 5);

  hdrminj1tauvis = book<TH1F>("drj1tauvis", ";#Delta R(jet 1, closest vis. #tau); Events / bin", 50, 0, 5);
  hdrminj2tauvis = book<TH1F>("drj2tauvis", ";#Delta R(jet 2, closest vis. #tau); Events / bin", 50, 0, 5);

  hptmet = book<TH1F>("ptmet", ";E_{T}^{miss} (GenMET) [GeV]; Events / bin", 300, 0, 3000);
  hphimet = book<TH1F>("phimet", ";#phi(E_{T}^{miss} (GenMET)); Events / bin", 60, -3.5, 3.5);
  hptmetfrominvis = book<TH1F>("ptmetfrominvis", ";E_{T}^{miss} (from invis.) [GeV]; Events / bin", 300, 0, 3000);
  hphimetfrominvis = book<TH1F>("phimetfrominvis", ";#phi(E_{T}^{miss} (from invis.)); Events / bin", 60, -3.5, 3.5);
  hst = book<TH1F>("st", ";S_{T} [GeV]; Events / bin", 300, 0, 3000);
  hstmet = book<TH1F>("stmet", ";S_{T}^{MET} [GeV]; Events / bin", 300, 0, 3000);
  hstmetfrominvis = book<TH1F>("stmetfrominvis", ";S_{T}^{MET} (from invis.) [GeV]; Events / bin", 300, 0, 3000);

  hmj1tauvis1 = book<TH1F>("mj1tauvis1", ";M(jet 1, vis. #tau 1) [GeV]; Events / bin", 300, 0, 3000);

  hsumweights = book<TH1F>("sumweights", ";bincontent = sum of event weights; Events / bin", 1, 0.5, 1.5);

}

void GenHists::fill(const GenEvent & event){
  double weight = event.weight;


  // loop through hard particles
  // ===========================

  size_t nlq, nchi, npsi, nbhard, ntauhard;
  nlq = nchi = npsi = nbhard = ntauhard = 0;
  for(size_t i=0; i<event.genparticles_hard->size(); i++){
    GenParticle gp = event.genparticles_hard->at(i);
    int id = abs(gp.pdgid());

    // hard LQs
    for(size_t j=0; j<lqids.size(); j++){
      if(id == lqids[j]){
        if(nlq==0){
          hptlq1 ->Fill(gp.pt(), weight);
          hetalq1->Fill(gp.eta(), weight);
          hphilq1->Fill(gp.phi(), weight);
          hmlq1  ->Fill(gp.m(), weight);
        }
        else if(nlq==1){
          hptlq2 ->Fill(gp.pt(), weight);
          hetalq2->Fill(gp.eta(), weight);
          hphilq2->Fill(gp.phi(), weight);
          hmlq2  ->Fill(gp.m(), weight);
        }
        nlq++;
      }
    }

    // hard #chi
    for(size_t j=0; j<chiids.size(); j++){
      if(id == chiids[j]){
        if(nchi==0){
          hptchi1 ->Fill(gp.pt(), weight);
          hetachi1->Fill(gp.eta(), weight);
          hphichi1->Fill(gp.phi(), weight);
          hmchi1  ->Fill(gp.m(), weight);
        }
        else if(nchi==1){
          hptchi2 ->Fill(gp.pt(), weight);
          hetachi2->Fill(gp.eta(), weight);
          hphichi2->Fill(gp.phi(), weight);
          hmchi2  ->Fill(gp.m(), weight);
        }
        nchi++;
      }
    }

    //hard #psi
    for(size_t j=0; j<psiids.size(); j++){
      if(id == psiids[j]){
        if(npsi == 0){
          hptpsi1 ->Fill(gp.pt(), weight);
          hetapsi1->Fill(gp.eta(), weight);
          hphipsi1->Fill(gp.phi(), weight);
          hmpsi1  ->Fill(gp.m(), weight);
        }
        else if(npsi == 1){
          hptpsi2 ->Fill(gp.pt(), weight);
          hetapsi2->Fill(gp.eta(), weight);
          hphipsi2->Fill(gp.phi(), weight);
          hmpsi2  ->Fill(gp.m(), weight);
        }
        npsi++;
      }
    }

    //hard b
    if(id == 5){
      if(nbhard == 0){
        hptbhard1 ->Fill(gp.pt(), weight);
        hetabhard1->Fill(gp.eta(), weight);
        hphibhard1->Fill(gp.phi(), weight);
        hmbhard1  ->Fill(gp.m(), weight);
      }
      else if(nbhard == 1){
        hptbhard2 ->Fill(gp.pt(), weight);
        hetabhard2->Fill(gp.eta(), weight);
        hphibhard2->Fill(gp.phi(), weight);
        hmbhard2  ->Fill(gp.m(), weight);
      }
      nbhard++;
    }

    //hard tau
    if(id == 15){
      if(ntauhard == 0){
        hpttauhard1 ->Fill(gp.pt(), weight);
        hetatauhard1->Fill(gp.eta(), weight);
        hphitauhard1->Fill(gp.phi(), weight);
        hmtauhard1  ->Fill(gp.m(), weight);
      }
      else if(ntauhard == 1){
        hpttauhard2 ->Fill(gp.pt(), weight);
        hetatauhard2->Fill(gp.eta(), weight);
        hphitauhard2->Fill(gp.phi(), weight);
        hmtauhard2  ->Fill(gp.m(), weight);
      }
      ntauhard++;
    }
  } // end loop through hard particles

  hnlq->Fill(nlq, weight);
  hnchi->Fill(nchi, weight);
  hnpsi->Fill(npsi, weight);
  hnbhard->Fill(nbhard, weight);
  hntauhard->Fill(ntauhard, weight);

  // Loop through visible tau decay products
  // =======================================

  size_t ntauvis = event.genparticles_visibletaus->size();
  for(size_t i=0; i<ntauvis; i++){
    GenParticle gp = event.genparticles_visibletaus->at(i);

    // visible taus
    if(i==0){
      hpttauvis1 ->Fill(gp.pt(), weight);
      hetatauvis1->Fill(gp.eta(), weight);
      hphitauvis1->Fill(gp.phi(), weight);
      hmtauvis1  ->Fill(gp.m(), weight);
    }
    else if(i==1){
      hpttauvis2 ->Fill(gp.pt(), weight);
      hetatauvis2->Fill(gp.eta(), weight);
      hphitauvis2->Fill(gp.phi(), weight);
      hmtauvis2  ->Fill(gp.m(), weight);
    }
  }
  hntauvis->Fill(ntauvis, weight);

  // Loop through genjets
  // ====================

  size_t njets = event.genjets->size();
  for(size_t i=0; i<njets; i++){
    GenJet j = event.genjets->at(i);

    // hard LQs
    if(i==0){
      hptjet1 ->Fill(j.pt(), weight);
      hetajet1->Fill(j.eta(), weight);
      hphijet1->Fill(j.phi(), weight);
      hmjet1  ->Fill(j.m(), weight);
    }
    else if(i==1){
      hptjet2 ->Fill(j.pt(), weight);
      hetajet2->Fill(j.eta(), weight);
      hphijet2->Fill(j.phi(), weight);
      hmjet2  ->Fill(j.m(), weight);
    }
    else if(i==2){
      hptjet3 ->Fill(j.pt(), weight);
      hetajet3->Fill(j.eta(), weight);
      hphijet3->Fill(j.phi(), weight);
      hmjet3  ->Fill(j.m(), weight);
    }
  }
  hnjets->Fill(njets, weight);

  // dR between jets and closest visible taus
  double dR1min = 999.;
  double dR2min = 999.;
  for(size_t i=0; i<event.genparticles_visibletaus->size(); i++){
    GenParticle gt = event.genparticles_visibletaus->at(i);
    if(njets >= 1){
      GenJet j1 = event.genjets->at(0);
      dR1min = min(deltaR(j1, gt), dR1min);
    }
    if(njets >= 2){
      GenJet j2 = event.genjets->at(1);
      dR2min = min(deltaR(j2, gt), dR2min);
    }
  }
  hdrminj1tauvis->Fill(dR1min, weight);
  hdrminj2tauvis->Fill(dR2min, weight);


  // Event-based variables
  // =====================

  // MET
  hptmet->Fill(event.genmet->pt(), weight);
  hphimet->Fill(event.genmet->phi(), weight);
  hptmetfrominvis->Fill(event.genmet_invis->pt(), weight);
  hphimetfrominvis->Fill(event.genmet_invis->phi(), weight);

  // calculate ST
  double st = 0;
  double stmet = event.genmet->pt();
  double stmetfrominvis = event.genmet_invis->pt();
  int njetsmax = min((size_t)2, event.genjets->size());
  int ntauvismax = min((size_t)2, event.genparticles_visibletaus->size());
  for(int i=0; i<njetsmax; i++) st += event.genjets->at(i).pt();
  for(int i=0; i<ntauvismax; i++) st += event.genparticles_visibletaus->at(i).pt();
  stmet += st;
  stmetfrominvis += st;

  hst->Fill(st, weight);
  hstmet->Fill(stmet, weight);
  hstmetfrominvis->Fill(stmetfrominvis, weight);

  double mj1tauvis1 = 0.;
  if(njets > 0 && ntauvis > 0) mj1tauvis1 = (event.genjets->at(0).p4() + event.genparticles_visibletaus->at(0).p4()).M();
  hmj1tauvis1->Fill(mj1tauvis1, weight);


  hsumweights->Fill(1, weight);
}
