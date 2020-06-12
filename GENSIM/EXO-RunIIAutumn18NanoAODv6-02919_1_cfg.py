# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step1 --filein dbs:/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM --fileout file:EXO-RunIIAutumn18NanoAODv6-02919.root --mc --eventcontent NANOEDMAODSIM --datatier NANOAODSIM --conditions 102X_upgrade2018_realistic_v20 --step NANO --nThreads 2 --era Run2_2018,run2_nanoAOD_102Xv1 --python_filename EXO-RunIIAutumn18NanoAODv6-02919_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 10000
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

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
    input = cms.untracked.int32(10000)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/84F1CDC0-2028-804B-B255-77C75EBEFCCD.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/E23C5888-DBB1-7546-9EA6-82ADEA7926CE.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/33EC4432-7DC7-4D45-9A03-DF9AECC64036.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/D7BD3726-B85E-9A43-AEA3-EA5F06B47298.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/D1456C5F-5EA8-5345-9E58-9493D80A3B78.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/B20AAD9A-765A-314A-92C7-1E5F9D196AB3.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/26A6F3F1-453F-0341-A806-45B9BDA09910.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/6B3B68E6-FA10-8C47-B150-BB4D1BBAEB49.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/1BD25200-792A-BA4B-8E9E-2A67106AEE11.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/54ABCD90-022A-DB4E-965D-BA2BAF6F0A8D.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/ADF0126A-D0D8-FA48-9B69-83A9B17F4A14.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/3130A1F0-34B1-5643-8BE2-1FFAA5D7827F.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/64CE0C51-9B9E-FB4B-8D23-DF152DEFA12F.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/2D26DE92-279B-5D4F-88C6-709B9F9B80F8.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/80357A0A-B584-584F-A90C-18053FEA4904.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/E8DBD07D-529E-234F-A40E-0AC874C204BD.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/2F23B9E1-4B84-9D45-BD2E-D3955AA51884.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/D7383583-D45A-464D-871F-5D059244572C.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/F3EB89CE-B508-E240-AE87-6CC5805CEE6C.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/77FE0CC3-E2A6-9845-B947-A91A2A36F59D.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/E6E0326F-E233-E442-9D63-FE91538649C8.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/AE05CDCD-C815-9348-87C0-0A07154387A6.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/A02AB457-3BBE-8E43-8B2B-7DEC991259D4.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/A8D80EF5-9DBC-8345-8EFF-AA9E3B708EFA.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/5AF72408-7F63-FD45-AD2A-5AD3E4E46720.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/C02D6ED6-F8B9-5D46-B855-E6D29FC4A275.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/22054120-888F-8C4C-B010-5C19D87763D2.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/8E6D2EEE-B718-4A4D-B62E-88E77039F5C3.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/CF6B6B00-099C-D84D-AE6E-035E771D76CA.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/A3C65FEE-D7FD-9D4D-BEC7-D63BD808FB1F.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/01A5C3EE-E29B-9D4F-A0AC-069A29636318.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/CA461654-10A6-024F-9C77-9238E9D111DA.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/F18C2138-4E18-F44E-9412-845C9F0B2ACA.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/9BD86E43-77F1-D747-9BDE-78066DB46CF4.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/E06785FC-912D-784B-ABF1-E8E497280506.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/65C82A62-CF2D-8540-AAF8-DE1D7DAC7234.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/C02EA76A-1B75-B942-9CFF-0EC311447BD3.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/B079C4AC-FC0F-A546-B2E5-CCC33C0DC920.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/1CB7380A-C11E-FA4D-98EF-09CD1D43F829.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/A928F426-C6C8-CD4F-9351-E1985D17EC4A.root', 
        '/store/mc/RunIIAutumn18MiniAOD/SingleScalarLQ_InclusiveDecay_M-1100_L-1p0_TuneCP2_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/10000/3522F438-285B-EE4C-B63A-DD8BC9E4BA54.root'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step1 nevts:10000'),
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
    fileName = cms.untracked.string('file:EXO-RunIIAutumn18NanoAODv6-02919.root'),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v20', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODSIMoutput_step = cms.EndPath(process.NANOEDMAODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(2)
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
