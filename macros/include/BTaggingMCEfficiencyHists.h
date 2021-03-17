#pragma once

#include <TString.h>
#include <TH2D.h>
#include <map>
#include "include/RecoEvent.h"
#include "include/BaseHists.h"
#include "include/JetIds.h"


class BTaggingMCEfficiencyHists: public BaseHists {
public:
  BTaggingMCEfficiencyHists(TString dir_, JetBTag::wp wp);
  BTaggingMCEfficiencyHists(const BTaggingMCEfficiencyHists &) = default;
  BTaggingMCEfficiencyHists & operator = (const BTaggingMCEfficiencyHists &) = default;
  void fill(const RecoEvent & event);

protected:

  JetBTag m_btagid;
  shared_ptr<TH2D> h_b_passing, h_b_total, h_c_passing, h_c_total, h_udsg_passing, h_udsg_total;
};
