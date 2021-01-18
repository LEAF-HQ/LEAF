#! /bin/bash

# Settings for SLURM
#
#SBATCH --account=t3
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out
#SBATCH --export SCRAM_ARCH,CMSSW_BASE
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch

eval "source $VO_CMS_SW_DIR/cmsset_default.sh"
eval "cd $CMSSW_BASE/src"
eval `scramv1 runtime -sh`

# add macro folder to PATH after CMSSW modified it
JOBLIST=$1
PATH=$PATH:$2
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$3

# the joblist contains a list of 'cmsRun pSet.py ......' commands
# TASKCMD="Analyzer /work/areimers/LQDM/macros/LQDM/config/workdir_LQDMPreselection/PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0/PsiPsiToLQChi_MLQ1000_MPS567_MC1457_L1p0_3.xml"
TASKCMD=$(cat $JOBLIST | sed "${SLURM_ARRAY_TASK_ID}q;d")
echo $TASKCMD
eval $TASKCMD
echo Done.
