#pragma once
#include "Analyzer/include/AnalysisModule.h"
#include "Analyzer/include/Config.h"
#include "Analyzer/include/useful_functions.h"
#include "Analyzer/include/constants.h"


class LumiWeightApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit LumiWeightApplicator(const Config& cfg);
  virtual ~LumiWeightApplicator() = default;

  virtual bool process(RecoEvent & event) override;

protected:
  double m_targetlumi = -1.;
  double m_datasetlumi = -1.;
};
