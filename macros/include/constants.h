#pragma once
#include <TString.h>

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>


// const std::vector<int> lqids = {9000008, 9000009};
const std::vector<int> lqids = {9000005};
// const std::vector<int> psiids  = {9000006, 9000007};
const std::vector<int> psiids  = {9000009};
// const std::vector<int> dmids = {9000005};
const std::vector<int> chiids = {9000007};

// 2016: 35920 --- 2017: 41530

const std::unordered_map<std::string, std::unordered_map<std::string, std::string> > jecRunMap = {
  {"Summer16", {
    {"B", "BCD"},
    {"C", "BCD"},
    {"D", "BCD"},
    {"BCD", "BCD"},
    {"E", "EF"},
    {"F", "EF"},
    {"EF", "EF"},
    {"G", "GH"},
    {"H", "GH"},
    {"GH", "GH"}
  }},
  {"Fall17", {
    {"B", "B"},
    {"C", "C"},
    {"D", "DE"},
    {"E", "DE"},
    {"DE", "DE"},
    {"F", "F"}
  }},
  {"Summer19UL17", {
    {"B", "B"},
    {"C", "C"},
    {"D", "D"},
    {"E", "E"},
    {"F", "F"}
  }},
  {"Autumn18", {
    {"A", "A"},
    {"B", "B"},
    {"C", "C"},
    {"D", "D"}
  }},
};

const std::vector<std::string> runPeriods2016 = {"B", "C", "D", "E", "F", "G", "H"};
const std::vector<std::string> runPeriods2017 = {"B", "C", "D", "E", "F"};
const std::vector<std::string> runPeriods2018 = {"A", "B", "C", "D"};

const std::unordered_map<std::string, std::vector<std::string>> yearRunMap = {
  {"2016", runPeriods2016},
  {"2017", runPeriods2017},
  {"2018", runPeriods2018},
};

const std::unordered_map<std::string, std::unordered_map<std::string, std::string> > JERC = {
  {"2016", {
    {"JEC", "Summer16_07Aug2017_V11"},
    {"JER", "Summer16_25nsV1b"},
  }},
  {"2017", {
    {"JEC", "Fall17_17Nov2017_V32"},
    {"JER", "Fall17_V3b"},
  }},
  {"2018", {
    {"JEC", "Autumn18_V19"},
    {"JER", "Autumn18_V7b"},
  }},
};

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
