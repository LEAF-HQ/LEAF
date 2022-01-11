#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class NJetSelection: public Selection<RecoEvent>{
public:
  explicit NJetSelection(const Config & cfg, int nmin_, int nmax_);
  explicit NJetSelection(const Config & cfg, int nmin_, int nmax_, ID<Jet> id_);
  virtual bool passes(RecoEvent & event) override;

private:
  int nmin, nmax;
  ID<Jet> id;

};
