# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: Configuration/GenProduction/python/EXO-RunIIFall18wmLHEGS-02934-fragment.py --fileout file:EXO-RunIIFall18wmLHEGS-02934.root --mc --eventcontent RAWSIM,LHE --datatier GEN-SIM,LHE --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --step LHE,GEN,SIM --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename EXO-RunIIFall18wmLHEGS-02934_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring --customise_commands process.RandomNumberGeneratorService.externalLHEProducer.initialSeed=int(51) -n 1013


# Necessary setup (setup_slurm.sh):
###################################
# export SCRAM_ARCH=slc6_amd64_gcc700
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# cd /work/areimers/CMSSW_10_2_10/src
# eval `scramv1 runtime -sh`
# cd ../..
# voms-proxy-init --voms cms --valid 168:00

# Run like:
###########
# cmsRun pset_gensim_working.py nevents=10 gridpack=/work/areimers/LQDM/GENSIM/gridpacks/LQDM_MLQ1400_MX660_MDM600_L1p0_slc7_amd64_gcc700_CMSSW_9_3_16_tarball.tar.xz outfilename=GENSIM_working_1.root nThreads=1 skipSimStep=True

import FWCore.ParameterSet.Config as cms
from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
from Configuration.StandardSequences.Eras import eras
from FWCore.ParameterSet.VarParsing import VarParsing
import os


gridpack    = ''
outfilename = ''
nevents     = -1
nThreads    = -1
skipSimStep = True


# USER OPTIONS
options = VarParsing('analysis')
options.register('gridpack',    gridpack,    mytype=VarParsing.varType.string)
options.register('outfilename', outfilename, mytype=VarParsing.varType.string)
options.register('nevents',     nevents,     mytype=VarParsing.varType.int)
options.register('nThreads',    nThreads,    mytype=VarParsing.varType.int)
options.register('skipSimStep', skipSimStep, mytype=VarParsing.varType.bool)
options.parseArguments()
gridpack    = os.path.abspath(options.gridpack)
nevents     = options.nevents
nThreads    = options.nThreads
skipSimStep = options.skipSimStep
outfilename = 'file:' + os.path.abspath(options.outfilename)
outfile_LHE = outfilename.replace('.root', '_LHE.root')


if gridpack is '' or outfilename is '' or nevents is -1 or nThreads is -1:
    raise ValueError('At least one of the 4 mandatory options is not set, please give all 4 options.')


print ">>> gridpack    = '%s'"%gridpack
print ">>> nevents     = %s"%nevents
print ">>> nThreads    = %s"%nThreads
print ">>> skipSimStep = %s"%skipSimStep
print ">>> outfilename = '%s'"%outfilename
print ">>> outfile_LHE = '%s'"%outfile_LHE


process = cms.Process('SIM',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2018Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
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
    annotation = cms.untracked.string('Configuration/GenProduction/python/EXO-RunIIFall18wmLHEGS-02934-fragment.py nevts:1013'),
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
        dataTier = cms.untracked.string('GEN-SIM'),
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
process.XMLFromDBSource.label = cms.string("Extended")
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v11', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v21', '')

process.generator = cms.EDFilter("Pythia8HadronizerFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring(
            'pythia8CommonSettings',
            'pythia8CP2Settings',
            'pythia8PSweightsSettings'
        ),
        pythia8CP2Settings = cms.vstring(
            'Tune:pp 14',
            'Tune:ee 7',
            'MultipartonInteractions:ecmPow=0.1391',
            'PDF:pSet=17',
            'MultipartonInteractions:bProfile=2',
            'MultipartonInteractions:pT0Ref=2.306',
            'MultipartonInteractions:coreRadius=0.3755',
            'MultipartonInteractions:coreFraction=0.3269',
            'ColourReconnection:range=2.323',
            'SigmaTotal:zeroAXB=off',
            'SpaceShower:rapidityOrder=off',
            'SpaceShower:alphaSvalue=0.13',
            'TimeShower:alphaSvalue=0.13'
        ),
        pythia8CommonSettings = cms.vstring(
            'Tune:preferLHAPDF = 2',
            'Main:timesAllowErrors = 10000',
            'Check:epTolErr = 0.01',
            'Beams:setProductionScalesFromLHEF = off',
            'SLHA:keepSM = on',
            'SLHA:minMassSM = 1000.',
            'ParticleDecays:limitTau0 = on',
            'ParticleDecays:tau0Max = 10',
            'ParticleDecays:allowPhotonRadiation = on'
        ),
        pythia8PSweightsSettings = cms.vstring(
            'UncertaintyBands:doVariations = on',
            'UncertaintyBands:List = {isrRedHi isr:muRfac=0.707,fsrRedHi fsr:muRfac=0.707,isrRedLo isr:muRfac=1.414,fsrRedLo fsr:muRfac=1.414,isrDefHi isr:muRfac=0.5,fsrDefHi fsr:muRfac=0.5,isrDefLo isr:muRfac=2.0,fsrDefLo fsr:muRfac=2.0,isrConHi isr:muRfac=0.25,fsrConHi fsr:muRfac=0.25,isrConLo isr:muRfac=4.0,fsrConLo fsr:muRfac=4.0,fsr_G2GG_muR_dn fsr:G2GG:muRfac=0.5,fsr_G2GG_muR_up fsr:G2GG:muRfac=2.0,fsr_G2QQ_muR_dn fsr:G2QQ:muRfac=0.5,fsr_G2QQ_muR_up fsr:G2QQ:muRfac=2.0,fsr_Q2QG_muR_dn fsr:Q2QG:muRfac=0.5,fsr_Q2QG_muR_up fsr:Q2QG:muRfac=2.0,fsr_X2XG_muR_dn fsr:X2XG:muRfac=0.5,fsr_X2XG_muR_up fsr:X2XG:muRfac=2.0,fsr_G2GG_cNS_dn fsr:G2GG:cNS=-2.0,fsr_G2GG_cNS_up fsr:G2GG:cNS=2.0,fsr_G2QQ_cNS_dn fsr:G2QQ:cNS=-2.0,fsr_G2QQ_cNS_up fsr:G2QQ:cNS=2.0,fsr_Q2QG_cNS_dn fsr:Q2QG:cNS=-2.0,fsr_Q2QG_cNS_up fsr:Q2QG:cNS=2.0,fsr_X2XG_cNS_dn fsr:X2XG:cNS=-2.0,fsr_X2XG_cNS_up fsr:X2XG:cNS=2.0,isr_G2GG_muR_dn isr:G2GG:muRfac=0.5,isr_G2GG_muR_up isr:G2GG:muRfac=2.0,isr_G2QQ_muR_dn isr:G2QQ:muRfac=0.5,isr_G2QQ_muR_up isr:G2QQ:muRfac=2.0,isr_Q2QG_muR_dn isr:Q2QG:muRfac=0.5,isr_Q2QG_muR_up isr:Q2QG:muRfac=2.0,isr_X2XG_muR_dn isr:X2XG:muRfac=0.5,isr_X2XG_muR_up isr:X2XG:muRfac=2.0,isr_G2GG_cNS_dn isr:G2GG:cNS=-2.0,isr_G2GG_cNS_up isr:G2GG:cNS=2.0,isr_G2QQ_cNS_dn isr:G2QQ:cNS=-2.0,isr_G2QQ_cNS_up isr:G2QQ:cNS=2.0,isr_Q2QG_cNS_dn isr:Q2QG:cNS=-2.0,isr_Q2QG_cNS_up isr:Q2QG:cNS=2.0,isr_X2XG_cNS_dn isr:X2XG:cNS=-2.0,isr_X2XG_cNS_up isr:X2XG:cNS=2.0}',
            'UncertaintyBands:nFlavQ = 4',
            'UncertaintyBands:MPIshowers = on',
            'UncertaintyBands:overSampleFSR = 10.0',
            'UncertaintyBands:overSampleISR = 10.0',
            'UncertaintyBands:FSRpTmin2Fac = 20',
            'UncertaintyBands:ISRpTmin2Fac = 1'
        )
    ),
    comEnergy = cms.double(13000.0),
    filterEfficiency = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(1)
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
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)
process.LHEoutput_step = cms.EndPath(process.LHEoutput)

# Schedule definition
if skipSimStep:
    process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RAWSIMoutput_step,process.LHEoutput_step)
else:
    process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step,process.LHEoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(nThreads)
process.options.numberOfStreams=cms.untracked.uint32(0)
# filter all path with the production filter sequence
for path in process.paths:
	if path in ['lhe_step']: continue
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq

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
