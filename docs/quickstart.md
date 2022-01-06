# Quickstart guide

Welcome to the quickstart guide for performing an analysis using LEAF! The steps below will introduce some essential features of any data analysis.

## Prerequisites

This guide assumes you have just installed LEAF and created a fresh analysis following the instructions in the [installation guide](installation.md).

!!! note
    For this guide, we will assume the new analysis was named `MyAnalysis`. If you chose a different name, please adjust all the commands below accordingly. You will not need to modify any code, but only the commands to be executed

If you have not yet set up your own analysis, either complete the installation and setup of a new analysis first, or make sure to adjust the commands and file contents shown below to your structure.

## Event selection and histogram production

The first step will be to loop over some test samples of (mock-)data, a simulated background, and two simulated signals. Within the loop, events will be selected and a number of histograms will be filled. We will use the `AnalysisTool` class to perform this task. A new incarnation of such a tool was created when setting up the new analysis. It can be found in `LEAF/MyAnalysis/Analyzer/src/MyAnalysisTool.cc`.

The settings of the job, such as the files to run over or the input/output paths are configured in an `xml` file, which can be found in `LEAF/MyAnalysis/Analyzer/config/MyAnalysis.xml`. Be sure to have a look into both files and understand what is going on.

The configuration file is already prepared to run over the test samples (in `LEAF/.testsamples/*.root`), so we can simply run the `Analyzer` executable locally, passing the configuration file as an argument:

```bash
cd $LEAFPATH/MyAnalysis/Analyzer/config
Analyzer MyAnalysis.xml
```

!!! note
    The above command can be run from anywhere, then the relative (or absolute, if preferred) path to the `xml` file must be adjusted accordingly. However, this is not true for all programs along the way, so it is best to execute all commands from within the folder that contains the file passed as an argument.



The default configuration file will instruct the `Analyzer` to store the output root files in a folder on the same level as the main LEAF folder, `MyAnalysis/2017/Preselection/InitialSetup`. To get there, do

```bash
cd $LEAFPATH/../MyAnalysis/2017/Preselection/InitialSetup
```

 You will find four root files in that folder, one for each of the samples we processed.

In a real analysis, a given process will often be split into different samples binned in a certain variable (for example HT, PT, or M). In order to merge samples adding up to the same process, we will use the `Submitter`:

```bash
cd $LEAFPATH/MyAnalysis/Analyzer/config
submit.py MyAnalysis.xml -p
```

!!! note
    In this exercise, this step would not really be necessary, but in a full-fledged analysis it will be.

You can see two new files created, one for data and one for background. Note that the names of the new samples are slightly changed.

## Plotting distributions

The next step will be to visualize the events processed by plotting distributions of relevant observables and comparing different processes. The `Plotter` package takes care of this. Just like the `Analyzer` executable, also the `Plotter` executable is configured through an `xml` file, which contains information on the datasets to be plotted.

When creating the new analysis, a corresponding configuration file for the `Plotter` has already been created, so simply plot the distributions:

```bash
cd $LEAFPATH/MyAnalysis/Plotter
Plotter Default.xml
```

The distributions will be created in the folder containing the output root files of the previous step, which is on the same level as the main LEAF folder: `MyAnalysis/2017/Preselection/InitialSetup/plots/distributions`. To get there, do
```bash
cd $LEAFPATH/../MyAnalysis/2017/Preselection/InitialSetup/plots/distributions
```

Feel free to inspect the plots before moving on. Also feel free to try and add some new event selection steps and plot the default distributions after those. Adding more observables could be useful as well.

## Post-analysis

After having selected events and plotted distributions at the different stages of the event selection, now we will perform some further analysis to understand our selection and finally infer the presence or absence of a signal over the standard model expectation.

Together with the new analysis came a basic collection of analysis scripts, with are contained in the `PostAnalyzer` folder. It contains one main executable script. Let us execute it:
```bash
cd $LEAFPATH/MyAnalysis/Analyzer/PostAnalyzer
./steer.py
```

This will produce two results at the moment. They are new plots to be found in the usual output folder. To get there, do
```bash
cd $LEAFPATH/../MyAnalysis/2017/Preselection/InitialSetup/plots
```


 The first are two plots of the efficiency of each selection step applied in the beginning of this quickstart, one with a linear and one with a logarithmic y-axis scale. This type of plot is useful for monitoring the behavior of the event selections applied.

The second new result is the expected upper limit on our test signal cross section, as extracted from the selected background and signal. Note that the data are not considered here for the moment.

## Conclusion

In this short example, you have performed a pre-defined event selection, you have visualized the intermediate steps and the final outcome. Last, you have run additional scripts on your fully selected events to compute the selection efficiency of each step and expected upper limits on the signal production cross section. Details on each LEAF package can be found in this documentation as well, see the links in [here](README.md).
