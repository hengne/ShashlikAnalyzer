import FWCore.ParameterSet.Config as cms


ShashlikAna = cms.EDAnalyzer('ShashlikTupleDumper',
    electronCollection = cms.InputTag("gsfElectrons"),
    superClusterEB = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALBarrel"),
    superClusterEE = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALEndcapWithPreshower"),
    mcTruthCollection = cms.InputTag("genParticles"),
    barrelRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    endcapRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEK"),
    outputFile = cms.string("ShashlikTupleDumper.root"),
    DeltaR = cms.double(0.1),
    MatchingMotherID = cms.vint32(23,25),
    printMCtable = cms.bool(False)

)
