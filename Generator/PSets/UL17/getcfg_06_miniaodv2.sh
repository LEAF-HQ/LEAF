#!/bin/bash
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_6_20/src ] ; then
 echo release CMSSW_10_6_20 already exists
else
scram p CMSSW CMSSW_10_6_20
fi
cd CMSSW_10_6_20/src
eval `scram runtime -sh`


scram b
cd ../../

cmsDriver.py  --python_filename SUS-RunIISummer20UL17MiniAODv2-00029_1_cfg.py --eventcontent MINIAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier MINIAODSIM --fileout file:SUS-RunIISummer20UL17MiniAODv2-00029.root --conditions 106X_mc2017_realistic_v9 --step PAT --procModifiers run2_miniAOD_UL --geometry DB:Extended --filein "dbs:/ZZTo4L_M-1toInf_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17RECO-106X_mc2017_realistic_v6-v1/AODSIM" --era Run2_2017 --runUnscheduled --no_exec --mc -n 10000

rm -r CMSSW_10_6_20
