#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "TMath.h"

enum class ParticleID {
  unknown=0,
  u=1, d=2, s=3, c=4, b=5, t=6, q=7,
  e=11, mu=13, tau=15, l=17,
  v_e=12, v_mu=14, v_tau=16, v=18,
  g=21, photon=22, Z=23, W=24, H=25,
  pi_0 = 111, pi_plus = 211,
  kaon_0_L = 130, kaon_0_S = 310, kaon_0  = 311, kaon_star_0 = 313, kaon_plus = 321, kaon_star_plus = 323,
  D_plus = 411, D_star_plus = 413, D_0 = 421, D_star_0 = 423, D_plus_S = 431,
  phi = 333, rho_0 = 113, rho_plus = 213, omega = 223, delta_plus_plus = 523,
  lambda = 3122, proton = 2212,
};

// https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/DataFormats/ParticleFlowCandidate/interface/PFCandidate.h
// https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/RecoJets/JetProducers/src/JetSpecific.cc
enum class ParticleType {
  X = 0,        // undefined
  e = 11,       // electron
  mu = 13,      // muon
  gamma = 22,   // photon
  h = 211,      // charged hadron
  h0 = 130,     // neutral hadron
  h_HF = 1,     // HF tower identified as a hadron
  egamma_HF = 2 // HF tower identified as an EM particle
};

enum class Decay {
  nodecay =0,
  uu=11, dd=22, ss=33, cc=44, bb=55, tt=66, light = 123, qq=77, gg=2121,
  ee=1111, mumu=1313, tautau=1515, ll=1717, vv=1818,
  gammagamma=2222, ZZ=232300, WW=242400,
  ZZeeee=232301,       ZZmumumumu=232302, ZZtautautautau=232303, ZZvvvv=232304,
  ZZeemumu=232305,     ZZeetautau=232306, ZZeevv=232307,
  ZZmumutautau=232308, ZZmumuvv=232309,   ZZtautauvv=232310,
  ZZllll=232311,           ZZqqqq=232312,         ZZqqll=232313,
  WWveve=242401,       WWvevmu=242402,    WWvevtau=242403,
  WWvlvl=242404,       WWqqqq=242405,         WWvlqq=242406,
  Wb=245,
};



const float Z_mass   = 91.1876;
const float W_mass   = 80.376;
const float H_mass   = 125.10;
const float top_mass = 172.9;

// const std::vector<int> lqids = {9000008, 9000009};
const std::vector<int> lqids = {9000005};
// const std::vector<int> psiids  = {9000006, 9000007};
const std::vector<int> psiids  = {9000009};
// const std::vector<int> dmids = {9000005};
const std::vector<int> chiids = {9000007};
