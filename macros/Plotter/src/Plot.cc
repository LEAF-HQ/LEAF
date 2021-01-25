#include "Plotter/include/PlottingTool.h"
#include "Plotter/include/cosmetics.h"
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

// void make_plots(vector<TString> infilenames_all, vector<TString> samples, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, vector<TString> infilenames_stack, TString numerator, bool debug = false);
void make_plots(TString infolder, vector<TString> samples, vector<TString> stacks, TString numerator, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, bool debug = false);
void plot_folder(vector<TFile*> infiles_single, vector<TFile*> infiles_stack, vector<TFile*> infiles_numerator, TString outfolder, TString outnameprefix, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels_stack, vector<int> colors_stack, vector<int> linestyles_stack, vector<TString> labels_single, vector<int> colors_single, vector<int> linestyles_single, vector<int> colors_numerator, vector<int> linestyles_numerator, bool debug = false);
vector<TString> produce_infilenames(TString infolder, vector<TString> samples);
vector<TString> get_foldernames(TFile* infile);
vector<TString> get_histnames(TFile* infile, TString foldername);
void do_cosmetics(TH1F* hist, double minimum, double maximum, int color, int linestyle, bool ratio=false);



void PlottingTool::Plot(bool normalize, bool logy, bool singlePDF){
  cout << endl << endl << green << "--> Now plotting with settings:" << reset << endl;
  cout << green << "    normalize : " << normalize << reset << endl;
  cout << green << "    logy :      " << logy << reset << endl;
  cout << green << "    singlePDF : " << singlePDF << reset << endl;

  TString infolder = PlottingTool::base_path_analysisfiles;
  vector<TString> samples       = PlottingTool::samples;
  map<TString, TString> labels  = PlottingTool::labels;
  map<TString, int> colors      = PlottingTool::colors;
  map<TString, int> linestyles  = PlottingTool::linestyles;
  vector<TString> stacks        = PlottingTool::stacks;
  TString numerator             = PlottingTool::numerator;
  TString outfolder = PlottingTool::base_path_plots;
  TString outnameprefix = PlottingTool::prefix_plots;

  TString mkdircommand = "mkdir -p " + outfolder;
  system((const char*)mkdircommand);






  // vector<TString> infilenames_all = produce_infilenames(infolder, samples);
  // vector<TString> infilenames_stack = produce_infilenames(infolder, stacks);
  // make_plots(infilenames_all, samples, outfolder, outnameprefix, singlePDF, normalize, logy, labels, colors, linestyles, infilenames_stack, numerator, debug);
  make_plots(infolder, samples, stacks, numerator, outfolder, outnameprefix, singlePDF, normalize, logy, labels, colors, linestyles, debug);


}

// void make_plots(vector<TString> infilenames_all, vector<TString> samples, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, vector<TString> infilenames_stack, TString numerator, bool debug){
void make_plots(TString infolder, vector<TString> samples, vector<TString> stacks, TString numerator, TString outfolder, TString outnameprefix, bool singlePDF, bool normalize, bool logy, map<TString, TString> labels, map<TString, int> colors, map<TString, int> linestyles, bool debug){

  bool do_stack = false;
  if(numerator != "") do_stack = true;

  vector<TString> infilenames_all = produce_infilenames(infolder, samples);
  vector<TString> infilenames_stack = produce_infilenames(infolder, stacks);
  vector<TString> infilenames_numerator = {};
  if(do_stack) infilenames_numerator = produce_infilenames(infolder, {numerator});
  if(infilenames_numerator.size() > 1) throw runtime_error("In make_plots(): vector of infilenames for the numerator should contain at most 1 element, but now it contains more. How did this happen?");

  gErrorIgnoreLevel = kError;
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // Reorder infilenames to get the stacking order right. Always start with stacks and then do the rest.
  vector<TString> infilenames_single, infilenames_stack_ordered = {};
  vector<TString> labels_single, labels_stack = {};
  vector<int> colors_single, colors_stack, colors_numerator = {};
  vector<int> linestyles_single, linestyles_stack, linestyles_numerator = {};
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
    if (infilenames_numerator.size() > 0){
      if(infilenames_all[i] == infilenames_numerator[0]){
        colors_numerator.emplace_back(colors[samples[i]]);
        linestyles_numerator.emplace_back(linestyles[samples[i]]);
      }
    }
  }

  // Get remaining infile pointers. Skip if already present in infilenames_stack
  vector<TFile*> infiles_single, infiles_stack, infiles_numerator = {};
  for(size_t i=0; i<infilenames_single.size(); i++){
    infiles_single.emplace_back(new TFile(infilenames_single[i], "READ"));
  }
  for(size_t i=0; i<infilenames_stack_ordered.size(); i++){
    infiles_stack.emplace_back(new TFile(infilenames_stack_ordered[i], "READ"));
  }
  for(size_t i=0; i<infilenames_numerator.size(); i++){
    infiles_numerator.emplace_back(new TFile(infilenames_numerator[i], "READ"));
  }

  // Get foldernames from first infile as blueprint
  vector<TString> foldernames = {};
  if(infiles_single.size() > 0) foldernames = get_foldernames(infiles_single[0]);
  else if(infiles_stack.size() > 0) foldernames = get_foldernames(infiles_stack[0]);
  else throw runtime_error("In make_plots(): infile-list for both single histograms and for stacks is empty. What should even be plotted?");

  // Plot plots in each folder
  for(size_t i=0; i<foldernames.size(); i++){

    TString foldername = foldernames[i];
    plot_folder(infiles_stack, infiles_single, infiles_numerator, outfolder, outnameprefix, foldername, singlePDF, normalize, logy, labels_stack, colors_stack, linestyles_stack, labels_single, colors_single, linestyles_single, colors_numerator, linestyles_numerator, debug);
  }

  for(size_t i=0; i<infiles_single.size(); i++){
    delete infiles_single[i];
  }
  for(size_t i=0; i<infiles_stack.size(); i++){
    delete infiles_stack[i];
  }
  for(size_t i=0; i<infiles_numerator.size(); i++){
    delete infiles_numerator[i];
  }
  cout << green << "--> Wrote plots to folder: " << outfolder << reset << endl;
}

// Function to plot plots in a single folder
void plot_folder(vector<TFile*> infiles_stack, vector<TFile*> infiles_single, vector<TFile*> infiles_numerator, TString outfolder, TString outnameprefix, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels_stack, vector<int> colors_stack, vector<int> linestyles_stack, vector<TString> labels_single, vector<int> colors_single, vector<int> linestyles_single, vector<int> colors_numerator, vector<int> linestyles_numerator, bool debug){

  cout << green << "    --> Folder: " << foldername << reset << endl;

  // check if we need to make a ratio plot
  bool do_ratio = false;
  if(infiles_numerator.size() == 1) do_ratio = true;
  else if(infiles_numerator.size() > 1) throw runtime_error("In plot_folder(): infile-list for numerator contains more than one element. This should have been caught by an earlier check, what happened?");

  // get names of histograms in this folder
  vector<TString> histnames = get_histnames(infiles_single[0], foldername);


  // make sure outfolder exists
  if(singlePDF) outfolder += "SinglePDF/";
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

  //set up canvas
  TCanvas* c = new TCanvas("c", "c", 400, 400);
  TPad* pad_top, *pad_ratio;
  if(do_ratio){
    pad_top = SetupRatioPadTop();
    pad_ratio = SetupRatioPad();
    pad_top->Draw();
    pad_ratio->Draw();
  }
  else{
    pad_top = SetupPad();
    pad_top->Draw();
  }

  float height_per_legitem = 0.055;
  if(!do_ratio) height_per_legitem *=0.66666;
  float leg_y_high = 0.9;
  float leg_y_low  = leg_y_high - height_per_legitem * (infiles_stack.size() + infiles_single.size());

  // loop over histograms and plot each
  for(size_t i=0; i<histnames.size(); i++){
    TString histname = histnames[i];


    TLegend* leg = new TLegend(0.6, leg_y_low, 0.9, leg_y_high);
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


    // find histograms to be stacked
    THStack* stack = new THStack("stack", "");
    for(size_t j=0; j<infiles_stack.size(); j++){
      TH1F* hist = ((TH1F*)infiles_stack[j]->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      hist->SetFillColor(colors_stack[j]);
      hist->SetLineWidth(0);
      stack->Add(hist);
      stack->SetHistogram(hist);
    }

    vector<bool> is_data = {};
    for(size_t j=0; j<infiles_single.size(); j++){
      if(((TString)infiles_single[j]->GetName()).Contains("DATA")) is_data.emplace_back(true);
      else is_data.emplace_back(false);
      TH1F* hist = ((TH1F*)infiles_single[j]->Get(foldername + "/" + histname));
      if(is_data[j]) {
        leg->AddEntry(hist, labels_single[j], "lp");
      }
    }

    for(int j=infiles_stack.size()-1; j>=0; j--){
      // cout << "j2: " << j << endl;
      TH1F* hist = ((TH1F*)infiles_stack[j]->Get(foldername + "/" + histname));
      hist->SetFillColor(colors_stack[j]);
      leg->AddEntry(hist, labels_stack[j], "f");
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
      if(!is_data[j])leg->AddEntry(hist, labels_single[j], "l");
    }

    pad_top->Clear();
    pad_top->cd();

    // first draw a histogram (if any)
    size_t nsingle = 0;
    for(size_t j=0; j<hists_single.size(); j++){
      do_cosmetics(hists_single[j], minimum, maximum*maxscale, colors_single[j], linestyles_single[j]);
      if(normalize) hists_single[j]->GetYaxis()->SetTitle("Event fraction");
      if(is_data[j]){
        hists_single[j]->SetMarkerStyle(20);
        hists_single[j]->SetMarkerSize(0.75);

      }

      TString opt = "HIST";
      if (is_data[j]) opt = "E";

      if (j > 0) opt += " SAME";
      hists_single[j]->Draw(opt);
      nsingle++;
    }

    // now draw the stack (must be afterwards to get axes right)
    TH1F* h_err;
    if(stack){
      TString opt = "HIST";
      if(nsingle > 0) opt += " SAME";
      stack->Draw(opt);

      // draw uncertainty of stack
      h_err = new TH1F(*(TH1F*)(stack->GetStack()->Last()));
      h_err->SetFillColor(kGray+1);
      h_err->SetLineWidth(0);
      h_err->SetMarkerStyle(0);
      h_err->SetMarkerSize(0);
      h_err->SetFillStyle(3245);
      h_err->Draw("E2 same");
    }

    // now draw single histograms again (so they are in the foreground)
    for(size_t j=0; j<hists_single.size(); j++){
      TString opt = "HIST";
      if (is_data[j]) opt = "E";
      if(nsingle > 0 || stack) opt += " SAME";
      hists_single[j]->Draw(opt);
    }

    pad_top->RedrawAxis();
    leg->Draw();
    if(logy) pad_top->SetLogy(true);


    // now handle all the ratio business

    TH1F* h_numerator = new TH1F();
    TH1F* h_denom = new TH1F();
    if(do_ratio){
      // if(false){

      delete h_numerator;
      delete h_denom;

      // numerator is given, denominator will be the stack.
      h_numerator = new TH1F(*(TH1F*)(infiles_numerator[0]->Get(foldername + "/" + histname)));
      // ((TH1F*)(infiles_numerator[0]->Get(foldername + "/" + histname)))->Copy(*h_numerator);
      h_denom = new TH1F(*(TH1F*)((stack->GetStack()->Last())));
      // ((TH1F*)((stack->GetStack()->Last())))->Copy(*h_denom);

      if(h_denom->GetNbinsX() != h_numerator->GetNbinsX()) throw runtime_error("Data and stack have different number of bins, ratio cannot be calculated.");
      size_t nbins = h_denom->GetNbinsX();
      for(size_t j=1; j<nbins+1; j++){
        double val_n = h_numerator->GetBinContent(j);
        double err_n = h_numerator->GetBinError(j);
        double val_d = h_denom->GetBinContent(j);
        double err_d = h_denom->GetBinError(j);

        if(val_d > 0){
          h_denom->SetBinContent(j, 1.);
          h_denom->SetBinError(j, err_d/val_d);
          h_numerator->SetBinContent(j, val_n/val_d);
          h_numerator->SetBinError(j, err_n/val_d);
        }
        else{
          h_denom->SetBinContent(j, 0.);
          h_denom->SetBinError(j, 0.);
          h_numerator->SetBinContent(j, 0.);
          h_numerator->SetBinError(j, 0.);
        }
      }
      h_denom->SetMarkerStyle(0);
      h_denom->SetMarkerSize(0);
      h_denom->SetLineColor(kGray+1);
      h_denom->SetFillColor(kGray+1);
      do_cosmetics(h_numerator, 0.3, 1.7, colors_numerator[0], linestyles_numerator[0], true);
      h_numerator->GetYaxis()->SetTitle("Data / Pred.");
      h_numerator->SetMarkerStyle(20);
      h_numerator->SetMarkerSize(0.75);

      // draw it!
      pad_ratio->Clear();
      pad_ratio->cd();
      pad_ratio->SetLogy(0);
      pad_ratio->SetLogx(0);
      h_numerator->Draw("AXIS");
      h_denom->Draw("E2 SAME");
      h_numerator->Draw("SAME");

      double xmin = h_numerator->GetBinLowEdge(1);
      double xmax = h_numerator->GetBinLowEdge(h_numerator->GetNbinsX()+1);
      TLine* l_unity = new TLine(xmin, 1, xmax, 1);
      l_unity->SetLineColor(kBlack);
      l_unity->SetLineWidth(2);
      l_unity->SetLineStyle(2);
      l_unity->Draw("SAME");
      pad_ratio->RedrawAxis();

    }

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

    if(do_ratio){
      delete h_numerator;
      delete h_denom;
    }

    if(stack){
      delete h_err;
    }


  }
  delete c;

}




// Utility functions
// =================

vector<TString> produce_infilenames(TString infolder, vector<TString> samples){
  vector<TString> result = {};
  for(size_t i=0; i<samples.size(); i++){
    result.emplace_back(infolder + samples[i] + ".root");
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


void do_cosmetics(TH1F* hist, double minimum, double maximum, int color, int linestyle, bool ratio){

  HistCosmetics(hist, ratio);
  if(!ratio){
    hist->SetMinimum(minimum);
    hist->SetMaximum(maximum);
  }
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetLineStyle(linestyle);
}
