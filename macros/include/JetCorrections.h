#pragma once
#include "include/AnalysisModule.h"
#include "include/useful_functions.h"
#include "include/constants.h"
#include "include/Jet.h"
#include "include/GenJet.h"
#include "include/Config.h"


// #include "CondFormats/JetMETObjects/interface/JetResolution.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"


class JERCorrector : public AnalysisModule<RecoEvent> {
public:
    JERCorrector(const double & mindr_);
    explicit JERCorrector(Config cfg, TString ScaleFactorFileName="", TString ResolutionFileName="Fall17_V3_MC_PtResolution_AK4PFchs.txt");
    virtual ~JERCorrector() = default;
    virtual bool process(RecoEvent & event) override;

private:
    virtual float getScaleFactor(float pt, float eta);
    void apply_JER_smearing(std::vector<Jet>&, const std::vector<GenJet>&, float radius, float rho);

     int direction = 0; // -1 = down, +1 = up, 0 = nominal
     JME::JetResolution res;
     JME::JetResolutionScaleFactor res_sf;
};
