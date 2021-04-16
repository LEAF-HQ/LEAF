#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

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

  shared_ptr<TH1D> hntaus, hnmatchedtaus, htaupt, htaueta, htauphi, htaumass, htauenergy, htaugendrmin, htaugenstatus, htau1pt, htau1eta, htau1phi, htau1mass, htau1energy, htau1gendrmin, htau1genstatus, htau2pt, htau2eta, htau2phi, htau2mass, htau2energy, htau2gendrmin, htau2genstatus, htau3pt, htau3eta, htau3phi, htau3mass, htau3energy, htau3gendrmin, htau3genstatus, htau4pt, htau4eta, htau4phi, htau4mass, htau4energy, htau4gendrmin, htau4genstatus;





};
