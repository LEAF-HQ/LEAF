# Submitter

The Submitter package is a helper tool for the [Analyzer](packages/analyzer.md). It allows for convenient yet efficient submission submission of jobs to the local cluster.


## Supported clusters

These are the current supproted clusters. Links to tutorials and settings are provided.

- [SLURM](https://support.ceci-hpc.be/doc/_contents/QuickStart/SubmittingJobs/SlurmTutorial.html)
    - [PSI guide](https://www.psi.ch/en/lin-no-computing/cluster-usage)
- [HTCondor](https://htcondor.readthedocs.io/en/latest/users-manual/quick-start-guide.html)
    - @CERN ([guide](https://batchdocs.web.cern.ch/local/quick.html))
    - @Desy ([guide](https://confluence.desy.de/pages/viewpage.action?pageId=81094361))

It takes care of the parallelized (re-)submission of Analyzer jobs, retrieving the output, merging individual and groups of processes and prepare them for plotting. No coding should be necessary for a user of LEAF here.

## Create User specific settings

This allows to store user-specific options to run the jobs into the cluster. The output in the form of a dictionary is store in a json inside the `$SUBMITTERPATH` folder. An example is given in `$SUBMITTERPATH/Settings_exampleuser.json`.

To create your personal setting, you can simply create your own json (The path and naming scheme MUST be the same. Just place you username instead of exampleuser.), or run the following command.

```bash
./createUserSettings.py -u <username> -k <cluster>  -e <email>
```

!!! Note
    This command should be done only once, or anytime one wants to update its own settings.


## Usage

Once you set up your own [user settings](#create), you can simply run you xml file as:

```bash
submit.py MyAnalysis.xml <option-1> <option-2> <arg-option-2> <option-3>
```

Multiple options, available in the `Submitter` class are allowed:

| Long name | Short name | Default | Description |
| --------- | ---------- | ------- | ----------- |
| --clean           | -c |  False  | Remove the local and the remote workdir.|
| --divide          | -d |  False  | Divide the xml file into chunks, create workdir.|
| --local           | -l |         | Run split jobs locally.|
| --cluster         | -k |         | Overwrite cluster settings defined by the user specific settings.|
| --submit          | -s |  False  | Submit split jobs to cluster.|
| --output          | -o |  False  | Check the status of the expected output files.|
| --add             | -a |  False  | Add split files back together for samples that are fully processed.|
| --forceadd        | -f |  False  | Force hadding.|
| --notreeadd       | -t |  False  | Add split files without adding the trees.|
| --allowincomplete | -i |  False  | Ignore the non-existent files and does the hadd nonetheless.|
| --plothadd        | -p |  False  | Hadd files to groups used for plotting and further analysis.|



## Inside-the-box

There is some magic going inside the above settings. Here, the minimum info for the expert user.

### CondorBase

This class is designed to make usage of the [python bindings](https://htcondor.readthedocs.io/en/latest/apis/python-bindings/index.html) for `HTCondor`. It takes care of creating the job info (default values are stored, but can always be modified via `ModifyJobInfo`). The minimal inputs are the executable and its arguments.

This class takes care of submitting a single job (`SubmitJob`) as well as multiple jobs (`SubmitManyJobs`). The latter is implemented as default in the `Submitter` class.

Already available, but not implemented anywhere yet, is the `CheckStatus` option to monitor the job queue.

This class is generic and can be easily used to submit any type of job to the HTCondor, as it's not linked to the xml structure provided by the main `Analyser`.
