#! /bin/bash
#$ -l h=!@t3wn5*

# Settings for SLURM
#
#SBATCH --account=t3
#SBATCH --time 01:00:00
#SBATCH --chdir /work/areimers/workdir_slurm
#SBATCH -e %x-%A.err
#SBATCH -o %x-%A.out
#SBATCH --mail-type FAIL
#SBATCH --mail-user arne.reimers@physik.uzh.ch
##SBATCH --export ALL

printf "######################################################\n"
printf "##   Generate GENSIM sample for SLQ %-16s##\n" "$1"
printf "######################################################\n"

# USER INPUT
PSET="$1"
GRIDPACK="$2"
SAMPLE="$3"

# SETTINGS
DBG=2
SEOUTFILES="*GENSIM*.root"
BASEDIR="/work/areimers/LQDM/GENSIM"
CMSSWDIR="/work/areimers/CMSSW_10_2_10"
XROOTD="root://t3dcachedb03.psi.ch"
GFAL="gsiftp://t3se01.psi.ch"
SE_HOME="/pnfs/psi.ch/cms/trivcat/store/user/$USER"
JOBDIR="LQDM"

# OPTIONAL
OPTIND=4 # look for optional arguments after first two non-optional ones
INDEX=1
NCORES=1
NEVENTS=100
echo ">>> arguments are $@"
while getopts c:i:M:N: option; do
case "${option}" in
  i) INDEX=${OPTARG};;
  N) NEVENTS=${OPTARG};;
  c) NCORES=${OPTARG};;
esac
done
[ $NEVENTS -le 0 ] && NEVENTS=1000

cat <<EOF

###########################################
##            JOB PARAMETERS:            ##
###########################################
  \$PSET=$PSET
  \$GRIDPACK=$GRIDPACK
  \$SAMPLE=$SAMPLE
  \$INDEX=$INDEX
  \$NCORES=$NCORES
  \$SEOUTFILES=$SEOUTFILES
  \$NEVENTS=$NEVENTS
  \$OPTS=$OPTS
EOF

WORKDIR="/scratch/$USER/$JOBDIR/$SAMPLE/index_$INDEX"
OUTDIR="$WORKDIR" # where SEOUTFILES are generated
SERESULTDIR="$SE_HOME/GENSIM/$JOBDIR/${SAMPLE}"



##### MONITORING/DEBUG INFORMATION #######################################################

DATE_START=`date +%s`
echo "Job started at " `date`
function peval { echo ">>> $@"; eval "$@"; }
cat <<EOF

###########################################
##       QUEUEING SYSTEM SETTINGS:       ##
###########################################
  \$HOME=$HOME
  \$USER=$USER
  \$JOB_ID=$JOB_ID
  \$JOB_NAME=$JOB_NAME
  \$HOSTNAME=$HOSTNAME
  \$TASK_ID=$TASK_ID
  \$QUEUE=$QUEUE
EOF



##### SET ENVIRONMENT ####################################################################

if test -e "$WORKDIR"; then
   echo "ERROR: WORKDIR ($WORKDIR) already exists!" >&2
   peval "ls $WORKDIR" >&2
   #exit 1
fi
peval "mkdir -p $WORKDIR"
if [ ! -d $WORKDIR ]; then
   echo "ERROR: Failed to create workdir ($WORKDIR)! Aborting..." >&2
   exit 1
fi

# ENSURE RESULT DIRECTORY ON PSI T3 SE
if [ ! -d $SERESULTDIR ]; then
  peval "gfal-mkdir -p $GFAL/$SERESULTDIR" # always before cmsenv!
  TRY=0
  printf ">>> checking mkdir success..."
  while [ ! -d $SERESULTDIR -a $TRY -lt 20 ]; do
    printf "."; sleep 4; TRY=$((TRY+1))
  done; echo
  if [ ! -d $SERESULTDIR ]; then
     echo "ERROR: Failed to create resultdir on the SE ($SERESULTDIR)! Continuing anyway..." >&2
     #exit 1
  fi
fi

cat <<EOF

###########################################
##             JOB SETTINGS:             ##
###########################################
  \$BASEDIR=$BASEDIR
  \$WORKDIR=$WORKDIR
  \$WORKMGDIR=$WORKMGDIR
  \$WORKCARDDIR=$WORKCARDDIR
  \$CMSSWDIR=$CMSSWDIR
  \$RESULTDIR=$RESULTDIR
  \$REPORTDIR=$REPORTDIR
  \$SERESULTDIR=$SERESULTDIR
EOF

echo " "
echo "###########################################"
echo "##           SETUP ENVIRONMENT           ##"
echo "###########################################"

echo ">>> setting up CMSSW"
peval "source $VO_CMS_SW_DIR/cmsset_default.sh" || exit 1
peval "export SCRAM_ARCH=slc6_amd64_gcc630" || exit 1
peval "cd $CMSSWDIR/src"  || exit 1
peval "eval `scramv1 runtime -sh`"
if test $? -ne 0; then
   echo "ERROR: Failed to source scram environment" >&2
   exit 1
fi
peval "export PYTHONPATH=$BASEDIR:$PYTHONPATH" # to include python modules
echo $PYTHONPATH



##### MAIN FUNCTIONALITY CODE ############################################################

echo " "
echo "###########################################"
echo "##         MY FUNCTIONALITY CODE         ##"
echo "###########################################"

# GENERATE
peval "cd $WORKDIR"
peval "cmsRun $BASEDIR/$PSET gridpack=$GRIDPACK nevents=$NEVENTS index=$INDEX nThreads=$NCORES"

# RENAME output
peval "cd $OUTDIR"
peval "ls"



##### RETRIEVAL OF OUTPUT FILES AND CLEANING UP ##########################################

cd $WORKDIR
if [ 0"$DBG" -gt 0 ]; then
    echo " "
    echo "########################################################"
    echo "##   OUTPUT WILL BE MOVED TO \$RESULTDIR and \$OUTDIR   ##"
    echo "########################################################"
    echo "  \$RESULTDIR=$RESULTDIR"
    echo "  \$REPORTDIR=$REPORTDIR"
    echo "  \$PWD: " `pwd`
    peval "find . -maxdepth 2 -ls"
    peval "ls $OUTDIR"
fi

cd $OUTDIR
if test x"$SEOUTFILES" != x; then
    if [ 0"$DBG" -gt 2 ]; then
        debug="-v"
    fi
    if [[ ! -d $SERESULTDIR ]]; then
        echo ">>> $SERESULTDIR does not exist!"
        #echo "uberftp t3se01.psi.ch 'mkdir $SERESULTDIR'"
        #uberftp t3se01.psi.ch 'mkdir $SERESULTDIR'
    fi
    for outfile in `ls $SEOUTFILES`; do
        echo ">>> copying $OUTDIR/$outfile to $SERESULTDIR/$outfile"
        echo "xrdcp -d $DBG $debug --force $OUTDIR/$outfile $XROOTD/$SERESULTDIR/$outfile >&2"
        xrdcp -d $DBG $debug --force $OUTDIR/$outfile $XROOTD/$SERESULTDIR/$outfile >&2
        if test $? -ne 0; then
          echo "ERROR: Failed to copy $OUTDIR/$outfile to $SERESULTDIR/$outfile" >&2
        fi
    done
fi

printf "\nRemoving $WORKDIR (on ${HOSTNAME})\n"
rm -rf $WORKDIR

printf "\nRemoving files containing '_LHE_' in $XROOTD/$SERESULTDIR/GENSIM_LHE_$INDEX.root\n"
peval "uberftp t3se01.psi.ch 'rm $SERESULTDIR/GENSIM_LHE_$INDEX.root'"
# peval "gfal-rm $XROOTD/$SERESULTDIR/GENSIM_LHE_$INDEX.root"



##########################################################################################

DATE_END=`date +%s`
RUNTIME=$((DATE_END-DATE_START))
printf "\n#####################################################"
printf "\n    Job finished at %s" "$(date)"
printf "\n    Wallclock running time: %02d:%02d:%02d" "$(( $RUNTIME / 3600 ))" "$(( $RUNTIME % 3600 /60 ))" "$(( $RUNTIME % 60 ))"
printf "\n#####################################################\n\n"

exit 0
