#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

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
