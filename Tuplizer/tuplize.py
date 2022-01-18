#! /usr/bin/env python

import os

from TuplizeRunner import *

from Samples.Data_MiniAODv2 import *
from Samples.Backgrounds_MiniAODv2 import *
from Samples.Signals_MiniAODv2 import *


username = os.environ['USER']
workarea = macrofolder = os.environ['TUPLIZERPATH']+'/Workarea'
macrofolder = os.environ['ANALYZERPATH']

AllSamples = SampleContainer()
Add_Data(AllSamples)
Add_Background(AllSamples)
Add_LQSignals(AllSamples)
print (AllSamples)


config_per_year = {
    'UL17': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_28'
    },
    'UL18': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_28'
    }
}




year = 'UL18'
stage = 'mini'
submit = True
nevt_per_job = 100000




def main():
    for samplename, sample in AllSamples.items():
        print green('--> Working on sample: \'%s\'' % (samplename))
        # Tuplizer = TuplizeRunner(sample=sample, stage=stage, year=year, config=config_per_year[year], workarea=workarea, submit=submit)
        # Tuplizer.CountEvents(check_missing=True)
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00,00), nevt_per_job=nevt_per_job, mode='new')
        # Tuplizer.CleanBrokenFiles(nevt_per_job=nevt_per_job, only_check_missing=True)
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(02,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(05,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(23,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.CreateDatasetXMLFile(force_counting=True, count_weights=False)
        # Tuplizer.PrintDASCrossSection(sample=s, year=year, recalculate=True)
    create_default_config(allsamples=AllSamples, year='UL17', configoutname= os.path.join(os.environ['LEAFPATH'], 'LQDM', 'config', 'Default.xml'))














def create_default_config(allsamples, year, configoutname='default_config.xml'):
    samplenames = [x[0] for x in allsamples.items()]
    templatefilename = os.path.join(os.environ['LEAFPATH'], 'templates', 'config_template.xml')
    newlines = []
    with open(templatefilename, 'r') as f:
        lines = f.readlines()
        found_entity = False
        found_configuration = False
        found_dataset_start = False
        for i, line in enumerate(lines):
            newline = line
            if '<!ENTITY' in line and not 'TargetLumi' in line and not 'outfilepath' in line :
                if found_entity: continue
                found_entity = True

                # replace this line with all the entities we need according to our samples
                for samplename in samplenames:
                    s = allsamples.get_sample(samplename)
                    newline = '<!ENTITY %s SYSTEM "%s" >\n' % (s.name, os.path.join(macrofolder, s.xmlfiles[year]))
                    newlines.append(newline)
            elif '<Configuration' in line:
                if found_configuration: continue
                found_configuration = True
                newline = line.replace('$MYTOOLNAME', '#REPLACEME')
                newlines.append(newline)
            elif '<Dataset' in line :
                if found_dataset_start: continue
                found_dataset_start = True
                for samplename in samplenames:
                    s = allsamples.get_sample(samplename)
                    if s.type is 'DATA':
                        samplelumi = 1.
                    elif s.xsecs[year] is not None:
                        samplelumi = float(s.nevents[year]) / float(s.xsecs[year])
                    elif s.nevents[year] is not None:
                        samplelumi = float(s.nevents[year]) # normalize to 1 pb
                    else:
                        raise ValueError('Cannot assign lumiweight for sample \'%s\', please check. Abort.' % (samplename))
                    newline = '        <Dataset Name="%s"                Lumi="%.10g"  Year="%s" Type="%s" Group="%s" >                 &%s;                </Dataset>\n' % (s.name, samplelumi, year, s.type, str(s.group[year]), s.name)
                    newlines.append(newline)
            else:
                newlines.append(line)
    # print newlines
    with open(configoutname, 'w') as f:
        for l in newlines:
            f.write(l)
    print green('--> created default config file \'%s\'' % (configoutname))



if __name__ == '__main__':
    main()
