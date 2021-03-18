#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class NMuonSelection: public Selection<RecoEvent>{
public:
  explicit NMuonSelection(const Config & cfg, int nmin_, int nmax_);
  explicit NMuonSelection(const Config & cfg, int nmin_, int nmax_, ID<Muon> id_);
  virtual bool passes(RecoEvent & event) override;

private:
  int nmin, nmax;
  ID<Muon> id;

};
