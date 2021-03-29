#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

using namespace std;

class GenParticleHists : public BaseHists{

public:
  // Constructors, destructor
  GenParticleHists(TString dir_);
  GenParticleHists(const GenParticleHists &) = default;
  GenParticleHists & operator = (const GenParticleHists &) = default;
  ~GenParticleHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hngentaus, hptgentau1, hptgentau2, hptgentau1_rebin, hptgentau2_rebin, hptgentau1_rebin2, hptgentau2_rebin2, hptgentau1_rebin3, hptgentau2_rebin3;





};
