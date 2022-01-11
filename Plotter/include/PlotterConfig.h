#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>

#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Plotter/include/PlottingDataset.h"

// struct plotting_dataset{
//   TString name                = "";
//   int     color               = -1;
//   int     linestyle           = -1;
//   TString legend              = "";
//   TString type                = "";
//   bool    stack               = false;
//   TString infilename          = "";
// };


// Class to store the XML information and ultimately steer the looping through the different datasets.
class PlotterConfig {

public:
  // Constructors, destructor
  PlotterConfig(TString configfilename);
  PlotterConfig(const PlotterConfig &) = default;
  PlotterConfig & operator = (const PlotterConfig &) = default;
  ~PlotterConfig() = default;

  void increment_idx(){m_idx += 1;};
  void set_idx(size_t i){m_idx = i;};
  void add_dataset(PlottingDataset d){m_datasets.emplace_back(d);};
  const size_t  n_datasets()   const {return m_datasets.size();};
  const size_t  idx()          const {return m_idx;};

  const TString output_directory() const {return m_output_directory;};
  const TString input_directory() const {return m_input_directory;};
  const TString se_director() const {return m_se_director;};
  const TString prefix() const {return m_prefix;};
  const TString lumitext() const {return m_lumitext;};
  const bool blind() const {return m_blind;};
  const bool logY() const {return m_logY;};
  const bool normalize() const {return m_normalize;};
  const bool singlePDF() const {return m_singlePDF;};
  const TString numerator() const {return m_numerator;};
  const std::vector<PlottingDataset> datasets() const {return m_datasets;};

  const TString dataset_name() const {return m_datasets[m_idx].name;};
  const int dataset_color() const {return m_datasets[m_idx].color;};
  const int dataset_linestyle() const {return m_datasets[m_idx].linestyle;};
  const TString dataset_legend() const {return m_datasets[m_idx].legend;};
  const TString dataset_type() const {return m_datasets[m_idx].type;};
  const bool dataset_stack() const {return m_datasets[m_idx].stack;};




private:
  TString m_input_directory, m_output_directory, m_se_director, m_prefix, m_lumitext, m_numerator;
  bool m_blind, m_logY, m_normalize, m_singlePDF;
  std::vector<PlottingDataset> m_datasets = {};
  int m_idx = 0;
  bool m_is_init = false;

};
