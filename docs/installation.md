# Installation

## Getting the code (once)

Getting the LEAF code is easy, there is a script that takes care of everything for you. It will set up LEAF and a CMSSW version in the directory the script is executed from. You will need access to /cvmfs in order for the compilation to work. The latest tag that has been tested extensively is used.

After downloading the code and checking out the necessary repositories, most notably the `JECDatabase`, `JRDatabase`, and `Combine`, some packages of LEAF will be compiled to generate all executables used in the various steps of a data analysis. This is all done automatically, so nothing to worry about. The following snippet will install LEAF and several versions of `CMSSW` in the folder the snippet below is executed from. It will reuse existing installations of `CMSSW` of the correct versions, if there are any. Make sure to run in a clean shell:

```bash
wget https://github.com/reimersa/LEAF/blob/v1.0/get_leaf.sh
source get_leaf.sh   
```

At this point, LEAF is fully functional and all its packages can be used. You should now close this shell and start again in a fresh one. If it is intended to perform a usual data analysis, it is necessary to set up a new analysis skeleton, which can be modified and extended according to each user's needs and wishes. Simply follow the remaining steps on this page.

## Setup (every time)

Each package of LEAF can be used more or less standalone, even though there are some interconnections between the packages. To set up LEAF in a fresh shell, simply `cd` into your LEAF folder and source the setup script:
```bash
cd <PATH/TO/LEAF>
source setup.sh
```

## Setting up a new analysis (once)
There is a handy macro that creates all structures needed for a new analysis and integrates it into the LEAF compilation workflow. All that needs to be done (in an environment where LEAF has already been [set up](#setup-(every-time))) is

```bash
cd $LEAFPATH/Analyzer
./createNewAnalysis.py <NewAnalysisName>
make clean
make -j
```

This will create all necessary files and folders for the new analysis to be compiled and linked automatically when comiling the Analyzer package. See the [Analyzer documentation](packages/analyzer.md) for details. It is advisable to choose a concise name for `<NewAnalysisName>`, it will be typed frequently. Also make sure the first few letters are convenient to type.

If you are new to LEAF, you can follow the [quickstart guide](quickstart.md) to run a small, self-contained test analysis, introducing some essential features. If you already know what you are doing, you are all set. Detailed information can be found in the documentation of each LEAF package, which is linked from the top navigation bar and from the [homepage](README.md).
