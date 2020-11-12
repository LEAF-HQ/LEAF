#!/bin/bash
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
#SBATCH --export NONE

echo HOME:                $HOME
echo USER:                $USER
echo SLURM_JOB_ID:        $SLURM_JOB_ID
echo SLURM_ARRAY_TASK_ID: $SLURM_ARRAY_TASK_ID
echo HOSTNAME:            $HOSTNAME

JOBLIST=$1

cd $CODEFOLDER
TASKCMD=$(cat $JOBLIST | sed "${SLURM_ARRAY_TASK_ID}q;d")
echo $TASKCMD
eval $TASKCMD

echo Done with mother-job.
