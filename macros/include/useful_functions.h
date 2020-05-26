#pragma once

#include <TString.h>
#include <TH1F.h>

using namespace std;

TString lambstr(double lambda);
TString get_samplename(double mlq, double mx, double mdm, double lambda);

const std::string red("\x1b[0;31m");
const std::string green("\x1b[0;32m");
const std::string yellow("\x1b[0;33m");
const std::string cyan("\x1b[0;36m");
const std::string magenta("\x1b[0;35m");
const std::string reset("\x1b[0m");

map<TString, unique_ptr<TH1F>> setup_histmap();
