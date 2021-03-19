#include "Analyzer/include/JetCorrections.h"
#include "Analyzer/include/useful_functions.h"


using namespace std;


unique_ptr<JetCorrectionUncertainty> corrector_uncertainty(const Config & cfg, const vector<string> & filenames, const int& direction){

  //initialize JetCorrectionUncertainty if shift direction is not "nominal", else return NULL pointer
  if(direction!=0){

    //take name from the L1FastJet correction (0th element of filenames) and replace "L1FastJet" by "UncertaintySources" to get the proper name of the uncertainty file
    TString macropath = (TString)getenv("ANALYZERPATH"); // set up by setup.sh
    TString unc_file = (TString)(macropath + "/" + filenames[0]);
    if (unc_file.Contains("L1FastJet")) {
      unc_file.ReplaceAll("L1FastJet","UncertaintySources");
    }
    else if (unc_file.Contains("L2Relative")) {
      unc_file.ReplaceAll("L2Relative","UncertaintySources");
    }
    else {
      throw runtime_error("WARNING No JEC Uncertainty File found!");
    }
    return unique_ptr<JetCorrectionUncertainty>(new JetCorrectionUncertainty(*(new JetCorrectorParameters(unc_file.Data(), "Total"))));
  }
  return nullptr;

}

unique_ptr<FactorizedJetCorrector> build_corrector(const vector<string>& filenames){
  string macropath = (string)getenv("ANALYZERPATH"); // set up by setup.sh

  vector<JetCorrectorParameters> pars;
  for(const auto & filename : filenames){
    pars.emplace_back((string)(macropath + "/" + filename));
  }
  return make_unique<FactorizedJetCorrector>(pars);
}

void correct_jet(FactorizedJetCorrector & corrector, Jet & jet, const RecoEvent & event, JetCorrectionUncertainty & jec_unc, int jec_unc_direction){
  double raw_factor = jet.raw_factor();

  corrector.setJetPt(jet.pt() * raw_factor);
  corrector.setJetEta(jet.eta());
  corrector.setJetE(jet.e() * raw_factor);
  corrector.setJetPhi(jet.phi());
  corrector.setJetA(jet.area());
  corrector.setRho(event.rho);
  auto correctionfactors    = corrector.getSubCorrections();
  auto correctionfactor     = correctionfactors.back();
  auto correctionfactor_L1  = correctionfactors.front();

  // un-correct and the re-correct the jet with chosen JECs
  TLorentzVector jet_p4_corrected = jet.p4() * (raw_factor * correctionfactor);

  // check if correction needs to be shifted up or down
  if(jec_unc_direction != 0){

    // ignore jets with very low pt or high eta, avoiding a crash from the JESUncertainty tool
    double pt = jet_p4_corrected.Pt();
    double eta = jet_p4_corrected.Eta();
    if (!(pt<5. || fabs(eta)>5.)) {

      jec_unc.setJetEta(eta);
      jec_unc.setJetPt(pt);

      double unc = 0.;
      if (jec_unc_direction == 1){ // shift up
        unc = jec_unc.getUncertainty(true);
        correctionfactor *= (1 + fabs(unc));
      }
      else if (jec_unc_direction == -1){ // shift down
        unc = jec_unc.getUncertainty(false);
        correctionfactor *= (1 - fabs(unc));
      }
      else throw runtime_error("JEC 'direction' is != 0, but not 1 or -1. Other values should not happen. Abort.");

      // overwrite corrected jet p4
      jet_p4_corrected = jet.p4() * (raw_factor * correctionfactor);
    }
  }

  // set corrected jet p4
  jet.set_p4(jet_p4_corrected);
  jet.set_raw_factor(1. / correctionfactor);
  jet.set_L1_factor(correctionfactor_L1); // does not exist in NanoAOD
}


JECCorrector::JECCorrector(const Config& cfg, const TString & year_, const TString & jetcollection_) : year(year_), jetcollection(jetcollection_){

  int direction = 0;
  TString dir = (TString) cfg.get("JECDirection");
  if     (dir == "nominal") direction =  0;
  else if(dir == "up")      direction =  1;
  else if(dir == "down")    direction = -1;
  else throw std::runtime_error("JECCorrector::JECCorrector -- invalid value in config: JECDirection='"+dir+"' (valid: 'nominal', 'up', 'down')");

  for (const TString run: yearRunMap.at((string)year)) {
    correctors[run] = build_corrector(JERCFiles("JEC", run, JERC.at((string)year).at("JEC"), (string)jetcollection));
    jec_uncertainties[run] = corrector_uncertainty(cfg, JERCFiles("JEC", run, JERC.at((string)year).at("JEC"), (string)jetcollection), direction) ;
  }
  correctors["MC"] = build_corrector(JERCFiles("JEC", "MC", JERC.at((string)year).at("JEC"), (string)jetcollection));
  jec_uncertainties["MC"] = corrector_uncertainty(cfg, JERCFiles("JEC", "MC", JERC.at((string)year).at("JEC"), (string)jetcollection), direction) ;

}



//propagate JEC to MET (L123 - L1 scheme) = type-1 correction
bool JECCorrector::correct_met(RecoEvent & event, double pt_thresh){

  // we start from raw MET
  TLorentzVector rawmet_p4 = event.rawmet->p4();
  for(Jet & jet : *event.jets){

    //thresholds on the corrected jets: pt > 15 EM fraction < 0.9
    if((jet.pt() > pt_thresh) && ((jet.ne_em_efrac() + jet.ch_em_efrac()) < 0.9)){

      // subtracting something from the p4 is actually adding it to MET, which is defined as the negative vectorial sum of everything
      rawmet_p4 -= jet.p4();
      rawmet_p4 += (jet.raw_factor() * jet.L1_factor()) * jet.p4();
    }
  }
  event.met->set_pt(rawmet_p4.Pt());
  event.met->set_phi(rawmet_p4.Phi());
  return true;
}



bool JECCorrector::process(RecoEvent& event){

  // Find correct run-period of event using event.run, either 'MC' or 'A' or 'B' or ....
  TString runperiod = event.get_runperiod(year);
  if(direction != 0 && jec_uncertainties.at(runperiod) == nullptr) throw runtime_error("JEC variation should be applied, but JEC uncertainty object is NULL. Abort.");

  //apply jet corrections
  for(Jet & jet : *event.jets){
    correct_jet(*correctors.at(runperiod), jet, event, *jec_uncertainties.at(runperiod), direction);
  }

  return true;
}










JetLeptonCleaner::JetLeptonCleaner(const Config& cfg, const TString& year_, const TString & jetcollection_) : year(year_), jetcollection(jetcollection_){

  direction = 0;
  TString dir = (TString) cfg.get("JECDirection");
  if     (dir == "nominal") direction =  0;
  else if(dir == "up")      direction =  1;
  else if(dir == "down")    direction = -1;
  else throw std::runtime_error("JECCorrector::JECCorrector -- invalid value in config: JECDirection='"+dir+"' (valid: 'nominal', 'up', 'down')");

  for (const TString run: yearRunMap.at((string)year)) {
    correctors[run] = build_corrector(JERCFiles("JEC", run, JERC.at((string)year).at("JEC"), (string)jetcollection));
    jec_uncertainties[run] = corrector_uncertainty(cfg, JERCFiles("JEC", run, JERC.at((string)year).at("JEC"), (string)jetcollection), direction) ;
  }
  correctors["MC"] = build_corrector(JERCFiles("JEC", "MC", JERC.at((string)year).at("JEC"), (string)jetcollection));
  jec_uncertainties["MC"] = corrector_uncertainty(cfg, JERCFiles("JEC", "MC", JERC.at((string)year).at("JEC"), (string)jetcollection), direction) ;

}


bool JetLeptonCleaner::process(RecoEvent& event) {

  TString runperiod = event.get_runperiod(year);
  for(Jet & jet : *event.jets){
    bool correct_p4 = false;
    TLorentzVector jet_p4_raw = jet.p4() * jet.raw_factor();

    // muons
    if(jet.n_muons() > 0 && event.muons->size() > 0){

      // find muon(s) and remove
      for(Muon & muo : *event.muons){
        if((m_mu_id && !m_mu_id(muo, event)) || (jet.identifier() != muo.jetidx())) continue;
        correct_p4 = true;
        jet_p4_raw -= muo.p4();
        jet.set_n_muons(jet.n_muons() - 1);
        jet.set_mu_efrac(max(0., (jet.e() * jet.mu_efrac() - muo.e()) / jet.e()));
      }
    }

    // electrons
    if(jet.n_electrons() > 0 && event.electrons->size() > 0){

      // find electron(s) and remove
      for(Electron & ele : *event.electrons){
        if((m_ele_id && !m_ele_id(ele, event)) || (jet.identifier() != ele.jetidx())) continue;
        correct_p4 = true;
        jet_p4_raw -= ele.p4();
        jet.set_n_electrons(jet.n_electrons() - 1);
        jet.set_ch_em_efrac(max(0., (jet.e() * jet.ch_em_efrac() - ele.e()) / jet.e()));
      }
    }

    // jet-p4 correction with JEC
    if(correct_p4){
      jet.set_raw_factor(1.);
      jet.set_p4(jet_p4_raw);
      correct_jet(*correctors.at(runperiod), jet, event, *jec_uncertainties.at(runperiod), direction);
    }
  }

  return true;
}















JERCorrector::JERCorrector(Config cfg, TString ScaleFactorFileName, TString ResolutionFileName) {

  TString dir = (TString) cfg.get("JERDirection");
  if     (dir == "nominal") direction =  0;
  else if(dir == "up")      direction =  1;
  else if(dir == "down")    direction = -1;
  else throw std::runtime_error("JERCorrector::JERCorrector -- invalid value in config: JERDirection='"+dir+"' (valid: 'nominal', 'up', 'down')");

  //read in file for jet resolution (taken from https://github.com/cms-jet/JRDatabase/blob/master/textFiles/)
  TString macropath = (TString)getenv("ANALYZERPATH"); // set up by setup.sh
  res = JME::JetResolution((string)(macropath + "/" + ResolutionFileName));
  res_sf = JME::JetResolutionScaleFactor((string)(macropath + "/" + ScaleFactorFileName));

}

bool JERCorrector::process(RecoEvent & event){

  if(event.is_data) return true;
  apply_JER_smearing(*event.jets, *event.genjets, 0.4, event.rho);
  return true;

}




void JERCorrector::apply_JER_smearing(std::vector<Jet>& rec_jets, const std::vector<GenJet>& gen_jets, float radius, float rho){

  for(unsigned int i=0; i<rec_jets.size(); ++i){

    Jet& jet = rec_jets.at(i);
    float recopt = jet.pt();
    float recoeta = jet.eta();
    float abseta = fabs(recoeta);

    // find next genjet:
    auto closest_genjet = closestParticle(jet, gen_jets);
    float genpt = -1.;

    // Get resolution for this jet:
    float resolution = res.getResolution({{JME::Binning::JetPt, recopt}, {JME::Binning::JetEta, recoeta}, {JME::Binning::Rho, rho}});

    // Resolution can be nan if bad formula parameters - check here
    // Generally this should be reported! This is a Bad Thing
    if (isnan(resolution)){
      if (recopt < 35){ // leniency in this problematic region, hopefully fixed in future version of JER
        cout << "WARNING: getResolution() evaluated to nan. Since this jet is in problematic region, it will instead be set to 0." << endl;
        cout << "Input eta : rho : pt = " << recoeta << " : " << rho << ": " << recopt << endl;
        resolution = 0.;
      }
      else{
        TString errormessage = "getResolution() evaluated to nan. Input eta : rho : pt = ";
        errormessage += recoeta;
        errormessage += " : ";
        errormessage += rho;
        errormessage += " : ";
        errormessage += recopt;
        throw runtime_error(errormessage);
      }
    }

    // Test if acceptable genjet match:
    // Ignore unmatched jets (= no genjets at all, or large DeltaR relative to jet radius),
    // or jets where the difference between recojet & genjet is much larger
    // than the expected resolution, or the genjet pt is too small.
    // These jets will instead be treated with the stochastic method.
    if(!(closest_genjet == nullptr) && deltaR(*closest_genjet, jet) < 0.5*radius){
      genpt = closest_genjet->pt();
    }
    if( fabs(genpt-recopt) > 3*resolution*recopt){
      genpt=-1;
    }
    if(genpt < 15.0f) {
      genpt=-1.;
    }

    // Get the scale factor for this jet
    float c = getScaleFactor(recopt, recoeta);
    if (c < 0) {
      cout << "WARNING: JERCorrector: no scale factor found for this jet with pt : eta = " << recopt << " : " << recoeta << endl;
      cout << "         No JER smearing will be applied." << endl;
    }

    // Calculate the new pt
    float new_pt = -1.;
    // Use scaling method in case a matching generator jet was found
    if(genpt>0){
      new_pt = std::max(0.0f, genpt + c * (recopt - genpt));
    }

    // Use stochastic method if no generator jet could be matched to the reco jet
    else{
      // Initialize random generator with eta-dependend random seed to be reproducible
      TRandom rand((int)(1000*abseta));
      float random_gauss = rand.Gaus(0, resolution);
      new_pt = recopt * (1 + random_gauss*sqrt(max(c*c-1, 0.0f)));
    }

    // scale the jet
    TLorentzVector jet_p4 = jet.p4();
    jet_p4 *= new_pt / recopt;

    // Update JEC_raw_factor needed for smearing MET
    float raw_factor = jet.raw_factor();
    raw_factor *= recopt/new_pt;

    jet.set_raw_factor(raw_factor);
    jet.set_p4(jet_p4);
  }

  return;
}



float JERCorrector::getScaleFactor(float pt, float eta){
  float c = -1;
  if (direction == 0) {
    c = res_sf.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}});
  } else if (direction == 1) {
    c = res_sf.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}}, Variation::UP);
  } else {
    c = res_sf.getScaleFactor({{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}}, Variation::DOWN);
  }
  return c;
}
