#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "Analyzer/include/Event.h"
#include "Analyzer/include/BaseHists.h"
#include "Analyzer/include/CleaningModules.h"
#include "Analyzer/include/Config.h"
#include "Analyzer/include/Registry.h"
#include "Analyzer/include/Jet.h"
#include <chrono>

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
  cfg.event_chain->SetBranchAddress("Events", &event);
  cfg.outputtree->Branch("Events", &event);

  // Loop through chain
  auto start = std::chrono::high_resolution_clock::now();
  Long64_t maxidx = -1;
  if(cfg.nevt_max() < 0) maxidx = cfg.event_chain->GetEntries();
  else if(cfg.nevt_max() > 0) maxidx = min((Long64_t)(cfg.nevt_skip() + cfg.nevt_max()), cfg.event_chain->GetEntries());
  else throw runtime_error("cfg.nevt_max() returned 0. This should have been caught by an earlier condition in Config.cc. In any case, this is not allowed. Must be > or < 0.");
  cout << green << "--> Going to process " << maxidx - cfg.nevt_skip() << " events, skipping the first " << cfg.nevt_skip() << "." << reset << endl;

  for(Long64_t i=cfg.nevt_skip(); i<maxidx; ++i) {
    if(i%1000==0 || i == maxidx-1){
      auto now = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
      std::chrono::milliseconds sec_left = std::chrono::milliseconds(999999999999);
      if(i > cfg.nevt_skip()){
        std::chrono::milliseconds msec_left = std::chrono::milliseconds((int)(((double)duration.count()) / ((double)i-cfg.nevt_skip()) * ((double)(maxidx - cfg.nevt_skip())) - ((double)duration.count())));
        auto seconds_left = std::chrono::duration_cast<std::chrono::seconds>(msec_left);
        auto minutes_left = std::chrono::duration_cast<std::chrono::minutes>(seconds_left);
        seconds_left -= std::chrono::duration_cast<std::chrono::seconds>(minutes_left);
        auto hours_left = std::chrono::duration_cast<std::chrono::hours>(minutes_left);
        minutes_left -= std::chrono::duration_cast<std::chrono::minutes>(hours_left);
        cout << green << "    --> Processing event no. (" << i+1-cfg.nevt_skip() << " / " << maxidx - cfg.nevt_skip() << ") [ " << fixed << setprecision(2) << ((double)(i+1-cfg.nevt_skip()))/((double)(maxidx - cfg.nevt_skip()))*100 << "% ], time left: " << std::setfill('0') << std::setw(2) << hours_left.count() << ":" << std::setfill('0') << std::setw(2) << minutes_left.count() << ":" << std::setfill('0') << std::setw(2) << seconds_left.count() << reset << endl;
      }
      else{
        cout << green << "    --> Processing event no. (" << i+1-cfg.nevt_skip() << " / " << maxidx - cfg.nevt_skip() << ")" << reset << endl;
      }
    }

    // read the data for i-th event
    cfg.event_chain->GetEntry(i);

    // weight must be: target_lumi / dataset_lumi or 1 for data
    // if(cfg.dataset_type() == "DATA") event->weight = 1.;
    // else event->weight *= (double)cfg.target_lumi() / (double)cfg.dataset_lumi();

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
