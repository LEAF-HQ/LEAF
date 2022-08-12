#pragma once

#include <TString.h>
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/FlagSelection.h"


#include <vector>
// #include <pair>

class METFilterSelection: public Selection<RecoEvent>{
 public:
  explicit METFilterSelection(const Config & cfg, TString year);
  virtual bool passes(RecoEvent & event) override;

 private:
  std::vector<TString> metfilternames;
  std::vector<std::unique_ptr<FlagSelection>> flag_selections;

};
