#!/bin/bash
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -J add_tuples
#SBATCH -e %x-%A.err
#SBATCH -o %x-%A.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
##SBATCH --export ALL

echo HOME: $HOME
echo USER: $USER
echo SLURM_JOB_ID: $SLURM_JOB_ID
echo HOSTNAME: $HOSTNAME
pwd

ARCHTAG=$1
CMSSWDIR=$2
BASEFOLDER=$3
TARGETFOLDERNAME=$4
CMDFILE=$5

# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/addGensim_${SLURM_JOB_ID}
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
TASKCMD=$(cat $CMDFILE)
echo $TASKCMD
eval $TASKCMD

# remove folder with individual files and recreate it (to remove single files)
echo "removing folder: $TARGETFOLDERNAME"
RMDIRCOMMAND='LD_LIBRARY_PATH='' PYTHONPATH='' gfal-rm -r $TARGETFOLDERNAME; sleep 5s;'
# eval "$RMDIRCOMMAND"
echo "recreating folder: $TARGETFOLDERNAME"
MKDIRCOMMAND='LD_LIBRARY_PATH='' PYTHONPATH='' gfal-mkdir -p $TARGETFOLDERNAME; sleep 5s;'
eval "$MKDIRCOMMAND"

# copy the file from /scratch to T2
FILENAME=$(ls *.root)
echo "copying file $FILENAME"
eval "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f file:////$PWD/$FILENAME $TARGETFOLDERNAME"
echo "removing file $FILENAME in $PWD"
eval "rm $FILENAME"

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
