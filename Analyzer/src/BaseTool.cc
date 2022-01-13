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
