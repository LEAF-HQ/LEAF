from printing_utils import *

class SampleSettings:

    def __init__(self, name, category, label, color, linestyle, legendtext):
        self.name = name
        self.category = category
        self.label = label
        self.color = color
        self.linestyle = linestyle
        self.legendtext = legendtext

    def __str__(self):
        print('')
        prettydict(self.__dict__, indent=30)
        return ''
    #
    # def __getitem__(self, name):
    #     return self.__dict__[name]
