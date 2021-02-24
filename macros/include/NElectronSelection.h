#pragma once

#include "include/Config.h"
#include "include/Selection.h"
#include "include/RecoEvent.h"
#include "include/ObjectIdUtils.h"

#include <vector>
// #include <pair>

class NElectronSelection: public Selection<RecoEvent>{
public:
  explicit NElectronSelection(const Config & cfg, int nmin_, int nmax_);
  explicit NElectronSelection(const Config & cfg, int nmin_, int nmax_, ID<Electron> id_);
  virtual bool passes(RecoEvent & event) override;

private:
  int nmin, nmax;
  ID<Electron> id;

};
