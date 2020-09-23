#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/RecoEvent.h"
#include "include/BaseHists.h"

using namespace std;

class TauHists : public BaseHists{

public:
  // Constructors, destructor
  TauHists(TString dir_);
  TauHists(const TauHists &) = default;
  TauHists & operator = (const TauHists &) = default;
  ~TauHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hntaus, htau1pt, htau1eta, htau1phi, htau1mass, htau1energy, htau2pt, htau2eta, htau2phi, htau2mass, htau2energy, htau3pt, htau3eta, htau3phi, htau3mass, htau3energy, htau4pt, htau4eta, htau4phi, htau4mass, htau4energy;





};
