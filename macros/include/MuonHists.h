#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/RecoEvent.h"
#include "include/BaseHists.h"

using namespace std;

class MuonHists : public BaseHists{

public:
  // Constructors, destructor
  MuonHists(TString dir_);
  MuonHists(const MuonHists &) = default;
  MuonHists & operator = (const MuonHists &) = default;
  ~MuonHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hnmuons, hmuon1pt, hmuon1eta, hmuon1phi, hmuon1mass, hmuon1energy, hmuon2pt, hmuon2eta, hmuon2phi, hmuon2mass, hmuon2energy, hmuon3pt, hmuon3eta, hmuon3phi, hmuon3mass, hmuon3energy, hmuon4pt, hmuon4eta, hmuon4phi, hmuon4mass, hmuon4energy;





};
