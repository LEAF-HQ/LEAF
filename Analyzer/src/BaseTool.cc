#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

#include "LEAF/Analyzer/include/BaseTool.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include <sys/stat.h>
#include "LEAF/Analyzer/include/Registry.h"

using namespace std;

BaseTool::BaseTool(const Config & cfg){
  event = new Event();
}

// Write all output to the outputfile
void BaseTool::WriteHistograms(const Config & cfg){

  // store histograms and tree(s) to output file
  for(const TString & x : histfolders){
    HistFolder(x)->save(cfg.outfile.get());
  }
}


template <>
void load_additional_collection<Event>(Event* main_event, Event* additional_event, collection c){
  std::string errormsg = "Using the base class 'Event' when trying to load additional collections. This event class has only one member, which is a weight. Please instead use a derived event class like 'RecoEvent'";
  throw std::runtime_error(errormsg);
}
template <>
void load_additional_collection<GenEvent>(GenEvent* main_event, GenEvent* additional_event, collection c){
  std::string errormsg = "Using the base class 'GenEvent' when trying to load additional collections. Please instead use an event class like 'RecoEvent' that has support for additional collections";
  throw std::runtime_error(errormsg);
}

template<>
void load_entry_lumiblock_number<Event>(shared_ptr<TChain> chain, Event* main_event){
  std::string errormsg = "Using the base class 'Event' when trying to load entry of additional collections. This event class has only one member, which is a weight. Please instead use a derived event class like 'RecoEvent'";
  throw std::runtime_error(errormsg);
}
template<>
void load_entry_lumiblock_number<GenEvent>(shared_ptr<TChain> chain, GenEvent* main_event){
  std::string errormsg = "Using the base class 'GenEvent' when trying to load entry of additional collections. Please instead use an event class like 'RecoEvent' that has support for additional collections";
  throw std::runtime_error(errormsg);
}
