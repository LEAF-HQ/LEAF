# This script must be sourced before working in this folder.


# Append path to our own libraries to LD_LIBRARY_PATH, such that our programs can use them!
export MACROPATH=$(readlink -f macros)
export MACROLIBPATH=$(readlink -f macros/lib)
export MACROLIBPATH=$MACROLIBPATH:$(readlink -f macros/external/lib)

export MACROBINPATH=$(readlink -f macros/bin)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MACROLIBPATH
export PATH=$PATH:$MACROBINPATH
