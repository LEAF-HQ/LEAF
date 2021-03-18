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


scram b
cd ../../
cmsDriver.py step1 --fileout file:B2G-RunIISummer19UL17RECO-00041.root --mc --eventcontent AODSIM --runUnscheduled --datatier AODSIM --conditions 106X_mc2017_realistic_v6 --step RAW2DIGI,L1Reco,RECO,RECOSIM --nThreads 8 --geometry DB:Extended --era Run2_2017 --python_filename B2G-RunIISummer19UL17RECO-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 3979

rm -r CMSSW_10_6_12
