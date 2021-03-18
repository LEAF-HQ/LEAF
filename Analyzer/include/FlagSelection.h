#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class FlagSelection: public Selection<RecoEvent>{
public:
  explicit FlagSelection(const Config & cfg, TString flagname_);
  virtual bool passes(RecoEvent & event) override;

private:
  TString flagname;

};
