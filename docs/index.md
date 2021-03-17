# LEAF, the LHC Event Analysis Framework

# Introduction

These pages document the [RooStats](https://twiki.cern.ch/twiki/bin/view/RooStats/WebHome) / [RooFit](https://root.cern.ch/roofit) - based software tools used for statistical analysis within the [Higgs PAG](HiggsWG) - **combine**.

Combine provides a command line interface to many different statistical techniques available inside RooFit/RooStats used widely inside CMS.

The package exists in GIT under [https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit](https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit)

For more information about GIT and its usage in CMS, see [http://cms-sw.github.io/cmssw/faq.html](http://cms-sw.github.io/cmssw/faq.html)

The code can be checked out from GIT and compiled on top of a CMSSW release that includes a recent RooFit/RooStats

# Setting up the environment and installation

The instructions below are for installation within a CMSSW environment

## For end users that don't need to commit or do any development

You can find the latest releases on github under [https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit/releases](https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit/releases)

### CC7 release `CMSSW_10_2_X` - recommended version

Setting up the environment (once):

```sh
export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
```
Update to a recommended tag - currently the recommended tag is **v8.2.0**: [see release notes](https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit/releases/tag/v8.2.0)

```sh
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v8.2.0
scramv1 b clean; scramv1 b # always make a clean build
```
