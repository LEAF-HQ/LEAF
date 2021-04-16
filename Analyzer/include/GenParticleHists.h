#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"
#include "Analyzer/include/Muon.h"
#include "Analyzer/include/useful_functions.h"

using namespace std;

class GenParticleHists : public BaseHists{

public:
  // Constructors, destructor
  GenParticleHists(TString dir_);
  GenParticleHists(const GenParticleHists &) = default;
  GenParticleHists & operator = (const GenParticleHists &) = default;
  ~GenParticleHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hngentaus, hptgentau1, hptgentau1_rebin, hptgentau1_rebin2, hptgentau1_rebin3, hptgentau1_rebin4, hptgentau2, hptgentau2_rebin, hptgentau2_rebin2, hptgentau2_rebin3, hptgentau2_rebin4,

  hngenvistaus, hngenvistausmatched, hgenvistaustotal, hgenvistausmatched, hptgenvistau, hptgenvistau_rebin, hptgenvistau_rebin2, hptgenvistaumatched, hptgenvistaumatched_rebin, hptgenvistaumatched_rebin2, hdrmintau, hgenvistaudecaymode, hptgenvistau1, hptgenvistau1_rebin, hptgenvistau1_rebin2, hptgenvistau1matched, hptgenvistau1matched_rebin, hptgenvistau1matched_rebin2, hdrmintau1, hgenvistau1decaymode, hptgenvistau2, hptgenvistau2_rebin, hptgenvistau2_rebin2, hptgenvistau2matched, hptgenvistau2matched_rebin, hptgenvistau2matched_rebin2, hdrmintau2, hgenvistau2decaymode,

  hngenmus, hngenmusmatched, hgenmustotal, hgenmusmatched, hptgenmu, hptgenmu_rebin, hptgenmu_rebin2, hptgenmumatched, hptgenmumatched_rebin, hptgenmumatched_rebin2, hdrminmu, hgenmuorigin, hptgenmu1, hptgenmu1_rebin, hptgenmu1_rebin2, hptgenmu1matched, hptgenmu1matched_rebin, hptgenmu1matched_rebin2, hdrminmu1, hgenmu1origin, hptgenmu2, hptgenmu2_rebin, hptgenmu2_rebin2, hptgenmu2matched, hptgenmu2matched_rebin, hptgenmu2matched_rebin2, hdrminmu2, hgenmu2origin, hgenmusfromtautotal, hgenmusfromtaumatched, hptgenmufromtau, hptgenmufromtau_rebin, hptgenmufromtau_rebin2, hptgenmufromtaumatched, hptgenmufromtaumatched_rebin, hptgenmufromtaumatched_rebin2,

  hngenels, hngenelsmatched, hgenelstotal, hgenelsmatched, hptgenel, hptgenel_rebin, hptgenel_rebin2, hptgenelmatched, hptgenelmatched_rebin, hptgenelmatched_rebin2, hdrminel, hgenelorigin, hptgenel1, hptgenel1_rebin, hptgenel1_rebin2, hptgenel1matched, hptgenel1matched_rebin, hptgenel1matched_rebin2, hdrminel1, hgenel1origin, hptgenel2, hptgenel2_rebin, hptgenel2_rebin2, hptgenel2matched, hptgenel2matched_rebin, hptgenel2matched_rebin2, hdrminel2, hgenel2origin, hgenelsfromtautotal, hgenelsfromtaumatched, hptgenelfromtau, hptgenelfromtau_rebin, hptgenelfromtau_rebin2, hptgenelfromtaumatched, hptgenelfromtaumatched_rebin, hptgenelfromtaumatched_rebin2;





};
