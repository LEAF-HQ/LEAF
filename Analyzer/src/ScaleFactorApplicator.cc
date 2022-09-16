#include "LEAF/Analyzer/include/ScaleFactorApplicator.h"

using namespace std;

// to be used by derived classes with their own implementation of `load_histogram()`
ScaleFactorApplicator::ScaleFactorApplicator(){
  m_factor_uncertainty = 1.;
  m_bin_x = -1;
  m_bin_y = -1;
  m_is_2d = false;
  m_is_graph = false;
}

ScaleFactorApplicator::ScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname){

  m_factor_uncertainty = 1.;
  m_bin_x = -1;
  m_bin_y = -1;
  m_is_2d = false;
  m_is_graph = false;

  load_histogram(year, infilename, histname);

}

void ScaleFactorApplicator::load_histogram(TString year, TString infilename, TString histname){
  TString macropath = (TString)getenv("ANALYZERPATH"); // set up by setup.sh
  TString infilepath = macropath + "/data/" + year + "/" + infilename;
  load_histogram(infilepath, histname);
}


void ScaleFactorApplicator::load_histogram(TString infilename, TString histname){

  m_infile.reset(new TFile(infilename, "READ"));

  // check if SF file is 2-d or 1-d
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
    if(cl->InheritsFrom("TGraph")){
      TString name = key->GetName();
      if(name == histname){
        m_is_graph = true;
        break;
      }
    }
    if(cl->InheritsFrom("TGraph2D")){
      throw runtime_error("In ScaleFactorApplicator::load_histogram(): seem to read a 2-d graph (inherits from TGraph2D), so far only 1-d graphs are supported. Please use a TH2 instead.");
    }
  }

  if(m_is_graph){
    m_graph_1d.reset((TGraphAsymmErrors*)m_infile->Get(histname));
  }
  else{
    if(m_is_2d) m_hist_2d.reset((TH2D*)m_infile->Get(histname));
    else        m_hist_1d.reset((TH1D*)m_infile->Get(histname));
  }
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
  if(m_is_2d) throw runtime_error("In ScaleFactorApplicator::set_bin(double val): called 1-d function using 2-d histogram.");
  // if(m_is_graph) throw runtime_error("In ScaleFactorApplicator::set_bin(double val): called histogram function while using graph, call set_value() instead.");
  reset();
  if(m_is_graph){
    double x, y;
    double minimum=9999999.;
    double maximum=-9999999.;
    double binmin = -1;
    double binmax = -1;
    for(int i=0; i<m_graph_1d->GetN(); i++){
      m_graph_1d->GetPoint(i, x, y);
      if(x < minimum){
        minimum = x;
        binmin = i;
      }
      if(x > maximum){
        maximum = x;
        binmax = i;
      }
      if((x - m_graph_1d->GetErrorXlow(i)) <= val && (x + m_graph_1d->GetErrorXhigh(i)) > val){
        m_bin_graph = i;
        return;
      }
    }
    if(val < minimum){
      m_bin_graph = binmin;
      m_factor_uncertainty *= 2;
    }
    if(val > maximum){
      m_bin_graph = binmax;
      m_factor_uncertainty *= 2;
    }
  }
  else{
    m_bin_x = find_bin(val, m_hist_1d->GetXaxis());
  }
}

void ScaleFactorApplicator::set_bin(double valx, double valy){
  if(!m_is_2d) throw runtime_error("In ScaleFactorApplicator::set_bin(double valx, double valy): called 2-d function using 1-d histogram.");
  if(m_is_graph) throw runtime_error("In ScaleFactorApplicator::set_bin(double valx, double valy): called 2-d function while using graph, so far only 1-d graphs are supported. Please use a TH2 instead.");
  reset();
  m_bin_x = find_bin(valx, m_hist_2d->GetXaxis());
  m_bin_y = find_bin(valy, m_hist_2d->GetYaxis());

}


double ScaleFactorApplicator::get_scalefactor(){
  // function to read the scale factor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called.

  if(m_is_graph){
    if(m_bin_graph < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_graph has not been set. Call ScaleFactorApplicator::set_bin() before.");
    double x, y;
    m_graph_1d->GetPoint(m_bin_graph, x, y);
    return y;
  }
  else{
    if(m_bin_x < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_x has not been set. Call ScaleFactorApplicator::set_bin() before.");
    if(!m_is_2d) return m_hist_1d->GetBinContent(m_bin_x);


    if(m_bin_y < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_y has not been set. Call ScaleFactorApplicator::set_bin() before.");
    return m_hist_2d->GetBinContent(m_bin_x, m_bin_y);
  }
}


double ScaleFactorApplicator::get_uncertainty(){
  // function to read the uncertainty on the scalefactor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called. Will return the (inflated) BinError, so it better be assigned properly by the POG.

  if(m_is_graph) throw runtime_error("In ScaleFactorApplicator::get_uncertainty(): scale factor comes from a TGraphAsymmErrors, please use get_uncertainty_up() or get_uncertainty_down().");

  if(m_bin_x < 0) throw runtime_error("In ScaleFactorApplicator::get_uncertainty(): m_bin_x has not been set. Call ScaleFactorApplicator::set_bin() before.");
  if(!m_is_2d) return m_hist_1d->GetBinError(m_bin_x) * m_factor_uncertainty;

  if(m_bin_y < 0) throw runtime_error("In ScaleFactorApplicator::get_uncertainty(): m_bin_y has not been set. Call ScaleFactorApplicator::set_bin() before.");
  return m_hist_2d->GetBinError(m_bin_x, m_bin_y) * m_factor_uncertainty;

}


double ScaleFactorApplicator::get_uncertainty_up(){
  // function to read the uncertainty on the scalefactor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called. Will return the (inflated) BinError, so it better be assigned properly by the POG.
  if(m_is_graph){
    if(m_bin_graph < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_graph has not been set. Call ScaleFactorApplicator::set_bin() before.");
    return m_graph_1d->GetErrorYhigh(m_bin_graph) * m_factor_uncertainty;
  }

  // for non-graphs, return the symmetric uncertainty for compatibility
  return get_uncertainty();
}


double ScaleFactorApplicator::get_uncertainty_down(){
  // function to read the uncertainty on the scalefactor from the histograms, works for 1-d and 2-d. Requires the ::set_bin() function to have been called. Will return the (inflated) BinError, so it better be assigned properly by the POG.
  if(m_is_graph){
    if(m_bin_graph < 0) throw runtime_error("In ScaleFactorApplicator::get_scalefactor(): m_bin_graph has not been set. Call ScaleFactorApplicator::set_bin() before.");
    return m_graph_1d->GetErrorYlow(m_bin_graph) * m_factor_uncertainty;
  }

  // for non-graphs, return the symmetric uncertainty for compatibility
  return get_uncertainty();
}
