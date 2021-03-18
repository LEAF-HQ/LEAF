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

curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/B2G-RunIISummer19UL17wmLHEGEN-00041 --retry 2 --create-dirs -o Configuration/GenProduction/python/B2G-RunIISummer19UL17wmLHEGEN-00041-fragment.py
[ -s Configuration/GenProduction/python/B2G-RunIISummer19UL17wmLHEGEN-00041-fragment.py ] || exit $?;

scram b
cd ../../
cmsDriver.py Configuration/GenProduction/python/B2G-RunIISummer19UL17wmLHEGEN-00041-fragment.py --fileout file:B2G-RunIISummer19UL17wmLHEGEN-00041.root --mc --eventcontent RAWSIM,LHE --datatier GEN,LHE --conditions 106X_mc2017_realistic_v6 --beamspot Realistic25ns13TeVEarly2017Collision --step LHE,GEN --geometry DB:Extended --era Run2_2017 --python_filename B2G-RunIISummer19UL17wmLHEGEN-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 5450

rm -r CMSSW_10_6_12
