#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class METSelection: public Selection<RecoEvent>{
public:
  explicit METSelection(const Config & cfg, float min_, float max_);
  virtual bool passes(RecoEvent & event) override;

private:
  float min, max;

};
