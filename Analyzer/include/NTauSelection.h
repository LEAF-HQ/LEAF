#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

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
