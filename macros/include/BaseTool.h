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
  void LoopEvents(const Config & cfg);
  void WriteOutput(const Config & cfg);
  void ProcessDataset(const Config & cfg);

  // This is called for each event, do the analysis here. In this base class, this is only some default behavior
  virtual bool Process(Event & event){return true;};


protected:
  // For internal use, do not touch
  unique_ptr<TChain> event_chain;
  int nevt;
  vector<TString> histfolders;
  map<TString, unique_ptr<GenHists>> histmap;
  TTree* outputtree;
  shared_ptr<TFile> outfile;
};


typedef Registry<BaseTool, Config> ToolRegistry;
// mark as unused otherwise generates warnings
#define REGISTER_TOOL(T) namespace { __attribute__ ((unused)) int dummy##T = ::ToolRegistry::register_<T>(#T); }
