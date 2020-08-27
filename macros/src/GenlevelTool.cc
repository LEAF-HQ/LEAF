#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>
#include "include/Registry.h"
#include "include/GenEvent.h"

using namespace std;

class GenlevelTool : public BaseTool {

public:
  // Constructors, destructor
  GenlevelTool(const Config & cfg);
  ~GenlevelTool() = default;
  // void LoopEvents(const Config & cfg, GenEvent* event);
  void ProcessDataset(const Config & cfg) override {LoopEvents<GenlevelTool, GenEvent>(cfg, m_event, *this);};
  // void GenlevelTool::ProcessDataset(const Config & cfg){
  //   LoopEvents<GenlevelTool, GenEvent>(cfg, m_event, *this);
  // }

  bool Process(GenEvent & event);


private:

  // Modules used in the analysis
  GenJetId      genjet_id;
  GenParticleId genvistau_id;
  double        mindr_genjet_tauvis;

  unique_ptr<GenJetCleaner>       cleaner_genjet;
  unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;

  GenEvent* m_event;
};


// void GenlevelTool::LoopEvents(const Config & cfg, GenEvent* event){
//
//   // Print current number of dataset
//   cout << endl << green << "--> Initializing sample " << cfg.idx()+1 << "/" << cfg.n_datasets() << ": " << cfg.dataset_name() << reset << endl;
//
//   // Initialize event for later looping through chain
//   cfg.event_chain->SetBranchAddress("Event", &event);
//   cfg.outputtree->Branch("Event", &event);
//
//   // Loop through chain
//   for(int i=0; i<cfg.event_chain->GetEntries(); ++i) {
//     if(i%1000==0){
//       cout << green << "    --> Processing event no. (" << i << " / " << cfg.nevt << ")" << reset << endl;
//     }
//
//     // read the data for i-th event
//     cfg.event_chain->GetEntry(i);
//
//     // weight must be: target_lumi / dataset_lumi
//     event->weight *= cfg.target_lumi() / cfg.dataset_lumi();
//
//     // call Process() for each event, main part of this function.
//     bool keep_event = Process(*event);
//     if(keep_event) cfg.outputtree->Fill();
//     event->reset();
//   }
//
//   event->clear();
//   delete event;
// }






GenlevelTool::GenlevelTool(const Config & cfg) : BaseTool(cfg){
  cout << "Hello from GenlevelTool" << endl;

  m_event = new GenEvent();
  m_event->reset();

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




// bool GenlevelTool::Process(Event & event){
bool GenlevelTool::Process(GenEvent & event){
  // cout << "+++ NEW EVENT" << endl;
  // cout << "njets: " << event.genjets->size() << endl;
  // cout << "test: " << event.test << endl;
  n++;

  // order all objecs in pT
  sort_by_pt<GenParticle>(*event.genparticles_hard);
  sort_by_pt<GenParticle>(*event.genparticles_final);
  sort_by_pt<GenParticle>(*event.genparticles_visibletaus);
  sort_by_pt<GenJet>(*event.genjets);
  histmap["input"]->fill(event);


  // clean jets and visible taus
  cleaner_genvistau   ->process(event);
  cleaner_genjet      ->process(event);
  cleaner_genjetvistau->process(event);
  histmap["cleaner"]->fill(event);

  if(event.genparticles_visibletaus->size() < 1) return false;
  if(event.genparticles_visibletaus->at(0).pt() < 50) return false;
  if(event.genjets->size() < 1) return false;
  if(event.genjets->at(0).pt() < 50) return false;
  histmap["objectselection"]->fill(event);



  // calculate STMET
  double st = 0;
  // double stmet = event.genmet->pt();
  double stmet = event.genmet_invis->pt();
  int njetsmax = min((size_t)2, event.genjets->size());
  int ntauvismax = min((size_t)2, event.genparticles_visibletaus->size());
  for(int i=0; i<njetsmax; i++) st += event.genjets->at(i).pt();
  for(int i=0; i<ntauvismax; i++) st += event.genparticles_visibletaus->at(i).pt();
  stmet += st;
  // cout << "stmet: " << stmet << endl;
  // event.weight *= 2;
  if(stmet < 600) return false;
  histmap["stmet"]->fill(event);



  return true;
}




REGISTER_TOOL(GenlevelTool)
