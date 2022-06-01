#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "LEAF/Analyzer/include/Event.h"
#include "LEAF/Analyzer/include/BaseHists.h"
#include "LEAF/Analyzer/include/CleaningModules.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Registry.h"
#include "LEAF/Analyzer/include/Jet.h"
#include <chrono>

class BaseTool {

public:
  // Constructors, destructor
  BaseTool(const Config & cfg);
  virtual ~BaseTool() = default;

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
  std::vector<TString> histfolders;
  std::map<TString, std::unique_ptr<BaseHists>> histmap;
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
  std::cout  << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << std::endl;

  // Initialize event for later looping through chain
  cfg.event_chain->SetBranchAddress("Events", &event);
  cfg.outputtree->Branch("Events", &event);

  // Initialize additional events to read additional inputs. The addresses of the corresponding additional collections will be set to the address of the main event in order to merge them.
  std::vector<E*> additional_events = {};
  for(size_t i=0; i<cfg.m_additional_event_chains.size(); i++){
    E* add_event = new E();
    additional_events.emplace_back(add_event);
  }
  for(size_t i=0; i<cfg.m_additional_event_chains.size(); i++){
    cfg.m_additional_event_chains.at(i)->SetBranchAddress("Events", &additional_events.at(i));
  }

  // for each additional information, check if a matching dataset exists. Store this info to use later when loading the branches
  std::vector<bool> used_ais = {};
  for(size_t i=0; i<cfg.additional_inputs().size(); i++){
    bool used_ai = false;
    for(size_t j=0; j<cfg.additional_inputs().at(i).datasets.size(); j++){
      dataset ds = cfg.additional_inputs().at(i).datasets.at(j);
      if(ds.name == cfg.dataset_name() && ds.year == cfg.dataset_year()) used_ai = true;
    }
    used_ais.emplace_back(used_ai);
  }


  // Loop through chain
  auto start = std::chrono::high_resolution_clock::now();
  Long64_t maxidx = -1;
  if(cfg.nevt_max() < 0) maxidx = cfg.event_chain->GetEntries();
  else if(cfg.nevt_max() > 0) maxidx = std::min((Long64_t)(cfg.nevt_skip() + cfg.nevt_max()), cfg.event_chain->GetEntries());
  else throw std::runtime_error("cfg.nevt_max() returned 0. This should have been caught by an earlier condition in Config.cc. In any case, this is not allowed. Must be > or < 0.");
  std::cout << green << "--> Going to process " << maxidx - cfg.nevt_skip() << " events, skipping the first " << cfg.nevt_skip() << "." << reset << std::endl;

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
        std::cout << green << "    --> Processing event no. (" << i+1-cfg.nevt_skip() << " / " << maxidx - cfg.nevt_skip() << ") [ " << std::fixed << std::setprecision(2) << ((double)(i+1-cfg.nevt_skip()))/((double)(maxidx - cfg.nevt_skip()))*100 << "% ], time left: " << std::setfill('0') << std::setw(2) << hours_left.count() << ":" << std::setfill('0') << std::setw(2) << minutes_left.count() << ":" << std::setfill('0') << std::setw(2) << seconds_left.count() << reset << std::endl;
      }
      else{
        std::cout << green << "    --> Processing event no. (" << i+1-cfg.nevt_skip() << " / " << maxidx - cfg.nevt_skip() << ")" << reset << std::endl;
      }
    }

    // read the data for i-th event, nominal and for all additional inputs
    cfg.event_chain->GetEntry(i);

    // load additional branches, skip event loop if one of them cannot be found
    bool is_additional_input_complete = true;
    for(size_t j=0; j<cfg.m_additional_event_chains.size(); j++){
      int returncode = load_entry_lumiblock_number(cfg.m_additional_event_chains.at(j), event);
      if(returncode < 0) is_additional_input_complete = false;
    }

    if(is_additional_input_complete){

      // set addresses for external collections
      size_t idx_addeventchain = 0;
      for(size_t j=0; j<cfg.additional_inputs().size(); j++){
        if(!used_ais[j]) continue;

        for(size_t k=0; k<cfg.additional_inputs().at(j).collections.size(); k++){
          load_additional_collection(event, additional_events.at(idx_addeventchain), cfg.additional_inputs().at(j).collections.at(k));
        }
        idx_addeventchain++;
      }

      // call Process() for each event, main part of this function!
      bool keep_event = tool.Process();
      // std::cout << "keep event? " << keep_event << std::endl;

      if(keep_event) cfg.outputtree->Fill();
    }
    else{
      throw std::runtime_error("When loading additional inputs to nominal event, a mismatch between lumiblock:eventnumber occurred in the nominal event and at least one of the additional ones. If this affects only a few events, this error should become a warning in the future, but for the moment it is probably better to be made aware of this event by crashing the program.");
    }

    event->reset();
    for(size_t j=0; j<additional_events.size(); j++){
      additional_events.at(j)->reset();
    }
  }

  event->clear();
  delete event;

  for(size_t j=0; j<additional_events.size(); j++){
    additional_events.at(j)->clear();
    delete additional_events.at(j);
  }
}

template<typename E>
void load_additional_collection(E* main_event, E* additional_event, collection c){
  if(c.branchname == "pfcands"){
    *main_event->pfcands = *additional_event->pfcands;
  }
  else if(c.branchname == "triggerobjects"){
    *main_event->triggerobjects = *additional_event->triggerobjects;
  }
  else if(c.branchname == "jets_ak4puppi"){
    *main_event->jets_ak4puppi = *additional_event->jets_ak4puppi;
  }
  else if(c.branchname == "jets_ak8puppi"){
    *main_event->jets_ak8puppi = *additional_event->jets_ak8puppi;
  }
  else if(c.branchname == "genparticles_stable"){
    *main_event->genparticles_stable = *additional_event->genparticles_stable;
  }
  else{
    std::string errormsg = "In Analyzer/include/BaseTool.h: Invalid branchname given when loading additional collections: " + (std::string)c.branchname;
    throw std::runtime_error(errormsg);
  }
}

// specializations to stop compiler from complaining
template <>
void load_additional_collection<Event>(Event* main_event, Event* additional_event, collection c);
template <>
void load_additional_collection<GenEvent>(GenEvent* main_event, GenEvent* additional_event, collection c);

template<typename E>
int load_entry_lumiblock_number(std::shared_ptr<TChain> chain, E* main_event){
  return chain->GetEntryWithIndex(main_event->lumiblock, main_event->number);
}

// specializations to stop compiler from complaining
template<>
int load_entry_lumiblock_number<Event>(std::shared_ptr<TChain> chain, Event* main_event);
template<>
int load_entry_lumiblock_number<GenEvent>(std::shared_ptr<TChain> chain, GenEvent* main_event);


typedef Registry<BaseTool, Config> ToolRegistry;
// mark as unused otherwise generates warnings
#define REGISTER_TOOL(T) namespace { __attribute__ ((unused)) int dummy##T = ::ToolRegistry::register_<T>(#T); }
