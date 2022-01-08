from copy import deepcopy
from utils import red
from functools import total_ordering
from collections import OrderedDict

@total_ordering
class TimeFormat():
    def __init__(self, *args, **kwargs):
        self.time = {'g':0,'h':0,'m':0,'s':0}
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
                    self.time['g'], self.time['h'] = (int(parts[0].split('-')[0]),int(parts[0].split('-')[1]))
                else:
                    self.time['h'] = int(parts[0])
                self.time['m'], self.time['s'] = (int(parts[1]), int(parts[2]))
            elif type(args[0])== dict:
                self.time.update(args[0])
            elif type(args[0])== list:
                if len(args[0])==3:
                    self.time.update(dict(zip(['h','m','s'],args[0])))
                if len(args[0])==4:
                    self.time.update(dict(zip(['g','h','m','s'],args[0])))
            else:
                raise ValueError(red('Unsupported input format for TimeFormat. Args is not a list nor a dict.'))
        else:
            raise ValueError(red('Unsupported input format for TimeFormat. Args or kwargs given with more that 1 value.'))


    def __repr__(self):
        time_str = '%02i:%02i:%02i' % (self.time['h'], self.time['m'], self.time['s'])
        if self.time['g']!=0:
            time_str = ('%02i-' %(self.time['g']))+time_str
        return time_str

    def __eq__(self, other):
        return self.time == other.time

    def __lt__(self, other):
        if self.time['g'] < other.time['g']:   return True
        elif self.time['g'] > other.time['g']: return False
        elif self.time['h'] < other.time['h']: return True
        elif self.time['h'] > other.time['h']: return False
        elif self.time['m'] < other.time['m']: return True
        elif self.time['m'] > other.time['m']: return False
        elif self.time['s'] < other.time['s']: return True
        else:                                  return False



class ClusterSpecificSettings():
    def __init__(self):
        self.Settings = {}

    def getSettings(self, name):
        if "lxplus" in name.lower():
            self.htcondor_lxplus()
        return self.Settings()

    def slurmGeneral(self):
        self.Settings["Cluster"] = "slurm"

    def slurm_PSI(self):
        self.slurmGeneral()
        self.Settings['JobFlavour'] = OrderedDict()
        self.Settings['JobFlavour']['short'] = TimeFormat('1:00:00')
        self.Settings['JobFlavour']['standard'] = TimeFormat('12:00:00')
        self.Settings['JobFlavour']['long'] = TimeFormat('24:00:00')

    def htcondorGeneral(self):
        self.Settings["Cluster"] = "htcondor"

    def htcondor_lxplus(self):
        self.htcondorGeneral()
        self.Settings['JobFlavour'] = OrderedDict()
        self.Settings['JobFlavour']['espresso'] = TimeFormat('00:20:00')
        self.Settings['JobFlavour']['microcentury'] = TimeFormat('01:00:00')
        self.Settings['JobFlavour']['longlunch'] = TimeFormat('02:00:00')
        self.Settings['JobFlavour']['workday'] = TimeFormat('08:00:00')
        self.Settings['JobFlavour']['tomorrow'] = TimeFormat('1-00:00:00')
        self.Settings['JobFlavour']['testmatch'] = TimeFormat('3-00:00:00')
        self.Settings['JobFlavour']['nextweek'] = TimeFormat('7-00:00:00')

    def GetTimeUpperLimit(self, givenTime_ = '01:00:00', format='name'):
        givenTime = TimeFormat(givenTime_)
        for time in self.Settings['JobFlavour']:
            if givenTime < self.Settings['JobFlavour'][time]:
                if format=='name': return time
                elif format=='time': return self.Settings['JobFlavour'][time]
                else return (time,self.Settings['JobFlavour'][time])
        raise ValueError(red('Runtime exceeds 7 days, please choose something a bit faster.'))
