#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "LEAF/Analyzer/include/Event.h"
#include "LEAF/Analyzer/include/BaseHists.h"
#include "LEAF/Analyzer/include/CleaningModules.h"

struct dataset{
  TString name                = "";
  TString type                = "";
  TString year                = "";
  vector<TString> infilenames = {};
  double lumi                  = -1.;
};


// Class to store the XML information and ultimately steer the looping through the different datasets.
class Config {

public:
  // Constructors, destructor
  Config(TString configfilename);
  Config(const Config &) = default;
  Config & operator = (const Config &) = default;
  ~Config() = default;

  void increment_idx(){m_idx += 1;};
  void set_idx(size_t i){m_idx = i;};
  void add_dataset(dataset d){m_datasets.emplace_back(d);};

  const bool    has(const string s) const {auto it = m_additionalvariables.find(s); return (it != m_additionalvariables.end());};
  const string  get(const string s) const {if(Config::has(s)){return m_additionalvariables.at(s);} else{throw runtime_error("Trying to get non-existent variable '" + s + "' from Config.");}};
  const TString output_directory() const {return m_output_directory;};
  const TString se_director() const {return m_se_director;};
  const TString postfix() const {return m_postfix;};
  const double  target_lumi() const {return m_target_lumi;};
  const string  analysis_tool() const {return m_analysis_tool;};
  const int     nevt_max() const {return m_nevt_max;};
  const int     nevt_skip() const {return m_nevt_skip;};
  const TString dataset_name() const {return m_datasets[m_idx].name;};
  const TString dataset_type() const {return m_datasets[m_idx].type;};
  const TString dataset_year() const {return m_datasets[m_idx].year;};
  const vector<TString> dataset_infilenames() const {return m_datasets[m_idx].infilenames;};
  const double  dataset_lumi() const {return m_datasets[m_idx].lumi;};
  const size_t  n_datasets()   const {return m_datasets.size();};
  const size_t  idx()          const {return m_idx;};

  void process_datasets();



  shared_ptr<TChain> event_chain;
  int nevt;
  TTree* outputtree;
  shared_ptr<TFile> outfile;

private:
  TString m_output_directory, m_se_director, m_postfix;
  string m_analysis_tool;
  double m_target_lumi;
  int m_nevt_max, m_nevt_skip;
  std::unordered_map<std::string, std::string> m_additionalvariables;
  std::vector<dataset> m_datasets = {};
  size_t m_idx = 0;
  bool m_is_init = false;

};
