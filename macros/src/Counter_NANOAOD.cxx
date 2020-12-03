#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#include "include/RecoEvent.h"
#include "include/Met.h"
#include "include/Particle.h"
#include "include/GenParticle.h"
#include "include/GenJet.h"
#include "include/Jet.h"
#include "include/useful_functions.h"
#include "include/constants.h"

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
