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

JOBLIST=$1
TARGETFOLDERNAME=$2


# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/test_${SLURM_JOB_ID}_${SLURM_ARRAY_TASK_ID}
mkdir -p $TMPDIR
echo TMPDIR: $TMPDIR
cd $TMPDIR

# create sample-specific folder and all missing parent folders
echo "creating folder: $TARGETFOLDERNAME"
MKDIRCOMMAND='LD_LIBRARY_PATH='' PYTHONPATH='' gfal-mkdir -p $TARGETFOLDERNAME; sleep 10s;'
eval "$MKDIRCOMMAND"

# actual job
source /t3home/areimers/setup.sh
# cd /work/areimers/LQDM/GENSIM
export TASKID=$SLURM_ARRAY_TASK_ID
echo $TASKID
TASKCMD=$(cat $JOBLIST | sed "${TASKID}q;d")
echo $TASKCMD
eval $TASKCMD

# copy the file from /scratch to storage element
FILENAME=$(ls *.root)
echo "copying file $FILENAME"
eval "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f file:////$PWD/$FILENAME $TARGETFOLDERNAME"
echo "removing file $FILENAME in $PWD"
eval "rm $FILENAME"

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
