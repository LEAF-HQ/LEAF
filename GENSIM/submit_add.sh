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

# each worker node has local /scratch space to be used during job run
export TMPDIR=/scratch/$USER/addGensim_${SLURM_JOB_ID}
mkdir -p $TMPDIR
echo TMPDIR: $TMPDIR

# actual job
source /t3home/areimers/setup_slurm.sh
cd /work/areimers/LQDM/GENSIM/simple_files
SAMPLE=$1
echo SAMPLE: ${SAMPLE}
TARGET=${SAMPLE}_GENSIM_simple.root
SOURCE=${SAMPLE}_GENSIM_simple_*.root
eval "hadd -f ${TARGET} ${SOURCE}"
eval "rm ${SOURCE}"

# cleaning of temporal working dir when job was completed:
rm -rf $TMPDIR
echo Removed TMPDIR: $TMPDIR
echo Done.
