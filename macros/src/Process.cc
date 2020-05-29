#include "../include/GenlevelTool.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include "../include/useful_functions.h"
#include "../include/GenHists.h"
#include "../include/Event.h"
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

using namespace std;

void GenlevelTool::Process(Event & event){
  // cout << "+++ NEW EVENT" << endl;
  // cout << "genmet: " << event.genmet->pt() << endl;


  histmap["input"]->fill(event);
  //
  // cout << "n GenJets: " << event.genjets->size() << endl;
  // cleaner_genjet->process(event);
  // cout << "n genjets cleaned: " << event.genjets->size() << endl;
  // // histmap["cleaner"]->fill(event);
  //
  //
  // if(event.st < 100) return;
  //
  // histmap["st"]->fill(event);


}
