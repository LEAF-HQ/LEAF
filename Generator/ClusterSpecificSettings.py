from copy import deepcopy
from utils import red
from functools import total_ordering
from collections import OrderedDict

@total_ordering
class TimeFormat():
    def __init__(self, *args, **kwargs):
        self.time = {'d':0,'h':0,'m':0,'s':0}
        if len(args)!=0 and len(kwargs)!=0:
            raise ValueError(red('Unsupported input format for TimeFormat. Both args and kwargs given.'))
        elif len(kwargs) != 0:
            self.time.update(kwargs)
        elif len(args)==1:
            if isinstance(args[0], self.__class__):
                self.__dict__ = deepcopy(args[0].__dict__)
            elif type(args[0])== str:
                parts = args[0].split(':')
                if '-' in parts[0]:
                    self.time['d'], self.time['h'] = (int(parts[0].split('-')[0]),int(parts[0].split('-')[1]))
                else:
                    self.time['h'] = int(parts[0])
                self.time['m'], self.time['s'] = (int(parts[1]), int(parts[2]))
            elif type(args[0])== dict:
                self.time.update(args[0])
            elif type(args[0])== list:
                if len(args[0])==3:
                    self.time.update(dict(zip(['h','m','s'],args[0])))
                if len(args[0])==4:
                    self.time.update(dict(zip(['d','h','m','s'],args[0])))
            else:
                raise ValueError(red('Unsupported input format for TimeFormat. Args is not a list nor a dict.'))
        else:
            raise ValueError(red('Unsupported input format for TimeFormat. Args or kwargs given with more that 1 value.'))


    def __repr__(self):
        time_str = '%02i:%02i:%02i' % (self.time['h'], self.time['m'], self.time['s'])
        if self.time['d']!=0:
            time_str = ('%02i-' %(self.time['d']))+time_str
        return time_str

    def __eq__(self, other):
        return self.time == other.time

    def __lt__(self, other):
        if self.time['d'] < other.time['d']:   return True
        elif self.time['d'] > other.time['d']: return False
        elif self.time['h'] < other.time['h']: return True
        elif self.time['h'] > other.time['h']: return False
        elif self.time['m'] < other.time['m']: return True
        elif self.time['m'] > other.time['m']: return False
        elif self.time['s'] < other.time['s']: return True
        else:                                  return False



class ClusterSpecificSettings():
    def __init__(self, cluster):
        self.Settings = {}
        if 'htcondor_lxplus' in cluster.lower():
            self.htcondor_lxplus()
        if 'htcondor_ulb' in cluster.lower():
            self.htcondor_ulb()
        elif 'slurm_psi' in cluster.lower():
            self.slurm_PSI()

    def getSettings(self):
        return self.Settings

    def slurmGeneral(self):
        self.Settings['Cluster'] = 'slurm'

    def slurm_PSI(self):
        self.slurmGeneral()
        self.Settings['MaxRunTime'] = ('queue', None)
        timedictName = self.Settings['MaxRunTime'][0]
        self.Settings[timedictName] = OrderedDict()
        self.Settings[timedictName]['short'] = TimeFormat('1:00:00')
        self.Settings[timedictName]['standard'] = TimeFormat('12:00:00')
        self.Settings[timedictName]['long'] = TimeFormat('24:00:00')

    def htcondorGeneral(self):
        self.Settings['Cluster'] = 'htcondor'

    def htcondor_lxplus(self):
        self.htcondorGeneral()
        self.Settings['MaxRunTime'] = ('JobFlavour', None)
        timedictName = self.Settings['MaxRunTime'][0]
        self.Settings[timedictName] = OrderedDict()
        self.Settings[timedictName]['espresso'] = TimeFormat('00:20:00')
        self.Settings[timedictName]['microcentury'] = TimeFormat('01:00:00')
        self.Settings[timedictName]['longlunch'] = TimeFormat('02:00:00')
        self.Settings[timedictName]['workday'] = TimeFormat('08:00:00')
        self.Settings[timedictName]['tomorrow'] = TimeFormat('1-00:00:00')
        self.Settings[timedictName]['testmatch'] = TimeFormat('3-00:00:00')
        self.Settings[timedictName]['nextweek'] = TimeFormat('7-00:00:00')

    def htcondor_ulb(self):
        self.htcondorGeneral()
        # self.Settings['MaxRunTime'] = ('RunTime', None)
        # timedictName = self.Settings['MaxRunTime'][0]
        # self.Settings[timedictName] = OrderedDict()
        # self.Settings[timedictName]['standard'] = TimeFormat('01:00:00')
        # self.Settings[timedictName]['long'] = TimeFormat('08:00:00')

    def setJobTimeUpperLimit(self, ref_time = '01:00:00'):
        ref_time_ = TimeFormat(ref_time)
        if not 'MaxRunTime' in self.Settings:
            self.Settings['MaxRunTime'] = (None, None)
            return
        timedict = self.Settings[self.Settings['MaxRunTime'][0]]
        for time_ in timedict:
            if ref_time_ < timedict[time_]:
                self.Settings[self.Settings['MaxRunTime'][1]] = time_
                return
        raise ValueError(red('Runtime exceeds 7 days, please choose something a bit faster.'))
