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


  if(argc != 2) cout << red << "Analyzer requires exactly one argument. Usage: 'Analyzer <CONFIGFILE>.xml'" << reset << endl;
  TString configfilename = (TString)argv[1];

  Config cfg(configfilename);

  while(cfg.idx() < cfg.n_datasets()){

    GenlevelTool GenTool(cfg);






    GenTool.LoopEvents(cfg);
    GenTool.WriteOutput(cfg);



    cfg.increment_idx();
  }
}
