// Taken from https://github.com/UHH2/UHH2/blob/RunII_102X_v2/scripts/crab/countNumberEvents.C

#include <iostream>
#include <iomanip>      // std::setprecision

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

using namespace std;

int main(int argc, char * argv[]){

  if (argc != 2) throw runtime_error("Requires exactly one argument: filename");
  TString filename = argv[1];

  TFile* f = TFile::Open(filename, "READ");
  TTree* tree = (TTree*) f->Get("AnalysisTree");
  TTreeReader reader(tree);
  TTreeReaderValue<double> eweight(reader, "weight");
  double sum = tree->GetEntriesFast();
  double sum_weights = 0.; // MUST be double otherwise loses precision
  while (reader.Next()) {
    sum_weights += *eweight;
  }

  delete tree;
  f->Close();
  delete f;
  cout << setprecision(9) << sum << " " << sum_weights << endl;
  return 0;
}
