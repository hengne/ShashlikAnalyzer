ShashlikAnalyzer

Analyzer for Shahlik ECAL upgrade samples.



Install:

> export SCRAM_ARCH=slc6_amd64_gcc472

> cmsrel CMSSW_6_2_0_SLHC17_patch1

> cd CMSSW_6_2_0_SLHC17_patch1/src

> cmsenv

> git clone https://github.com/hengne/ShashlikAnalyzer.git

> scram b -j8

Note: change the above release version as needed.



Run Ntuple Dumper:

> cp ShashlikAnalyzer/ShashlikAnalyzer/test/ShashlikTupleDumper_cfg.py .

> cmsRun ShashlikTupleDumper_cfg.py

Note: check and change the input and output files in the configuration files


If using Crab3, some useful commands:

Setup env:
>    source /cvmfs/cms.cern.ch/crab3/crab.sh

Init grid cert:

>   voms-proxy-init -voms cms --hours 172 --valid 172:00

Submit:

>   crab submit -c crabJob_DYToEE_withHits.py

Check status:

>   crab status -t crab_projects/crab_crab3Job_DYToEE_withHits/




Run the analysis macros:

>  cp ShashlikAnalyzer/ShashlikAnalyzer/test/*.C .

one example is PrintPlots.C
It read the Ntuple produced by the ShashlikeTupleDumper and draw plots.
Plots are printted into a ps/pdf file + a root file.




