#pragma once

#include <TString.h>
#include "massconfig.h"

using namespace std;

const double  intlumi      = 35920.;
const TString tag          = "";

const vector<massconfig> mass_configurations = {
  //MLQ, MX , MDM following the ordering in massconfig.h
  {600,  220, 200},
  {700,  275, 250},
  {800,  330, 300},
  {900,  385, 350},
  {1000, 440, 400},
  {1100, 495, 450},
  {1200, 550, 500},
  {1300, 605, 550},
  {1400, 660, 600},
  {1500, 715, 650},
  {1600, 770, 700},
  {1700, 825, 750},
  {1800, 880, 800},
  {1900, 935, 850},
  {2000, 990, 900}
};
// const vector<massconfig> mass_configurations = {
//   //MLQ, MX , MDM following the ordering in massconfig.h
//   {600,  220, 200}
// };

const vector<double> lambdas = {1.0};
