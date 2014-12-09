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
  void clearTreeBranchVectors();

  double matchDR(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec);
  double matchDRV2(reco::GenParticleCollection::const_iterator pmc, reco::GsfElectronCollection::const_iterator prec);

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
  std::vector<int> PDG;
  std::vector<bool> isEB, isEE;

  std::vector<double> PTrackOut, PtTrackOut, PxTrackOut, PyTrackOut, PzTrackOut;
  std::vector<double> EtaTrackOut, PhiTrackOut;

  std::vector<double> PTrackIn, PtTrackIn, PxTrackIn, PyTrackIn, PzTrackIn;
  std::vector<double> EtaTrackIn, PhiTrackIn;

  std::string outputFile_;
  edm::InputTag electronCollection_;
  edm::InputTag mcTruthCollection_;
  edm::InputTag barrelRecHitCollection_ ;
  edm::InputTag endcapRecHitCollection_ ;

  double deltaR_;
  std::vector<int> matchingIDs_;
  std::vector<int> matchingMotherIDs_;

  bool printMCtable_;

 };

#endif



