#include <cmath>
#include <iostream>
#include "include/PlottingTool.h"
#include "include/constants.h"
#include <TString.h>

using namespace std;

int main(){

  // Greet
  cout << "Hello from the Plotter." << endl;

  PlottingTool Plotter;
  Plotter.PlotGenlevel(false, true, false);
  // Plotter.PlotGenlevel(true, true, false);     // normalized
  // Plotter.PlotGenlevel(false, false, false);   // lin Y
  // Plotter.PlotGenlevel(true, false, false);    // lin Y normalized
  // Plotter.PlotGenlevel(false, true, true);        // SinglePDF
  // Plotter.PlotGenlevel(true, true, true);         // SinglePDF normalized











}
