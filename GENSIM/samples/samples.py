import copy

from Sample import *
from Storage import *
from Signals import signals
from Backgrounds import backgrounds
from Data import data

def merge_dicts_safe(dict1, dict2):
    result = copy.deepcopy(dict1)
    for key in dict2.keys():
        if key in result:
            raise ValueError('Duplicate keys encountered when merging dicts. Prefer to exit. If this error should be ignored, use python\'s "dict.update()" instead.')
        result[key] = dict2[key]
    return result


def create_sample_dict_safe():
    result = {}
    return merge_dicts_safe(merge_dicts_safe(merge_dicts_safe(result, backgrounds), data), signals)
    return result

samples = {}
samples.update(backgrounds)
samples.update(data)
samples.update(signals)
