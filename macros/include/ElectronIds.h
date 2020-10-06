#pragma once

#include "AnalysisModule.h"
#include "RecoEvent.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"


class ElectronID {
public:
  explicit ElectronID(Electron::Selector);
  bool operator()(const Electron&, const RecoEvent&) const;

private:
  Electron::Selector sel;
};
