#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/Event.h"

using namespace std;

class BaseHists {

public:
  // Constructors, destructor
  BaseHists(TString dir_);
  BaseHists(const BaseHists &) = default;
  BaseHists & operator = (const BaseHists &) = default;
  ~BaseHists() = default;

  // Main functions
  virtual void fill(const Event & event){return;};
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

};
