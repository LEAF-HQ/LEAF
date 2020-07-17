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
cmsDriver.py step1 --filein "dbs:/ZprimeToTT_M1000_W10_TuneCP2_PSweights_13TeV-madgraph-pythiaMLM-pythia8/RunIISummer19UL17RECO-106X_mc2017_realistic_v6-v1/AODSIM" --fileout file:B2G-RunIISummer19UL17MiniAOD-00041.root --mc --eventcontent MINIAODSIM --runUnscheduled --datatier MINIAODSIM --conditions 106X_mc2017_realistic_v7 --step PAT --nThreads 8 --geometry DB:Extended --era Run2_2017 --python_filename B2G-RunIISummer19UL17MiniAOD-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 10000

rm -r CMSSW_10_6_12
