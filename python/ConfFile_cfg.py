import FWCore.ParameterSet.Config as cms

process = cms.Process("ShashlikAna")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #    'file:myfile.root'
       'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt35Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/1E4EBCA3-5C2D-E411-AAFF-0025905A60E4.root'
    )
)

process.ShashlikAna = cms.EDAnalyzer('ShashlikAnalyzer'
    electronCollection = cms.InputTag("gsfElectrons"),
    mcTruthCollection = cms.InputTag("genParticles"),
    readAOD = cms.bool(False),
    outputFile = cms.string(data_sample+".GsfElectronMCAnalyzer.root"),
    MaxPt = cms.double(100.0),
    DeltaR = cms.double(0.05),
    MatchingID = cms.vint32(11,-11),
    MatchingMotherID = cms.vint32(23,24,-24,32),
    MaxAbsEta = cms.double(2.5),
    HistosConfigurationMC = cms.PSet(
        mcAnalyzerStdBiningParameters
        #mcAnalyzerFineBiningParameters
    )
)


process.p = cms.Path(process.ShashlikAna)
