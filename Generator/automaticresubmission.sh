#! /bin/bash

echo "Automatical resubmission running..."

while [ true ]
do 
	if [[ $(squeue -u mhuwiler | grep resub | wc -l) -lt 2 ]]
	then 
		echo Resumitting
		python newsteer.py --noproxy 
		printf "\n\nAutomatic resubmission running...\n\n"
		sleep 2
	else 
		sleep 5
		#echo more than two running jobs
	fi
done 
