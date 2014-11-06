import FWCore.ParameterSet.Config as cms


ShashlikAna = cms.EDAnalyzer('ShashlikTupleDumper',
    electronCollection = cms.InputTag("gsfElectrons"),
    mcTruthCollection = cms.InputTag("genParticles"),
    barrelRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    endcapRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEK"),
    outputFile = cms.string("ShashlikTupleDumper.root"),
    DeltaR = cms.double(0.05),
    MatchingMotherID = cms.vint32(0),
)
