from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'crab3Job_DYToEE_withHits2'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ShashlikTupleDumper_cfg.py'
config.JobType.outputFiles = ['output.root'] 

config.section_("Data")
config.Data.inputDataset = '/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/SHCAL2023Upg14DR-PU140bx25_PH2_1K_FB_V4-v1/GEN-SIM-RECO'
config.Data.dbsUrl = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 50
config.Data.publication = True
config.Data.publishDbsUrl = 'phys03'
config.Data.publishDataName = 'crab3Job_DYToEE_withHits2'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN' 

