#pragma once
// #ifdef __CINT__
#include <TString.h>
#include "massconfig.h"
#include <vector>

// using namespace std;


const std::vector<int> lqids = {9000008, 9000009};
const std::vector<int> xids  = {9000006, 9000007};
const std::vector<int> dmids = {9000005};

const double  intlumi      = 35920.;
const TString tag          = "";

const std::vector<massconfig> mass_configurations = {
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
// const std::vector<massconfig> mass_configurations = {
//   //MLQ, MX , MDM following the ordering in massconfig.h
//   {1400, 660, 600}
// };

const std::vector<double> lambdas = {1.0};

// #endif
