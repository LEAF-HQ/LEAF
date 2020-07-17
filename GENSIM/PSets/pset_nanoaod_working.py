# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step1 --filein dbs:/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM --fileout file:EXO-RunIIAutumn18NanoAODv7-00754.root --mc --eventcontent NANOEDMAODSIM --datatier NANOAODSIM --conditions 102X_upgrade2018_realistic_v21 --step NANO --nThreads 2 --era Run2_2018,run2_nanoAOD_102Xv1 --python_filename EXO-RunIIAutumn18NanoAODv7-00754_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 10000


# Necessary setup (setup_slurm.sh):
###################################
# export SCRAM_ARCH=slc6_amd64_gcc700
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# cd /work/areimers/CMSSW_10_2_10/src
# eval `scramv1 runtime -sh`
# cd ../..

# Run like:
###########
# cmsRun pset_nanoaod_working.py infilename=/pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/MINIAOD/MINIAOD_working_1.root outfilename=NANOAOD_working.root nevents=10 nThreads=5 index=1
# cmsRun pset_nanoaod_working.py infilename=/pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/MINIAOD/MINIAOD_working_1.root outfilename=/pnfs/psi.ch/cms/trivcat/store/user/areimers/NANOAOD_working.root nevents=10 nThreads=5 index=1



# Copy output to T2 and remove local file
# LD_LIBRARY_PATH='' PYTHONPATH='' gfal-copy file:////$PWD/MINIAOD_1.root gsiftp://storage01.lcg.cscs.ch//pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/MINIAOD/LQDM/; rm MINIAOD_1.root


import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

from FWCore.ParameterSet.VarParsing import VarParsing
import os


nevents     = -99
nThreads    = -1
infilename  = ''
outfilename = ''


# USER OPTIONS
options = VarParsing('analysis')
options.register('nevents',     nevents,     mytype=VarParsing.varType.int)
options.register('nThreads',    nThreads,    mytype=VarParsing.varType.int)
options.register('infilename',  infilename,  mytype=VarParsing.varType.string)
options.register('outfilename', outfilename, mytype=VarParsing.varType.string)
options.parseArguments()
nevents     = options.nevents
nThreads    = options.nThreads

if 'lcg.cscs.ch' in options.infilename or 'pnfs/psi.ch' in options.infilename:
    infilename += options.infilename
else:
    infilename += 'file:' + os.path.abspath(options.infilename)

outfilename = 'file:' + os.path.abspath(options.outfilename)

if nevents is -99 or nThreads is -1 or infilename is '' or outfilename is '':
    raise ValueError('At least one of the 4 mandatory options is not set, please give all 4 options.')

print ">>> nevents     = %s"%nevents
print ">>> nThreads    = %s"%nThreads
print ">>> infilename  = '%s'"%infilename
print ">>> outfilename = '%s'"%outfilename


process = cms.Process('NANO',eras.Run2_2018,eras.run2_nanoAOD_102Xv1)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nevents)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(infilename),
    secondaryFileNames = cms.untracked.vstring()
)
process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step1 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.NANOEDMAODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAODSIM'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string(outfilename),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v21', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODSIMoutput_step = cms.EndPath(process.NANOEDMAODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(nThreads)
process.options.numberOfStreams=cms.untracked.uint32(0)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.NanoAOD.nano_cff
from PhysicsTools.NanoAOD.nano_cff import nanoAOD_customizeMC

#call to customisation function nanoAOD_customizeMC imported from PhysicsTools.NanoAOD.nano_cff
process = nanoAOD_customizeMC(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
