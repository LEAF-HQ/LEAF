#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"


class TauID {
public:
  explicit TauID(Tau::Selector);
  bool operator()(const Tau&, const RecoEvent&) const;

private:
  Tau::Selector sel;
};

class TauDecaymodeID {
public:
  explicit TauDecaymodeID(std::vector<int>);
  bool operator()(const Tau&, const RecoEvent&) const;

private:
  std::vector<int> decaymodes;
};

class TauDecaymodeVetoID {
public:
  explicit TauDecaymodeVetoID(std::vector<int>);
  bool operator()(const Tau&, const RecoEvent&) const;

private:
  std::vector<int> decaymodes;
};
