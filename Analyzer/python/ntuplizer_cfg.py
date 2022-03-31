import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from FWCore.ParameterSet.VarParsing import VarParsing
import os

# Example to run:
# cmsRun $ANALYZERPATH/python/ntuplizer_cfg.py type=MC infilename=root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL18MiniAODv2/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/00000/D1F6F7C6-58B6-8142-9A44-D17FBB1C4F40.root outfilename=NTuples_pfonly.root idxStart=0 idxStop=100 year=UL18 standard=True pfcands=False triggerobjects=False stablegenparticles=False

# USER OPTIONS
options = VarParsing()
options.register('idxStart',           -99,     mytype=VarParsing.varType.int)
options.register('idxStop',            -99,     mytype=VarParsing.varType.int)
options.register('type',               '',      mytype=VarParsing.varType.string)
options.register('year',               '',      mytype=VarParsing.varType.string)
options.register('infilename',         '',      mytype=VarParsing.varType.string)
options.register('outfilename',        '',      mytype=VarParsing.varType.string)
options.register('standard',           'False', mytype=VarParsing.varType.string)
options.register('pfcands',            'False', mytype=VarParsing.varType.string)
options.register('triggerobjects',     'False', mytype=VarParsing.varType.string)
options.register('extrajets',          'False', mytype=VarParsing.varType.string)
options.register('stablegenparticles', 'False', mytype=VarParsing.varType.string)
options.parseArguments()

idx_start   = options.idxStart
idx_stop    = options.idxStop
type        = options.type
year        = options.year
infilename  = options.infilename
outfilename = options.outfilename
do_standard_event = options.standard.lower() == 'true'
do_pfcands  = options.pfcands.lower() == 'true'
do_triggerobjects = options.triggerobjects.lower() == 'true'
do_extrajets = options.extrajets.lower() == 'true'
do_stablegenparticles = options.stablegenparticles.lower() == 'true'

if idx_start < 0 or idx_stop < 1 or type is '' or year is '' or infilename is '' or outfilename is '':
    raise ValueError('At least one of the 6 required options is not set properly, please give all 6 options.')
if not type in ['DATA', 'MC']:
    raise ValueError('Invalid value for argument \'type\': %s. Can be \'MC\' or \'DATA\'.' % (type))
if not idx_start < idx_stop:
    raise ValueError('Invalid value for arguments \'idx-start\' and \'idx-stop\': %i and %i. The stop index must be greater than the start index.' % (idx_start, idx_stop))
if not (do_standard_event or do_pfcands or do_triggerobjects or do_extrajets or do_stablegenparticles):
   raise AttributeError('None of the collections is being requested, this sample would be empty! Is this a bug?')

do_ak4chs = do_standard_event
do_ak4puppi = do_extrajets
do_ak8puppi = do_extrajets

print '-->  idx-start    = %s'     % idx_start
print '-->  idx-stop     = %s'     % idx_stop
print '-->  type         = %s'     % type
print '-->  year         = %s'     % year
print '-->  infilename   = \'%s\'' % infilename
print '-->  outfilename  = \'%s\'' % outfilename
print '-->  do_standard_event  = \'%s\'' % do_standard_event
print '-->  do_triggerobjects  = \'%s\'' % do_triggerobjects
print '-->  do_stablegenparticles = \'%s\'' % do_stablegenparticles
print '-->  do_pfcands   = \'%s\'' % do_pfcands
print '-->  do_ak4chs    = \'%s\'' % do_ak4chs
print '-->  do_ak4puppi  = \'%s\'' % do_ak4puppi
print '-->  do_ak8puppi  = \'%s\'' % do_ak8puppi

process = cms.Process("NTuples")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_v7', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(idx_stop - idx_start) )

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(infilename),
   skipEvents= cms.untracked.uint32(idx_start)
)

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
    jets_ak4chs       = cms.InputTag('slimmedJets'),
    jets_ak4puppi     = cms.InputTag('slimmedJetsPuppi'),
    jets_ak8puppi     = cms.InputTag('slimmedJetsAK8'),
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
    genparticles_pruned = cms.InputTag('prunedGenParticles'),
    genparticles      = cms.InputTag('packedGenParticles'),
    geninfo           = cms.InputTag('generator'),
    lhe               = cms.InputTag('externalLHEProducer'),

    do_standard_event = cms.bool(do_standard_event),
    do_triggerobjects = cms.bool(do_triggerobjects),
    do_pfcands        = cms.bool(do_pfcands),
    do_stablegenparticles = cms.bool(do_stablegenparticles),
    do_prefiring      = cms.bool(not year in ['2018', 'UL18']),
    do_ak4chs         = cms.bool(do_ak4chs),
    do_ak4puppi       = cms.bool(do_ak4puppi),
    do_ak8puppi       = cms.bool(do_ak8puppi),

    outfilename       = cms.string(outfilename),
    is_mc             = cms.bool(is_mc),
    year              = cms.string(year)
)





process.p = cms.Path(process.ntuplizer)
