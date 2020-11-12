#!/bin/bash
#
#SBATCH --account=t3
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x.err
#SBATCH -o %x.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
#SBATCH --export NONE

echo "Running job on machine `uname -a`"


function peval { echo "--> $@"; eval "$@"; }
# function peval { echo "--> $@"; }

peval "cd /scratch/${USER}"

for FILE in $(ls)
do
  peval "rm -r /scratch/${USER}/$FILE"
done

echo "Done cleaning."
exit 0
