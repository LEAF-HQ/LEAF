#include <cmath>
#include <iostream>
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/Config.h"
#include <TString.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

using namespace std;



int main(int argc, char* argv[]){

  // Greet
  cout << endl << endl << green << "+-------------------------------+" << reset << endl;
  cout << green << "|                               |" << reset << endl;
  cout << green << "|     Starting the Analyzer     |" << reset << endl;
  cout << green << "|     =====================     |" << reset << endl;
  cout << green << "|                               |" << reset << endl;
  cout << green << "+-------------------------------+" << reset << endl << endl << endl;
  if(argc != 2) cout << red << "--> Analyzer requires exactly one argument. Usage: 'Analyzer <CONFIGFILE>.xml'" << reset << endl;
  TString configfilename = (TString)argv[1];

  Config cfg(configfilename);
  cfg.process_datasets();
}
