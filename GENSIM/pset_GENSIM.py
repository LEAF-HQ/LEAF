#! /usr/bin/env cmsRun
# Author: Izaak Neutelings (November, 2019)
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: Configuration/GenProduction/python/EXO-RunIIFall18wmLHEGS-00790-fragment.py --fileout file:EXO-RunIIFall18wmLHEGS-00790.root --mc --eventcontent RAWSIM,LHE --datatier GEN-SIM,LHE --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --step LHE,GEN,SIM --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename EXO-RunIIFall18wmLHEGS-00790_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring --customise_commands process.RandomNumberGeneratorService.externalLHEProducer.initialSeed=int() -n 732
print ">>> %s start pset_GENSIM.py %s"%('-'*15,'-'*15)
import os
import FWCore.ParameterSet.Config as cms
from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
from utils import format_tag
from eras import globaltags, eras

# DEFAULTS
gridpack       = "/cvmfs/cms.cern.ch/phys_generator/gridpacks/2017/13TeV/madgraph/V5_2.6.0/VectorLQ/VectorLQ_M1100_slc6_amd64_gcc630_CMSSW_9_3_8_tarball_v2.tar.xz"
sample         = "" #"test"
index          = -1
year           = 2018
nevents        = 100
seed           = -1
nThreads       = 2
signal         = "VectorPair"
skipSimStep    = True #and False
globaltag      = '102X_upgrade2018_realistic_v11'

# USER OPTIONS
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register('index',    index,    mytype=VarParsing.varType.int)
options.register('sample',   sample,   mytype=VarParsing.varType.string)
options.register('gridpack', gridpack, mytype=VarParsing.varType.string)
options.register('year',     year,     mytype=VarParsing.varType.int)
options.register('nevents',  nevents,  mytype=VarParsing.varType.int)
options.register('seed',     seed,     mytype=VarParsing.varType.int)
options.register('nThreads', nThreads, mytype=VarParsing.varType.int)
options.parseArguments()
sample      = options.sample
index       = options.index
gridpack    = os.path.abspath(options.gridpack)
year        = options.year
nevents     = options.nevents
seed        = options.seed
nThreads    = options.nThreads
###globaltag = globaltags['miniAOD'].get(year,'auto:phase1_2017_realistic')
tag         = sample
if index>0:
  tag      += format_tag('_'+str(index))
outfile_RAW = "file:GENSIM%s.root"%(tag)
outfile_LHE = "file:GENSIM_LHE%s.root"%(tag)

print ">>> sample      = '%s'"%sample
print ">>> index       = %s"%index
print ">>> gridpack    = '%s'"%gridpack
print ">>> year        = %s"%year
print ">>> nevents     = %s"%nevents
print ">>> nThreads    = %s"%nThreads
print ">>> globaltag   = '%s'"%globaltag
print ">>> outfile_RAW = '%s'"%outfile_RAW
print ">>> outfile_LHE = '%s'"%outfile_LHE
print ">>> "+'-'*52

# PROCESS
process = cms.Process('SIM',eras['SIM'][year])

# IMPORTS
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
#process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2017Collision_cfi')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2018Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# INPUT
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(nevents)
)
process.source = cms.Source('EmptySource')
process.options = cms.untracked.PSet()

# INFO
process.configurationMetadata = cms.untracked.PSet(
  annotation = cms.untracked.string('Configuration/GenProduction/python/EXO-RunIIFall18wmLHEGS-00790-fragment.py nevts:732'),
  name = cms.untracked.string('Applications'),
  version = cms.untracked.string('$Revision: 1.19 $')
)

# OUTPUT
process.RAWSIMoutput = cms.OutputModule('PoolOutputModule',
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
  fileName = cms.untracked.string(outfile_RAW),
  outputCommands = process.RAWSIMEventContent.outputCommands,
  splitLevel = cms.untracked.int32(0)
)
process.LHEoutput = cms.OutputModule('PoolOutputModule',
  dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('LHE'),
      filterName = cms.untracked.string('')
  ),
  fileName = cms.untracked.string(outfile_LHE),
  outputCommands = process.LHEEventContent.outputCommands,
  splitLevel = cms.untracked.int32(0)
)

# Other statements
process.XMLFromDBSource.label = cms.string('Extended')
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globaltag, '')

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

# PATH DEFINITIONS
process.lhe_step = cms.Path(process.externalLHEProducer)
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)
process.LHEoutput_step = cms.EndPath(process.LHEoutput)

# SCHEDULE
if skipSimStep:
  process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,
                                  process.endjob_step,process.RAWSIMoutput_step,process.LHEoutput_step)
else:
  process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,
                                  process.simulation_step,
                                  process.endjob_step,process.RAWSIMoutput_step,process.LHEoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# SETUP FWK for multithreaded
process.options.numberOfThreads = cms.untracked.uint32(nThreads)
process.options.numberOfStreams = cms.untracked.uint32(0)
for path in process.paths: # filter all path with the production filter sequence
  if path in ['lhe_step']: continue
  getattr(process,path)._seq = process.generator * getattr(process,path)._seq

# CUSTUMIZATION
from Configuration.DataProcessing.Utils import addMonitoring
process = addMonitoring(process)

# CUSTUMIZATION from command line
if seed>0:
  process.RandomNumberGeneratorService.externalLHEProducer.initialSeed = int(seed)
else:
  randSvc = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
  randSvc.populate() # set random number each cmsRun
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete # early deletion of temporary data products to reduce peak memory need
process = customiseEarlyDelete(process)

print ">>> %s done pset_GENSIM.py %s"%('-'*15,'-'*16)
