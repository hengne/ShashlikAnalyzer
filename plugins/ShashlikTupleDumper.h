#ifndef ShashlikTupleDumper_h
#define ShashlikTupleDumper_h

//
// Package:         ShashlikAnalyzer/ShashlikAnalyzer
// Class:           ShashlikTupleDumper
//

//
// Original Author:  Hengne Li
//         Created:  Wed, 03 Sep 2014 10:41:20 GMT
// $Id$ 
//
//


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFwd.h"
#include "Geometry/CaloTopology/interface/CaloTowerConstituentsMap.h"

class TFile;
class TTree;

class ShashlikTupleDumper : public edm::EDAnalyzer
{
 public:

  explicit ShashlikTupleDumper(const edm::ParameterSet& conf);

  virtual ~ShashlikTupleDumper();

  virtual void beginJob();
  virtual void endJob();
  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);

  void bookTree();
  void bookQCDTree();
  void clearTreeBranchVectors();
  void clearQCDTreeBranchVectors();
  void FillTree(const edm::Event& e, const edm::EventSetup& c);
  void FillQCDTree(const edm::Event& e, const edm::EventSetup& c);

  double matchDR(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec);
  double matchDRV2(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec);
  double getHCALClusterEnergy(const reco::SuperCluster & sc, const reco::PFClusterCollection *hcalpfcs, float EtMin, double hOverEConeSize) const;
  const reco::PFRecHit* getNearestHCALPFRecHit(const reco::SuperCluster & sc, const reco::PFRecHitCollection * pfrechits) const;
  bool isValidHCALPFRecHit(const reco::SuperCluster & sc, const reco::PFRecHit *hit);  
  double getHcalsumE(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits);
  double getHcalsumE2(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits);
  double getHcalsumE3(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits);
  double getHcalwtE(const reco::PFRecHit * hit, const reco::PFRecHitCollection * pfrechits);

 private:

  TFile *histfile_;
  TTree *tree;
  
  // variables for the tree
  ULong64_t RunNum, EvtNum, LumNum;
  int NPV;
  double VtxXTrue, VtxYTrue, VtxZTrue;
  double VtxX, VtxY, VtxZ;
  
  int Nparts, Nelecs, Nphots;

  std::vector<double> ETrue, PtTrue, PxTrue, PyTrue, PzTrue;
  std::vector<double> EtaTrue, PhiTrue, ChargeTrue;
  std::vector<int> PDGTrue;
  std::vector<int> MomPDGTrue;
  std::vector<int> FoundGsf;
  std::vector<int> FoundSc;
  std::vector<double> DeltaRGsf, DeltaRSc;
  

  std::vector<double> ESc, EScRaw, EtSc, EtaSc, PhiSc;
  std::vector<double> EScSeed, EtScSeed, EtaScSeed, PhiScSeed;
  std::vector<int> ScSeedNHits;
  std::vector< std::vector<float> > ScSeedHitFrac, ScSeedHitE;

  std::vector<int> ScNCl;
  std::vector< std::vector<int> > ScClNHits;
  std::vector< std::vector<double> > ScClE;
  std::vector< std::vector<double> > ScClEta;
  std::vector< std::vector<double> > ScClPhi;
  std::vector< std::vector<float> > ScClHitFrac;
  std::vector< std::vector<float> > ScClHitE;

  std::vector<double> E, Pt, Px, Py, Pz, Eta, Phi, Charge;
  std::vector<int> PDG, Classify;
  std::vector<bool> isEB, isEE, ecalDriven, trackDriven;
  std::vector<float> HoE, HoE1, HoE2, sigmaEtaEta, sigmaIetaIeta, sigmaIphiIphi, r9;
  std::vector<float> dEtaSCAtVtx, dEtaSCAtCal, dPhiSCAtVtx, dPhiSCAtCal, trackFbrem, scFbrem;

  std::vector<double> PTrackOut, PtTrackOut, PxTrackOut, PyTrackOut, PzTrackOut;
  std::vector<double> EtaTrackOut, PhiTrackOut;

  std::vector<double> PTrackIn, PtTrackIn, PxTrackIn, PyTrackIn, PzTrackIn;
  std::vector<double> EtaTrackIn, PhiTrackIn;
  std::vector<double> HoEpf, HoEsumE, HoEwtE, HoEsumE2, HoEsumE3;

  std::string outputFile_;
  std::string treeType_;
  edm::InputTag electronCollection_;
  edm::InputTag photonCollection_;
  edm::InputTag superClusterEB_;
  edm::InputTag superClusterEE_;
  edm::InputTag mcTruthCollection_;
  edm::InputTag barrelRecHitCollection_ ;
  edm::InputTag endcapRecHitCollection_ ;
  edm::InputTag hcalPFClusterCollection_;
  edm::InputTag hcalPFRecHitCollection_;

  double deltaR_;
  std::vector<int> matchingIDs_;
  std::vector<int> matchingMotherIDs_;

  bool printMCtable_;

  const CaloTowerConstituentsMap* theTowerConstituentsMap_;

 };

#endif



