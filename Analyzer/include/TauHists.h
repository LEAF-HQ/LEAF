#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/BaseHists.h"

using namespace std;

class TauHists : public BaseHists{

public:
  // Constructors, destructor
  TauHists(TString dir_);
  TauHists(const TauHists &) = default;
  TauHists & operator = (const TauHists &) = default;
  ~TauHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D>
  hntaus, htaupt, htaupt_rebin, htaupt_rebin2, htaueta, htauphi, htaumass, htauenergy, htauiso, htauorigin, htaudxy, htaudz, htaud, htaugendrmin, htaugenstatus,
  hntausmatched, htaumatchedpt, htaumatchedpt_rebin, htaumatchedpt_rebin2, htaumatchedeta, htaumatchedphi, htaumatchedmass, htaumatchedenergy, htaumatchediso, htaumatchedorigin, htaumatcheddxy, htaumatcheddz, htaumatchedd, htaumatchedgendrmin, htaumatchedgenstatus,
  hntausunmatched, htauunmatchedpt, htauunmatchedpt_rebin, htauunmatchedpt_rebin2, htauunmatchedeta, htauunmatchedphi, htauunmatchedmass, htauunmatchedenergy, htauunmatchediso, htauunmatchedorigin, htauunmatcheddxy, htauunmatcheddz, htauunmatchedd, htauunmatchedgendrmin, htauunmatchedgenstatus,

  htau1pt, htau1pt_rebin, htau1pt_rebin2, htau1eta, htau1phi, htau1mass, htau1energy, htau1iso, htau1origin, htau1dxy, htau1dz, htau1d, htau1gendrmin, htau1genstatus,
  htau2pt, htau2pt_rebin, htau2pt_rebin2, htau2eta, htau2phi, htau2mass, htau2energy, htau2iso, htau2origin, htau2dxy, htau2dz, htau2d, htau2gendrmin, htau2genstatus,
  htau3pt, htau3pt_rebin, htau3pt_rebin2, htau3eta, htau3phi, htau3mass, htau3energy, htau3iso, htau3origin, htau3dxy, htau3dz, htau3d, htau3gendrmin, htau3genstatus,
  htau4pt, htau4pt_rebin, htau4pt_rebin2, htau4eta, htau4phi, htau4mass, htau4energy, htau4iso, htau4origin, htau4dxy, htau4dz, htau4d, htau4gendrmin, htau4genstatus;





};
