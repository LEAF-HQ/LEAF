#!/bin/bash

export SCRAM_ARCH=slc7_amd64_gcc700

source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_2_16_UL/src ] ; then
  echo release CMSSW_10_2_16_UL already exists
else
  scram p CMSSW CMSSW_10_2_16_UL
fi
cd CMSSW_10_2_16_UL/src
eval `scram runtime -sh`

scram b
cd ../..

# cmsDriver command
cmsDriver.py  --python_filename TOP-RunIISummer20UL18HLT-00117_1_cfg.py --eventcontent RAWSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --fileout file:TOP-RunIISummer20UL18HLT-00117.root --conditions 102X_upgrade2018_realistic_v15 --customise_commands 'process.source.bypassVersionCheck = cms.untracked.bool(True)' --step HLT:2018v32 --geometry DB:Extended --filein file:TOP-RunIISummer20UL18DIGIPremix-00117.root --era Run2_2018 --no_exec --mc -n 123


rm -rf CMSSW_10_2_16_UL
