# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: Configuration/GenProduction/python/B2G-RunIISummer19UL17wmLHEGEN-00041-fragment.py --fileout file:B2G-RunIISummer19UL17wmLHEGEN-00041.root --mc --eventcontent RAWSIM,LHE --datatier GEN,LHE --conditions 106X_mc2017_realistic_v7 --beamspot Realistic25ns13TeVEarly2017Collision --step LHE,GEN --geometry DB:Extended --era Run2_2017 --python_filename B2G-RunIISummer19UL17wmLHEGEN-00041_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 5450
import FWCore.ParameterSet.Config as cms
from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
from GeneratorInterface.ExternalDecays.TauolaSettings_cff import *
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *
from Configuration.Generator.PSweightsPythia.PythiaPSweightsSettings_cfi import *
from FWCore.ParameterSet.VarParsing import VarParsing
import os
from Configuration.Eras.Era_Run2_2017_cff import Run2_2017


gridpack    = ''
outfilename = ''
nevents     = -99
nThreads    = -1


# USER OPTIONS
options = VarParsing('analysis')
options.register('gridpack',    gridpack,    mytype=VarParsing.varType.string)
options.register('outfilename', outfilename, mytype=VarParsing.varType.string)
options.register('nevents',     nevents,     mytype=VarParsing.varType.int)
options.register('nThreads',    nThreads,    mytype=VarParsing.varType.int)
options.parseArguments()
gridpack    = os.path.abspath(options.gridpack)
nevents     = options.nevents
nThreads    = options.nThreads
outfilename = 'file:' + os.path.abspath(options.outfilename)
outfile_LHE = outfilename.replace('.root', '_LHE.root')


if gridpack is '' or outfilename is '' or nevents is -99 or nThreads is -1:
    raise ValueError('At least one of the 4 mandatory options is not set, please give all 4 options.')


print ">>> gridpack    = '%s'"%gridpack
print ">>> nevents     = %s"%nevents
print ">>> nThreads    = %s"%nThreads
print ">>> outfilename = '%s'"%outfilename
print ">>> outfile_LHE = '%s'"%outfile_LHE



process = cms.Process('GEN',Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2017Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nevents)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Configuration/GenProduction/python/B2G-RunIISummer19UL17wmLHEGEN-00041-fragment.py nevts:5450'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(1),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(20971520),
    fileName = cms.untracked.string(outfilename),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.LHEoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('LHE'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string(outfile_LHE),
    outputCommands = process.LHEEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_v6', '')

process.generator = cms.EDFilter("Pythia8HadronizerFilter",
    PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,
        pythia8CP5SettingsBlock,
        pythia8PSweightsSettingsBlock,
        parameterSets = cms.vstring('pythia8CommonSettings', 'pythia8CP5Settings', 'pythia8PSweightsSettings'),
    ),
    comEnergy = cms.double(13000.0),
    filterEfficiency = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    ExternalDecays = cms.PSet(
        Tauola = cms.untracked.PSet(
            TauolaPolar,
            InputCards = cms.PSet(
                pjak1 = cms.int32(0),
                pjak2 = cms.int32(0),
                mdtau = cms.int32(202)
            )
        ),
        parameterSets = cms.vstring('Tauola')
    )
)


process.externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    args = cms.vstring(gridpack),
    nEvents = cms.untracked.uint32(nevents),
    numberOfParameters = cms.uint32(1),
    outputFile = cms.string('cmsgrid_final.lhe'),
    scriptName = cms.FileInPath('GeneratorInterface/LHEInterface/data/run_generic_tarball_cvmfs.sh')
)


# Path and EndPath definitions
process.lhe_step = cms.Path(process.externalLHEProducer)
process.generation_step = cms.Path(process.pgen)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)
process.LHEoutput_step = cms.EndPath(process.LHEoutput)

# Schedule definition
process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RAWSIMoutput_step,process.LHEoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(nThreads)
process.options.numberOfStreams=cms.untracked.uint32(0)
# filter all path with the production filter sequence
for path in process.paths:
	if path in ['lhe_step']: continue
	getattr(process,path).insert(0, process.generator)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring
process = addMonitoring(process)

# End of customisation functions

# Customisation from command line
randSvc = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randSvc.populate() # set random number each cmsRun

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
