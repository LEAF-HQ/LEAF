# This script must be sourced from this exact folder before working in this folder.

# Set up LEAF folder structure
export LEAFPATH=$(readlink -f .)
export ANALYZERPATH=$(readlink -f Analyzer)
export ANALYZERLIBPATH=${ANALYZERPATH}/lib
export ANALYZERBINPATH=${ANALYZERPATH}/bin
export SUBMITTERPATH=$(readlink -f Submitter)
export PLOTTERPATH=$(readlink -f Plotter)
export PLOTTERBINPATH=${PLOTTERPATH}/bin
export GENERATORPATH=$(readlink -f Generator)
export SAMPLESPATH=$(readlink -f Samples)

# Set up correct CMSSW version and scram architecure
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $LEAFPATH/../CMSSW_10_6_12/src
eval `scramv1 runtime -sh`
cd $LEAFPATH


# Append path to our own libraries and paths to LD_LIBRARY_PATH and PATH and PYTHONPATH, such that our programs can use them!
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ANALYZERLIBPATH
export PATH=${PATH}:${ANALYZERBINPATH}:${PLOTTERBINPATH}:${SUBMITTERPATH}
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$LEAFPATH
export PYTHONPATH=$PYTHONPATH:${GENERATORPATH}:${LEAFPATH}

# LHAPDF
cd $CMSSW_BASE/src
export LHAPDFLIB=`scram tool tag lhapdf LIBDIR`
export LHAPDFINC=`scram tool tag lhapdf INCLUDE`
cd $LEAFPATH

# Combine
export CMSSW_COMBINE_BASE=$(readlink -f $LEAFPATH/../CMSSW_10_2_13)
export COMBINEPATH=$(readlink -f HiggsAnalysis/CombinedLimit)
export PATH=${PATH}:${COMBINEPATH}/exe:${COMBINEPATH}/scripts
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${COMBINEPATH}/lib:
export PYTHONPATH=${PYTHONPATH}:${COMBINEPATH}/lib/python:${COMBINEPATH}/lib
