#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

using namespace std;

class PreselectionHists : public BaseHists{

public:
  // Constructors, destructor
  PreselectionHists(TString dir_);
  PreselectionHists(const PreselectionHists &) = default;
  PreselectionHists & operator = (const PreselectionHists &) = default;
  ~PreselectionHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hmetpt, hmetphi, hsumweights;

};
