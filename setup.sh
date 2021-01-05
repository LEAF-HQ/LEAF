# This script must be sourced from this exact folder before working in this folder.


# Append path to our own libraries to LD_LIBRARY_PATH, such that our programs can use them!
export MACROPATH=$(readlink -f macros)
export MACROLIBPATH=${MACROPATH}/lib
export MACROBINPATH=${MACROPATH}/bin
export PLOTTERPATH=${MACROPATH}/Plotter
export PLOTTERBINPATH=${PLOTTERPATH}/bin
export GENSIMPATH=$(readlink -f GENSIM)
export NANOAODTOOLS_BASE=${GENSIMPATH}/NanoAODTools

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MACROLIBPATH
export PATH=${PATH}:${MACROBINPATH}:${PLOTTERBINPATH}
export PYTHONPATH=$PYTHONPATH:$GENSIMPATH
export PYTHONPATH=${PYTHONPATH}:${NANOAODTOOLS_BASE}/build/lib/python
