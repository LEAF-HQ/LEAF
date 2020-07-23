# This script must be sourced from this exact folder before working in this folder.


# Append path to our own libraries to LD_LIBRARY_PATH, such that our programs can use them!
export MACROPATH=$(readlink -f macros)
export MACROLIBPATH=$(readlink -f macros/lib)
export MACROBINPATH=$(readlink -f macros/bin)
export GENSIMPATH=$(readlink -f GENSIM)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MACROLIBPATH
export PATH=$PATH:$MACROBINPATH
export PYTHONPATH=$PYTHONPATH:$GENSIMPATH
