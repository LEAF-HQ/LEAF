# Author: Izaak Neutelings (October, 2019)
# Source:
#  https://docs.google.com/presentation/d/1YTANRT_ZeL5VubnFq7lNGHKsiD7D3sDiOPNgXUYVI0I/edit#slide=id.g61f8771f52_33_8


globaltags = { 'mc': { }, 'data': { }, }
globaltags['mc']['miniAOD'] = {
  # https://docs.google.com/presentation/d/1YTANRT_ZeL5VubnFq7lNGHKsiD7D3sDiOPNgXUYVI0I/edit#slide=id.g61f8771f52_33_8
  'default': 'auto:phase1_2017_realistic',
  2016:      '94X_mcRun2_asymptotic_v3',
  2017:      '94X_mc2017_realistic_v17', #'94X_mc2017_realistic_v14',
  2018:      '102X_upgrade2018_realistic_v20', #'102X_upgrade2018_realistic_v15',
}
globaltags['mc']['nanoAOD'] = {
  'default': 'auto:phase1_2017_realistic',
  2016:      '102X_mcRun2_asymptotic_v7',
  2017:      '102X_mc2017_realistic_v7', #'94X_mc2017_realistic_v14',
  2018:      '102X_upgrade2018_realistic_v19', #'102X_upgrade2018_realistic_v20', #'102X_upgrade2018_realistic_v15',
}
globaltags['data']['nanoAOD'] = {
  'default': 'auto:phase1_2017_realistic',
  2016:      '102X_dataRun2_v11',
  2017:      '102X_dataRun2_v11',
  2018:      '102X_dataRun2_v12',
  '2018D':   '102X_dataRun2_Prompt_v15',
}

from Configuration.StandardSequences.Eras import eras as Eras
eras = { }
eras['nanoAOD'] = {
  2016: Eras.run2_nanoAOD_94X2016,
  2017: Eras.run2_nanoAOD_94XMiniAODv2,
  2018: Eras.run2_nanoAOD_102Xv1,
}
eras['SIM'] = {
  2016: Eras.Run2_2016,
  2017: Eras.Run2_2017,
  2018: Eras.Run2_2018,
}
