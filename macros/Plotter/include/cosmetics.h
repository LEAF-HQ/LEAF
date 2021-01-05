#pragma once

#include <TMultiGraph.h>
#include <TPad.h>
#include <TH1D.h>
#include <TGraph.h>


TPad* SetupPad();
TPad* SetupRatioPad();
TPad* SetupRatioPadTop();
void HistCosmetics(TH1* hist, bool ratio = false);
void HistCosmetics(TGraph* hist, bool ratio = false);
void HistCosmetics(TMultiGraph* hist, bool ratio = false);
