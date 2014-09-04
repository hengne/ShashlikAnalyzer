import FWCore.ParameterSet.Config as cms


from ShashlikAnalyzer.ShashlikAnalyzer.mcAnalyzerStdBiningParameters_cff import *
from ShashlikAnalyzer.ShashlikAnalyzer.mcAnalyzerFineBiningParameters_cff import *

ShashlikAna = cms.EDAnalyzer('ShashlikAnalyzer',
    electronCollection = cms.InputTag("gsfElectrons"),
    mcTruthCollection = cms.InputTag("genParticles"),
    readAOD = cms.bool(False),
    outputFile = cms.string("ShashlikAnalyzer.root"),
    MaxPt = cms.double(100.0),
    DeltaR = cms.double(0.05),
    MatchingID = cms.vint32(11,-11),
    MatchingMotherID = cms.vint32(23,24,-24,32),
    MaxAbsEta = cms.double(4.0),
    HistosConfigurationMC = cms.PSet(
        mcAnalyzerStdBiningParameters
        #mcAnalyzerFineBiningParameters
    )
)
