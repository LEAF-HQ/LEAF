#!/bin/bash
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_6_19_patch3/src ] ; then
  echo release CMSSW_10_6_19_patch3 already exists
else
  scram p CMSSW CMSSW_10_6_19_patch3
fi
cd CMSSW_10_6_19_patch3/src
eval `scram runtime -sh`

# Download fragment from McM
curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/TOP-RunIISummer20UL18wmLHEGEN-00070 --retry 3 --create-dirs -o Configuration/GenProduction/python/TOP-RunIISummer20UL18wmLHEGEN-00070-fragment.py
[ -s Configuration/GenProduction/python/TOP-RunIISummer20UL18wmLHEGEN-00070-fragment.py ] || exit $?;


scram b
cd ../..



# cmsDriver command
cmsDriver.py Configuration/GenProduction/python/TOP-RunIISummer20UL18wmLHEGEN-00070-fragment.py --python_filename TOP-RunIISummer20UL18wmLHEGEN-00070_1_cfg.py --eventcontent RAWSIM,LHE --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN,LHE --fileout file:TOP-RunIISummer20UL18wmLHEGEN-00070.root --conditions 106X_upgrade2018_realistic_v4 --beamspot Realistic25ns13TeVEarly2018Collision --customise_commands process.source.numberEventsInLuminosityBlock="cms.untracked.uint32(100)" --step LHE,GEN --geometry DB:Extended --era Run2_2018 --no_exec --mc -n 123

rm -rf CMSSW_10_6_19_patch3
