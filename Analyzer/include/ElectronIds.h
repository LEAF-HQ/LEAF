#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"


class ElectronID {
public:
  explicit ElectronID(Electron::Selector);
  bool operator()(const Electron&, const RecoEvent&) const;

private:
  Electron::Selector sel;
};

class ElectronIPID {
public:
  explicit ElectronIPID(float dmin_, float dmax_ = -1.);
  bool operator()(const Electron&, const RecoEvent&) const;

private:
  float dmin, dmax;
};
