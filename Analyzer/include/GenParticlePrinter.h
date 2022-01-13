#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"

#include <vector>
// #include <pair>

class GenParticlePrinter: public AnalysisModule<RecoEvent>{
 public:
  explicit GenParticlePrinter(const Config & cfg);
  virtual bool process(RecoEvent & event) override;

};
