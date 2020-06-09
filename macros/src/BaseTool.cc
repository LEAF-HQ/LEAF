#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>

using namespace std;

BaseTool::BaseTool(const Config & cfg){
  TString infilename = cfg.dataset_filename();
  simple_file.reset(new TFile(infilename, "READ"));
}


void BaseTool::LoopEvents(const Config & cfg){

  // Get the input tree
  cout << endl << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;
  TTreeReader myReaderEvent("AnalysisTree", simple_file.get());
  int nevt = myReaderEvent.GetEntries(true);

  // Set up variables used in 'AnalysisTree', read from Tuples
  TTreeReaderValue<Event> ev(myReaderEvent, "Event");

  // Event loop
  int idx = 0;
  while (myReaderEvent.Next()) {
    if(idx%10000==0){
      cout << green << "    --> Processing event no. (" << idx << " / " << nevt << ")" << reset << endl;
    }
    idx++;
    Event event = *ev;

    // weight must be: target_lumi / dataset_lumi
    event.weight *= cfg.target_lumi() / cfg.dataset_lumi();

    // call event loop, main part of this function!
    Process(event);
    event.clear();
  }
}

// Write all output to the outputfile
void BaseTool::WriteOutput(const Config & cfg){

  // make sure outdir exists
  TString outfolder = cfg.output_directory();
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  // create file and store histograms
  TString outfilename = outfolder + "/" + cfg.dataset_type() + "__" + cfg.dataset_name() + ".root";
  shared_ptr<TFile> outfile;
  outfile.reset(new TFile(outfilename, "RECREATE"));
  for(const TString & x : histfolders){
    histmap[x]->save(outfile.get());
  }
  outfile->Close();
  cout << green << "--> Wrote histograms to file: " << outfilename << reset << endl;

}
