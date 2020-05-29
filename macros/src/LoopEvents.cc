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
void GenlevelTool::LoopEvents(){


  cout << endl << endl << green << "--> Now processing file with configuration (MLQ, MX, MDM) = (" << MLQ << ", " << MX << ", " << MDM << ") and lambda = " << lambda << reset << endl;
  TString lambdastr = lambstr(lambda);

  TTreeReader myReaderEvent("AnalysisTree", simple_file.get());
  int nevt = myReaderEvent.GetEntries(true);


  // Set up variables used in 'AnalysisTree', read from Tuples
  // ========================================================

  TTreeReaderValue<Met> genmet(myReaderEvent, "GenMET");
  TTreeReaderValue<vector<GenParticle>> gps_hard(myReaderEvent, "GenparticlesHard");
  TTreeReaderValue<vector<GenParticle>> gps_final(myReaderEvent, "GenparticlesFinal");
  TTreeReaderValue<vector<GenParticle>> gps_prompttaudecayprod(myReaderEvent, "GenparticlesPromptTauDecayProd");
  TTreeReaderValue<vector<GenJet>>      genjets(myReaderEvent, "GenJets");


  // Get cross section TGraph from file
  // ==================================

  TString crosssectionfilename = base_path_crosssections + "LQCrosssections.root";
  unique_ptr<TFile> crosssectionfile;
  crosssectionfile.reset(new TFile(crosssectionfilename, "READ"));
  TString crosssectiongraphname = "ScalarLQ_Pair_nlo_L" + lambdastr;
  TGraphAsymmErrors* crosssections = (TGraphAsymmErrors*)crosssectionfile->Get(crosssectiongraphname);
  double xsec = crosssections->Eval(MLQ);


  // Event loop
  // ==========

  int idx = 0;
  while (myReaderEvent.Next()) {
    if(debug && (idx%10000==0)) cout << green << "    --> Processing event no. (" << idx << " / " << nevt << ")" << reset << endl;
    idx++;

    Event event;
    event.genmet = &*genmet;
    event.genparticles_hard = &*gps_hard;
    event.genparticles_final = &*gps_final;
    event.genparticles_prompttaudecayprod = &*gps_prompttaudecayprod;
    event.genjets = &*genjets;

    // set eventweight --  generator weight * xsec / nevt --> normalization corresponds to L_int = 1/pb
    // event.weight = *evweight;
    event.weight *= xsec / double(nevt);

    // call event loop, main part of this function!
    Process(event);
    // event.clear();
  }


  // Store filled histograms
  // =======================

  TString outfolder = base_path_analysisfiles;
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  TString outfilename = outfolder + "LQDM_" + get_samplename(MLQ, MX, MDM, lambda) + ".root";
  unique_ptr<TFile> outfile;
  outfile.reset(new TFile(outfilename, "RECREATE"));
  for(const auto & x : histmap) x.second->save(outfile.get());
  outfile->Close();
  cout << green << "--> Wrote histograms to file: " << outfilename << reset << endl;
}
