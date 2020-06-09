#include "include/GenlevelTool.h"
#include "include/cosmetics.h"
#include "include/constants.h"
#include "include/useful_functions.h"
#include "include/GenHists.h"
#include "include/Event.h"
#include <TH1D.h>
#include <TH2F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TMath.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>
#include "include/classes.h"

using namespace std;
void GenlevelTool::LoopEvents(const Config & cfg){

  // Get the input tree
  // ==================
  cout << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;
  TTreeReader myReaderEvent("AnalysisTree", simple_file.get());
  int nevt = myReaderEvent.GetEntries(true);



  // Set up variables used in 'AnalysisTree', read from Tuples
  // ========================================================
  TTreeReaderValue<Event> ev(myReaderEvent, "Event");


  // Event loop
  // ==========
  int idx = 0;
  while (myReaderEvent.Next()) {
    if(idx%10000==0) cout << green << "    --> Processing event no. (" << idx << " / " << nevt << ")" << reset << endl;
    idx++;
    Event event = *ev;

    // weight must be: target_lumi / dataset_lumi
    event.weight *= cfg.target_lumi() / cfg.dataset_lumi();

    // call event loop, main part of this function!
    Process(event);
    event.clear();
  }
}
