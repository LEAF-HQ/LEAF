#! /usr/bin/env python


import os, sys, math
from os.path import isfile, join
import subprocess
import time
import parse
from operator import itemgetter
import importlib
from utils import *

workdir = '/work/areimers/workdir_slurm'

command = 'ls %s' % (workdir)
filelist = subprocess.check_output(command.split(' ')).split('\n')
print filelist[0:20]
print len(filelist)

commands = []
for file in filelist:
    commands.append('rm %s/%s' % (workdir, file))

print commands[0:20]
execute_commands_parallel(commands=commands, ncores=1)
