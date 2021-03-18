# This script must be sourced from this exact folder before working in this folder.


# Append path to our own libraries and paths to LD_LIBRARY_PATH and PATH and PYTHONPATH, such that our programs can use them!
export LEAFPATH=$(readlink -f .)
export MACROPATH=$(readlink -f macros)
export MACROLIBPATH=${MACROPATH}/lib
export MACROBINPATH=${MACROPATH}/bin
export SUBMITTERPATH=$(readlink -f Submitter)
export PLOTTERPATH=$(readlink -f Plotter)
export PLOTTERBINPATH=${PLOTTERPATH}/bin
export GENERATORPATH=$(readlink -f Generator)
export NANOAODTOOLS_BASE=${GENERATORPATH}/NanoAODTools

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MACROLIBPATH
export PATH=${PATH}:${MACROBINPATH}:${PLOTTERBINPATH}:${SUBMITTERPATH}
export PYTHONPATH=$PYTHONPATH:$GENERATORPATH
export PYTHONPATH=${PYTHONPATH}:${NANOAODTOOLS_BASE}/build/lib/python
