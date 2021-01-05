import os
import subprocess
from utils import *

class Storage():
    def __init__(self, path):
        self.director = None
        self.path = path


class Storage_DAS(Storage):
    def __init__(self, path):
        self.director = 'root://cms-xrd-global.cern.ch/'
        self.path = path
        self.filelist = self.get_file_list()

    def get_file_list(self):
        #call 'dasgoclient' to get a list of rootfiles from the DAS string
        dasgocommand = 'dasgoclient -query="file dataset=%s"' % (self.path)
        filelist = subprocess.check_output(dasgocommand, shell=True).split('\n')
        newfiles = []
        for f in filelist:
            if f is '': continue
            newfiles.append(self.director + f)
        return newfiles

#gsiftp://storage01.lcg.cscs.ch/
class Storage_T2PSI(Storage):
    def __init__(self, path):
        self.director = 'root://storage01.lcg.cscs.ch/'
        self.path = '/pnfs/lcg.cscs.ch/cms/trivcat' + path
        self.filelist = self.get_file_list()

    def get_file_list(self):
        command = 'LD_LIBRARY_PATH='' PYTHONPATH='' gfal-ls %s' % (self.director.replace('root://', 'gsiftp://')+self.path)
        filelist = subprocess.check_output(command, shell=True).split('\n')
        newfiles = []
        for f in filelist:
            if f is '': continue
            newfiles.append(os.path.join(self.director+self.path, f))
        return newfiles


class Storage_T3PSI(Storage):
    def __init__(self, path):
        self.director = 'root://t3dcachedb03.psi.ch/'
        self.path = '/pnfs/psi.ch/cms/trivcat' + path
        self.filelist = self.get_file_list()

    # if the path does not yet exist, create it
    def make_dirs(self):
        ensureDirectory(self.path)

    def get_file_list(self):
        if not os.path.exists(self.path):
            return []
        command = 'ls %s' % (self.path)
        filelist = subprocess.check_output(command, shell=True).split('\n')
        newfiles = []
        for f in filelist:
            if f is '': continue
            newfiles.append(os.path.join(self.director+self.path, f))
        return newfiles
