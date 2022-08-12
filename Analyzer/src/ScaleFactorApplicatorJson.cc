#include "LEAF/Analyzer/include/ScaleFactorApplicatorJson.h"

using namespace std;

ScaleFactorApplicatorJson::ScaleFactorApplicatorJson(const Config& cfg, TString year, TString infilename, TString sfname) : m_sfname(sfname){

  if(year == "UL16preVFP")        m_year = "2016preVFP_UL";
  else if (year == "UL16postVFP") m_year = "2016postVFP_UL";
  else if (year == "UL17")        m_year = "2017_UL";
  else if (year == "UL18")        m_year = "2018_UL";
  else throw std::runtime_error("In ScaleFactorApplicatorJson::ScaleFactorApplicatorJson(): Invalid value passed as 'year'.");

  TString analyzerpath = (TString)getenv("ANALYZERPATH"); // set up by setup.sh
  TString infilepath = analyzerpath + "/data/" + year + "/" + infilename;

  std::unique_ptr<correction::CorrectionSet> evaluator = correction::CorrectionSet::from_file(infilepath.Data());
  m_correction = evaluator->at(sfname.Data());
}
