#include "LEAF/Analyzer/include/useful_functions.h"

using namespace std;

TString lambstr(double lambda){
  ostringstream ss;
  ss << fixed << setprecision(1) << lambda;
  string s(ss.str());
  TString result = s;
  result = result.ReplaceAll(".", "p");
  return result;
}

TString get_samplename(double mlq, double mx, double mdm, double lambda){
  TString result = "MLQ";
  result += mlq;
  result += "_MX";
  result += mx;
  result += "_MDM";
  result += mdm;
  result += "_L";
  result += lambstr(lambda);
  return result;
}

vector<int> get_npids(){
  vector<int> npids = lqids;
  npids.insert(npids.end(), psiids.begin(), psiids.end());
  npids.insert(npids.end(), chiids.begin(), chiids.end());
  return npids;
}

bool path_exists(const TString &s){
  struct stat buffer;
  return (stat(s, &buffer) == 0);
}




/// distance in R
// T and U have to have a 'eta()' and 'phi()' method, e.g. Particle etc.
// template<typename T, typename U>
// double deltaR(const T & p1, const U & p2){
double deltaR(const Particle & p1, const Particle & p2){
  double de = deltaEta(p1, p2);
  double dp = deltaPhi(p1, p2);
  return sqrt(de * de + dp * dp);
}


float getDatasetLumi(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Lumi");
  string s_lumi = (const char*)prop;
  float lumi = stod(s_lumi);
  return lumi;
}

TString getDatasetName(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Name");
  TString name = (const char*)prop;
  return name;
}

TString getDatasetType(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Type");
  TString type = (const char*)prop;
  return type;
}

TString getDatasetYear(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Year");
  TString type = (const char*)prop;
  return type;
}

TString getInputFileFileName(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"FileName");
  TString file = (const char*)prop;
  return file;
}

TString getJobOutputpath(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"OutputDirectory");
  TString path = (const char*)prop;
  return path;
}

TString getJobSEDirector(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"SEDirector");
  TString path = (const char*)prop;
  return path;
}

TString getJobPostfix(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"PostFix");
  TString pf = (const char*)prop;
  return pf;
}

float getJobTargetlumi(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"TargetLumi");
  string s_lumi = (const char*)prop;
  float lumi = stod(s_lumi);
  return lumi;
}

string getJobAnalysisTool(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"AnalysisTool");
  string at = (const char*)prop;
  return at;
}

int getJobNEventsMax(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"NEventsMax");
  string s_nevt = (const char*)prop;
  int lumi = stoi(s_nevt);
  return lumi;
}

int getJobNEventsSkip(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"NEventsSkip");
  string s_nevt = (const char*)prop;
  int lumi = stoi(s_nevt);
  return lumi;
}

string getVariableName(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Name");
  string name = (const char*)prop;
  return name;
}

string getVariableValue(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"Value");
  string value = (const char*)prop;
  return value;
}



string getCollectionClassname(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"ClassName");
  string value = (const char*)prop;
  return value;
}

string getCollectionBranchname(xmlNode* node){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)"BranchName");
  string value = (const char*)prop;
  return value;
}




const TString JERCPathString(const string& dataset, const string& version, const string& jetCollection, const string& type, const bool& isJEC) {
  TString result = isJEC? "JEC":"JR";
  result += "Database/textFiles/";
  result += version+"_"+dataset+"/";
  result += version+"_"+dataset+"_";
  result += type+"_"+jetCollection;
  result += ".txt";
  return result;
}

const TString JERPathString(const string& version, const string& jetCollection, const string& correction, const TString& runName) {
  string dataset = (runName.Contains("MC"))? "MC": "DATA";
  return JERCPathString(dataset,version,jetCollection,correction,false);
}


const TString JECPathString(const string& version, const string& jetCollection, const string& correction, const TString& runName) {
  string dataset = "MC";
  if (!runName.Contains("MC")){
    dataset = "DATA";
    string runName_ = TString(runName).ReplaceAll("Run","").Data();
    TString temp = version;
    TString tok; int from = 0;
    temp.Tokenize(tok, from, "_");
    string newRunName = Run2JECName.at(tok.Data()).at(runName_);

    //in 2018 and UL, they use "_RunX" instead of just "X"
    if (version.find("18") != string::npos ||  version.find("UL") != string::npos){
      newRunName = "_Run" +runName_;
    }
    string version_ = TString(version).ReplaceAll("_V", newRunName+"_V").Data();
    return JERCPathString(dataset,version_,jetCollection,correction,true);
  }
  return JERCPathString(dataset,version,jetCollection,correction,true);

}
vector<string> JERCFiles(const string& type, const TString& runName, const string& version, const string& jetCollection) {
  vector<string> results = {};
  for (const string level: JERCLevels.at(type).at("default")){
    if (type.find("JEC") != string::npos) results.push_back(JECPathString(version, jetCollection, level, runName).Data());
    if (type.find("JER") != string::npos) results.push_back(JERPathString(version, jetCollection, level, runName).Data());
  }
  return results;
}


bool closeFloat(float a, float b, float maxRelDiff, float maxAbsDiff) {
  return fabs(a-b) <= max(maxRelDiff * max(fabs(a), fabs(b)), maxAbsDiff);
}


bool FindInString(const std::string& search, const std::string& str) {
  return str.find(search)!=std::string::npos ;
}
