#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class FlagSelection: public Selection<RecoEvent>{
public:
  explicit FlagSelection(const Config & cfg, TString flagname_);
  virtual bool passes(RecoEvent & event) override;

private:
  TString flagname;

};
