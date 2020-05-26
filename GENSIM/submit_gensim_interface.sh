#! /bin/bash


# Settings for SLURM
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch

echo HOME: $HOME
echo USER: $USER
echo SLURM_JOB_ID: $SLURM_JOB_ID
echo HOSTNAME: $HOSTNAME

# each worker node has local /scratch space to be used during job run
# export TMPDIR=/scratch/$USER/test_${SLURM_JOB_ID}
# mkdir -p /scratch/$USER/test_${SLURM_JOB_ID}
# echo TMPDIR: $TMPDIR

# actual job
# cd /work/areimers/LQDM/GENSIM
export TASKID=$SLURM_ARRAY_TASK_ID
echo $TASKID
JOBLIST=$1
echo $JOBLIST
TASKCMD=$(cat $JOBLIST | sed "${TASKID}q;d")
echo $TASKCMD
eval $TASKCMD

# cleaning of temporal working dir when job was completed:
# rm -rf $TMPDIR
# echo Removed TMPDIR: $TMPDIR
# echo Done.
