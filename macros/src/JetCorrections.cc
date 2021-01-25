#include "include/JetCorrections.h"
#include "include/useful_functions.h"

using namespace std;




void JERCReader() {


}














JERCorrector::JERCorrector(Config cfg, TString ScaleFactorFileName, TString ResolutionFileName) {


  TString dir = (TString) cfg.get("JERDirection");
  if     (dir == "nominal") direction =  0;
  else if(dir == "up")      direction =  1;
  else if(dir == "down")    direction = -1;
  else throw std::runtime_error("JERCorrector::JERCorrector -- invalid value in config: JERDirection='"+dir+"' (valid: 'nominal', 'up', 'down')");

  //read in file for jet resolution (taken from https://github.com/cms-jet/JRDatabase/blob/master/textFiles/)
  // res = JME::JetResolution(locate_file(ResolutionFileName.Data()));
  // res_sf = JME::JetResolutionScaleFactor(locate_file(ScaleFactorFileName.Data()));
  res = JME::JetResolution("test.txt");
  res_sf = JME::JetResolutionScaleFactor("test.txt");

}



bool JERCorrector::process(RecoEvent & event){

  if(event.is_data) return true;
  apply_JER_smearing(*event.jets, *event.genjets, 0.4, event.rho);
  apply_JER_smearing(*event.jets, *event.genjets, 0.4, event.rho);
  return true;
}




void JERCorrector::apply_JER_smearing(std::vector<Jet>& rec_jets, const std::vector<GenJet>& gen_jets, float radius, float rho){

  // for(unsigned int i=0; i<rec_jets.size(); ++i){
  //
  //   Jet& jet = rec_jets.at(i);
  //
  //   LorentzVector jet_v4 = jet.v4();
  //   float recopt = jet_v4.pt();
  //   float recoeta = jet_v4.eta();
  //   float abseta = fabs(recoeta);
  //
  //   // find next genjet:
  //   auto closest_genjet = closestParticle(jet, gen_jets);
  //   float genpt = -1.;
  //
  //   // Get resolution for this jet:
  //   float resolution = resolution_.getResolution({{JME::Binning::JetPt, recopt}, {JME::Binning::JetEta, recoeta}, {JME::Binning::Rho, rho}});
  //
  //   // Resolution can be nan if bad formula parameters - check here
  //   // Generally this should be reported! This is a Bad Thing
  //   if (isnan(resolution)) {
  //     if (recopt < 35) { // leniency in this problematic region, hopefully fixed in future version of JER
  //       cout << "WARNING: getResolution() evaluated to nan. Since this jet is in problematic region, it will instead be set to 0." << endl;
  //       cout << "Input eta : rho : pt = " << recoeta << " : " << rho << ": " << recopt << endl;
  //       resolution = 0.;
  //     } else {
  //       throw std::runtime_error("getResolution() evaluated to nan. Input eta : rho : pt = " + double2string(recoeta) + " : " + double2string(rho) + " : " + double2string(recopt));
  //     }
  //   }
  //
  //   // Test if acceptable genjet match:
  //   // Ignore unmatched jets (= no genjets at all, or large DeltaR relative to jet radius),
  //   // or jets where the difference between recojet & genjet is much larger
  //   // than the expected resolution, or the genjet pt is too small.
  //   // These jets will instead be treated with the stochastic method.
  //   if(!(closest_genjet == nullptr) && uhh2::deltaR(*closest_genjet, jet) < 0.5*radius){
  //     genpt = closest_genjet->pt();
  //   }
  //   if( fabs(genpt-recopt) > 3*resolution*recopt){
  //     genpt=-1;
  //   }
  //   if(genpt < 15.0f) {
  //     genpt=-1.;
  //   }
  //
  //   // Get the scale factor for this jet
  //   float c = getScaleFactor(recopt, recoeta);
  //   if (c < 0) {
  //     std::cout << "WARNING: GenericJetResolutionSmearer: no scale factor found for this jet with pt : eta = " << recopt << " : " << recoeta << std::endl;
  //     std::cout << "         No JER smearing will be applied." << std::endl;
  //   }
  //
  //   // Calculate the new pt
  //   float new_pt = -1.;
  //   // Use scaling method in case a matching generator jet was found
  //   if(genpt>0){
  //     new_pt = std::max(0.0f, genpt + c * (recopt - genpt));
  //   }
  //   // Use stochastic method if no generator jet could be matched to the reco jet
  //   else{
  //     // Initialize random generator with eta-dependend random seed to be reproducible
  //     TRandom rand((int)(1000*abseta));
  //     float random_gauss = rand.Gaus(0, resolution);
  //     new_pt = recopt * (1 + random_gauss*sqrt(std::max(c*c-1, 0.0f)));
  //   }
  //   jet_v4 *= new_pt / recopt;
  //
  //   // Update JEC_factor_raw needed for smearing MET
  //   float factor_raw = jet.JEC_factor_raw();
  //   factor_raw *= recopt/new_pt;
  //
  //   jet.set_JEC_factor_raw(factor_raw);
  //   jet.set_v4(jet_v4);
  // }

  return;
}



float JERCorrector::getScaleFactor(float pt, float eta){
  // // Using the JERSmearing::SFtype1 structure
  // if (res_sf_.getResolutionObject() == nullptr) {
  //   // Check if there is a valid scale factor for this jet (i.e. jet is within bounds for parameters)
  //   int ieta(-1);
  //   float abseta = fabs(eta);
  //
  //   for(unsigned int idx=0; idx<JER_SFs_.size(); ++idx){
  //
  //     const float min_eta = idx ? JER_SFs_.at(idx-1).at(0) : 0.;
  //     const float max_eta =       JER_SFs_.at(idx)  .at(0);
  //
  //     if(min_eta <= abseta && abseta < max_eta){ ieta = idx; break; }
  //   }
  //   if(ieta < 0) {
  //     return -1.;
  //   }
  //
  //   // Get the scale factor for this jet
  //   float c = -1.;
  //   if (direction == 0) {
  //     c = JER_SFs_.at(ieta).at(1);
  //   } else if (direction == 1) {
  //     c = JER_SFs_.at(ieta).at(2);
  //   } else {
  //     c = JER_SFs_.at(ieta).at(3);
  //   }
  //
  //   return c;
  // }
  //
  // // Using the JetResolutionScaleFactor object
  // else {
  //   float c = -1;
  //   if (direction == 0) {
  //     c = res_sf_.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}});
  //   } else if (direction == 1) {
  //     c = res_sf_.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}}, Variation::UP);
  //   } else {
  //     c = res_sf_.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}}, Variation::DOWN);
  //   }
  //   return c;
  // }
}
