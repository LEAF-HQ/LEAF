#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"

class JetHists : public BaseHists{

public:
  // Constructors, destructor
  JetHists(TString dir_);
  JetHists(const JetHists &) = default;
  JetHists & operator = (const JetHists &) = default;
  ~JetHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  std::shared_ptr<TH1D> hnjets, hndeepbloose, hndeepbmedium, hndeepbtight, hjetpt, hjeteta, hjetphi, hjetmass, hjetenergy, hjethadronflavor,hjetpartonflavor, hjetdeepb, hjetdrminele, hjetdrminmuon, hjetdrmintau, hjet1pt, hjet1eta, hjet1phi, hjet1mass, hjet1energy, hjet1hadronflavor,hjet1partonflavor, hjet1deepb, hjet1drminele, hjet1drminmuon, hjet1drmintau, hjet2pt, hjet2eta, hjet2phi, hjet2mass, hjet2energy, hjet2hadronflavor,hjet2partonflavor, hjet2deepb, hjet2drminele, hjet2drminmuon, hjet2drmintau, hjet3pt, hjet3eta, hjet3phi, hjet3mass, hjet3energy, hjet3hadronflavor,hjet3partonflavor, hjet3deepb, hjet3drminele, hjet3drminmuon, hjet3drmintau, hjet4pt, hjet4eta, hjet4phi, hjet4mass, hjet4energy, hjet4hadronflavor,hjet4partonflavor, hjet4deepb, hjet4drminele, hjet4drminmuon, hjet4drmintau, hjet5pt, hjet5eta, hjet5phi, hjet5mass, hjet5energy, hjet5hadronflavor,hjet5partonflavor, hjet5deepb, hjet5drminele, hjet5drminmuon, hjet5drmintau;

  std::shared_ptr<TH1D> hngenjets, hgenjetpt, hgenjeteta, hgenjetphi, hgenjetmass, hgenjetenergy, hgenjetdrminele, hgenjetdrminmuon, hgenjetdrmintau, hgenjet1pt, hgenjet1eta, hgenjet1phi, hgenjet1mass, hgenjet1energy, hgenjet1drminele, hgenjet1drminmuon, hgenjet1drmintau, hgenjet2pt, hgenjet2eta, hgenjet2phi, hgenjet2mass, hgenjet2energy, hgenjet2drminele, hgenjet2drminmuon, hgenjet2drmintau;





};
