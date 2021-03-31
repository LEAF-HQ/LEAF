# This script must be sourced from this exact folder before working in this folder.


# Append path to our own libraries and paths to LD_LIBRARY_PATH and PATH and PYTHONPATH, such that our programs can use them!
export LEAFPATH=$(readlink -f .)
export ANALYZERPATH=$(readlink -f Analyzer)
export ANALYZERLIBPATH=${ANALYZERPATH}/lib
export ANALYZERBINPATH=${ANALYZERPATH}/bin
export SUBMITTERPATH=$(readlink -f Submitter)
export PLOTTERPATH=$(readlink -f Plotter)
export PLOTTERBINPATH=${PLOTTERPATH}/bin
export GENERATORPATH=$(readlink -f Generator)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ANALYZERLIBPATH
export PATH=${PATH}:${ANALYZERBINPATH}:${PLOTTERBINPATH}:${SUBMITTERPATH}
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$LEAFPATH
export PYTHONPATH=$PYTHONPATH:$GENERATORPATH

# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/gcc/7.0.0-omkpbe2/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/lcg/root/6.12.07-gnimlf5/bin/thisroot.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/gsl/2.2.1-omkpbe2/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/tbb/2018_U1-omkpbe2/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/cms/vdt/0.4.0-gnimlf/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/boost/1.63.0-gnimlf/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/pcre/8.37-omkpbe2/etc/profile.d/init.sh
# . /cvmfs/cms.cern.ch/${SCRAM_ARCH}/external/eigen/64060da8461a627eb25b5a7bc0616776068db58b/etc/profile.d/init.sh

export CMSSW_COMBINE_BASE=$(readlink -f $LEAFPATH/../CMSSW_10_2_13)

export COMBINEPATH=$(readlink -f HiggsAnalysis/CombinedLimit)
export PATH=${PATH}:${COMBINEPATH}/exe:${COMBINEPATH}/scripts
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${COMBINEPATH}/lib:
export PYTHONPATH=${PYTHONPATH}:${COMBINEPATH}/lib/python:${COMBINEPATH}/lib
