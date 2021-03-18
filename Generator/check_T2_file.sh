FILENAME=$1

COMMAND="LD_LIBRARY_PATH='' PYTHONPATH='' gfal-ls -l ${FILENAME}"
eval "${COMMAND}" || { echo "Opening the file failed" ; exit 1 ; }
