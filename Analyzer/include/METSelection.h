#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class METSelection: public Selection<RecoEvent>{
public:
  explicit METSelection(const Config & cfg, float min_, float max_);
  virtual bool passes(RecoEvent & event) override;

private:
  float min, max;

};
