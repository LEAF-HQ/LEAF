#include "../include/GenlevelTool.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include "../include/useful_functions.h"
#include "../include/GenHists.h"
#include "../include/Event.h"
#include <TH1D.h>
#include <TH2F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TMath.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;
void GenlevelTool::LoopEvents(){


  cout << endl << endl << green << "--> Now processing file with configuration (MLQ, MX, MDM) = (" << MLQ << ", " << MX << ", " << MDM << ") and lambda = " << lambda << reset << endl;
  TString lambdastr = lambstr(lambda);

  TTreeReader myReaderEvent("event", simple_file.get());
  TTreeReader myReaderJet  ("jet_raw", simple_file.get());
  int nevt = myReaderEvent.GetEntries(true);


  // Set up variables used in 'Event', read from simple_files
  // ========================================================

  TTreeReaderValue<int>       id_jet(myReaderJet,     "event_id");
  TTreeReaderValue<double>    ptjet(myReaderJet,      "pt");
  TTreeReaderValue<double>    etajet(myReaderJet,     "eta");
  TTreeReaderValue<double>    phijet(myReaderJet,     "phi");
  TTreeReaderValue<double>    mjet(myReaderJet,       "mass");

  TTreeReaderValue<int>    id(myReaderEvent,          "event_id");
  TTreeReaderValue<int>    njets(myReaderEvent,        "njet");
  TTreeReaderValue<int>    nb(myReaderEvent,           "nbgen");
  TTreeReaderValue<int>    nbcut(myReaderEvent,        "nbcut");
  TTreeReaderValue<int>    nbcut50(myReaderEvent,      "nbcut50");
  TTreeReaderValue<int>    nlq(myReaderEvent,          "nlq");
  TTreeReaderValue<int>    nx(myReaderEvent,           "nx");
  TTreeReaderValue<int>    ndm(myReaderEvent,          "ndm");
  TTreeReaderValue<int>    ntau(myReaderEvent,         "ntau");
  TTreeReaderValue<int>    ntaucut(myReaderEvent,      "ntaucut");
  TTreeReaderValue<int>    ntaucut50(myReaderEvent,    "ntaucut50");
  TTreeReaderValue<int>    ntaucut_vis(myReaderEvent,  "ntaucut_vis");
  TTreeReaderValue<int>    ntaucut50_vis(myReaderEvent,"ntaucut50_vis");
  TTreeReaderValue<double> evweight(myReaderEvent,     "weight");
  TTreeReaderValue<double> mlq1(myReaderEvent,         "lq1_mass");
  TTreeReaderValue<double> mlq2(myReaderEvent,         "lq2_mass");
  TTreeReaderValue<double> mx(myReaderEvent,           "x_mass");
  TTreeReaderValue<double> mdm1(myReaderEvent,         "dm1_mass");
  TTreeReaderValue<double> mdm2(myReaderEvent,         "dm2_mass");
  TTreeReaderValue<double> ptlq1(myReaderEvent,        "lq1_pt");
  TTreeReaderValue<double> ptlq2(myReaderEvent,        "lq2_pt");
  TTreeReaderValue<double> ptx(myReaderEvent,          "x_pt");
  TTreeReaderValue<double> ptdm1(myReaderEvent,        "dm1_pt");
  TTreeReaderValue<double> ptdm2(myReaderEvent,        "dm2_pt");
  TTreeReaderValue<double> etalq1(myReaderEvent,       "lq1_eta");
  TTreeReaderValue<double> etalq2(myReaderEvent,       "lq2_eta");
  TTreeReaderValue<double> etax(myReaderEvent,         "x_eta");
  TTreeReaderValue<double> etadm1(myReaderEvent,       "dm1_eta");
  TTreeReaderValue<double> etadm2(myReaderEvent,       "dm2_eta");
  TTreeReaderValue<double> philq1(myReaderEvent,       "lq1_phi");
  TTreeReaderValue<double> philq2(myReaderEvent,       "lq2_phi");
  TTreeReaderValue<double> phix(myReaderEvent,         "x_phi");
  TTreeReaderValue<double> phidm1(myReaderEvent,       "dm1_phi");
  TTreeReaderValue<double> phidm2(myReaderEvent,       "dm2_phi");
  TTreeReaderValue<double> ptjet1(myReaderEvent,       "jet1_pt");
  TTreeReaderValue<double> ptjet2(myReaderEvent,       "jet2_pt");
  TTreeReaderValue<double> ptjet3(myReaderEvent,       "jet3_pt");
  TTreeReaderValue<double> ptb1(myReaderEvent,         "b1_pt");
  TTreeReaderValue<double> ptb2(myReaderEvent,         "b2_pt");
  TTreeReaderValue<double> pttau1(myReaderEvent,       "tau1_pt");
  TTreeReaderValue<double> pttau2(myReaderEvent,       "tau2_pt");
  TTreeReaderValue<double> pttauvis1(myReaderEvent,    "tau1_ptvis");
  TTreeReaderValue<double> pttauvis2(myReaderEvent,    "tau2_ptvis");
  TTreeReaderValue<double> mjet1(myReaderEvent,        "jet1_mass");
  TTreeReaderValue<double> mjet2(myReaderEvent,        "jet2_mass");
  TTreeReaderValue<double> mjet3(myReaderEvent,        "jet3_mass");
  TTreeReaderValue<double> mb1(myReaderEvent,          "b1_mass");
  TTreeReaderValue<double> mb2(myReaderEvent,          "b2_mass");
  TTreeReaderValue<double> mtau1(myReaderEvent,        "tau1_mass");
  TTreeReaderValue<double> mtau2(myReaderEvent,        "tau2_mass");
  TTreeReaderValue<double> mtauvis1(myReaderEvent,     "tau1_massvis");
  TTreeReaderValue<double> mtauvis2(myReaderEvent,     "tau2_massvis");
  TTreeReaderValue<double> etajet1(myReaderEvent,      "jet1_eta");
  TTreeReaderValue<double> etajet2(myReaderEvent,      "jet2_eta");
  TTreeReaderValue<double> etajet3(myReaderEvent,      "jet3_eta");
  TTreeReaderValue<double> etab1(myReaderEvent,        "b1_eta");
  TTreeReaderValue<double> etab2(myReaderEvent,        "b2_eta");
  TTreeReaderValue<double> etatau1(myReaderEvent,      "tau1_eta");
  TTreeReaderValue<double> etatau2(myReaderEvent,      "tau2_eta");
  TTreeReaderValue<double> etatauvis1(myReaderEvent,   "tau1_etavis");
  TTreeReaderValue<double> etatauvis2(myReaderEvent,   "tau2_etavis");
  TTreeReaderValue<double> phijet1(myReaderEvent,      "jet1_phi");
  TTreeReaderValue<double> phijet2(myReaderEvent,      "jet2_phi");
  TTreeReaderValue<double> phijet3(myReaderEvent,      "jet3_phi");
  TTreeReaderValue<double> phib1(myReaderEvent,        "b1_phi");
  TTreeReaderValue<double> phib2(myReaderEvent,        "b2_phi");
  TTreeReaderValue<double> phitau1(myReaderEvent,      "tau1_phi");
  TTreeReaderValue<double> phitau2(myReaderEvent,      "tau2_phi");
  TTreeReaderValue<double> phitauvis1(myReaderEvent,   "tau1_phivis");
  TTreeReaderValue<double> phitauvis2(myReaderEvent,   "tau2_phivis");
  TTreeReaderValue<double> ptmet(myReaderEvent,        "met_pt");
  TTreeReaderValue<double> phimet(myReaderEvent,       "met_phi");
  TTreeReaderValue<double> st(myReaderEvent,           "st");
  TTreeReaderValue<double> stmet(myReaderEvent,        "st_met");


  // Get cross section TGraph from file
  // ==================================

  TString crosssectionfilename = base_path_crosssections + "LQCrosssections.root";
  unique_ptr<TFile> crosssectionfile;
  crosssectionfile.reset(new TFile(crosssectionfilename, "READ"));
  TString crosssectiongraphname = "ScalarLQ_Pair_nlo_L" + lambdastr;
  TGraphAsymmErrors* crosssections = (TGraphAsymmErrors*)crosssectionfile->Get(crosssectiongraphname);
  double xsec = crosssections->Eval(MLQ);


  // Event loop
  // ==========

  int idx = 0;
  GenJet first_jet_for_next;
  bool fill_jet_next = false;
  while (myReaderEvent.Next()) {
    if(debug && (idx%10000==0)) cout << green << "    --> Processing event no. (" << idx << " / " << nevt << ")" << reset << endl;
    idx++;

    Event event;
    event.id = *id;
    event.njets = *njets;
    event.nb = *nb;
    event.nbcut = *nbcut;
    event.nbcut50 = *nbcut50;
    event.nlq = *nlq;
    event.nx = *nx;
    event.ndm = *ndm;
    event.ntau = *ntau;
    event.ntaucut = *ntaucut;
    event.ntaucut50 = *ntaucut50;
    event.ntaucut_vis = *ntaucut_vis;
    event.ntaucut50_vis = *ntaucut50_vis;
    event.mlq1 = *mlq1;
    event.mlq2 = *mlq2;
    event.mx = *mx;
    event.mdm1 = *mdm1;
    event.mdm2 = *mdm2;
    event.ptlq1 = *ptlq1;
    event.ptlq2 = *ptlq2;
    event.ptx = *ptx;
    event.ptdm1 = *ptdm1;
    event.ptdm2 = *ptdm2;
    event.etalq1 = *etalq1;
    event.etalq2 = *etalq2;
    event.etax = *etax;
    event.etadm1 = *etadm1;
    event.etadm2 = *etadm2;
    event.philq1 = *philq1;
    event.philq2 = *philq2;
    event.phix = *phix;
    event.phidm1 = *phidm1;
    event.phidm2 = *phidm2;
    event.ptjet1 = *ptjet1;
    event.ptjet2 = *ptjet2;
    event.ptjet3 = *ptjet3;
    event.ptb1 = *ptb1;
    event.ptb2 = *ptb2;
    event.pttau1 = *pttau1;
    event.pttau2 = *pttau2;
    event.pttauvis1 = *pttauvis1;
    event.pttauvis2 = *pttauvis2;
    event.mjet1 = *mjet1;
    event.mjet2 = *mjet2;
    event.mjet3 = *mjet3;
    event.mb1 = *mb1;
    event.mb2 = *mb2;
    event.mtau1 = *mtau1;
    event.mtau2 = *mtau2;
    event.mtauvis1 = *mtauvis1;
    event.mtauvis2 = *mtauvis2;
    event.etajet1 = *etajet1;
    event.etajet2 = *etajet2;
    event.etajet3 = *etajet3;
    event.etab1 = *etab1;
    event.etab2 = *etab2;
    event.etatau1 = *etatau1;
    event.etatau2 = *etatau2;
    event.etatauvis1 = *etatauvis1;
    event.etatauvis2 = *etatauvis2;
    event.phijet1 = *phijet1;
    event.phijet2 = *phijet2;
    event.phijet3 = *phijet3;
    event.phib1 = *phib1;
    event.phib2 = *phib2;
    event.phitau1 = *phitau1;
    event.phitau2 = *phitau2;
    event.phitauvis1 = *phitauvis1;
    event.phitauvis2 = *phitauvis2;
    event.ptmet = *ptmet;
    event.phimet = *phimet;
    event.st = *st;
    event.stmet = *stmet;

    //fill jets
    if(fill_jet_next && (event.id == first_jet_for_next.evtid())){
      event.genjets->emplace_back(first_jet_for_next);
    }

    while (myReaderJet.Next()) {
      GenJet j;
      j.set_evtid(*id_jet);
      j.set_p4(*ptjet, *etajet, *phijet, *mjet);
      if(j.evtid() == event.id){
        event.genjets->emplace_back(j);
        fill_jet_next = false;
      }
      else{
        first_jet_for_next = j;
        fill_jet_next = true;
        break;
      }
    }

    // set eventweight --  generator weight * xsec / nevt --> normalization corresponds to L_int = 1/pb
    event.weight = *evweight;
    event.weight *= xsec / double(nevt);

    // call event loop, main part of this function!
    Process(event);
    // event.clear();
  }


  // Store filled histograms
  // =======================

  TString outfolder = base_path_analysisfiles;
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  TString outfilename = outfolder + "LQDM_" + get_samplename(MLQ, MX, MDM, lambda) + ".root";
  unique_ptr<TFile> outfile;
  outfile.reset(new TFile(outfilename, "RECREATE"));
  for(const auto & x : histmap) x.second->save(outfile.get());
  outfile->Close();
  cout << green << "--> Wrote histograms to file: " << outfilename << reset << endl;
}
