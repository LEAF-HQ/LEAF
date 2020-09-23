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
#include "include/JetHists.h"
#include "include/MuonHists.h"
#include "include/ElectronHists.h"
#include "include/TauHists.h"

using namespace std;

class PreselectionTool : public BaseTool {

public:
  // Constructors, destructor
  PreselectionTool(const Config & cfg);
  ~PreselectionTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<PreselectionTool, RecoEvent>(cfg, event, *this);};
  virtual bool Process() override;
  void book_histograms(vector<TString>);
  void fill_histograms(TString);


private:
  RecoEvent* event;

  // Modules used in the analysis
  JetId      jet_id;
  // GenParticleId genvistau_id;
  // double        mindr_genjet_tauvis;
  //
  unique_ptr<JetCleaner>       cleaner_jet;
  // unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  // unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;
};



PreselectionTool::PreselectionTool(const Config & cfg) : BaseTool(cfg){

  event = new RecoEvent();
  event->reset();

  jet_id           = PtEtaId(30, 2.5);
  // genvistau_id        = PtEtaId(30, 2.5);
  // mindr_genjet_tauvis = 0.4;
  //
  cleaner_jet      .reset(new JetCleaner(jet_id));
  // cleaner_genvistau   .reset(new GenVisTauCleaner(genvistau_id));
  // cleaner_genjetvistau.reset(new GenJetVisTauCleaner(mindr_genjet_tauvis));


  // histfolders
  vector<TString> histtags = {"input", "cleaner"};
  book_histograms(histtags);
}




bool PreselectionTool::Process(){

  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  sort_by_pt<GenParticle>(*event->genparticles_hard);
  sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  sort_by_pt<GenParticle>(*event->genparticles_final);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets);
  sort_by_pt<Muon>(*event->muons);
  sort_by_pt<Electron>(*event->electrons);
  sort_by_pt<Tau>(*event->taus);
  fill_histograms("input");

  cleaner_jet->process(*event);
  fill_histograms("cleaner");




  return true;
}











void PreselectionTool::book_histograms(vector<TString> tags){
  for(const TString & tag : tags){
    TString mytag = tag+"_General";
    book_HistFolder(mytag, new PreselectionHists(mytag));
    mytag = tag+"_Jets";
    book_HistFolder(mytag, new JetHists(mytag));
    mytag = tag+"_Muons";
    book_HistFolder(mytag, new MuonHists(mytag));
    mytag = tag+"_Electrons";
    book_HistFolder(mytag, new ElectronHists(mytag));
    mytag = tag+"_Taus";
    book_HistFolder(mytag, new TauHists(mytag));
  }
}

void PreselectionTool::fill_histograms(TString tag){
  TString mytag = tag+"_General";
  HistFolder<PreselectionHists>(mytag)->fill(*event);
  mytag = tag+"_Jets";
  HistFolder<JetHists>(mytag)->fill(*event);
  mytag = tag+"_Muons";
  HistFolder<MuonHists>(mytag)->fill(*event);
  mytag = tag+"_Electrons";
  HistFolder<ElectronHists>(mytag)->fill(*event);
  mytag = tag+"_Taus";
  HistFolder<TauHists>(mytag)->fill(*event);
}




REGISTER_TOOL(PreselectionTool)
