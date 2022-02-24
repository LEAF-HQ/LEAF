#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "LEAF/Analyzer/include/GenLevelConstants.h"

bool isLeptonic(int pdgId);
bool isHadronic(int pdgId);
bool DoubleDecay(int pdgId1, int pdgId2, Decay decay);

std::string PdgID2str(int);
std::string Decay2str(int);
