#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

using namespace std;

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

  shared_ptr<TH1D> hnjets, hndeepbloose, hndeepbmedium, hndeepbtight, hjetpt, hjeteta, hjetphi, hjetmass, hjetenergy, hjetdeepb, hjetdrminele, hjetdrminmuon, hjetdrmintau, hjet1pt, hjet1eta, hjet1phi, hjet1mass, hjet1energy, hjet1deepb, hjet1drminele, hjet1drminmuon, hjet1drmintau, hjet2pt, hjet2eta, hjet2phi, hjet2mass, hjet2energy, hjet2deepb, hjet2drminele, hjet2drminmuon, hjet2drmintau, hjet3pt, hjet3eta, hjet3phi, hjet3mass, hjet3energy, hjet3deepb, hjet3drminele, hjet3drminmuon, hjet3drmintau, hjet4pt, hjet4eta, hjet4phi, hjet4mass, hjet4energy, hjet4deepb, hjet4drminele, hjet4drminmuon, hjet4drmintau, hjet5pt, hjet5eta, hjet5phi, hjet5mass, hjet5energy, hjet5deepb, hjet5drminele, hjet5drminmuon, hjet5drmintau;





};
