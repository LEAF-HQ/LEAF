#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "include/RecoEvent.h"
#include "include/BaseHists.h"

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

  shared_ptr<TH1D> hnelectrons, helectronpt, helectroneta, helectronphi, helectronmass, helectronenergy, helectron1pt, helectron1eta, helectron1phi, helectron1mass, helectron1energy, helectron2pt, helectron2eta, helectron2phi, helectron2mass, helectron2energy, helectron3pt, helectron3eta, helectron3phi, helectron3mass, helectron3energy, helectron4pt, helectron4eta, helectron4phi, helectron4mass, helectron4energy;





};
