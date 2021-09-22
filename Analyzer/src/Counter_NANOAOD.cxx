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


  if(argc != 2 && argc != 3) throw runtime_error("Expected exactly one or exactly 2 argument(2). Usage: Counter_NANOAOD <infilename> [treename, if different from 'Events']");
  string inarg  = argv[1];
  TString treename = "Events";
  if(argc == 3) treename = (TString)argv[2];

  TString infilename = (TString)inarg;
  TFile* infile = TFile::Open(infilename, "READ");
  int n_total = ((TTree*)infile->Get(treename))->GetEntriesFast();
  cout << n_total << endl;
  return 0;
}
