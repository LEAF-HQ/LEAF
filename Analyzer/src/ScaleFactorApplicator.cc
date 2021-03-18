#include "Analyzer/include/ScaleFactorApplicator.h"

using namespace std;

ScaleFactorApplicator::ScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname){

  load_histogram(year, infilename, histname);
  m_factor_uncertainty = 1.;
  m_bin_x = -1;
  m_bin_y = -1;

}

void ScaleFactorApplicator::load_histogram(TString year, TString infilename, TString histname){

  TString macropath = (TString)getenv("MACROPATH"); // set up by setup.sh
  TString infilepath = macropath + "/data/" + year + "/" + infilename;

  m_infile.reset(new TFile(infilepath, "READ"));

  // check if SF file is 2-d or 1-d
  m_is_2d = false;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  vector<TString> result = {};
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TH2")){
      TString name = key->GetName();
      if(name == histname){
        m_is_2d = true;
        break;
      }
    }
  }

  if(m_is_2d) m_hist_2d.reset((TH2D*)m_infile->Get(histname));
  else        m_hist_1d.reset((TH1D*)m_infile->Get(histname));
}


void ScaleFactorApplicator::reset(){
  m_factor_uncertainty = 1.;
  m_bin_x = -1;
  m_bin_y = -1;
}


int ScaleFactorApplicator::find_bin(double val, TAxis* axis){
  int result = -1;
  unsigned int lastbin = axis->GetNbins();
  if(val < axis->GetBinLowEdge(1)){
    result = 1;
    m_factor_uncertainty *= 2;
  }
  else if(val >= axis->GetBinUpEdge(lastbin)){
    result = lastbin;
    m_factor_uncertainty *= 2;
  }
  else{
    result = axis->FindBin(val);
  }

  return result;
}

void ScaleFactorApplicator::set_bin(double val){
  if(m_is_2d) throw runtime_error("In ScaleFactorApplicator::set_bin(double val)): called 1-d function using 2-d histogram.");
  reset();

  m_bin_x = find_bin(val, m_hist_1d->GetXaxis());
}

void ScaleFactorApplicator::set_bin(double valx, double valy){
  if(!m_is_2d) throw runtime_error("In ScaleFactorApplicator::set_bin(double valx, double valy): called 2-d function using 1-d histogram.");
  reset();

  m_bin_x = find_bin(valx, m_hist_2d->GetXaxis());
  m_bin_y = find_bin(valy, m_hist_2d->GetYaxis());
}


double ScaleFactorApplicator::get_scalefactor(){
  // function to read the scale factor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called.

  if(m_bin_x < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_x has not been set. Call ScaleFactorApplicator::set_bin() before.");
  if(!m_is_2d) return m_hist_1d->GetBinContent(m_bin_x);

  if(m_bin_y < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_y has not been set. Call ScaleFactorApplicator::set_bin() before.");
  return m_hist_2d->GetBinContent(m_bin_x, m_bin_y);

}


double ScaleFactorApplicator::get_uncertainty(){
  // function to read the uncertainty on the scalefactor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called. Will return the (inflated) BinError, so it better be assigned properly by the POG.

  if(m_bin_x < 0) throw runtime_error("In ScaleFactorApplicator::get_uncertainty(): m_bin_x has not been set. Call ScaleFactorApplicator::set_bin() before.");
  if(!m_is_2d) return m_hist_1d->GetBinError(m_bin_x) * m_factor_uncertainty;

  if(m_bin_y < 0) throw runtime_error("In ScaleFactorApplicator::get_uncertainty(): m_bin_y has not been set. Call ScaleFactorApplicator::set_bin() before.");
  return m_hist_2d->GetBinError(m_bin_x, m_bin_y) * m_factor_uncertainty;

}
