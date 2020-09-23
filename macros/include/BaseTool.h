#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "include/Event.h"
#include "include/GenHists.h"
#include "include/CleaningModules.h"
#include "include/Config.h"
#include "include/Registry.h"
#include "include/Jet.h"

class BaseTool {

public:
  // Constructors, destructor
  BaseTool(const Config & cfg);
  ~BaseTool() = default;

  // Base functions
  template <class M, class E>
  void LoopEvents(const Config & cfg, E* event, M & tool);
  void WriteHistograms(const Config & cfg);
  virtual void ProcessDataset(const Config & cfg){LoopEvents<BaseTool, Event>(cfg, event, *this);};

  // This is called for each event, do the analysis here. In this base class, this is only some default behavior
  virtual bool Process() = 0;


protected:
  // For internal use, do not touch
  template<typename F> void book_HistFolder(const TString&, F*);
  template<typename F=BaseHists> F* HistFolder(const TString&);
  vector<TString> histfolders;
  map<TString, unique_ptr<BaseHists>> histmap;
  Event* event;
};



template<typename F>
void BaseTool::book_HistFolder(const TString& dirname, F* f_ptr){

  if(histmap.find(dirname) != histmap.end()) throw std::runtime_error("BaseTool::book_HistFolder -- already existing dirname: "+dirname);
  else {
    histmap[dirname].reset(f_ptr);
    histfolders.emplace_back(dirname);
  }
  return;
}

template<typename F>
F* BaseTool::HistFolder(const TString& dirname){

  F* f(0);

  if(histmap.find(dirname) != histmap.end()) f = static_cast<F*>(histmap[dirname].get());
  else throw std::runtime_error("BaseTool::HistFolder -- folder dirname not found: "+dirname);

  if(!f) throw std::runtime_error("BaseTool::HistFolder -- null pointer to folder: "+dirname);

  return f;
}



template <class M, class E>
void BaseTool::LoopEvents(const Config & cfg, E* event, M & tool){

  // Print current number of dataset
  cout  << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;

  // Initialize event for later looping through chain
  cfg.event_chain->SetBranchAddress("Event", &event);
  cfg.outputtree->Branch("Event", &event);

  // E outevent;
  // // outevent.reset();
  // cfg.outputtree->Branch("Event", &outevent);

  // Loop through chain
  for(int i=0; i<cfg.event_chain->GetEntries(); ++i) {
    if(i%1000==0){
      cout << green << "    --> Processing event no. (" << i << " / " << cfg.nevt << ")" << reset << endl;
    }

    // read the data for i-th event
    cfg.event_chain->GetEntry(i);

    // weight must be: target_lumi / dataset_lumi
    event->weight *= (double)cfg.target_lumi() / (double)cfg.dataset_lumi();

    // call Process() for each event, main part of this function!
    bool keep_event = tool.Process();
    // cout << "keep event? " << keep_event << endl;

    // outevent = *event;
    if(keep_event) cfg.outputtree->Fill();
    event->reset();
  }

  event->clear();
  delete event;
}


typedef Registry<BaseTool, Config> ToolRegistry;
// mark as unused otherwise generates warnings
#define REGISTER_TOOL(T) namespace { __attribute__ ((unused)) int dummy##T = ::ToolRegistry::register_<T>(#T); }
