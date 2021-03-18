#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

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
