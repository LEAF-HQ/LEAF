#include "Analyzer/include/ElectronHists.h"
// #include "Analyzer/include/cosmetics.h"
#include "Analyzer/include/constants.h"
#include "Analyzer/include/useful_functions.h"
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

ElectronHists::ElectronHists(TString dir_) : BaseHists(dir_){

  hnelectrons = book<TH1D>("nelectrons", ";N_{e}; Events / bin", 11, -0.5, 10.5);
  helectronpt = book<TH1D>("electronpt", ";p_{T}^{e} [GeV]; Events / bin", 50, 0, 1500);
  helectronpt_rebin = book<TH1D>("electronpt_rebin", ";p_{T}^{e} [GeV]; Events / bin", 50, 0, 200);
  helectroneta = book<TH1D>("electroneta", ";#eta^{e};Events / bin", 100, -5., 5.);
  helectronphi = book<TH1D>("electronphi", ";#phi^{e};Events / bin", 70, -3.5, 3.5);
  helectronmass = book<TH1D>("electronmass", ";m^{e} [GeV];Events / bin", 50, 0, 1500);
  helectronenergy = book<TH1D>("electronenergy", ";E^{e} [GeV];Events / bin", 50, 0, 1500);
  helectronpfiso = book<TH1D>("electronpfiso", ";Iso_{PF}^{e};Events / bin", 100, 0, 1);
  helectrondxy = book<TH1D>("electrondxy", ";e d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectrondz = book<TH1D>("electrondz", ";e d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectrond = book<TH1D>("electrond", ";e d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron_dxy_vs_dz = book<TH2D>("electron_dxy_vs_dz", ";e d_{xy} wrt. PV [cm];e d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  helectrongendrmin = book<TH1D>("electrongendrmin", ";#DeltaR(e, closest gen e);Events / bin", 60, 0, 3);

  helectronclosestorigin = book<TH1D>("electronclosestorigin", ";closest e -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  helectronclosestd = book<TH1D>("electronclosestd", ";closest e d [cm]; Events / bin", 250, 0, 0.5);

  hnelectronsfromtau = book<TH1D>("nelectronsfromtau", ";N_{e from #tau}; Events / bin", 11, -0.5, 10.5);
  helectronfromtaupt = book<TH1D>("electronfromtaupt", ";p_{T}^{e from #tau} [GeV]; Events / bin", 50, 0, 1500);
  helectronfromtaupt_rebin = book<TH1D>("electronfromtaupt_rebin", ";p_{T}^{e from #tau} [GeV]; Events / bin", 50, 0, 200);
  helectronfromtaueta = book<TH1D>("electronfromtaueta", ";#eta^{e from #tau};Events / bin", 100, -5., 5.);
  helectronfromtauphi = book<TH1D>("electronfromtauphi", ";#phi^{e from #tau};Events / bin", 70, -3.5, 3.5);
  helectronfromtaumass = book<TH1D>("electronfromtaumass", ";m^{e from #tau} [GeV];Events / bin", 50, 0, 1500);
  helectronfromtauenergy = book<TH1D>("electronfromtauenergy", ";E^{e from #tau} [GeV];Events / bin", 50, 0, 1500);
  helectronfromtaupfiso = book<TH1D>("electronfromtaupfiso", ";Iso_{PF}^{e from #tau};Events / bin", 100, 0, 1);
  helectronfromtaudxy = book<TH1D>("electronfromtaudxy", ";e from #tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronfromtaudz = book<TH1D>("electronfromtaudz", ";e from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronfromtaud = book<TH1D>("electronfromtaud", ";e from #tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronfromtau_dxy_vs_dz = book<TH2D>("electronfromtau_dxy_vs_dz", ";e from #tau d_{xy} wrt. PV [cm];e from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  helectronfromtaugendrmin = book<TH1D>("electronfromtaugendrmin", ";#DeltaR(e from #tau, closest gen e);Events / bin", 60, 0, 3);

  hnelectronsnotfromtau = book<TH1D>("nelectronsnotfromtau", ";N_{e not from #tau}; Events / bin", 11, -0.5, 10.5);
  helectronnotfromtaupt = book<TH1D>("electronnotfromtaupt", ";p_{T}^{e not from #tau} [GeV]; Events / bin", 50, 0, 1500);
  helectronnotfromtaupt_rebin = book<TH1D>("electronnotfromtaupt_rebin", ";p_{T}^{e not from #tau} [GeV]; Events / bin", 50, 0, 200);
  helectronnotfromtaueta = book<TH1D>("electronnotfromtaueta", ";#eta^{e not from #tau};Events / bin", 100, -5., 5.);
  helectronnotfromtauphi = book<TH1D>("electronnotfromtauphi", ";#phi^{e not from #tau};Events / bin", 70, -3.5, 3.5);
  helectronnotfromtaumass = book<TH1D>("electronnotfromtaumass", ";m^{e not from #tau} [GeV];Events / bin", 50, 0, 1500);
  helectronnotfromtauenergy = book<TH1D>("electronnotfromtauenergy", ";E^{e not from #tau} [GeV];Events / bin", 50, 0, 1500);
  helectronnotfromtaupfiso = book<TH1D>("electronnotfromtaupfiso", ";Iso_{PF}^{e not from #tau};Events / bin", 100, 0, 1);
  helectronnotfromtaudxy = book<TH1D>("electronnotfromtaudxy", ";e not from #tau d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronnotfromtaudz = book<TH1D>("electronnotfromtaudz", ";e not from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronnotfromtaud = book<TH1D>("electronnotfromtaud", ";e not from #tau d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectronnotfromtau_dxy_vs_dz = book<TH2D>("electronnotfromtau_dxy_vs_dz", ";e not from #tau d_{xy} wrt. PV [cm];e not from #tau d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5, 250, 0, 0.5);
  helectronnotfromtaugendrmin = book<TH1D>("electronnotfromtaugendrmin", ";#DeltaR(e not from #tau, closest gen e);Events / bin", 60, 0, 3);

  helectrongenorigin = book<TH1D>("electrongenorigin", ";e -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);
  hnelectronsgenfromtau = book<TH1D>("nelectronsgenfromtau", ";Number of e from #tau decay; Events / bin", 11, -0.5, 10.5);
  hnelectronsgenfromhadron = book<TH1D>("nelectronsgenfromhadron", ";Number of e from hadron decay; Events / bin", 11, -0.5, 10.5);
  hnelectronsgenfromelse = book<TH1D>("nelectronsgenfromelse", ";Number of e from other decay; Events / bin", 11, -0.5, 10.5);
  hnelectronsgenunmatched = book<TH1D>("nelectronsgenunmatched", ";Number of unmatched e; Events / bin", 11, -0.5, 10.5);

  helectron1pt = book<TH1D>("electron1pt", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 1500);
  helectron1pt_rebin = book<TH1D>("electron1pt_rebin", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 200);
  helectron1eta = book<TH1D>("electron1eta", ";#eta^{e 1};Events / bin", 100, -5., 5.);
  helectron1phi = book<TH1D>("electron1phi", ";#phi^{e 1};Events / bin", 70, -3.5, 3.5);
  helectron1mass = book<TH1D>("electron1mass", ";m^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron1energy = book<TH1D>("electron1energy", ";E^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron1pfiso = book<TH1D>("electron1pfiso", ";Iso_{PF}^{e 1};Events / bin", 100, 0, 1);
  helectron1dxy = book<TH1D>("electron1dxy", ";e 1 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1dz = book<TH1D>("electron1dz", ";e 1 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1d = book<TH1D>("electron1d", ";e 1 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1gendrmin = book<TH1D>("electron1gendrmin", ";#DeltaR(e 1, closest gen e);Events / bin", 60, 0, 3);
  helectron1genorigin = book<TH1D>("electron1genorigin", ";e 1 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);

  helectron2pt = book<TH1D>("electron2pt", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 1500);
  helectron2pt_rebin = book<TH1D>("electron2pt_rebin", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 200);
  helectron2eta = book<TH1D>("electron2eta", ";#eta^{e 2};Events / bin", 100, -5., 5.);
  helectron2phi = book<TH1D>("electron2phi", ";#phi^{e 2};Events / bin", 70, -3.5, 3.5);
  helectron2mass = book<TH1D>("electron2mass", ";m^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron2energy = book<TH1D>("electron2energy", ";E^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron2pfiso = book<TH1D>("electron2pfiso", ";Iso_{PF}^{e 2};Events / bin", 100, 0, 1);
  helectron2dxy = book<TH1D>("electron2dxy", ";e 2 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2dz = book<TH1D>("electron2dz", ";e 2 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2d = book<TH1D>("electron2d", ";e 2 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2gendrmin = book<TH1D>("electron2gendrmin", ";#DeltaR(e 2, closest gen e);Events / bin", 60, 0, 3);
  helectron2genorigin = book<TH1D>("electron2genorigin", ";e 2 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);

  helectron3pt = book<TH1D>("electron3pt", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 1500);
  helectron3pt_rebin = book<TH1D>("electron3pt_rebin", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 200);
  helectron3eta = book<TH1D>("electron3eta", ";#eta^{e 3};Events / bin", 100, -5., 5.);
  helectron3phi = book<TH1D>("electron3phi", ";#phi^{e 3};Events / bin", 70, -3.5, 3.5);
  helectron3mass = book<TH1D>("electron3mass", ";m^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron3energy = book<TH1D>("electron3energy", ";E^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron3pfiso = book<TH1D>("electron3pfiso", ";Iso_{PF}^{e 3};Events / bin", 100, 0, 1);
  helectron3dxy = book<TH1D>("electron3dxy", ";e 3 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3dz = book<TH1D>("electron3dz", ";e 3 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3d = book<TH1D>("electron3d", ";e 3 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3gendrmin = book<TH1D>("electron3gendrmin", ";#DeltaR(e 2, closest gen e);Events / bin", 60, 0, 3);
  helectron3genorigin = book<TH1D>("electron3genorigin", ";e 3 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);

  helectron4pt = book<TH1D>("electron4pt", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 1500);
  helectron4pt_rebin = book<TH1D>("electron4pt_rebin", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 200);
  helectron4eta = book<TH1D>("electron4eta", ";#eta^{e 4};Events / bin", 100, -5., 5.);
  helectron4phi = book<TH1D>("electron4phi", ";#phi^{e 4};Events / bin", 70, -3.5, 3.5);
  helectron4mass = book<TH1D>("electron4mass", ";m^{e 4} [GeV];Events / bin", 50, 0, 1500);
  helectron4energy = book<TH1D>("electron4energy", ";E^{e 4} [GeV];Events / bin", 50, 0, 1500);
  helectron4pfiso = book<TH1D>("electron4pfiso", ";Iso_{PF}^{e 4};Events / bin", 100, 0, 1);
  helectron4dxy = book<TH1D>("electron4dxy", ";e 4 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4dz = book<TH1D>("electron4dz", ";e 4 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4d = book<TH1D>("electron4d", ";e 4 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4gendrmin = book<TH1D>("electron4gendrmin", ";#DeltaR(e 3, closest gen e);Events / bin", 60, 0, 3);
  helectron4genorigin = book<TH1D>("electron4genorigin", ";e 4 -- 1: from hard #tau, 2: from hadron, 0: else, -1: unmatched; Events / bin", 4, -1.5, 2.5);

}

void ElectronHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t nelectrons = event.electrons->size();
  size_t nfromtau = 0;
  size_t nfromhadron = 0;
  size_t nfromelse = 0;
  size_t nunmatched = 0;

  double d_max = 999999.;
  int gen_origin_closest = -1;
  for(size_t i=0; i<nelectrons; i++){
    Electron e = event.electrons->at(i);
    float gendr_min = 99999.;
    int gen_origin = -1;
    for(const auto & gp : *event.genparticles_all){
      if(abs(gp.pdgid()) != 11) continue;
      if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;
      float dr = deltaR(e, gp);
      if(dr < gendr_min){
        gendr_min = dr;
        if(gendr_min < 0.1){ // these are updated only for better matches than the previous closest match
          if(gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct)) gen_origin = 1;
          else if(gp.get_statusflag(GenParticle::isDirectHadronDecayProduct)) gen_origin = 2;
          else gen_origin = 0;
        }
      }
    }
    if(gen_origin == 1) nfromtau++;
    else if (gen_origin == 2) nfromhadron++;
    else if (gen_origin == 0) nfromelse++;
    else if (gen_origin == -1) nunmatched++;

    float d_pv = sqrt(e.dxy()*e.dxy() + e.dz()*e.dz());
    if(d_pv < d_max){
      d_max = d_pv;
      gen_origin_closest = gen_origin;
    }

    helectronpt->Fill(e.pt(), weight);
    helectronpt_rebin->Fill(e.pt(), weight);
    helectroneta->Fill(e.eta(), weight);
    helectronphi->Fill(e.phi(), weight);
    helectronmass->Fill(e.m(), weight);
    helectronenergy->Fill(e.e(), weight);
    helectronpfiso->Fill(e.iso_rel_03(), weight);
    helectrondxy->Fill(e.dxy(), weight);
    helectrondz->Fill(e.dz(), weight);
    helectrond->Fill(d_pv, weight);
    helectron_dxy_vs_dz->Fill(e.dxy(), e.dz(), weight);
    helectrongendrmin->Fill(gendr_min, weight);
    helectrongenorigin->Fill(gen_origin, weight);



    if(gen_origin == 1){
      helectronfromtaupt->Fill(e.pt(), weight);
      helectronfromtaupt_rebin->Fill(e.pt(), weight);
      helectronfromtaueta->Fill(e.eta(), weight);
      helectronfromtauphi->Fill(e.phi(), weight);
      helectronfromtaumass->Fill(e.m(), weight);
      helectronfromtauenergy->Fill(e.e(), weight);
      helectronfromtaupfiso->Fill(e.iso_rel_03(), weight);
      helectronfromtaudxy->Fill(e.dxy(), weight);
      helectronfromtaudz->Fill(e.dz(), weight);
      helectronfromtaud->Fill(d_pv, weight);
      helectronfromtau_dxy_vs_dz->Fill(e.dxy(), e.dz(), weight);
      helectronfromtaugendrmin->Fill(gendr_min, weight);
    }
    else{
      helectronnotfromtaupt->Fill(e.pt(), weight);
      helectronnotfromtaupt_rebin->Fill(e.pt(), weight);
      helectronnotfromtaueta->Fill(e.eta(), weight);
      helectronnotfromtauphi->Fill(e.phi(), weight);
      helectronnotfromtaumass->Fill(e.m(), weight);
      helectronnotfromtauenergy->Fill(e.e(), weight);
      helectronnotfromtaupfiso->Fill(e.iso_rel_03(), weight);
      helectronnotfromtaudxy->Fill(e.dxy(), weight);
      helectronnotfromtaudz->Fill(e.dz(), weight);
      helectronnotfromtaud->Fill(d_pv, weight);
      helectronnotfromtau_dxy_vs_dz->Fill(e.dxy(), e.dz(), weight);
      helectronnotfromtaugendrmin->Fill(gendr_min, weight);
    }

    if(i==0){
      helectron1pt->Fill(e.pt(), weight);
      helectron1pt_rebin->Fill(e.pt(), weight);
      helectron1eta->Fill(e.eta(), weight);
      helectron1phi->Fill(e.phi(), weight);
      helectron1mass->Fill(e.m(), weight);
      helectron1energy->Fill(e.e(), weight);
      helectron1pfiso->Fill(e.iso_rel_03(), weight);
      helectron1dxy->Fill(e.dxy(), weight);
      helectron1dz->Fill(e.dz(), weight);
      helectron1d->Fill(d_pv, weight);
      helectron1gendrmin->Fill(gendr_min, weight);
      helectron1genorigin->Fill(gen_origin, weight);
    }
    else if(i==1){
      helectron2pt->Fill(e.pt(), weight);
      helectron2pt_rebin->Fill(e.pt(), weight);
      helectron2eta->Fill(e.eta(), weight);
      helectron2phi->Fill(e.phi(), weight);
      helectron2mass->Fill(e.m(), weight);
      helectron2energy->Fill(e.e(), weight);
      helectron2pfiso->Fill(e.iso_rel_03(), weight);
      helectron2dxy->Fill(e.dxy(), weight);
      helectron2dz->Fill(e.dz(), weight);
      helectron2d->Fill(d_pv, weight);
      helectron2gendrmin->Fill(gendr_min, weight);
      helectron2genorigin->Fill(gen_origin, weight);
    }
    else if(i==2){
      helectron3pt->Fill(e.pt(), weight);
      helectron3pt_rebin->Fill(e.pt(), weight);
      helectron3eta->Fill(e.eta(), weight);
      helectron3phi->Fill(e.phi(), weight);
      helectron3mass->Fill(e.m(), weight);
      helectron3energy->Fill(e.e(), weight);
      helectron3pfiso->Fill(e.iso_rel_03(), weight);
      helectron3dxy->Fill(e.dxy(), weight);
      helectron3dz->Fill(e.dz(), weight);
      helectron3d->Fill(d_pv, weight);
      helectron3gendrmin->Fill(gendr_min, weight);
      helectron3genorigin->Fill(gen_origin, weight);
    }
    else if(i==3){
      helectron4pt->Fill(e.pt(), weight);
      helectron4pt_rebin->Fill(e.pt(), weight);
      helectron4eta->Fill(e.eta(), weight);
      helectron4phi->Fill(e.phi(), weight);
      helectron4mass->Fill(e.m(), weight);
      helectron4energy->Fill(e.e(), weight);
      helectron4pfiso->Fill(e.iso_rel_03(), weight);
      helectron4dxy->Fill(e.dxy(), weight);
      helectron4dz->Fill(e.dz(), weight);
      helectron4d->Fill(d_pv, weight);
      helectron4gendrmin->Fill(gendr_min, weight);
      helectron4genorigin->Fill(gen_origin, weight);
    }
  }
  hnelectrons->Fill(nelectrons, weight);
  hnelectronsfromtau->Fill(nfromtau, weight);
  hnelectronsnotfromtau->Fill(nelectrons - nfromtau, weight);
  hnelectronsgenfromtau->Fill(nfromtau, weight);
  hnelectronsgenfromhadron->Fill(nfromhadron, weight);
  hnelectronsgenfromelse->Fill(nfromelse, weight);
  hnelectronsgenunmatched->Fill(nunmatched, weight);

  helectronclosestorigin->Fill(gen_origin_closest, weight);
  helectronclosestd->Fill(d_max, weight);
}
