#include "Plotter/include/PlottingTool.h"
#include "Plotter/include/cosmetics.h"
// #include "include/constants.h"
#include "include/useful_functions.h"
#include <TH1D.h>
#include <THStack.h>
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

void make_plots(vector<TString> infilenames_all, vector<TString> samples, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, vector<TString> infilenames_stack, bool debug = false);
void plot_folder(vector<TFile*> infiles_single, vector<TFile*> infiles_stack, TString outfolder, TString outnameprefix, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels_stack, vector<int> colors_stack, vector<int> linestyles_stack, vector<TString> labels_single, vector<int> colors_single, vector<int> linestyles_single, bool debug = false);
vector<TString> produce_infilenames(TString infolder, TString postfix, vector<TString> samples);
vector<TString> get_foldernames(TFile* infile);
vector<TString> get_histnames(TFile* infile, TString foldername);
void do_cosmetics(TH1F* hist, double minimum, double maximum, int color, int linestyle);



void PlottingTool::Plot(bool normalize, bool logy, bool singlePDF){
  cout << endl << endl << green << "--> Now plotting with settings:" << reset << endl;
  cout << green << "    normalize : " << normalize << reset << endl;
  cout << green << "    logy :      " << logy << reset << endl;
  cout << green << "    singlePDF : " << singlePDF << reset << endl;

  TString infolder = PlottingTool::base_path_analysisfiles;
  TString infile_postfix = ".root";
  vector<TString> samples = PlottingTool::samples;
  // vector<TString> labels  = PlottingTool::labels;
  // vector<int> colors  = PlottingTool::colors;
  // vector<int> linestyles  = PlottingTool::linestyles;
  map<TString, TString> labels  = PlottingTool::labels;
  map<TString, int> colors      = PlottingTool::colors;
  map<TString, int> linestyles  = PlottingTool::linestyles;
  vector<TString> stacks  = PlottingTool::stacks;
  TString outfolder = PlottingTool::base_path_plots;
  TString outnameprefix = PlottingTool::prefix_plots;






  vector<TString> infilenames_all = produce_infilenames(infolder, infile_postfix, samples);
  vector<TString> infilenames_stack = produce_infilenames(infolder, infile_postfix, stacks);
  make_plots(infilenames_all, samples, outfolder, outnameprefix, singlePDF, normalize, logy, labels, colors, linestyles, infilenames_stack, debug);


}

void make_plots(vector<TString> infilenames_all, vector<TString> samples, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, vector<TString> infilenames_stack, bool debug){

  gErrorIgnoreLevel = kError;
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // Reorder infilenames to get the stacking order right. Always start with stacks and then do the rest.
  vector<TString> infilenames_single, infilenames_stack_ordered = {};
  vector<TString> labels_single, labels_stack = {};
  vector<int> colors_single, colors_stack = {};
  vector<int> linestyles_single, linestyles_stack = {};
  for(size_t i=0; i<infilenames_all.size(); i++){
    if(find(infilenames_stack.begin(), infilenames_stack.end(), infilenames_all[i]) != infilenames_stack.end()) {
      infilenames_stack_ordered.emplace_back(infilenames_all[i]);
      labels_stack.emplace_back(labels[samples[i]]);
      colors_stack.emplace_back(colors[samples[i]]);
      linestyles_stack.emplace_back(linestyles[samples[i]]);
      // cout << "added to stacking values: " << samples[i] << endl;
    }
    else{
      infilenames_single.emplace_back(infilenames_all[i]);
      labels_single.emplace_back(labels[samples[i]]);
      colors_single.emplace_back(colors[samples[i]]);
      linestyles_single.emplace_back(linestyles[samples[i]]);
    }
    // cout << "sample: " << samples[i] << ", color: " << colors[samples[i]] << endl;
  }

  // Get remaining infile pointers. Skip if already present in infilenames_stack
  vector<TFile*> infiles_single, infiles_stack = {};
  for(size_t i=0; i<infilenames_single.size(); i++){
    infiles_single.emplace_back(new TFile(infilenames_single[i], "READ"));
  }
  for(size_t i=0; i<infilenames_stack_ordered.size(); i++){
    infiles_stack.emplace_back(new TFile(infilenames_stack_ordered[i], "READ"));
  }

  // Get foldernames from first infile as blueprint
  vector<TString> foldernames = {};
  if(infiles_single.size() > 0) foldernames = get_foldernames(infiles_single[0]);
  else if(infiles_stack.size() > 0) foldernames = get_foldernames(infiles_stack[0]);
  else throw runtime_error("In make_plots(): infile-list for both single histograms and for stacks is empty. What should even be plotted?");

  // Plot plots in each folder
  for(size_t i=0; i<foldernames.size(); i++){

    TString foldername = foldernames[i];
    plot_folder(infiles_stack, infiles_single, outfolder, outnameprefix, foldername, singlePDF, normalize, logy, labels_stack, colors_stack, linestyles_stack, labels_single, colors_single, linestyles_single, debug);
  }

  for(size_t i=0; i<infiles_single.size(); i++){
    delete infiles_single[i];
  }
  for(size_t i=0; i<infiles_stack.size(); i++){
    delete infiles_stack[i];
  }
  cout << green << "--> Wrote plots to folder: " << outfolder << reset << endl;
}

// Function to plot plots in a single folder
void plot_folder(vector<TFile*> infiles_stack, vector<TFile*> infiles_single, TString outfolder, TString outnameprefix, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels_stack, vector<int> colors_stack, vector<int> linestyles_stack, vector<TString> labels_single, vector<int> colors_single, vector<int> linestyles_single, bool debug){


  cout << green << "    --> Folder: " << foldername << reset << endl;

  // get names of histograms in this folder
  vector<TString> histnames = get_histnames(infiles_single[0], foldername);


  // make sure outfolder exists
  if(singlePDF) outfolder += "SinglePDF/";
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  //set up canvas
  TCanvas* c = new TCanvas("c", "c", 400, 400);
  TPad* pad = SetupPad();
  pad->Draw();
  pad->cd();

  float height_per_legitem = 0.033;
  float leg_y_high = 0.9;
  float leg_y_low  = leg_y_high - height_per_legitem * (infiles_stack.size() + infiles_single.size());

  // loop over histograms and plot each
  for(size_t i=0; i<histnames.size(); i++){
    TString histname = histnames[i];


    TLegend* leg = new TLegend(0.5, leg_y_low, 0.9, leg_y_high);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(43);
    leg->SetTextSize(12);

    //defaults fo cosmetics
    double minimum = 0.;
    if(normalize) minimum = 5E-5;
    else if(logy) minimum = 5E-6;
    double maxscale = 1.5;
    if(logy) maxscale = 100;
    double maximum = -1.;


    //same for stacked histograms
    THStack* stack = new THStack("stack", "");
    for(size_t j=0; j<infiles_stack.size(); j++){
      TH1F* hist = ((TH1F*)infiles_stack[j]->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      // do_cosmetics(hist, minimum, maximum*maxscale, colors_stack[j], linestyles_stack[j]);
      hist->SetFillColor(colors_stack[j]);
      hist->SetLineWidth(0);
      // hist->SetLineStyle(0);
      stack->Add(hist);
      stack->SetHistogram(hist);
      leg->AddEntry(hist, labels_stack[j], "f");
      // cout << "Added to the stack: " << labels_stack[j] << ", color: " << colors_stack[j] << endl;
    }
    if(infiles_stack.size() > 0){
      maximum = max(max(maximum, ((TH1*)(stack->GetStack()->Last()))->GetMaximum()), 1E-4);
    }

    //get single histograms from each file and apply cosmetics
    vector<TH1F*> hists_single = {};
    for(size_t j=0; j<infiles_single.size(); j++){
      TH1F* hist = ((TH1F*)infiles_single[j]->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      maximum = max(max(maximum, hist->GetMaximum()), 1E-4);
      hists_single.emplace_back(hist);
      leg->AddEntry(hist, labels_single[j], "l");
    }

    // first draw a histogram (if any)
    size_t nsingle = 0;
    for(size_t j=0; j<hists_single.size(); j++){
      do_cosmetics(hists_single[j], minimum, maximum*maxscale, colors_single[j], linestyles_single[j]);
      if(normalize) hists_single[j]->GetYaxis()->SetTitle("Event fraction");
      if(j==0) hists_single[j]->Draw("HIST");
      else     hists_single[j]->Draw("HIST SAME");
      nsingle++;
    }

    // now draw the stack (must be afterwards to get axes right)
    if(stack){
      TString opt = "HIST";
      if(nsingle > 0) opt += " SAME";
      stack->Draw(opt);
    }

    // now draw single histograms again (so they are in the foreground)
    for(size_t j=0; j<hists_single.size(); j++){
      TString opt = "HIST";
      if(nsingle > 0 || stack) opt += " SAME";
      hists_single[j]->Draw(opt);
    }

    pad->RedrawAxis();
    leg->Draw();
    if(logy) pad->SetLogy(true);

    TString outfilename = "";
    if(singlePDF){
      outfilename = outfolder + outnameprefix + foldername + "_" + histname + ".pdf";
      if(!logy) outfilename.ReplaceAll(".pdf", "_linY.pdf");
      if(normalize) outfilename.ReplaceAll(".pdf", "_norm.pdf");
      c->Print(outfilename);
      // cout << "outfilename: " << outfilename << endl;
    }
    else{
      outfilename = outfolder + outnameprefix + foldername + ".pdf";
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


void do_cosmetics(TH1F* hist, double minimum, double maximum, int color, int linestyle){

  HistCosmetics(hist);
  hist->SetMinimum(minimum);
  hist->SetMaximum(maximum);
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetLineStyle(linestyle);
}
