
import sys, os, string, re, pwd, commands, ast, optparse, shlex, time
import ROOT
import itertools
import math
from DataFormats.FWLite import Events, Handle
from array import array

grootargs = []
def callback_rootargs(option, opt, value, parser):
    grootargs.append(opt)

### Define function for parsing options
def parseOptions():

    global opt, args, runAllSteps

    usage = ('usage: %prog [options]\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)

    # input options
    parser.add_option("-l",action="callback",callback=callback_rootargs)
    parser.add_option("-q",action="callback",callback=callback_rootargs)
    parser.add_option("-b",action="callback",callback=callback_rootargs)

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()

# parse the arguments and options
global opt, args, runAllSteps
parseOptions()
sys.argv = grootargs

GsfElectrons = Handle ('std::vector<reco::GsfElectron>')
GenParticles = Handle ('std::vector<reco::GenParticle>')


events = Events([
'root://cmsxrootd.fnal.gov//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/002CD53C-57A7-E411-BB32-002618943901.root',
'root://cmsxrootd.fnal.gov//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/009271E3-EAA6-E411-A58E-0025905A6132.root',
'root://cmsxrootd.fnal.gov//store/mc/TP2023SHCALDR/DYToEE_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/0094D1BB-00A7-E411-8121-0025905A60F2.root'
])

f=ROOT.TFile("study_ele.root","recreate")


def deltaR2( e1, p1, e2, p2):
    de = e1 - e2
    dp = deltaPhi(p1, p2)
    return de*de + dp*dp


def deltaR( *args ):
    return math.sqrt( deltaR2(*args) )


def deltaPhi( p1, p2):
    '''Computes delta phi, handling periodic limit conditions.'''
    res = p1 - p2
    while res > math.pi:
        res -= 2*math.pi
    while res < -math.pi:
        res += 2*math.pi
    return res


hElecPT = ROOT.TH1F("hElecPT","hElecPT", 100, 0, 100)
hElecPTEB = ROOT.TH1F("hElecPTEB","hElecPTEB", 100, 0, 100)
hElecPTEE = ROOT.TH1F("hElecPTEE","hElecPTEE", 100, 0, 100)
hElecEta = ROOT.TH1F("hElecEta","hElecEta", 100, -5, 5)

N=0.0
for event in events:
    N=N+1.0

    event.getByLabel('gsfElectrons','','RECO', GsfElectrons)
    event.getByLabel('genParticles','','SIM', GenParticles)

    gsfElectrons = GsfElectrons.product()
    genParticles = GenParticles.product()

    for ele in gsfElectrons:
        hElecPT.Fill(ele.pt())
        hElecEta.Fill(ele.eta())
        if (ele.isEB()): 
            hElecPTEB.Fill(ele.pt())
        if (ele.isEE()): 
            hElecPTEE.Fill(ele.pt())


f.cd()

hElecPT.Write()
hElecPTEB.Write()
hElecPTEE.Write()
hElecEta.Write()

f.Close()
