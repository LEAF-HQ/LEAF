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
  vector<TString> histfolders;
  map<TString, unique_ptr<GenHists>> histmap;
  Event* event;
};



template <class M, class E>
void BaseTool::LoopEvents(const Config & cfg, E* event, M & tool){

  // Print current number of dataset
  cout  << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;

  // Initialize event for later looping through chain
  cfg.event_chain->SetBranchAddress("Event", &event);
  cfg.outputtree->Branch("Event", &event);

  // Loop through chain
  for(int i=0; i<cfg.event_chain->GetEntries(); ++i) {
    if(i%1000==0){
      cout << green << "    --> Processing event no. (" << i << " / " << cfg.nevt << ")" << reset << endl;
    }

    // read the data for i-th event
    cfg.event_chain->GetEntry(i);

    // weight must be: target_lumi / dataset_lumi
    event->weight *= cfg.target_lumi() / cfg.dataset_lumi();

    // call Process() for each event, main part of this function!
    bool keep_event = tool.Process();
    if(keep_event) cfg.outputtree->Fill();
    event->reset();
  }

  event->clear();
  delete event;
}


typedef Registry<BaseTool, Config> ToolRegistry;
// mark as unused otherwise generates warnings
#define REGISTER_TOOL(T) namespace { __attribute__ ((unused)) int dummy##T = ::ToolRegistry::register_<T>(#T); }
