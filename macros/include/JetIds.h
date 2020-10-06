#pragma once

#include "AnalysisModule.h"
#include "RecoEvent.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"


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
