#! /usr/bin/env python

import os, sys, math
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
from utils import *
from functions import *

import ROOT
from ROOT import gROOT, gStyle, gPad, TLegend, TFile, TCanvas, Double, TF1, TH2D, TGraph, TGraph2D, TGraphAsymmErrors, TLine,\
                 kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet,\
                 kSolid, kDashed, kDotted
from math import sqrt, log, floor, ceil
from array import array

from preferred_configurations import *
from tdrstyle_all import *
import tdrstyle_all as TDR

class CrossSectionRunner:
    def __init__(self, processnames, tag, lambdas, cardfolder, crosssecfolder, gensimfolder, mgfolder_local, workarea, cmssw_tag_sim, workdir_slurm, submit=False):
        self.processnames = processnames
        self.tag = tag
        self.lambdas = lambdas
        self.cardfolder = cardfolder
        self.crosssecfolder = crosssecfolder
        self.gensimfolder = gensimfolder
        self.mgfolder_local = mgfolder_local
        self.workarea = workarea
        self.cmssw_tag_sim = cmssw_tag_sim
        self.workdir_slurm = workdir_slurm
        self.submit = submit


    def ProduceCards(self):
        for processname in self.processnames:
            configs = get_config_list(preferred_configurations=preferred_configurations, processname=processname)
            idx = 0
            for config in configs:
                mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=preferred_configurations, config=config)
                for lamb in self.lambdas:
                    if self.submit:
                        make_card(card_template_folder=self.cardfolder+'/CrossBR', card_output_folder=self.cardfolder+'/CrossBR/%s' % (processname), processname=processname, tag=self.tag, mlq=mlq, mps=mps, mch=mch, lamb=lamb, verbose=False)
                        idx += 1
                        if idx % 20 is 0:
                            print green('--> Produced %i out of %i cards for process %s (%.2f%%).' % (idx, len(configs)*len(self.lambdas), processname, float(idx)/float(len(configs)*len(self.lambdas))*100))

            if not self.submit:
                print yellow('Would have produced %i cards for process %s.' % (len(configs)*len(self.lambdas), processname))

    def RunMG(self, only_resubmit=False, ncores=2, runtime=(00,40), maxjobs_per_proc=50):
        runtime_str = '%02i:%02i:00' % runtime
        queue = 'wn' if runtime[0] > 1 else 'quick'      # quick -- wn

        for processname in self.processnames:
            if only_resubmit:
                shortfilelist = get_filelist_crossbr(filepath=self.crosssecfolder+'/'+processname, short=True, tag=self.tag)
            njobs = 0
            commandfilename = self.gensimfolder + '/commands/CrossBR_%s.txt' % (processname)
            f = open(commandfilename, 'w')
            configs = get_config_list(preferred_configurations=preferred_configurations, processname=processname)
            for config in configs:
                for lamb in self.lambdas:
                    # if njobs > 1: break
                    mlq, mps, mch = get_mlq_mps_mch(preferred_configurations=preferred_configurations, config=config)
                    jobname       = get_jobname(processname=processname, mlq=mlq, mps=mps, mch=mch, lamb=lamb, tag=self.tag)
                    write_command = True
                    if only_resubmit:
                        write_command = False
                        if len(shortfilelist) == 0:
                            write_command = True
                        else:
                            param_card_shortname   = jobname+'_param_card_short.txt'
                            crosssection_shortname = jobname+'_crosssection_short.txt'
                            if (not (param_card_shortname in shortfilelist) or not (crosssection_shortname in shortfilelist)):
                                write_command = True
                    # write to a command file the shell command: 'source run_crossbr.sh  .....' %
                    command = 'source %s %s %s %s %s %s %s %s %i' % (self.gensimfolder+'/run_crossbr.sh', self.mgfolder_local, jobname, self.cardfolder+'/CrossBR/%s' % (processname), self.workarea + '/' + self.cmssw_tag_sim, self.workdir_slurm, self.crosssecfolder, processname, ncores)
                    if write_command:
                        f.write(command + '\n')
                        njobs += 1
            f.close()
            slurmjobname = 'CrossBR_%s' % (processname)
            slurm_max_array_size = 4000
            submit_more_arrays = True if (njobs > slurm_max_array_size) else False
            # if submit_more_arrays:
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
                command = 'sbatch --parsable -a 1-%i%%%i -J %s -p %s -t %s --cpus-per-task %i submit_crossbr_array.sh %s %i' % (arrayend, maxjobs_per_proc, slurmjobname, queue, runtime_str, ncores, commandfilename, idx_offset)
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

    def ReadoutCrossBR(self):
        for processname in self.processnames:
            total_writelines_cross = []
            total_writelines_br = []

            total_writelines_cross.append('# ATTENTION: All cross sections in this file have the default BW cutoff of M +- 15 * Gamma.\n')
            total_writelines_cross.append('crosssection = {\n')
            total_writelines_br.append('branchingratio = {\n')
            if 'LQLQ' in processname:
                total_writelines_cross.append('  # lambda --> mass(chi) -->  (mass(LQ),    sigma,       Q_low,   Q_up,    PDF)\n')
                total_writelines_br.append('  # mass(LQ) --> mass(chi) --> (dau1, dau2) --> (br, partial width)\n')
            elif 'PsiPsi' in processname:
                total_writelines_cross.append('  # lambda --> mass(LQ)  -->  (mass(chi),   sigma,       Q_low,   Q_up,    PDF)\n')
                # total_writelines_br.append('  # mass(chi) --> mass(LQ) --> (dau1, dau2) --> (br, partial width)\n')
            else:
                raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')

            filenames = get_filelist_crossbr(filepath=self.crosssecfolder+'/'+processname, short=True, tag=self.tag)
            tuplelist = []
            tupledicts_per_lambda = {}
            target_tuplelist_dict = {}
            brs_per_mref = {}
            # for lamb in self.lambdas:
            #     print lamb
            #     tupledicts_per_lambda[lamb] = {}
            #     brs_per_mref[lamb] = {}
            # print '%i files found' % (len(filenames))
            for filename in filenames:
                is_param_card = True if 'param_card' in filename else False
                parse_pattern_cross = processname + '_MLQ{}_MPS{}_MC1{}_L{}'
                parse_pattern_cross += '%s_crosssection{}' % (self.tag)
                parse_pattern_br = processname + '_MLQ{}_MPS{}_MC1{}_L{}'
                parse_pattern_br += '%s_param_card{}' % (self.tag)
                if not is_param_card:
                    parser_cross = parse.compile(parse_pattern_cross)
                    # print filename
                    mlq, mps, mch, lambstr, dummy = parser_cross.parse(filename)
                    mlq, mps, mch, lamb = float(mlq), float(mps), float(mch), lambstr_to_float(lambstr)
                    # print lambstr, lamb
                    # if not lamb in self.lambdas: continue
                    # lamb_key = lamb
                    # if is_best_lambda(lamb, mlq):
                    #     lamb_key = 'best'

                    # find correct lines to parse and set up the patterns
                    pattern_crosssection = '{}:   {} +- {} pb\n'
                    pattern_scale        = '{}: +{}% -{}%\n'
                    pattern_pdf          = '{}: +{}% -{}%\n'
                    fin = open(join(self.crosssecfolder+'/'+processname, filename), 'r')
                    lines = fin.readlines()
                    line_crosssection = ''
                    line_scale        = 'TEST'
                    line_pdf          = ''
                    lineidx = 0
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

                    # put everything into the right tuples and sort
                    mref = mch if 'LQLQ' in processname else mlq
                    mdep = mlq if 'LQLQ' in processname else mch
                    # print lamb
                    if not lamb in tupledicts_per_lambda.keys():
                        tupledicts_per_lambda[lamb] = {}
                    if not mref in tupledicts_per_lambda[lamb]: tupledicts_per_lambda[lamb][mref] = []
                    tupledicts_per_lambda[lamb][mref].append((mdep, xsec, scale_down, scale_up, str(max(float(pdf_up), float(pdf_down)))))

                else: # param card
                    if not processname == 'LQLQ': continue
                    parser_br = parse.compile(parse_pattern_br)
                    # print filename
                    mlq, mps, mch, lambstr, dummy = parser_br.parse(filename)
                    mlq, mps, mch, lamb = float(mlq), float(mps), float(mch), lambstr_to_float(lambstr)
                    # if not lamb in self.lambdas: continue
                    mref = mlq if 'LQLQ' in processname else mch
                    mdep = mch if 'LQLQ' in processname else mlq

                    fin = open(join(self.crosssecfolder+'/'+processname, filename), 'r')
                    lines = fin.readlines()
                    branchingratios = {}
                    for line in lines:
                        if line[0:5] == 'DECAY' or line[0] == '#': continue
                        # remaining lines contain BRs
                        content = line.split()
                        br, decaywidth, dau1, dau2 = float(content[0]), float(content[5]), int(content[2]), int(content[3])
                        dautup = (dau1, dau2)
                        brtup  = ((br, decaywidth))
                        branchingratios[dautup] = brtup
                    if not lamb in brs_per_mref.keys():
                        brs_per_mref[lamb] = {}
                    if not mref in brs_per_mref[lamb].keys():
                        brs_per_mref[lamb][mref] = {}
                    if not mdep in brs_per_mref[lamb][mref].keys():
                        brs_per_mref[lamb][mref][mdep] = {}
                    if not brs_per_mref[lamb][mref][mdep] == {}:
                        # print mref, mdep
                        # print brs_per_mref[mref]
                        # print branchingratios
                        raise ValueError('M_dep %f is already a key in the dictionary, how did this happen?' % mdep)
                    brs_per_mref[lamb][mref][mdep] = branchingratios

            for lamb in tupledicts_per_lambda:
                for mrefkey in tupledicts_per_lambda[lamb]:
                    tupledicts_per_lambda[lamb][mrefkey].sort(key=itemgetter(0))
            for lamb in sorted(tupledicts_per_lambda):
                total_writelines_cross.append('%s: {\n' % (get_lambdastring_withpoint(lamb)))
                for mref in sorted(tupledicts_per_lambda[lamb]):
                    total_writelines_cross.append('    %i: [\n' % (mref))
                    for tup in tupledicts_per_lambda[lamb][mref]:
                        total_writelines_cross.append('            ( %s, %s, %s, %s, %s),\n' % (str(int(tup[0])).rjust(4, ' '), str(tup[1]).ljust(9, ' '), str(tup[2]).ljust(4, ' '), str(tup[3]).ljust(4, ' '), tup[4].ljust(4, ' ')))
                    total_writelines_cross[-1] = total_writelines_cross[-1].replace('),', ')')
                    total_writelines_cross.append('        ], # closing for this mref\n')
                total_writelines_cross = total_writelines_cross[:-1]
                total_writelines_cross.append('        ] # closing for this mref\n')
                total_writelines_cross.append('    }, # Closing for this lambda\n')
            total_writelines_cross = total_writelines_cross[:-1]
            total_writelines_cross.append('    } # Closing for this lambda\n')
            total_writelines_cross.append('} # Closing for entire dictionary\n')

            # now make writelines for branching ratios
            if processname == 'LQLQ':
                for lamb in sorted(brs_per_mref):
                    total_writelines_br.append('  %s: {\n' % (get_lambdastring_withpoint(lamb)))
                    for mref in sorted(brs_per_mref[lamb]):
                        total_writelines_br.append('    %i: {\n' % (mref))
                        for mdep in sorted(brs_per_mref[lamb][mref]):
                            total_writelines_br.append('      %i: {\n' % (mdep))
                            for daus in sorted(brs_per_mref[lamb][mref][mdep]):
                                total_writelines_br.append('        (%i, %i): (%2.3f, %f),\n' % (daus[0], daus[1], brs_per_mref[lamb][mref][mdep][daus][0], brs_per_mref[lamb][mref][mdep][daus][1]))
                            total_writelines_br[-1] = total_writelines_br[-1].replace('),', ')')
                            total_writelines_br.append('      }, # closing for this mdep\n')
                        total_writelines_br = total_writelines_br[:-1]
                        total_writelines_br.append('      } # closing for this mdep\n')
                        total_writelines_br.append('    }, # Closing for this mref\n')
                    total_writelines_br = total_writelines_br[:-1]
                    total_writelines_br.append('    } # Closing for this mref\n')
                    total_writelines_br.append('  }, # Closing for this lambda\n')
                total_writelines_br = total_writelines_br[:-1]
                total_writelines_br.append('  } # Closing for this lambda\n')
                total_writelines_br.append('} # Closing for entire dictionary\n')



            #finally write the files
            if self.submit:
                print green('--> Writing cross sections and branching fractions for process: %s' % (processname))
                outfilename = self.crosssecfolder+'/Crosssections_%s%s.py' % (processname, self.tag)
                with open(outfilename, 'w') as fout:
                    for wl in total_writelines_cross:
                        fout.write(wl)
                if processname == 'LQLQ':
                    outfilename = self.crosssecfolder+'/Branchingratios_%s%s.py' % (processname, self.tag)
                    with open(outfilename, 'w') as fout:
                        for wl in total_writelines_br:
                            fout.write(wl)
            else:
                print yellow('--> Would write cross sections and branching fractions for process: %s' % (processname))


    def RootifyCrossBR(self):
        for processname in self.processnames:
            outfilename_cross = self.crosssecfolder+'/Crosssections_%s%s.root' % (processname, self.tag)
            cross_module = importlib.import_module('crosssections.ChiPsi.Crosssections_%s' % (processname))
            crosssections = cross_module.crosssection
            if self.submit:
                outfile = TFile(outfilename_cross, 'RECREATE')
            else:
                print yellow('--> Would have created outfile %s' % (outfilename_cross))
            print green('--> Now at sample %s' % (processname))
            for lamb in self.lambdas:
                if not lamb in crosssections: continue
                print green('  --> Now at lambda: %s' % (get_lambdastring(lamb)))

                xsecs_per_mref = crosssections[lamb]
                graph2d = TGraph2D()
                npoints2d=0
                set_points ={}
                all_combinations = get_all_combinations(preferred_configurations=preferred_configurations)
                for mlq in all_combinations:
                    set_points[mlq] = {}
                    for mch in all_combinations[mlq]:
                        set_points[mlq][mch] = False
                for mref in xsecs_per_mref:
                    xsecs = xsecs_per_mref[mref]
                    final_xsecs = []
                    mdeps  = array('d')
                    sigmas  = array('d')
                    tot_los = array('d')
                    tot_his = array('d')
                    mdeps_lo = array('d')
                    mdeps_hi = array('d')

                    for tuple in xsecs:
                        mdep, sigma, q_lo, q_hi, pdf = tuple
                        tot_lo = XsecTotErr(sigma, q_lo, pdf)
                        tot_hi = XsecTotErr(sigma, q_hi, pdf)
                        final_xsecs.append((mdep, sigma, tot_lo, tot_hi))
                        mdeps.append(mdep)
                        sigmas.append(sigma)
                        tot_los.append(tot_lo)
                        tot_his.append(tot_hi)
                        mdeps_lo.append(0.)
                        mdeps_hi.append(0.)
                        if 'LQLQ' in processname:
                            graph2d.SetPoint(npoints2d, mdep, mref, sigma)
                            set_points[mdep][mref] = True
                        elif 'PsiPsi' in processname:
                            graph2d.SetPoint(npoints2d, mref, mdep, sigma)
                            set_points[mref][mdep] = True
                        else:
                            raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')
                        npoints2d += 1

                    # make TGraph out of it
                    graph = TGraphAsymmErrors(len(mdeps), mdeps, sigmas, mdeps_lo, mdeps_hi, tot_los, tot_his)
                    xaxistitle = 'M_{LQ} [GeV]' if 'LQLQ' in processname else 'M_{#chi_{1}} [GeV]'
                    graph.GetXaxis().SetTitle('M_{LQ} [GeV]')
                    graph.GetYaxis().SetTitle('#sigma [pb]')
                    graphname = processname
                    if 'LQLQ' in processname:
                        graphname += '_MC1%i' % (mref)
                    elif 'PsiPsi' in processname:
                        graphname += '_MLQ%i' % (mref)
                    else:
                        raise ValueError('processname does not contain \'LQLQ\' or \'PsiPsi\', what kind of process are we looking at here?')

                    graphname += '_L%s' % (get_lambdastring(lamb))
                    graph.SetName(graphname)
                    # print 'graphname: %s' % (graphname)
                    graphtitle = processname
                    if 'LQLQ' in processname:
                        graphtitle += ', M_{#chi_{1}} = %i GeV' % (mref)
                    elif 'PsiPsi' in processname:
                        graphtitle += ', M_{LQ} = %i GeV' % (mref)
                    graphtitle += ', #lambda = %s' % (get_lambdastring(lamb).replace('p', '.'))
                    # print 'graphtitle: %s' % (graphtitle)
                    graph.SetTitle(graphtitle)
                    if self.submit:
                        outfile.cd()
                        graph.Write()
                    else:
                        print yellow('  --> Would have written graph %s to outfile' % (graphname))

                # fill remaining points in 2d graph with zeros
                for mlq in set_points:
                    for mch in set_points[mlq]:
                        if not set_points[mlq][mch]:
                            graph2d.SetPoint(npoints2d, mlq, mch, 0.)
                            npoints2d += 1
                graph2d.SetName(processname + '_L%s' % (get_lambdastring(lamb)))
                graph2d.GetXaxis().SetTitle('M_{LQ} [GeV]')
                graph2d.GetYaxis().SetTitle('M_{#chi_{1}} = %i [GeV]')
                graph2d.GetZaxis().SetTitle('#sigma [pb]')
                graph2d.SetTitle(processname + ', #lambda = %s' % (get_lambdastring(lamb).replace('p', '.')))
                if self.submit:
                    graph2d.Write()
                else:
                    print yellow('  --> Would have written 2d-graph to outfile')
            if self.submit:
                outfile.Close()

            # also rootify BRs if we are looking at the LQLQ process without decays (just for fun, could also be any other LQLQ process)
            if processname == 'LQLQ':
                outfilename_br = self.crosssecfolder+'/Branchingratios_%s%s.root' % (processname, self.tag)
                if self.submit:
                    outfile = TFile(outfilename_br, 'RECREATE')
                else:
                    print yellow('--> Would have created outfile %s' % (outfilename_br))
                br_module = importlib.import_module('crosssections.ChiPsi.Branchingratios_%s' % (processname))
                allbrs = br_module.branchingratio
                for lamb in allbrs.keys():
                    brs = allbrs[lamb]
                    brs2d = {}
                    npoints2d = {}
                    set_points ={}
                    for mlq in all_combinations:
                        set_points[mlq] = {}
                        for mch in all_combinations[mlq]:
                            set_points[mlq][mch] = {}
                            for decaymode in decaymode_dict.keys():
                                set_points[mlq][mch][decaymode] = False

                    decaymodes_present = []
                    for mlq in sorted(brs):
                        mchs_per_decaymode = {}
                        brs_per_decaymode = {}
                        for mch in sorted(brs[mlq]):
                            for decaymode in brs[mlq][mch]:
                                if not decaymode in decaymodes_present:
                                    decaymodes_present.append(decaymode)
                                if not decaymode in mchs_per_decaymode.keys(): mchs_per_decaymode[decaymode] = array('d')
                                if not decaymode in brs_per_decaymode.keys():  brs_per_decaymode[decaymode] = array('d')
                                # if not decaymode in set_points[mlq][mch].keys():
                                #     # print mlq, mch, decaymode
                                #     set_points[mlq][mch][decaymode] = False
                                if not decaymode in brs2d.keys():
                                    graphname2d = processname + ('_L%s_%i_%i' % (get_lambdastring(lamb), abs(decaymode[0]), abs(decaymode[1])))
                                    # print graphname2d
                                    npoints2d[decaymode] = 0
                                    brs2d[decaymode] = TGraph2D()
                                    brs2d[decaymode].SetName(graphname2d)
                                    brs2d[decaymode].GetXaxis().SetTitle('M_{LQ} [GeV]')
                                    brs2d[decaymode].GetYaxis().SetTitle('M_{#chi_{1}} = %i [GeV]')
                                    brs2d[decaymode].GetZaxis().SetTitle('BR (LQLQ#rightarrow%s)' % (decaymode_dict[decaymode]))
                                    brs2d[decaymode].SetTitle(processname + ', %s' % (decaymode_dict[decaymode]))

                                mchs_per_decaymode[decaymode].append(mch)
                                brs_per_decaymode[decaymode].append(brs[mlq][mch][decaymode][0])
                                brs2d[decaymode].SetPoint(npoints2d[decaymode], mlq, mch, brs[mlq][mch][decaymode][0])
                                set_points[mlq][mch][decaymode] = True
                                npoints2d[decaymode] += 1

                        for decaymode in mchs_per_decaymode.keys():
                            graph = TGraph(len(mchs_per_decaymode[decaymode]), mchs_per_decaymode[decaymode], brs_per_decaymode[decaymode])
                            graphname = processname + ('_MLQ%i_L%s_%i_%i' % (mlq, get_lambdastring(lamb), abs(decaymode[0]), abs(decaymode[1])))
                            graph.SetName(graphname)
                            graph.GetXaxis().SetTitle('M_{#chi_{1}} [GeV]')
                            graph.GetYaxis().SetTitle('BR (LQLQ#rightarrow%s)' % (decaymode_dict[decaymode]))
                            graph.SetTitle(processname + ', %s' % (decaymode_dict[decaymode]))
                            if self.submit:
                                graph.Write()
                            else:
                                print yellow('  --> Would have written graph %s to outfile' % (graphname))

                    # fill remaining points in 2d graph with zeros
                    for mlq in set_points:
                        for mch in set_points[mlq]:
                            for decaymode in set_points[mlq][mch]:
                                if not set_points[mlq][mch][decaymode] and decaymode in decaymodes_present:
                                    # print decaymode
                                    # print brs2d.keys()
                                    # print npoints2d.keys()
                                    # print 'Setting BR for MLQ=%i, MCH=%i, decay=(%i, %i) to 0' % (mlq, mch, decaymode[0], decaymode[1])
                                    brs2d[decaymode].SetPoint(npoints2d[decaymode], mlq, mch, 0)
                                    npoints2d[decaymode] += 1
                    if self.submit:
                        for decaymode in brs2d:
                            brs2d[decaymode].Write()
                    else:
                        print yellow('  --> Would have written 2d-graphs to outfile')
                outfile.Close()



    def PlotCrossBR(self):
        ensureDirectory(self.crosssecfolder+'/plots')
        for processname in self.processnames:

            gROOT.SetBatch(1)
            print green('--> Plotting cross section and BR plots for process %s' % processname)

            # for a reasonably spaced set of particle masses, find the closest correspondence in the preferred_configurations:
            if 'PsiPsi' in processname:
                mrefs_initial = [1000, 2000, 3000, 4500, 6000]
                xaxis_min = 100
                xaxis_max = 5000
                xaxis_title = 'M_{#chi_{1}} [GeV]'

            else:
                mrefs_initial = [100, 300, 1000, 3000, 10000]
                xaxis_min = 1000
                xaxis_max = 10000
                xaxis_title = 'M_{LQ} [GeV]'

            mrefs = []
            for mref in mrefs_initial:
                if 'PsiPsi' in processname:
                    mrefs.append(find_closest(sorted(preferred_configurations), mref))
                else:
                    mrefs.append(find_closest(sorted(preferred_configurations[preferred_configurations.keys()[0]]), mref))

            # open rootfile and get corresponding graphs
            if 'LQLQ' in processname:
                rootfilename_brs = self.crosssecfolder+'/Branchingratios_LQLQ%s.root' % (self.tag)
            else:
                rootfilename_brs = ''
            rootfilename = self.crosssecfolder+'/Crosssections_%s%s.root' % (processname, self.tag)
            infile = TFile(rootfilename, 'READ');
            for lamb in self.lambdas:
                ymin = 2E-15 #if 'LQLQ' in processname else 2E-15
                ymax = 1 if 'LQLQ' in processname else 1E5
                c = tdrCanvas('c', xaxis_min, xaxis_max, ymin, ymax, xaxis_title, '#sigma (pp #rightarrow %s) [pb]' % (procname_to_latex[processname]), square=True, iPeriod=0, iPos=11)
                c.SetLogy()
                leg = tdrLeg(0.55,0.55,0.9,0.9)
                idx = 0
                for mref in mrefs:
                    graphname = processname
                    if 'PsiPsi' in processname:
                        graphname += '_MLQ'
                    else:
                        graphname += '_MC1'
                    graphname += '%i_L%s' % (mref, get_lambdastring(lamb))
                    graph = infile.Get(graphname)
                    try:
                        tdrDraw(graph, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.4)
                        graph.GetXaxis().SetLabelSize(14)

                        if 'PsiPsi' in processname:
                            legtext = 'M_{LQ} = %i GeV' % (mref)
                        else:
                            legtext = 'M_{#chi_{1}} = %i GeV' % (mref)
                        leg.AddEntry(graph, legtext, 'lf');
                    except ReferenceError:
                        # print 'skip this one'
                        idx +=1
                        continue
                    idx += 1
                leg.Draw('SAME')
                plotname = self.crosssecfolder+'/plots/Crosssections_%s_L%s%s.pdf' % (processname, get_lambdastring(lamb), self.tag)
                if self.submit:
                    c.SaveAs(plotname)

                if 'LQLQ' in processname and not processname == 'LQLQ':
                    infile_brs = TFile(rootfilename_brs, 'READ')
                    infile_lqlq = TFile(self.crosssecfolder+'/Crosssections_LQLQ.root', 'READ')
                    decaymodes = procname_to_decaymodes[processname]
                    graphname_br1 = 'LQLQ_L%s_%i_%i' % (get_lambdastring(lamb), abs(decaymodes[0][0]), abs(decaymodes[0][1]))
                    graphname_br2 = 'LQLQ_L%s_%i_%i' % (get_lambdastring(lamb), abs(decaymodes[1][0]), abs(decaymodes[1][1]))
                    graph_br1 = infile_brs.Get(graphname_br1)
                    graph_br2 = infile_brs.Get(graphname_br2)

                    idx = 0
                    for mref in mrefs:
                        c_ratio = tdrDiCanvas('c_ratio', xaxis_min, xaxis_max, ymin, ymax, 0.3, 1.7, xaxis_title, '#sigma (pp #rightarrow %s) [pb]' % (procname_to_latex[processname]), '#sigma (full) / #sigma #times BR', square=True, iPeriod=0, iPos=11)
                        c_ratio.cd(1)
                        gPad.SetLogy()
                        leg_ratio = tdrLeg(0.55,0.8,0.9,0.9)
                        graphname_top = processname + '_MC1%i_L%s' % (mref, get_lambdastring(lamb))
                        graph_top = infile.Get(graphname_top)
                        graphname_xsecbr = 'LQLQ_MC1%i_L%s' % (mref, get_lambdastring(lamb))
                        graph_xsecbr = infile_lqlq.Get(graphname_xsecbr)
                        try:
                            c_ratio.cd(1)
                            tdrDraw(graph_top, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.2)
                            graph_top.GetXaxis().SetLabelSize(14)
                            masses_orig_top = array('d')
                            y_top_ups = array('d')
                            y_top_dns = array('d')
                            for i in range(graph_top.GetN()):
                                x=Double(0)
                                y=Double(0)
                                graph_top.GetPoint(i, x, y)
                                masses_orig_top.append(x)
                                y_top_ups.append(Double(graph_top.GetErrorYhigh(i)))
                                y_top_dns.append(Double(graph_top.GetErrorYlow(i)))

                            nremoved = 0
                            masses_orig_xsec = array('d')
                            for i in range(graph_xsecbr.GetN()):
                                x=Double(0)
                                y=Double(0)
                                graph_xsecbr.GetPoint(i-nremoved, x, y)
                                br1 = graph_br1.Interpolate(x, mref)
                                br2 = graph_br2.Interpolate(x, mref)
                                n_channels = 1 if (decaymodes[0] == decaymodes[1]) else 2
                                newval = y * br1 * br2 * n_channels
                                if y == 0 or newval == 0:
                                    graph_xsecbr.RemovePoint(i-nremoved)
                                    nremoved += 1
                                else:
                                    graph_xsecbr.SetPoint(i-nremoved, x, newval)
                                    masses_orig_xsec.append(x)
                            tdrDraw(graph_xsecbr, "LX", mcolor=colors[idx], lcolor=colors[idx])
                            graph_xsecbr.SetLineStyle(2)

                            # calculate ratio
                            graph_top_up = TGraph(len(masses_orig_top), masses_orig_top, y_top_ups)
                            graph_top_dn = TGraph(len(masses_orig_top), masses_orig_top, y_top_dns)
                            xs = array('d')
                            xs_up = array('d')
                            xs_dn = array('d')
                            ys = array('d')
                            ys_up = array('d')
                            ys_dn = array('d')
                            for mass in masses_orig_top:
                                if mass in masses_orig_xsec:
                                    xs.append(Double(mass))
                                    xs_up.append(Double(0))
                                    xs_dn.append(Double(0))
                                    ys.append(Double(graph_top.Eval(mass) / graph_xsecbr.Eval(mass)))
                                    ys_up.append(Double(graph_top_up.Eval(mass) / graph_xsecbr.Eval(mass)))
                                    ys_dn.append(Double(graph_top_dn.Eval(mass) / graph_xsecbr.Eval(mass)))
                            graph_ratio = TGraphAsymmErrors(len(xs), xs, ys, xs_dn, xs_up, ys_dn, ys_up)
                            c_ratio.cd(2)
                            tdrDraw(graph_ratio, "3L", mcolor=colors[idx], lcolor=colors[idx], fcolor=colors[idx], alpha=0.4)
                            legtext_ratio = 'M_{#chi_{1}} = %i GeV' % (mref)
                            leg_ratio.AddEntry(graph_top, legtext_ratio, 'lf');
                        except ReferenceError:
                            idx +=1
                            continue
                        idx += 1
                        plotname_ratio = self.crosssecfolder+'/plots/Crosssections_comparison_%s_MC1%i_L%s%s.pdf' % (processname, mref, get_lambdastring(lamb), self.tag)
                        if self.submit:
                            c_ratio.SaveAs(plotname_ratio)
                    infile_brs.Close()
                    infile_lqlq.Close()

                graphname2 = processname
                graphname2 += '_L%s' % (get_lambdastring(lamb))
                print lamb, graphname2
                graph2d = infile.Get(graphname2)
                h2 = TH2D('h2', 'h2', 500, min(preferred_configurations.keys()), max(preferred_configurations.keys()), 500, 100, 21000)
                graph2d.SetHistogram(h2)
                c2 = TCanvas('c2', 'c2', 800, 600)
                graph2d.Draw("COLZ")
                graph2d.GetHistogram().SetContour(150)
                graph2d.GetHistogram().GetXaxis().SetNdivisions(505)
                graph2d.GetHistogram().GetXaxis().SetTitle('M_{LQ} [GeV]')
                graph2d.GetHistogram().GetYaxis().SetTitle('M_{#chi_{1}} [GeV]')
                graph2d.GetHistogram().GetZaxis().SetTitle('#sigma (pp#rightarrow %s) [pb]' % (procname_to_latex[processname]))
                graph2d.GetHistogram().GetZaxis().SetTitleOffset(1.25)
                graph2d.GetHistogram().GetYaxis().SetTitleOffset(1.0)
                graph2d.GetHistogram().SetMaximum(1E-1)
                graph2d.GetHistogram().SetMinimum(2E-19)
                c2.SetLogy()
                c2.SetLogz()
                c2.SetRightMargin(0.20)
                c2.SetLeftMargin(0.13)
                c2.SetTopMargin(0.05)
                c2.Update()
                plotname = self.crosssecfolder+'/plots/Crosssections2d_%s_L%s%s.pdf' % (processname, get_lambdastring(lamb), self.tag)
                if self.submit:
                    c2.SaveAs(plotname)
            infile.Close()
            for lamb in self.lambdas:
                if processname == 'LQLQ':
                    # decaymodes = [(5, -15), (6, -16), (9000009, 9000007), (9000009, 9000008)]
                    decaymodes = decaymode_dict.keys()
                    mlqs_initial = [1000, 2000, 3000, 4500, 6000]
                    xaxis_min = 90
                    xaxis_max = 20000
                    xaxis_title = 'M_{#chi_{1}} [GeV]'
                    mlqs = []
                    for mlq in mlqs_initial:
                        mlqs.append(find_closest(sorted(preferred_configurations), mlq))

                    # open rootfile and get corresponding graphs
                    infile_brs = TFile(rootfilename_brs, 'READ')
                    print rootfilename_brs
                    for mlq in mlqs:
                        c3 = tdrCanvas('c3', xaxis_min, xaxis_max, 0, 1.1, xaxis_title, 'Branching ratio', square=True, iPeriod=0, iPos=11)
                        c3.SetLogx()
                        leg3 = tdrLeg(0.55,0.65,0.9,0.9)
                        legheader3 = 'M_{LQ} = %i GeV' % (mlq)
                        tdrHeader(leg3, legheader3)
                        idx = 0
                        for decaymode in decaymodes:
                            graphname3 = processname + '_MLQ%i_L%s_%i_%i' % (mlq, get_lambdastring(lamb), abs(decaymode[0]), abs(decaymode[1]))
                            # print graphname
                            graph3 = infile_brs.Get(graphname3)
                            try:
                                tdrDraw(graph3, "3L", mcolor=colors[idx], lcolor=colors[idx])
                                graph3.GetXaxis().SetLabelSize(14)
                                # legtext = 'M_{LQ} = %i GeV' % (mlq)
                                legtext3 = 'LQ #rightarrow %s' % (decaymode_dict[decaymode])
                                leg3.AddEntry(graph3, legtext3, 'l');
                            except ReferenceError:
                                # print 'skip this one'
                                idx +=1
                                continue
                            idx += 1
                        leg3.Draw('SAME')
                        plotname = self.crosssecfolder+'/plots/Branchingratios_%s_MLQ%i_L%s%s.pdf' % (processname, mlq, get_lambdastring(lamb), self.tag)
                        if self.submit:
                            print plotname
                            c3.SaveAs(plotname)

                    for decaymode in decaymodes:
                        try:
                            graphname = processname + '_L%s_%i_%i' % (get_lambdastring(lamb), abs(decaymode[0]), abs(decaymode[1]))
                            graph2d = infile_brs.Get(graphname)
                            h2 = TH2D('h2', 'h2', 500, min(preferred_configurations.keys()), max(preferred_configurations.keys()), 500, 100, 21000)
                            print decaymode, lamb, graphname
                            graph2d.SetHistogram(h2)
                            c4 = TCanvas('c4', 'c4', 800, 600)
                            graph2d.Draw("COLZ")
                            graph2d.GetHistogram().SetContour(150)
                            graph2d.GetHistogram().GetXaxis().SetNdivisions(505)
                            graph2d.GetHistogram().GetXaxis().SetTitle('M_{LQ} [GeV]')
                            graph2d.GetHistogram().GetYaxis().SetTitle('M_{#chi_{1}} [GeV]')
                            graph2d.GetHistogram().GetZaxis().SetTitle('BR (LQ #rightarrow %s)' % (decaymode_dict[decaymode]))
                            graph2d.GetHistogram().GetZaxis().SetTitleOffset(1.25)
                            graph2d.GetHistogram().GetYaxis().SetTitleOffset(1.0)
                            graph2d.GetHistogram().SetMaximum(0.7)
                            graph2d.GetHistogram().SetMinimum(0.)
                            c4.SetLogy()
                            c4.SetRightMargin(0.20)
                            c4.SetLeftMargin(0.13)
                            c4.SetTopMargin(0.05)
                            c4.Update()
                            plotname = self.crosssecfolder+'/plots/Branchingratios2d_%s_L%s_%i_%i%s.pdf' % (processname, get_lambdastring(lamb), abs(decaymode[0]), abs(decaymode[1]), self.tag)
                            if self.submit:
                                c4.SaveAs(plotname)
                        except AttributeError:
                            continue

                    infile_brs.Close()
