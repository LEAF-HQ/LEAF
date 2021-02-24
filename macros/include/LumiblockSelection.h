#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"

#include <vector>
// #include <pair>

class LumiblockSelection: public Selection<RecoEvent>{
 public:
  explicit LumiblockSelection(const Config & cfg);
  virtual bool passes(RecoEvent & event) override;

 private:
   std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>> runs_and_lbs;

};
