#include <cmath>
#include <iostream>
#include "Plotter/include/PlottingTool.h"
#include "Plotter/include/PlotterConfig.h"
#include <TString.h>

using namespace std;

int main(int argc, char* argv[]){

  // Greet
  cout << endl << endl << green << "+-------------------------------+" << reset << endl;
  cout << green << "|                               |" << reset << endl;
  cout << green << "|     Starting the Plotter      |" << reset << endl;
  cout << green << "|     ====================      |" << reset << endl;
  cout << green << "|                               |" << reset << endl;
  cout << green << "+-------------------------------+" << reset << endl << endl << endl;
  if(argc != 2) cout << red << "--> Plotter requires exactly one argument. Usage: 'Plotter <CONFIGFILE>.xml'" << reset << endl;
  TString configfilename = (TString)argv[1];

  PlotterConfig cfg = PlotterConfig(configfilename);
  PlottingTool Plotter_Recolevel = PlottingTool(cfg);
  Plotter_Recolevel.Plot();





}
