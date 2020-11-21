#! /usr/bin/env python

import os, sys, math
from os.path import isfile, join
from fnmatch import fnmatch
import subprocess
import time
import parse
from operator import itemgetter
import importlib
from utils import *

submit = True



get_wns = 'sinfo -N --partition wn -o "%N"'
wns = subprocess.check_output(get_wns.split(' ')).split('\n')
for wn in wns:
    wn = wn.strip('\"')
    if not 't3wn' in wn: continue
    command = 'sbatch -J cleanup_%s -p quick -t 00:50:00 -w %s clean_wn_scratches.sh' % (wn, wn)
    # command = 'sbatch -J cleanup -p quick -t 00:10:00 clean_wn_scratches.sh'
    print command
    if submit:
        os.system(command)
