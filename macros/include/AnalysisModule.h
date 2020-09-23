#pragma once
#include "include/RecoEvent.h"

class GenAnalysisModule {
public:

    virtual bool process(Event & event) = 0;
    virtual ~GenAnalysisModule() = default;
};

class RecoAnalysisModule {
public:

    virtual bool process(RecoEvent & event) = 0;
    virtual ~RecoAnalysisModule() = default;
};
