#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>



const std::vector<std::string> Run2Years = {"UL16preVFP", "UL16postVFP", "UL17", "UL18"};

const std::map<std::string, std::vector<std::string> > Reco2Years = {
  {"UL",  Run2Years},
};

const std::map<std::string, std::vector<std::string>> Year2Run = {
  {"UL16preVFP",  {"B", "C", "D", "E", "F"}},
  {"UL16postVFP", {"F", "G", "H"}},
  {"UL17",        {"B", "C", "D", "E", "F"}},
  {"UL18",        {"A", "B", "C", "D"}},
};

const std::map<std::string, float > Year2Lumi = {
  {"UL16preVFP",  19.53},
  {"UL16postVFP", 16.80},
  {"UL17",        41.48},
  {"UL18",        59.83},
};

const std::map<std::string, std::map<std::string, float > > Year2Run2Lumi = {
  {"UL16preVFP",  {
    {"B",  5.83},
    {"C",  2.62},
    {"D",  4.29},
    {"E",  4.07},
    {"F",  3.14},
  }},
  {"UL16postVFP", {
    {"F",  3.14},
    {"G",  7.65},
    {"H",  8.74},
  }},
  {"UL17",        {
    {"B",  4.80},
    {"C",  9.57},
    {"D",  4.25},
    {"E",  9.31},
    {"F", 13.54},
  }},
  {"UL18",        {
    {"A", 14.03},
    {"B",  7.07},
    {"C",  6.90},
    {"D", 31.84},
  }},
};

const std::map<std::string, std::map<std::string, int > > Year2Runnumber = {
  {"UL16preVFP",  {{"min", 272007}, {"max", 278801}}},
  {"UL16postVFP", {{"min", 278802}, {"max", 284044}}},
  {"UL17",        {{"min", 297046}, {"max", 306462}}},
  {"UL18",        {{"min", 315252}, {"max", 325175}}},
};

const std::map<std::string, std::map<std::string, std::map<std::string, int > > > Year2Run2Runnumber = {
  {"UL16preVFP",  {
    {"B",  {{"min", 272007}, {"max", 275376}}},
    {"C",  {{"min", 275657}, {"max", 276283}}},
    {"D",  {{"min", 276315}, {"max", 276811}}},
    {"E",  {{"min", 276831}, {"max", 277420}}},
    {"F",  {{"min", 277772}, {"max", 278801}}},
  }},
  {"UL16postVFP", {
    {"F",  {{"min", 278802}, {"max", 278808}}},
    {"G",  {{"min", 278820}, {"max", 280385}}},
    {"H",  {{"min", 280919}, {"max", 284044}}},
  }},
  {"UL17",        {
    {"B",  {{"min", 297046}, {"max", 299329}}},
    {"C",  {{"min", 299368}, {"max", 302029}}},
    {"D",  {{"min", 302030}, {"max", 303434}}},
    {"E",  {{"min", 303824}, {"max", 304797}}},
    {"F",  {{"min", 305040}, {"max", 306462}}},
  }},
  {"UL18",        {
    {"A",  {{"min", 315252}, {"max", 316995}}},
    {"B",  {{"min", 317080}, {"max", 319310}}},
    {"C",  {{"min", 319337}, {"max", 320065}}},
    {"D",  {{"min", 320673}, {"max", 325175}}},
  }},
};


const std::unordered_map<std::string, std::unordered_map<std::string, std::string> > JERC_Info = {
  {"UL16preVFP", {
    {"JEC_Version", "Summer19UL17_V5"},
    {"JER_Version", "Summer19UL17_JRV2"},
  }},
  {"UL16postVFP", {
    {"JEC_Version", "Summer19UL17_V5"},
    {"JER_Version", "Summer19UL17_JRV2"},
  }},
  {"UL17", {
    {"JEC_Version", "Summer19UL17_V5"},
    {"JER_Version", "Summer19UL17_JRV2"},
  }},
  {"UL18", {
    {"JEC_Version", "Summer19UL17_V5"},
    {"JER_Version", "Summer19UL17_JRV2"},
  }},

};
