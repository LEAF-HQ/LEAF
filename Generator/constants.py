from ROOT import kBlack, kRed, kBlue, kAzure, kCyan, kGreen, kGreen, kYellow, kOrange, kMagenta, kViolet, kSolid, kDashed, kDotted


colors = [kRed+4, kRed+1, kAzure-2, kOrange, kGreen-2]
slurm_queues_runtimes = {
1: 'short',
12: 'standard',
24: 'long'
}


procname_to_latex = {
    'LQLQ': 'LQ LQ',
    'LQLQToBTau': 'LQ LQ #rightarrow b#tau b#tau',
    'LQLQToBTauPsiChi': 'LQ LQ #rightarrow b#tau #psi#chi_{1}',
    'LQLQToPsiChi': 'LQ LQ #rightarrow #psi#chi_{1} #psi#chi_{1}',
    'PsiPsiToLQChi': '#psi#psi #rightarrow b#tau#chi_{1} b#tau#chi_{1}',
    'PsiPsi': '#psi#psi',
    'LQTChannelTauNu': 'LQ t-channel #tau#nu',
    'LQTChannelTauTau': 'LQ t-channel #tau#tau',
}

decaymode_dict = {
    (5, -15): 'b #tau',
    (6, -16): 't #nu',
    (4, -16): 'c #nu',
    (9000009, 9000007): '#psi #chi_{1}',
    (9000009, 9000008): '#psi #chi_{2}'
}

procname_to_decaymodes = {
    'LQLQToBTau': [(5, -15), (5, -15)],
    'LQLQToBTauPsiChi':  [(5, -15), (9000009, 9000007)],
    'LQLQToPsiChi':  [(9000009, 9000007), (9000009, 9000007)],
    'LQLQToPsiChi_PsiToBTauChi':  [(9000009, 9000007), (9000009, 9000007)]
}
