#!/bin/bash
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out  # replace default slurm-SLURM_JOB_ID.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
##SBATCH --export ALL

echo HOME: $HOME
echo USER: $USER
echo SLURM_JOB_ID: $SLURM_JOB_ID
echo HOSTNAME: $HOSTNAME
pwd

# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/test_${SLURM_JOB_ID}_${SLURM_ARRAY_TASK_ID}
mkdir -p $TMPDIR
echo TMPDIR: $TMPDIR

# actual job
source /t3home/areimers/setup_slurm.sh
cd /work/areimers/LQDM/GENSIM
export TASKID=$SLURM_ARRAY_TASK_ID
echo $TASKID
JOBLIST=$1
TASKCMD=$(cat $JOBLIST | sed "${TASKID}q;d")
echo $TASKCMD
eval $TASKCMD

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
