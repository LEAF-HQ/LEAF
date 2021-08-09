# Tools for analysing job execution time

This folder contains a set of scripts to analyse the job execution time of the different steps of event generation. It should help tuning the settings for further iterations. 

## Getting job execution time

First, on needs to filter out the execution time from the job log files. Each job writes in the log file the total execution time on a single line, in the format ```Execution time: hh:mm:ss```. To obtain a file with the execution times for all DR jobs, for example, the following command can be used: 

	cat *_gensim_* | grep 'Execution time' 2>&1 | tee timeGENSIMstep.dat
	cat *dr* | grep 'Execution time' > timeDRstep.dat
	cat *_aod_* | grep 'Execution time' 2>&1 | tee timeAODstep.dat

On can also filter out the time for a single job, using the job number, etc... 

## Analysing the timing

The script ```AnalyseJobTiming.py``` reads a text file containing the timing info lines from the job log and can porduce histograms of the execution time distribution: 

	python AnalyseJobTiming.py timeDRstep.dat 

The first agrument is the text file obtained in the previous step. It can optionally take more arguments: 

	python AnalyseJobTiming.py timeDRstep.dat --threshold value

Will only consider jobs with execution time higher than the provided value. It is used to veto jobs that did not properly run, and crashed due to missing input file for example. 

	python AnalyseJobTiming.py timeDRstep.dat --threshold 1 --prefix somestring

Can be specified to remove a substring ```somestring``` from the lines in the input text file. By thefault, this option is set to ```Execution time: ``` which is the prefix used in the job output logs. 

	python AnalyseJobTiming.py timeDRstep.dat --threshold 1 --save image.pdf 

Saves the histogram with filename ```image.pdf```, or any other desired format, for further use. By default the histogram is not saved. 