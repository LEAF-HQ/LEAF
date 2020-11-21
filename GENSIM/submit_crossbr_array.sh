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


function peval { echo "--> $@"; eval "$@"; }

JOBLIST=$1
STARTINDEX=$2
EFFECTIVEINDEX=$(( $STARTINDEX + $SLURM_ARRAY_TASK_ID ))
echo "--> EFFECTIVEINDEX = ${EFFECTIVEINDEX}"


peval "cd $CODEFOLDER"
TASKCMD=$(cat $JOBLIST | sed "${EFFECTIVEINDEX}q;d")
peval "${TASKCMD}"

echo Done with mother-job.
