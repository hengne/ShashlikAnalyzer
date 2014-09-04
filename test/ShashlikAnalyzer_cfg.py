
import httplib, urllib, urllib2, types, string, os, sys
import FWCore.ParameterSet.Config as cms

process = cms.Process("shashlik")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt35Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/1E4EBCA3-5C2D-E411-AAFF-0025905A60E4.root',
       'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt35Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/6226BAA7-5C2D-E411-87C9-0025905B85AA.root'
    )
)

process.load("ShashlikAnalyzer.ShashlikAnalyzer.ShashlikAnalyzer_cfi")
process.ShashlikAna.outputFile = cms.string("ShashlikAnalyzer_RelValSingleElectronPt35Extended_DES23_62_V1_UPG2023SHNoTaper-v1.root")


process.p = cms.Path(process.ShashlikAna)
