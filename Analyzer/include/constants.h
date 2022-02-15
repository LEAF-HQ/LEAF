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

// const std::unordered_map<std::string, std::unordered_map<std::string, std::string> > jecRunMap = {
//   {"Summer16", {
//     {"B", "BCD"},
//     {"C", "BCD"},
//     {"D", "BCD"},
//     {"BCD", "BCD"},
//     {"E", "EF"},
//     {"F", "EF"},
//     {"EF", "EF"},
//     {"G", "GH"},
//     {"H", "GH"},
//     {"GH", "GH"}
//   }},
//   {"Fall17", {
//     {"B", "B"},
//     {"C", "C"},
//     {"D", "DE"},
//     {"E", "DE"},
//     {"DE", "DE"},
//     {"F", "F"}
//   }},
//   {"Summer19UL17", {
//     {"B", "B"},
//     {"C", "C"},
//     {"D", "D"},
//     {"E", "E"},
//     {"F", "F"}
//   }},
//   {"Autumn18", {
//     {"A", "A"},
//     {"B", "B"},
//     {"C", "C"},
//     {"D", "D"}
//   }},
// };

// const std::vector<std::string> runPeriods2016 = {"B", "C", "D", "E", "F", "G", "H"};
// const std::vector<std::string> runPeriods2017 = {"B", "C", "D", "E", "F"};
// const std::vector<std::string> runPeriods2018 = {"A", "B", "C", "D"};
//
// const std::unordered_map<std::string, std::vector<std::string>> yearRunMap = {
//   {"2016", runPeriods2016},
//   {"2017", runPeriods2017},
//   {"2018", runPeriods2018},
// };

// All pairs for a run period are inclusive of both lower & upper numbers
// const std::map<TString, std::map<std::pair<unsigned int, unsigned int>, TString>>
//   run_number_map = {
//     // taken from https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis
//     { "2016", {
//         {std::pair(272007, 275376), "B" },
//         {std::pair(275657, 276283), "C" },
//         {std::pair(276315, 276811), "D" },
//         {std::pair(276831, 277420), "E" },
//         {std::pair(277772, 278808), "F" },
//         {std::pair(278820, 280385), "G" },
//         {std::pair(280919, 284044), "H" },
//     }},
//     // taken from https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis
//     { "2017", {
//         {std::pair(297020, 299329), "B" },
//         {std::pair(299337, 302029), "C" },
//         {std::pair(302030, 303434), "D" },
//         {std::pair(303435, 304826), "E" },
//         {std::pair(304911, 306462), "F" },
//     }},
//     // taken from https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
//     { "2018", {
//         {std::pair(315252, 316995), "A" },
//         {std::pair(316998, 319312), "B" },
//         {std::pair(319313, 320393), "C" },
//         {std::pair(320394, 325273), "D" },
//     }},
// };

// const std::unordered_map<std::string, std::unordered_map<std::string, std::string> > JERC = {
//   // {"2016", {
//   //   {"JEC", "Summer16_07Aug2017_V11"},
//   //   {"JER", "Summer16_25nsV1b"},
//   // }},
//   {"2017", {
//     {"JEC", "Summer19UL17_V5"},
//     {"JER", "Summer19UL17_JRV2"},
//   }},
//   // {"2018", {
//   //   {"JEC", "Autumn18_V19"},
//   //   {"JER", "Autumn18_V7b"},
//   // }},
// };

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
