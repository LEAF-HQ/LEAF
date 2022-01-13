import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from FWCore.ParameterSet.VarParsing import VarParsing
import os


idx_start   = -99
idx_stop    = -99
type        = ''
year        = ''
infilename  = ''
outfilename = ''


# USER OPTIONS
options = VarParsing()
options.register('idxStart',   idx_start,   mytype=VarParsing.varType.int)
options.register('idxStop',    idx_stop,    mytype=VarParsing.varType.int)
options.register('type',        type,        mytype=VarParsing.varType.string)
options.register('year',        year,        mytype=VarParsing.varType.string)
options.register('infilename',  infilename,  mytype=VarParsing.varType.string)
options.register('outfilename', outfilename, mytype=VarParsing.varType.string)
options.parseArguments()

idx_start   = options.idxStart
idx_stop    = options.idxStop
type        = options.type
year        = options.year
infilename  = options.infilename
outfilename = options.outfilename

if idx_start < 0 or idx_stop < 1 or type is '' or year is '' or infilename is '' or outfilename is '':
    raise ValueError('At least one of the 6 required options is not set properly, please give all 6 options.')
if not type in ['DATA', 'MC']:
    raise ValueError('Invalid value for argument \'type\': %s. Can be \'MC\' or \'DATA\'.' % (type))
if not idx_start < idx_stop:
    raise ValueError('Invalid value for arguments \'idx-start\' and \'idx-stop\': %i and %i. The stop index must be greater than the start index.' % (idx_start, idx_stop))

print '-->  idx-start   = %s'     % idx_start
print '-->  idx-stop    = %s'     % idx_stop
print '-->  type        = %s'     % type
print '-->  year        = %s'     % year
print '-->  infilename  = \'%s\'' % infilename
print '-->  outfilename = \'%s\'' % outfilename

process = cms.Process("NTuples")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_v7', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(idx_stop - idx_start) )

# '/store/mc/RunIISummer20UL17MiniAODv2/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v1/00000/9C735D57-8F9C-394D-BC45-D31EE59BBEFD.root'
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(infilename),
   skipEvents= cms.untracked.uint32(idx_start)
)

# cmsRun python/ntuplizer_cfg.py type=MC infilename=/store/mc/RunIISummer20UL17MiniAODv2/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v1/00000/9C735D57-8F9C-394D-BC45-D31EE59BBEFD.root outfilename=NTuples_args.root idxStart=100 idxStop=350 year=UL17

process.load("FWCore.MessageService.MessageLogger_cfi")
# process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options = cms.untracked.PSet(
    wantSummary=cms.untracked.bool(False),
    numberOfStreams = cms.untracked.uint32(0) # 0 = use number of threads; to set use -n
)

# process.Timing = cms.Service("Timing",
#     summaryOnly=cms.untracked.bool(False),
#     useJobReport=cms.untracked.bool(True)
# )

# process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#     ignoreTotal=cms.untracked.int32(2),
#     oncePerEventMode=cms.untracked.bool(True),
#     moduleMemorySummary=cms.untracked.bool(True)
# )


is_mc = (type == 'MC')

metfilterstep = 'PAT'
if not is_mc:
    metfilterstep = 'RECO'

process.ntuplizer = cms.EDFilter('NTuplizer',
    muons             = cms.InputTag('slimmedMuons'),
    ak4jets           = cms.InputTag('slimmedJets'),
    electrons         = cms.InputTag('slimmedElectrons'),
    taus              = cms.InputTag('slimmedTaus'),
    hltresults        = cms.InputTag('TriggerResults', '', 'HLT'),
    metfilterresults  = cms.InputTag('TriggerResults', '', metfilterstep),
    triggerobjects    = cms.InputTag('slimmedPatTrigger'),
    pfcands           = cms.InputTag('packedPFCandidates'),
    primary_vertices  = cms.InputTag('offlineSlimmedPrimaryVertices'),
    rho               = cms.InputTag('fixedGridRhoFastjetAll'),
    l1prefiring       = cms.InputTag('prefiringweight', 'nonPrefiringProb'),
    l1prefiring_up    = cms.InputTag('prefiringweight', 'nonPrefiringProbUp'),
    l1prefiring_down  = cms.InputTag('prefiringweight', 'nonPrefiringProbDown'),
    met               = cms.InputTag('slimmedMETs'),
    pileup            = cms.InputTag('slimmedAddPileupInfo'),
    genjets           = cms.InputTag('slimmedGenJets'),
    genparticles      = cms.InputTag('prunedGenParticles'),
    geninfo           = cms.InputTag('generator'),
    lhe               = cms.InputTag('externalLHEProducer'),

    do_triggerobjects = cms.bool(False),
    do_pfcands        = cms.bool(False),
    do_prefiring      = cms.bool(not year in ['2018', 'UL18']),

    outfilename       = cms.string(outfilename),
    is_mc             = cms.bool(is_mc),
    year              = cms.string(year)
)





process.p = cms.Path(process.ntuplizer)
