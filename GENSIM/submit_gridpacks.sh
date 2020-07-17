#!/bin/bash
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A.err
#SBATCH -o %x-%A.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch

ulimit -a

echo HOME: $HOME
echo USER: $USER
echo SLURM_JOB_ID: $SLURM_JOB_ID
echo HOSTNAME: $HOSTNAME
pwd

echo "--> User input:"
CMSSW_MG_FOLDER=$1
JOBNAME=$2
CARDDIR=$3
QUEUEMODE=$4
echo $CMSSW_MG_FOLDER
echo $JOBNAME
echo $CARDDIR
echo $QUEUEMODE
echo "<-- End user input."

# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/gridpack_workdir_${SLURM_JOB_ID}
echo TMPDIR: $TMPDIR
mkdir -p $TMPDIR

# actual job
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700

# cd /work/areimers/CMSSW_10_2_10/src/genproductions/bin/MadGraph5_aMCatNLO
cd $CMSSW_MG_FOLDER
RELPATH_TO_CARDS=`realpath --relative-to="${PWD}" ${CARDDIR}`

TASKCMD="./gridpack_generation.sh ${JOBNAME} ${RELPATH_TO_CARDS} ${QUEUEMODE}"

echo $TASKCMD
eval $TASKCMD


# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
sstat -j $SLURM_JOB_ID.batch --format=jobid,MaxRSS,MaxVMSize
