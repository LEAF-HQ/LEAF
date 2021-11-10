import ROOT
ROOT.gROOT.SetBatch(1)

# file2 = open('/work/areimers/LEAF/Generator/gridpacks/ChiPsi/LQTChannelTauNu_DynamicScale/test/cmsgrid_final.lhe', 'r')
# file2 = open('/work/areimers/MG5_aMC_v2_7_2/LQTChannelTauNu_M3000/Events/run_05/unweighted_events.lhe', 'r')
# file2 = open('/work/areimers/MG5_aMC_v2_6_5/LQTChannelTauNu_FixedGridpacks_M3000/test/events.lhe', 'r') # MG5 v2.6.5 GP local
file2 = open('//work/areimers/MG5_aMC_v2_6_5/LQTChannelTauNu_FixedGridpacks_M3000/Events/run_01/unweighted_events.lhe', 'r') # MG5 v2.6.5 directly local

Lines_Double = file2.readlines()

# Strips the newline character
tau1 = ROOT.TLorentzVector()
met  = ROOT.TLorentzVector()

h1 = ROOT.TH1D("h1", "h1", 40, 0, 500)
h1.SetXTitle("#tau_{1} p_{T} [GeV]");
h2 = ROOT.TH1D("h2", "h2", 70, -7, 7)
h2.SetXTitle("#tau_{1} #eta");
h3 = ROOT.TH1D("h3", "h3", 100, 0, 500)
h3.SetXTitle("MET [GeV]");

nevt = 0
found_event = False
for line in Lines_Double:
  adouble = line.strip()
  word_counter = 0
  found_tau = False
  found_nu = False
  px = 0
  py = 0
  pz = 0
  enegry = 0
  particle_id = 0
  for word in line.split():
    if ('<event>' in word):
      found_event = True
      # print line
    if not found_event:
      continue
    if (word == '15' or word == '-15' or found_tau):
    # if (word == '15' or word == '-15'):
      found_tau = True
      word_counter += 1
      if (word_counter==1):
        particle_id = word
      if (word_counter==7):
        px = float(word)
      if (word_counter==8):
        py = float(word)
      if (word_counter==9):
        pz = float(word)
      if (word_counter==10):
        energy = float(word)

        # if (particle_id == '15' or particle_id == '-15'):
          # tau1.SetPxPyPzE(px, py, pz, energy)
        tau1.SetPxPyPzE(px, py, pz, energy)

    if (word == '16' or word == '-16' or word == '-14' or word == '14' or word == '-12' or word == '12' or found_nu):
      found_nu = True
      word_counter += 1
      # print line
      if (word_counter==1):
        particle_id = word
      if (word_counter==7):
        px = float(word)
      if (word_counter==8):
        py = float(word)
      if (word_counter==9):
        pz = float(word)
      if (word_counter==10):
        energy = float(word)

        # if (particle_id == '15' or particle_id == '-15'):
          # tau1.SetPxPyPzE(px, py, pz, energy)
        met.SetPxPyPzE(px, py, pz, energy)




    if (word == '</event>'):
      nevt += 1
      found_event = False
      if nevt % 500 == 0: print nevt
      h1.Fill( (tau1).Pt() )
      h2.Fill( (tau1).Eta() )
      h3.Fill( (met).Pt() )


c1 = ROOT.TCanvas("c1","inv mass",900,900)
h1.Draw()
c1.SetLogy()
c1.SaveAs('tau1_pt.pdf')


c2 = ROOT.TCanvas("c2","inv mass",900,900)
h2.Draw()
c2.SetLogy()
c2.SaveAs('tau1_eta.pdf')


c3 = ROOT.TCanvas("c3","inv mass",900,900)
h3.Draw()
c3.SetLogy()
c3.SaveAs('met_pt.pdf')
