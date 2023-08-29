#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"
//#include <string>


class MuonID {
public:
  explicit MuonID(Muon::Selector);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  Muon::Selector sel;
};

class MuonIPID {
public:
  explicit MuonIPID(float dmin_, float dmax_ = -1.);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  float dmin, dmax;
};

class MuonDxyID {
public:
  explicit MuonDxyID(float dxymin_, float dmax_ = -1.);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  float dmin, dmax;
};

class MuonDzID {
public:
  explicit MuonDzID(float dxymin_, float dmax_ = -1.);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  float dmin, dmax;
};

class MuonIso {
public:
  explicit MuonIso(float dmin_, std::string isoname_);
  bool operator()(const Muon&, const RecoEvent&) const;

private:
  float min_iso;
  std::string isolation_name;
};