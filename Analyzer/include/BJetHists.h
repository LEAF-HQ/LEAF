#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

using namespace std;

class BJetHists : public BaseHists{

public:
  // Constructors, destructor
  BJetHists(TString dir_);
  BJetHists(const BJetHists &) = default;
  BJetHists & operator = (const BJetHists &) = default;
  ~BJetHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hnbjetlooses, hbjetloosept, hbjetlooseeta, hbjetloosephi, hbjetloosemass, hbjetlooseenergy, hbjetloosehadronflavor, hbjetloosepartonflavor, hbjetloosedeepb, hbjetloosedrminele, hbjetloosedrminmuon, hbjetloosedrmintau, hbjetloose1pt, hbjetloose1eta, hbjetloose1phi, hbjetloose1mass, hbjetloose1energy, hbjetloose1hadronflavor, hbjetloose1partonflavor, hbjetloose1deepb, hbjetloose1drminele, hbjetloose1drminmuon, hbjetloose1drmintau, hnnotbjetlooses, hnotbjetloosept, hnotbjetlooseeta, hnotbjetloosephi, hnotbjetloosemass, hnotbjetlooseenergy, hnotbjetloosehadronflavor, hnotbjetloosepartonflavor, hnotbjetloosedeepb, hnotbjetloosedrminele, hnotbjetloosedrminmuon, hnotbjetloosedrmintau, hnotbjetloose1pt, hnotbjetloose1eta, hnotbjetloose1phi, hnotbjetloose1mass, hnotbjetloose1energy, hnotbjetloose1hadronflavor, hnotbjetloose1partonflavor, hnotbjetloose1deepb, hnotbjetloose1drminele, hnotbjetloose1drminmuon, hnotbjetloose1drmintau;

  shared_ptr<TH1D> hnbjetmediums, hbjetmediumpt, hbjetmediumeta, hbjetmediumphi, hbjetmediummass, hbjetmediumenergy, hbjetmediumhadronflavor, hbjetmediumpartonflavor, hbjetmediumdeepb, hbjetmediumdrminele, hbjetmediumdrminmuon, hbjetmediumdrmintau, hbjetmedium1pt, hbjetmedium1eta, hbjetmedium1phi, hbjetmedium1mass, hbjetmedium1energy, hbjetmedium1hadronflavor, hbjetmedium1partonflavor, hbjetmedium1deepb, hbjetmedium1drminele, hbjetmedium1drminmuon, hbjetmedium1drmintau, hnnotbjetmediums, hnotbjetmediumpt, hnotbjetmediumeta, hnotbjetmediumphi, hnotbjetmediummass, hnotbjetmediumenergy, hnotbjetmediumhadronflavor, hnotbjetmediumpartonflavor, hnotbjetmediumdeepb, hnotbjetmediumdrminele, hnotbjetmediumdrminmuon, hnotbjetmediumdrmintau, hnotbjetmedium1pt, hnotbjetmedium1eta, hnotbjetmedium1phi, hnotbjetmedium1mass, hnotbjetmedium1energy, hnotbjetmedium1hadronflavor, hnotbjetmedium1partonflavor, hnotbjetmedium1deepb, hnotbjetmedium1drminele, hnotbjetmedium1drminmuon, hnotbjetmedium1drmintau;

  shared_ptr<TH1D> hnbjettights, hbjettightpt, hbjettighteta, hbjettightphi, hbjettightmass, hbjettightenergy, hbjettighthadronflavor, hbjettightpartonflavor, hbjettightdeepb, hbjettightdrminele, hbjettightdrminmuon, hbjettightdrmintau, hbjettight1pt, hbjettight1eta, hbjettight1phi, hbjettight1mass, hbjettight1energy, hbjettight1hadronflavor, hbjettight1partonflavor, hbjettight1deepb, hbjettight1drminele, hbjettight1drminmuon, hbjettight1drmintau, hnnotbjettights, hnotbjettightpt, hnotbjettighteta, hnotbjettightphi, hnotbjettightmass, hnotbjettightenergy, hnotbjettighthadronflavor, hnotbjettightpartonflavor, hnotbjettightdeepb, hnotbjettightdrminele, hnotbjettightdrminmuon, hnotbjettightdrmintau, hnotbjettight1pt, hnotbjettight1eta, hnotbjettight1phi, hnotbjettight1mass, hnotbjettight1energy, hnotbjettight1hadronflavor, hnotbjettight1partonflavor, hnotbjettight1deepb, hnotbjettight1drminele, hnotbjettight1drminmuon, hnotbjettight1drmintau;





};
