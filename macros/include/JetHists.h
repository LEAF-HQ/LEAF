#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/RecoEvent.h"
#include "include/BaseHists.h"

using namespace std;

class JetHists : public BaseHists{

public:
  // Constructors, destructor
  JetHists(TString dir_);
  JetHists(const JetHists &) = default;
  JetHists & operator = (const JetHists &) = default;
  ~JetHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hnjets, hjet1pt, hjet1eta, hjet1phi, hjet1mass, hjet1energy, hjet2pt, hjet2eta, hjet2phi, hjet2mass, hjet2energy, hjet3pt, hjet3eta, hjet3phi, hjet3mass, hjet3energy, hjet4pt, hjet4eta, hjet4phi, hjet4mass, hjet4energy, hjet5pt, hjet5eta, hjet5phi, hjet5mass, hjet5energy;





};
