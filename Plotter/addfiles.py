#! /usr/bin/env python

import os
import sys
import subprocess

srcfiles = {
'MC__TT.root': 'MC__TTTo*.root',
'MC__ST.root': 'MC__ST_*.root',
'DATA__DATA_Tau.root': 'DATA__DATA_Tau_*.root'
}


processes = []
for key in srcfiles:
    command = 'hadd -f ' + key + ' ' + srcfiles[key]
    processes.append(subprocess.Popen(command, shell=True))

for proc in processes:
    proc.wait()
