#pragma once
#include "include/AnalysisModule.h"
#include "include/useful_functions.h"
#include "include/constants.h"
#include "include/ObjectIdUtils.h"
#include "include/Jet.h"
#include "include/GenJet.h"
#include "include/Config.h"

#include <TRandom.h>
#include <string>


#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#pragma GCC diagnostic pop



class JECCorrector: public AnalysisModule<RecoEvent> {
public:
  explicit JECCorrector(const Config& cfg, const TString& year_, const TString& jetcollection_);
  virtual ~JECCorrector() = default;

  virtual bool process(RecoEvent & event) override;
  virtual bool correct_met(RecoEvent & event, double pt_thresh = 15.);

protected:
  std::map<TString, std::unique_ptr<FactorizedJetCorrector>> correctors;
  std::map<TString, std::unique_ptr<JetCorrectionUncertainty>> jec_uncertainties;
  int direction = 0; // -1 = down, +1 = up, 0 = nominal
  TString year, jetcollection;
};



class JetLeptonCleaner: public AnalysisModule<RecoEvent> {

public:
  explicit JetLeptonCleaner(const Config& cfg, const TString& year_, const TString& jetcollection_);
  virtual ~JetLeptonCleaner() = default;

  virtual bool process(RecoEvent & event) override;
  void set_muon_id(const ID<Muon> & mu_id){m_mu_id = mu_id;}
  void set_electron_id(const ID<Electron> & ele_id){m_ele_id = ele_id;}

protected:
  std::map<TString, std::unique_ptr<FactorizedJetCorrector>> correctors;
  std::map<TString, std::unique_ptr<JetCorrectionUncertainty>> jec_uncertainties;
  int direction = 0; // -1 = down, +1 = up, 0 = nominal
  TString year, jetcollection;
  ID<Muon> m_mu_id;
  ID<Electron> m_ele_id;
};



class JERCorrector : public AnalysisModule<RecoEvent> {

public:
  explicit JERCorrector(Config cfg, TString ScaleFactorFileName="", TString ResolutionFileName="");
  virtual ~JERCorrector() = default;
  virtual bool process(RecoEvent & event) override;

private:
  virtual float getScaleFactor(float pt, float eta);
  void apply_JER_smearing(std::vector<Jet>&, const std::vector<GenJet>&, float radius, float rho);

  int direction = 0; // -1 = down, +1 = up, 0 = nominal
  JME::JetResolution res;
  JME::JetResolutionScaleFactor res_sf;
};
