#! /bin/bash

# Settings for SLURM
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A-%a.err
#SBATCH -o %x-%A-%a.out
#SBATCH --export NONE
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch

echo HOME:                $HOME
echo USER:                $USER
echo SLURM_JOB_ID:        $SLURM_JOB_ID
echo SLURM_ARRAY_TASK_ID: $SLURM_ARRAY_TASK_ID
echo HOSTNAME:            $HOSTNAME

#Pick up arguments
CODEFOLDER=$1       # ......./LQDM/GENSIM
ARCHTAG=$2
CMSSWDIR=$3         # Location of CMSSW for this production
TARGETFOLDERNAME=$4 # Basefolder to store files to. Still need to create sample-specific subfolder (LQM1400_DM1323232321_X93281)
JOBLIST=$5          # List of cmsRun commands


#Set up CMSSW and PYTHONPATH
eval "source $VO_CMS_SW_DIR/cmsset_default.sh"
# eval "export SCRAM_ARCH=slc6_amd64_gcc700"
eval "export SCRAM_ARCH=$ARCHTAG"
eval "cd $CMSSWDIR/src"
eval `scramv1 runtime -sh`

# to include python modules in basefolder and PSet folder
export PYTHONPATH=$PYTHONPATH:$CODEFOLDER
# export PYTHONPATH=$CODEFOLDER/PSets:$PYTHONPATH
echo $PYTHONPATH

# each worker node has local /scratch space to be used during job run. This is where the output of cmsRun will end up in.
export TMPDIR=/scratch/$USER/tmpdir_${SLURM_JOB_ID}_${SLURM_ARRAY_TASK_ID}
echo TMPDIR: $TMPDIR
mkdir -p $TMPDIR
cd $TMPDIR

echo $LD_LIBRARY_PATH
echo $PATH
echo $PYTHONPATH

# the joblist contains a list of 'cmsRun pSet.py ......' commands
TASKCMD=$(cat $JOBLIST | sed "${SLURM_ARRAY_TASK_ID}q;d")
echo $TASKCMD
TASK_FAILED=0
eval $TASKCMD || { echo "cmsRun failed. Going to delete rootfile(s)." ; rm -rf $(ls *.root) ; }


# Delete the "_LHE.root" file and move the output to the T2 (the only file with *.root left :) )
eval "ls"
eval "rm *_LHE.root"
FILENAME=$(ls *.root)

# create sample-specific folder and all missing parent folders
echo "creating folder: $TARGETFOLDERNAME"
MKDIRCOMMAND='LD_LIBRARY_PATH='' PYTHONPATH='' gfal-mkdir -p $TARGETFOLDERNAME; sleep 10s;'
eval "$MKDIRCOMMAND"

# copy the file from /scratch to T2
echo "copying file $FILENAME"
# eval "cp $FILENAME /work/areimers/LQDM/GENSIM/"
eval "LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy -f file:////$PWD/$FILENAME $TARGETFOLDERNAME"
echo "removing file $FILENAME in $PWD"
eval "rm $FILENAME"

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
