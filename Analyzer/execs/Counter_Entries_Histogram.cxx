#include <iostream>

#include <TFile.h>
#include <TH1F.h>

using namespace std;

int main(int argc, char* argv[]){


  if(argc != 2 && argc != 3) throw runtime_error("Expected exactly one or exactly 2 argument(2). Usage: Counter_Entries <infilename> [treename, if different from 'Events']");
  string inarg  = argv[1];
  TString histname = "h_nevents";
  if(argc == 3) histname = (TString)argv[2];

  TString infilename = (TString)inarg;
  TFile* infile = TFile::Open(infilename, "READ");
  int n_total = ((TH1F*)infile->Get(histname))->GetBinContent(1);
  cout << n_total << endl;
  return 0;
}
