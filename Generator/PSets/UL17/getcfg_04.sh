#!/bin/bash
export SCRAM_ARCH=slc7_amd64_gcc630
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_9_4_14_UL_patch1/src ] ; then
 echo release CMSSW_9_4_14_UL_patch1 already exists
else
scram p CMSSW CMSSW_9_4_14_UL_patch1
fi
cd CMSSW_9_4_14_UL_patch1/src
eval `scram runtime -sh`


scram b
cd ../../
cmsDriver.py step1 --fileout file:B2G-RunIISummer19UL17HLT-00041.root --mc --eventcontent RAWSIM --datatier GEN-SIM-RAW --conditions 94X_mc2017_realistic_v15 --customise_commands 'process.source.bypassVersionCheck = cms.untracked.bool(True)' --step HLT:2e34v40 --nThreads 8 --geometry DB:Extended --era Run2_2017 --python_filename B2G-RunIISummer19UL17HLT-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 2754

rm -r CMSSW_9_4_14_UL_patch1
