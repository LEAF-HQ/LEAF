#include <cmath>
#include <iostream>
#include "include/GenlevelTool.h"
#include "include/PlottingTool.h"
#include "include/constants.h"
#include "include/Config.h"
#include <TString.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

using namespace std;



int main(int argc, char* argv[]){

  // Greet
  cout << "Hello from main()." << endl;


  if(argc != 2) cout << red << "Analyzer requires exactly one argument. Usage: 'Analyser <CONFIGFILE>.xml'" << reset << endl;
  TString configfilename = (TString)argv[1];

  Config cfg(configfilename);
  // cout << "outfilename: " << cfg.output_directory() << endl;
  // string itemvalue = config.get("test");
  // cout << "config.get('test'): " << itemvalue << endl;
  //
  // for(size_t i=0; i<cfg.n_datasets(); i++){
  //   cout << "dataset number: " << i << endl;
  //   cout << "dataset name:   " << cfg.dataset_name(i) << endl;
  //   cout << "dataset infile: " << cfg.dataset_filename(i) << endl;
  // }

  while(cfg.idx() < cfg.n_datasets()){
    // cout << "dataset number: " << cfg.idx() << endl;
    // cout << "dataset name:   " << cfg.dataset_name() << endl;
    // cout << "dataset infile: " << cfg.dataset_filename() << endl;

    GenlevelTool GenTool(cfg);






    GenTool.LoopEvents(cfg);
    // GenTool.WriteOutput(cfg);



    cfg.increment_idx();
  }

  // Common configs
  // bool debug = true;


  cout << "looping through mass configurations" << endl;
  // for(size_t i=0; i<mass_configurations.size(); i++){
  //   double MLQ = mass_configurations[i].mlq;
  //   double MX  = mass_configurations[i].mx;
  //   double MDM = mass_configurations[i].mdm;
  //
  //   for(size_t j=0; j<lambdas.size(); j++){
  //     double lambda = lambdas[j];
  //
  //
  //
  //     // Actual work happens here
  //     // ========================
  //     GenlevelTool GenTool(MLQ, MX, MDM, lambda, debug);
  //     // looping over events
  //     // GenTool.LoopEvents();
  //   }
  // }
}
