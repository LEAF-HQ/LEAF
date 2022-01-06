
import os, sys, math, time
import subprocess
from utils import *
from collections import OrderedDict
from ROOT import TFile, TH1D

def ProduceCombineHistograms(self, signal_scaled_by=1., blind=True, use_fake_data=True):
    print green('  --> Producing histograms for combine.')

    samples = self.signals + self.backgrounds + ['DATA']
    syst_shifts = [('up', 'Up'), ('down', 'Down')]

    ensureDirectory(self.combineinput_path)
    outfilename = os.path.join(self.combineinput_path, 'combine_histograms.root')
    outfile = TFile(outfilename, 'RECREATE')

    # loop
    for category in self.histnames_in_out_per_category:
        for channel in self.channels:
            for syst in self.systematics:
                print green('  --> Systematic: %s' % (syst))
                for shiftidx, syst_shift in enumerate(syst_shifts):
                    dir_nom = self.finalselection_path

                    if syst == 'nominal' and shiftidx > 0: continue
                    for sample in samples:
                        type = 'DATA__' if sample == 'DATA' else 'MC__'

                        force_nominal = False
                        sample_out = sample
                        if sample_out == 'DATA': sample_out = 'data_obs_' + self.year
                        else:                    sample_out += '_' + self.year
                        print green('    --> Sample: %s' % (sample))

                        if sample == 'DATA' and not syst == 'nominal': force_nominal = True
                        if not syst in self.processes_per_systematic.keys() and not syst == 'nominal': raise ValueError('When producing combine histograms: found systematic in systematic list that is not covered by \'processes_per_systematic\' dictionary. Please add it there and in the other dictionaries.')
                        if not syst == 'nominal' and not sample == self.processes_per_systematic[syst] and not self.processes_per_systematic[syst] == 'all': force_nominal = True
                        if not syst == 'nominal' and self.pdf_per_systematic[syst] == 'lnN': force_nominal = True

                        if sample == 'DATA': # choose correct PD
                            if blind and use_fake_data:
                                sample = samples[0] if not (samples[0] == 'DATA') else samples[1]
                                type = 'MC__'
                                print '!!! Using fake data for Combine, since we are running blind. Can override this by setting \'use_fake_data\' to \'False\''
                            else:
                                if channel == 'much' or channel == 'elmuch':
                                    sample += '_SingleMuon'
                                elif channel == 'elch':
                                    sample += '_SingleElectron'
                                elif channel == 'tach':
                                    sample += '_Tau'
                                elif channel == None:
                                    raise ValueError('Using unspecific channel \'None\', please use different channel name or hard-code a PD name (dangerous)')
                                else:
                                    raise ValueError('Which data to use for channel \'%s\'?' % (channel))

                        infilename = os.path.join(dir_nom, type+sample+'.root')
                        infile = TFile(infilename, 'READ')

                        histname_in = '_'.join([x for x in [channel, category, syst, self.limithisttag] if x is not None])
                        if force_nominal: histname_in = '_'.join([x for x in [channel, category, 'nominal', self.limithisttag] if x is not None])
                        if not syst == 'nominal' and not force_nominal: histname_in = '_'.join([histname_in, syst_shift[0]])
                        histname_in += '/' + self.histnames_in_out_per_category[category][0]

                        histname_out = '_'.join([x for x in [self.histnames_in_out_per_category[category][1], channel, category] if x is not None]) + '__' + sample_out
                        if not syst == 'nominal': histname_out += '__' + syst + syst_shift[1]
                        h_in = infile.Get(histname_in)
                        h_in.SetName(histname_out)
                        h_in.Scale(signal_scaled_by)
                        outfile.cd()
                        h_in.Write()
                        infile.Close()

    print green('  --> Finished producing the combine histograms in \'%s\'.' % (outfilename))
