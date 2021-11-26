#!/bin/bash
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_6_12/src ] ; then
 echo release CMSSW_10_6_12 already exists
else
scram p CMSSW CMSSW_10_6_12
fi
cd CMSSW_10_6_12/src
eval `scram runtime -sh`

curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/B2G-RunIISummer20UL17wmLHEGEN-00130 --retry 3 --create-dirs -o Configuration/GenProduction/python/B2G-RunIISummer20UL17wmLHEGEN-00130-fragment.py

scram b
cd ../../
cmsDriver.py Configuration/GenProduction/python/B2G-RunIISummer20UL17wmLHEGEN-00130-fragment.py --python_filename B2G-RunIISummer20UL17wmLHEGEN-00130_1_cfg.py --eventcontent RAWSIM,LHE --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN,LHE --fileout file:B2G-RunIISummer20UL17wmLHEGEN-00130.root --conditions 106X_mc2017_realistic_v6 --beamspot Realistic25ns13TeVEarly2017Collision  --step LHE,GEN --geometry DB:Extended --era Run2_2017 --no_exec --mc -n 5450

rm -r CMSSW_10_6_12
