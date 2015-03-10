// -*- C++ -*-
//
// Package:    ShashlikAnalyzer/ShashlikAnalyzer
// Class:      ShashlikTupleDumper
//
/**\class ShashlikTupleDumper ShashlikTupleDumper.cc ShashlikAnalyzer/ShashlikAnalyzer/plugins/ShashlikTupleDumper.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hengne Li
//         Created:  Wed, 03 Sep 2014 10:41:20 GMT
// $Id$
//
//


// user include files
#include "ShashlikAnalyzer/ShashlikAnalyzer/plugins/ShashlikTupleDumper.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalSeverityLevel.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "Geometry/CaloTopology/interface/CaloTowerTopology.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/Records/interface/CaloTopologyRecord.h"
#include "Math/Vector3D.h"
#include "Math/VectorUtil.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgoRcd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "CommonTools/Utils/interface/StringToEnumValue.h"
#include "RecoEgamma/EgammaElectronAlgos/interface/ElectronUtilities.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

//#include "CLHEP/Units/GlobalPhysicalConstants.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TVector2.h"
#include "TF1.h"


DEFINE_FWK_MODULE(ShashlikTupleDumper);


ShashlikTupleDumper::ShashlikTupleDumper(const edm::ParameterSet& conf)
 {
  outputFile_ = conf.getParameter<std::string>("outputFile");
  histfile_ = new TFile(outputFile_.c_str(),"RECREATE");
  treeType_ = conf.getParameter<std::string>("treeType");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  superClusterEB_ = conf.getParameter<edm::InputTag>("superClusterEB");
  superClusterEE_ = conf.getParameter<edm::InputTag>("superClusterEE");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");
  barrelRecHitCollection_ = conf.getParameter<edm::InputTag>("barrelRecHitCollection");
  endcapRecHitCollection_ = conf.getParameter<edm::InputTag>("endcapRecHitCollection");
  hcalPFClusterCollection_ = conf.getParameter<edm::InputTag>("hcalPFClusterCollection");
  hcalPFRecHitCollection_ = conf.getParameter<edm::InputTag>("hcalPFRecHitCollection");
  deltaR_ = conf.getParameter<double>("DeltaR");
  matchingMotherIDs_ = conf.getParameter<std::vector<int> >("MatchingMotherID");
  printMCtable_ = conf.getParameter<bool>("printMCtable");

  // helpers
  ElectronHcalHelper::Configuration hcalCfgBarrel ;
  hcalCfgBarrel.hOverEConeSize = 0.15; //conf_.getParameter<double>("hOverEConeSize") ;
  hcalCfgBarrel.hOverEMethod = 0; // conf_.getParameter<int>("hOverEMethodBarrel") ;
  hcalCfgBarrel.useTowers = true ;
  hcalCfgBarrel.hcalTowers = conf.getParameter<edm::InputTag>("hcalTowers") ;
  hcalCfgBarrel.hcalClusters = hcalPFClusterCollection_; //conf_.getParameter<edm::InputTag>("endcapHCALClusters") ;
  hcalCfgBarrel.hOverEPtMin = 0;// conf_.getParameter<double>("hOverEPtMin") ;
  hcalHelperBarrel_ = new ElectronHcalHelper(hcalCfgBarrel) ;

  ElectronHcalHelper::Configuration hcalCfgEndcap ;
  hcalCfgEndcap.hOverEConeSize = 0.15; // conf_.getParameter<double>("hOverEConeSize") ;
  hcalCfgEndcap.hOverEMethod = 0; //conf_.getParameter<int>("hOverEMethodEndcap") ;
  hcalCfgEndcap.useTowers = true ;
  hcalCfgEndcap.hcalTowers = conf.getParameter<edm::InputTag>("hcalTowers") ;
  hcalCfgEndcap.hcalClusters = hcalPFClusterCollection_; //conf_.getParameter<edm::InputTag>("endcapHCALClusters") ;
  hcalCfgEndcap.hOverEPtMin = 0; // conf_.getParameter<double>("hOverEPtMin") ;
  hcalHelperEndcap_ = new ElectronHcalHelper(hcalCfgEndcap) ;

  const std::vector<std::string> flagnamesbarrel = conf.getParameter<std::vector<std::string> >("recHitFlagsToBeExcludedBarrel");
  recHitFlagsToBeExcludedBarrel_ = StringToEnumValue<EcalRecHit::Flags>(flagnamesbarrel);
  const std::vector<std::string> flagnamesendcaps = conf.getParameter<std::vector<std::string> >("recHitFlagsToBeExcludedEndcaps");
  recHitFlagsToBeExcludedEndcaps_ = StringToEnumValue<EcalRecHit::Flags>(flagnamesendcaps);
  const std::vector<std::string> severitynamesbarrel = conf.getParameter<std::vector<std::string> >("recHitSeverityToBeExcludedBarrel");
  recHitSeverityToBeExcludedBarrel_ = StringToEnumValue<EcalSeverityLevel::SeverityLevel>(severitynamesbarrel);
  const std::vector<std::string> severitynamesendcaps = conf.getParameter<std::vector<std::string> >("recHitSeverityToBeExcludedEndcaps");
  recHitSeverityToBeExcludedEndcaps_ = StringToEnumValue<EcalSeverityLevel::SeverityLevel>(severitynamesendcaps);

 }

void 
ShashlikTupleDumper::beginJob()
{
  histfile_->cd();
  if (treeType_=="Ztree"){
    bookTree();
  }
  else if (treeType_=="QCDtree"){
    bookQCDTree();
  }
  else if (treeType_=="QCDScOnlytree"){
    bookQCDScOnlyTree();
  }
  else {
    throw cms::Exception("ShashlikTupleDumper") << "ShashlikTupleDumper::unknown treeType " << treeType_ << "." << std::endl; 
  }

  // initialize correction functions

  // corr deltaEtaScAtVtx
  char func[10000];
  sprintf(func,"gaus(0)");
  for (int i=1;i<20; i++){
    sprintf(func, "%s+gaus(%d)", func, i*3);
  }
  func_corrDeltaEtaScVtx = new TF1("func_corrDeltaEtaScVtx", func, 1.47, 3.0);  
  double params[] = {0.00801413,1.508,0.0242909,0.023352,1.584,0.106734,0.0028098,1.66,0.0317669,0.0089099,1.736,0.0390202,0.0067355,1.812,0.0348707,0.00602966,1.888,0.0390016,0.00299287,1.964,0.0307741,0.0360896,2.04,0.250584,0.0403011,2.116,0.310596,-0.0403029,2.192,0.187177,0.0496289,2.268,0.217546,0.0214814,2.344,0.261552,0.0202145,2.42,0.207958,0.0160461,2.496,0.30491,0.030677,2.572,0.141072,-0.193856,2.648,0.199843,0.308114,2.724,0.229894,-0.181284,2.8,-0.668033,0.761307,2.876,-5.14181e-05,13.613,2.952,0.00153964};
  func_corrDeltaEtaScVtx->SetParameters(params);

}

void
ShashlikTupleDumper::bookQCDTree()
{
  histfile_->cd();
  tree = new TTree("tree", "tree");

  tree->Branch("NPV", &NPV,"NPV/I");
  tree->Branch("Nparts", &Nparts,"Nparts/I");
  tree->Branch("ESc", &ESc);
  tree->Branch("EScRaw", &EScRaw);
  tree->Branch("EtSc", &EtSc);
  tree->Branch("EtaSc", &EtaSc);
  tree->Branch("PhiSc", &PhiSc);
  tree->Branch("EScSeed", &EScSeed);
  tree->Branch("EtScSeed", &EtScSeed);
  tree->Branch("EtaScSeed", &EtaScSeed);
  tree->Branch("PhiScSeed", &PhiScSeed);
  tree->Branch("ScSeedNHits", &ScSeedNHits);
  tree->Branch("ScNCl", &ScNCl);
  tree->Branch("E", &E);
  tree->Branch("Pt", &Pt);
  tree->Branch("Px", &Px);
  tree->Branch("Py", &Py);
  tree->Branch("Pz", &Pz);
  tree->Branch("Eta", &Eta);
  tree->Branch("Phi", &Phi);
  tree->Branch("isEB", &isEB);
  tree->Branch("isEE", &isEE);
  tree->Branch("Charge", &Charge);
  tree->Branch("PDG", &PDG);
  tree->Branch("Classify", &Classify);
  tree->Branch("HoE", &HoE); // hcalOverEcal()
  tree->Branch("HoE1", &HoE1); // hcalDepth1OverEcal1()
  tree->Branch("HoE2", &HoE2); // hcalDepth1OverEcal2()
  tree->Branch("HoEpf", &HoEpf);
  tree->Branch("HoEwtE", &HoEwtE);
  tree->Branch("HoEsumE", &HoEsumE);
  tree->Branch("HoEsumE2", &HoEsumE2);
  tree->Branch("HoEsumE3", &HoEsumE3);
  tree->Branch("HoEcone", &HoEcone); 
  tree->Branch("ecalDriven", &ecalDriven); //ecalDrivenSeed() 
  tree->Branch("trackDriven", &trackDriven); //trackerDrivenSeed() 
  tree->Branch("sigmaEtaEta", &sigmaEtaEta); // sigmaEtaEta()
  tree->Branch("sigmaIetaIeta", &sigmaIetaIeta); // sigmaIetaIeta()
  tree->Branch("sigmaIphiIphi", &sigmaIphiIphi); // sigmaIphiIphi()
  tree->Branch("r9", &r9); // r9()
  tree->Branch("dEtaSCAtVtx", &dEtaSCAtVtx); // deltaEtaSuperClusterAtVtx 
  tree->Branch("dEtaSCAtCal", &dEtaSCAtCal); // deltaEtaEleClusterAtCalo
  tree->Branch("dEtaSeedAtCal", &dEtaSeedAtCal); // deltaEtaEleClusterAtCalo
  tree->Branch("dPhiSCAtVtx", &dPhiSCAtVtx); // deltaPhiSuperClusterAtVtx 
  tree->Branch("dPhiSCAtCal", &dPhiSCAtCal); // deltaPhiEleClusterAtCalo
  tree->Branch("dPhiSeedAtCal", &dPhiSeedAtCal); // deltaPhiEleClusterAtCalo
  tree->Branch("sigmaEtaEtaRec", &sigmaEtaEtaRec); // sigmaEtaEta()
  tree->Branch("sigmaIetaIetaRec", &sigmaIetaIetaRec); // sigmaIetaIeta()
  tree->Branch("sigmaIphiIphiRec", &sigmaIphiIphiRec); // sigmaIphiIphi()
  tree->Branch("dEtaSCAtVtxRec", &dEtaSCAtVtxRec); // deltaEtaSuperClusterAtVtx 
  tree->Branch("dEtaSCAtCalRec", &dEtaSCAtCalRec); // deltaEtaEleClusterAtCalo
  tree->Branch("dPhiSCAtVtxRec", &dPhiSCAtVtxRec); // deltaPhiSuperClusterAtVtx 
  tree->Branch("dPhiSCAtCalRec", &dPhiSCAtCalRec); // deltaPhiEleClusterAtCalo
  tree->Branch("dEtaSCAtVtxCorr", &dEtaSCAtVtxCorr); 
  tree->Branch("TrackVtxD0", &TrackVtxD0);
  tree->Branch("TrackVtxDz", &TrackVtxDz);
  tree->Branch("trackFbrem", &trackFbrem); // trackFbrem 
  tree->Branch("scFbrem", &scFbrem); // superClusterFbrem
  tree->Branch("PTrackOut", &PTrackOut);
  tree->Branch("PtTrackOut", &PtTrackOut);
  tree->Branch("PxTrackOut", &PxTrackOut);
  tree->Branch("PyTrackOut", &PyTrackOut);
  tree->Branch("PzTrackOut", &PzTrackOut);
  tree->Branch("EtaTrackOut", &EtaTrackOut);
  tree->Branch("PhiTrackOut", &PhiTrackOut);
  tree->Branch("PTrackIn", &PTrackIn);
  tree->Branch("PtTrackIn", &PtTrackIn);
  tree->Branch("PxTrackIn", &PxTrackIn);
  tree->Branch("PyTrackIn", &PyTrackIn);
  tree->Branch("PzTrackIn", &PzTrackIn);
  tree->Branch("EtaTrackIn", &EtaTrackIn);
  tree->Branch("PhiTrackIn", &PhiTrackIn);


}

void
ShashlikTupleDumper::bookQCDScOnlyTree()
{
  histfile_->cd();
  tree = new TTree("tree", "tree");

  tree->Branch("NPV", &NPV,"NPV/I");
  tree->Branch("Nparts", &Nparts,"Nparts/I");
  tree->Branch("isEB", &isEB);
  tree->Branch("isEE", &isEE);
  tree->Branch("ESc", &ESc);
  tree->Branch("EScRaw", &EScRaw);
  tree->Branch("EtSc", &EtSc);
  tree->Branch("EtaSc", &EtaSc);
  tree->Branch("PhiSc", &PhiSc);
  tree->Branch("EScSeed", &EScSeed);
  tree->Branch("EtScSeed", &EtScSeed);
  tree->Branch("EtaScSeed", &EtaScSeed);
  tree->Branch("PhiScSeed", &PhiScSeed);
  tree->Branch("ScSeedNHits", &ScSeedNHits);
  tree->Branch("ScNCl", &ScNCl);
  tree->Branch("HoEpf", &HoEpf);
  tree->Branch("HoEwtE", &HoEwtE);
  tree->Branch("HoEsumE", &HoEsumE);
  tree->Branch("HoEsumE2", &HoEsumE2);
  tree->Branch("HoEsumE3", &HoEsumE3);
  tree->Branch("HoEcone", &HoEcone); 

}

void 
ShashlikTupleDumper::bookTree()
{
  histfile_->cd();
  tree = new TTree("tree", "tree");

  tree->Branch("RunNum", &RunNum,"RunNum/l");
  tree->Branch("EvtNum", &EvtNum,"EvtNum/l");
  tree->Branch("LumNum", &LumNum,"LumNum/l");
  tree->Branch("NPV", &NPV,"NPV/I");
  tree->Branch("VtxXTrue", &VtxXTrue,"VtxXTrue/D");
  tree->Branch("VtxYTrue", &VtxYTrue,"VtxYTrue/D");
  tree->Branch("VtxZTrue", &VtxZTrue,"VtxZTrue/D");
  tree->Branch("VtxX", &VtxX,"VtxX/D");
  tree->Branch("VtxY", &VtxY,"VtxY/D");
  tree->Branch("VtxZ", &VtxZ,"VtxZ/D");
  tree->Branch("Nparts", &Nparts,"Nparts/I");
  tree->Branch("Nelecs", &Nelecs,"Nelecs/I");
  tree->Branch("Nphots", &Nphots,"Nphots/I"); 
  tree->Branch("ETrue", &ETrue);
  tree->Branch("PtTrue", &PtTrue);
  tree->Branch("PxTrue", &PxTrue);
  tree->Branch("PyTrue", &PyTrue);
  tree->Branch("PzTrue", &PzTrue);
  tree->Branch("EtaTrue", &EtaTrue);
  tree->Branch("PhiTrue", &PhiTrue);
  tree->Branch("ChargeTrue", &ChargeTrue);
  tree->Branch("PDGTrue", &PDGTrue);
  tree->Branch("MomPDGTrue", &MomPDGTrue);
  tree->Branch("FoundGsf", &FoundGsf);
  tree->Branch("FoundSc", &FoundSc);
  tree->Branch("DeltaRGsf", &DeltaRGsf);
  tree->Branch("DeltaRSc", &DeltaRSc);
  tree->Branch("ESc", &ESc);
  tree->Branch("EScRaw", &EScRaw);
  tree->Branch("EtSc", &EtSc);
  tree->Branch("EtaSc", &EtaSc);
  tree->Branch("PhiSc", &PhiSc);
  tree->Branch("EScSeed", &EScSeed);
  tree->Branch("EtScSeed", &EtScSeed);
  tree->Branch("EtaScSeed", &EtaScSeed);
  tree->Branch("PhiScSeed", &PhiScSeed);
  tree->Branch("ScSeedNHits", &ScSeedNHits);
  tree->Branch("ScSeedHitFrac", &ScSeedHitFrac);
  tree->Branch("ScSeedHitE", &ScSeedHitE);
  tree->Branch("ScNCl", &ScNCl);
  tree->Branch("ScClNHits", &ScClNHits);
  tree->Branch("ScClE", &ScClE);
  tree->Branch("ScClEta", &ScClEta);
  tree->Branch("ScClPhi", &ScClPhi);
  tree->Branch("ScClHitFrac", &ScClHitFrac);
  tree->Branch("ScClHitE", &ScClHitE);
  tree->Branch("E", &E);
  tree->Branch("Pt", &Pt);
  tree->Branch("Px", &Px);
  tree->Branch("Py", &Py);
  tree->Branch("Pz", &Pz);
  tree->Branch("Eta", &Eta);
  tree->Branch("Phi", &Phi);
  tree->Branch("isEB", &isEB);
  tree->Branch("isEE", &isEE);
  tree->Branch("Charge", &Charge);
  tree->Branch("PDG", &PDG);
  tree->Branch("Classify", &Classify);
  tree->Branch("HoE", &HoE); // hcalOverEcal()
  tree->Branch("HoE1", &HoE1); // hcalDepth1OverEcal1()
  tree->Branch("HoE2", &HoE2); // hcalDepth1OverEcal2()
  tree->Branch("HoEpf", &HoEpf);
  tree->Branch("HoEwtE", &HoEwtE);
  tree->Branch("HoEsumE", &HoEsumE);
  tree->Branch("HoEsumE2", &HoEsumE2);
  tree->Branch("HoEsumE3", &HoEsumE3);
  tree->Branch("HoEcone", &HoEcone); 
  tree->Branch("ecalDriven", &ecalDriven); //ecalDrivenSeed() 
  tree->Branch("trackDriven", &trackDriven); //trackerDrivenSeed() 
  tree->Branch("sigmaEtaEta", &sigmaEtaEta); // sigmaEtaEta()
  tree->Branch("sigmaIetaIeta", &sigmaIetaIeta); // sigmaIetaIeta()
  tree->Branch("sigmaIphiIphi", &sigmaIphiIphi); // sigmaIphiIphi()
  tree->Branch("r9", &r9); // r9()
  tree->Branch("dEtaSCAtVtx", &dEtaSCAtVtx); // deltaEtaSuperClusterAtVtx 
  tree->Branch("dEtaSCAtCal", &dEtaSCAtCal); // deltaEtaEleClusterAtCalo
  tree->Branch("dEtaSeedAtCal", &dEtaSeedAtCal); // deltaEtaEleClusterAtCalo
  tree->Branch("dPhiSCAtVtx", &dPhiSCAtVtx); // deltaPhiSuperClusterAtVtx 
  tree->Branch("dPhiSCAtCal", &dPhiSCAtCal); // deltaPhiEleClusterAtCalo
  tree->Branch("dPhiSeedAtCal", &dPhiSeedAtCal); // deltaPhiEleClusterAtCalo
  tree->Branch("sigmaEtaEtaRec", &sigmaEtaEtaRec); // sigmaEtaEta()
  tree->Branch("sigmaIetaIetaRec", &sigmaIetaIetaRec); // sigmaIetaIeta()
  tree->Branch("sigmaIphiIphiRec", &sigmaIphiIphiRec); // sigmaIphiIphi()
  tree->Branch("dEtaSCAtVtxRec", &dEtaSCAtVtxRec); // deltaEtaSuperClusterAtVtx 
  tree->Branch("dEtaSCAtCalRec", &dEtaSCAtCalRec); // deltaEtaEleClusterAtCalo
  tree->Branch("dPhiSCAtVtxRec", &dPhiSCAtVtxRec); // deltaPhiSuperClusterAtVtx 
  tree->Branch("dPhiSCAtCalRec", &dPhiSCAtCalRec); // deltaPhiEleClusterAtCalo
  tree->Branch("dEtaSCAtVtxCorr", &dEtaSCAtVtxCorr); 
  tree->Branch("TrackVtxD0", &TrackVtxD0);
  tree->Branch("TrackVtxDz", &TrackVtxDz);
  tree->Branch("trackFbrem", &trackFbrem); // trackFbrem 
  tree->Branch("scFbrem", &scFbrem); // superClusterFbrem
  tree->Branch("PTrackOut", &PTrackOut);
  tree->Branch("PtTrackOut", &PtTrackOut);
  tree->Branch("PxTrackOut", &PxTrackOut);
  tree->Branch("PyTrackOut", &PyTrackOut);
  tree->Branch("PzTrackOut", &PzTrackOut);
  tree->Branch("EtaTrackOut", &EtaTrackOut);
  tree->Branch("PhiTrackOut", &PhiTrackOut);
  tree->Branch("PTrackIn", &PTrackIn);
  tree->Branch("PtTrackIn", &PtTrackIn);
  tree->Branch("PxTrackIn", &PxTrackIn);
  tree->Branch("PyTrackIn", &PyTrackIn);
  tree->Branch("PzTrackIn", &PzTrackIn);
  tree->Branch("EtaTrackIn", &EtaTrackIn);
  tree->Branch("PhiTrackIn", &PhiTrackIn);


}

void
ShashlikTupleDumper::clearQCDScOnlyTreeBranchVectors()
{
  isEB.clear();
  isEE.clear();  
  ESc.clear();
  EScRaw.clear();
  EtSc.clear();
  EtaSc.clear();
  PhiSc.clear();
  EScSeed.clear();
  EtScSeed.clear();
  EtaScSeed.clear();
  PhiScSeed.clear();
  ScNCl.clear();
  HoEpf.clear();
  HoEsumE.clear();
  HoEsumE2.clear();
  HoEsumE3.clear();
  HoEwtE.clear();
  HoEcone.clear();

}

void
ShashlikTupleDumper::clearQCDTreeBranchVectors()
{
  isEB.clear();
  isEE.clear();
  ESc.clear();
  EScRaw.clear();
  EtSc.clear();
  EtaSc.clear();
  PhiSc.clear();
  EScSeed.clear();
  EtScSeed.clear();
  EtaScSeed.clear();
  PhiScSeed.clear();
  ScSeedNHits.clear();
  ScNCl.clear();
  E.clear();
  Pt.clear();
  Px.clear();
  Py.clear();
  Pz.clear();
  Eta.clear();
  Phi.clear();
  isEB.clear();
  isEE.clear();
  Charge.clear();
  PDG.clear();
  Classify.clear();
  HoE.clear();
  HoE1.clear();
  HoE2.clear();
  HoEpf.clear();
  HoEsumE.clear();
  HoEsumE2.clear();
  HoEsumE3.clear();
  HoEwtE.clear();
  HoEcone.clear();
  ecalDriven.clear();
  trackDriven.clear();
  sigmaEtaEta.clear();
  sigmaIetaIeta.clear();
  sigmaIphiIphi.clear();
  r9.clear();
  dEtaSCAtVtx.clear();
  dEtaSCAtCal.clear();
  dEtaSeedAtCal.clear();
  dPhiSCAtVtx.clear();
  dPhiSCAtCal.clear();
  dPhiSeedAtCal.clear();
  sigmaEtaEtaRec.clear();
  sigmaIetaIetaRec.clear();
  sigmaIphiIphiRec.clear();
  dEtaSCAtVtxRec.clear();
  dEtaSCAtCalRec.clear();
  dPhiSCAtVtxRec.clear();
  dPhiSCAtCalRec.clear();
  dEtaSCAtVtxCorr.clear();
  TrackVtxD0.clear();
  TrackVtxDz.clear();
  trackFbrem.clear();
  scFbrem.clear();
  PTrackOut.clear();
  PtTrackOut.clear();
  PxTrackOut.clear();
  PyTrackOut.clear();
  PzTrackOut.clear();
  EtaTrackOut.clear();
  PhiTrackOut.clear();
  PTrackIn.clear();
  PtTrackIn.clear();
  PxTrackIn.clear();
  PyTrackIn.clear();
  PzTrackIn.clear();
  EtaTrackIn.clear();
  PhiTrackIn.clear();


}


void
ShashlikTupleDumper::clearTreeBranchVectors()
{
  ETrue.clear();
  PtTrue.clear();
  PxTrue.clear();
  PyTrue.clear();
  PzTrue.clear();
  EtaTrue.clear();
  PhiTrue.clear();
  ChargeTrue.clear();
  PDGTrue.clear();
  MomPDGTrue.clear();
  FoundGsf.clear();
  FoundSc.clear();
  DeltaRGsf.clear();
  DeltaRSc.clear();
  ESc.clear();
  EScRaw.clear();
  EtSc.clear();
  EtaSc.clear();
  PhiSc.clear();
  EScSeed.clear();
  EtScSeed.clear();
  EtaScSeed.clear();
  PhiScSeed.clear();
  ScSeedNHits.clear();
  ScSeedHitFrac.clear();
  ScSeedHitE.clear();
  ScNCl.clear();
  ScClNHits.clear();
  ScClE.clear();
  ScClEta.clear();
  ScClPhi.clear();
  ScClHitFrac.clear();
  ScClHitE.clear();
  E.clear();
  Pt.clear();
  Px.clear();
  Py.clear();
  Pz.clear();
  Eta.clear();
  Phi.clear();
  isEB.clear();
  isEE.clear();
  Charge.clear();
  PDG.clear();
  Classify.clear();
  HoE.clear();
  HoE1.clear();
  HoE2.clear();
  HoEpf.clear();
  HoEsumE.clear();
  HoEsumE2.clear();
  HoEsumE3.clear();
  HoEwtE.clear();
  HoEcone.clear();
  ecalDriven.clear();
  trackDriven.clear();
  sigmaEtaEta.clear();
  sigmaIetaIeta.clear();
  sigmaIphiIphi.clear();
  r9.clear();
  dEtaSCAtVtx.clear();
  dEtaSCAtCal.clear();
  dEtaSeedAtCal.clear();
  dPhiSCAtVtx.clear();
  dPhiSCAtCal.clear();
  dPhiSeedAtCal.clear();
  sigmaEtaEtaRec.clear();
  sigmaIetaIetaRec.clear();
  sigmaIphiIphiRec.clear();
  dEtaSCAtVtxRec.clear();
  dEtaSCAtCalRec.clear();
  dPhiSCAtVtxRec.clear();
  dPhiSCAtCalRec.clear();
  dEtaSCAtVtxCorr.clear();
  TrackVtxD0.clear();
  TrackVtxDz.clear();
  trackFbrem.clear();
  scFbrem.clear();
  PTrackOut.clear();
  PtTrackOut.clear();
  PxTrackOut.clear();
  PyTrackOut.clear();
  PzTrackOut.clear();
  EtaTrackOut.clear();
  PhiTrackOut.clear();
  PTrackIn.clear();
  PtTrackIn.clear();
  PxTrackIn.clear();
  PyTrackIn.clear();
  PzTrackIn.clear();
  EtaTrackIn.clear();
  PhiTrackIn.clear();

}


void 
ShashlikTupleDumper::endJob()
{

  histfile_->cd();
  tree->Write();

}

ShashlikTupleDumper::~ShashlikTupleDumper()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  histfile_->Write();
  histfile_->Close();

}


//=========================================================================
// Main method
//=========================================================================

void
ShashlikTupleDumper::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if (treeType_=="Ztree"){
    FillTree(iEvent,iSetup);
  }
  else if (treeType_=="QCDtree"){
    FillQCDTree(iEvent,iSetup);
  }
  else if (treeType_=="QCDScOnlytree"){
    FillQCDScOnlyTree(iEvent,iSetup);
  }  
  else {
    throw cms::Exception("ShashlikTupleDumper") << "ShashlikTupleDumper::unknown treeType " << treeType_ << "." << std::endl;
  }
}


void
ShashlikTupleDumper::FillQCDTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::Handle<reco::GsfElectronCollection> gsfElectrons;
  iEvent.getByLabel(electronCollection_,gsfElectrons);

  edm::Handle<reco::SuperClusterCollection> superClustersEB;
  iEvent.getByLabel(superClusterEB_,superClustersEB);

  edm::Handle<reco::SuperClusterCollection> superClustersEE;
  iEvent.getByLabel(superClusterEE_,superClustersEE);

  edm::Handle<EcalRecHitCollection> barrelRecHits ;
  iEvent.getByLabel(barrelRecHitCollection_,barrelRecHits);

  edm::Handle<EcalRecHitCollection> endcapRecHits ;
  iEvent.getByLabel(endcapRecHitCollection_,endcapRecHits);

  edm::Handle<reco::PFClusterCollection> hcalPFClusters;
  iEvent.getByLabel(hcalPFClusterCollection_,hcalPFClusters);

  edm::Handle<reco::PFRecHitCollection> hcalPFRecHits;
  iEvent.getByLabel(hcalPFRecHitCollection_,hcalPFRecHits);

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;
  NPV = -1;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI)
  {
    int BX = PVI->getBunchCrossing();
    if(BX == 0)
    {
      NPV = PVI->getPU_NumInteractions();
      continue;
    }
  }

  edm::ESHandle<CaloTowerConstituentsMap> ctmap;
  iSetup.get<CaloGeometryRecord>().get(ctmap);
  theTowerConstituentsMap_ = ctmap.product();

  hcalHelperBarrel_->checkSetup(iSetup) ;
  hcalHelperBarrel_->readEvent(iEvent) ;
  hcalHelperEndcap_->checkSetup(iSetup) ;
  hcalHelperEndcap_->readEvent(iEvent) ;

  edm::ESHandle<CaloGeometry> caloGeom ;
  edm::ESHandle<CaloTopology> caloTopo ;
  iSetup.get<CaloGeometryRecord>().get(caloGeom);
  iSetup.get<CaloTopologyRecord>().get(caloTopo);

  edm::ESHandle<EcalSeverityLevelAlgo> sevLevel;
  iSetup.get<EcalSeverityLevelAlgoRcd>().get(sevLevel);

  // get the beamspot from the Event:
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle ;
  iEvent.getByLabel(edm::InputTag("offlineBeamSpot"),recoBeamSpotHandle) ;
  beamspot_ = recoBeamSpotHandle.product() ;

  edm::ESHandle<TrackerGeometry> trackerHandle ;
  iSetup.get<TrackerDigiGeometryRecord>().get(trackerHandle);

  edm::ESHandle<MagneticField> magField ;
  iSetup.get<IdealMagneticFieldRecord>().get(magField);


  // clear tree brach vectors
  clearQCDTreeBranchVectors();

  Nparts=0;

  // loopover all gsfElectrons
  for (reco::GsfElectronCollection::const_iterator gsfIter=gsfElectrons->begin();
       gsfIter!=gsfElectrons->end(); gsfIter++)
  {
    if (gsfIter->pt()<10) continue;
    Nparts++;
    // gsfElectron info
    E.push_back(gsfIter->energy());
    Pt.push_back(gsfIter->pt());
    Px.push_back(gsfIter->px());
    Py.push_back(gsfIter->py());
    Pz.push_back(gsfIter->pz());
    Eta.push_back(gsfIter->eta());
    Phi.push_back(gsfIter->phi());
    isEB.push_back(gsfIter->isEB());
    isEE.push_back(gsfIter->isEE());
    Charge.push_back((double)gsfIter->charge());
    PDG.push_back(gsfIter->pdgId());
    Classify.push_back(gsfIter->classification());
    HoE.push_back(gsfIter->hcalOverEcal());
    HoE1.push_back(gsfIter->hcalDepth1OverEcal());
    HoE2.push_back(gsfIter->hcalDepth2OverEcal());
    ecalDriven.push_back(gsfIter->ecalDrivenSeed());
    trackDriven.push_back(gsfIter->trackerDrivenSeed());
    sigmaEtaEta.push_back(gsfIter->sigmaEtaEta());
    sigmaIetaIeta.push_back(gsfIter->sigmaIetaIeta());
    sigmaIphiIphi.push_back(gsfIter->sigmaIphiIphi());
    r9.push_back(gsfIter->r9());
    dEtaSCAtVtx.push_back(gsfIter->deltaEtaSuperClusterTrackAtVtx());
    dEtaSCAtCal.push_back(gsfIter->deltaEtaEleClusterTrackAtCalo());
    dEtaSeedAtCal.push_back(gsfIter->deltaEtaSeedClusterTrackAtCalo());
    dPhiSCAtVtx.push_back(gsfIter->deltaPhiSuperClusterTrackAtVtx());
    dPhiSCAtCal.push_back(gsfIter->deltaPhiEleClusterTrackAtCalo());
    dPhiSeedAtCal.push_back(gsfIter->deltaPhiSeedClusterTrackAtCalo());
    TrackVtxD0.push_back(gsfIter->gsfTrack()->dxy());
    TrackVtxDz.push_back(gsfIter->gsfTrack()->dz());
    trackFbrem.push_back(gsfIter->trackFbrem());
    scFbrem.push_back(gsfIter->superClusterFbrem());

    // superCluster
    reco::SuperClusterRef superCluster = gsfIter->superCluster();

    // now fill the gsf electron info
    ESc.push_back(superCluster->energy());
    EScRaw.push_back(superCluster->rawEnergy());
    EtSc.push_back(superCluster->energy()/cosh(superCluster->eta()));
    EtaSc.push_back(superCluster->eta());
    PhiSc.push_back(superCluster->phi());

    // seed
    reco::CaloClusterPtr seedCluster = superCluster->seed();
    EScSeed.push_back(seedCluster->energy());
    EtScSeed.push_back(seedCluster->energy()/cosh(seedCluster->eta()));
    EtaScSeed.push_back(seedCluster->eta());
    PhiScSeed.push_back(seedCluster->phi());

    // HoE
    HoEpf.push_back(getHCALClusterEnergy(*superCluster, hcalPFClusters.product(), 0, 0.15)/superCluster->energy());

    // Hcone
    double Hcone1(0);
    double Hcone2(0);
    if (gsfIter->isEB()){ 
      Hcone1 = hcalHelperBarrel_->hcalESumDepth1(*superCluster);
      Hcone2 = hcalHelperBarrel_->hcalESumDepth2(*superCluster);
    } else {
      Hcone1 = hcalHelperEndcap_->hcalESumDepth1(*superCluster);
      Hcone2 = hcalHelperEndcap_->hcalESumDepth2(*superCluster);
    }
    HoEcone.push_back((Hcone1+Hcone2)/superCluster->energy());

    // nearest rechit
    const reco::PFRecHit* nearestHit = getNearestHCALPFRecHit(*superCluster, hcalPFRecHits.product());
    //std::cout << "nearestHit:: " ;
    bool validHit = isValidHCALPFRecHit(*superCluster,nearestHit);
    if (validHit) {
      //std::cout << "Hhit/E=" << nearestHit->energy()/superCluster->energy() << std::endl;
      // HsumE
      double HsumE = getHcalsumE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE/E=" << HsumE/superCluster->energy() << std::endl;
      // HsumE2
      double HsumE2 = getHcalsumE2(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE2/E=" << HsumE2/superCluster->energy() << std::endl;
      // HsumE3
      double HsumE3 = getHcalsumE3(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE3/E=" << HsumE3/superCluster->energy() << std::endl;
      // HwtE
      double HwtE = getHcalwtE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HwtE/E=" << HwtE/superCluster->energy() << std::endl;
      HoEsumE.push_back( HsumE/superCluster->energy());
      HoEsumE2.push_back( HsumE2/superCluster->energy());
      HoEsumE3.push_back( HsumE3/superCluster->energy());
      HoEwtE.push_back( HwtE/superCluster->energy());
    }


    // recalculate eid variables

    const CaloTopology * topology = caloTopo.product() ;
    const CaloGeometry * geometry = caloGeom.product() ;
    const EcalRecHitCollection * recHits = 0 ;
    std::vector<int> recHitFlagsToBeExcluded ;
    std::vector<int> recHitSeverityToBeExcluded ;
    const EcalSeverityLevelAlgo * severityLevelAlgo = sevLevel.product() ;
    if (gsfIter->isEB())
    {
      recHits = barrelRecHits.product() ;
      recHitFlagsToBeExcluded = recHitFlagsToBeExcludedBarrel_ ;
      recHitSeverityToBeExcluded = recHitSeverityToBeExcludedBarrel_ ;
    }
    else
    {
      recHits = endcapRecHits.product() ;
      recHitFlagsToBeExcluded = recHitFlagsToBeExcludedEndcaps_ ;
      recHitSeverityToBeExcluded = recHitSeverityToBeExcludedEndcaps_ ;
    }

    std::vector<float> covariances = EcalClusterTools::covariances(*seedCluster,recHits,topology,geometry,recHitFlagsToBeExcluded,recHitSeverityToBeExcluded,severityLevelAlgo) ;
    std::vector<float> localCovariances = EcalClusterTools::localCovariances(*seedCluster,recHits,topology,recHitFlagsToBeExcluded,recHitSeverityToBeExcluded,severityLevelAlgo) ;

    sigmaEtaEtaRec.push_back(sqrt(covariances[0]));
    sigmaIetaIetaRec.push_back(sqrt(localCovariances[0]));
    sigmaIphiIphiRec.push_back(sqrt(localCovariances[2]));

    dEtaSCAtVtxRec.push_back(gsfIter->deltaEtaSuperClusterTrackAtVtx());
    dEtaSCAtCalRec.push_back(gsfIter->deltaEtaEleClusterTrackAtCalo());
    dPhiSCAtVtxRec.push_back(gsfIter->deltaPhiSuperClusterTrackAtVtx());
    dPhiSCAtCalRec.push_back(gsfIter->deltaPhiEleClusterTrackAtCalo());

    // simple correction of the 
    float corrDeltaEtaScVtx(0);
    if (fabs(gsfIter->eta())>1.47&&fabs(gsfIter->eta())<3.0) {
      corrDeltaEtaScVtx = (float)func_corrDeltaEtaScVtx->Eval(fabs(gsfIter->eta()));
      if (gsfIter->eta()<0) corrDeltaEtaScVtx = -corrDeltaEtaScVtx;
    }
    dEtaSCAtVtxCorr.push_back(gsfIter->deltaEtaSuperClusterTrackAtVtx()-corrDeltaEtaScVtx);

    // track
    reco::GsfTrackRef gsfTrack = gsfIter->gsfTrack();
    if (!gsfTrack)
    {
      PTrackOut.push_back(-100);
      PtTrackOut.push_back(-100);
      PxTrackOut.push_back(-100);
      PyTrackOut.push_back(-100);
      PzTrackOut.push_back(-100);
      EtaTrackOut.push_back(-100);
      PhiTrackOut.push_back(-100);
      PTrackIn.push_back(-100);
      PtTrackIn.push_back(-100);
      PxTrackIn.push_back(-100);
      PyTrackIn.push_back(-100);
      PzTrackIn.push_back(-100);
      EtaTrackIn.push_back(-100);
      PhiTrackIn.push_back(-100);
      continue;
    }


    PTrackOut.push_back(gsfTrack->outerMomentum().R());
    PtTrackOut.push_back(gsfTrack->outerMomentum().Rho());
    PxTrackOut.push_back(gsfTrack->outerMomentum().X());
    PyTrackOut.push_back(gsfTrack->outerMomentum().Y());
    PzTrackOut.push_back(gsfTrack->outerMomentum().Z());
    EtaTrackOut.push_back(gsfTrack->outerMomentum().eta());
    PhiTrackOut.push_back(gsfTrack->outerMomentum().phi());
    PTrackIn.push_back(gsfTrack->innerMomentum().R());
    PtTrackIn.push_back(gsfTrack->innerMomentum().Rho());
    PxTrackIn.push_back(gsfTrack->innerMomentum().X());
    PyTrackIn.push_back(gsfTrack->innerMomentum().Y());
    PzTrackIn.push_back(gsfTrack->innerMomentum().Z());
    EtaTrackIn.push_back(gsfTrack->innerMomentum().eta());
    PhiTrackIn.push_back(gsfTrack->innerMomentum().phi());

  } // loop over gsfElectrons 

  tree->Fill();
}


void
ShashlikTupleDumper::FillQCDScOnlyTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::Handle<reco::SuperClusterCollection> superClustersEB;
  iEvent.getByLabel(superClusterEB_,superClustersEB);

  edm::Handle<reco::SuperClusterCollection> superClustersEE;
  iEvent.getByLabel(superClusterEE_,superClustersEE);

  edm::Handle<reco::PFClusterCollection> hcalPFClusters;
  iEvent.getByLabel(hcalPFClusterCollection_,hcalPFClusters);

  edm::Handle<reco::PFRecHitCollection> hcalPFRecHits;
  iEvent.getByLabel(hcalPFRecHitCollection_,hcalPFRecHits);

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;
  NPV = -1;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI)
  {
    int BX = PVI->getBunchCrossing();
    if(BX == 0)
    {
      NPV = PVI->getPU_NumInteractions();
      continue;
    }
  }

  edm::ESHandle<CaloTowerConstituentsMap> ctmap;
  iSetup.get<CaloGeometryRecord>().get(ctmap);
  theTowerConstituentsMap_ = ctmap.product();

  hcalHelperBarrel_->checkSetup(iSetup) ;
  hcalHelperBarrel_->readEvent(iEvent) ;
  hcalHelperEndcap_->checkSetup(iSetup) ;
  hcalHelperEndcap_->readEvent(iEvent) ;


  // clear tree brach vectors
  clearQCDScOnlyTreeBranchVectors();

  Nparts=0;

  // EB
  for (reco::SuperClusterCollection::const_iterator scIter=superClustersEB->begin();
       scIter!=superClustersEB->end(); scIter++)
  {
    // et cut
    double et = scIter->energy()/cosh(scIter->eta());
    if (et<=10.0) continue;
    Nparts++;
    isEB.push_back(true);
    isEE.push_back(false);
    ESc.push_back(scIter->energy());
    EScRaw.push_back(scIter->rawEnergy());
    EtSc.push_back(scIter->energy()/cosh(scIter->eta()));
    EtaSc.push_back(scIter->eta());
    PhiSc.push_back(scIter->phi());
    ScNCl.push_back((int)scIter->clustersSize());
    // seed
    reco::CaloClusterPtr seedCluster = scIter->seed();
    EScSeed.push_back(seedCluster->energy());
    EtScSeed.push_back(seedCluster->energy()/cosh(seedCluster->eta()));
    EtaScSeed.push_back(seedCluster->eta());
    PhiScSeed.push_back(seedCluster->phi());
    // HoE
    HoEpf.push_back(getHCALClusterEnergy(*scIter, hcalPFClusters.product(), 0, 0.15)/scIter->energy());
    // Hcone
    double Hcone1 = hcalHelperBarrel_->hcalESumDepth1(*scIter);
    double Hcone2 = hcalHelperBarrel_->hcalESumDepth2(*scIter);
    HoEcone.push_back((Hcone1+Hcone2)/scIter->energy());


    // nearest rechit
    const reco::PFRecHit* nearestHit = getNearestHCALPFRecHit(*scIter, hcalPFRecHits.product());
    //std::cout << "nearestHit:: " ;
    bool validHit = isValidHCALPFRecHit(*scIter,nearestHit);
    if (validHit) {
      //std::cout << "Hhit/E=" << nearestHit->energy()/scIter->energy() << std::endl;
      // HsumE
      double HsumE = getHcalsumE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE/E=" << HsumE/scIter->energy() << std::endl;
      // HsumE2
      double HsumE2 = getHcalsumE2(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE2/E=" << HsumE2/scIter->energy() << std::endl;
      // HsumE3
      double HsumE3 = getHcalsumE3(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE3/E=" << HsumE3/scIter->energy() << std::endl;
      // HwtE
      double HwtE = getHcalwtE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HwtE/E=" << HwtE/scIter->energy() << std::endl;
      // H cone 
      //double Hcone = 
      HoEsumE.push_back( HsumE/scIter->energy());
      HoEsumE2.push_back( HsumE2/scIter->energy());
      HoEsumE3.push_back( HsumE3/scIter->energy());
      HoEwtE.push_back( HwtE/scIter->energy());

    }
    else {
      //std::cout << "Not match , Hhit/E=" << nearestHit->energy()/scIter->energy() << std::endl;
      HoEsumE.push_back(0);
      HoEsumE2.push_back(0);
      HoEsumE3.push_back(0);
      HoEwtE.push_back(0);
    }

        

  } // loop over sc 

  // EE
  for (reco::SuperClusterCollection::const_iterator scIter=superClustersEE->begin();
       scIter!=superClustersEE->end(); scIter++)
  {
    // et cut
    double et = scIter->energy()/cosh(scIter->eta());
    if (et<=10.0) continue;
    Nparts++;
    isEB.push_back(false);
    isEE.push_back(true);
    ESc.push_back(scIter->energy());
    EScRaw.push_back(scIter->rawEnergy());
    EtSc.push_back(scIter->energy()/cosh(scIter->eta()));
    EtaSc.push_back(scIter->eta());
    PhiSc.push_back(scIter->phi());
    ScNCl.push_back((int)scIter->clustersSize());
    // seed
    reco::CaloClusterPtr seedCluster = scIter->seed();
    EScSeed.push_back(seedCluster->energy());
    EtScSeed.push_back(seedCluster->energy()/cosh(seedCluster->eta()));
    EtaScSeed.push_back(seedCluster->eta());
    PhiScSeed.push_back(seedCluster->phi());
    // HoE
    HoEpf.push_back(getHCALClusterEnergy(*scIter, hcalPFClusters.product(), 0, 0.15)/scIter->energy());

    // Hcone
    double Hcone1 = hcalHelperEndcap_->hcalESumDepth1(*scIter);
    double Hcone2 = hcalHelperEndcap_->hcalESumDepth2(*scIter);
    HoEcone.push_back((Hcone1+Hcone2)/scIter->energy());

    // nearest rechit
    const reco::PFRecHit* nearestHit = getNearestHCALPFRecHit(*scIter, hcalPFRecHits.product());
    //std::cout << "nearestHit:: " ;
    bool validHit = isValidHCALPFRecHit(*scIter,nearestHit);
    if (validHit) {
      //std::cout << "Hhit/E=" << nearestHit->energy()/scIter->energy() << std::endl;
      // HsumE
      double HsumE = getHcalsumE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE/E=" << HsumE/scIter->energy() << std::endl;
      // HsumE2
      double HsumE2 = getHcalsumE2(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE2/E=" << HsumE2/scIter->energy() << std::endl;
      // HsumE3
      double HsumE3 = getHcalsumE3(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE3/E=" << HsumE3/scIter->energy() << std::endl;
      // HwtE
      double HwtE = getHcalwtE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HwtE/E=" << HwtE/scIter->energy() << std::endl;
      HoEsumE.push_back( HsumE/scIter->energy());
      HoEsumE2.push_back( HsumE2/scIter->energy());
      HoEsumE3.push_back( HsumE3/scIter->energy());
      HoEwtE.push_back( HwtE/scIter->energy());
    }
    else {
      //std::cout << "Not match , Hhit/E=" << nearestHit->energy()/scIter->energy() << std::endl;
      HoEsumE.push_back(0);
      HoEsumE2.push_back(0);
      HoEsumE3.push_back(0);
      HoEwtE.push_back(0);
    }

  } // loop over sc 

  tree->Fill();

}

void 
ShashlikTupleDumper::FillTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::GsfElectronCollection> gsfElectrons;
  iEvent.getByLabel(electronCollection_,gsfElectrons);
  edm::LogInfo("")<<"\n\n =================> Treating event "<<iEvent.id()<<" Number of electrons "<<gsfElectrons.product()->size();

  edm::Handle<reco::SuperClusterCollection> superClustersEB;
  iEvent.getByLabel(superClusterEB_,superClustersEB);

  edm::Handle<reco::SuperClusterCollection> superClustersEE;
  iEvent.getByLabel(superClusterEE_,superClustersEE);

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(mcTruthCollection_, genParticles);

  edm::Handle<EcalRecHitCollection> barrelRecHits ;
  iEvent.getByLabel(barrelRecHitCollection_,barrelRecHits);

  edm::Handle<EcalRecHitCollection> endcapRecHits ;
  iEvent.getByLabel(endcapRecHitCollection_,endcapRecHits);

  edm::Handle<reco::PFClusterCollection> hcalPFClusters;
  iEvent.getByLabel(hcalPFClusterCollection_,hcalPFClusters);

  edm::Handle<reco::PFRecHitCollection> hcalPFRecHits;
  iEvent.getByLabel(hcalPFRecHitCollection_,hcalPFRecHits);

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;
  NPV = -1;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) 
  {
    int BX = PVI->getBunchCrossing();
    if(BX == 0)
    {
      NPV = PVI->getPU_NumInteractions();
      continue;
    }
  }

  edm::ESHandle<CaloTowerConstituentsMap> ctmap;
  iSetup.get<CaloGeometryRecord>().get(ctmap);
  theTowerConstituentsMap_ = ctmap.product();

  hcalHelperBarrel_->checkSetup(iSetup) ;
  hcalHelperBarrel_->readEvent(iEvent) ;
  hcalHelperEndcap_->checkSetup(iSetup) ;
  hcalHelperEndcap_->readEvent(iEvent) ;

  edm::ESHandle<CaloGeometry> caloGeom ;
  edm::ESHandle<CaloTopology> caloTopo ;
  iSetup.get<CaloGeometryRecord>().get(caloGeom);
  iSetup.get<CaloTopologyRecord>().get(caloTopo);

  edm::ESHandle<EcalSeverityLevelAlgo> sevLevel;
  iSetup.get<EcalSeverityLevelAlgoRcd>().get(sevLevel);

  // get the beamspot from the Event:
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle ;
  iEvent.getByLabel(edm::InputTag("offlineBeamSpot"),recoBeamSpotHandle) ;
  beamspot_ = recoBeamSpotHandle.product() ;

  edm::ESHandle<TrackerGeometry> trackerHandle ;
  iSetup.get<TrackerDigiGeometryRecord>().get(trackerHandle);

  edm::ESHandle<MagneticField> magField ;  
  iSetup.get<IdealMagneticFieldRecord>().get(magField);


  // clear tree brach vectors
  clearTreeBranchVectors(); 

  int mcNum=0;
  bool matchingMotherID;
  int mcid=0;

  // print
  if (printMCtable_)  
      std::cout << " MC info: id | pdgid | status | charge | mass | energy | p | pt | px | py | pz | vx | vy | vz |" << std::endl;

  // association mc-reco
  for (reco::GenParticleCollection::const_iterator mcIter=genParticles->begin();
       mcIter != genParticles->end(); mcIter++ ) 
  {

    // print 
    double tcharge = mcIter->charge();
    double tpx = mcIter->px();
    double tpy = mcIter->py();
    double tpz = mcIter->pz();
    double tpt = mcIter->pt();
    double tp = mcIter->p();
    double teta = mcIter->eta();
    double tphi = mcIter->phi();
    double tenergy = mcIter->energy();
    double tmass =  mcIter->mass();
    int tpdgid = mcIter->pdgId();
    int tstatus = mcIter->status();
    double tvx = mcIter->vx();
    double tvy = mcIter->vy();
    double tvz = mcIter->vz();
    if (printMCtable_) 
      std::cout << "   " << mcid++ << " | "
         << tpdgid << " | "
         << tstatus << " | "
         << tcharge << " | "
         << tmass << " | "
         << tenergy << " | "
         << tp << " | "
         << tpt << " | "
         << tpx << " | "
         << tpy << " | "
         << tpz << " | "
         << tvx << " | "
         << tvy << " | "
         << tvz << " | "
         << std::endl;

    
    // only use gen status ==1
    //if (tstatus!=1) continue; // have to remove this request

    // only select electrons
    if (abs(tpdgid)!=11) continue;

    // select requested mother matching gen particle
    // always include single particle with no mother
    const reco::Candidate * mother = mcIter->mother();
    matchingMotherID=false;
    //matchingMotherID=true;
    for (unsigned int i=0; i<matchingMotherIDs_.size(); i++)
    {   
      if ((mother == 0) || ((mother != 0) &&  mother->pdgId() == matchingMotherIDs_[i]) ) 
      {  matchingMotherID=true; }
    }

    // continue if no match
    if (!matchingMotherID) continue; 

    // set MC truth info
    ETrue.push_back(tenergy);
    PtTrue.push_back(tpt); 
    PxTrue.push_back(tpx);
    PyTrue.push_back(tpy);
    PzTrue.push_back(tpz);
    EtaTrue.push_back(teta);
    PhiTrue.push_back(tphi);
    ChargeTrue.push_back(tcharge);
    PDGTrue.push_back(tpdgid);
    MomPDGTrue.push_back(mother->pdgId());

    // looking for the best matching gsf electron
    bool okGsfFound = false;
    double deltaR_min = 999999.;
    double gsfOkRatio = 999999.;
    double deltaRGsf = 999999.;
    // find best matched electron
    reco::GsfElectron bestGsfElectron;
    for (reco::GsfElectronCollection::const_iterator gsfIter=gsfElectrons->begin();
         gsfIter!=gsfElectrons->end(); gsfIter++)
    {
      double deltaR = matchDRV2(mcIter, gsfIter);
      //std::cout << "mcPar " << mcNum << ": deltaR=" << deltaR << std::endl;
      if ( deltaR < deltaR_ )
      {
        if ( ( (mcIter->pdgId() == 11) && (gsfIter->charge() < 0.) ) ||
             ( (mcIter->pdgId() == -11) && (gsfIter->charge() > 0.) ) )
        {
          if (deltaR<deltaR_min) 
          {
            deltaR_min = deltaR;
          //  bestGsfElectron=*gsfIter;
          //  okGsfFound = true;
          }
          double tmpGsfRatio = gsfIter->p()/mcIter->p();
          if ( std::abs(tmpGsfRatio-1) < std::abs(gsfOkRatio-1) ) {
            gsfOkRatio = tmpGsfRatio;
            bestGsfElectron=*gsfIter;
            deltaRGsf = deltaR;
            okGsfFound = true;
          }
        }
      }
    } // loop over rec ele to look for the best one    


    // if not found gsfElectron, try superClusters
    bool okScFound = false;
    double deltaRSc_min = 999999.;
    double ScOkRatio = 999999.;
    double deltaRSc = 999999.;
    bool isInEB = false; 
    bool isInEE = false; 
    // find best matched sc
    reco::SuperCluster bestSuperCluster;
    if (!okGsfFound){
      // EB
      for (reco::SuperClusterCollection::const_iterator scIter=superClustersEB->begin();
           scIter!=superClustersEB->end(); scIter++)
      {
        double deltaR = reco::deltaR(*mcIter, *scIter);
        //std::cout << "mcPar " << mcNum << ": deltaR=" << deltaR << std::endl;
        if ( deltaR < deltaR_ )
        {
          if (deltaR<deltaRSc_min)
          {
            deltaRSc_min = deltaR;
          }
          double tmpScRatio = scIter->energy()/mcIter->energy();
          if ( std::abs(tmpScRatio-1) < std::abs(ScOkRatio-1) ) {
            ScOkRatio = tmpScRatio;
            bestSuperCluster=*scIter;
            deltaRSc=deltaR;
            okScFound = true;
            isInEB = true;
            isInEE = false;
          }
        }
      } // loop over sc to look for the best one 
     
      // EE
      for (reco::SuperClusterCollection::const_iterator scIter=superClustersEE->begin();
           scIter!=superClustersEE->end(); scIter++)
      {
        double deltaR = reco::deltaR(*mcIter, *scIter);
        if ( deltaR < deltaR_ )
        {
          if (deltaR<deltaRSc_min)
          {
            deltaRSc_min = deltaR;
          }
          double tmpScRatio = scIter->energy()/mcIter->energy();
          if ( std::abs(tmpScRatio-1) < std::abs(ScOkRatio-1) ) {
            ScOkRatio = tmpScRatio;
            bestSuperCluster=*scIter;
            deltaRSc=deltaR;
            okScFound = true;
            isInEB = false; 
            isInEE = true;
          }
        }
      } // loop over sc to look for the best one 

    } 

    // only book truth if gsf is not found
    if (!okGsfFound) 
    {
      FoundGsf.push_back(0);
      DeltaRGsf.push_back(-100);
      isEB.push_back(isInEB);
      isEE.push_back(isInEE);
      E.push_back(-100);
      Pt.push_back(-100);
      Px.push_back(-100);
      Py.push_back(-100);
      Pz.push_back(-100);
      Eta.push_back(-100);
      Phi.push_back(-100);
      Charge.push_back(-100);
      PDG.push_back(-100);
      Classify.push_back(-100);
      HoE.push_back(-100);
      HoE1.push_back(-100);
      HoE2.push_back(-100);
      ecalDriven.push_back(false);
      trackDriven.push_back(false);
      sigmaEtaEta.push_back(-100);
      sigmaIetaIeta.push_back(-100);
      sigmaIphiIphi.push_back(-100);
      r9.push_back(-100);
      dEtaSCAtVtx.push_back(-100);
      dEtaSCAtCal.push_back(-100);
      dEtaSeedAtCal.push_back(-100);
      dPhiSCAtVtx.push_back(-100);
      dPhiSCAtCal.push_back(-100);
      dPhiSeedAtCal.push_back(-100);
      dEtaSCAtVtxRec.push_back(-100);
      dEtaSCAtCalRec.push_back(-100);
      dPhiSCAtVtxRec.push_back(-100);
      dPhiSCAtCalRec.push_back(-100);
      dEtaSCAtVtxCorr.push_back(-100);
      TrackVtxD0.push_back(-100);
      TrackVtxDz.push_back(-100);
      trackFbrem.push_back(-100);
      scFbrem.push_back(-100);
      PTrackOut.push_back(-100);
      PtTrackOut.push_back(-100);
      PxTrackOut.push_back(-100);
      PyTrackOut.push_back(-100);
      PzTrackOut.push_back(-100);
      EtaTrackOut.push_back(-100);
      PhiTrackOut.push_back(-100);
      PTrackIn.push_back(-100);
      PtTrackIn.push_back(-100);
      PxTrackIn.push_back(-100);
      PyTrackIn.push_back(-100);
      PzTrackIn.push_back(-100);
      EtaTrackIn.push_back(-100);
      PhiTrackIn.push_back(-100);    
      ScSeedNHits.push_back(-100);
      std::vector<float> avec; 
      ScSeedHitFrac.push_back(avec);
      std::vector<float> bvec;
      ScSeedHitE.push_back(bvec);
      ScNCl.push_back(-100);
      std::vector<int> cvec;
      ScClNHits.push_back(cvec);
      std::vector<double> dvec1,dvec2,dvec3;
      ScClE.push_back(dvec1);
      ScClEta.push_back(dvec2);
      ScClPhi.push_back(dvec3);
      std::vector<float> evec1,evec2;
      ScClHitFrac.push_back(evec1);
      ScClHitE.push_back(evec2);
    }

    // no gsf also no supercluster
    if (!okGsfFound&&!okScFound)
    {
      FoundSc.push_back(0);
      DeltaRSc.push_back(-100);
      ESc.push_back(-100);
      EScRaw.push_back(-100);
      EtSc.push_back(-100);
      EtaSc.push_back(-100);
      PhiSc.push_back(-100);
      EScSeed.push_back(-100);
      EtScSeed.push_back(-100);
      EtaScSeed.push_back(-100);
      PhiScSeed.push_back(-100);
      HoEpf.push_back(-100);
      HoEwtE.push_back(-100);
      HoEsumE.push_back(-100);
      HoEsumE2.push_back(-100);
      HoEsumE3.push_back(-100); 
    }

    // now, no gsf and no sc cases are skipped, 
    // starting here are two case:
    //   1.) no gsf but found sc
    //   2.) has gsf
    // starting from case 1.) no gsf but found sc
    if (!okGsfFound&&okScFound)
    {
      FoundSc.push_back(1);
      DeltaRSc.push_back(deltaRSc);
      // now fill the gsf electron info
      ESc.push_back(bestSuperCluster.energy());
      EScRaw.push_back(bestSuperCluster.rawEnergy());
      EtSc.push_back(bestSuperCluster.energy()/cosh(bestSuperCluster.eta()));
      EtaSc.push_back(bestSuperCluster.eta());
      PhiSc.push_back(bestSuperCluster.phi());
      // seed
      reco::CaloClusterPtr seedCluster = bestSuperCluster.seed();
      EScSeed.push_back(seedCluster->energy());
      EtScSeed.push_back(seedCluster->energy()/cosh(seedCluster->eta()));
      EtaScSeed.push_back(seedCluster->eta());
      PhiScSeed.push_back(seedCluster->phi());

      // HoE
      HoEpf.push_back(getHCALClusterEnergy(bestSuperCluster, hcalPFClusters.product(), 0, 0.15)/bestSuperCluster.energy());

      // Hcone
      double Hcone1(0);
      double Hcone2(0);
      if (isInEB){
        Hcone1 = hcalHelperBarrel_->hcalESumDepth1(bestSuperCluster);
        Hcone2 = hcalHelperBarrel_->hcalESumDepth2(bestSuperCluster);
      } else {
        Hcone1 = hcalHelperEndcap_->hcalESumDepth1(bestSuperCluster);
        Hcone2 = hcalHelperEndcap_->hcalESumDepth2(bestSuperCluster);
      }
      
      HoEcone.push_back((Hcone1+Hcone2)/bestSuperCluster.energy());

      // nearest rechit
      const reco::PFRecHit* nearestHit = getNearestHCALPFRecHit(bestSuperCluster, hcalPFRecHits.product());
      //std::cout << "nearestHit:: " ;
      bool validHit = isValidHCALPFRecHit(bestSuperCluster,nearestHit);
      if (validHit) {
        //std::cout << "Hhit/E=" << nearestHit->energy()/bestSuperCluster.energy() << std::endl;
        // HsumE
        double HsumE = getHcalsumE(nearestHit, hcalPFRecHits.product());
        //std::cout << "HsumE/E=" << HsumE/bestSuperCluster.energy() << std::endl;
        // HsumE2
        double HsumE2 = getHcalsumE2(nearestHit, hcalPFRecHits.product());
        //std::cout << "HsumE2/E=" << HsumE2/bestSuperCluster.energy() << std::endl;
        // HsumE3
        double HsumE3 = getHcalsumE3(nearestHit, hcalPFRecHits.product());
        //std::cout << "HsumE3/E=" << HsumE3/bestSuperCluster.energy() << std::endl;
        // HwtE
        double HwtE = getHcalwtE(nearestHit, hcalPFRecHits.product());
        //std::cout << "HwtE/E=" << HwtE/bestSuperCluster.energy() << std::endl;

        HoEsumE.push_back( HsumE/bestSuperCluster.energy());
        HoEsumE2.push_back( HsumE2/bestSuperCluster.energy());
        HoEsumE3.push_back( HsumE3/bestSuperCluster.energy());
        HoEwtE.push_back( HwtE/bestSuperCluster.energy());
      }
      else {
        //std::cout << "Not match , Hhit/E=" << nearestHit->energy()/bestSuperCluster.energy() << std::endl;
        HoEsumE.push_back(0);
        HoEsumE2.push_back(0);
        HoEsumE3.push_back(0);
        HoEwtE.push_back(0);
      }

    }

    if (!okGsfFound){
      // skip the rests
      mcNum++;
      continue; 
    }

    // otherwise found gsf
    FoundGsf.push_back(1);
    DeltaRGsf.push_back(deltaRGsf);
    FoundSc.push_back(1);
 
    // gsfElectron info
    E.push_back(bestGsfElectron.energy());
    Pt.push_back(bestGsfElectron.pt());
    Px.push_back(bestGsfElectron.px());
    Py.push_back(bestGsfElectron.py());
    Pz.push_back(bestGsfElectron.pz());
    Eta.push_back(bestGsfElectron.eta());
    Phi.push_back(bestGsfElectron.phi());
    isEB.push_back(bestGsfElectron.isEB());
    isEE.push_back(bestGsfElectron.isEE()); 
    Charge.push_back((double)bestGsfElectron.charge());
    PDG.push_back(bestGsfElectron.pdgId());
    Classify.push_back(bestGsfElectron.classification());
    HoE.push_back(bestGsfElectron.hcalOverEcal());
    HoE1.push_back(bestGsfElectron.hcalDepth1OverEcal());
    HoE2.push_back(bestGsfElectron.hcalDepth2OverEcal());
    ecalDriven.push_back(bestGsfElectron.ecalDrivenSeed());
    trackDriven.push_back(bestGsfElectron.trackerDrivenSeed());
    sigmaEtaEta.push_back(bestGsfElectron.sigmaEtaEta());
    sigmaIetaIeta.push_back(bestGsfElectron.sigmaIetaIeta());
    sigmaIphiIphi.push_back(bestGsfElectron.sigmaIphiIphi());
    r9.push_back(bestGsfElectron.r9());
    dEtaSCAtVtx.push_back(bestGsfElectron.deltaEtaSuperClusterTrackAtVtx());
    dEtaSCAtCal.push_back(bestGsfElectron.deltaEtaEleClusterTrackAtCalo());
    dEtaSeedAtCal.push_back(bestGsfElectron.deltaEtaSeedClusterTrackAtCalo());
    dPhiSCAtVtx.push_back(bestGsfElectron.deltaPhiSuperClusterTrackAtVtx());
    dPhiSCAtCal.push_back(bestGsfElectron.deltaPhiEleClusterTrackAtCalo());
    dPhiSeedAtCal.push_back(bestGsfElectron.deltaPhiSeedClusterTrackAtCalo());
    TrackVtxD0.push_back(bestGsfElectron.gsfTrack()->dxy());
    TrackVtxDz.push_back(bestGsfElectron.gsfTrack()->dz());
    trackFbrem.push_back(bestGsfElectron.trackFbrem());
    scFbrem.push_back(bestGsfElectron.superClusterFbrem());

    // superCluster
    reco::SuperClusterRef superCluster = bestGsfElectron.superCluster();
 
    // now fill the gsf electron info
    ESc.push_back(superCluster->energy());
    EScRaw.push_back(superCluster->rawEnergy());
    EtSc.push_back(superCluster->energy()/cosh(superCluster->eta()));
    EtaSc.push_back(superCluster->eta());
    PhiSc.push_back(superCluster->phi());

    // seed
    reco::CaloClusterPtr seedCluster = superCluster->seed();
    EScSeed.push_back(seedCluster->energy());
    EtScSeed.push_back(seedCluster->energy()/cosh(seedCluster->eta()));
    EtaScSeed.push_back(seedCluster->eta());
    PhiScSeed.push_back(seedCluster->phi()); 

    // HoE
    HoEpf.push_back(getHCALClusterEnergy(*superCluster, hcalPFClusters.product(), 0, 0.15)/superCluster->energy());

    // nearest rechit
    const reco::PFRecHit* nearestHit = getNearestHCALPFRecHit(*superCluster, hcalPFRecHits.product());
    //std::cout << "nearestHit:: " ;
    bool validHit = isValidHCALPFRecHit(*superCluster,nearestHit);
    if (validHit) {
      //std::cout << "Hhit/E=" << nearestHit->energy()/superCluster->energy() << std::endl;
      // HsumE
      double HsumE = getHcalsumE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE/E=" << HsumE/superCluster->energy() << std::endl;
      // HsumE2
      double HsumE2 = getHcalsumE2(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE2/E=" << HsumE2/superCluster->energy() << std::endl;
      // HsumE3
      double HsumE3 = getHcalsumE3(nearestHit, hcalPFRecHits.product());
      //std::cout << "HsumE3/E=" << HsumE3/superCluster->energy() << std::endl;
      // HwtE
      double HwtE = getHcalwtE(nearestHit, hcalPFRecHits.product());
      //std::cout << "HwtE/E=" << HwtE/superCluster->energy() << std::endl;
      HoEsumE.push_back( HsumE/superCluster->energy());
      HoEsumE2.push_back( HsumE2/superCluster->energy());
      HoEsumE3.push_back( HsumE3/superCluster->energy());
      HoEwtE.push_back( HwtE/superCluster->energy());
    }
    else {
      //std::cout << "Not match , Hhit/E=" << nearestHit->energy()/superCluster->energy() << std::endl;
      HoEsumE.push_back(0);
      HoEsumE2.push_back(0);
      HoEsumE3.push_back(0);
      HoEwtE.push_back(0);
    }

    // Hcone
    double Hcone1(0);
    double Hcone2(0); 
    if (bestGsfElectron.isEB()){
      Hcone1 = hcalHelperBarrel_->hcalESumDepth1(bestSuperCluster);
      Hcone2 = hcalHelperBarrel_->hcalESumDepth2(bestSuperCluster);
    } else {
      Hcone1 = hcalHelperEndcap_->hcalESumDepth1(bestSuperCluster);
      Hcone2 = hcalHelperEndcap_->hcalESumDepth2(bestSuperCluster);
    }
    HoEcone.push_back((Hcone1+Hcone2)/bestSuperCluster.energy());

    // recalculate eid variables

    const CaloTopology * topology = caloTopo.product() ;
    const CaloGeometry * geometry = caloGeom.product() ;
    const EcalRecHitCollection * recHits = 0 ;
    std::vector<int> recHitFlagsToBeExcluded ;
    std::vector<int> recHitSeverityToBeExcluded ;
    const EcalSeverityLevelAlgo * severityLevelAlgo = sevLevel.product() ;
    if (bestGsfElectron.isEB())
    {
      recHits = barrelRecHits.product() ;
      recHitFlagsToBeExcluded = recHitFlagsToBeExcludedBarrel_ ;
      recHitSeverityToBeExcluded = recHitSeverityToBeExcludedBarrel_ ;
    }
    else
    {
      recHits = endcapRecHits.product() ;
      recHitFlagsToBeExcluded = recHitFlagsToBeExcludedEndcaps_ ;
      recHitSeverityToBeExcluded = recHitSeverityToBeExcludedEndcaps_ ;
    }

    std::vector<float> covariances = EcalClusterTools::covariances(*seedCluster,recHits,topology,geometry,recHitFlagsToBeExcluded,recHitSeverityToBeExcluded,severityLevelAlgo) ;
    std::vector<float> localCovariances = EcalClusterTools::localCovariances(*seedCluster,recHits,topology,recHitFlagsToBeExcluded,recHitSeverityToBeExcluded,severityLevelAlgo) ;
   
    sigmaEtaEtaRec.push_back(sqrt(covariances[0]));
    sigmaIetaIetaRec.push_back(sqrt(localCovariances[0]));
    sigmaIphiIphiRec.push_back(sqrt(localCovariances[2]));

    // track-match
/*
    ElectronData electronData(bestGsfElectron.core(),*beamspot_) ;

    MultiTrajectoryStateTransform  mtsTransform(trackerHandle.product(),magField.product());

    electronData.calculateTSOS( mtsTransform, eventSetupData_->constraintAtVtx )

    CaloClusterPtr elbcRef = electronData_->getEleBasicCluster(eventSetupData_->mtsTransform) ;
 
    EleRelPointPair scAtVtx(bestSuperCluster.position(),electronData_->sclPos,beamspot_->position()) ;
    //tcMatching.deltaEtaSuperClusterAtVtx = scAtVtx.dEta() ;
    //tcMatching.deltaPhiSuperClusterAtVtx = scAtVtx.dPhi() ;

    EleRelPointPair seedAtCalo(seedCluster->position(),electronData_->seedPos,beamspot_->position()) ;
    //tcMatching.deltaEtaSeedClusterAtCalo = seedAtCalo.dEta() ;
    //tcMatching.deltaPhiSeedClusterAtCalo = seedAtCalo.dPhi() ;

    EleRelPointPair ecAtCalo(elbcRef->position(),electronData_->elePos,beamspot_->position()) ;
    //tcMatching.deltaEtaEleClusterAtCalo = ecAtCalo.dEta() ;
    //tcMatching.deltaPhiEleClusterAtCalo = ecAtCalo.dPhi() ;

*/
    dEtaSCAtVtxRec.push_back(bestGsfElectron.deltaEtaSuperClusterTrackAtVtx());
    dEtaSCAtCalRec.push_back(bestGsfElectron.deltaEtaEleClusterTrackAtCalo());
    dPhiSCAtVtxRec.push_back(bestGsfElectron.deltaPhiSuperClusterTrackAtVtx());
    dPhiSCAtCalRec.push_back(bestGsfElectron.deltaPhiEleClusterTrackAtCalo());

    // simple correction of the 
    float corrDeltaEtaScVtx(0);
    if (fabs(bestGsfElectron.eta())>1.47&&fabs(bestGsfElectron.eta())<3.0) {
      corrDeltaEtaScVtx = (float)func_corrDeltaEtaScVtx->Eval(fabs(bestGsfElectron.eta()));
      if (bestGsfElectron.eta()<0) corrDeltaEtaScVtx = -corrDeltaEtaScVtx;
    }
    dEtaSCAtVtxCorr.push_back(bestGsfElectron.deltaEtaSuperClusterTrackAtVtx()-corrDeltaEtaScVtx);

    // get hits energies and fractions
    const std::vector<std::pair<DetId,float> > seedHitsAndFracs = seedCluster->hitsAndFractions();
    ScSeedNHits.push_back(0);
    std::vector<float> seedFracs;
    std::vector<float> seedEs;
    for (size_t ihit=0; ihit<seedHitsAndFracs.size(); ihit++)
    {
      // Det id
      DetId id = seedHitsAndFracs.at(ihit).first;
      // try barrel first
      EcalRecHitCollection::const_iterator it = barrelRecHits->find( id );
      // if not found in barrel, try endcap
      if (it == barrelRecHits->end()) it = endcapRecHits->find( id );
      // if found, give energy
      if (it !=endcapRecHits->end()) 
      {
        seedFracs.push_back(seedHitsAndFracs.at(ihit).second);
        seedEs.push_back(it->energy());
        ScSeedNHits.at(mcNum)++;
      }
    } 
    ScSeedHitFrac.push_back(seedFracs);
    ScSeedHitE.push_back(seedEs);

    // all clusters
    ScNCl.push_back((int)superCluster->clustersSize());
    std::vector<int> clnhits;
    std::vector<double> cle;
    std::vector<double> cleta;
    std::vector<double> clphi;
    std::vector<float> hitfracs;
    std::vector<float> hites;
    for (reco::CaloCluster_iterator caloCluster = superCluster->clustersBegin();
         caloCluster!=superCluster->clustersEnd(); caloCluster++)
    {
      cle.push_back((*caloCluster)->energy());
      cleta.push_back((*caloCluster)->eta());
      clphi.push_back((*caloCluster)->phi());
      const std::vector<std::pair<DetId,float> > hitsandfracs = (*caloCluster)->hitsAndFractions(); 
      clnhits.push_back(0);
      for (size_t ihit=0; ihit<hitsandfracs.size(); ihit++)
      {
        // Det id
        DetId id = hitsandfracs.at(ihit).first;
        // try barrel first
        EcalRecHitCollection::const_iterator it = barrelRecHits->find( id );
        // if not found in barrel, try endcap
        if (it == barrelRecHits->end()) it = endcapRecHits->find( id );
        // if found, give energy
        if (it !=endcapRecHits->end())
        {
          hitfracs.push_back(hitsandfracs.at(ihit).second);
          hites.push_back(it->energy());
          clnhits.back()++;
        }
      }
    }    
    
    ScClNHits.push_back(clnhits);
    ScClHitFrac.push_back(hitfracs);
    ScClHitE.push_back(hites);
    ScClE.push_back(cle);
    ScClEta.push_back(cleta);
    ScClPhi.push_back(clphi);

    reco::GsfTrackRef gsfTrack = bestGsfElectron.gsfTrack();
    if (!gsfTrack) 
    {
      PTrackOut.push_back(-100);
      PtTrackOut.push_back(-100);
      PxTrackOut.push_back(-100);
      PyTrackOut.push_back(-100);
      PzTrackOut.push_back(-100);
      EtaTrackOut.push_back(-100);
      PhiTrackOut.push_back(-100);
      PTrackIn.push_back(-100);
      PtTrackIn.push_back(-100);
      PxTrackIn.push_back(-100);
      PyTrackIn.push_back(-100);
      PzTrackIn.push_back(-100);
      EtaTrackIn.push_back(-100);
      PhiTrackIn.push_back(-100);
      mcNum++;
      continue;
    }

   
    PTrackOut.push_back(gsfTrack->outerMomentum().R());
    PtTrackOut.push_back(gsfTrack->outerMomentum().Rho());
    PxTrackOut.push_back(gsfTrack->outerMomentum().X());
    PyTrackOut.push_back(gsfTrack->outerMomentum().Y());
    PzTrackOut.push_back(gsfTrack->outerMomentum().Z());
    EtaTrackOut.push_back(gsfTrack->outerMomentum().eta());
    PhiTrackOut.push_back(gsfTrack->outerMomentum().phi());
    PTrackIn.push_back(gsfTrack->innerMomentum().R());
    PtTrackIn.push_back(gsfTrack->innerMomentum().Rho());
    PxTrackIn.push_back(gsfTrack->innerMomentum().X());
    PyTrackIn.push_back(gsfTrack->innerMomentum().Y());
    PzTrackIn.push_back(gsfTrack->innerMomentum().Z());
    EtaTrackIn.push_back(gsfTrack->innerMomentum().eta());
    PhiTrackIn.push_back(gsfTrack->innerMomentum().phi());


    // number of mc particles
    mcNum++;

  } // loop over mc particle


  Nparts = mcNum;
  tree->Fill();
  
}


double ShashlikTupleDumper::matchDR(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec )
{
  double xvg = 0.1*pmc->vertex().x();
  double yvg = 0.1*pmc->vertex().y();
  double zvg = 0.1*pmc->vertex().z();
  double pxg = pmc->px();
  double pyg = pmc->py();
  double pzg = pmc->pz();
  double eg  = pmc->energy();

  double xp = prec->caloPosition().x();
  double yp = prec->caloPosition().y();
  double zp = prec->caloPosition().z();

  double R = sqrt((xp-xvg)*(xp-xvg) + (yp-yvg)*(yp-yvg) + (zp-zvg)*(zp-zvg));
  double dR = sqrt(pow(xvg + R*pxg/eg - xp, 2) + pow(yvg + R*pyg/eg - yp, 2) + pow(zvg + R*pzg/eg - zp, 2));
  if(dR<1e-5) dR=1e-5;
  return dR;
}

double ShashlikTupleDumper::matchDRV2(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec )
{
  double mcEta = pmc->eta();
  double mcPhi = pmc->phi();

  double pEta = prec->eta(); 
  double pPhi = prec->phi(); 

  double deta = mcEta - pEta;
  double dphi = TVector2::Phi_mpi_pi(mcPhi-pPhi);
  return TMath::Sqrt(deta*deta+dphi*dphi);
}

double ShashlikTupleDumper::getHCALClusterEnergy(const reco::SuperCluster & sc, const reco::PFClusterCollection *hcalpfcs, float EtMin, double hOverEConeSize) const 
{
  math::XYZVector vectorSC(sc.position().x(),sc.position().y(),sc.position().z());

  double totalEnergy = 0.;
  for( std::vector<reco::PFCluster>::const_iterator trItr = hcalpfcs->begin();
       trItr != hcalpfcs->end() ; ++trItr){
    math::XYZVector vectorHgcalHFECluster(trItr->position().x(),trItr->position().y(),trItr->position().z());
    double dR = ROOT::Math::VectorUtil::DeltaR(vectorSC,vectorHgcalHFECluster);
    if (dR<hOverEConeSize) totalEnergy += trItr->energy();
  }

  return totalEnergy;
}

const reco::PFRecHit* ShashlikTupleDumper::getNearestHCALPFRecHit(const reco::SuperCluster & sc, const reco::PFRecHitCollection * pfrechits) const
{
  
  reco::PFRecHitCollection::const_iterator trIter = pfrechits->begin();   
  reco::PFRecHitCollection::const_iterator nearestHit = trIter;
  double dRmin = 999999;
  math::XYZVector vectorSC(sc.position().x(),sc.position().y(),sc.position().z());
  for (; trIter!=pfrechits->end(); ++trIter){
    if (trIter->depth()!=1) continue; // only take the first layer.
    math::XYZVector vectorHcal(trIter->position().x(),trIter->position().y(),trIter->position().z());
    double dR = ROOT::Math::VectorUtil::DeltaR(vectorSC,vectorHcal);
    if (dR<dRmin) {
      nearestHit = trIter;
      dRmin = dR;
    }
  }

  //HcalDetId detid_nst(nearestHit->detId());
  //int ieta_nst = detid_nst.ieta();
  //int iphi_nst = detid_nst.iphi();
  //int depth_nst = nearestHit->depth();
  //std::cout << "ShashlikTupleDumper::getNearestHCALPFRecHit: " << "dR=" << dRmin << "; depth=" << depth_nst << "; ieta=" << ieta_nst << "; iphi=" << iphi_nst 
  //          << std::endl;

  return &(*nearestHit); 
}


bool ShashlikTupleDumper::isValidHCALPFRecHit(const reco::SuperCluster & sc, const reco::PFRecHit *hit) 
{
  // nearest should behind the sc
  math::XYZVector vectorSC(sc.position().x(),sc.position().y(),sc.position().z());
  math::XYZVector vectorHit(hit->position().x(),hit->position().y(),hit->position().z());
  double dPhi = ROOT::Math::VectorUtil::DeltaPhi(vectorSC,vectorHit);
  double dEta = fabs(vectorSC.eta()-vectorHit.eta());

  if (   ((hit->layer()==1||hit->layer()==2)&&(fabs(dPhi)>0.087||fabs(dEta)>0.087))  //  HCAL_BARREL1 = 1,HCAL_BARREL2 = 2,
      || ((hit->layer()==3 && fabs(hit->position().eta())<1.6)&&(fabs(dPhi)>0.087||fabs(dEta)>0.087)) //HCAL_ENDCAP = 3,
      || ((hit->layer()==3 && fabs(hit->position().eta())>=1.6)&&(fabs(dPhi)>0.17||fabs(dEta)>0.17)) ) //HCAL_ENDCAP = 3,
    return false;

  return true;

}

double ShashlikTupleDumper::getHcalsumE(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits)
{

  HcalDetId detid_nst(hit->detId());
  CaloTowerDetId towerDetId_nst = theTowerConstituentsMap_->towerOf(detid_nst);

  double energy(0);
  reco::PFRecHitCollection::const_iterator trIter = pfrechits->begin();
  for (; trIter!=pfrechits->end(); ++trIter){
    HcalDetId detid(trIter->detId());
    CaloTowerDetId towerDetId = theTowerConstituentsMap_->towerOf(detid);
    if (towerDetId.rawId()==towerDetId_nst.rawId()){
      energy += trIter->energy();
      //int ieta = detid.ieta();
      //int iphi = detid.iphi();
      //int depth = trIter->depth();
      //std::cout << "ShashlikTupleDumper::getHcalsumE: " << "; depth=" << depth << "; ieta=" << ieta << "; iphi=" << iphi << std::endl;
    }
  }
  return energy; 
}

double ShashlikTupleDumper::getHcalsumE2(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits)
{

  HcalDetId detid_nst(hit->detId());
  CaloTowerDetId towerDetId_nst = theTowerConstituentsMap_->towerOf(detid_nst);

  double energy(0);
  reco::PFRecHitCollection::const_iterator trIter = pfrechits->begin();
  for (; trIter!=pfrechits->end(); ++trIter){
    if (trIter->depth()<=1) continue;
    HcalDetId detid(trIter->detId());
    CaloTowerDetId towerDetId = theTowerConstituentsMap_->towerOf(detid);
    if (towerDetId.rawId()==towerDetId_nst.rawId()){
      energy += trIter->energy();
    }
  }
  return energy;
}

double ShashlikTupleDumper::getHcalsumE3(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits)
{

  HcalDetId detid_nst(hit->detId());
  CaloTowerDetId towerDetId_nst = theTowerConstituentsMap_->towerOf(detid_nst);

  double energy(0);
  reco::PFRecHitCollection::const_iterator trIter = pfrechits->begin();
  for (; trIter!=pfrechits->end(); ++trIter){
    if (trIter->depth()<=2) continue;
    HcalDetId detid(trIter->detId());
    CaloTowerDetId towerDetId = theTowerConstituentsMap_->towerOf(detid);
    if (towerDetId.rawId()==towerDetId_nst.rawId()){
      energy += trIter->energy();
    }
  }
  return energy;
}


double ShashlikTupleDumper::getHcalwtE(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits)
{
  double sumDepthEng(0);
  double sumDepth(0);
  HcalDetId detid_nst(hit->detId());
  CaloTowerDetId towerDetId_nst = theTowerConstituentsMap_->towerOf(detid_nst);
  reco::PFRecHitCollection::const_iterator trIter = pfrechits->begin();
  for (; trIter!=pfrechits->end(); ++trIter){
    HcalDetId detid(trIter->detId());
    CaloTowerDetId towerDetId = theTowerConstituentsMap_->towerOf(detid);
    if (towerDetId.rawId()==towerDetId_nst.rawId()){
      int depth = trIter->depth();
      sumDepthEng += depth*trIter->energy();
      sumDepth += depth;
    }
  }
  return sumDepthEng/sumDepth;

}

