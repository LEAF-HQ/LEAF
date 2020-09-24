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
