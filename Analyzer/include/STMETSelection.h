#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class STMETSelection: public Selection<RecoEvent>{
public:
  explicit STMETSelection(const Config & cfg, double min_, double max_);
  virtual bool passes(RecoEvent & event) override;

private:
  double min, max;

};
