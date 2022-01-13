#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"

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
