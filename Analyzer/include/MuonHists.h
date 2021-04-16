#pragma once

#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

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

  shared_ptr<TH1D> hnmuons, hmuonpt, hmuonpt_rebin, hmuoneta, hmuonphi, hmuonmass, hmuonenergy, hmuonpfiso, hmuonminiiso, hmuondxy, hmuondz, hmuond, hmuongendrmin, hmuongenorigin, hmuongenflav, hnmuonsgenfromtau, hnmuonsgenfromhadron, hnmuonsgenfromelse, hnmuonsgenunmatched,

  hmuonclosestorigin, hmuonclosestd,

  hnmuonsfromtau, hmuonfromtaupt, hmuonfromtaupt_rebin, hmuonfromtaueta, hmuonfromtauphi, hmuonfromtaumass, hmuonfromtauenergy, hmuonfromtaupfiso, hmuonfromtauminiiso, hmuonfromtaudxy, hmuonfromtaudz, hmuonfromtaud, hmuonfromtaugendrmin,
  hnmuonsnotfromtau, hmuonnotfromtaupt, hmuonnotfromtaupt_rebin, hmuonnotfromtaueta, hmuonnotfromtauphi, hmuonnotfromtaumass, hmuonnotfromtauenergy, hmuonnotfromtaupfiso, hmuonnotfromtauminiiso, hmuonnotfromtaudxy, hmuonnotfromtaudz, hmuonnotfromtaud, hmuonnotfromtaugendrmin,

  hmuon1pt, hmuon1pt_rebin, hmuon1eta, hmuon1phi, hmuon1mass, hmuon1energy, hmuon1pfiso, hmuon1miniiso, hmuon1dxy, hmuon1dz, hmuon1d, hmuon1gendrmin, hmuon1genorigin, hmuon1genflav,
  hmuon2pt, hmuon2pt_rebin, hmuon2eta, hmuon2phi, hmuon2mass, hmuon2energy, hmuon2pfiso, hmuon2miniiso, hmuon2dxy, hmuon2dz, hmuon2d, hmuon2gendrmin, hmuon2genorigin, hmuon2genflav,
  hmuon3pt, hmuon3pt_rebin, hmuon3eta, hmuon3phi, hmuon3mass, hmuon3energy, hmuon3pfiso, hmuon3miniiso, hmuon3dxy, hmuon3dz, hmuon3d, hmuon3gendrmin, hmuon3genorigin, hmuon3genflav,
  hmuon4pt, hmuon4pt_rebin, hmuon4eta, hmuon4phi, hmuon4mass, hmuon4energy, hmuon4pfiso, hmuon4miniiso, hmuon4dxy, hmuon4dz, hmuon4d, hmuon4gendrmin, hmuon4genorigin, hmuon4genflav;

  shared_ptr<TH2D> hmuon_dxy_vs_dz, hmuonfromtau_dxy_vs_dz, hmuonnotfromtau_dxy_vs_dz;





};
