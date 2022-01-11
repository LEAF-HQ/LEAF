#pragma once
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/GenEvent.h"

template <class E>
class Selection {
public:

    virtual bool passes(E & event) = 0;
    virtual ~Selection() = default;
};
