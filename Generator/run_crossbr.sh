echo "--> User input:"
MG_FOLDER=$1
JOBNAME=$2
CARDDIR=$3
CMSSWDIR=$4
LOGDIR=$5
TARGETFOLDER=$6
PROCNAME=$7
NCORES=$8
echo $MG_FOLDER
echo $JOBNAME
echo $CARDDIR
echo "<-- End user input."

function peval { echo "--> $@"; eval "$@"; }

# set up CMSSW and root
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd $CMSSWDIR/src
eval `scramv1 runtime -sh`
eval 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MG_FOLDER/HEPTools/hepmc/lib'
eval 'export CXXFLAGS="$CXXFLAGS -I$MG_FOLDER/HEPTools/boost/include"' # silly lhapdf doesn't find boost includes otherwise... seems to be a MG/LHAPDF error
eval 'export PYTHIA8DATA=$MG_FOLDER/HEPTools/pythia8/share/Pythia8/xmldoc'

# create local workdir on /scratch for MG to work in
WORKDIR="/scratch/$USER/LQDM_CrossBR/$JOBNAME"  # local workdir for slurm
peval "mkdir -p ${WORKDIR}"
peval "cd ${WORKDIR}"

# start MadGraph
# cd /work/areimers/MG5_aMC_v2_7_2
# echo "--> cd $MG_FOLDER"
# cd $MG_FOLDER
RELPATH_TO_CARDS=`realpath --relative-to="${PWD}" ${CARDDIR}`
echo $RELPATH_TO_CARDS
RUN_CARD=${JOBNAME}_run_card.dat
PROC_CARD=${JOBNAME}_proc_card.dat
CUST_CARD=${JOBNAME}_customizecards.dat
echo $RELPATH_TO_CARDS/$CUST_CARD

# create file with commands
COMMANDFILE=commands_$JOBNAME.dat
echo "command file: $COMMANDFILE"
echo "analysis=OFF" >> $COMMANDFILE
echo "shower=OFF" >> $COMMANDFILE
echo "done" >> $COMMANDFILE
cat $RELPATH_TO_CARDS/$CUST_CARD >> $COMMANDFILE
echo "done" >> $COMMANDFILE

# start process generation
echo "--> Starting process generation with command:"
peval "${MG_FOLDER}/bin/mg5_aMC $RELPATH_TO_CARDS/$PROC_CARD"
# ./bin/mg5_aMC $RELPATH_TO_CARDS/$PROC_CARD

echo "--> copying run_card:"
peval "cp $RELPATH_TO_CARDS/$RUN_CARD $JOBNAME/Cards/run_card.dat"
# cp $RELPATH_TO_CARDS/$RUN_CARD $JOBNAME/Cards/run_card.dat

# now generate some events to get the cross section and BRs (going to be in the param_card.dat)
echo "--> Starting event generation with command: "
peval "cat $COMMANDFILE | $JOBNAME/bin/generate_events --multicore --nb_core=${NCORES}"
# cat $COMMANDFILE | $JOBNAME/bin/generate_events --multicore --nb_core=${NCORES}

# copy logfile and param_card for later scrutiny
peval "mkdir -p $TARGETFOLDER/$PROCNAME"
echo "--> Copying logfile and param_card.dat to target directory:"
peval "cp $LOGDIR/${SLURM_JOB_NAME}-${SLURM_ARRAY_JOB_ID}-${SLURM_ARRAY_TASK_ID}.out $TARGETFOLDER/$PROCNAME/${JOBNAME}_crosssection.txt"
# cp $LOGDIR/${SLURM_JOB_NAME}-${SLURM_ARRAY_JOB_ID}-${SLURM_ARRAY_TASK_ID}.out $TARGETFOLDER/$PROCNAME/${JOBNAME}_crosssection.txt

peval "cp $JOBNAME/Cards/param_card.dat $TARGETFOLDER/$PROCNAME/${JOBNAME}_param_card.dat"


# echo "--> Removing MG process folder $JOBNAME and associated command file"
peval "cd .."
peval "ls"
peval "rm -rf $WORKDIR"
peval "ls"


echo Done with daughter-job.
