#include "LEAF/Analyzer/include/ElectronHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"
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
  helectronpt_rebin2 = book<TH1D>("electronpt_rebin2", ";p_{T}^{e} [GeV]; Events / bin", 50, 0, 50);
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

  helectron1pt = book<TH1D>("electron1pt", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 1500);
  helectron1pt_rebin = book<TH1D>("electron1pt_rebin", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 200);
  helectron1pt_rebin2 = book<TH1D>("electron1pt_rebin2", ";p_{T}^{e 1} [GeV]; Events / bin", 50, 0, 50);
  helectron1eta = book<TH1D>("electron1eta", ";#eta^{e 1};Events / bin", 100, -5., 5.);
  helectron1phi = book<TH1D>("electron1phi", ";#phi^{e 1};Events / bin", 70, -3.5, 3.5);
  helectron1mass = book<TH1D>("electron1mass", ";m^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron1energy = book<TH1D>("electron1energy", ";E^{e 1} [GeV];Events / bin", 50, 0, 1500);
  helectron1pfiso = book<TH1D>("electron1pfiso", ";Iso_{PF}^{e 1};Events / bin", 100, 0, 1);
  helectron1dxy = book<TH1D>("electron1dxy", ";e 1 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1dz = book<TH1D>("electron1dz", ";e 1 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1d = book<TH1D>("electron1d", ";e 1 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron1gendrmin = book<TH1D>("electron1gendrmin", ";#DeltaR(e 1, closest gen e);Events / bin", 60, 0, 3);

  helectron2pt = book<TH1D>("electron2pt", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 1500);
  helectron2pt_rebin = book<TH1D>("electron2pt_rebin", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 200);
  helectron2pt_rebin2 = book<TH1D>("electron2pt_rebin2", ";p_{T}^{e 2} [GeV]; Events / bin", 50, 0, 50);
  helectron2eta = book<TH1D>("electron2eta", ";#eta^{e 2};Events / bin", 100, -5., 5.);
  helectron2phi = book<TH1D>("electron2phi", ";#phi^{e 2};Events / bin", 70, -3.5, 3.5);
  helectron2mass = book<TH1D>("electron2mass", ";m^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron2energy = book<TH1D>("electron2energy", ";E^{e 2} [GeV];Events / bin", 50, 0, 1500);
  helectron2pfiso = book<TH1D>("electron2pfiso", ";Iso_{PF}^{e 2};Events / bin", 100, 0, 1);
  helectron2dxy = book<TH1D>("electron2dxy", ";e 2 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2dz = book<TH1D>("electron2dz", ";e 2 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2d = book<TH1D>("electron2d", ";e 2 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron2gendrmin = book<TH1D>("electron2gendrmin", ";#DeltaR(e 2, closest gen e);Events / bin", 60, 0, 3);

  helectron3pt = book<TH1D>("electron3pt", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 1500);
  helectron3pt_rebin = book<TH1D>("electron3pt_rebin", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 200);
  helectron3pt_rebin2 = book<TH1D>("electron3pt_rebin2", ";p_{T}^{e 3} [GeV]; Events / bin", 50, 0, 50);
  helectron3eta = book<TH1D>("electron3eta", ";#eta^{e 3};Events / bin", 100, -5., 5.);
  helectron3phi = book<TH1D>("electron3phi", ";#phi^{e 3};Events / bin", 70, -3.5, 3.5);
  helectron3mass = book<TH1D>("electron3mass", ";m^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron3energy = book<TH1D>("electron3energy", ";E^{e 3} [GeV];Events / bin", 50, 0, 1500);
  helectron3pfiso = book<TH1D>("electron3pfiso", ";Iso_{PF}^{e 3};Events / bin", 100, 0, 1);
  helectron3dxy = book<TH1D>("electron3dxy", ";e 3 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3dz = book<TH1D>("electron3dz", ";e 3 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3d = book<TH1D>("electron3d", ";e 3 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron3gendrmin = book<TH1D>("electron3gendrmin", ";#DeltaR(e 3, closest gen e);Events / bin", 60, 0, 3);

  helectron4pt = book<TH1D>("electron4pt", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 1500);
  helectron4pt_rebin = book<TH1D>("electron4pt_rebin", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 200);
  helectron4pt_rebin2 = book<TH1D>("electron4pt_rebin2", ";p_{T}^{e 4} [GeV]; Events / bin", 50, 0, 50);
  helectron4eta = book<TH1D>("electron4eta", ";#eta^{e 4};Events / bin", 100, -5., 5.);
  helectron4phi = book<TH1D>("electron4phi", ";#phi^{e 4};Events / bin", 70, -3.5, 3.5);
  helectron4mass = book<TH1D>("electron4mass", ";m^{e 4} [GeV];Events / bin", 50, 0, 1500);
  helectron4energy = book<TH1D>("electron4energy", ";E^{e 4} [GeV];Events / bin", 50, 0, 1500);
  helectron4pfiso = book<TH1D>("electron4pfiso", ";Iso_{PF}^{e 4};Events / bin", 100, 0, 1);
  helectron4dxy = book<TH1D>("electron4dxy", ";e 4 d_{xy} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4dz = book<TH1D>("electron4dz", ";e 4 d_{z} wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4d = book<TH1D>("electron4d", ";e 4 d wrt. PV [cm];Events / bin", 250, 0, 0.5);
  helectron4gendrmin = book<TH1D>("electron4gendrmin", ";#DeltaR(e 4, closest gen e);Events / bin", 60, 0, 3);

}

void ElectronHists::fill(const RecoEvent & event){
  double weight = event.weight;



  // Loop through jets
  // ====================

  size_t nelectrons = event.electrons->size();

  for(size_t i=0; i<nelectrons; i++){
    Electron e = event.electrons->at(i);
    float gendr_min = 99999.;
    for(const auto & gp : *event.genparticles_all){
      if(abs(gp.pdgid()) != 11) continue;
      if(!gp.isLastCopy()) continue;
      float dr = deltaR(e, gp);
      if(dr < gendr_min){
        gendr_min = dr;
      }
    }


    helectronpt->Fill(e.pt(), weight);
    helectronpt_rebin->Fill(e.pt(), weight);
    helectronpt_rebin2->Fill(e.pt(), weight);
    helectroneta->Fill(e.eta(), weight);
    helectronphi->Fill(e.phi(), weight);
    helectronmass->Fill(e.m(), weight);
    helectronenergy->Fill(e.e(), weight);
    helectronpfiso->Fill(e.iso_rel_03(), weight);
    helectrondxy->Fill(e.dxy(), weight);
    helectrondz->Fill(e.dz(), weight);
    helectrond->Fill(e.d0(), weight);
    helectron_dxy_vs_dz->Fill(e.dxy(), e.dz(), weight);
    helectrongendrmin->Fill(gendr_min, weight);


    if(i==0){
      helectron1pt->Fill(e.pt(), weight);
      helectron1pt_rebin->Fill(e.pt(), weight);
      helectron1pt_rebin2->Fill(e.pt(), weight);
      helectron1eta->Fill(e.eta(), weight);
      helectron1phi->Fill(e.phi(), weight);
      helectron1mass->Fill(e.m(), weight);
      helectron1energy->Fill(e.e(), weight);
      helectron1pfiso->Fill(e.iso_rel_03(), weight);
      helectron1dxy->Fill(e.dxy(), weight);
      helectron1dz->Fill(e.dz(), weight);
      helectron1d->Fill(e.d0(), weight);
      helectron1gendrmin->Fill(gendr_min, weight);
    }
    else if(i==1){
      helectron2pt->Fill(e.pt(), weight);
      helectron2pt_rebin->Fill(e.pt(), weight);
      helectron2pt_rebin2->Fill(e.pt(), weight);
      helectron2eta->Fill(e.eta(), weight);
      helectron2phi->Fill(e.phi(), weight);
      helectron2mass->Fill(e.m(), weight);
      helectron2energy->Fill(e.e(), weight);
      helectron2pfiso->Fill(e.iso_rel_03(), weight);
      helectron2dxy->Fill(e.dxy(), weight);
      helectron2dz->Fill(e.dz(), weight);
      helectron2d->Fill(e.d0(), weight);
      helectron2gendrmin->Fill(gendr_min, weight);
    }
    else if(i==2){
      helectron3pt->Fill(e.pt(), weight);
      helectron3pt_rebin->Fill(e.pt(), weight);
      helectron3pt_rebin2->Fill(e.pt(), weight);
      helectron3eta->Fill(e.eta(), weight);
      helectron3phi->Fill(e.phi(), weight);
      helectron3mass->Fill(e.m(), weight);
      helectron3energy->Fill(e.e(), weight);
      helectron3pfiso->Fill(e.iso_rel_03(), weight);
      helectron3dxy->Fill(e.dxy(), weight);
      helectron3dz->Fill(e.dz(), weight);
      helectron3d->Fill(e.d0(), weight);
      helectron3gendrmin->Fill(gendr_min, weight);
    }
    else if(i==3){
      helectron4pt->Fill(e.pt(), weight);
      helectron4pt_rebin->Fill(e.pt(), weight);
      helectron4pt_rebin2->Fill(e.pt(), weight);
      helectron4eta->Fill(e.eta(), weight);
      helectron4phi->Fill(e.phi(), weight);
      helectron4mass->Fill(e.m(), weight);
      helectron4energy->Fill(e.e(), weight);
      helectron4pfiso->Fill(e.iso_rel_03(), weight);
      helectron4dxy->Fill(e.dxy(), weight);
      helectron4dz->Fill(e.dz(), weight);
      helectron4d->Fill(e.d0(), weight);
      helectron4gendrmin->Fill(gendr_min, weight);
    }
  }
  hnelectrons->Fill(nelectrons, weight);
}
