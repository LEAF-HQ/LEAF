#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"

using namespace std;

class EventHists : public BaseHists{

public:
  // Constructors, destructor
  EventHists(TString dir_);
  EventHists(const EventHists &) = default;
  EventHists & operator = (const EventHists &) = default;
  ~EventHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hmetpt, hmetphi, hisdata, hnpv, hnpv_good, hnpu, hntrueint, hweight_prefiring, hweight_prefiring_up, hweight_prefiring_down, hweight, hsumweights;

};
