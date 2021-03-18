#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

#include <vector>

class METSelection: public Selection<RecoEvent>{
public:
  explicit METSelection(const Config & cfg, double min_, double max_);
  virtual bool passes(RecoEvent & event) override;

private:
  double min, max;

};
