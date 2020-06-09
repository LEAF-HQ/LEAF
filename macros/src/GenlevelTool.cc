#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/GenlevelTool.h"
#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>

using namespace std;

GenlevelTool::GenlevelTool(const Config & cfg) : BaseTool(cfg){

  genjet_id           = PtEtaId(30, 2.5);
  genvistau_id        = PtEtaId(30, 2.5);
  mindr_genjet_tauvis = 0.4;

  cleaner_genjet      .reset(new GenJetCleaner(genjet_id));
  cleaner_genvistau   .reset(new GenVisTauCleaner(genvistau_id));
  cleaner_genjetvistau.reset(new GenJetVisTauCleaner(mindr_genjet_tauvis));


  vector<TString> histtags = {"input", "cleaner", "objectselection", "stmet"};
  // histfolders
  for(const TString s : histtags){
    histmap[s].reset(new GenHists(s));
    histfolders.emplace_back(s);
  }
}
