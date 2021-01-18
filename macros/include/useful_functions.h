#pragma once

#include <TString.h>
#include <TH1F.h>
#include <vector>
#include "include/constants.h"
#include <libxml/xmlreader.h>
#include "include/Particle.h"

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

template<typename T, typename U>
double deltaPhi(const T & p1, const U & p2);

template<typename T, typename U>
double deltaEta(const T & p1, const U & p2);

// template<typename T, typename U>
// double deltaR(const T & p1, const U & p2);
double deltaR(const Particle & p1, const Particle & p2);

template<typename P>
inline void sort_by_pt(std::vector<P> & particles){
    std::sort(particles.begin(), particles.end(), [](const P & p1, const P & p2){return p1.pt() > p2.pt();});
}

void validateConfigFile(const char *filename);
xmlNode* findNodeByName(xmlNode* rootnode, TString name);

float getDatasetLumi(xmlNode* node);
TString getDatasetName(xmlNode* node);
TString getDatasetType(xmlNode* node);
// TString getDatasetFilename(xmlNode* node);
TString getInputFileFileName(xmlNode* node);


TString getJobOutputpath(xmlNode* node);
TString getJobSEDirector(xmlNode* node);
TString getJobPostfix(xmlNode* node);
float   getJobTargetlumi(xmlNode* node);
string  getJobAnalysisTool(xmlNode* node);
int     getJobNEventsMax(xmlNode* node);
int     getJobNEventsSkip(xmlNode* node);

std::string getVariableName(xmlNode* node);
std::string getVariableValue(xmlNode* node);
