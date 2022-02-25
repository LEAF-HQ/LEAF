#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "TMath.h"

enum ParticleID {
  unknown=0,
  u=1, d=2, s=3, c=4, b=5, t=6, q=7,
  e=11, mu=13, tau=15, l=17,
  v_e=12, v_mu=14, v_tau=16, v=18,
  g=21, photon=22, Z=23, W=24, H=25,
};


enum Decay {
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
