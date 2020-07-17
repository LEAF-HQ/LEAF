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
# cmsDriver.py step1 --fileout file:B2G-RunIISummer19UL17DIGIPremix-00041.root  --pileup_input "dbs:/Neutrino_E-10_gun/RunIISummer19ULPrePremix-UL17_106X_mc2017_realistic_v6-v1/PREMIX" --mc --eventcontent PREMIXRAW --runUnscheduled --datatier GEN-SIM-DIGI --conditions 106X_mc2017_realistic_v6 --step DIGI,DATAMIX,L1,DIGI2RAW --procModifiers premix_stage2 --nThreads 8 --geometry DB:Extended --datamix PreMix --era Run2_2017 --python_filename B2G-RunIISummer19UL17DIGIPremix-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 2104
cmsDriver.py step1 --fileout file:B2G-RunIISummer19UL17DIGIPremix-00041.root  --pileup_input "dbs:/Neutrino_E-10_gun/RunIISummer19ULPrePremix-UL17_106X_mc2017_realistic_v6-v1/PREMIX" --mc --eventcontent PREMIXRAW --runUnscheduled --datatier GEN-SIM-DIGI --conditions 106X_mc2017_realistic_v6 --step SIM,DIGI,DATAMIX,L1,DIGI2RAW --procModifiers premix_stage2 --nThreads 8 --geometry DB:Extended --datamix PreMix --era Run2_2017 --python_filename B2G-RunIISummer19UL17DIGIPremix-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 2104
# cmsDriver.py step1 --fileout file:B2G-RunIISummer19UL17DIGIPremix-00041.root --mc --eventcontent PREMIXRAW --runUnscheduled --datatier GEN-SIM-DIGI --conditions 106X_mc2017_realistic_v6 --step SIM,DIGI,DATAMIX,L1,DIGI2RAW --procModifiers premix_stage2 --nThreads 8 --geometry DB:Extended --datamix PreMix --era Run2_2017 --python_filename B2G-RunIISummer19UL17DIGIPremix-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 2104

rm -r CMSSW_10_6_12
