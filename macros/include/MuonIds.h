#pragma once

#include "AnalysisModule.h"
#include "RecoEvent.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"


class MuonID {
public:
  explicit MuonID(Muon::Selector);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  Muon::Selector sel;
};
