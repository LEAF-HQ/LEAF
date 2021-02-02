#pragma once

#include <TString.h>
#include <string>
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

void validateConfigFile(const char *filename);
xmlNode* findNodeByName(xmlNode* rootnode, TString name);

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
