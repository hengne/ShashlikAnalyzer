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
  electronCollection_=conf.getParameter<edm::InputTag>("electronCollection");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");
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
  tree->Branch("ETrue", ETrue,"ETrue[Nparts]/D");
  tree->Branch("PtTrue", PtTrue,"PtTrue[Nparts]/D");
  tree->Branch("PxTrue", PxTrue,"PxTrue[Nparts]/D");
  tree->Branch("PyTrue", PyTrue,"PyTrue[Nparts]/D");
  tree->Branch("PzTrue", PzTrue,"PzTrue[Nparts]/D");
  tree->Branch("EtaTrue", EtaTrue,"EtaTrue[Nparts]/D");
  tree->Branch("PhiTrue", PhiTrue,"PhiTrue[Nparts]/D");
  tree->Branch("ChargeTrue", ChargeTrue,"ChargeTrue[Nparts]/D");
  tree->Branch("PDGTrue", PDGTrue,"PDGTrue[Nparts]/I");
  tree->Branch("MomPDGTrue", MomPDGTrue,"MomPDGTrue[Nparts]/I");
  tree->Branch("FoundGsf", FoundGsf,"FoundGsf[Nparts]/I");
  tree->Branch("ESc", ESc,"ESc[Nparts]/D");
  tree->Branch("EtSc", EtSc,"EtSc[Nparts]/D");
  tree->Branch("EtaSc", EtaSc,"EtaSc[Nparts]/D");
  tree->Branch("PhiSc", PhiSc,"PhiSc[Nparts]/D");
  tree->Branch("EScSeed", EScSeed,"EScSeed[Nparts]/D");
  tree->Branch("EtScSeed", EtScSeed,"EtScSeed[Nparts]/D");
  tree->Branch("EtaScSeed", EtaScSeed,"EtaScSeed[Nparts]/D");
  tree->Branch("PhiScSeed", PhiScSeed,"PhiScSeed[Nparts]/D");
  tree->Branch("E", E,"E[Nparts]/D");
  tree->Branch("Pt", Pt,"Pt[Nparts]/D");
  tree->Branch("Px", Px,"Px[Nparts]/D");
  tree->Branch("Py", Py,"Py[Nparts]/D");
  tree->Branch("Pz", Pz,"Pz[Nparts]/D");
  tree->Branch("Eta", Eta,"Eta[Nparts]/D");
  tree->Branch("Phi", Phi,"Phi[Nparts]/D");
  tree->Branch("isEB", isEB,"isEB[Nparts]/O");
  tree->Branch("isEE", isEE,"isEE[Nparts]/O");
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
    ETrue[mcNum] = tenergy;
    PtTrue[mcNum] = tpt; 
    PxTrue[mcNum] = tpx;
    PyTrue[mcNum] = tpy;
    PzTrue[mcNum] = tpz;
    EtaTrue[mcNum] = teta;
    PhiTrue[mcNum] = tphi;
    ChargeTrue[mcNum] = tcharge;
    PDGTrue[mcNum] = tpdgid;
    MomPDGTrue[mcNum] = mother->pdgId();

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
      FoundGsf[mcNum] = 0;
      ESc[mcNum] = -100;
      EtSc[mcNum] = -100;
      EtaSc[mcNum] = -100;
      PhiSc[mcNum] = -100;
      EScSeed[mcNum] = -100;
      EtScSeed[mcNum] = -100;
      EtaScSeed[mcNum] = -100;
      PhiScSeed[mcNum] = -100;
      E[mcNum] = -100;
      Pt[mcNum] = -100;
      Px[mcNum] = -100;
      Py[mcNum] = -100;
      Pz[mcNum] = -100;
      Eta[mcNum] = -100;
      Phi[mcNum] = -100;
      Charge[mcNum] = -100;
      PDG[mcNum] = -100;
      isEB[mcNum] = false;
      isEE[mcNum] = false;
      PTrackOut[mcNum] = -100;
      PtTrackOut[mcNum] = -100;
      PxTrackOut[mcNum] = -100;
      PyTrackOut[mcNum] = -100;
      PzTrackOut[mcNum] = -100;
      EtaTrackOut[mcNum] = -100;
      PhiTrackOut[mcNum] = -100;
      PTrackIn[mcNum] = -100;
      PtTrackIn[mcNum] = -100;
      PxTrackIn[mcNum] = -100;
      PyTrackIn[mcNum] = -100;
      PzTrackIn[mcNum] = -100;
      EtaTrackIn[mcNum] = -100;
      PhiTrackIn[mcNum] = -100;     
      // skip the rests
      mcNum++;
      continue;
    }

    // otherwise found gsf
    FoundGsf[mcNum] = 1;
   
    // now fill the gsf electron info
    ESc[mcNum] = bestGsfElectron.superCluster()->energy();
    EtSc[mcNum] = bestGsfElectron.superCluster()->energy()/cosh(bestGsfElectron.superCluster()->eta());
    EtaSc[mcNum] = bestGsfElectron.superCluster()->eta();
    PhiSc[mcNum] = bestGsfElectron.superCluster()->phi();

    //
    E[mcNum] = bestGsfElectron.energy();
    Pt[mcNum] = bestGsfElectron.pt();
    Px[mcNum] = bestGsfElectron.px();
    Py[mcNum] = bestGsfElectron.py();
    Pz[mcNum] = bestGsfElectron.pz();
    Eta[mcNum] = bestGsfElectron.eta();
    Phi[mcNum] = bestGsfElectron.phi();
    isEB[mcNum] = bestGsfElectron.isEB();
    isEE[mcNum] = bestGsfElectron.isEE(); 
    Charge[mcNum] = (double)bestGsfElectron.charge();
    PDG[mcNum] = bestGsfElectron.pdgId();
 
    reco::GsfTrackRef gsfTrack = bestGsfElectron.gsfTrack();
    if (!gsfTrack) 
    {
      PTrackOut[mcNum] = -100;
      PtTrackOut[mcNum] = -100;
      PxTrackOut[mcNum] = -100;
      PyTrackOut[mcNum] = -100;
      PzTrackOut[mcNum] = -100;
      EtaTrackOut[mcNum] = -100;
      PhiTrackOut[mcNum] = -100;
      PTrackIn[mcNum] = -100;
      PtTrackIn[mcNum] = -100;
      PxTrackIn[mcNum] = -100;
      PyTrackIn[mcNum] = -100;
      PzTrackIn[mcNum] = -100;
      EtaTrackIn[mcNum] = -100;
      PhiTrackIn[mcNum] = -100;
      EScSeed[mcNum] = -100;
      EtScSeed[mcNum] = -100;
      EtaScSeed[mcNum] = -100;
      PhiScSeed[mcNum] = -100;
      mcNum++;
      continue;
    }

   
    PTrackOut[mcNum] = gsfTrack->outerMomentum().R();
    PtTrackOut[mcNum] = gsfTrack->outerMomentum().Rho();
    PxTrackOut[mcNum] = gsfTrack->outerMomentum().X();
    PyTrackOut[mcNum] = gsfTrack->outerMomentum().Y();
    PzTrackOut[mcNum] = gsfTrack->outerMomentum().Z();
    EtaTrackOut[mcNum] = gsfTrack->outerMomentum().eta();
    PhiTrackOut[mcNum] = gsfTrack->outerMomentum().phi();
    PTrackIn[mcNum] = gsfTrack->innerMomentum().R();
    PtTrackIn[mcNum] = gsfTrack->innerMomentum().Rho();
    PxTrackIn[mcNum] = gsfTrack->innerMomentum().X();
    PyTrackIn[mcNum] = gsfTrack->innerMomentum().Y();
    PzTrackIn[mcNum] = gsfTrack->innerMomentum().Z();
    EtaTrackIn[mcNum] = gsfTrack->innerMomentum().eta();
    PhiTrackIn[mcNum] = gsfTrack->innerMomentum().phi();


    // number of mc particles
    mcNum++;

  } // loop over mc particle


  Nparts = mcNum;
  tree->Fill();
  
}


