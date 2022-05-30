from printing_utils import prettydict

class InfoSettings:
    def __init__(self, **kwargs):
        self.__dict__.update(kwargs)

    def __str__(self):
        print('')
        prettydict(self.__dict__, indent=30)
        return ''

    def __getitem__(self, name):
        return self.__dict__[name]

    def __setitem__(self, name,val):
        self.__dict__[name] = val




class SampleSettings(InfoSettings):
    def __init__(self, filename, samplename, category):
        InfoSettings.__init__(self, filename=filename, samplename=samplename, category=category)
