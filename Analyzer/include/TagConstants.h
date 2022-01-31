#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>



const std::string normtag = "/cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json";
const std::string afs_cern_path = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/";

const std::map<std::string, std::map<std::string, std::string > > Year2PuLumi = {
  {"UL16preVFP",  {
    {"JSON",     afs_cern_path+"Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"Pileup",   afs_cern_path+"Collisions16/13TeV/PileUp/UltraLegacy/pileup_latest.txt"},
    {"PileupMC", "SimGeneral.MixingModule.mix_2016_25ns_UltraLegacy_PoissonOOTPU_cfi"},
    {"HN",       "https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3577/1.html"},
  }},
  {"UL16postVFP", {
    {"JSON",     afs_cern_path+"Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"Pileup",   afs_cern_path+"Collisions16/13TeV/PileUp/UltraLegacy/pileup_latest.txt"},
    {"PileupMC", "SimGeneral.MixingModule.mix_2016_25ns_UltraLegacy_PoissonOOTPU_cfi"},
    {"HN",       "https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3577/1.html"},
  }},
  {"UL17",        {
    {"JSON",     afs_cern_path+"Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt"},
    {"Pileup",   afs_cern_path+"Collisions17/13TeV/PileUp/UltraLegacy/pileup_latest.txt"},
    {"PileupMC", "SimGeneral.MixingModule.mix_2017_25ns_UltraLegacy_PoissonOOTPU_cfi"},
    {"HN",       "https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3499.html "},
  }},
  {"UL18",        {
    {"JSON",     afs_cern_path+"Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},
    {"Pileup",   afs_cern_path+"Collisions18/13TeV/PileUp/UltraLegacy/pileup_latest.txt"},
    {"PileupMC", "SimGeneral.MixingModule.mix_2018_25ns_UltraLegacy_PoissonOOTPU_cfi"},
    {"HN",       "https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3526.html "},
  }},
};
