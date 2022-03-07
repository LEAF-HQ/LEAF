#include <iostream>
#include <bitset>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/Met.h"
#include "LEAF/Analyzer/include/Particle.h"
#include "LEAF/Analyzer/include/GenParticle.h"
#include "LEAF/Analyzer/include/GenJet.h"
#include "LEAF/Analyzer/include/Jet.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"

using namespace std;

int main(int argc, char* argv[]){


  if(argc != 2 && argc != 3) throw runtime_error("Expected exactly one or exactly 2 argument(2). Usage: Counter_Entries <infilename> [treename, if different from 'Events']");
  string inarg  = argv[1];
  TString treename = "Events";
  if(argc == 3) treename = (TString)argv[2];

  TString infilename = (TString)inarg;
  TFile* infile = TFile::Open(infilename, "READ");
  int n_total = ((TTree*)infile->Get(treename))->GetEntriesFast();
  cout << n_total << endl;
  return 0;
}
