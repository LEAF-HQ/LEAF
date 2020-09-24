#pragma once
#include "include/RecoEvent.h"
#include "include/GenEvent.h"

template <class E>
class AnalysisModule {
public:

    virtual bool process(E & event) = 0;
    virtual ~AnalysisModule() = default;
};
