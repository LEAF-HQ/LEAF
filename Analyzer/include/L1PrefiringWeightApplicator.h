#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"


class L1PrefiringWeightApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit L1PrefiringWeightApplicator();
  virtual ~L1PrefiringWeightApplicator() = default;

  virtual bool process(RecoEvent & event) override;
};
