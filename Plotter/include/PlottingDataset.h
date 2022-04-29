#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>

#include "LEAF/Analyzer/include/useful_functions.h"



// Simple container class + functionality to load and delete infiles

class PlottingDataset {

public:
  // Constructors, destructor
  PlottingDataset(TString name_="", int color_=-1, int linestyle_=-1, TString legend_="", TString type_="", bool stack_=false, double scalefactor_=1., TString infilename_="") : name(name_), color(color_), linestyle(linestyle_), legend(legend_), type(type_), stack(stack_), scalefactor(scalefactor_), infilename(infilename_){
    is_infile_populated = false;
    infile = nullptr;
  };

  PlottingDataset(const PlottingDataset &) = default;
  PlottingDataset & operator = (const PlottingDataset &) = default;
  ~PlottingDataset(){
    ClearInfile();
    name                = "";
    color               = -1;
    linestyle           = -1;
    legend              = "";
    type                = "";
    stack               = false;
    scalefactor         = 1.;
    infilename          = "";
  };

  void PopulateInfile(){
    if(!is_infile_populated){
      infile = new TFile(infilename, "READ");
      is_infile_populated = true;
    }
  };

  void ClearInfile(){

    if(is_infile_populated){
      infile->cd();

      if(infile->IsOpen()){
        infile->Close();
      }

      delete infile;
      infile = nullptr;
      is_infile_populated = false;
    }
  };



  TString name;
  int     color;
  int     linestyle;
  TString legend;
  TString type;
  bool    stack;
  double  scalefactor;
  TString infilename;
  TFile*  infile;
  bool    is_infile_populated;


};






//
