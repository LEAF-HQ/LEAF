#pragma once

#include "LEAF/Analyzer/include/BTagCalibrationStandalone.h"
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Jet.h"
#include "LEAF/Analyzer/include/JetIds.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include <TH1D.h>
#include <TH2D.h>



class BTagCalibrationReader;  // forward declaration

class BTaggingScaleFactorApplicator: public AnalysisModule<RecoEvent>{
public:
  explicit BTaggingScaleFactorApplicator(const Config& cfg, JetBTag::wp wp, const TString & sysType="central", const std::string & measType_bc="comb", const std::string & measType_udsg="incl");
  virtual ~BTaggingScaleFactorApplicator() = default;
  virtual bool process(RecoEvent & event) override;

protected:
  std::tuple<double, double, double> get_weight_btag(const std::vector<Jet> jets, RecoEvent & event);
  std::pair<double, double> get_SF_btag(double pt, double abs_eta, int flav);

  std::unique_ptr<TFile> m_f_efficiencies;
  std::unique_ptr<TH2D> m_eff_b;
  std::unique_ptr<TH2D> m_eff_c;
  std::unique_ptr<TH2D> m_eff_udsg;
  JetBTag m_btagid;
  std::unique_ptr<BTagCalibrationReader> m_calib_up;
  std::unique_ptr<BTagCalibrationReader> m_calib_nominal;
  std::unique_ptr<BTagCalibrationReader> m_calib_down;
  TString m_sysType;
};
