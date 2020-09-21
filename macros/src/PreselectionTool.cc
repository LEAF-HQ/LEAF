#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>
#include "include/Registry.h"
#include "include/RecoEvent.h"
#include "include/PreselectionHists.h"

using namespace std;

class PreselectionTool : public BaseTool {

public:
  // Constructors, destructor
  PreselectionTool(const Config & cfg);
  ~PreselectionTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<PreselectionTool, RecoEvent>(cfg, event, *this);};
  virtual bool Process() override;


private:
  RecoEvent* event;

  // Modules used in the analysis
  // GenJetId      genjet_id;
  // GenParticleId genvistau_id;
  // double        mindr_genjet_tauvis;
  //
  // unique_ptr<GenJetCleaner>       cleaner_genjet;
  // unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  // unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;
};






PreselectionTool::PreselectionTool(const Config & cfg) : BaseTool(cfg){

  event = new RecoEvent();
  event->reset();

  // genjet_id           = PtEtaId(30, 2.5);
  // genvistau_id        = PtEtaId(30, 2.5);
  // mindr_genjet_tauvis = 0.4;
  //
  // cleaner_genjet      .reset(new GenJetCleaner(genjet_id));
  // cleaner_genvistau   .reset(new GenVisTauCleaner(genvistau_id));
  // cleaner_genjetvistau.reset(new GenJetVisTauCleaner(mindr_genjet_tauvis));


  // histfolders
  vector<TString> histtags = {"input"};
  for(const TString s : histtags){
    histmap[s].reset(new PreselectionHists(s));
    histfolders.emplace_back(s);
  }
}




bool PreselectionTool::Process(){

  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  // sort_by_pt<GenParticle>(*event->genparticles_hard);
  // sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  // sort_by_pt<GenParticle>(*event->genparticles_final);
  // sort_by_pt<GenJet>(*event->genjets);
  histmap["input"]->fill(*event);
  // cout << "njets: " << event->jets->size() << endl;




  return true;
}




REGISTER_TOOL(PreselectionTool)
