{
  char* tag = "ShashlikTupleDumper_RelValSingleElectronPt35Extended_DES23_62_V1_UPG2023SHNoTaper-v1";

  char name[1000];
  sprintf(name, "%s.root", tag);
  TFile* file = TFile::Open(name);
  TTree* tree = (TTree*)file->Get("tree");
  sprintf(name, "plots_%s.root", tag);
  TFile* fileout = TFile::Open(name, "RECREATE");
  gROOT->ProcessLine(".L tdrStyle.C");
  tdrstyle();

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

  TLegend* lg;

  TCanvas plots("plots", "plots", 400, 400);
  sprintf(name, "plots_%s.ps[", tag);
  plots.Print(name);

  // PtTrue
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("PtTrue>>h1", "isEB");
  tree->Draw("PtTrue>>h2", "isEE");
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // ETrue
  h1 = new TH1D("h1", "h1", 100, 0, 300);
  h2 = new TH1D("h2", "h2", 100, 0, 300);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("ETrue>>h1", "isEB");
  tree->Draw("ETrue>>h2", "isEE");
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrue
  h1 = new TH1D("h1", "h1", 50, -5, 5);
  h2 = new TH1D("h2", "h2", 50, -5, 5);
  h1->Sumw2();
  h2->Sumw2();
  tree->Draw("EtaTrue>>h1", "isEB");
  tree->Draw("EtaTrue>>h2", "isEE");
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();
  
  // eta sc
  h1 = new TH1D("h1", "h1", 50, -5, 5);
  h2 = new TH1D("h2", "h2", 50, -5, 5);
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrackIn
  h1 = new TH1D("h1", "h1", 50, -5, 5);
  h2 = new TH1D("h2", "h2", 50, -5, 5);
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();

  // EtaTrackOut
  h1 = new TH1D("h1", "h1", 50, -5, 5);
  h2 = new TH1D("h2", "h2", 50, -5, 5);
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();

  fileout->cd();
  h1->Write();
  h2->Write();
  lg->Write();


  // ESc/ETrue vs ETrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, 0, 300, 300,0,3);
  h2d2 = new TH2D("h2d2", "h2d2", 30, 0, 300, 300,0,3);
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


  plots.Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d1->Write();

  plots.Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


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

  plots.Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


  // ESc/ETrue vs EtaTrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, -5, 5, 300,0,3);
  h2d2 = new TH2D("h2d2", "h2d2", 30, -5, 5, 300,0,3);
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


  plots.Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d1->Write();

  plots.Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(ESc/Etrue) vs. EtaTrue and  RMS(ESc/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 30, -5, 5);
  h2 = new TH1D("h2", "h2", 30, -5, 5);
  h3 = new TH1D("h3", "h3", 30, -5, 5);
  h4 = new TH1D("h4", "h4", 30, -5, 5);
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


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

  plots.Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


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


  plots.Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d1->Write();

  plots.Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


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

  plots.Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


  // PTrackIn/ETrue vs EtaTrue
  h2d1 = new TH2D("h2d1", "h2d1", 30, -5, 5, 300,0,3);
  h2d2 = new TH2D("h2d2", "h2d2", 30, -5, 5, 300,0,3);
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


  plots.Clear();
  h2d1->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d1->Write();

  plots.Clear();
  h2d2->Draw("colz");
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  fileout->cd();
  h2d2->Write();

  // Mean(PTrackIn/Etrue) vs. EtaTrue and  RMS(PTrackIn/Etrue) vs. EtaTrue
  h1 = new TH1D("h1", "h1", 30, -5, 5);
  h2 = new TH1D("h2", "h2", 30, -5, 5);
  h3 = new TH1D("h3", "h3", 30, -5, 5);
  h4 = new TH1D("h4", "h4", 30, -5, 5);
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

  plots.Clear();
  h1->Draw();
  h2->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();


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

  plots.Clear();
  h3->Draw();
  h4->Draw("same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tag);
  plots.Print(name);
  plots.Clear();
  // eta

  // phi

  // 

  sprintf(name, "plots_%s.ps]", tag);
  plots.Print(name);

  sprintf(name, ".! ps2pdf plots_%s.ps", tag);
  gROOT->ProcessLine(name);
  fileout->Close();

}
