
import httplib, urllib, urllib2, types, string, os, sys
import FWCore.ParameterSet.Config as cms

process = cms.Process("shashlik")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

    # Single Electrons Pt=35GeV
    #   'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt35Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/1E4EBCA3-5C2D-E411-AAFF-0025905A60E4.root',
    #   'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt35Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/6226BAA7-5C2D-E411-87C9-0025905B85AA.root',

    # Single Elecrons Pt=10GeV
    #   'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt10Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/A2A2E5C4-522D-E411-8702-002618943896.root',
    #   'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValSingleElectronPt10Extended/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/D4D7E7C4-522D-E411-8639-002618943896.root'

    # Zee PU0
    #    'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/7466ABF1-652D-E411-A9CA-0025905964A6.root',
    #    'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/92D93EF3-672D-E411-BBBB-002618943900.root',
    #    'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/98FA28CD-592D-E411-BD10-0025905AA9CC.root',
    #    'root://eoscms//store/relval/CMSSW_6_2_0_SLHC17/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/DC872C06-652D-E411-AC65-00248C0BE005.root'
    # Zee PU0 Multifit
    #     'root://eoscms//store/relval/CMSSW_6_2_0_SLHC20/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/66388A2E-2B60-E411-9C5A-002590596486.root',
    #     'root://eoscms//store/relval/CMSSW_6_2_0_SLHC20/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/72AB19C1-BC5F-E411-AB71-0025905A607E.root',
    #     'root://eoscms//store/relval/CMSSW_6_2_0_SLHC20/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/9C4F5EC1-2B60-E411-9013-003048FF9AC6.root',
    #     'root://eoscms//store/relval/CMSSW_6_2_0_SLHC20/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/A8739D85-C15F-E411-AA62-00261894396D.root',
    #     'root://eoscms//store/relval/CMSSW_6_2_0_SLHC20/RelValZEE_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/DC8C127C-2B60-E411-B10A-0025905B855E.root'
    
    # Zee PU140
#    'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/002CD53C-57A7-E411-BB32-002618943901.root',
#    'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/006867B6-D8A6-E411-A8CD-0025905A6070.root',
#'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/009271E3-EAA6-E411-A58E-0025905A6132.root',
#'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/0094D1BB-00A7-E411-8121-0025905A60F2.root',
#'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/00B57B03-07A7-E411-98CB-00261894385D.root',
#'root://cms-xrd-global.cern.ch//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/00BEFD4D-E1A6-E411-AEBA-0025905B8596.root', 
    
    # Zee PU140 Phase1
'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/F63465C0-D6AB-E411-AEB4-003048FFD740.root',
'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/F6A2B2E4-F6AB-E411-AA14-0025905A48EC.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/F6D5FBC6-29AC-E411-B2B8-0025905A611E.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/F8BD422A-E1AB-E411-B38B-00248C55CC3C.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/FA55F7D8-15AC-E411-85A7-002590596484.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/FC8440E0-F3AB-E411-A3A1-0025905B85EE.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/FC945B0E-FFAB-E411-8B85-002618943925.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/FE4023C6-E0AB-E411-87AF-0025905B8592.root',
#'root://cms-xrd-global.cern.ch//store/mc/GEM2019Upg14DR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kJan23_PU140BX25_PH1_1K_FB_V3-v1/40000/FE4BC415-EAAB-E411-AEED-0025905A48FC.root',
    )
)

process.load("ShashlikAnalyzer.ShashlikAnalyzer.ShashlikTupleDumper_cfi")
process.ShashlikAna.outputFile = cms.string(
#"ShashlikTupleDumper_RelValSingleElectronPt35Extended_DES23_62_V1_UPG2023SHNoTaper-v1.root"
# "ShashlikTupleDumper_RelValZEE_14TeV_GEN-SIM-RECO_DES23_62_V1_UPG2023SHNoTaper-v1.root"
 "output.root"
)

#process.ShashlikAna.printMCtable = cms.bool(True)


process.p = cms.Path(process.ShashlikAna)
