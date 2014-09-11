ShashlikAnalyzer

Analyzer for Shahlik ECAL upgrade samples.



Install:

> export SCRAM_ARCH=slc6_amd64_gcc472
> cmsrel CMSSW_6_2_0_SLHC17_patch1
> cd CMSSW_6_2_0_SLHC17_patch1/src
> cmsenv
> git clone https://github.com/hengne/ShashlikAnalyzer.git
> sram b -j8

Note: change the above release version as needed.



Run Ntuple Dumper:
> cp ShashlikAnalyzer/ShashlikAnalyzer/test/ShashlikTupleDumper_cfg.py .
> cmsRun ShashlikTupleDumper_cfg.py

Note: check and change the input and output files in the configuration files


Run the analysis macros:
> cp ShashlikAnalyzer/ShashlikAnalyzer/test/*.C .

one example is PrintPlots.C
It read the Ntuple produced by the ShashlikeTupleDumper and draw plots.
Plots are printted into a ps/pdf file + a root file.



