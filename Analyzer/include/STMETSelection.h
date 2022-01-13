#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class STMETSelection: public Selection<RecoEvent>{
public:
  explicit STMETSelection(const Config & cfg, double min_, double max_);
  virtual bool passes(RecoEvent & event) override;

private:
  double min, max;

};
