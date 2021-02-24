#pragma once
#include "include/RecoEvent.h"
#include "include/GenEvent.h"

template <class E>
class Selection {
public:

    virtual bool passes(E & event) = 0;
    virtual ~Selection() = default;
};
