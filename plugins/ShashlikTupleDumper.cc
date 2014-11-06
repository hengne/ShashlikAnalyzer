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
#include"SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

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
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");
  barrelRecHitCollection_ = conf.getParameter<edm::InputTag>("barrelRecHitCollection");
  endcapRecHitCollection_ = conf.getParameter<edm::InputTag>("endcapRecHitCollection");
  deltaR_ = conf.getParameter<double>("DeltaR");
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
  // get electrons

  edm::Handle<reco::GsfElectronCollection> gsfElectrons;
  iEvent.getByLabel(electronCollection_,gsfElectrons);
  edm::LogInfo("")<<"\n\n =================> Treating event "<<iEvent.id()<<" Number of electrons "<<gsfElectrons.product()->size();

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(mcTruthCollection_, genParticles);

  edm::Handle<EcalRecHitCollection> barrelRecHits ;
  iEvent.getByLabel(barrelRecHitCollection_,barrelRecHits);

  edm::Handle<EcalRecHitCollection> endcapRecHits ;
  iEvent.getByLabel(endcapRecHitCollection_,endcapRecHits);

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;
  NPV = -1;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) 
  {
    int BX = PVI->getBunchCrossing();
    if(BX == 0)
    {
      NPV = PVI->getTrueNumInteractions();
      continue;
    }
  }

  // clear tree brach vectors
  clearTreeBranchVectors();  

  int mcNum=0;
  bool matchingMotherID;

  // print 
  //std::cout << " MC info: id | pdgid | status | charge | mass | energy | pt | px | py | pz | " << std::endl;

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
    //double tp = mcIter->p();
    double teta = mcIter->eta();
    double tphi = mcIter->phi();
    double tenergy = mcIter->energy();
    //double tmass =  mcIter->mass();
    int tpdgid = mcIter->pdgId();
    int tstatus = mcIter->status();
    //double tvx = mcIter->vx();
    //double tvy = mcIter->vy();
    //double tvz = mcIter->vz();
    //std::cout << "   " << mcNum << " | "
    //     << tpdgid << " | "
    //     << tstatus << " | "
    //     << tcharge << " | "
    //     << tmass << " | "
    //     << tenergy << " | "
    //     << tpt << " | "
    //     << tpx << " | "
    //     << tpy << " | "
    //     << tpz << " | "
    //     << std::endl;

    
    // only use gen status ==1
    if (tstatus!=1) continue;

    // only select electrons
    if (abs(tpdgid)!=11) continue;

    // select requested mother matching gen particle
    // always include single particle with no mother
    const reco::Candidate * mother = mcIter->mother();
    //matchingMotherID=false;
    matchingMotherID=true;
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
    double gsfOkRatio = 999999.;

    // find best matched electron
    reco::GsfElectron bestGsfElectron;
    for (reco::GsfElectronCollection::const_iterator gsfIter=gsfElectrons->begin();
         gsfIter!=gsfElectrons->end(); gsfIter++)
    {
      double dphi = gsfIter->phi()-mcIter->phi();
      if (std::abs(dphi)>CLHEP::pi) 
      {  dphi = dphi < 0? (CLHEP::twopi) + dphi : dphi - CLHEP::twopi; }

      double deltaR = sqrt(std::pow((gsfIter->eta()-mcIter->eta()),2) + std::pow(dphi,2));
      if ( deltaR < deltaR_ )
      {
        if ( ( (mcIter->pdgId() == 11) && (gsfIter->charge() < 0.) ) ||
             ( (mcIter->pdgId() == -11) && (gsfIter->charge() > 0.) ) )
        {
          double tmpGsfRatio = gsfIter->p()/mcIter->p();
          if ( std::abs(tmpGsfRatio-1) < std::abs(gsfOkRatio-1) ) 
          {
            gsfOkRatio = tmpGsfRatio;
            bestGsfElectron=*gsfIter;
            okGsfFound = true;
          }
        }
      }
    } // loop over rec ele to look for the best one    
   
    // only book truth if gsf is not found
    if (!okGsfFound) 
    {
      FoundGsf.push_back(0);
      ESc.push_back(-100);
      EScRaw.push_back(-100);
      EtSc.push_back(-100);
      EtaSc.push_back(-100);
      PhiSc.push_back(-100);
      EScSeed.push_back(-100);
      EtScSeed.push_back(-100);
      EtaScSeed.push_back(-100);
      PhiScSeed.push_back(-100);
      E.push_back(-100);
      Pt.push_back(-100);
      Px.push_back(-100);
      Py.push_back(-100);
      Pz.push_back(-100);
      Eta.push_back(-100);
      Phi.push_back(-100);
      Charge.push_back(-100);
      PDG.push_back(-100);
      isEB.push_back(false);
      isEE.push_back(false);
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
      // skip the rests
      mcNum++;
      continue;
    }

    // otherwise found gsf
    FoundGsf.push_back(1);
         
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


