#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>

using namespace std;

class GenHists {

public:
  // Constructors, destructor
  GenHists(TString dir_);
  GenHists(const GenHists &) = default;
  GenHists & operator = (const GenHists &) = default;
  ~GenHists() = default;

  // Main functions
  void fill(const Event & event);
  void save(TFile* outfile);
  template <typename T, typename... TARGS>
  shared_ptr<TH1F> book(TString name, TARGS... args){
    gROOT->mkdir(dir);
    gROOT->cd(dir);
    shared_ptr<TH1F> h;
    h.reset(new T(name, std::forward<TARGS>(args)...));
    h->SetName(name);
    h->Sumw2();
    hists[name] = h;
    gROOT->cd();
    return h;
  }


protected:
  TString dir;
  map<TString, shared_ptr<TH1>> hists;

  shared_ptr<TH1F> nlq, nx, ndm, njets, nb, nbcut, nbcut50, ntau, ntaucut, ntaucut50, ntaucut_vis, ntaucut50_vis, mlq1, mlq2, mx, mdm1, mdm2, ptlq1, ptlq2, ptx, ptdm1, ptdm2, etalq1, etalq2, etax, etadm1, etadm2, philq1, philq2, phix, phidm1, phidm2, ptjet1, ptjet2, ptjet3, ptb1, ptb2, pttau1, pttau2, pttauvis1, pttauvis2, etajet1, etajet2, etajet3, etab1, etab2, etatau1, etatau2, etatauvis1, etatauvis2, phijet1, phijet2, phijet3, phib1, phib2, phitau1, phitau2, phitauvis1, phitauvis2, mjet1, mjet2, mjet3, mb1, mb2, mtau1, mtau2, mtauvis1, mtauvis2, ptmet, phimet, st, stmet;

};
