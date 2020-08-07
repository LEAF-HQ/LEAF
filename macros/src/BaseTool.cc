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
  for(size_t i=0; i<cfg.dataset_infilenames().size(); i++){
    event_chain->Add(cfg.dataset_infilenames().at(i));
  }
  nevt = event_chain->GetEntries();

  // make sure outdir exists
  TString outfolder = cfg.output_directory();
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  // create output file and Tree(s)
  TString outfilename = outfolder + "/" + cfg.dataset_type() + "__" + cfg.dataset_name() + ".root";
  outfile.reset(new TFile(outfilename, "RECREATE"));

  outputtree = new TTree("AnalysisTree", "Events that passed the selection so far");
  default_event = new Event();
}


void BaseTool::LoopEvents(const Config & cfg, Event* event){

  // Print current number of dataset
  cout << endl << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;

  // Initialize event for later looping through chain
  // Event *event = new Event();
  event_chain->SetBranchAddress("Event", &event);
  outputtree->Branch("Event", &event);

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
    bool keep_event = Process(*event);
    if(keep_event) outputtree->Fill();
    event->reset();
  }

  event->clear();
  delete event;
}

// Write all output to the outputfile
void BaseTool::WriteOutput(const Config & cfg){

  // store histograms and tree(s) to output file
  for(const TString & x : histfolders){
    histmap[x]->save(outfile.get());
  }

  outputtree->Write();
  outfile->Close();
  cout << green << "--> Wrote histograms to file: " << outfile->GetName() << reset << endl;
}

// sumary of necessary functions
void BaseTool::ProcessDataset(const Config & cfg){
  LoopEvents(cfg, default_event);
  WriteOutput(cfg);
}
