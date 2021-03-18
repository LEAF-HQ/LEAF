#pragma once
#include "Analyzer/include/RecoEvent.h"
#include "Analyzer/include/GenEvent.h"

template <class E>
class AnalysisModule {
public:

    virtual bool process(E & event) = 0;
    virtual ~AnalysisModule() = default;
};
