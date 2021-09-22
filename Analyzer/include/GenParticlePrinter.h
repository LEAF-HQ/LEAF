#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"

#include <vector>
// #include <pair>

class GenParticlePrinter: public AnalysisModule<RecoEvent>{
 public:
  explicit GenParticlePrinter(const Config & cfg);
  virtual bool process(RecoEvent & event) override;

};
