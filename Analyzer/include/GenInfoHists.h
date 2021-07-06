#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"
#include <LHAPDF/LHAPDF.h>

using namespace std;

class GenInfoHists : public BaseHists{

public:
  // Constructors, destructor
  GenInfoHists(TString dir_);
  GenInfoHists(const GenInfoHists &) = default;
  GenInfoHists & operator = (const GenInfoHists &) = default;
  ~GenInfoHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1F> hptmet, hphimet, hgeninfoid1, hgeninfoid2, hgeninfox1, hgeninfox2, hgeninfoxpdf1, hgeninfoxpdf2, hgeninfoxpdfproduct, hgeninfoscalepdf, hsumweights;

  LHAPDF::PDF* pdf;
  double xmin, xmax, qmin, qmax;

};
