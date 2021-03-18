#pragma once

#include "Analyzer/include/Config.h"
#include "Analyzer/include/Selection.h"
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/ObjectIdUtils.h"

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
