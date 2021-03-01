#pragma once
#include "include/AnalysisModule.h"
#include "include/Config.h"
#include "include/useful_functions.h"
#include "include/constants.h"


class LumiWeightApplicator: public AnalysisModule<RecoEvent> {
public:
  explicit LumiWeightApplicator(const Config& cfg);
  virtual ~LumiWeightApplicator() = default;

  virtual bool process(RecoEvent & event) override;

protected:
  double m_targetlumi = -1.;
  double m_datasetlumi = -1.;
};
