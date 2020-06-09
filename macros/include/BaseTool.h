#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "include/Event.h"
#include "include/GenHists.h"
#include "include/CleaningModules.h"
#include "include/Config.h"

class BaseTool {

public:
  // Constructors, destructor
  BaseTool(const Config & cfg);
  ~BaseTool() = default;

  // Base functions
  void LoopEvents(const Config & cfg);
  void WriteOutput(const Config & cfg);

  // This is called for each event, do the analysis here. In this base class, this is only some default behavior
  virtual bool Process(Event & event){return true;};


protected:
  // For internal use, do not touch
  std::unique_ptr<TFile> simple_file;
  int nevt;
  Event event;
  vector<TString> histfolders;
  map<TString, unique_ptr<GenHists>> histmap;







};
