#include <TString.h>
#include <TFile.h>
#include <iostream>

#include "include/BaseTool.h"
#include "include/useful_functions.h"
#include <sys/stat.h>
#include "include/Registry.h"

using namespace std;

class GenlevelTool : public BaseTool {

public:
  // Constructors, destructor
  GenlevelTool(const Config & cfg);
  ~GenlevelTool() = default;
  virtual bool Process(Event & event) override;


private:

  // Modules used in the analysis
  GenJetId      genjet_id;
  GenParticleId genvistau_id;
  double        mindr_genjet_tauvis;

  unique_ptr<GenJetCleaner>       cleaner_genjet;
  unique_ptr<GenVisTauCleaner>    cleaner_genvistau;
  unique_ptr<GenJetVisTauCleaner> cleaner_genjetvistau;

};


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




bool GenlevelTool::Process(Event & event){
  // cout << "+++ NEW EVENT" << endl;

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
  double stmet = event.met_from_invis->pt();
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
