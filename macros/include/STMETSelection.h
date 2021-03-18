#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class STMETSelection: public Selection<RecoEvent>{
public:
  explicit STMETSelection(const Config & cfg, double min_, double max_);
  virtual bool passes(RecoEvent & event) override;

private:
  double min, max;

};
