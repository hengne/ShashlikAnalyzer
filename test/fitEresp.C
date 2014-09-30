{
TFile* file = TFile::Open("plots_ShashlikTupleDumper_RelValZEE_14TeV_GEN-SIM-RECO_DES23_62_V1_UPG2023SHNoTaper-v1.root");

TF1* func= new TF1("func", "[0]+[1]*x+[2]*x*x+[3]*x*x*x",1.5,3); 
TH1D* h1 = (TH1D*)file->Get("GausMeanEScOETrueVsEtaTrueEE");

h1->Fit(func, "R", "", 1.5, 2.9);

/*
Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1
 FCN=94.4273 FROM HESSE     STATUS=NOT POSDEF     25 CALLS         170 TOTAL
                     EDM=3.90927e-14    STRATEGY= 1      ERR MATRIX NOT POS-DEF
  EXT PARAMETER                APPROXIMATE        STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.57623e+00   2.09997e-03   3.75803e-07   3.60374e-05
   2  p1          -7.75739e-01   1.49061e-03   1.84951e-07  -1.01539e-04
   3  p2           3.19421e-01   6.23900e-04   7.61558e-08  -1.21571e-04
   4  p3          -4.36783e-02   1.84673e-04   1.88055e-08   4.70114e-04

1.57623-0.775739*x+0.319421*x*x-0.0436783*x*x*x

*/

TH1D* h2 = (TH1D*)file->Get("GausMeanEScOETrueVsETrueEE_EtaTrueBin2");

TF1* func2 = new TF1("func2", "[0]+[1]*x", 0,300);
h2->Fit(func2,"R");


}
