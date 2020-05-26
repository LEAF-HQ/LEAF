#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "../include/GenlevelTool.h"
#include "../include/useful_functions.h"

using namespace std;

GenlevelTool::GenlevelTool(double MLQ_, double MX_, double MDM_, double lambda_, bool debug_) : MLQ(MLQ_), MX(MX_), MDM(MDM_), lambda(lambda_), debug(debug_){

  base_path_gensim        = "/work/areimers/LQDM/GENSIM/simple_files/";
  base_path_analysisfiles = "/work/areimers/LQDM/GENSIM/analysisfiles/";
  // base_path_plots         = "/work/areimers/LQDM/GENSIM/plots/";
  base_path_crosssections = "/work/areimers/LQDM/GENSIM/crosssections/";
  base_path_out           = "/work/areimers/LQDM/GENSIM/";

  TString simple_file_name = base_path_gensim + "LQDM_" + get_samplename(MLQ, MX, MDM, lambda) + "_GENSIM_simple.root";
  simple_file.reset(new TFile(simple_file_name, "READ"));


  SetupModules();
  SetupHistograms();
}


// Define all modules and variables needed in GenlevelTool::Process
void GenlevelTool::SetupModules(){

  genjet_id = PtEtaId(20, 2.5);
  cleaner_genjet.reset(new GenJetCleaner(genjet_id));

}

// Define all histogram-sets that are later filled in GenlevelTool::Process
void GenlevelTool::SetupHistograms(){

  vector<string> histfolders = {"input", "st"};

  for(const string & s : histfolders){
    string histname = "gen_" + s;
    histmap[s].reset(new GenHists(histname));
  }

}
