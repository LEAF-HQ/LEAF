import os
import subprocess
from utils import *

class Storage():
    def __init__(self, path = None, director = None):
        self.path = path
        self.director = director

    def __str__(self):
        return self.get_path()

    def get_path(self, is_complete=True):
        if is_complete:
            return self.director+self.path
        else:
            return self.path

    def create_file_list(self):
        raise NotImplementedError()

    def get_file_list(self):
        return self.create_file_list()

    def make_list(self, command, outpath=""):
        filelist = subprocess.check_output(command, shell=True).split('\n')
        newfiles = []
        for f in filelist:
            if f is '': continue
            newfiles.append(outpath+f)
        return newfiles


class Storage_DAS(Storage):
    def __init__(self, path):
        Storage.__init__(self, path = path, director = 'root://cms-xrd-global.cern.ch/')

    def create_file_list(self):
        #call 'dasgoclient' to get a list of rootfiles from the DAS string
        dasgocommand = 'dasgoclient -query="file dataset=%s"' % (self.path)
        return self.make_list(dasgocommand, outpath=self.director)

#gsiftp://storage01.lcg.cscs.ch/
class Storage_T2PSI(Storage):
    def __init__(self, path):
        Storage.__init__(self, path = '/pnfs/lcg.cscs.ch/cms/trivcat' + path, director = 'root://storage01.lcg.cscs.ch/')

    # if the path does not yet exist, create it
    def make_dirs(self):
        ensureDirectory(self.get_path(is_complete=True).replace('root://', 'gsiftp://'), use_se=True)

    def create_file_list(self):
        command = 'LD_LIBRARY_PATH='' PYTHONPATH='' gfal-ls %s' % (self.director.replace('root://', 'gsiftp://')+self.path)
        return self.make_list(command, outpath=self.director+self.path)


class Storage_T3PSI(Storage):
    def __init__(self, path):
        Storage.__init__(self, path = '/pnfs/psi.ch/cms/trivcat' + path, director = 'root://t3dcachedb03.psi.ch/')

    # if the path does not yet exist, create it
    def make_dirs(self):
        ensureDirectory(self.path)

    def create_file_list(self):
        if not os.path.exists(self.path):
            return []
        command = 'ls %s' % (self.path)
        return self.make_list(command, outpath=self.director+self.path)



class Storage_T2ULB(Storage):
    def __init__(self, path):
        Storage.__init__(self, path = '/pnfs/iihe/cms' + path, director = 'root://maite.iihe.ac.be:1094/')

    def create_file_list(self):
        command = 'LD_LIBRARY_PATH='' PYTHONPATH='' gfal-ls %s' % (self.director+self.path)
        return self.make_list(command, outpath=self.director+self.path)
