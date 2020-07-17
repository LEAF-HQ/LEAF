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
cmsDriver.py step1 --filein MYINFILE.root --fileout file:B2G-RunIISummer19UL17NanoAOD-00011.root --mc --eventcontent NANOEDMAODSIM --datatier NANOAODSIM --conditions 106X_mc2017_realistic_v7 --step NANO --nThreads 8 --era Run2_2017 --python_filename B2G-RunIISummer19UL17NanoAOD-00011_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 10000

rm -r CMSSW_10_6_12
