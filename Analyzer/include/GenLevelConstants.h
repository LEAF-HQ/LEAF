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
  gammagamma=2222, ZZ=2323, WW=2424,
  ZZeeee=232311111111,       ZZmumumumu=232313131313, ZZtautautautau=232315151515, ZZvvvv=232318181818,
  ZZeemumu=232311111313,     ZZeetautau=232311111515, ZZeevv=232311111818,
  ZZmumutautau=232313131515, ZZmumuvv=232313131818,   ZZtautauvv=232315151818,
  ZZllll=23231717,           ZZqqqq=23237777,         ZZqqll=2323771717,
  WWveve=242412111211,       WWvevmu=242412111413,    WWvevtau=242412111615,
  WWvlvl=242418171817,       WWqqqq=24247777,         WWvlqq=2424181777,
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
