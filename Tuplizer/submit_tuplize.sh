#!/bin/bash
#
#SBATCH --account=t3
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out  # replace default slurm-SLURM_JOB_ID.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
##SBATCH --export ALL

echo HOME: $HOME
echo USER: $USER
echo SLURM_JOB_ID: $SLURM_JOB_ID
echo HOSTNAME: $HOSTNAME
echo VOMS: $X509_USER_PROXY
pwd

ARCHTAG=$1
CMSSWDIR=$2
BASEFOLDER=$3
TARGETFOLDERNAME=$4
JOBLIST=$5
STARTINDEX=$6

EFFECTIVEINDEX=$(( $STARTINDEX + $SLURM_ARRAY_TASK_ID ))


# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/tmpdir_${SLURM_JOB_ID}_${EFFECTIVEINDEX}
mkdir -p $TMPDIR
echo TMPDIR: $TMPDIR

# set up environment
eval "export SCRAM_ARCH=$ARCHTAG"
eval "source $VO_CMS_SW_DIR/cmsset_default.sh"
eval "cd $CMSSWDIR/src"
eval `scramv1 runtime -sh`
eval "cd $BASEFOLDER"
eval "source setup.sh"

# actual job
cd $TMPDIR
export TASKID=$EFFECTIVEINDEX
echo $TASKID
TASKCMD=$(cat $JOBLIST | sed "${TASKID}q;d")
echo $TASKCMD
eval $TASKCMD

# create sample-specific folder and all missing parent folders
echo "creating folder: $TARGETFOLDERNAME"
MKDIRCOMMAND='LD_LIBRARY_PATH='' PYTHONPATH='' gfal-mkdir -p $TARGETFOLDERNAME; sleep 10s;'
echo $MKDIRCOMMAND
eval "$MKDIRCOMMAND"

# copy the file from /scratch to T3
echo "ls -lrth"
ls -lrth
FILENAME=$(ls *.root)
echo "copying file $FILENAME"
eval "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f file:////$PWD/$FILENAME $TARGETFOLDERNAME"
echo "removing file $FILENAME in $PWD"
eval "rm $FILENAME"

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
