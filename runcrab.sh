

voms-proxy-init -voms cms --hours 172 --valid 172:00
source /cvmfs/cms.cern.ch/crab3/crab.sh
crab submit -c crabJob_DYToEE_withHits.py

crab status -t crab_projects/crab_crab3Job_DYToEE_withHits/

