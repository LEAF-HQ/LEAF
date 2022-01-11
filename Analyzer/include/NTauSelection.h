#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class NTauSelection: public Selection<RecoEvent>{
public:
  explicit NTauSelection(const Config & cfg, int nmin_, int nmax_);
  explicit NTauSelection(const Config & cfg, int nmin_, int nmax_, ID<Tau> id_);
  virtual bool passes(RecoEvent & event) override;

private:
  int nmin, nmax;
  ID<Tau> id;

};
