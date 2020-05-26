#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "GenJet.h"
#include "GenParticle.h"
// #include <memory>

using namespace std;

// Container class for all quantities
class Event {

public:
  // Constructors, destructor
  // Event() = default;
  Event();
  Event(const Event &) = default;
  Event & operator = (const Event &) = default;
  ~Event() = default;

  void clear();

  vector<GenJet>* genjets;
  vector<GenParticle>* genparticles;

  int    id = 0;
  int    njets = 0;
  int    nb = 0;
  int    nbcut = 0;
  int    nbcut50 = 0;
  int    nlq = 0;
  int    nx = 0;
  int    ndm = 0;
  int    ntau = 0;
  int    ntaucut = 0;
  int    ntaucut50 = 0;
  int    ntaucut_vis = 0;
  int    ntaucut50_vis = 0;
  double weight = 0.;
  double mlq1 = 0.;
  double mlq2 = 0.;
  double mx = 0.;
  double mdm1 = 0.;
  double mdm2 = 0.;
  double ptlq1 = 0.;
  double ptlq2 = 0.;
  double ptx = 0.;
  double ptdm1 = 0.;
  double ptdm2 = 0.;
  double etalq1 = 0.;
  double etalq2 = 0.;
  double etax = 0.;
  double etadm1 = 0.;
  double etadm2 = 0.;
  double philq1 = 0.;
  double philq2 = 0.;
  double phix = 0.;
  double phidm1 = 0.;
  double phidm2 = 0.;
  double ptjet1 = 0.;
  double ptjet2 = 0.;
  double ptjet3 = 0.;
  double ptb1 = 0.;
  double ptb2 = 0.;
  double pttau1 = 0.;
  double pttau2 = 0.;
  double pttauvis1 = 0.;
  double pttauvis2 = 0.;
  double mjet1 = 0.;
  double mjet2 = 0.;
  double mjet3 = 0.;
  double mb1 = 0.;
  double mb2 = 0.;
  double mtau1 = 0.;
  double mtau2 = 0.;
  double mtauvis1 = 0.;
  double mtauvis2 = 0.;
  double etajet1 = 0.;
  double etajet2 = 0.;
  double etajet3 = 0.;
  double etab1 = 0.;
  double etab2 = 0.;
  double etatau1 = 0.;
  double etatau2 = 0.;
  double etatauvis1 = 0.;
  double etatauvis2 = 0.;
  double phijet1 = 0.;
  double phijet2 = 0.;
  double phijet3 = 0.;
  double phib1 = 0.;
  double phib2 = 0.;
  double phitau1 = 0.;
  double phitau2 = 0.;
  double phitauvis1 = 0.;
  double phitauvis2 = 0.;
  double ptmet = 0.;
  double phimet = 0.;
  double st = 0.;
  double stmet = 0.;

};
