#include "../include/PlottingTool.h"
#include "../include/cosmetics.h"
#include "../include/constants.h"
#include "../include/useful_functions.h"
#include <TH1D.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

void make_plots(vector<TString> infilenames, TString outfolder, bool singlePDF, bool normalize, bool logy, vector<TString> labels, vector<int> linecolors, vector<int> linestyles, bool debug = false);
void plot_folder(vector<TFile*> infiles, TString outfolder, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels, vector<int> linecolors, vector<int> linestyles, bool debug = false);
vector<TString> produce_infilenames(TString infolder, TString postfix, vector<TString> samples);
vector<TString> get_foldernames(TFile* infile);
vector<TString> get_histnames(TFile* infile, TString foldername);
void do_cosmetics(TH1F* hist, double minimum, double maximum, int linecolor, int linestyle);



void PlottingTool::PlotGenlevel(bool normalize, bool logy, bool singlePDF){
  cout << endl << endl << green << "--> Now plotting with settings:" << reset << endl;
  cout << green << "    normalize : " << normalize << reset << endl;
  cout << green << "    logy :      " << logy << reset << endl;
  cout << green << "    singlePDF : " << singlePDF << reset << endl;

  TString infolder = PlottingTool::base_path_analysisfiles;
  TString infile_postfix = ".root";
  vector<TString> samples = PlottingTool::samples_genlevel;
  vector<TString> labels  = PlottingTool::labels_genlevel;
  vector<int> linecolors  = PlottingTool::linecolors_genlevel;
  vector<int> linestyles  = PlottingTool::linestyles_genlevel;
  TString outfolder = PlottingTool::base_path_plots;






  vector<TString> infilenames = produce_infilenames(infolder, infile_postfix, samples);
  make_plots(infilenames, outfolder, singlePDF, normalize, logy, labels, linecolors, linestyles, debug);


}

void make_plots(vector<TString> infilenames, TString outfolder, bool singlePDF, bool normalize, bool logy, vector<TString> labels, vector<int> linecolors, vector<int> linestyles, bool debug){

  gErrorIgnoreLevel = kError;
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // Get infile pointers
  vector<TFile*> infiles = {};
  for(size_t i=0; i<infilenames.size(); i++){
    infiles.emplace_back(new TFile(infilenames[i], "READ"));
  }

  // Get foldernames from first infile as blueprint
  vector<TString> foldernames = get_foldernames(infiles[0]);

  // Plot plots in each folder
  for(size_t i=0; i<foldernames.size(); i++){

    TString foldername = foldernames[i];
    plot_folder(infiles, outfolder, foldername, singlePDF, normalize, logy, labels, linecolors, linestyles, debug);

  }

  for(size_t i=0; i<infiles.size(); i++){
    delete infiles[i];
  }
}

// Function to plot plots in a single folder
void plot_folder(vector<TFile*> infiles, TString outfolder, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels, vector<int> linecolors, vector<int> linestyles, bool debug){


  cout << green << "    --> Folder: " << foldername << reset << endl;

  // get names of histograms in this folder
  vector<TString> histnames = get_histnames(infiles[0], foldername);

  //set up canvas
  TCanvas* c = new TCanvas("c", "c", 400, 400);
  TPad* pad = SetupPad();
  pad->Draw();
  pad->cd();

  // loop over histograms and plot each
  for(size_t i=0; i<histnames.size(); i++){
    TString histname = histnames[i];

    TLegend* leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(43);
    leg->SetTextSize(12);

    //get histograms from each file and apply cosmetics
    vector<TH1F*> hists = {};
    double maximum = -1.;
    for(size_t j=0; j<infiles.size(); j++){
      TH1F* hist = ((TH1F*)infiles[j]->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      maximum = max(max(maximum, hist->GetMaximum()), 1E-4);
      hists.emplace_back(hist);
    }

    double minimum = 0.;
    if(normalize) minimum = 5E-5;
    else if(logy) minimum = 5E-10;
    double maxscale = 1.5;
    if(logy) maxscale = 100;
    for(size_t j=0; j<hists.size(); j++){
      TH1F* hist = hists[j];
      do_cosmetics(hist, minimum, maximum*maxscale, linecolors[j], linestyles[j]);
      if(normalize) hist->GetYaxis()->SetTitle("Event fraction");

      if(j==0) hist->Draw("HIST");
      else     hist->Draw("HIST SAME");

      leg->AddEntry(hist, labels[j], "l");
    }
    leg->Draw();
    if(logy) pad->SetLogy(true);

    if(singlePDF){
      TString outfilename = outfolder + "SinglePDF/" + foldername + "_" + histname + ".pdf";
      if(!logy) outfilename.ReplaceAll(".pdf", "_linY.pdf");
      if(normalize) outfilename.ReplaceAll(".pdf", "_norm.pdf");
      c->Print(outfilename);
    }
    else{
      TString outfilename = outfolder + foldername + ".pdf";
      if(!logy) outfilename.ReplaceAll(".pdf", "_linY.pdf");
      if(normalize) outfilename.ReplaceAll(".pdf", "_norm.pdf");
      if(i==0)                     outfilename += "(";
      else if(i==histnames.size()-1) outfilename += ")";
      c->Print(outfilename, "pdf");
    }


  }
  delete c;

}




// Utility functions
// =================

vector<TString> produce_infilenames(TString infolder, TString postfix, vector<TString> samples){
  vector<TString> result = {};
  for(size_t i=0; i<samples.size(); i++){
    result.emplace_back(infolder + samples[i] + postfix);
  }
  return result;
}

vector<TString> get_foldernames(TFile* infile){

  infile->cd();
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;

  vector<TString> result = {};
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile") && !cl->InheritsFrom("TH1")){
      TString name = key->ReadObj()->GetName();
      result.emplace_back(name);
    }
  }

  return result;
}

vector<TString> get_histnames(TFile* infile, TString foldername){
  infile->cd(foldername);
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;

  vector<TString> result = {};
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(!cl->InheritsFrom("TDirectoryFile") && cl->InheritsFrom("TH1")){
      TString name = key->ReadObj()->GetName();
      result.emplace_back(name);
    }
  }

  return result;

}


void do_cosmetics(TH1F* hist, double minimum, double maximum, int linecolor, int linestyle){

  HistCosmetics(hist);
  hist->SetMinimum(minimum);
  hist->SetMaximum(maximum);
  hist->SetLineColor(linecolor);
  hist->SetMarkerColor(linecolor);
  hist->SetLineStyle(linestyle);
}
