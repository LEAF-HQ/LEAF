#pragma once
#include <TString.h>

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "LEAF/Analyzer/include/TagConstants.h"
#include "LEAF/Analyzer/include/RunConstants.h"

// const std::vector<int> lqids = {9000008, 9000009};
const std::vector<int> lqids = {9000005};
// const std::vector<int> psiids  = {9000006, 9000007};
const std::vector<int> psiids  = {9000009};
// const std::vector<int> dmids = {9000005};
const std::vector<int> chiids = {9000007};

// 2016: 35920 --- 2017: 41530

const std::vector<std::string> JEC_L1L2L3Res = {"L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"};
const std::vector<std::string> JER_SFPt = {"SF", "PtResolution"};

const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>> > JERCLevels = {
  {"JEC", {
    {"default", JEC_L1L2L3Res}
  }},
  {"JER", {
    {"default", JER_SFPt}
  }},
};
