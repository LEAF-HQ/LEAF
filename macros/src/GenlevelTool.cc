#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/GenlevelTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>

using namespace std;

GenlevelTool::GenlevelTool(const Config & cfg){

  base_path_crosssections = "/work/areimers/LQDM/GENSIM/crosssections/";

  TString infilename = cfg.dataset_filename();
  simple_file.reset(new TFile(infilename, "READ"));


  SetupModules();
  SetupHistograms();
}


// Define all modules and variables needed in GenlevelTool::Process
void GenlevelTool::SetupModules(){

  genjet_id           = PtEtaId(30, 2.5);
  genvistau_id        = PtEtaId(30, 2.5);
  mindr_genjet_tauvis = 0.4;

  cleaner_genjet      .reset(new GenJetCleaner(genjet_id));
  cleaner_genvistau   .reset(new GenVisTauCleaner(genvistau_id));
  cleaner_genjetvistau.reset(new GenJetVisTauCleaner(mindr_genjet_tauvis));

}

// Define all histogram-sets that are later filled in GenlevelTool::Process
void GenlevelTool::SetupHistograms(){


  histfolders = {"input", "cleaner", "objectselection", "stmet"};
  for(const string & s : histfolders){
    string histname = "gen_" + s;
    histmap[s].reset(new GenHists(histname));
  }

}

// Write all output to the outputfile
void GenlevelTool::WriteOutput(const Config & cfg){


// Store filled histograms
// =======================

// make sure outdir exists
TString outfolder = cfg.output_directory();
mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

// create file and store things
TString outfilename = outfolder + cfg.dataset_type() + "__" + cfg.dataset_name() + ".root";
unique_ptr<TFile> outfile;
outfile.reset(new TFile(outfilename, "RECREATE"));
for(const string & x : histfolders) histmap[x]->save(outfile.get());
outfile->Close();
cout << green << "--> Wrote histograms to file: " << outfilename << reset << endl;

}
