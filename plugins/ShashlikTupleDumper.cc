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
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "CLHEP/Units/GlobalPhysicalConstants.h"
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

DEFINE_FWK_MODULE(ShashlikTupleDumper);


ShashlikTupleDumper::ShashlikTupleDumper(const edm::ParameterSet& conf)
 {
  outputFile_ = conf.getParameter<std::string>("outputFile");
  histfile_ = new TFile(outputFile_.c_str(),"RECREATE");
  electronCollection_=conf.getParameter<edm::InputTag>("electronCollection");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");
  deltaR_ = conf.getParameter<double>("DeltaR");
  matchingIDs_ = conf.getParameter<std::vector<int> >("MatchingID");
  matchingMotherIDs_ = conf.getParameter<std::vector<int> >("MatchingMotherID");

 }

void 
ShashlikTupleDumper::beginJob()
{
  histfile_->cd();
  bookTree();
  
}

void 
ShashlikTupleDumper::bookTree()
{
  histfile_->cd();
  tree = new TTree("tree", "tree");

  tree->Branch("RunNum", &RunNum,"RunNum/l");
  tree->Branch("EvtNum", &EvtNum,"EvtNum/l");
  tree->Branch("LumNum", &LumNum,"LumNum/l");
  tree->Branch("VtxXTrue", &VtxXTrue,"VtxXTrue/D");
  tree->Branch("VtxYTrue", &VtxYTrue,"VtxYTrue/D");
  tree->Branch("VtxZTrue", &VtxZTrue,"VtxZTrue/D");
  tree->Branch("VtxX", &VtxX,"VtxX/D");
  tree->Branch("VtxY", &VtxY,"VtxY/D");
  tree->Branch("VtxZ", &VtxZ,"VtxZ/D");
  tree->Branch("Nparts", &Nparts,"Nparts/I");
  tree->Branch("Nelecs", &Nelecs,"Nelecs/I");
  tree->Branch("Nphots", &Nphots,"Nphots/I"); 
  tree->Branch("ETrue", ETrue,"ETrue[Nparts]/D");
  tree->Branch("PtTrue", PtTrue,"PtTrue[Nparts]/D");
  tree->Branch("PxTrue", PxTrue,"PxTrue[Nparts]/D");
  tree->Branch("PyTrue", PyTrue,"PyTrue[Nparts]/D");
  tree->Branch("PzTrue", PzTrue,"PzTrue[Nparts]/D");
  tree->Branch("EtaTrue", EtaTrue,"EtaTrue[Nparts]/D");
  tree->Branch("PhiTrue", PhiTrue,"PhiTrue[Nparts]/D");
  tree->Branch("ChargeTrue", ChargeTrue,"ChargeTrue[Nparts]/D");
  tree->Branch("PDGTrue", PDGTrue,"PDGTrue[Nparts]/I");
  tree->Branch("ESc", ESc,"ESc[Nparts]/D");
  tree->Branch("EtSc", EtSc,"EtSc[Nparts]/D");
  tree->Branch("EtaSc", EtaSc,"EtaSc[Nparts]/D");
  tree->Branch("PhiSc", PhiSc,"PhiSc[Nparts]/D");
  tree->Branch("EScSeed", EScSeed,"EScSeed[Nparts]/D");
  tree->Branch("EtScSeed", EtScSeed,"EtScSeed[Nparts]/D");
  tree->Branch("EtaScSeed", EtaScSeed,"EtaScSeed[Nparts]/D");
  tree->Branch("PhiScSeed", PhiScSeed,"PhiScSeed[Nparts]/D");
  tree->Branch("Charge", Charge,"Charge[Nparts]/D");
  tree->Branch("PDG", PDG,"PDG[Nparts]/I");
  tree->Branch("PTrackOut", PTrackOut,"PTrackOut[Nparts]/D");
  tree->Branch("PtTrackOut", PtTrackOut,"PtTrackOut[Nparts]/D");
  tree->Branch("PxTrackOut", PxTrackOut,"PxTrackOut[Nparts]/D");
  tree->Branch("PyTrackOut", PyTrackOut,"PyTrackOut[Nparts]/D");
  tree->Branch("PzTrackOut", PzTrackOut,"PzTrackOut[Nparts]/D");
  tree->Branch("EtaTrackOut", EtaTrackOut,"EtaTrackOut[Nparts]/D");
  tree->Branch("PhiTrackOut", PhiTrackOut,"PhiTrackOut[Nparts]/D");
  tree->Branch("PTrackIn", PTrackIn,"PTrackIn[Nparts]/D");
  tree->Branch("PtTrackIn", PtTrackIn,"PtTrackIn[Nparts]/D");
  tree->Branch("PxTrackIn", PxTrackIn,"PxTrackIn[Nparts]/D");
  tree->Branch("PyTrackIn", PyTrackIn,"PyTrackIn[Nparts]/D");
  tree->Branch("PzTrackIn", PzTrackIn,"PzTrackIn[Nparts]/D");
  tree->Branch("EtaTrackIn", EtaTrackIn,"EtaTrackIn[Nparts]/D");
  tree->Branch("PhiTrackIn", PhiTrackIn,"PhiTrackIn[Nparts]/D");


}

void 
ShashlikTupleDumper::endJob()
{

  tree->Write();
  histfile_->cd();

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
  // get electrons

  edm::Handle<reco::GsfElectronCollection> gsfElectrons;
  iEvent.getByLabel(electronCollection_,gsfElectrons);
  edm::LogInfo("")<<"\n\n =================> Treating event "<<iEvent.id()<<" Number of electrons "<<gsfElectrons.product()->size();

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(mcTruthCollection_, genParticles);


  int mcNum=0, gamNum=0, eleNum=0;

  // print 
  std::cout << " MC info: id | pdgid | status | charge | mass | energy | pt | px | py | pz | " << std::endl;

  // association mc-reco
  for (reco::GenParticleCollection::const_iterator mcIter=genParticles->begin();
       mcIter != genParticles->end(); mcIter++ ) 
  {

    // counts 
    if (mcIter->pdgId() == 22 ){ gamNum++; }
    if (abs(mcIter->pdgId()) == 11 ){ eleNum++; }

    // print 
    double charge = mcIter->charge();
    double px = mcIter->px();
    double py = mcIter->py();
    double pz = mcIter->pz();
    double pt = mcIter->pt();
    double energy = mcIter->energy();
    double mass =  mcIter->mass();
    double pdgid = mcIter->pdgId();
    double status = mcIter->status();
    std::cout << "   " << mcNum << " | "
         << pdgid << " | "
         << status << " | "
         << charge << " | "
         << mass << " | "
         << energy << " | "
         << pt << " | "
         << px << " | "
         << py << " | "
         << pz << " | "
         << std::endl;
   

 
    // number of mc particles
    mcNum++;

  } // loop over mc particle


}


