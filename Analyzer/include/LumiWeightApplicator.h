#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"


class LumiWeightApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit LumiWeightApplicator(const Config& cfg);
  virtual ~LumiWeightApplicator() = default;

  virtual bool process(RecoEvent & event) override;

protected:
  double m_targetlumi = -1.;
  double m_datasetlumi = -1.;
};
