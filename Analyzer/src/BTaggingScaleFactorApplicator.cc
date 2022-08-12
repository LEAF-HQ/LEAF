#include "LEAF/Analyzer/include/BTaggingScaleFactorApplicator.h"

using namespace std;

BTaggingScaleFactorApplicator::BTaggingScaleFactorApplicator(const Config& cfg, JetBTag::wp wp, const TString & sysType, const std::string & measType_bc, const std::string & measType_udsg) : m_btagid(wp), m_sysType(sysType) {


  TString leafpath = (TString)getenv("LEAFPATH"); // set up by setup.sh
  TString infilename_mceff = leafpath + "/" + cfg.get("BTaggingMCEfficiencies");
  m_f_efficiencies.reset(new TFile(infilename_mceff, "READ"));
  m_eff_b.reset((TH2D*) m_f_efficiencies->Get("b_efficiency"));
  m_eff_c.reset((TH2D*) m_f_efficiencies->Get("c_efficiency"));
  m_eff_udsg.reset((TH2D*) m_f_efficiencies->Get("udsg_efficiency"));

  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagCalibration
  TString infilename_sfs = leafpath + "/" + cfg.get("BTaggingScaleFactors");
  BTagCalibration calib_data((string)infilename_sfs);
  BTagEntry::OperatingPoint op = (BTagEntry::OperatingPoint)m_btagid.get_wp();

  m_calib_up.reset(new BTagCalibrationReader(op, "up"));
  m_calib_nominal.reset(new BTagCalibrationReader(op, "central"));
  m_calib_down.reset(new BTagCalibrationReader(op, "down"));

  m_calib_up->load(calib_data, BTagEntry::FLAV_B, measType_bc);
  m_calib_up->load(calib_data, BTagEntry::FLAV_C, measType_bc);
  m_calib_up->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
  m_calib_nominal->load(calib_data, BTagEntry::FLAV_B, measType_bc);
  m_calib_nominal->load(calib_data, BTagEntry::FLAV_C, measType_bc);
  m_calib_nominal->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
  m_calib_down->load(calib_data, BTagEntry::FLAV_B, measType_bc);
  m_calib_down->load(calib_data, BTagEntry::FLAV_C, measType_bc);
  m_calib_down->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
}

bool BTaggingScaleFactorApplicator::process(RecoEvent & event) {

  if(event.is_data) return true;
  if(!m_calib_nominal) return true;

  double weight, weightErrBC, weightErrUDSG;
  tie(weight, weightErrBC, weightErrUDSG) = get_weight_btag(*event.jets_ak4chs, event);
  double weightErr = sqrt(weightErrBC*weightErrBC + weightErrUDSG*weightErrUDSG);

  double weight_up        = weight + weightErr;
  double weight_down      = weight - weightErr;
  double weight_bc_up     = weight + weightErrBC;
  double weight_bc_down   = weight - weightErrBC;
  double weight_udsg_up   = weight + weightErrUDSG;
  double weight_udsg_down = weight - weightErrUDSG;

  if (m_sysType == "up")             event.weight *= weight_up;
  else if (m_sysType == "down")      event.weight *= weight_down;
  else if (m_sysType == "up_bc")     event.weight *= weight_bc_up;
  else if (m_sysType == "down_bc")   event.weight *= weight_bc_down;
  else if (m_sysType == "up_udsg")   event.weight *= weight_udsg_up;
  else if (m_sysType == "down_udsg") event.weight *= weight_udsg_down;
  else                               event.weight *= weight;

  return true;
}


// originally taken from https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
tuple<double, double, double> BTaggingScaleFactorApplicator::get_weight_btag(const vector<Jet> jets, RecoEvent & event) {

  double mcTag = 1.;
  double mcNoTag = 1.;
  double dataTag = 1.;
  double dataNoTag = 1.;

  double err1 = 0.;
  double err2 = 0.;
  double err3 = 0.;
  double err4 = 0.;

  //Here we loop over all selected jets
  for (const Jet & jet : jets) {

    int hadronFlavor = abs(jet.hadron_flavor());
    double abs_eta = fabs(jet.eta());
    double pt = jet.pt();

    if(abs_eta > 2.4) {
      continue;
    }

    TH2D* eff_hist;
    if (hadronFlavor == 5)    eff_hist = m_eff_b.get();
    else if( hadronFlavor==4) eff_hist = m_eff_c.get();
    else                      eff_hist = m_eff_udsg.get();
    const auto eff_pt_axis = eff_hist->GetXaxis();

    float pt_low_edge = eff_pt_axis->GetBinLowEdge(eff_pt_axis->GetFirst());
    float pt_high_edge = eff_pt_axis->GetBinUpEdge(eff_pt_axis->GetLast());
    float pt_for_eff = (pt > pt_low_edge) ? pt : pt_low_edge + 1.;
    pt_for_eff = (pt_for_eff < pt_high_edge) ? pt_for_eff : pt_high_edge - 1.;
    float eff = eff_hist->GetBinContent(eff_hist->FindFixBin(pt_for_eff, abs_eta));

    double SF = 1., SFerr = 0.;
    tie(SF, SFerr) = get_SF_btag(pt, abs_eta, hadronFlavor);

    if(m_btagid(jet, event)){
      mcTag *= eff;
      dataTag *= eff*SF;

      if(hadronFlavor==5 || hadronFlavor ==4)  err1 += SFerr/SF; ///correlated for b/c
      else err3 += SFerr/SF; //correlated for light

    }
    else{
      mcNoTag *= (1- eff);
      dataNoTag *= (1- eff*SF);

      if(hadronFlavor==5 || hadronFlavor ==4 ) err2 += (-eff*SFerr)/(1-eff*SF); /// /correlated for b/c
      else err4 +=  (-eff*SFerr)/(1-eff*SF);  ////correlated for light

    }
  }


  double wtbtag = (dataNoTag * dataTag ) / ( mcNoTag * mcTag );
  double wtbtagErrBC = fabs(err1+err2) * wtbtag;
  double wtbtagErrUDSG = fabs(err3+err4) * wtbtag;

  string errStr = " is NaN in BTaggingScaleFactorApplicator::get_weight_btag. Please check that all efficiency-bins are greater than 0.";
  if (isnan(wtbtag)) throw runtime_error("wtbtag" + errStr);
  if (isnan(wtbtagErrBC)) throw runtime_error("wtbtagErrBC" + errStr);
  if (isnan(wtbtagErrUDSG)) throw runtime_error("wtbtagErrUDSG" + errStr);

  return make_tuple(wtbtag, wtbtagErrBC, wtbtagErrUDSG);

}


// originally taken from https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
// (only the purpose of the function is the same, interface and implementation changed)
pair<double, double> BTaggingScaleFactorApplicator::get_SF_btag(double pt, double abs_eta, int flav) {

  auto btagentry_flav = flav == 5 ? BTagEntry::FLAV_B : (flav == 4 ? BTagEntry::FLAV_C : BTagEntry::FLAV_UDSG);
  auto sf_bounds = m_calib_nominal->min_max_pt(btagentry_flav, abs_eta);

  double pt_for_eval = pt;
  bool is_out_of_bounds = false;
  if(pt < sf_bounds.first){
    pt_for_eval = sf_bounds.first + 1e-5;
    is_out_of_bounds = true;
  }
  else if(pt > sf_bounds.second){
    pt_for_eval = sf_bounds.second - 0.1;
    is_out_of_bounds = true;
  }

  double SF_up   = m_calib_up->eval(btagentry_flav, abs_eta, pt_for_eval);
  double SF      = m_calib_nominal->eval(btagentry_flav, abs_eta, pt_for_eval);
  double SF_down = m_calib_down->eval(btagentry_flav, abs_eta, pt_for_eval);

  double SFerr_up_ = fabs(SF - SF_up);
  double SFerr_down_ = fabs(SF - SF_down);  // positive value!!

  double SFerr = SFerr_up_ > SFerr_down_ ? SFerr_up_ : SFerr_down_;

  if (is_out_of_bounds) SFerr *= 2;

  if (SF < 1e-10) {
    cout << "WARNING: SF vanishes! Will return SF = 1., SFerr = 0., Values: "
    << "(SF, SFerr, is_out_of_bounds, lowbound, highbound, pt, pt_for_eval, btagentry_flav): "
    << SF << ", " << SFerr << ", " << is_out_of_bounds << ", "
    << sf_bounds.first << ", " << sf_bounds.second << ", "
    << pt << ", " << pt_for_eval << ", " << btagentry_flav << endl;
    SF = 1.;
    SFerr = 0.;
  }
  return make_pair(SF, SFerr);
}
