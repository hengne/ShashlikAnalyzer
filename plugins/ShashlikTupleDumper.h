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


#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"

#include <vector>

class MagneticField;
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

 private:

  TrajectoryStateTransform transformer_;
  edm::ESHandle<TrackerGeometry> pDD;
  edm::ESHandle<MagneticField> theMagField;
  TFile *histfile_;
  TTree *tree_;
  float mcEnergy[10], mcEta[10], mcPhi[10], mcPt[10], mcQ[10];
  float superclusterEnergy[10], superclusterEta[10], superclusterPhi[10], superclusterEt[10];
  float seedMomentum[10], seedEta[10], seedPhi[10], seedPt[10], seedQ[10];

  std::string outputFile_;
  edm::InputTag electronCollection_;
  edm::InputTag  mcTruthCollection_;
  bool readAOD_;

  double maxPt_;
  double maxAbsEta_;
  double deltaR_;
  std::vector<int> matchingIDs_;
  std::vector<int> matchingMotherIDs_;

 };

#endif



