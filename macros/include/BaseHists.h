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
  shared_ptr<T> book(TString name, TARGS... args){
    gROOT->mkdir(dir);
    gROOT->cd(dir);
    shared_ptr<T> h;
    h.reset(new T(name, std::forward<TARGS>(args)...));
    h->SetDirectory(0);
    h->SetName(name);
    h->Sumw2();
    hists[name] = h;
    histnames.emplace_back(name);
    gROOT->cd();
    return h;
  }


protected:
  vector<TString> histnames;
  map<TString, shared_ptr<TH1>> hists;
  TString dir;

};
