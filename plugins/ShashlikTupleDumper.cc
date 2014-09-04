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

using namespace reco;

ShashlikTupleDumper::ShashlikTupleDumper(const edm::ParameterSet& conf)
 {
  outputFile_ = conf.getParameter<std::string>("outputFile");
  histfile_ = new TFile(outputFile_.c_str(),"RECREATE");
  electronCollection_=conf.getParameter<edm::InputTag>("electronCollection");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");
  readAOD_ = conf.getParameter<bool>("readAOD");
  maxPt_ = conf.getParameter<double>("MaxPt");
  maxAbsEta_ = conf.getParameter<double>("MaxAbsEta");
  deltaR_ = conf.getParameter<double>("DeltaR");
  matchingIDs_ = conf.getParameter<std::vector<int> >("MatchingID");
  matchingMotherIDs_ = conf.getParameter<std::vector<int> >("MatchingMotherID");

 }

void ShashlikTupleDumper::beginJob(){

  histfile_->cd();

}

void
ShashlikTupleDumper::endJob(){

  histfile_->cd();

}

ShashlikAnalyzer::~ShashlikAnalyzer()
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
ShashlikAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get electrons

  edm::Handle<GsfElectronCollection> gsfElectrons;
  iEvent.getByLabel(electronCollection_,gsfElectrons);
  edm::LogInfo("")<<"\n\n =================> Treating event "<<iEvent.id()<<" Number of electrons "<<gsfElectrons.product()->size();

  edm::Handle<GenParticleCollection> genParticles;
  iEvent.getByLabel(mcTruthCollection_, genParticles);


  int mcNum=0, gamNum=0, eleNum=0;
  bool matchingID, matchingMotherID;

  // association mc-reco
  for (reco::GenParticleCollection::const_iterator mcIter=genParticles->begin(); mcIter != genParticles->end(); mcIter++ ) {

    // number of mc particles
    mcNum++;

    // counts photons
    if (mcIter->pdgId() == 22 ){ gamNum++; }

      // select requested matching gen particle
      matchingID=false;
      for (unsigned int i=0; i<matchingIDs_.size(); i++)
       if ( mcIter->pdgId() == matchingIDs_[i] ) matchingID=true;

      if (matchingID) {

      // select requested mother matching gen particle
      // always include single particle with no mother
      const Candidate * mother = mcIter->mother();
      matchingMotherID=false;
      for (unsigned int i=0; i<matchingMotherIDs_.size(); i++)
       if ((mother == 0) || ((mother != 0) &&  mother->pdgId() == matchingMotherIDs_[i]) ) matchingMotherID=true;

      if (matchingMotherID) {

      if (mcIter->pt()> maxPt_ || std::abs(mcIter->eta())> maxAbsEta_) continue;

      // suppress the endcaps
      //if (std::abs(mcIter->eta()) > 1.5) continue;
      // select central z
      //if ( std::abs(mcIter->production_vertex()->position().z())>50.) continue;

      eleNum++;
      // looking for the best matching gsf electron
      bool okGsfFound = false;
      double gsfOkRatio = 999999.;

      // find best matched electron
      reco::GsfElectron bestGsfElectron;
      for (reco::GsfElectronCollection::const_iterator gsfIter=gsfElectrons->begin();
       gsfIter!=gsfElectrons->end(); gsfIter++){

        double dphi = gsfIter->phi()-mcIter->phi();
        if (std::abs(dphi)>CLHEP::pi)
         dphi = dphi < 0? (CLHEP::twopi) + dphi : dphi - CLHEP::twopi;
    	double deltaR = sqrt(std::pow((gsfIter->eta()-mcIter->eta()),2) + std::pow(dphi,2));
	if ( deltaR < deltaR_ ){
	  if ( ( (mcIter->pdgId() == 11) && (gsfIter->charge() < 0.) ) ||
	       ( (mcIter->pdgId() == -11) && (gsfIter->charge() > 0.) ) )
	   {
	    double tmpGsfRatio = gsfIter->p()/mcIter->p();
	    if ( std::abs(tmpGsfRatio-1) < std::abs(gsfOkRatio-1) ) {
	      gsfOkRatio = tmpGsfRatio;
	      bestGsfElectron=*gsfIter;
	      okGsfFound = true;
	    }
	  }
	}
      } // loop over rec ele to look for the best one

      // analysis when the mc track is found
     if (okGsfFound){

      } // gsf electron found

    } // mc particle found

    }

  } // loop over mc particle


}


