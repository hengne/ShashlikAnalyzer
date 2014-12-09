#!/bin/sh

list=""
MaxCount=57


Output=Ntuple_DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola_withhits3.root
base="root://eoscms//store/user/heli/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/crab3Job_DYToEE_withHits3/141208_163902/0000/output_"
#Output=Ntuple_DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola.root
#base="root://eoscms//store/user/heli/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/crab3Job_DYToEE_withHits2/141106_191402/0000/output_"
#Output=Ntuple_GluGluToHToZZTo4e_M-125_14TeV-powheg-pythia6_test2.root
#base="root://eoscms//store/user/heli/GluGluToHToZZTo4e_M-125_14TeV-powheg-pythia6/crab_ggHZZ4e_test2/141001_133819/0000/output_"
#Output=Ntuple_DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola_test3.root
#base="root://eoscms//store/user/heli/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/crab3Job_DYToEE_test3/140925_191105/0000/output_"

for id in `seq 1 1 ${MaxCount}`;
do 
 list="${list} ${base}${id}.root "
done


hadd ${Output} ${list}

