#! /usr/bin/env python

import os, sys, math
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
import itertools

import json
from yaml import safe_load


from utils import *
from functions import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array
import pandas as pd

from preferred_configurations import *
from tdrstyle_all import *


class CrossSectionRunner:
    def __init__(self, processnames, tag, individual_settings, general_settings, cardfolder, crosssecfolder, generatorfolder, mgfolder_local, workarea, cmssw_tag_sim, workdir_slurm, submit=False):
        self.processnames = processnames
        self.tag = tag
        self.individual_settings = individual_settings
        self.general_settings = general_settings
        self.cardfolder = cardfolder
        self.crosssecfolder = crosssecfolder
        self.generatorfolder = generatorfolder
        self.mgfolder_local = mgfolder_local
        self.workarea = workarea
        self.cmssw_tag_sim = cmssw_tag_sim
        self.workdir_slurm = workdir_slurm
        self.submit = submit



    def ProduceCards(self):

        for processname in self.processnames:
            idx = 0
            for individual_setting in self.individual_settings:
                if self.submit:
                    make_card_flex(card_template_folder=self.cardfolder+'/CrossBR', card_output_folder=self.cardfolder+'/CrossBR/%s' % (processname), processname=processname, tag=self.tag, general_settings=self.general_settings, individual_setting=individual_setting, verbose=False)
                    idx += 1
                    if idx % 20 is 0:
                        print green('--> Produced %i out of %i cards for process %s (%.2f%%).' % (idx, len(self.individual_settings), processname, float(idx)/float(len(self.individual_settings))*100))
            if not self.submit:
                print yellow('Would have produced %i cards for process %s.' % (len(self.individual_settings), processname))



    def RunMG(self, only_resubmit=False, ignore_br=True, ncores=2, runtime=(00,40), maxjobs_per_proc=50):
        runtime_str, queue = format_runtime(runtime)

        for processname in self.processnames:
            if only_resubmit:
                shortfilelist = get_filelist_crossbr(filepath=self.crosssecfolder+'/'+processname, short=True, tag=self.tag)
            njobs = 0
            commandfilename = self.generatorfolder + '/commands/CrossBR_%s.txt' % (processname)
            f = open(commandfilename, 'w')
            for individual_setting in self.individual_settings:
                # if njobs > 1: break
                jobname = get_jobname_flex(processname=processname, ordered_dict=individual_setting, tag=self.tag)
                write_command = True
                if only_resubmit:
                    write_command = False
                    if len(shortfilelist) == 0:
                        write_command = True
                    else:
                        param_card_shortname   = jobname+'_param_card_short.txt'
                        crosssection_shortname = jobname+'_crosssection_short.txt'
                        if not (crosssection_shortname in shortfilelist):
                            write_command = True
                        if not ignore_br:
                            if not (param_card_shortname in shortfilelist):
                                write_command = True
                # write to a command file the shell command: 'source run_crossbr.sh  .....' %
                command = 'source %s %s %s %s %s %s %s %s %i' % (self.generatorfolder+'/run_crossbr.sh', self.mgfolder_local, jobname, self.cardfolder+'/CrossBR/%s' % (processname), self.workarea + '/' + self.cmssw_tag_sim, self.workdir_slurm, self.crosssecfolder, processname, ncores)
                if write_command:
                    f.write(command + '\n')
                    njobs += 1
            f.close()
            slurmjobname = 'CrossBR_%s' % (processname)
            slurm_max_array_size = 4000
            submit_more_arrays = True if (njobs > slurm_max_array_size) else False
            njobs_left = njobs
            narrays = 0
            njobs_per_array = []
            if njobs == 0:
                print yellow('--> No jobs to be submitted for process %s. Continue.' % (processname))
                continue
            while njobs_left > 0:
                idx_offset = slurm_max_array_size*narrays
                arrayend = min(njobs_left, slurm_max_array_size)
                njobs_per_array.append(arrayend)
                command = 'sbatch --parsable -a 1-%i%%%i -J %s -p %s -t %s --exclude t3wn[49,50,54,40,44,39] --cpus-per-task %i --ntasks-per-core 1 submit_crossbr_array.sh %s %i' % (arrayend, maxjobs_per_proc, slurmjobname, queue, runtime_str, ncores*2, commandfilename, idx_offset)
                if self.submit:
                    jobid = int(subprocess.check_output(command.split(' ')))
                    print green("--> Submitted an array of %i jobs for process %s. Master-jobid: %i"%(njobs_per_array[narrays], processname, int(jobid)))
                else:
                    print command
                    print yellow("--> Would submit array of %i jobs for process %s"%(njobs_per_array[narrays], processname))
                njobs_left -= arrayend
                narrays += 1

    def ShortenCrossBR(self):
        for processname in self.processnames:
            longlist = get_filelist_crossbr(filepath=self.crosssecfolder+'/'+processname, short=False, tag=self.tag)
            if len(longlist) == 0:
                print green('--> No long files found for process %s.' % (processname))
                continue
            print green('--> Going to shorten %i long files.' % (len(longlist)))
            for filename in longlist:
                # is it the param card for the BR or the logfile for the cross section?
                is_param_card = True if 'param_card' in filename else False
                infilename = self.crosssecfolder+'/'+processname+'/'+filename
                shortfilename = join(self.crosssecfolder+'/'+processname+'/', filename[:-4] + '_short.txt')
                if not isfile(infilename):
                    print 'logfile "%s" not found' % (infilename)
                    continue
                fin = open(infilename,'r')
                lines = fin.readlines()
                erase_line = True
                found_systs = False
                found_start = False
                newlines = []
                if not is_param_card:
                    for line in lines:
                        if found_systs: erase_line = True # after the PDF line we don't need anything anymore
                        if '  === Results Summary for run' in line:
                            found_start = True
                            erase_line = False
                        if 'PDF variation' in line: found_systs = True
                        if not erase_line:
                            newlines.append(line)
                else:
                    for line in lines:
                        # start recording when finding the LQ decay
                        if 'DECAY  9000005' in line:
                            found_start = True
                            erase_line = False
                        # stop when reaching the next particle
                        if '#      PDG        Width' in line:
                            erase_line = True
                        if not erase_line:
                            newlines.append(line)

                fin.close()
                if (is_param_card and not found_start) or (not is_param_card and (not found_systs or not found_start)):
                    print yellow('  --> didn\'t find the summary or systematics in file %s, going to skip this file, won\'t create a shortfile, deleting the logfile.' % (infilename))
                elif self.submit:
                    fout = open(shortfilename,'w')
                    print green('  --> Replacing long with shortened file: %s' % (shortfilename))
                    for newline in newlines:
                        fout.write(newline)
                    fout.close()
                else:
                    print yellow('  --> Would replace long with shortened file %s' % (shortfilename))

                if self.submit:
                    os.remove(infilename)
            if self.submit: check_shortfiles(filepath=self.crosssecfolder+'/'+processname, tag=self.tag)




    def ReadoutCrossBR(self, ignore_br=True):
        for processname in self.processnames:

            # if 'LQLQ' in processname:
            #     filenamepattern_base = 'MLQ{}_MPS{}_MC1{}_L{}'
            #     variable_order = [x.replace('{}', '') for x in filenamepattern_base.split('_')]
            #
            # elif 'LQTChannel' in processname and not 'UFOFlex' in processname:
            #     filenamepattern_base = 'MLQ{}_L{}_B33R{}_B33L{}_B23L{}_B32L{}'
            #     variable_order = [x.replace('{}', '') for x in filenamepattern_base.split('_')]
            #
            # elif 'LQTChannel' in processname and 'UFOFlex' in processname:
            #     filenamepattern_base = 'MLQ{}_L{}_B12L{}_B33R{}_B11L{}_B23L{}_B22L{}_B13L{}_B21L{}_B33L{}_B31L{}_B32L{}'
            #     variable_order = [x.replace('{}', '') for x in filenamepattern_base.split('_')]
            #
            # elif 'PsiPsi' in processname:
            #     # filenamepattern_base = 'MLQ{}_MCH{}_MPS{}_L{}'
            #     # variable_order = [x.replace('{}', '') for x in filenamepattern_base.split('_')]
            #     variable_order = [self.individual_settings[0][key][1] for key in self.individual_settings[0].keys() if self.individual_settings[0][key][1] is not None]
            #     filenamepattern_base = '_'.join(['%s{}' % (x) for x in variable_order])
            #     # print variable_order
            #     # print filenamepattern_base
            # else:
            #     raise ValueError('processname does not contain \'LQLQ\' or \'LQTChannel\' or \'PsiPsi\', what kind of process are we looking at here?')
            variable_order = [self.individual_settings[0][key][1] for key in self.individual_settings[0].keys() if self.individual_settings[0][key][1] is not None]
            filenamepattern_base = '_'.join(['%s{}' % (x) for x in variable_order])

            filenames = get_filelist_crossbr(filepath=self.crosssecfolder+'/'+processname, short=True, tag=self.tag)
            if ignore_br:
                filenames = [x for x in filenames if not 'param_card' in x]
            colnames_settings  = self.individual_settings[0].keys() #common for BR and XSEC
            colnames_xsec = ['crosssection', 'scale_down', 'scale_up', 'pdf'] # specific column names
            colnames_br   = ['daughter_1', 'daughter_2', 'branchingratio', 'decaywidth'] # specific column names
            varlists_xsec  = []
            varlists_br    = []

            for filename in filenames:
                is_param_card = True if 'param_card' in filename else False
                if not is_param_card:

                    parse_pattern_cross = processname + '_' + filenamepattern_base
                    parse_pattern_cross += '%s_crosssection{}' % (self.tag)
                    infilename = join(self.crosssecfolder+'/'+processname, filename)
                    varlist = readout_crossection(infilename=infilename, filenamepattern=parse_pattern_cross, variable_order=variable_order, order_settings=variable_order, order_values=colnames_xsec)
                    varlists_xsec.append(varlist)

                else: # param card
                    if not processname == 'LQLQ': continue

                    parse_pattern_br = processname + '_' + filenamepattern_base
                    parse_pattern_br += '%s_param_card{}' % (self.tag)
                    infilename = join(self.crosssecfolder+'/'+processname, filename)

                    varlist = readout_branchingratio(infilename=infilename, filenamepattern=parse_pattern_br, variable_order=variable_order, order_settings=variable_order, order_values=colnames_br)
                    for l in varlist: # can return multiple lists, one for each decay mode
                        varlists_br.append(l)

            varlists_xsec.sort(key=lambda x: x[4])


            #finally write the files
            if self.submit:
                print green('--> Writing cross sections and branching fractions for process: %s...' % (processname))
                outfilename = self.crosssecfolder+'/Crosssections_%s%s.json' % (processname, self.tag)
                df = pd.DataFrame(varlists_xsec, columns=variable_order+colnames_xsec)
                df.to_json(outfilename, orient='records', lines=True, double_precision=15)

                if processname == 'LQLQ':
                    outfilename = self.crosssecfolder+'/Branchingratios_%s%s.json' % (processname, self.tag)
                    df_br = pd.DataFrame(varlists_br, columns=variable_order+colnames_br)
                    df_br.to_json(outfilename, orient='records', lines=True)
                print green('--> Done: Wrote cross sections and branching fractions for process: %s' % (processname))
            else:
                print yellow('--> Would write cross sections and branching fractions for process: %s' % (processname))



    def RootifyCrosssections(self, variables, graphs_per, forcepoints2d):
        for processname in self.processnames:
            print green('--> Now at sample %s' % (processname))

            # read dataframe from json
            outfilename = self.crosssecfolder+'/Crosssections_%s%s_vs_%s.root' % (processname, self.tag, '_'.join(variables))
            df = pd.read_json( self.crosssecfolder+'/Crosssections_%s%s.json' % (processname, self.tag), orient='records', lines=True )
            print df

            # create outfile
            if self.submit:
                outfile = TFile(outfilename, 'RECREATE')
            else:
                print yellow('--> Would have created outfile %s' % (outfilename))

            # get list of points that MUST be set
            if forcepoints2d is not None:
                set_points = {}
                for forceval_x in forcepoints2d:
                    set_points[forceval_x] = {}
                    for forceval_y in forcepoints2d[forceval_x]:
                        set_points[forceval_x][forceval_y] = False

            # inside the loop, we have one DF per combination of values of 'graphs_per', so inside the loop we make one graph as a function of 'variable'
            for value, grouped_df in df.groupby(graphs_per):
                grouped_df = grouped_df.sort_values(by=variables)
                grouped_df['tot_hi'] = grouped_df.apply( lambda x: XsecTotErrPandas(x,'crosssection', 'scale_up', 'pdf'), axis=1 )
                grouped_df['tot_lo'] = grouped_df.apply( lambda x: XsecTotErrPandas(x,'crosssection', 'scale_down', 'pdf'), axis=1 )
                grouped_df['x_hi']   = 0
                grouped_df['x_lo']   = 0

                # convert relevant columns to arrays (needed by TGraphs)
                vararray1    = grouped_df[variables[0]].to_numpy()
                if len(variables) > 1:
                    vararray2    = grouped_df[variables[1]].to_numpy()
                crosssection = grouped_df['crosssection'].to_numpy()
                tot_lo       = grouped_df['tot_lo'].to_numpy()
                tot_hi       = grouped_df['tot_hi'].to_numpy()
                x_lo         = grouped_df['x_lo'].to_numpy()
                x_hi         = grouped_df['x_hi'].to_numpy()

                # create graph and fill in points
                if len(variables) == 1:
                    graph = TGraphAsymmErrors(vararray1.size)
                    for idx in range(vararray1.size):
                        graph.SetPoint(idx, vararray1[idx], crosssection[idx])
                        graph.SetPointError(idx, 0, 0, tot_lo[idx], tot_hi[idx])
                else:
                    npoints2d = 0
                    graph = TGraph2D()
                    for idx in range(vararray1.size):
                        graph.SetPoint(npoints2d, vararray1[idx], vararray2[idx], crosssection[idx])
                        npoints2d += 1
                        if forcepoints2d is not None:
                            set_points[vararray1[idx]][vararray2[idx]] = True

                    # now fill all "open" points with 0
                    for forceval_x in set_points:
                        for forceval_y in set_points[forceval_x]:
                            if not set_points[forceval_x][forceval_y]:
                                graph.SetPoint(npoints2d, forceval_x, forceval_y, 0)
                                npoints2d += 1

                # set axis and graph names, flexibly for 1 and 2-d graphs
                xaxistitle = variables[0]
                graph.GetHistogram().GetXaxis().SetTitle(xaxistitle)
                if len(variables) > 1:
                    graph.GetHistogram().GetYaxis().SetTitle(variables[1])
                    graph.GetHistogram().GetZaxis().SetTitle('#sigma [pb]')
                else:
                    graph.GetYaxis().SetTitle('#sigma [pb]')
                graphname = processname
                if len(graphs_per) == 1:
                    graphname += '_%s%s' % (graphs_per[0], get_floatstring(value))
                else:
                    for idx in range(len(graphs_per)):
                        graphname += '_%s%s' % (graphs_per[idx], get_floatstring(value[idx]))

                # print graphname
                graph.SetName(graphname)
                graph.SetTitle('')

                # save
                if self.submit:
                    outfile.cd()
                    graph.Write()
                else:
                    print yellow('  --> Would have written graph %s to outfile' % (graphname))

            # close file
            if self.submit:
                outfile.Close()

    #TODO
    def RootifyBranchingratios():
        pass




    def PlotCrosssections(self, variables, overlay, overlay_values):

        # make plotting function part of the readout function, and give it option to only plot. Only then the correlations are properly kept without the need for parsing the graphnames and knowing the order. Other people/programs can still plot those cross sections "by hand", but here it needs to be systematic

        # # 'overlay': list of variables to be overlaid on the same plot. If None, make one plot per graph
        # # 'overlay_values': list of lists, one list per 'overlay' value. Give values for variables to be overlaid (in case there are super many), ignoring the others. If None, take all that are in the file
        #
        # make a few sanity checks
        if overlay is not None:
            if not len(overlay) == len(overlay_values):
                raise AttributeError('Different length of variable names and values to overlay. The latter must be one list per element of the former')

        # dictionary to transform axisnames into nicely formatted strings
        varname_to_axistitle = {
            'MPS': 'M_{#psi} [GeV]',
            'MLQ': 'M_{LQ} [GeV]',
            'MCH': 'M_{#chi_{1}} [GeV]',
        }


        ensureDirectory(self.crosssecfolder+'/plots')
        for processname in self.processnames:
            print green('--> Now at sample %s' % (processname))
            gROOT.SetBatch(1)

            # open rootfile
            infilename = self.crosssecfolder+'/Crosssections_%s%s_vs_%s.root' % (processname, self.tag, '_'.join(variables))
            if self.submit:
                infile = TFile(infilename, 'READ')
            else:
                print yellow('--> Would have opened inputfile %s' % (outfilename))

            # sanity check
            if len(variables) > 1 and overlay is not None:
                raise AttributeError('Requesting higher dimension than 1, in this case nothing can be overlaid. Please only use this option with \'overlay=None\'.')
            if len(variables) > 2:
                raise AttributeError('Requesting higher dimension than 2, this is not possible.')


            # parse graphnames to get list of all combinations of variables that exist in the file. The pattern of the graphname is known.
            graphnames_overlay = []
            graphnames_all = []
            for key in ROOT.gDirectory.GetListOfKeys():
                if ROOT.gROOT.GetClass(key.GetClassName()).InheritsFrom("TGraph"):
                    graphnames_overlay.append(key.GetName().replace(processname + '_', ''))
                    graphnames_all.append(key.GetName())
                if len(variables) > 1:
                    if ROOT.gROOT.GetClass(key.GetClassName()).InheritsFrom("TGraph2D"):
                        graphnames_all.append(key.GetName())



            # remove processname, then split at '_'
            graphnames_split = [g.split('_') for g in graphnames_overlay]

            graphs_per_plot = {}


            # nicely arrange all values per variable in 'overlay' that exist in the file
            if overlay is not None:
                var_values_infile = {}
                for var in overlay:
                    values = []
                    for graphparts in graphnames_split:
                        for part in graphparts:
                            if not part.startswith(var): continue
                            val = part.replace(var, '')
                            if not val in values:
                                values.append(val)
                    var_values_infile[var] = values

                # remove those values that are not in 'overlay_values', then we have a dictionary of all settings we want to overlay on each plot.
                var_values_to_plot = {}
                for idx in range(len(overlay)):
                    varname = overlay[idx]
                    if not varname in var_values_infile:
                        raise AttributeError('Requesting the overlay of variable %s, which does not exist in the file at all.' % (varname))
                    if overlay_values[idx] is not None:
                        varlist = overlay_values[idx]
                        for var in varlist:
                            if not var in var_values_infile[varname]:
                                raise AttributeError('Requesting value %s of variable %s, which does not exist in the file.' % (var, varname))
                        common_elements = list(set(varlist).intersection(var_values_infile[varname]))
                    else:
                        common_elements = var_values_infile[varname]
                    var_values_to_plot[varname] = common_elements


                # get "sum" of values to put in each plot, and construct the tags to search for in graphname
                tags_per_plot = []
                for varname in var_values_to_plot:
                    for val in var_values_to_plot[varname]:
                        tags_per_plot.append(varname+val)

                # from all graphnames, remove all the tags that are in the 'tags_per_plot'. afterwards, all graphs with the same "remaining name" (gn_cleaned) belong on the same plot.
                graphnames_and_cleaned_and_tags = []
                for gn in graphnames_all:
                    gn_cleaned = gn
                    tags = ''
                    for tag in tags_per_plot:
                        if tag in gn_cleaned:
                            gn_cleaned = gn_cleaned.replace('_%s' % (tag), '')
                            tags += '_%s' % (tag)
                    for varname in overlay:

                        tags = tags.replace('_%s' % (varname), ', %s: ' % (varname))
                    tags = tags.strip(', ')
                    graphnames_and_cleaned_and_tags.append((gn_cleaned, gn, tags))

                # group graphnames into lists if they have the same cleaned graphname
                for (gn_cleaned, gn, tag) in graphnames_and_cleaned_and_tags:
                    if not gn_cleaned in graphs_per_plot:
                        graphs_per_plot[gn_cleaned] = [(gn, tag)]
                    else:
                        graphs_per_plot[gn_cleaned].append((gn, tag))

            else: #no overlay, make one plot per graph
                for gn in graphnames_all:
                    graphs_per_plot[gn] = [(gn, processname)]


            # now, each key in the dictionary corresponds to one plot to be made. Make them!
            for plotname in graphs_per_plot:
                thisplotname = self.crosssecfolder+'/plots/Crosssections_%s_vs_%s%s.pdf'%(plotname, '_'.join(variables), self.tag)

                xsectitle_formatted = '#sigma [pb]'
                if 'LQLQ' in plotname:
                    xsectitle_formatted = '#sigma (pp #rightarrow LQ LQ) [pb]'
                if 'PsiPsi' in plotname:
                    xsectitle_formatted = '#sigma (pp #rightarrow #psi #psi) [pb]'
                if 'LQTChannelTauNu' in plotname:
                    xsectitle_formatted = '#sigma_{LQ} (pp #rightarrow #tau #nu) [pb]'
                if 'LQTChannelTauTau' in plotname:
                    xsectitle_formatted = '#sigma_{LQ} (pp #rightarrow #tau #tau) [pb]'
                print varname_to_axistitle[variables[0]]

                if len(variables) == 1:
                    plot_xsec_1d(infile=infile, graphnames_and_legends_for_canvas=graphs_per_plot[plotname], axistitles=[varname_to_axistitle[variables[0]], xsectitle_formatted], plotname=thisplotname)
                elif len(variables) == 2:
                    plot_xsec_2d(infile=infile, graphnames_and_legends_for_canvas=graphs_per_plot[plotname], axistitles=[varname_to_axistitle[variables[0]], varname_to_axistitle[variables[1]], xsectitle_formatted], plotname=thisplotname)







# small useful functions only defined in this file, not used elsewhere

def readout_crossection(infilename, filenamepattern, variable_order, order_settings, order_values):
    # parse parameters from filename
    parser_cross = parse.compile(filenamepattern)

    vartuple_string = parser_cross.parse(infilename.split('/')[-1])
    # print vartuple_string
    varlist_string = [itup for itup in vartuple_string if not itup.endswith('.txt')]
    # print varlist_string
    vardict = {}
    for i in range(len(variable_order)):
        if not varlist_string[i] == 'best':
            vardict[variable_order[i]] = floatstring_to_float(varlist_string[i])
        else:
            vardict[variable_order[i]] = varlist_string[i]

    # extract relevant parameters for dataframe from dict
    # print order_settings
    # print vardict
    # print order_settings
    varlist = [vardict[param] for param in order_settings]

    # find correct lines to parse and set up the patterns
    pattern_crosssection = '{}:   {} +- {} pb\n'
    pattern_scale        = '{}: +{}% -{}%\n'
    pattern_pdf          = '{}: +{}% -{}%\n'
    fin = open(infilename, 'r')
    lines = fin.readlines()
    line_crosssection = ''
    line_scale        = 'TEST'
    line_pdf          = ''

    for line in lines:
        if 'Cross-section :' in line: line_crosssection = line
        elif 'scale variation:' in line: line_scale = line
        elif 'PDF variation:' in line: line_pdf = line

    # do the parsing
    parser_xsec  = parse.compile(pattern_crosssection)
    parser_scale = parse.compile(pattern_scale)
    parser_pdf   = parse.compile(pattern_pdf)

    pre, xsec, xsec_unc = parser_xsec.parse(line_crosssection)
    pre, scale_up, scale_down = parser_scale.parse(line_scale)
    pre, pdf_up, pdf_down = parser_pdf.parse(line_pdf)

    # will crash if some unexpected value is requested, which is good.
    dict = {'crosssection': float(xsec), 'scale_down': float(scale_down), 'scale_up': float(scale_up), 'pdf': float(str(max(float(pdf_up), float(pdf_down))))}
    for key in order_values:
        varlist += [dict[key]]

    # print varlist
    return varlist


def readout_branchingratio(infilename, filenamepattern, variable_order, order_settings, order_values):
    parser_br = parse.compile(filenamepattern)

    vartuple_string = parser_br.parse(infilename.split('/')[-1])
    varlist_string = [itup for itup in vartuple_string if not itup.endswith('.txt')]
    vardict = {}
    for i in range(len(variable_order)):
        if not varlist_string[i] == 'best':
            vardict[variable_order[i]] = floatstring_to_float(varlist_string[i])
        else:
            vardict[variable_order[i]] = varlist_string[i]


    varlist = [vardict[param] for param in order_settings]
    # varlist_base = []
    # for param in self.individual_settings[0].keys():
    #     key = self.individual_settings[0][param][1]
    #     varlist_base.append(vardict[key])

    fin = open(infilename, 'r')
    lines = fin.readlines()
    result_lists = []
    for line in lines:
        if line[0:5] == 'DECAY' or line[0] == '#': continue
        # remaining lines contain BRs
        content = line.split()
        br, decaywidth, dau1, dau2 = float(content[0]), float(content[5]), int(content[2]), int(content[3])

        # will crash if some unexpected value is requested, which is good.
        dict = {'daughter_1': dau1, 'daughter_2': dau2, 'branchingratio': br, 'decaywidth': decaywidth}
        for key in order_values:
            varlist += [dict[key]]
        result_lists.append(varlist)
    return result_lists


def plot_xsec_1d(infile, graphnames_and_legends_for_canvas, axistitles, plotname, colors=[kRed+4, kRed+1, kAzure-2, kOrange, kGreen-2]):

    graphs_and_legnames = []
    xmax = ymax = 0
    xmin = ymin = 1E-10
    for gn, legname in graphnames_and_legends_for_canvas:
        g = infile.Get(gn)
        graphs_and_legnames.append((g, legname))
        xmax = max(g.GetXaxis().GetXmax(), xmax)
        ymax = max(g.GetHistogram().GetMaximum()*10, ymax)
        xmin = min(g.GetXaxis().GetXmin(), xmin)
        ymin = max(min(g.GetHistogram().GetMinimum(), ymin), 1E-10)

    # c = tdrCanvas('c', xmin, xmax, ymin, ymax, graphs_and_legnames[0][0].GetXaxis().GetTitle(), axistitles[1], square=True, iPeriod=0, iPos=11)
    c = tdrCanvas('c', xmin, xmax, ymin, ymax, axistitles[0], axistitles[1], square=True, iPos=11)
    c.SetLogy()
    legy_high = 0.9
    entryheight = 0.07
    legy_low = 0.9-entryheight*len(graphs_and_legnames)
    leg = tdrLeg(0.35,legy_low,0.9,legy_high, textSize=0.037)

    idx = 0
    for idx, (g, legname) in enumerate(graphs_and_legnames):
        try:
            tdrDraw(g, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.4)
            g.GetXaxis().SetLabelSize(14)
            legtext = legname.replace('_', ', ')
            leg.AddEntry(g, legtext, 'lf')
        except ReferenceError:
            print 'skip this one'
            continue

    leg.Draw('SAME')
    c.SaveAs(plotname)

def plot_xsec_2d(infile, graphnames_and_legends_for_canvas, axistitles, plotname, colors=[kRed+4, kRed+1, kAzure-2, kOrange, kGreen-2]):
    if not len(graphnames_and_legends_for_canvas) == 1:
        raise AttributeError('Not exactly one 2-d plot given to overlay on the same canvas, this is not possible.')
    if not len(axistitles) == 3:
        raise AttributeError('Must pass exactly 3 axistitles to plot_xsec_2d().')

    gn, legname = graphnames_and_legends_for_canvas[0]
    xmin = ymin = zmin = 1E-19
    zmax = 1E3

    g = infile.Get(gn)
    xmax = g.GetXaxis().GetXmax()
    ymax = g.GetYaxis().GetXmax()
    xmin = g.GetXaxis().GetXmin()
    ymin = max(g.GetYaxis().GetXmin(), ymin)

    c = tdrCanvas2d('c', square=False)
    c.SetLogy()
    c.SetLogz()
    tdrDraw2d(g, 'COLZ', 500, xmin, xmax, 500, ymin, ymax, 150, zmin, zmax, axistitles)



    c.SaveAs(plotname)
