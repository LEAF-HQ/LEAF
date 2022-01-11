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

class ElectronHists : public BaseHists{

public:
  // Constructors, destructor
  ElectronHists(TString dir_);
  ElectronHists(const ElectronHists &) = default;
  ElectronHists & operator = (const ElectronHists &) = default;
  ~ElectronHists() = default;

  // Main functions
  void fill(const RecoEvent & event);


protected:

  shared_ptr<TH1D> hnelectrons, helectronpt, helectronpt_rebin, helectronpt_rebin2, helectroneta, helectronphi, helectronmass, helectronenergy, helectronpfiso, helectrondxy, helectrondz, helectrond, helectrongendrmin,


  helectron1pt, helectron1pt_rebin, helectron1pt_rebin2, helectron1eta, helectron1phi, helectron1mass, helectron1energy, helectron1pfiso, helectron1gendrmin, helectron1genorigin, helectron1dxy, helectron1dz, helectron1d,
  helectron2pt, helectron2pt_rebin, helectron2pt_rebin2, helectron2eta, helectron2phi, helectron2mass, helectron2energy, helectron2pfiso, helectron2gendrmin, helectron2genorigin, helectron2dxy, helectron2dz, helectron2d,
  helectron3pt, helectron3pt_rebin, helectron3pt_rebin2, helectron3eta, helectron3phi, helectron3mass, helectron3energy, helectron3pfiso, helectron3gendrmin, helectron3genorigin, helectron3dxy, helectron3dz, helectron3d,
  helectron4pt, helectron4pt_rebin, helectron4pt_rebin2, helectron4eta, helectron4phi, helectron4mass, helectron4energy, helectron4pfiso, helectron4gendrmin, helectron4genorigin, helectron4dxy, helectron4dz, helectron4d;

  shared_ptr<TH2D> helectron_dxy_vs_dz;





};
