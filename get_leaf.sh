# script to get all necessary ingredients to download and run LEAF. Running standalone.

# set up architecture
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
echo $PWD

# get CMSSW_10_2_13 for combine
if [ -r CMSSW_10_2_13/src ] ; then
 echo "Release CMSSW_10_2_13 already exists, using that."
else
  echo "Setting up CMSSW_10_2_13."
  cmsrel CMSSW_10_2_13
fi

# get CMSSW_10_6_12 for UL
if [ -r CMSSW_10_6_12/src ] ; then
 echo "Release CMSSW_10_6_12 already exists, using that."
else
  echo "Setting up CMSSW_10_6_12."
  cmsrel CMSSW_10_6_12
fi
echo $PWD

cd CMSSW_10_6_12/src
echo $PWD
eval `scramv1 runtime -sh`
scram b
cd ../../
echo $PWD

# download LEAF
git clone https://github.com/reimersa/LEAF.git LEAF
cd LEAF
echo $PWD
export LEAFPATH=$(readlink -f .)
echo $LEAFPATH
echo $PWD

# clone JEC and JR databases into Analyzer
cd $LEAFPATH/Analyzer
echo $PWD
git clone https://github.com/cms-jet/JECDatabase.git
git clone https://github.com/cms-jet/JRDatabase.git
echo $PWD

# download Higgs Combine
cd ../
echo $PWD
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
sleep 2
ls -lrth
echo $PWD
cd HiggsAnalysis/CombinedLimit
echo $PWD
sleep 1
git fetch origin
echo $PWD
sleep 1
git checkout v8.2.0
echo $PWD
sleep 1
ls -lrth
sleep 1
cd ../../
echo $PWD
# cd $CMSSW_BASE/src
# git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
# cd HiggsAnalysis/CombinedLimit/
# git fetch origin
# git checkout v8.2.0
# scramv1 b clean
# scramv1 b
# cd ../../
# cmsrel CMSSW_10_2_13
# cd CMSSW_10_2_13/src
# cmsenv
# git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
# cd HiggsAnalysis/CombinedLimit
# cd $LEAFPATH

# all folders there, set up environment
sleep 2
cd $LEAFPATH
sleep 2
ls -lrth
sleep 5
source setup.sh
echo $PWD

sleep 2
echo $PATH
sleep 1
echo $LD_LIBRARY_PATH
sleep 1
echo $CXXFLAGS

# compile all!
cd $ANALYZERPATH
echo $PWD
ls -lrth
sleep 2
make clean
echo $PWD
sleep 2
make -j
echo $PWD

cd $PLOTTERPATH
echo $PWD
sleep 2
make clean
echo $PWD
sleep 2
make -j
echo $PWD

cd $COMBINEPATH
echo $PWD
sleep 2
ls -lrth
sleep 1
source env_standalone.sh
echo $PWD
sleep 2
make clean
echo $PWD
sleep 2
make -j
echo $PWD
sleep 2

cd $LEAFPATH
echo $PWD
echo "--> Done setting up LEAF!"
