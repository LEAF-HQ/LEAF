#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "LEAF/Analyzer/include/GenLevelConstants.h"

bool isLeptonic(int pdgId);
bool isHadronic(int pdgId);
bool isDecayMode(int pdgId1, int pdgId2, Decay decay);

std::string pdgId2str(int);
std::string decay2str(int);
