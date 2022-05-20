from Sample import *
from Storage import *
from Data_MET_MiniAODv2 import *
from Data_Tau_MiniAODv2 import *
from Data_SingleMuon_MiniAODv2 import *
from Data_SingleElectron_MiniAODv2 import *


def Add_Data(SampleContainer):
    Add_Data_MET(SampleContainer)
    Add_Data_Tau(SampleContainer)
    Add_Data_SingleMuon(SampleContainer)
    Add_Data_SingleElectron(SampleContainer)
