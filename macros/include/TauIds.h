#pragma once

#include "AnalysisModule.h"
#include "RecoEvent.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"


class TauID {
public:
  explicit TauID(Tau::Selector);
  bool operator()(const Tau&, const RecoEvent&) const;

private:
  Tau::Selector sel;
};
