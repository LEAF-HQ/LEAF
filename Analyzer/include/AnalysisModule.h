#pragma once
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/GenEvent.h"

template <class E>
class AnalysisModule {
public:

    virtual bool process(E & event) = 0;
    virtual ~AnalysisModule() = default;
};
