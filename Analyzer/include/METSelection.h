#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

#include <vector>

class METSelection: public Selection<RecoEvent>{
public:
  explicit METSelection(const Config & cfg, double min_, double max_);
  virtual bool passes(RecoEvent & event) override;

private:
  double min, max;

};
