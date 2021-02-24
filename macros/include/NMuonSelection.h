#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

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
