#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>
#include "include/Registry.h"

using namespace std;

BaseTool::BaseTool(const Config & cfg){

  // Chain all samples of the same dataset into a TChain
  event_chain.reset(new TChain("AnalysisTree"));
  event_chain->Add(cfg.dataset_filename());

  cout << "added file: " << cfg.dataset_filename() << endl;
  nevt = event_chain->GetEntries();
}


void BaseTool::LoopEvents(const Config & cfg){

  // Print current number of dataset
  cout << endl << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;

  // Initialize event for later looping through chain
  Event* event = 0;
  event_chain->SetBranchAddress("Event", &event);

  // Loop through chain
  for(int i=0; i<event_chain->GetEntries(); ++i) {
    if(i%1000==0){
      cout << green << "    --> Processing event no. (" << i << " / " << nevt << ")" << reset << endl;
    }

    // read the data for i-th event
    event_chain->GetEntry(i);

    // weight must be: target_lumi / dataset_lumi
    event->weight *= cfg.target_lumi() / cfg.dataset_lumi();

    // call Process() for each event, main part of this function!
    Process(*event);
    event->clear();

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

// sumary of necessary functions
void BaseTool::ProcessDataset(const Config & cfg){
  LoopEvents(cfg);
  WriteOutput(cfg);
}
