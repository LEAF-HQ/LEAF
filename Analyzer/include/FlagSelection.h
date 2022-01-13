#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class FlagSelection: public Selection<RecoEvent>{
public:
  explicit FlagSelection(const Config & cfg, TString flagname_);
  virtual bool passes(RecoEvent & event) override;

private:
  TString flagname;

};
