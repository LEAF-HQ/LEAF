# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step1 --fileout file:EXO-RunIIAutumn18DRPremix-03463_step1.root --pileup_input dbs:/Neutrino_E-10_gun/RunIISummer17PrePremix-PUAutumn18_102X_upgrade2018_realistic_v15-v1/GEN-SIM-DIGI-RAW --mc --eventcontent PREMIXRAW --datatier GEN-SIM-RAW --conditions 102X_upgrade2018_realistic_v15 --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:@relval2018 --procModifiers premix_stage2 --nThreads 8 --geometry DB:Extended --datamix PreMix --era Run2_2018 --python_filename EXO-RunIIAutumn18DRPremix-03463_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 2626


# Necessary setup (setup_slurm.sh):
###################################
# export SCRAM_ARCH=slc6_amd64_gcc700
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# cd /work/areimers/CMSSW_10_2_10/src
# eval `scramv1 runtime -sh`
# cd ../..

# Run like:
###########
# cmsRun pset_dr_working.py infilename=/pnfs/lcg.cscs.ch/cms/trivcat/store/user/areimers/GENSIM/LQDM/GENSIM_1.root outfilename=DRPREMIX.root nevents=100 nThreads=1 doSimStep=False
# cmsRun pset_dr_working.py infilename=../01GridpackToGensim/GENSIM_working_1.root outfilename=DR_working.root nevents=10 nThreads=5 doSimStep=True


import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
from Configuration.ProcessModifiers.premix_stage2_cff import premix_stage2

from mixdata import mixdatalist
from FWCore.ParameterSet.VarParsing import VarParsing
import os


nevents     = -99
nThreads    = -1
infilename  = ''
outfilename = ''
doSimStep   = True


# USER OPTIONS
options = VarParsing('analysis')
options.register('nevents',     nevents,     mytype=VarParsing.varType.int)
options.register('nThreads',    nThreads,    mytype=VarParsing.varType.int)
options.register('infilename',  infilename,  mytype=VarParsing.varType.string)
options.register('outfilename', outfilename, mytype=VarParsing.varType.string)
options.register('doSimStep',   doSimStep,   mytype=VarParsing.varType.bool)
options.parseArguments()
nevents     = options.nevents
nThreads    = options.nThreads
doSimStep   = options.doSimStep

infilename  = ''
if 'lcg.cscs.ch' in options.infilename or 'pnfs/psi.ch' in options.infilename:
    infilename += options.infilename
else:
    infilename += 'file:' + os.path.abspath(options.infilename)

outfilename = 'file:' + os.path.abspath(options.outfilename)

if nevents is -99 or nThreads is -1 or infilename is '' or outfilename is '':
    raise ValueError('At least one of the 5 mandatory options is not set, please give all 5 options.')

print ">>> nevents     = %s"%nevents
print ">>> nThreads    = %s"%nThreads
print ">>> infilename  = '%s'"%infilename
print ">>> outfilename = '%s'"%outfilename






process = cms.Process('HLT',eras.Run2_2018,premix_stage2)

# import of standard configurations
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.DigiDM_cff')
process.load('Configuration.StandardSequences.DataMixerPreMix_cff')
process.load('Configuration.StandardSequences.SimL1EmulatorDM_cff')
process.load('Configuration.StandardSequences.DigiToRawDM_cff')
process.load('HLTrigger.Configuration.HLT_2018v32_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nevents)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring(infilename),
    inputCommands = cms.untracked.vstring(
        'keep *',
        'drop *_genParticles_*_*',
        'drop *_genParticlesForJets_*_*',
        'drop *_kt4GenJets_*_*',
        'drop *_kt6GenJets_*_*',
        'drop *_iterativeCone5GenJets_*_*',
        'drop *_ak4GenJets_*_*',
        'drop *_ak7GenJets_*_*',
        'drop *_ak8GenJets_*_*',
        'drop *_ak4GenJetsNoNu_*_*',
        'drop *_ak8GenJetsNoNu_*_*',
        'drop *_genCandidatesForMET_*_*',
        'drop *_genParticlesForMETAllVisible_*_*',
        'drop *_genMetCalo_*_*',
        'drop *_genMetCaloAndNonPrompt_*_*',
        'drop *_genMetTrue_*_*',
        'drop *_genMetIC5GenJs_*_*'
    ),
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

process.PREMIXRAWoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string(outfilename),
    outputCommands = process.PREMIXRAWEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from mixdata import mixdatalist
process.mixData.input.fileNames = cms.untracked.vstring(mixdatalist)
from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v21', '')

# Path and EndPath definitions
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.datamixing_step = cms.Path(process.pdatamix)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.PREMIXRAWoutput_step = cms.EndPath(process.PREMIXRAWoutput)

# Schedule definition
if doSimStep:
    process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step,process.datamixing_step,process.L1simulation_step,process.digi2raw_step)
else:
    process.schedule = cms.Schedule(process.digitisation_step,process.datamixing_step,process.L1simulation_step,process.digi2raw_step)
# process.schedule = cms.Schedule(process.digitisation_step,process.datamixing_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.PREMIXRAWoutput_step])
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(nThreads)
process.options.numberOfStreams=cms.untracked.uint32(0)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
