#include "include/GenlevelTool.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include <TH1D.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TMath.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

TString lambstr(double lambda){
  ostringstream ss;
  ss << fixed << setprecision(1) << lambda;
  string s(ss.str());
  TString result = s;
  result = result.ReplaceAll(".", "p");
  return result;
}

TString get_samplename(double mlq, double mx, double mdm, double lambda){
  TString result = "MLQ";
  result += mlq;
  result += "_MX";
  result += mx;
  result += "_MDM";
  result += mdm;
  result += "_L";
  result += lambstr(lambda);
  return result;
}

vector<int> get_npids(){
  vector<int> npids = lqids;
  npids.insert(npids.end(), xids.begin(), xids.end());
  npids.insert(npids.end(), dmids.begin(), dmids.end());
  return npids;
}

bool path_exists(const TString &s){
  struct stat buffer;
  return (stat(s, &buffer) == 0);
}

/// distance in phi, with the convention -phi < deltaPhi <= phi
// T and U have to have a 'phi()' method, e.g. Particle, LorentzVector, etc.
template<typename T, typename U>
double deltaPhi(const T & p1, const U & p2){
  double result = fabs(p1.phi() - p2.phi());
  if(result > TMath::Pi()) result = 2 * TMath::Pi() - result;
  return result;
}

/// distance in eta
// T and U have to have a 'eta()' method, e.g. Particle etc.
template<typename T, typename U>
double deltaEta(const T & p1, const U & p2){
  double result = fabs(p1.eta() - p2.eta());
  return result;
}

/// distance in R
// T and U have to have a 'eta()' and 'phi()' method, e.g. Particle etc.
template<typename T, typename U>
double deltaR(const T & p1, const U & p2){
  double de = deltaEta(p1, p2);
  double dp = deltaPhi(p1, p2);
  return sqrt(de * de + dp * dp);
}
