#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

#include "Analyzer/include/BaseTool.h"
#include "Analyzer/include/useful_functions.h"
#include <sys/stat.h>
#include "Analyzer/include/Registry.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/PreselectionHists.h"
#include "Analyzer/include/JetHists.h"
#include "Analyzer/include/MuonHists.h"
#include "Analyzer/include/ElectronHists.h"
#include "Analyzer/include/TauHists.h"
#include "Analyzer/include/JetIds.h"
#include "Analyzer/include/MuonIds.h"
#include "Analyzer/include/ElectronIds.h"
#include "Analyzer/include/TauIds.h"

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
  unique_ptr<JetCleaner> cleaner_jet;
  unique_ptr<JetCleaner> cleaner_jettauoverlap;
  unique_ptr<MuonCleaner> cleaner_muon;
  unique_ptr<ElectronCleaner> cleaner_electron;
  unique_ptr<TauCleaner> cleaner_tau;
};



PreselectionTool::PreselectionTool(const Config & cfg) : BaseTool(cfg){

  event = new RecoEvent();
  event->reset();

  MultiID<Muon> muon_id = {PtEtaId(20, 2.4), MuonID(Muon::IDCutBasedLoose)};
  MultiID<Electron> electron_id = {PtEtaId(20, 2.4), ElectronID(Electron::IDCutBasedLoose)};
  MultiID<Tau> tau_id = {PtEtaId(20, 2.4), TauID(Tau::DeepTauVsJetMedium), TauID(Tau::DeepTauVsEleVVVLoose), TauID(Tau::DeepTauVsMuVLoose)};
  // MultiID<Jet> jet_id = {PtEtaId(20, 2.5), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT), JetTauOverlapID(0.4)};
  MultiID<Jet> jet_id = {PtEtaId(20, 2.5), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  MultiID<Jet> jet_overlapid = {JetTauOverlapID(0.4), JetLeptonOverlapID(0.4)};

  cleaner_muon.reset(new MuonCleaner(muon_id));
  cleaner_electron.reset(new ElectronCleaner(electron_id));
  cleaner_tau.reset(new TauCleaner(tau_id));
  cleaner_jet.reset(new JetCleaner(jet_id));
  cleaner_jettauoverlap.reset(new JetCleaner(jet_overlapid));


  // histfolders
  vector<TString> histtags = {"input", "cleaner", "jettaucleaner"};
  book_histograms(histtags);
}




bool PreselectionTool::Process(){

  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  // sort_by_pt<GenParticle>(*event->genparticles_hard);
  sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  // sort_by_pt<GenParticle>(*event->genparticles_final);
  sort_by_pt<GenParticle>(*event->genparticles_all);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets);
  sort_by_pt<Muon>(*event->muons);
  sort_by_pt<Electron>(*event->electrons);
  sort_by_pt<Tau>(*event->taus);
  fill_histograms("input");

  cleaner_muon->process(*event);
  cleaner_electron->process(*event);
  cleaner_tau->process(*event);
  cleaner_jet->process(*event);
  fill_histograms("cleaner");

  cleaner_jettauoverlap->process(*event);
  fill_histograms("jettaucleaner");




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
