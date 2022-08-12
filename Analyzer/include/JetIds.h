#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"


class JetID {
public:
  enum wp {WP_TIGHT};
  explicit JetID(wp working_point);
  bool operator()(const Jet&, const RecoEvent&) const;
private:
  wp m_wp;
};

class JetPUID {
public:
  enum wp {WP_TIGHT};
  explicit JetPUID(wp working_point);
  bool operator()(const Jet&, const RecoEvent&) const;
private:
  wp m_wp;
};


class JetBTag {
public:
  enum wp {DeepJet_Loose=0, DeepJet_Medium=1, DeepJet_Tight=2}; // needs to be in sync with BTagCalibrationStandalone.h's "enum OperatingPoint", so hard-code enums to be sure
  explicit JetBTag(wp working_point);
  bool operator()(const Jet&, const RecoEvent&) const;
  int get_wp(){return (int)m_wp;};
private:
  wp m_wp;
};

class JetTauOverlapID {
public:
  explicit JetTauOverlapID(double dr);
  bool operator()(const Jet&, const RecoEvent&) const;
private:
  double m_dr;
};

class JetLeptonOverlapID {
public:
  explicit JetLeptonOverlapID(double dr);
  bool operator()(const Jet&, const RecoEvent&) const;
private:
  double m_dr;
};

class GenJetLeptonOverlapID {
public:
  explicit GenJetLeptonOverlapID(double dr);
  bool operator()(const GenJet&, const GenEvent&) const;
private:
  double m_dr;
};
