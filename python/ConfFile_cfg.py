import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/nfs/dust/cms/user/zoiirene/DiBoson/GravitonToWW/FixingPU/2000/step2/EXO-RunIISummer16DR80Premix-08160_step2_97.root',
    )
)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(-1),
  printVertex = cms.untracked.bool(False),
  printOnlyHardInteraction = cms.untracked.bool(False), # Print only status=3 particles. This will not work for Pythia8, which does not have any such particles.
  src = cms.InputTag("genParticles")
)

process.filt = cms.EDFilter("GenFilter"
)

process.p = cms.Path(process.filt*process.printTree)
