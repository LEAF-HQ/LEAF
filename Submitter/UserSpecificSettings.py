import os, json

class UserSpecificSettings():
    """docstring for UserSpecificSettings."""

    def __init__(self, username, email='', cluster=''):
        self.UserInfo = {
            'username': username,
            'email':    email,
            'cluster':  cluster,
            }

    def GetJSONPath(self,username):
        return os.getenv('SUBMITTERPATH')+'/Settings_'+username+'.json'

    def LoadJSON(self, name=''):
        json_name = name if name !='' else self.GetJSONPath(self.UserInfo['username'])
        with open(json_name, 'r') as f:
            self.UserInfo = json.load(f)

    def SaveJSON(self):
        with open(self.GetJSONPath(self.UserInfo['username']), 'w') as f:
            json.dump(self.UserInfo, f, sort_keys=True, indent=4)

    def Set(self,name,info):
        self.UserInfo.update({name:info})

    def Get(self,name):
        return self.UserInfo[name]
