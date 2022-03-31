#pragma once

#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"

using namespace std;

class MuonHists : public BaseHists{

public:
  // Constructors, destructor
  MuonHists(TString dir_, bool do_stablegenparticles_ = false);
  MuonHists(const MuonHists &) = default;
  MuonHists & operator = (const MuonHists &) = default;
  ~MuonHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  bool do_stablegenparticles;
  vector<GenParticle>* genparticles;
  shared_ptr<TH1D> hnmuons, hmuonpt, hmuonpt_rebin, hmuonpt_rebin2, hmuoneta, hmuonphi, hmuonmass, hmuonenergy, hmuonpfiso, hmuondxy, hmuondz, hmuond, hmuongendrmin, hmuongenflav,

  hmuonclosestd,

  hmuon1pt, hmuon1pt_rebin, hmuon1pt_rebin2, hmuon1eta, hmuon1phi, hmuon1mass, hmuon1energy, hmuon1pfiso, hmuon1dxy, hmuon1dz, hmuon1d, hmuon1gendrmin, hmuon1genflav,
  hmuon2pt, hmuon2pt_rebin, hmuon2pt_rebin2, hmuon2eta, hmuon2phi, hmuon2mass, hmuon2energy, hmuon2pfiso, hmuon2dxy, hmuon2dz, hmuon2d, hmuon2gendrmin, hmuon2genflav,
  hmuon3pt, hmuon3pt_rebin, hmuon3pt_rebin2, hmuon3eta, hmuon3phi, hmuon3mass, hmuon3energy, hmuon3pfiso, hmuon3dxy, hmuon3dz, hmuon3d, hmuon3gendrmin, hmuon3genflav,
  hmuon4pt, hmuon4pt_rebin, hmuon4pt_rebin2, hmuon4eta, hmuon4phi, hmuon4mass, hmuon4energy, hmuon4pfiso, hmuon4dxy, hmuon4dz, hmuon4d, hmuon4gendrmin, hmuon4genflav;

  shared_ptr<TH2D> hmuon_dxy_vs_dz;





};
