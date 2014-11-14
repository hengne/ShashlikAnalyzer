{
  char* tag = 
   //  "ShashlikTupleDumper_RelValSingleElectronPt35Extended_DES23_62_V1_UPG2023SHNoTaper-v1"
   //  "ShashlikTupleDumper_RelValZEE_14TeV_GEN-SIM-RECO_DES23_62_V1_UPG2023SHNoTaper-v1"
      "Ntuple_DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola_test3"
  ;

  char name[1000];
  sprintf(name, "%s.root", tag);
  TFile* file = TFile::Open(name);
  TTree* tree = (TTree*)file->Get("tree");
  sprintf(name, "plots_%s.root", tag);
  TFile* fileout = TFile::Open(name, "RECREATE");
  gROOT->ProcessLine(".L tdrStyle.C");
  tdrstyle();
  //gROOT->SetStyle("Plain");

  TH1D* h1;
  TH1D* h2;
  TH1D* h3;
  TH1D* h4;
  TH1D* h5;
  TH1D* h6;
 
  TH2D* h2d1;
  TH2D* h2d2;
  TH2D* h2d3;
  TH2D* h2d4;
  TH2D* h2d5;
  TH2D* h2d6;

  TProfile* p1;
  TProfile* p2;
  TProfile* p3;
  TProfile* p4;
  TProfile* p5;
  TProfile* p6;

  TH3D* h3d1;
  TH3D* h3d2;
  TH3D* h3d3;
  TH3D* h3d4;

  TH1D* ha1[100];
  TH1D* ha2[100];
  TH1D* ha3[100];
  TH1D* ha4[100];
  TH1D* ha5[100];
  TH1D* ha6[100];

  TLegend* lg;

  TCanvas* plots = new TCanvas("plots", "plots", 400, 400);
  sprintf(name, "plots_%s.ps[", tag);
  plots->Print(name);

  // PtTrue
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PtTrue>>h1", "abs(EtaTrue)<1.5");
  tree->Draw("PtTrue>>h2", "abs(EtaTrue)>1.5");
  h1->SetName("ElePtTrueEB");
  h2->SetName("ElePtTrueEE");
  h1->SetTitle("Electron True Pt");
  h2->SetTitle("Electron True Pt");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Pt true (GeV)");
  h2->GetXaxis()->SetTitle("Pt true (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_PtTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // ETrue
  h1 = new TH1D("h1", "h1", 100, 0, 300);
  h2 = new TH1D("h2", "h2", 100, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("ETrue>>h1", "abs(EtaTrue)<1.5");
  tree->Draw("ETrue>>h2", "abs(EtaTrue)>1.5");
  h1->SetName("EleETrueEB");
  h2->SetName("EleETrueEE");
  h1->SetTitle("Electron True Energy");
  h2->SetTitle("Electron True Energy");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("E true (GeV)");
  h2->GetXaxis()->SetTitle("E true (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_ETrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrue
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtaTrue>>h1", "abs(EtaTrue)<1.5");
  tree->Draw("EtaTrue>>h2", "abs(EtaTrue)>1.5");
  h1->SetName("EleEtaTrueEB");
  h2->SetName("EleEtaTrueEE");
  h1->SetTitle("Electron True Eta");
  h2->SetTitle("Electron True Eta");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Eta True");
  h2->GetXaxis()->SetTitle("Eta True");

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_EtaTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // Eff vs Eta
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h3 = new TH1D("h3", "h3", 100, -5, 5);
  h4 = new TH1D("h4", "h4", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  tree->Draw("EtaTrue>>h1", "abs(EtaTrue)<1.5");
  tree->Draw("EtaTrue>>h2", "abs(EtaTrue)>1.5");
  tree->Draw("EtaTrue>>h3", "abs(EtaTrue)<1.5&&FoundGsf");
  tree->Draw("EtaTrue>>h4", "abs(EtaTrue)>1.5&&FoundGsf");
  h3->Divide(h1);
  h4->Divide(h2);
  h3->SetName("EleEffEtaTrueEB");
  h4->SetName("EleEffEtaTrueEE");
  h3->SetTitle("Electron Gsf Finding Efficiency vs True Eta");
  h4->SetTitle("Electron Gsf Finding Efficiency vs True Eta");
  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("Eta True");
  h4->GetXaxis()->SetTitle("Eta True");
  //h3->GetYaxis()->SetRangeUser(0.9, 1.1);
  //h4->GetYaxis()->SetRangeUser(0.9, 1.1);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_EffEtaTrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h3->Write();
  h4->Write();
  lg->Write();  

  // Et sc 
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtSc>>h1", "isEB&&FoundGsf");
  tree->Draw("EtSc>>h2", "isEE&&FoundGsf");
  h1->SetName("EleEtScEB");
  h2->SetName("EleEtScEE");
  h1->SetTitle("Electron SuperCluster Et");
  h2->SetTitle("Electron SuperCluster Et");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4); 
  h1->GetXaxis()->SetTitle("Et (GeV)");
  h2->GetXaxis()->SetTitle("Et (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_EtSc");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  
  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // E SC
  h1 = new TH1D("h1", "h1", 100, 0, 300);
  h2 = new TH1D("h2", "h2", 100, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("ESc>>h1", "isEB&&FoundGsf");
  tree->Draw("ESc>>h2", "isEE&&FoundGsf");
  h1->SetName("EleEScEB");
  h2->SetName("EleEScEE");
  h1->SetTitle("Electron SuperCluster Energy");
  h2->SetTitle("Electron SuperCluster Energy");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("E (GeV)");
  h2->GetXaxis()->SetTitle("E (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_EtSc");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();
  
  // eta sc
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtaSc>>h1", "isEB&&FoundGsf");
  tree->Draw("EtaSc>>h2", "isEE&&FoundGsf");
  h1->SetName("EleEtaScEB");
  h2->SetName("EleEtaScEE");
  h1->SetTitle("Electron SuperCluster Eta");
  h2->SetTitle("Electron SuperCluster Eta");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Eta");
  h2->GetXaxis()->SetTitle("Eta");

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_EtaSc");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();  
 

  // PtTrackIn
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PtTrackIn>>h1", "isEB&&FoundGsf");
  tree->Draw("PtTrackIn>>h2", "isEE&&FoundGsf");
  h1->SetName("ElePtTrackInEB");
  h2->SetName("ElePtTrackInEE");
  h1->SetTitle("Electron Pt Track In");
  h2->SetTitle("Electron Pt Track In");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Pt Track In (GeV)");
  h2->GetXaxis()->SetTitle("Pt Track In (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_PtTrackIn");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // PTrackIn
  h1 = new TH1D("h1", "h1", 100, 0, 300);
  h2 = new TH1D("h2", "h2", 100, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PTrackIn>>h1", "isEB&&FoundGsf");
  tree->Draw("PTrackIn>>h2", "isEE&&FoundGsf");
  h1->SetName("ElePTrackInEB");
  h2->SetName("ElePTrackInEE");
  h1->SetTitle("Electron Track P In");
  h2->SetTitle("Electron Track P In");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("P TrackIn (GeV)");
  h2->GetXaxis()->SetTitle("P TrackIn (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_PTrackIn");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrackIn
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtaTrackIn>>h1", "isEB&&FoundGsf");
  tree->Draw("EtaTrackIn>>h2", "isEE&&FoundGsf");
  h1->SetName("EleEtaTrackInEB");
  h2->SetName("EleEtaTrackInEE");
  h1->SetTitle("Electron Track Eta In");
  h2->SetTitle("Electron Track Eta In");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Eta Track");
  h2->GetXaxis()->SetTitle("Eta Track");

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_EtaTrackIn");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // PtTrackOut
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PtTrackOut>>h1", "isEB&&FoundGsf");
  tree->Draw("PtTrackOut>>h2", "isEE&&FoundGsf");
  h1->SetName("ElePtTrackOutEB");
  h2->SetName("ElePtTrackOutEE");
  h1->SetTitle("Electron Pt TrackOut");
  h2->SetTitle("Electron Pt TrackOut");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Pt TrackOut (GeV)");
  h2->GetXaxis()->SetTitle("Pt TrackOut (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_PtTrackOut");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // PTrackOut
  h1 = new TH1D("h1", "h1", 100, 0, 300);
  h2 = new TH1D("h2", "h2", 100, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PTrackOut>>h1", "isEB&&FoundGsf");
  tree->Draw("PTrackOut>>h2", "isEE&&FoundGsf");
  h1->SetName("ElePTrackOutEB");
  h2->SetName("ElePTrackOutEE");
  h1->SetTitle("Electron Track P In");
  h2->SetTitle("Electron Track P In");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("P TrackOut (GeV)");
  h2->GetXaxis()->SetTitle("P TrackOut (GeV)");

  lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetName("lg_PTrackOut");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrackOut
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtaTrackOut>>h1", "isEB&&FoundGsf");
  tree->Draw("EtaTrackOut>>h2", "isEE&&FoundGsf");
  h1->SetName("EleEtaTrackOutEB");
  h2->SetName("EleEtaTrackOutEE");
  h1->SetTitle("Electron Eta TrackOut");
  h2->SetTitle("Electron Eta TrackOut");
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Eta TrackOut");
  h2->GetXaxis()->SetTitle("Eta TrackOut");

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_EtaTrackOut");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // ESc/ETrue vs ETrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, 0, 300, 200,0.5,1.5);
  h2d2 = new TH2D("h2d2", "h2d2", 30, 0, 300, 200,0.5,1.5);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("ESc/ETrue:ETrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("ESc/ETrue:ETrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("EleEScOETrueVsETrueEB");
  h2d2->SetName("EleEScOETrueVsETrueEE");
  h2d1->SetTitle("Electron SuperCluster Energy Response vs True Energy EB");
  h2d2->SetTitle("Electron SuperCluster Energy Response vs True Energy EE");
  h2d1->GetXaxis()->SetTitle("E true (GeV)");
  h2d2->GetXaxis()->SetTitle("E true (GeV)");
  h2d1->GetYaxis()->SetTitle("ESc/ETrue");
  h2d2->GetYaxis()->SetTitle("ESc/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(ESc/Etrue) vs. ETrue and  RMS(ESc/Etrue) vs. Etrue
  h1 = new TH1D("h1", "h1", 30, 0, 300);
  h2 = new TH1D("h2", "h2", 30, 0, 300);
  h3 = new TH1D("h3", "h3", 30, 0, 300);
  h4 = new TH1D("h4", "h4", 30, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("MeanEScOETrueVsETrueEB");  
  h2->SetName("MeanEScOETrueVsETrueEE");  
  h3->SetName("RMSEScOETrueVsETrueEB");  
  h4->SetName("RMSEScOETrueVsETrueEE");  
  h1->SetTitle("Mean ESC/ETrue vs. ETrue");
  h2->SetTitle("Mean ESC/ETrue vs. ETrue");
  h3->SetTitle("RMS ESC/ETrue vs. ETrue");
  h4->SetTitle("RMS ESC/ETrue vs. ETrue");


  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    TH1D* hist = h2d1->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS(); 
    double rmserr = hist->GetRMSError();
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
  }
  
  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    TH1D* hist = (TH1D*)h2d2->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
  }
 
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("ETrue (GeV)");
  h2->GetXaxis()->SetTitle("ETrue (GeV)");
  h1->GetYaxis()->SetTitle("Mean ESc/ETrue");
  h2->GetYaxis()->SetTitle("Mean ESc/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);
 

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_MeanEScOETrueVsETrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  
  h1->Write();
  h2->Write();
  lg->Write();


  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("ETrue (GeV)");
  h4->GetXaxis()->SetTitle("ETrue (GeV)");
  h3->GetYaxis()->SetTitle("RMS ESc/ETrue");
  h4->GetYaxis()->SetTitle("RMS ESc/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.2);
  h4->GetYaxis()->SetRangeUser(0.0, 0.2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_RMSEScOETrueVsETrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();


  TF1* fgaus = new TF1("fgaus", "gaus", 0,3);

  // mu (ESc/Etrue) vs. ETrue and  sigma(ESc/Etrue) vs. Etrue
  h1 = new TH1D("h1", "h1", 30, 0, 300);
  h2 = new TH1D("h2", "h2", 30, 0, 300);
  h3 = new TH1D("h3", "h3", 30, 0, 300);
  h4 = new TH1D("h4", "h4", 30, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("GausMeanEScOETrueVsETrueEB");
  h2->SetName("GausMeanEScOETrueVsETrueEE");
  h3->SetName("GausSigmaEScOETrueVsETrueEB");
  h4->SetName("GausSigmaEScOETrueVsETrueEE");
  h1->SetTitle("Gaus Mean ESC/ETrue vs. ETrue");
  h2->SetTitle("Gaus Mean ESC/ETrue vs. ETrue");
  h3->SetTitle("Gaus Sigma ESC/ETrue vs. ETrue");
  h4->SetTitle("Gaus Sigma ESC/ETrue vs. ETrue");


  plots->Clear();
  plots->cd(0);
  plots->Divide(6,5);
  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hESciOETrueEB_ETrueBin%d", ii);
    TH1D* hist = h2d1->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hESciOETrueEB_ETrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    //hist->Fit(func);
    //double m = func->GetParameter(1);
    //double rms = func->GetParameter(2);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);

    hist->Draw();
    hist->Write();
    func->Write();
  }
  plots->cd(0);
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();


  plots->Clear();
  plots->Divide(6,5);
  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hESciOETrueEE_ETrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d2->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hESciOETrueEE_ETrueBin%d", ii);
    //TF1* func = new TF1(name, "gaus", 0,3);
    //double m = func->GetParameter(1);
    //double rms = func->GetParameter(2);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("ETrue (GeV)");
  h2->GetXaxis()->SetTitle("ETrue (GeV)");
  h1->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  h2->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausMeanEScOETrueVsETrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("ETrue (GeV)");
  h4->GetXaxis()->SetTitle("ETrue (GeV)");
  h3->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  h4->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.06);
  h4->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausSigmaEScOETrueVsETrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();


  // ESc/ETrue vs EtaTrue
  h2d1 = new TH2D("h2d1", "h2d1", 60, -3, 3, 200,0.5,1.5);
  h2d2 = new TH2D("h2d2", "h2d2", 60, -3, 3, 200,0.5,1.5);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("ESc/ETrue:EtaTrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("ESc/ETrue:EtaTrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("EleEScOETrueVsEtaTrueEB");
  h2d2->SetName("EleEScOETrueVsEtaTrueEE");
  h2d1->SetTitle("Electron SuperCluster Energy Response vs EtaTrue EB");
  h2d2->SetTitle("Electron SuperCluster Energy Response vs EtaTrue EE");
  h2d1->GetXaxis()->SetTitle("EtaTrue");
  h2d2->GetXaxis()->SetTitle("EtaTrue");
  h2d1->GetYaxis()->SetTitle("ESc/ETrue");
  h2d2->GetYaxis()->SetTitle("ESc/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(ESc/Etrue) vs. EtaTrue and  RMS(ESc/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 60, -3, 3);
  h2 = new TH1D("h2", "h2", 60, -3, 3);
  h3 = new TH1D("h3", "h3", 60, -3, 3);
  h4 = new TH1D("h4", "h4", 60, -3, 3);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("MeanEScOETrueVsEtaTrueEB");
  h2->SetName("MeanEScOETrueVsEtaTrueEE");
  h3->SetName("RMSEScOETrueVsEtaTrueEB");
  h4->SetName("RMSEScOETrueVsEtaTrueEE");
  h1->SetTitle("Mean ESC/ETrue vs. EtaTrue");
  h2->SetTitle("Mean ESC/ETrue vs. EtaTrue");
  h3->SetTitle("RMS ESC/ETrue vs. EtaTrue");
  h4->SetTitle("RMS ESC/ETrue vs. EtaTrue");


  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    TH1D* hist = h2d1->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
  }

  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    TH1D* hist = (TH1D*)h2d2->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
  }

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("EtaTrue");
  h2->GetXaxis()->SetTitle("EtaTrue");
  h1->GetYaxis()->SetTitle("Mean ESc/ETrue");
  h2->GetYaxis()->SetTitle("Mean ESc/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_MeanEScOETrueVsEtaTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("EtaTrue");
  h4->GetXaxis()->SetTitle("EtaTrue");
  h3->GetYaxis()->SetTitle("RMS ESc/ETrue");
  h4->GetYaxis()->SetTitle("RMS ESc/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.2);
  h4->GetYaxis()->SetRangeUser(0.0, 0.2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_RMSEScOETrueVsEtaTrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();

  // Gaus Mean(ESc/Etrue) vs. EtaTrue and Gaus Sigma (ESc/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 60, -3, 3);
  h2 = new TH1D("h2", "h2", 60, -3, 3);
  h3 = new TH1D("h3", "h3", 60, -3, 3);
  h4 = new TH1D("h4", "h4", 60, -3, 3);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("GausMeanEScOETrueVsEtaTrueEB");
  h2->SetName("GausMeanEScOETrueVsEtaTrueEE");
  h3->SetName("GausSigmaEScOETrueVsEtaTrueEB");
  h4->SetName("GausSigmaEScOETrueVsEtaTrueEE");
  h1->SetTitle("Gaus Mean ESC/ETrue vs. EtaTrue");
  h2->SetTitle("Gaus Mean ESC/ETrue vs. EtaTrue");
  h3->SetTitle("Gaus Sigma ESC/ETrue vs. EtaTrue");
  h4->SetTitle("Gaus Sigma ESC/ETrue vs. EtaTrue");


  plots->Clear();
  plots->cd(0);
  plots->Divide(10,6);
  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hESciOETrueEB_EtaTrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d1->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hESciOETrueEB_EtaTrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  plots->Clear();
  plots->cd(0);
  plots->Divide(10,6);
  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hESciOETrueEE_EtaTrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d2->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hESciOETrueEE_EtaTrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("EtaTrue");
  h2->GetXaxis()->SetTitle("EtaTrue");
  h1->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  h2->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausMeanEScOETrueVsEtaTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("EtaTrue");
  h4->GetXaxis()->SetTitle("EtaTrue");
  h3->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  h4->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.06);
  h4->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GuasSigmaEScOETrueVsEtaTrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();

  // PTrackIn/ETrue vs ETrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, 0, 300, 300,0,3);
  h2d2 = new TH2D("h2d2", "h2d2", 30, 0, 300, 300,0,3);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("PTrackIn/ETrue:ETrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("PTrackIn/ETrue:ETrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("ElePTrackInOETrueVsETrueEB");
  h2d2->SetName("ElePTrackInOETrueVsETrueEE");
  h2d1->SetTitle("Electron Track Momentum Response vs True Energy EB");
  h2d2->SetTitle("Electron Track Momentum Response vs True Energy EE");
  h2d1->GetXaxis()->SetTitle("E true (GeV)");
  h2d2->GetXaxis()->SetTitle("E true (GeV)");
  h2d1->GetYaxis()->SetTitle("PTrackIn/ETrue");
  h2d2->GetYaxis()->SetTitle("PTrackIn/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(PTrackIn/Etrue) vs. ETrue and  RMS(PTrackIn/Etrue) vs. Etrue
  h1 = new TH1D("h1", "h1", 30, 0, 300);
  h2 = new TH1D("h2", "h2", 30, 0, 300);
  h3 = new TH1D("h3", "h3", 30, 0, 300);
  h4 = new TH1D("h4", "h4", 30, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("MeanPTrackInOETrueVsETrueEB");
  h2->SetName("MeanPTrackInOETrueVsETrueEE");
  h3->SetName("RMSPTrackInOETrueVsETrueEB");
  h4->SetName("RMSPTrackInOETrueVsETrueEE");
  h1->SetTitle("Mean PTrackIn/ETrue vs. ETrue");
  h2->SetTitle("Mean PTrackIn/ETrue vs. ETrue");
  h3->SetTitle("RMS PTrackIn/ETrue vs. ETrue");
  h4->SetTitle("RMS PTrackIn/ETrue vs. ETrue");


  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    TH1D* hist = h2d1->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
  }

  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    TH1D* hist = (TH1D*)h2d2->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
  }

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("ETrue (GeV)");
  h2->GetXaxis()->SetTitle("ETrue (GeV)");
  h1->GetYaxis()->SetTitle("Mean PTrackIn/ETrue");
  h2->GetYaxis()->SetTitle("Mean PTrackIn/ETrue");
  h1->GetYaxis()->SetRangeUser(0., 2);
  h2->GetYaxis()->SetRangeUser(0., 2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_MeanPTrackInOETrueVsETrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("ETrue (GeV)");
  h4->GetXaxis()->SetTitle("ETrue (GeV)");
  h3->GetYaxis()->SetTitle("RMS PTrackIn/ETrue");
  h4->GetYaxis()->SetTitle("RMS PTrackIn/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 2);
  h4->GetYaxis()->SetRangeUser(0.0, 2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_RMSPTrackInOETrueVsETrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();

  // PTrackIn/ETrue vs EtaTrue
  h2d1 = new TH2D("h2d1", "h2d1", 100, -5, 5, 300,0,3);
  h2d2 = new TH2D("h2d2", "h2d2", 100, -5, 5, 300,0,3);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("PTrackIn/ETrue:EtaTrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("PTrackIn/ETrue:EtaTrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("ElePTrackInOETrueVsEtaTrueEB");
  h2d2->SetName("ElePTrackInOETrueVsEtaTrueEE");
  h2d1->SetTitle("Electron Track Momentum Response vs EtaTrue EB");
  h2d2->SetTitle("Electron Track Momentum Response vs EtaTrue EE");
  h2d1->GetXaxis()->SetTitle("EtaTrue");
  h2d2->GetXaxis()->SetTitle("EtaTrue");
  h2d1->GetYaxis()->SetTitle("PTrackIn/ETrue");
  h2d2->GetYaxis()->SetTitle("PTrackIn/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(PTrackIn/Etrue) vs. EtaTrue and  RMS(PTrackIn/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 100, -5, 5);
  h2 = new TH1D("h2", "h2", 100, -5, 5);
  h3 = new TH1D("h3", "h3", 100, -5, 5);
  h4 = new TH1D("h4", "h4", 100, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("MeanPTrackInOETrueVsEtaTrueEB");
  h2->SetName("MeanPTrackInOETrueVsEtaTrueEE");
  h3->SetName("RMSPTrackInOETrueVsEtaTrueEB");
  h4->SetName("RMSPTrackInOETrueVsEtaTrueEE");
  h1->SetTitle("Mean ESC/ETrue vs. EtaTrue");
  h2->SetTitle("Mean ESC/ETrue vs. EtaTrue");
  h3->SetTitle("RMS ESC/ETrue vs. EtaTrue");
  h4->SetTitle("RMS ESC/ETrue vs. EtaTrue");


  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    TH1D* hist = h2d1->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
  }

  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    TH1D* hist = (TH1D*)h2d2->ProjectionY("hist", ii, ii, "e");
    double m = hist->GetMean();
    double merr = hist->GetMeanError();
    double rms = hist->GetRMS();
    double rmserr = hist->GetRMSError();
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
  }

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("EtaTrue");
  h2->GetXaxis()->SetTitle("EtaTrue");
  h1->GetYaxis()->SetTitle("Mean PTrackIn/ETrue");
  h2->GetYaxis()->SetTitle("Mean PTrackIn/ETrue");
  h1->GetYaxis()->SetRangeUser(0., 2);
  h2->GetYaxis()->SetRangeUser(0., 2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_MeanPTrackInOETrueVsEtaTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("EtaTrue");
  h4->GetXaxis()->SetTitle("EtaTrue");
  h3->GetYaxis()->SetTitle("RMS PTrackIn/ETrue");
  h4->GetYaxis()->SetTitle("RMS PTrackIn/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 2);
  h4->GetYaxis()->SetRangeUser(0.0, 2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_RMSPTrackInOETrueVsEtaTrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();



  // ESc/ETrue vs ETrue vs. EtaTrue
  h3d1 = new TH3D("h3d1", "h3d1", 3,0.0,1.5, 10, 0, 300, 200,0.5,1.5);
  h3d2 = new TH3D("h3d2", "h3d2", 3,1.5,3.0, 10, 0, 300, 200,0.5,1.5);
  h3d1->Sumw2();
  h3d2->Sumw2();
  tree->Draw("ESc/ETrue:ETrue:abs(EtaTrue)>>h3d1", "isEB&&FoundGsf");
  tree->Draw("ESc/ETrue:ETrue:abs(EtaTrue)>>h3d2", "isEE&&FoundGsf");
  h3d1->SetName("EleEScOETrueVsETrueVsEtaTrueEB");
  h3d2->SetName("EleEScOETrueVsETrueVsEtaTrueEE");
  h3d1->SetTitle("Electron SuperCluster Energy Response vs True Energy vs Eta True EB");
  h3d2->SetTitle("Electron SuperCluster Energy Response vs True Energy vs Eta True EE");
  h3d1->GetXaxis()->SetTitle("EtaTrue");
  h3d2->GetXaxis()->SetTitle("EtaTrue");
  h3d1->GetYaxis()->SetTitle("E true (GeV)");
  h3d2->GetYaxis()->SetTitle("E true (GeV)");
  h3d1->GetZaxis()->SetTitle("ESc/ETrue");
  h3d2->GetZaxis()->SetTitle("ESc/ETrue");
  h3d1->SetMarkerStyle(1);
  h3d2->SetMarkerStyle(1);

  plots->Clear();
  h3d1->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h3d1->Write();

  plots->Clear();
  h3d2->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h3d2->Write();

  // Gaus Mean (ESc/Etrue) vs. ETrue and Gaus Sigma (ESc/Etrue) vs. ETrue in bins of EtaTrue
  // EB
  for (int ieta=1; ieta<=(int)h3d1->GetNbinsX(); ieta++)
  {
    ha1[ieta-1] = new TH1D("h1", "h1", 10, 0, 300);
    ha2[ieta-1] = new TH1D("h2", "h2", 10, 0, 300);
    ha1[ieta-1]->Sumw2();
    ha2[ieta-1]->Sumw2();
    sprintf(name, "GausMeanEScOETrueVsETrueEB_EtaTrueBin%d", ieta);
    ha1[ieta-1]->SetName(name);
    sprintf(name, "GausSigmaEScOETrueVsETrueEB_EtaTrueBin%d", ieta);
    ha2[ieta-1]->SetName(name);
    sprintf(name, "Gaus Mean ESC/ETrue vs. ETrue for EB in EtaTrueBins");
    ha1[ieta-1]->SetTitle(name);
    sprintf(name, "Gaus Sigma ESC/ETrue vs. ETrue for EB in EtaTrueBins");
    ha2[ieta-1]->SetTitle(name);

    // EB
    plots->Clear();
    plots->cd(0);
    plots->Divide(6,5);
    for (int ie=1; ie<=(int)ha1[ieta-1]->GetNbinsX(); ie++)
    {
      plots->cd(ie);
      sprintf(name, "hESciOETrueEB_EtaTrueBin%d_ETrueBin%d", ieta, ie);
      TH1D* hist = (TH1D*)h3d1->ProjectionZ(name, ieta, ieta, ie, ie, "e");
      sprintf(name, "hESciOETrueEB_EtaTrueBin%d_ETrueBin%d %.2f < EtaTrue < %.2f", ieta, ie, h3d1->GetXaxis()->GetBinLowEdge(ieta), h3d1->GetXaxis()->GetBinUpEdge(ieta));
      hist->SetTitle(name);
      hist->SetMarkerStyle(1);
      if (hist->GetEntries()<3) continue;
      sprintf(name, "fgaus_hESciOETrueEB_EtaTrueBin%d_ETrueBin%d", ieta, ie);
      TF1* func = new TF1(name, "gaus", 0,3);
      double m = hist->GetMean();
      double rms = hist->GetRMS();
      hist->Fit(func, "R", "", m-3*rms, m+3*rms);
      m = func->GetParameter(1);
      rms = func->GetParameter(2);
      double merr = func->GetParError(1);
      double rmserr = func->GetParError(2);
      if (rms>hist->GetRMS())
      {
        m = hist->GetMean();
        merr = hist->GetMeanError();
        rms = hist->GetRMS();
        rmserr = hist->GetRMSError();
      }
      ha1[ieta-1]->SetBinContent(ie, m);
      ha1[ieta-1]->SetBinError(ie, merr);
      ha2[ieta-1]->SetBinContent(ie, rms);
      ha2[ieta-1]->SetBinError(ie, rmserr);

      hist->Draw();
      hist->Write();
      func->Write();
    }
    plots->cd(0);
    sprintf(name, "plots_%s.ps", tag);
    plots->Print(name);
    plots->Clear();
  }



  //EE
  for (int ieta=1; ieta<=(int)h3d2->GetNbinsX(); ieta++)
  {
    ha3[ieta-1] = new TH1D("h3", "h3", 10, 0, 300);
    ha4[ieta-1] = new TH1D("h4", "h4", 10, 0, 300);
    ha3[ieta-1]->Sumw2();
    ha4[ieta-1]->Sumw2();
    sprintf(name, "GausMeanEScOETrueVsETrueEE_EtaTrueBin%d", ieta);
    ha3[ieta-1]->SetName(name);
    sprintf(name, "GausSigmaEScOETrueVsETrueEE_EtaTrueBin%d", ieta);
    ha4[ieta-1]->SetName(name);
    sprintf(name, "Gaus Mean ESC/ETrue vs. ETrue for EE in EtaTrueBins");
    ha3[ieta-1]->SetTitle(name);
    sprintf(name, "Gaus Sigma ESC/ETrue vs. ETrue for EE in EtaTrueBins");
    ha4[ieta-1]->SetTitle(name);

    // EE
    plots->Clear();
    plots->cd(0);
    plots->Divide(6,5);
    for (int ie=1; ie<=(int)ha3[ieta-1]->GetNbinsX(); ie++)
    {
      plots->cd(ie);
      sprintf(name, "hESciOETrueEE_EtaTrueBin%d_ETrueBin%d", ieta, ie);
      TH1D* hist = (TH1D*)h3d2->ProjectionZ(name, ieta, ieta, ie, ie, "e");
      sprintf(name, "hESciOETrueEE_EtaTrueBin%d_ETrueBin%d %.2f < EtaTrue < %.2f", ieta, ie, h3d2->GetXaxis()->GetBinLowEdge(ieta), h3d2->GetXaxis()->GetBinUpEdge(ieta));
      hist->SetTitle(name);
      hist->SetMarkerStyle(1);
      if (hist->GetEntries()<3) continue;
      sprintf(name, "fgaus_hESciOETrueEE_EtaTrueBin%d_ETrueBin%d", ieta, ie);
      TF1* func = new TF1(name, "gaus", 0,3);
      double m = hist->GetMean();
      double rms = hist->GetRMS();
      hist->Fit(func, "R", "", m-3*rms, m+3*rms);
      m = func->GetParameter(1);
      rms = func->GetParameter(2);
      double merr = func->GetParError(1);
      double rmserr = func->GetParError(2);
      if (rms>hist->GetRMS())
      {
        m = hist->GetMean();
        merr = hist->GetMeanError();
        rms = hist->GetRMS();
        rmserr = hist->GetRMSError();
      }
      ha3[ieta-1]->SetBinContent(ie, m);
      ha3[ieta-1]->SetBinError(ie, merr);
      ha4[ieta-1]->SetBinContent(ie, rms);
      ha4[ieta-1]->SetBinError(ie, rmserr);

      hist->Draw();
      hist->Write();
      func->Write();
    }

    plots->cd(0);
    sprintf(name, "plots_%s.ps", tag);
    plots->Print(name);
    plots->Clear();


  }

  // Gaus Mean Esc/ETrue vs. ETrue in bins of EtaTrue for EB
  ha1[0]->SetMarkerStyle(20);
  ha1[1]->SetMarkerStyle(20);
  ha1[2]->SetMarkerStyle(20);
  ha1[0]->SetMarkerColor(2);
  ha1[1]->SetMarkerColor(4);
  ha1[2]->SetMarkerColor(8);
  ha1[0]->SetLineColor(2);
  ha1[1]->SetLineColor(4);
  ha1[2]->SetLineColor(5);
  ha1[0]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha1[1]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha1[2]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha1[0]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[1]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[2]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[0]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha1[1]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha1[2]->GetYaxis()->SetRangeUser(0.8, 1.2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  sprintf(name, "lg_GausMeanEScOETrueVsETrueInEtaTrueBinsEB");
  lg->SetName(name);
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(1), h3d1->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha1[0], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(2), h3d1->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha1[1], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(3), h3d1->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha1[2], name, "pl");

  plots->Clear();
  ha1[0]->Draw();
  ha1[1]->Draw("same");
  ha1[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha1[0]->Write();
  ha1[1]->Write();
  ha1[2]->Write();
  lg->Write();

  // Gaus Sigma Esc/ETrue vs. ETrue in bins of EtaTrue for EB
  ha2[0]->SetMarkerStyle(20);
  ha2[1]->SetMarkerStyle(20);
  ha2[2]->SetMarkerStyle(20);
  ha2[0]->SetMarkerColor(2);
  ha2[1]->SetMarkerColor(4);
  ha2[2]->SetMarkerColor(8);
  ha2[0]->SetLineColor(2);
  ha2[1]->SetLineColor(4);
  ha2[2]->SetLineColor(5);
  ha2[0]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha2[1]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha2[2]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha2[0]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[1]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[2]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[0]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha2[1]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha2[2]->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  sprintf(name, "lg_GausSigmaEScOETrueVsETrueInEtaTrueBinsEB");
  lg->SetName(name);
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(1), h3d1->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha2[0], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(2), h3d1->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha2[1], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d1->GetXaxis()->GetBinLowEdge(3), h3d1->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha2[2], name, "pl");

  plots->Clear();
  ha2[0]->Draw();
  ha2[1]->Draw("same");
  ha2[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha2[0]->Write();
  ha2[1]->Write();
  ha2[2]->Write();
  lg->Write();

  // Gaus Mean Esc/ETrue vs. ETrue in bins of EtaTrue for EB
  ha3[0]->SetMarkerStyle(20);
  ha3[1]->SetMarkerStyle(20);
  ha3[2]->SetMarkerStyle(20);
  ha3[0]->SetMarkerColor(2);
  ha3[1]->SetMarkerColor(4);
  ha3[2]->SetMarkerColor(8);
  ha3[0]->SetLineColor(2);
  ha3[1]->SetLineColor(4);
  ha3[2]->SetLineColor(5);
  ha3[0]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha3[1]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha3[2]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha3[0]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[1]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[2]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[0]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha3[1]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha3[2]->GetYaxis()->SetRangeUser(0.8, 1.2);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  sprintf(name, "lg_GausMeanEScOETrueVsETrueInEtaTrueBinsEE");
  lg->SetName(name);
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(1), h3d2->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha3[0], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(2), h3d2->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha3[1], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(3), h3d2->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha3[2], name, "pl");

  plots->Clear();
  ha3[0]->Draw();
  ha3[1]->Draw("same");
  ha3[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha3[0]->Write();
  ha3[1]->Write();
  ha3[2]->Write();
  lg->Write();

  // Gaus Sigma Esc/ETrue vs. ETrue in bins of EtaTrue for EE
  ha4[0]->SetMarkerStyle(20);
  ha4[1]->SetMarkerStyle(20);
  ha4[2]->SetMarkerStyle(20);
  ha4[0]->SetMarkerColor(2);
  ha4[1]->SetMarkerColor(4);
  ha4[2]->SetMarkerColor(8);
  ha4[0]->SetLineColor(2);
  ha4[1]->SetLineColor(4);
  ha4[2]->SetLineColor(5);
  ha4[0]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha4[1]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha4[2]->GetXaxis()->SetTitle("ETrue (GeV)");
  ha4[0]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[1]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[2]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[0]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha4[1]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha4[2]->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  sprintf(name, "lg_GausSigmaEScOETrueVsETrueInEtaTrueBinsEE");
  lg->SetName(name);
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(1), h3d2->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha4[0], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(2), h3d2->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha4[1], name, "pl");
  sprintf(name, "%.2f < EtaTrue < %.2f", h3d2->GetXaxis()->GetBinLowEdge(3), h3d2->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha4[2], name, "pl");

  plots->Clear();
  ha4[0]->Draw();
  ha4[1]->Draw("same");
  ha4[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha4[0]->Write();
  ha4[1]->Write();
  ha4[2]->Write();
  lg->Write();


  // ESc/ETrue vs EtaTrue vs. ETrue
  h3d1 = new TH3D("h3d1", "h3d1", 3,0,300, 10, 0.0, 1.5, 200,0.5,1.5);
  h3d2 = new TH3D("h3d2", "h3d2", 3,0,300, 10, 1.5, 3.0, 200,0.5,1.5);
  h3d1->Sumw2();
  h3d2->Sumw2();
  tree->Draw("ESc/ETrue:abs(EtaTrue):ETrue>>h3d1", "isEB&&FoundGsf");
  tree->Draw("ESc/ETrue:abs(EtaTrue):ETrue>>h3d2", "isEE&&FoundGsf");
  h3d1->SetName("EleEScOETrueVsEtaTrueVsETrueEB");
  h3d2->SetName("EleEScOETrueVsEtaTrueVsETrueEE");
  h3d1->SetTitle("Electron SuperCluster Energy Response vs Eta True vs True Energy EB");
  h3d2->SetTitle("Electron SuperCluster Energy Response vs Eta True vs True Energy EE");
  h3d1->GetXaxis()->SetTitle("E True (GeV)");
  h3d2->GetXaxis()->SetTitle("E True (GeV)");
  h3d1->GetYaxis()->SetTitle("EtaTrue");
  h3d2->GetYaxis()->SetTitle("EtaTrue");
  h3d1->GetZaxis()->SetTitle("ESc/ETrue");
  h3d2->GetZaxis()->SetTitle("ESc/ETrue");
  h3d1->SetMarkerStyle(1);
  h3d2->SetMarkerStyle(1);

  plots->Clear();
  h3d1->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h3d1->Write();

  plots->Clear();
  h3d2->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h3d2->Write();

  // Gaus Mean (ESc/Etrue) vs. ETrue and Gaus Sigma (ESc/Etrue) vs. EtaTrue in bins of ETrue
  // EB
  for (int ie=1; ie<=(int)h3d1->GetNbinsX(); ie++)
  {
    ha1[ie-1] = new TH1D("h1", "h1", 10, 0.0, 1.5);
    ha2[ie-1] = new TH1D("h2", "h2", 10, 0.0, 1.5);
    ha1[ie-1]->Sumw2();
    ha2[ie-1]->Sumw2();
    sprintf(name, "GausMeanEScOETrueVsEtaTrueEB_ETrueBin%d", ie);
    ha1[ie-1]->SetName(name);
    sprintf(name, "GausSigmaEScOETrueVsEtaTrueEB_ETrueBin%d", ie);
    ha2[ie-1]->SetName(name);
    sprintf(name, "Gaus Mean ESC/ETrue vs. EtaTrue for EB in ETrueBins");
    ha1[ie-1]->SetTitle(name);
    sprintf(name, "Gaus Sigma ESC/ETrue vs. EtaTrue for EB in ETrueBins");
    ha2[ie-1]->SetTitle(name);

    // EB
    plots->Clear();
    plots->cd(0);
    plots->Divide(6,5);
    for (int ieta=1; ieta<=(int)ha1[ie-1]->GetNbinsX(); ieta++)
    {
      plots->cd(ieta);
      sprintf(name, "hESciOETrueEB_ETrueBin%d_EtaTrueBin%d", ie, ieta);
      TH1D* hist = (TH1D*)h3d1->ProjectionZ(name, ie, ie, ieta, ieta, "e");
      sprintf(name, "hESciOETrueEB_ETrueBin%d_EtaTrueBin%d %.2f < ETrue < %.2f", ie, ieta, h3d1->GetXaxis()->GetBinLowEdge(ie), h3d1->GetXaxis()->GetBinUpEdge(ie));
      hist->SetTitle(name);
      hist->SetMarkerStyle(1);
      if (hist->GetEntries()<3) continue;
      sprintf(name, "fgaus_hESciOETrueEB_ETrueBin%d_EtaTrueBin%d", ie, ieta);
      TF1* func = new TF1(name, "gaus", 0,3);
      double m = hist->GetMean();
      double rms = hist->GetRMS();
      hist->Fit(func, "R", "", m-3*rms, m+3*rms);
      m = func->GetParameter(1);
      rms = func->GetParameter(2);
      double merr = func->GetParError(1);
      double rmserr = func->GetParError(2);
      if (rms>hist->GetRMS()) 
      {
        m = hist->GetMean();
        merr = hist->GetMeanError();
        rms = hist->GetRMS();
        rmserr = hist->GetRMSError();
      }
      ha1[ie-1]->SetBinContent(ieta, m);
      ha1[ie-1]->SetBinError(ieta, merr);
      ha2[ie-1]->SetBinContent(ieta, rms);
      ha2[ie-1]->SetBinError(ieta, rmserr);

      hist->Draw();
      hist->Write();
      func->Write();
    }
    plots->cd(0);
    sprintf(name, "plots_%s.ps", tag);
    plots->Print(name);
    plots->Clear();
  }



  //EE
  for (int ie=1; ie<=(int)h3d2->GetNbinsX(); ie++)
  {
    ha3[ie-1] = new TH1D("h3", "h3", 10, 1.5, 3.0);
    ha4[ie-1] = new TH1D("h4", "h4", 10, 1.5, 3.0);
    ha3[ie-1]->Sumw2();
    ha4[ie-1]->Sumw2();
    sprintf(name, "GausMeanEScOETrueVsEtaTrueEE_ETrueBin%d", ie);
    ha3[ie-1]->SetName(name);
    sprintf(name, "GausSigmaEScOETrueVsEtaTrueEE_ETrueBin%d", ie);
    ha4[ie-1]->SetName(name);
    sprintf(name, "Gaus Mean ESC/ETrue vs. EtaTrue for EE in ETrueBins");
    ha3[ie-1]->SetTitle(name);
    sprintf(name, "Gaus Sigma ESC/ETrue vs. EtaTrue for EE in ETrueBins");
    ha4[ie-1]->SetTitle(name);

    // EE
    plots->Clear();
    plots->cd(0);
    plots->Divide(6,5);
    for (int ieta=1; ieta<=(int)ha3[ie-1]->GetNbinsX(); ieta++)
    {
      plots->cd(ieta);
      sprintf(name, "hESciOETrueEE_ETrueBin%d_EtaTrueBin%d", ie, ieta);
      TH1D* hist = (TH1D*)h3d2->ProjectionZ(name, ie, ie, ieta, ieta, "e");
      sprintf(name, "hESciOETrueEE_ETrueBin%d_EtaTrueBin%d %.2f < ETrue < %.2f GeV", ie, ieta, h3d2->GetXaxis()->GetBinLowEdge(ie), h3d2->GetXaxis()->GetBinUpEdge(ie));
      hist->SetTitle(name);
      hist->SetMarkerStyle(1);
      if (hist->GetEntries()<3) continue;
      sprintf(name, "fgaus_hESciOETrueEE_ETrueBin%d_EtaTrueBin%d", ie, ieta);
      TF1* func = new TF1(name, "gaus", 0,3);
      double m = hist->GetMean();
      double rms = hist->GetRMS();
      hist->Fit(func, "R", "", m-3*rms, m+3*rms);
      m = func->GetParameter(1);
      rms = func->GetParameter(2);
      double merr = func->GetParError(1);
      double rmserr = func->GetParError(2);
      if (rms>hist->GetRMS())
      {
        m = hist->GetMean();
        merr = hist->GetMeanError();
        rms = hist->GetRMS();
        rmserr = hist->GetRMSError();
      }
      ha3[ie-1]->SetBinContent(ieta, m);
      ha3[ie-1]->SetBinError(ieta, merr);
      ha4[ie-1]->SetBinContent(ieta, rms);
      ha4[ie-1]->SetBinError(ieta, rmserr);

      hist->Draw();
      hist->Write();
      func->Write();
    }

    plots->cd(0);
    sprintf(name, "plots_%s.ps", tag);
    plots->Print(name);
    plots->Clear();


  }

  // Gaus Mean Esc/ETrue vs. EtaTrue in bins of ETrue for EB
  ha1[0]->SetMarkerStyle(20);
  ha1[1]->SetMarkerStyle(20);
  ha1[2]->SetMarkerStyle(20);
  ha1[0]->SetMarkerColor(2);
  ha1[1]->SetMarkerColor(4);
  ha1[2]->SetMarkerColor(8);
  ha1[0]->SetLineColor(2);
  ha1[1]->SetLineColor(4);
  ha1[2]->SetLineColor(5);
  ha1[0]->GetXaxis()->SetTitle("EtaTrue");
  ha1[1]->GetXaxis()->SetTitle("EtaTrue");
  ha1[2]->GetXaxis()->SetTitle("EtaTrue");
  ha1[0]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[1]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[2]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha1[0]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha1[1]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha1[2]->GetYaxis()->SetRangeUser(0.8, 1.2);

  lg = new TLegend(0.7,0.7,0.95,0.95);
  sprintf(name, "lg_GausMeanEScOETrueVsEtaTrueInETrueBinsEB");
  lg->SetName(name);
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(1), h3d1->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha1[0], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(2), h3d1->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha1[1], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(3), h3d1->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha1[2], name, "pl");

  plots->Clear();
  ha1[0]->Draw();
  ha1[1]->Draw("same");
  ha1[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha1[0]->Write();
  ha1[1]->Write();
  ha1[2]->Write();
  lg->Write();

  // Gaus Sigma Esc/ETrue vs. ETrue in bins of EtaTrue for EB
  ha2[0]->SetMarkerStyle(20);
  ha2[1]->SetMarkerStyle(20);
  ha2[2]->SetMarkerStyle(20);
  ha2[0]->SetMarkerColor(2);
  ha2[1]->SetMarkerColor(4);
  ha2[2]->SetMarkerColor(8);
  ha2[0]->SetLineColor(2);
  ha2[1]->SetLineColor(4);
  ha2[2]->SetLineColor(5);
  ha2[0]->GetXaxis()->SetTitle("EtaTrue");
  ha2[1]->GetXaxis()->SetTitle("EtaTrue");
  ha2[2]->GetXaxis()->SetTitle("EtaTrue");
  ha2[0]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[1]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[2]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha2[0]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha2[1]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha2[2]->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.7,0.7,0.95,0.95);
  sprintf(name, "lg_GausSigmaEScOETrueVsEtaTrueInETrueBinsEB");
  lg->SetName(name);
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(1), h3d1->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha2[0], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(2), h3d1->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha2[1], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d1->GetXaxis()->GetBinLowEdge(3), h3d1->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha2[2], name, "pl");

  plots->Clear();
  ha2[0]->Draw();
  ha2[1]->Draw("same");
  ha2[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha2[0]->Write();
  ha2[1]->Write();
  ha2[2]->Write();
  lg->Write();

  // Gaus Mean Esc/ETrue vs. EtaTrue in bins of ETrue for EB
  ha3[0]->SetMarkerStyle(20);
  ha3[1]->SetMarkerStyle(20);
  ha3[2]->SetMarkerStyle(20);
  ha3[0]->SetMarkerColor(2);
  ha3[1]->SetMarkerColor(4);
  ha3[2]->SetMarkerColor(8);
  ha3[0]->SetLineColor(2);
  ha3[1]->SetLineColor(4);
  ha3[2]->SetLineColor(5);
  ha3[0]->GetXaxis()->SetTitle("EtaTrue");
  ha3[1]->GetXaxis()->SetTitle("EtaTrue");
  ha3[2]->GetXaxis()->SetTitle("EtaTrue");
  ha3[0]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[1]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[2]->GetYaxis()->SetTitle("Gaus Mean ESc/ETrue");
  ha3[0]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha3[1]->GetYaxis()->SetRangeUser(0.8, 1.2);
  ha3[2]->GetYaxis()->SetRangeUser(0.8, 1.2);

  lg = new TLegend(0.7,0.7,0.95,0.95);
  sprintf(name, "lg_GausMeanEScOETrueVsEtaTrueInETrueBinsEE");
  lg->SetName(name);
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(1), h3d2->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha3[0], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(2), h3d2->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha3[1], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(3), h3d2->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha3[2], name, "pl");

  plots->Clear();
  ha3[0]->Draw();
  ha3[1]->Draw("same");
  ha3[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha3[0]->Write();
  ha3[1]->Write();
  ha3[2]->Write();
  lg->Write();

  // Gaus Sigma Esc/ETrue vs. ETrue in bins of EtaTrue for EE
  ha4[0]->SetMarkerStyle(20);
  ha4[1]->SetMarkerStyle(20);
  ha4[2]->SetMarkerStyle(20);
  ha4[0]->SetMarkerColor(2);
  ha4[1]->SetMarkerColor(4);
  ha4[2]->SetMarkerColor(8);
  ha4[0]->SetLineColor(2);
  ha4[1]->SetLineColor(4);
  ha4[2]->SetLineColor(5);
  ha4[0]->GetXaxis()->SetTitle("EtaTrue");
  ha4[1]->GetXaxis()->SetTitle("EtaTrue");
  ha4[2]->GetXaxis()->SetTitle("EtaTrue");
  ha4[0]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[1]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[2]->GetYaxis()->SetTitle("Gaus Sigma ESc/ETrue");
  ha4[0]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha4[1]->GetYaxis()->SetRangeUser(0.0, 0.06);
  ha4[2]->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.7,0.7,0.95,0.95);
  sprintf(name, "lg_GausSigmaEScOETrueVsEtaTrueInETrueBinsEE");
  lg->SetName(name);
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(1), h3d2->GetXaxis()->GetBinUpEdge(1));
  lg->AddEntry(ha4[0], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(2), h3d2->GetXaxis()->GetBinUpEdge(2));
  lg->AddEntry(ha4[1], name, "pl");
  sprintf(name, "%.2f < ETrue < %.2f GeV", h3d2->GetXaxis()->GetBinLowEdge(3), h3d2->GetXaxis()->GetBinUpEdge(3));
  lg->AddEntry(ha4[2], name, "pl");

  plots->Clear();
  ha4[0]->Draw();
  ha4[1]->Draw("same");
  ha4[2]->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  ha4[0]->Write();
  ha4[1]->Write();
  ha4[2]->Write();
  lg->Write();



  // energy correction string
  //"1.57623-0.775739*EtaTrue+0.319421*EtaTrue*EtaTrue-0.0436783*EtaTrue*EtaTrue*EtaTrue"
  tree->SetAlias("EscaleEtaTrue", "1.0/(1.57623-0.775739*abs(EtaTrue)+0.319421*abs(EtaTrue*EtaTrue)-0.0436783*abs(EtaTrue*EtaTrue*EtaTrue))");
  tree->SetAlias("EScCorr", "(EscaleEtaTrue*ESc)");

  // EScCorr/ETrue vs ETrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, 0, 300, 200,0.5,1.5);
  h2d2 = new TH2D("h2d2", "h2d2", 30, 0, 300, 200,0.5,1.5);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("ESc/ETrue:ETrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("EScCorr/ETrue:ETrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("EleEScCorrOETrueVsETrueEB");
  h2d2->SetName("EleEScCorrOETrueVsETrueEE");
  h2d1->SetTitle("Electron Corrected SuperCluster Energy Response vs True Energy EB");
  h2d2->SetTitle("Electron Corrected SuperCluster Energy Response vs True Energy EE");
  h2d1->GetXaxis()->SetTitle("E true (GeV)");
  h2d2->GetXaxis()->SetTitle("E true (GeV)");
  h2d1->GetYaxis()->SetTitle("EScCorr/ETrue");
  h2d2->GetYaxis()->SetTitle("EScCorr/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Gaus Mean (EScCorr/Etrue) vs. ETrue and  Gaus sigma(EScCorr/Etrue) vs. Etrue
  h1 = new TH1D("h1", "h1", 30, 0, 300);
  h2 = new TH1D("h2", "h2", 30, 0, 300);
  h3 = new TH1D("h3", "h3", 30, 0, 300);
  h4 = new TH1D("h4", "h4", 30, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("GausMeanEScCorrOETrueVsETrueEB");
  h2->SetName("GausMeanEScCorrOETrueVsETrueEE");
  h3->SetName("GausSigmaEScCorrOETrueVsETrueEB");
  h4->SetName("GausSigmaEScCorrOETrueVsETrueEE");
  h1->SetTitle("Gaus Mean EScCorr/ETrue vs. ETrue");
  h2->SetTitle("Gaus Mean EScCorr/ETrue vs. ETrue");
  h3->SetTitle("Gaus Sigma EScCorr/ETrue vs. ETrue");
  h4->SetTitle("Gaus Sigma EScCorr/ETrue vs. ETrue");


  plots->Clear();
  plots->cd(0);
  plots->Divide(6,5);
  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hEScCorrOETrueEB_ETrueBin%d", ii);
    TH1D* hist = h2d1->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hEScCorrOETrueEB_ETrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);

    hist->Draw();
    hist->Write();
    func->Write();
  }
  plots->cd(0);
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();


  plots->Clear();
  plots->Divide(6,5);
  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hEScCorrOETrueEE_ETrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d2->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hEScCorrOETrueEE_ETrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("ETrue (GeV)");
  h2->GetXaxis()->SetTitle("ETrue (GeV)");
  h1->GetYaxis()->SetTitle("Gaus Mean EScCorr/ETrue");
  h2->GetYaxis()->SetTitle("Gaus Mean EScCorr/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausMeanEScCorrOETrueVsETrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("ETrue (GeV)");
  h4->GetXaxis()->SetTitle("ETrue (GeV)");
  h3->GetYaxis()->SetTitle("Gaus Sigma EScCorr/ETrue");
  h4->GetYaxis()->SetTitle("Gaus Sigma EScCorr/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.06);
  h4->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausSigmaEScCorrOETrueVsETrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();


  // EScCorr/ETrue vs EtaTrue
  h2d1 = new TH2D("h2d1", "h2d1", 60, -3, 3, 200,0.5,1.5);
  h2d2 = new TH2D("h2d2", "h2d2", 60, -3, 3, 200,0.5,1.5);
  h2d1->Sumw2();
  h2d2->Sumw2();
  tree->Draw("ESc/ETrue:EtaTrue>>h2d1", "isEB&&FoundGsf");
  tree->Draw("EScCorr/ETrue:EtaTrue>>h2d2", "isEE&&FoundGsf");
  h2d1->SetName("EleEScCorrOETrueVsEtaTrueEB");
  h2d2->SetName("EleEScCorrOETrueVsEtaTrueEE");
  h2d1->SetTitle("Electron Corr SuperCluster Energy Response vs EtaTrue EB");
  h2d2->SetTitle("Electron Corr SuperCluster Energy Response vs EtaTrue EE");
  h2d1->GetXaxis()->SetTitle("EtaTrue");
  h2d2->GetXaxis()->SetTitle("EtaTrue");
  h2d1->GetYaxis()->SetTitle("EScCorr/ETrue");
  h2d2->GetYaxis()->SetTitle("EScCorr/ETrue");


  plots->Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d1->Write();

  plots->Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();
  fileout->cd();
  h2d2->Write();

  // Gaus Mean(EScCorr/Etrue) vs. EtaTrue and Gaus Sigma (EScCorr/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 60, -3, 3);
  h2 = new TH1D("h2", "h2", 60, -3, 3);
  h3 = new TH1D("h3", "h3", 60, -3, 3);
  h4 = new TH1D("h4", "h4", 60, -3, 3);
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4->Sumw2();
  h1->SetName("GausMeanEScCorrOETrueVsEtaTrueEB");
  h2->SetName("GausMeanEScCorrOETrueVsEtaTrueEE");
  h3->SetName("GausSigmaEScCorrOETrueVsEtaTrueEB");
  h4->SetName("GausSigmaEScCorrOETrueVsEtaTrueEE");
  h1->SetTitle("Gaus Mean EScCorr/ETrue vs. EtaTrue");
  h2->SetTitle("Gaus Mean EScCorr/ETrue vs. EtaTrue");
  h3->SetTitle("Gaus Sigma EScCorr/ETrue vs. EtaTrue");
  h4->SetTitle("Gaus Sigma EScCorr/ETrue vs. EtaTrue");


  plots->Clear();
  plots->cd(0);
  plots->Divide(10,6);
  for (int ii=1; ii<=(int)h1->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hEScCorrOETrueEB_EtaTrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d1->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hEScCorrOETrueEB_EtaTrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    //hist->Fit(func);
    //double m = func->GetParameter(1);
    //double rms = func->GetParameter(2);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h1->SetBinContent(ii, m);
    h1->SetBinError(ii, merr);
    h3->SetBinContent(ii, rms);
    h3->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  plots->Clear();
  plots->cd(0);
  plots->Divide(10,6);
  for (int ii=1; ii<=(int)h2->GetNbinsX(); ii++)
  {
    plots->cd(ii);
    sprintf(name, "hEScCorrOETrueEE_EtaTrueBin%d", ii);
    TH1D* hist = (TH1D*)h2d2->ProjectionY(name, ii, ii, "e");
    hist->SetMarkerStyle(1);
    if (hist->GetEntries()<100) continue;
    sprintf(name, "fgaus_hEScCorrOETrueEE_EtaTrueBin%d", ii);
    TF1* func = new TF1(name, "gaus", 0,3);
    //hist->Fit(func);
    //double m = func->GetParameter(1);
    //double rms = func->GetParameter(2);
    double m = hist->GetMean();
    double rms = hist->GetRMS();
    hist->Fit(func, "R", "", m-3*rms, m+3*rms);
    m = func->GetParameter(1);
    rms = func->GetParameter(2);
    double merr = func->GetParError(1);
    double rmserr = func->GetParError(2);
    if (rms>hist->GetRMS())
    {
      m = hist->GetMean();
      merr = hist->GetMeanError();
      rms = hist->GetRMS();
      rmserr = hist->GetRMSError();
    }
    h2->SetBinContent(ii, m);
    h2->SetBinError(ii, merr);
    h4->SetBinContent(ii, rms);
    h4->SetBinError(ii, rmserr);
    hist->Draw();
    hist->Write();
    func->Write();
  }
  sprintf(name, "plots_%s.ps", tag);
  plots->cd();
  plots->Print(name);
  plots->Clear();

  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(4);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("EtaTrue");
  h2->GetXaxis()->SetTitle("EtaTrue");
  h1->GetYaxis()->SetTitle("Gaus Mean EScCorr/ETrue");
  h2->GetYaxis()->SetTitle("Gaus Mean EScCorr/ETrue");
  h1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h2->GetYaxis()->SetRangeUser(0.8, 1.2);


  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GausMeanEScCorrOETrueVsEtaTrue");
  lg->AddEntry(h1, "EB", "pl");
  lg->AddEntry(h2, "EE", "pl");

  plots->Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h1->Write();
  h2->Write();
  lg->Write();

  h3->SetMarkerStyle(20);
  h3->SetMarkerColor(2);
  h3->SetLineColor(2);
  h4->SetMarkerStyle(20);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);
  h3->GetXaxis()->SetTitle("EtaTrue");
  h4->GetXaxis()->SetTitle("EtaTrue");
  h3->GetYaxis()->SetTitle("Gaus Sigma EScCorr/ETrue");
  h4->GetYaxis()->SetTitle("Gaus Sigma EScCorr/ETrue");
  h3->GetYaxis()->SetRangeUser(0.0, 0.06);
  h4->GetYaxis()->SetRangeUser(0.0, 0.06);

  lg = new TLegend(0.8,0.8,0.95,0.95);
  lg->SetName("lg_GuasSigmaEScCorrOETrueVsEtaTrue");
  lg->AddEntry(h3, "EB", "pl");
  lg->AddEntry(h4, "EE", "pl");

  plots->Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots->Print(name);
  plots->Clear();

  h3->Write();
  h4->Write();
  lg->Write();


  // end 
  sprintf(name, "plots_%s.ps]", tag);
  plots->Print(name);

  sprintf(name, ".! ps2pdf plots_%s.ps", tag);
  gROOT->ProcessLine(name);
  fileout->Close();

}
