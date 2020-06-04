#include <cmath>
#include <iostream>
#include "include/GenlevelTool.h"
#include "include/PlottingTool.h"
#include "include/constants.h"
#include <TString.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

using namespace std;

int main(){

  // Greet
  cout << "Hello from main()." << endl;

  // Common configs
  bool debug = true;



  for(size_t i=0; i<mass_configurations.size(); i++){
    double MLQ = mass_configurations[i].mlq;
    double MX  = mass_configurations[i].mx;
    double MDM = mass_configurations[i].mdm;

    for(size_t j=0; j<lambdas.size(); j++){
      double lambda = lambdas[j];



      // Actual work happens here
      // ========================
      GenlevelTool GenTool(MLQ, MX, MDM, lambda, debug);
      // looping over events
      // GenTool.LoopEvents();
    }
  }
}
