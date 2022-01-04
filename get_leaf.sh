# script to get all necessary ingredients to download and run LEAF. Running standalone.

# set up architecture
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh

# get CMSSW_10_6_28 for UL
if [ -r CMSSW_10_6_28/src ] ; then
 echo "Release CMSSW_10_6_28 already exists, using that."
else
  echo "Setting up CMSSW_10_6_28."
  cmsrel CMSSW_10_6_28 
fi

# get CMSSW_10_2_13 for Combine
if [ -r CMSSW_10_2_13/src ] ; then
 echo "Release CMSSW_10_2_13 already exists, using that."
else
  echo "Setting up CMSSW_10_2_13."
  cmsrel CMSSW_10_2_13
fi


# get CMSSW_9_4_14_UL_patch1 for HLT step in UL generation
if [ -r CMSSW_9_4_14_UL_patch1/src ] ; then
 echo "Release CMSSW_9_4_14_UL_patch1 already exists, using that."
else
  echo "Setting up CMSSW_9_4_14_UL_patch1."
  cmsrel CMSSW_9_4_14_UL_patch1
fi

cd CMSSW_9_4_14_UL_patch1/src
eval `scramv1 runtime -sh`
scram b
cd ../../

cd CMSSW_10_6_28/src
eval `scramv1 runtime -sh`
scram b
cd ../../

# download LEAF
git clone https://github.com/LEAF-HQ/LEAF.git LEAF
cd LEAF
export LEAFPATH=$(readlink -f .)

# clone JEC and JR databases into Analyzer
cd $LEAFPATH/Analyzer
git clone https://github.com/cms-jet/JECDatabase.git
git clone https://github.com/cms-jet/JRDatabase.git

# download Higgs Combine
cd ../
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v8.2.0
cd ../../

# all folders there, set up environment
cd $LEAFPATH
source $PWD/setup.sh

# compile all!
cd $ANALYZERPATH
make clean
make

cd $PLOTTERPATH
make clean
make

cd $COMBINEPATH
source $PWD/env_standalone.sh
make clean
make

cd $LEAFPATH
echo $PWD
echo "--> Done setting up LEAF!"
