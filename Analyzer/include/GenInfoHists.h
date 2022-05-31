#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"
#include <LHAPDF/LHAPDF.h>

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

  std::shared_ptr<TH1F> hptmet, hphimet, hgeninfoid1, hgeninfoid2, hgeninfox1, hgeninfox2, hgeninfoxall, hgeninfoxb, hgeninfoxc, hgeninfoxpdf1, hgeninfoxpdf2, hgeninfoxpdf1_rebin1, hgeninfoxpdf2_rebin1, hgeninfoxpdf1_rebin2, hgeninfoxpdf2_rebin2, hgeninfoxpdf1_rebin3, hgeninfoxpdf2_rebin3, hgeninfoxpdfall, hgeninfoxpdfb, hgeninfoxpdfc, hgeninfoxpdfproduct, hgeninfoxpdfproduct_rebin1, hgeninfoxpdfproduct_rebin2, hgeninfoxpdfproduct_rebin3, hgeninfoxpdfproduct_rebin4, hgeninfoscalepdf, hsumweights,

  hnewpdf_geninfoxpdf1, hnewpdf_geninfoxpdf2, hnewpdf_geninfoxpdf1_rebin1, hnewpdf_geninfoxpdf2_rebin1, hnewpdf_geninfoxpdf1_rebin2, hnewpdf_geninfoxpdf2_rebin2, hnewpdf_geninfoxpdf1_rebin3, hnewpdf_geninfoxpdf2_rebin3, hnewpdf_geninfoxpdfall, hnewpdf_geninfoxpdfb, hnewpdf_geninfoxpdfc, hnewpdf_geninfoxpdfproduct, hnewpdf_geninfoxpdfproduct_rebin1, hnewpdf_geninfoxpdfproduct_rebin2, hnewpdf_geninfoxpdfproduct_rebin3, hnewpdf_geninfoxpdfproduct_rebin4;

  LHAPDF::PDF* pdf, *pdf_new;
};
