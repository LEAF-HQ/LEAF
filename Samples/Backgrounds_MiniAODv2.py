from Sample import *
from Storage import *
from Backgrounds_TT_MiniAODv2 import *
from Backgrounds_WJets_MiniAODv2 import *
from Backgrounds_DYJets_MiniAODv2 import *
from Backgrounds_ZJetsToNuNu_MiniAODv2 import *
from Backgrounds_ST_MiniAODv2 import *
from Backgrounds_Diboson_MiniAODv2 import *
from Backgrounds_QCDHad_MiniAODv2 import *
from Backgrounds_QCDBEnriched_MiniAODv2 import *



def Add_Backgrounds(SampleContainer):
    Add_Backgrounds_TT(SampleContainer)
    Add_Backgrounds_WJets(SampleContainer)
    Add_Backgrounds_DYJets(SampleContainer)
    Add_Backgrounds_ZJetsToNuNu(SampleContainer)
    Add_Backgrounds_ST(SampleContainer)
    Add_Backgrounds_Diboson(SampleContainer)
    Add_Backgrounds_QCDHad(SampleContainer)
    Add_Backgrounds_QCDBEnriched(SampleContainer)
