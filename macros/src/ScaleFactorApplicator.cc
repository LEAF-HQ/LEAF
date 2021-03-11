#include "include/ScaleFactorApplicator.h"

using namespace std;

ScaleFactorApplicator::ScaleFactorApplicator(const Config& cfg, TString year, TString infilename, TString histname){

  load_histogram(year, infilename, histname);


  // if (m_is_2d){
  //   m_bin_x = find_bin(1.3, m_hist_2d->GetXaxis());
  //   m_bin_y = find_bin(200, m_hist_2d->GetYaxis());
  // }
  // else{
  //   m_bin_x = find_bin(200, m_hist_1d->GetXaxis());
  // }

  // cout << "x: " << m_bin_x << ", y: " << m_bin_y << endl;
}

void ScaleFactorApplicator::load_histogram(TString year, TString infilename, TString histname){

  TString macropath = (TString)getenv("MACROPATH"); // set up by setup.sh
  TString infilepath = macropath + "/data/" + year + "/" + infilename;
  cout << "infilepath: " << infilepath << endl;

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
      TString name = key->ReadObj()->GetName();
      if(name == histname){
        m_is_2d = true;
        break;
      }
    }
  }

  if(m_is_2d) m_hist_2d.reset((TH2D*)m_infile->Get(histname));
  else        m_hist_1d.reset((TH1D*)m_infile->Get(histname));
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

// // todo: get bin counting right for y-axis
// void ScaleFactorApplicator::find_bin_y(double val){
//
//   if (!m_is_2d) return;
//
//   int result = -1;
//   unsigned int nbinsy = m_hist_2d->GetNbinsY();
//
//   for(unsigned int i=1; i<nbinsy+1; i++){ // going through the first row in Y, all bins in X.
//     if(val >= m_hist_2d->GetYaxis()->GetBinLowEdge(i) && val < m_hist_2d->GetYaxis()->GetBinLowEdge(i+1)) result = i;
//   }
//   if(result < 0){
//     if(val < m_hist_2d->GetYaxis()->GetBinLowEdge(1)){
//       result = 1;
//       m_factor_uncertainty *= 2;
//     }
//     if(val >= m_hist_2d->GetYaxis()->GetBinUpEdge(nbinsy)){
//       result = nbinsy;
//       m_factor_uncertainty *= 2;
//     }
//   }
//   m_bin_y = result;
// }
