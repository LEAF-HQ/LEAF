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

  shared_ptr<TH1F> hnlq, hnx, hndm, hnjets, hnbhard, hntauhard, hntauvis, hmlq1, hmlq2, hmx, hmdm1, hmdm2, hptlq1, hptlq2, hptx, hptdm1, hptdm2, hetalq1, hetalq2, hetax, hetadm1, hetadm2, hphilq1, hphilq2, hphix, hphidm1, hphidm2, hptjet1, hptjet2, hptjet3, hptbhard1, hptbhard2, hpttauhard1, hpttauhard2, hpttauvis1, hpttauvis2, hetajet1, hetajet2, hetajet3, hetabhard1, hetabhard2, hetatauhard1, hetatauhard2, hetatauvis1, hetatauvis2, hphijet1, hphijet2, hphijet3, hphibhard1, hphibhard2, hphitauhard1, hphitauhard2, hphitauvis1, hphitauvis2, hmjet1, hmjet2, hmjet3, hmbhard1, hmbhard2, hmtauhard1, hmtauhard2, hmtauvis1, hmtauvis2, hdrminj1tauvis, hdrminj2tauvis, hptmet, hphimet, hptmetfrominvis, hphimetfrominvis, hst, hstmet, hstmetfrominvis, hmj1tauvis1, hsumweights;

};
