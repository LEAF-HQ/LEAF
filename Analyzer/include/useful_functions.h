#pragma once

#include <TString.h>
#include <string>
#include <TH1F.h>
#include <vector>
#include "LEAF/Analyzer/include/constants.h"
#include <libxml/xmlreader.h>
#include "LEAF/Analyzer/include/Particle.h"

// using namespace std;
TString lambstr(double lambda);
TString get_samplename(double mlq, double mx, double mdm, double lambda);
std::vector<int> get_npids();
bool path_exists(const TString &s);

const std::string red("\x1b[0;31m");
const std::string green("\x1b[0;32m");
const std::string yellow("\x1b[0;33m");
const std::string cyan("\x1b[0;36m");
const std::string magenta("\x1b[0;35m");
const std::string reset("\x1b[0m");

// distance in phi, with the convention -phi < deltaPhi <= phi
// T and U have to have a 'phi()' method, e.g. Particle, LorentzVector, etc.
template<typename T, typename U>
double deltaPhi(const T & p1, const U & p2){
  double result = fabs(p1.phi() - p2.phi());
  if(result > TMath::Pi()) result = 2 * TMath::Pi() - result;
  return result;
}

// distance in eta
// T and U have to have a 'eta()' method, e.g. Particle etc.
template<typename T, typename U>
double deltaEta(const T & p1, const U & p2){
  double result = fabs(p1.eta() - p2.eta());
  return result;
}

// template<typename T, typename U>
// double deltaR(const T & p1, const U & p2);
double deltaR(const Particle & p1, const Particle & p2);

template<typename T>
const T * closestParticle(const Particle  & p, const std::vector<T> & particles){
    double deltarmin = std::numeric_limits<double>::infinity();
    const T* next=0;
    for(unsigned int i=0; i<particles.size(); ++i) {
        const T & pi = particles[i];
        double dr = deltaR(pi, p);
        if(dr < deltarmin && &pi != &p) {
            deltarmin = dr;
            next = &pi;
        }
    }
    return next;
}

template<typename P>
inline void sort_by_pt(std::vector<P> & particles){
    std::sort(particles.begin(), particles.end(), [](const P & p1, const P & p2){return p1.pt() > p2.pt();});
}

inline void validateConfigFile(const char *filename){
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
      throw std::runtime_error("Couldn't validate config file. Abort.");
    }
    xmlFreeTextReader(reader);
    if (ret != 0) {
      throw std::runtime_error("failed to parse. Abort.");
    }
  }
  else {
    throw std::runtime_error("Unable to open xml file. Abort.");
    return;
  }
  std::cout << green << "--> XML file validated." << reset << std::endl;
}

inline xmlNode* findNodeByName(xmlNode* rootnode, TString name){
  std::string s_nn = (std::string)name;
  const xmlChar* nodename = (xmlChar*)(s_nn.c_str());

  xmlNode* node = rootnode;
  if(node == NULL){
    std::cout << red << "Document is empty!" << reset << std::endl;
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

inline std::string getNodeProperty(xmlNode* node, const char* property){
  xmlChar* prop = xmlGetProp(node, (xmlChar*)property);
  std::string result = (const char*)prop;
  return result;

}

float getDatasetLumi(xmlNode* node);
TString getDatasetName(xmlNode* node);
TString getDatasetType(xmlNode* node);
TString getDatasetYear(xmlNode* node);
TString getInputFileFileName(xmlNode* node);


TString getJobOutputpath(xmlNode* node);
TString getJobSEDirector(xmlNode* node);
TString getJobPostfix(xmlNode* node);
float   getJobTargetlumi(xmlNode* node);
std::string  getJobAnalysisTool(xmlNode* node);
int     getJobNEventsMax(xmlNode* node);
int     getJobNEventsSkip(xmlNode* node);

std::string getVariableName(xmlNode* node);
std::string getVariableValue(xmlNode* node);

const TString JERCPathString(const std::string& dataset, const std::string& version, const std::string& jetCollection, const std::string& type, const bool& isJEC);
const TString JERPathString(const std::string& version, const std::string& jetCollection, const std::string& correction, const TString& runName);
const TString JECPathString(const std::string& version, const std::string& jetCollection, const std::string& correction, const TString& runName);
std::vector<std::string> JERCFiles(const std::string& type, const TString& runName, const std::string& version, const std::string& jetCollection);
