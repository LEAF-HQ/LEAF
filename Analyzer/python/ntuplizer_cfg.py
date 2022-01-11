import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from RecoMuon.TrackingTools.MuonServiceProxy_cff import *

process = cms.Process("NTuples")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_v7', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
      '/store/mc/RunIISummer20UL17MiniAODv2/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v1/00000/9C735D57-8F9C-394D-BC45-D31EE59BBEFD.root'
   )
)



process.ntuplizer = cms.EDFilter('NTuplizer',
   muons = cms.InputTag("slimmedMuons"),
   primary_vertices = cms.InputTag('offlineSlimmedPrimaryVertices'),
   rho = cms.InputTag('fixedGridRhoFastjetAll'),
   l1prefiring = cms.InputTag('prefiringweight', 'nonPrefiringProb'),
   l1prefiring_up = cms.InputTag('prefiringweight', 'nonPrefiringProbUp'),
   l1prefiring_down = cms.InputTag('prefiringweight', 'nonPrefiringProbDown'),
   MET = cms.InputTag('slimmedMETs'),
   pileup = cms.InputTag('slimmedAddPileupInfo'),
   outfilename = cms.string("NTuples.root"),
   is_mc = cms.bool(True),
)





process.p = cms.Path(process.ntuplizer)
