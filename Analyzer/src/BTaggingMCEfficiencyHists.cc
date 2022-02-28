#include "LEAF/Analyzer/include/BTaggingMCEfficiencyHists.h"

using namespace std;

BTaggingMCEfficiencyHists::BTaggingMCEfficiencyHists(TString dir_, JetBTag::wp wp): BaseHists(dir_), m_btagid(wp){

  const vector<double> BTagMCEffBinsEta = {-2.4, 2.4};
  const vector<double> BTagMCEffBinsPt = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};

  h_b_passing =    book<TH2D>("b_passing",    ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());
  h_b_total =      book<TH2D>("b_total",      ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());
  h_c_passing =    book<TH2D>("c_passing",    ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());
  h_c_total =      book<TH2D>("c_total",      ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());
  h_udsg_passing = book<TH2D>("udsg_passing", ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());
  h_udsg_total =   book<TH2D>("udsg_total",   ";p_{T}^{jet} [GeV];#eta^{jet};Events / bin", BTagMCEffBinsPt.size()-1, BTagMCEffBinsPt.data(), BTagMCEffBinsEta.size()-1, BTagMCEffBinsEta.data());

}

void BTaggingMCEfficiencyHists::fill(const RecoEvent & event){
  if(event.is_data) return; // makes only sense for MC, check the class name. lol.

  double weight = event.weight;
  for (Jet & jet : *event.ak4chs){

    int flav = jet.hadron_flavor();
    bool is_tagged = m_btagid(jet, event);
    double pt = jet.pt();
    double eta = jet.eta();

    if(flav == 5){
      h_b_total->Fill(pt, eta, weight);
      if(is_tagged) h_b_passing->Fill(pt, eta, weight);
    }
    else if(flav == 4){
      h_c_total->Fill(pt, eta, weight);
      if(is_tagged) h_c_passing->Fill(pt, eta, weight);
    }
    else{
      h_udsg_total->Fill(pt, eta, weight);
      if(is_tagged) h_udsg_passing->Fill(pt, eta, weight);
    }
  }
}
