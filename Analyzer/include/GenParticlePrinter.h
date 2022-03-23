#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"

#include <vector>
// #include <pair>

class GenParticlePrinter: public AnalysisModule<RecoEvent>{
public:
  explicit GenParticlePrinter(const Config & cfg, bool do_allgenparticles_ = false);
  virtual bool process(RecoEvent & event) override;

protected:
  bool do_allgenparticles;
  vector<GenParticle>* genparticles;

};
