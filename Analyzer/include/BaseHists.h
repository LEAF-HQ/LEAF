#pragma once

#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/Analyzer/include/Event.h"

class BaseHists {

public:
  // Constructors, destructor
  BaseHists(TString dir_);
  BaseHists(const BaseHists &) = default;
  BaseHists & operator = (const BaseHists &) = default;
  virtual ~BaseHists() = default;

  // Main functions
  virtual void fill(const Event & event){return;};
  void save(TFile* outfile);

  template <typename T, typename... TARGS>
  std::shared_ptr<T> book(TString name, TARGS... args){
    gROOT->mkdir(dir);
    gROOT->cd(dir);
    std::shared_ptr<T> h;
    h.reset(new T(name, std::forward<TARGS>(args)...));
    h->SetDirectory(0);
    h->SetName(name);
    h->Sumw2();
    hists[name] = h;
    histnames.emplace_back(name);
    gROOT->cd();
    return h;
  }

  template<typename F>
  F* hist(const TString& key_){
    F* h(0);
    if(hists.find(key_) != hists.end()) h = static_cast<F*>(hists[key_].get());
    else throw std::runtime_error("BaseHists::hist -- histogram key not found: "+key_);
    return h;
  }


protected:
  std::vector<TString> histnames;
  std::map<TString, std::shared_ptr<TH1>> hists;
  TString dir;

};
