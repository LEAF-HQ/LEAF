#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "LEAF/Analyzer/include/GenLevelConstants.h"

bool isLeptonic(int pdgId);
bool isLeptonic(ParticleID pdgId);
bool isHadronic(int pdgId);
bool isHadronic(ParticleID pdgId);
bool isDecayMode(int pdgId1, ParticleID pdgId2, Decay decay);
bool isDecayMode(ParticleID pdgId1, ParticleID pdgId2, Decay decay);

std::string pdgId2str(int);
std::string pdgId2str(ParticleID);
std::string type2str(int);
std::string type2str(ParticleType);
std::string decay2str(int);
std::string decay2str(Decay);
