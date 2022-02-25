#pragma once
#include <TString.h>

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "LEAF/Analyzer/include/TagConstants.h"
#include "LEAF/Analyzer/include/RunConstants.h"
#include "LEAF/Analyzer/include/GenLevelConstants.h"
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
