#include "LEAF/Plotter/include/PlottingTool.h"
#include "LEAF/Plotter/include/cosmetics.h"
#include "LEAF/Analyzer/include/useful_functions.h"
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

void make_plots(vector<PlottingDataset*>& datasets_all, TString numerator, TString infolder, TString outfolder, TString outnameprefix, TString lumitext, bool singlePDF, bool normalize, bool logy, bool debug = false);

// void plot_folder(vector<TFile*> infiles_single, vector<TFile*> infiles_stack, vector<TFile*> infiles_numerator, TString outfolder, TString outnameprefix, TString lumitext, TString foldername, bool singlePDF, bool normalize, bool logy, vector<TString> labels_stack, vector<int> colors_stack, vector<int> linestyles_stack, vector<TString> labels_single, vector<int> colors_single, vector<int> linestyles_single, vector<int> colors_numerator, vector<int> linestyles_numerator, bool debug = false);
void plot_folder(vector<PlottingDataset*>& datasets_stack, vector<PlottingDataset*>& datasets_single, PlottingDataset* dataset_numerator, TString outfolder, TString outnameprefix, TString lumitext, TString foldername, bool singlePDF, bool normalize, bool logy, bool do_stack, bool do_ratio, bool debug = false);
// vector<TString> produce_infilenames(TString infolder, vector<PlottingDataset> samples);
// vector<TString> get_foldernames(TFile* infile);
vector<TString> get_foldernames(PlottingDataset* dataset);
// vector<TString> get_histnames(TFile* infile, TString foldername);
vector<TString> get_histnames(PlottingDataset* dataset, TString foldername);
void do_cosmetics(TH1F* hist, double minimum, double maximum, int color, int linestyle, bool ratio=false);



void PlottingTool::Plot(){
  cout << endl << endl << green << "--> Now plotting with settings:" << reset << endl;
  cout << green << "    blind :     " << PlottingTool::blind << reset << endl;
  cout << green << "    normalize : " << PlottingTool::normalize << reset << endl;
  cout << green << "    logy :      " << PlottingTool::logY << reset << endl;
  cout << green << "    singlePDF : " << PlottingTool::singlePDF << reset << endl;

  TString infolder = PlottingTool::base_path_analysisfiles;
  vector<PlottingDataset*> datasets       = {};
  for(PlottingDataset & dataset : PlottingTool::datasets){
    if(PlottingTool::blind && dataset.type.Contains("DATA")) continue;
    datasets.emplace_back(&dataset);
  }

  // find dataset that will be the numerator
  TString numerator             = PlottingTool::numerator;
  bool already_found_numerator = false;
  for(PlottingDataset dataset : PlottingTool::datasets){
    if(dataset.name == numerator){
      if(already_found_numerator) throw runtime_error("There seem to be at least 2 datasets with the same name, which is also equal to the numerator name: " + numerator + ".");
      if(PlottingTool::blind && dataset.type.Contains("DATA")) numerator = "";
      already_found_numerator = true;
    }
  }

  TString outfolder             = PlottingTool::base_path_plots;
  TString outnameprefix         = PlottingTool::prefix_plots;
  if(PlottingTool::blind) outnameprefix += "blind_";

  TString mkdircommand = "mkdir -p " + outfolder;
  system((const char*)mkdircommand);



  // samples, stacks, labels, colors, linestyles



  make_plots(datasets, numerator, infolder, outfolder, outnameprefix, PlottingTool::lumitext, PlottingTool::singlePDF, PlottingTool::normalize, PlottingTool::logY, PlottingTool::debug);


}

void make_plots(vector<PlottingDataset*>& datasets_all, TString numerator, TString infolder, TString outfolder, TString outnameprefix, TString lumitext, bool singlePDF, bool normalize, bool logy, bool debug ){

  // Split the list of all datasets into "stack" and "single", and also find the numerator
  bool do_stack = false;
  bool already_found_numerator = false;
  vector<PlottingDataset*> datasets_stack, datasets_single = {};
  PlottingDataset* dataset_numerator;
  for(PlottingDataset* dataset : datasets_all){
    if(dataset->stack){
      do_stack = true;
      datasets_stack.emplace_back(dataset);
    }
    else{
      datasets_single.emplace_back(dataset);
    }
    if(dataset->name == numerator){
      if(already_found_numerator) throw runtime_error("There seem to be at least 2 datasets with the same name, which is also equal to the numerator name: " + numerator + ".");
      dataset_numerator = dataset;
      already_found_numerator = true;
    }
  }

  // Some sanity checks
  if(!do_stack && already_found_numerator) throw runtime_error("Found the numerator, but won't stack. This is not supported at the moment, ratios can right now only be made between a stack and a histogram.");
  if(numerator != "" && !already_found_numerator) throw runtime_error("A numerator name was given, but it couldn't be found. Please check.");
  if(datasets_stack.size() == 0 && datasets_single.size() == 0) throw runtime_error("List of both single histograms and for stacks is empty. What should even be plotted?");
  if(datasets_all.size() != (datasets_single.size() + datasets_stack.size())) throw runtime_error("Number of all datasets is not the same as number of single + number of stacked datasets. Did something get lost?");


  gErrorIgnoreLevel = kError;
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // Get foldernames from first infile as blueprint
  vector<TString> foldernames = get_foldernames(datasets_all[0]);

  for(PlottingDataset* dataset : datasets_all){
    dataset->PopulateInfile();
  }

  // Plot plots in each folder
  for(size_t i=0; i<foldernames.size(); i++){

    TString foldername = foldernames[i];
    plot_folder(datasets_stack, datasets_single, dataset_numerator, outfolder, outnameprefix, lumitext, foldername, singlePDF, normalize, logy, do_stack, already_found_numerator, debug);

  }

  cout << green << "--> Wrote plots to folder: " << outfolder << ", now cleaning up..." << reset << endl;

  for(PlottingDataset* dataset : datasets_all){
    dataset->ClearInfile();
  }
  cout << green << "--> Cleaned up!" << reset << endl;
}



// Function to plot plots in a single folder
void plot_folder(vector<PlottingDataset*>& datasets_stack, vector<PlottingDataset*>& datasets_single, PlottingDataset* dataset_numerator, TString outfolder, TString outnameprefix, TString lumitext, TString foldername, bool singlePDF, bool normalize, bool logy, bool do_stack, bool do_ratio, bool debug){

  cout << green << "    --> Folder: " << foldername << reset << endl;




  // get names of histograms in this folder

  vector<TString> histnames = {};
  if(datasets_single.size() > 0){
    histnames = get_histnames(datasets_single[0], foldername);
  }
  else{
    histnames = get_histnames(datasets_stack[0], foldername);
  }


  // make sure outfolder exists
  mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  outfolder += "/";
  if(singlePDF){
    outfolder += "SinglePDF/";
    mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    outfolder +=  foldername + "/";
    mkdir(outfolder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  }

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

  // loop over histograms and plot each
  for(size_t i=0; i<histnames.size(); i++){
    TString histname = histnames[i];

    // Find number of legend entries to format it properly
    int n_legentries_per_col = 6;
    int n_legentries = datasets_single.size() + datasets_stack.size();
    int n_legcols = (n_legentries-1)/n_legentries_per_col + 1;
    float leg_colwidth = 0.15;
    float leg_x_high = 0.9;
    float leg_x_low = leg_x_high - n_legcols*leg_colwidth;



    float height_per_legitem = 0.055;
    if(!do_ratio) height_per_legitem *=0.66666;
    float leg_y_high = 0.915;
    int max_num_entries_per_col = ceil((double)n_legentries/n_legcols);
    float leg_y_low  = leg_y_high - height_per_legitem * max_num_entries_per_col;

    TLegend* leg = new TLegend(leg_x_low, leg_y_low, leg_x_high, leg_y_high);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(43);
    leg->SetTextSize(10);
    leg->SetNColumns(n_legcols);

    //defaults for cosmetics
    double minimum = 0.;
    if(normalize) minimum = 5E-1;
    if(logy){
      minimum = 5E-2;
      if(normalize) minimum = 5E-5;
    }
    double maxscale = 1.5;
    if(logy) maxscale = 100;
    double maximum = -1.;




    // find histograms to be stacked
    THStack* stack = new THStack("stack", "");
    for(PlottingDataset* dataset : datasets_stack){
      TH1F* hist = ((TH1F*)dataset->infile->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      else          hist->Scale(dataset->scalefactor);
      hist->SetFillColor(dataset->color);
      hist->SetLineWidth(0);
      stack->Add(hist);
      stack->SetHistogram(hist);
    }

    vector<bool> is_data = {};
    for(PlottingDataset* dataset : datasets_single){
      if(dataset->type.Contains("DATA")) is_data.emplace_back(true);
      else is_data.emplace_back(false);
      TH1F* hist = (TH1F*)(dataset->infile->Get(foldername + "/" + histname));
      if(dataset->type.Contains("DATA")) {
        leg->AddEntry(hist, dataset->legend, "lp");
      }
      else{
        delete hist;
      }

    }

    for(int j=datasets_stack.size()-1; j>=0; j--){
      TH1F* hist = ((TH1F*)datasets_stack[j]->infile->Get(foldername + "/" + histname));
      hist->SetFillColor(datasets_stack[j]->color);
      leg->AddEntry(hist, datasets_stack[j]->legend, "f");
    }

    if(datasets_stack.size() > 0){
      maximum = max(max(maximum, ((TH1*)(stack->GetStack()->Last()))->GetMaximum()), 1E-4);
    }

    //get single histograms from each file and apply cosmetics
    vector<TH1F*> hists_single = {};
    for(size_t j=0; j<datasets_single.size(); j++){
      TH1F* hist = ((TH1F*)datasets_single[j]->infile->Get(foldername + "/" + histname));
      if(normalize) hist->Scale(1./hist->Integral());
      else          hist->Scale(datasets_single[j]->scalefactor);
      maximum = max(max(maximum, hist->GetMaximum()), 1E-4);
      hists_single.emplace_back(hist);
      if(!is_data[j]) leg->AddEntry(hist, datasets_single[j]->legend, "l");
    }

    pad_top->Clear();
    pad_top->cd();

    // first draw a histogram (if any)
    size_t nsingle = 0;
    for(size_t j=0; j<hists_single.size(); j++){
      do_cosmetics(hists_single[j], minimum, maximum*maxscale, datasets_single[j]->color, datasets_single[j]->linestyle);
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
    if(do_stack){
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
      if(j > 0 || stack) opt += " SAME";
      hists_single[j]->Draw(opt);
    }

    pad_top->RedrawAxis();
    leg->Draw();
      if(logy) pad_top->SetLogy(true);

      // write texts, like the lumi, CMS tags, etc.
      TLatex *latex_lumitext = new TLatex(1, 1, lumitext);
      latex_lumitext->SetNDC();
      latex_lumitext->SetTextAlign(33);
      latex_lumitext->SetX(0.95);
      latex_lumitext->SetTextFont(42);
      float lumitextsize = 0.06;
      if(!do_ratio) lumitextsize *= 0.66666;
      latex_lumitext->SetTextSize(lumitextsize);
      latex_lumitext->SetY(1.);
      latex_lumitext->Draw();



      // now handle all the ratio business

      TH1F* h_numerator = new TH1F();
      TH1F* h_denom = new TH1F();
      if(do_ratio){
        // if(false){

        delete h_numerator;
        delete h_denom;

        // numerator is given, denominator will be the stack.
        h_numerator = new TH1F(*(TH1F*)(dataset_numerator->infile->Get(foldername + "/" + histname)));
        h_denom = new TH1F(*(TH1F*)((stack->GetStack()->Last())));

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
        do_cosmetics(h_numerator, 0.3, 1.7, dataset_numerator->color, dataset_numerator->linestyle, true);
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

      if(do_stack){
        delete h_err;
      }

      for(size_t j=0; j<hists_single.size(); j++){
        delete hists_single[j];
      }

      delete leg;
      delete stack;


  }
  delete c;

}




// Utility functions
// =================
vector<TString> get_foldernames(PlottingDataset* dataset){

  // unique_ptr<TFile> infile;
  // infile.reset(new TFile(dataset.infilename, "READ"));
  dataset->PopulateInfile();
  dataset->infile->cd();
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;

  vector<TString> result = {};
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile") && !cl->InheritsFrom("TH1")){
      TString name = key->ReadObj()->GetName();
      if(name == "BTaggingMCEfficiencies") continue; // ignore BTagging histograms, these are 2-d
      result.emplace_back(name);
    }
  }
  dataset->ClearInfile();
  return result;
}

vector<TString> get_histnames(PlottingDataset* dataset, TString foldername){
  bool was_populated = dataset->is_infile_populated;
  if(!was_populated) dataset->PopulateInfile();

  dataset->infile->cd(foldername);
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;

  vector<TString> result = {};
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(!cl->InheritsFrom("TDirectoryFile") && cl->InheritsFrom("TH1") && !cl->InheritsFrom("TH2")){
      TString name = key->ReadObj()->GetName();
      result.emplace_back(name);
    }
  }

  if(!was_populated) dataset->ClearInfile();
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
