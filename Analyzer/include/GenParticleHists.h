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

  shared_ptr<TH1D> hngentaus, hptgentau1, hptgentau1_rebin, hptgentau1_rebin2, hptgentau1_rebin3, hptgentau1_rebin4, hptgentau2, hptgentau2_rebin, hptgentau2_rebin2, hptgentau2_rebin3, hptgentau2_rebin4, hdrgenditau, hdphigenditau, hdetagenditau, hdrgentaumu, hdphigentaumu, hdetagentaumu, hdptgentaumu, hdptrelgentaumu, hdrgentaue, hdphigentaue, hdetagentaue, hdptgentaue, hdptrelgentaue,

  hngenvistaus, hngenvistausmatched, hgenvistaustotal, hgenvistausmatched, hptgenvistau, hptgenvistau_rebin, hptgenvistau_rebin2, hptgenvistaumatched, hptgenvistaumatched_rebin, hptgenvistaumatched_rebin2, hdrmintau, hgenvistaudecaymode, hptgenvistau1, hptgenvistau1_rebin, hptgenvistau1_rebin2, hptgenvistau1matched, hptgenvistau1matched_rebin, hptgenvistau1matched_rebin2, hdrmintau1, hgenvistau1decaymode, hptgenvistau2, hptgenvistau2_rebin, hptgenvistau2_rebin2, hptgenvistau2matched, hptgenvistau2matched_rebin, hptgenvistau2matched_rebin2, hdrmintau2, hgenvistau2decaymode, hdrgenvisditau, hdphigenvisditau, hdetagenvisditau, hdrgenvistaumu, hdphigenvistaumu, hdetagenvistaumu, hdrgenvistaue, hdphigenvistaue, hdetagenvistaue,

  hngenmus, hngenmusmatched, hgenmustotal, hgenmusmatched, hptgenmu, hptgenmu_rebin, hptgenmu_rebin2, hptgenmumatched, hptgenmumatched_rebin, hptgenmumatched_rebin2, hdrminmu, hgenmuorigin, hptgenmu1, hptgenmu1_rebin, hptgenmu1_rebin2, hptgenmu1matched, hptgenmu1matched_rebin, hptgenmu1matched_rebin2, hdrminmu1, hgenmu1origin, hptgenmu2, hptgenmu2_rebin, hptgenmu2_rebin2, hptgenmu2matched, hptgenmu2matched_rebin, hptgenmu2matched_rebin2, hdrminmu2, hgenmu2origin, hdrgendimu, hdphigendimu, hdetagendimu, hdrgenmuvistau, hdphigenmuvistau, hdetagenmuvistau, hdrgenmue, hdphigenmue, hdetagenmue,


  hgenmusfromtautotal, hgenmusfromtaumatched, hptgenmufromtau, hptgenmufromtau_rebin, hptgenmufromtau_rebin2, hptgenmufromtaumatched, hptgenmufromtaumatched_rebin, hptgenmufromtaumatched_rebin2, hdrgendimufromtau, hdphigendimufromtau, hdetagendimufromtau, hdrgenmufromtauvistau, hdphigenmufromtauvistau, hdetagenmufromtauvistau, hdrgenmufromtaue, hdphigenmufromtaue, hdetagenmufromtaue,


  hgenmusfromhadtotal, hgenmusfromhadmatched, hptgenmufromhad, hptgenmufromhad_rebin, hptgenmufromhad_rebin2, hptgenmufromhadmatched, hptgenmufromhadmatched_rebin, hptgenmufromhadmatched_rebin2, hdrgendimufromhad, hdphigendimufromhad, hdetagendimufromhad, hdrgenmufromhadvistau, hdphigenmufromhadvistau, hdetagenmufromhadvistau, hdrgenmufromhade, hdphigenmufromhade, hdetagenmufromhade,

  hngenels, hngenelsmatched, hgenelstotal, hgenelsmatched, hptgenel, hptgenel_rebin, hptgenel_rebin2, hptgenelmatched, hptgenelmatched_rebin, hptgenelmatched_rebin2, hdrminel, hgenelorigin, hptgenel1, hptgenel1_rebin, hptgenel1_rebin2, hptgenel1matched, hptgenel1matched_rebin, hptgenel1matched_rebin2, hdrminel1, hgenel1origin, hptgenel2, hptgenel2_rebin, hptgenel2_rebin2, hptgenel2matched, hptgenel2matched_rebin, hptgenel2matched_rebin2, hdrminel2, hgenel2origin, hdrgendie, hdphigendie, hdetagendie, hdrgenevistau, hdphigenevistau, hdetagenevistau, hdrgenemu, hdphigenemu, hdetagenemu,



  hgenelsfromtautotal, hgenelsfromtaumatched, hptgenelfromtau, hptgenelfromtau_rebin, hptgenelfromtau_rebin2, hptgenelfromtaumatched, hptgenelfromtaumatched_rebin, hptgenelfromtaumatched_rebin2, hdrgendiefromtau, hdphigendiefromtau, hdetagendiefromtau, hdrgenefromtauvistau, hdphigenefromtauvistau, hdetagenefromtauvistau, hdrgenefromtaumu, hdphigenefromtaumu, hdetagenefromtaumu,


  hgenelsfromhadtotal, hgenelsfromhadmatched, hptgenelfromhad, hptgenelfromhad_rebin, hptgenelfromhad_rebin2, hptgenelfromhadmatched, hptgenelfromhadmatched_rebin, hptgenelfromhadmatched_rebin2, hdrgendiefromhad, hdphigendiefromhad, hdetagendiefromhad, hdrgenefromhadvistau, hdphigenefromhadvistau, hdetagenefromhadvistau, hdrgenefromhadmu, hdphigenefromhadmu, hdetagenefromhadmu,



  hngenbs, hngenbsmatched, hgenbstotal, hgenbsmatched, hptgenb, hptgenb_rebin, hptgenb_rebin2, hptgenbmatched, hptgenbmatched_rebin, hptgenbmatched_rebin2, hdrminb, hgenborigin, hptgenb1, hptgenb1_rebin, hptgenb1_rebin2, hptgenb1matched, hptgenb1matched_rebin, hptgenb1matched_rebin2, hdrminb1, hgenb1origin, hptgenb2, hptgenb2_rebin, hptgenb2_rebin2, hptgenb2matched, hptgenb2matched_rebin, hptgenb2matched_rebin2, hdrminb2, hgenb2origin, hdrgendib, hdphigendib, hdetagendib, hdrgenbvistau, hdphigenbvistau, hdetagenbvistau, hdrgenbmu, hdphigenbmu, hdetagenbmu, hdrgenbe, hdphigenbe, hdetagenbe,

  hgenbsfromhardtotal, hgenbsfromhardmatched, hptgenbfromhard, hptgenbfromhard_rebin, hptgenbfromhard_rebin2, hptgenbfromhardmatched, hptgenbfromhardmatched_rebin, hptgenbfromhardmatched_rebin2, hdrgendibfromhard, hdphigendibfromhard, hdetagendibfromhard, hdrgenbfromhardvistau, hdphigenbfromhardvistau, hdetagenbfromhardvistau, hdrgenbfromhardmu, hdphigenbfromhardmu, hdetagenbfromhardmu, hdrgenbfromharde, hdphigenbfromharde, hdetagenbfromharde,

  hgenbsnotfromhardtotal, hgenbsnotfromhardmatched, hptgenbnotfromhard, hptgenbnotfromhard_rebin, hptgenbnotfromhard_rebin2, hptgenbnotfromhardmatched, hptgenbnotfromhardmatched_rebin, hptgenbnotfromhardmatched_rebin2, hdrgendibnotfromhard, hdphigendibnotfromhard, hdetagendibnotfromhard, hdrgenbnotfromhardvistau, hdphigenbnotfromhardvistau, hdetagenbnotfromhardvistau, hdrgenbnotfromhardmu, hdphigenbnotfromhardmu, hdetagenbnotfromhardmu, hdrgenbnotfromharde, hdphigenbnotfromharde, hdetagenbnotfromharde,


  hngennus, hptgennu, hptgennu_rebin, hptgennu_rebin2, hphigennu, hetagennu, hdrminnue, hdrminnumu, hdrminnutau, hdphiminnue, hdphiminnumu, hdphiminnutau, hdetaminnue, hdetaminnumu, hdetaminnutau,
  hptgennu1, hptgennu1_rebin, hptgennu1_rebin2, hphigennu1, hetagennu1, hdrminnu1e, hdrminnu1mu, hdrminnu1tau, hdphiminnu1e, hdphiminnu1mu, hdphiminnu1tau, hdetaminnu1e, hdetaminnu1mu, hdetaminnu1tau;






};
