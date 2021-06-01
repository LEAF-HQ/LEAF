# Installation

## Getting the code

Getting the LEAF code is easy, there is a script that takes care of everything for you. It will set up LEAF and a CMSSW version in the directory the script is executed from. You will need access to /cvmfs in order for the compilation to work.
To set get LEAF, do:

```bash
wget https://raw.githubusercontent.com/reimersa/LEAF/master/get_leaf.sh
source get_leaf.sh   
```

## Initial compilation
After downloading the code and checking out the necessary repositories, most notably the JECDatabase and JRDatabase, some packages of LEAF must be compiled to generate all executables used in the various steps of a data analysis:

```bash
cd Analyzer
make clean
make -j
```
```bash
cd ../Plotter
make clean
make -j
cd ..
```

At this point, LEAF is fully functional and its packages can be used. However, if it is intended to perform a usual data analysis, it is necessary to set up a new analysis skeleton, which can be modified and extended according to each user's needs and wishes. Here is how:

## Setting up a new analysis
There is a handy macro that creates all structures needed for a new analysis and integrates it into the LEAF compilation workflow. All that needs to be done is

```bash
cd $LEAFPATH/Analyzer
./createNewAnalysis.py <NewAnalysisName>
make clean
make -j
```

This will create all necessary files and folders for the new analysis to be compiled and linked automatically when comiling the Analyzer package. See the [Analyzer documentation](packages/analyzer.md) for details. It is advisable to choose a concise name for `<NewAnalysisName>`, it will be typed frequently. Also make sure the first few letters are convenient to type.
