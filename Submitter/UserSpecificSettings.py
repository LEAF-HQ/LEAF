import os, json

class UserSpecificSettings():
    """docstring for UserSpecificSettings."""

    def __init__(self, name, email='', cluster=''):
        self.UserInfo = {
            'username': name,
            'xml':      self.GetXMLPath(name),
            'email':    email,
            'cluster':  cluster,
            }

    def GetXMLPath(self,name):
        return os.getenv('SUBMITTERPATH')+'/Settings_'+name+'.xml'

    def LoadXml(self, name=''):
        xml_name = name if name !='' else self.UserInfo['xml']
        with open(xml_name, 'r') as f:
            self.UserInfo = json.load(f)

    def SaveXml(self):
        with open(self.UserInfo['xml'], 'w') as f:
            json.dump(self.UserInfo, f, sort_keys=True, indent=4)

    def Set(self,name,info):
        self.UserInfo.update({name:info})

    def Get(self,name):
        return self.UserInfo[name]
