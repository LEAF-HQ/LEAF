#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/Met.h"
#include "Analyzer/include/Particle.h"
#include "Analyzer/include/GenParticle.h"
#include "Analyzer/include/GenJet.h"
#include "Analyzer/include/Jet.h"
#include "Analyzer/include/useful_functions.h"
#include "Analyzer/include/constants.h"

using namespace std;

int main(int argc, char* argv[]){


  if(argc != 2) throw runtime_error("Expected exactly one argument. Usage: Counter_NANOAOD <infilename>");
  string inarg  = argv[1];

  TString infilename = (TString)inarg;
  TFile* infile = TFile::Open(infilename, "READ");
  int n_total = ((TTree*)infile->Get("Events"))->GetEntriesFast();
  cout << n_total << endl;
  return 0;
}
