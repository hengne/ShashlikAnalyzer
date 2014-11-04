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

 private:

  TFile *histfile_;
  TTree *tree;
  
  // variables for the tree
  ULong64_t RunNum, EvtNum, LumNum;
  int NPV;
  double VtxXTrue, VtxYTrue, VtxZTrue;
  double VtxX, VtxY, VtxZ;
  
  int Nparts, Nelecs, Nphots;

  double ETrue[100], PtTrue[100], PxTrue[100], PyTrue[100], PzTrue[100];
  double EtaTrue[100], PhiTrue[100], ChargeTrue[100];
  int PDGTrue[100];
  int MomPDGTrue[100];
  int FoundGsf[100];
  

  double ESc[100], EtSc[100], EtaSc[100], PhiSc[100];
  double EScSeed[100], EtScSeed[100], EtaScSeed[100], PhiScSeed[100];

  double E[100], Pt[100], Px[100], Py[100], Pz[100], Eta[100], Phi[100], Charge[100];
  int PDG[100];
  bool isEB[100], isEE[100];

  double PTrackOut[100], PtTrackOut[100], PxTrackOut[100], PyTrackOut[100], PzTrackOut[100];
  double EtaTrackOut[100], PhiTrackOut[100];

  double PTrackIn[100], PtTrackIn[100], PxTrackIn[100], PyTrackIn[100], PzTrackIn[100];
  double EtaTrackIn[100], PhiTrackIn[100];

  std::string outputFile_;
  edm::InputTag electronCollection_;
  edm::InputTag  mcTruthCollection_;

  double deltaR_;
  std::vector<int> matchingIDs_;
  std::vector<int> matchingMotherIDs_;

 };

#endif



