// #include "include/cosmetics.h"
#include "include/constants.h"
#include "include/useful_functions.h"
#include <TH1D.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TMath.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <sys/stat.h>
#include <libxml/xmlreader.h>

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

/// distance in phi, with the convention -phi < deltaPhi <= phi
// T and U have to have a 'phi()' method, e.g. Particle, LorentzVector, etc.
template<typename T, typename U>
double deltaPhi(const T & p1, const U & p2){
  double result = fabs(p1.phi() - p2.phi());
  if(result > TMath::Pi()) result = 2 * TMath::Pi() - result;
  return result;
}

/// distance in eta
// T and U have to have a 'eta()' method, e.g. Particle etc.
template<typename T, typename U>
double deltaEta(const T & p1, const U & p2){
  double result = fabs(p1.eta() - p2.eta());
  return result;
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


void validateConfigFile(const char *filename){
  xmlTextReaderPtr reader;
  int ret;


  /* default DTD attributes */  /* substitute entities */  /* validate with the DTD */
  reader = xmlReaderForFile(filename, NULL, XML_PARSE_DTDATTR | XML_PARSE_NOENT | XML_PARSE_DTDVALID);
  if (reader != NULL) {
    ret = xmlTextReaderRead(reader);
    while (ret == 1) {
      ret = xmlTextReaderRead(reader);
    }
    /*
    * Once the document has been fully parsed check the validation results
    */
    if (xmlTextReaderIsValid(reader) != 1) {
      fprintf(stderr, "Document %s does not validate\n", filename);
      throw runtime_error("Couldn't validate config file. Abort.");
    }
    xmlFreeTextReader(reader);
    if (ret != 0) {
      throw runtime_error("failed to parse. Abort.");
    }
  }
  else {
    throw runtime_error("Unable to open xml file. Abort.");
    return;
  }
  cout << green << "--> XML file validated." << reset << endl;
}

xmlNode* findNodeByName(xmlNode* rootnode, TString name){
  string s_nn = (string)name;
  const xmlChar* nodename = (xmlChar*)(s_nn.c_str());

  xmlNode* node = rootnode;
  if(node == NULL){
    cout << red << "Document is empty!" << reset << endl;
    return NULL;
  }
  while(node != NULL){

    if(node->type != XML_ELEMENT_NODE){
      node = node->next;
      continue;
    }

    if(!xmlStrcmp(node->name, nodename)){
      return node;
    }
    else if(node->children != NULL){
      // node = node->children;
      xmlNode* intNode =  findNodeByName(node->children, name);
      if(intNode != NULL){
        return intNode;
      }
    }
    node = node->next;
  }
  return NULL;
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


const TString JERCPathString(const string& dataset, const string& version, const string& jetCollection, const string& type, const bool& isJEC) {
  TString result = isJEC? "JEC":"JR";
  result += "Database/textFiles/";
  result += version+"_"+dataset+"/";
  result += version+"_"+dataset+"_";
  result += type+"_"+jetCollection;
  result += ".txt";
  return result;
}

const TString JERPathString(const string& version, const string& jetCollection, const string& correction, const string& runName) {
  string dataset = (runName.find("MC") != string::npos)? "MC": "DATA";
  return JERCPathString(dataset,version,jetCollection,correction,false);
}


const TString JECPathString(const string& version, const string& jetCollection, const string& correction, const string& runName) {
  string dataset = "MC";
  if (runName.find("MC") == string::npos){
    dataset = "DATA";
    string runName_ = TString(runName).ReplaceAll("Run","").Data();
    TString temp = version;
    TString tok; int from = 0;
    temp.Tokenize(tok, from, "_");
    // string newRunName = jecRunMap[tok.Data()][runName_];
    string newRunName = jecRunMap.at(tok.Data()).at(runName_);
    //in 2018 they use "_RunA" instead of just "A"
    if (version.find("18") != string::npos ||  version.find("UL") != string::npos){
      newRunName = "_Run" +runName_;
    }
    string version_ = TString(version).ReplaceAll("_V", newRunName+"_V").Data();
    return JERCPathString(dataset,version_,jetCollection,correction,true);
  }
  return JERCPathString(dataset,version,jetCollection,correction,true);

}
vector<string> JERCFiles(const string& type, const string& runName, const string& version, const string& jetCollection) {
  vector<string> results = {};
  for (const string level: JERCLevels.at(type).at("default")){
    if (type.find("JEC") != string::npos) results.push_back(JECPathString(version, jetCollection, level, runName).Data());
    if (type.find("JER") != string::npos) results.push_back(JERPathString(version, jetCollection, level, runName).Data());
  }
  return results;
}
