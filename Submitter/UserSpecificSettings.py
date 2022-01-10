import os, json

class UserSpecificSettings():
    """docstring for UserSpecificSettings."""

    def __init__(self, name, email='', cluster=''):
        self.UserInfo = {
            'username': name,
            'email':    email,
            'cluster':  cluster,
            }

    def GetJSONPath(self,name):
        return os.getenv('SUBMITTERPATH')+'/Settings_'+name+'.json'

    def LoadJSON(self, name=''):
        json_name = name if name !='' else self.GetJSONPath(name)
        with open(json_name, 'r') as f:
            self.UserInfo = json.load(f)

    def SaveJSON(self):
        with open(self.GetJSONPath(name), 'w') as f:
            json.dump(self.UserInfo, f, sort_keys=True, indent=4)

    def Set(self,name,info):
        self.UserInfo.update({name:info})

    def Get(self,name):
        return self.UserInfo[name]
