#pragma once

#include "Analyzer/include/AnalysisModule.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"
#include "Analyzer/include/useful_functions.h"


class MuonID {
public:
  explicit MuonID(Muon::Selector);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  Muon::Selector sel;
};

class MuonIPID {
public:
  explicit MuonIPID(float dmin_, float dmax_ = -1.);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  float dmin, dmax;
};
