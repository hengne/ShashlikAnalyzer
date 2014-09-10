import FWCore.ParameterSet.Config as cms


ShashlikAna = cms.EDAnalyzer('ShashlikTupleDumper',
    electronCollection = cms.InputTag("gsfElectrons"),
    mcTruthCollection = cms.InputTag("genParticles"),
    outputFile = cms.string("ShashlikTupleDumper.root"),
    DeltaR = cms.double(0.05),
    MatchingID = cms.vint32(11,-11),
    MatchingMotherID = cms.vint32(23,24,-24,32),
)
