#pragma once

#include "AnalysisModule.h"
#include "Event.h"
#include "ObjectIdUtils.h"

class GenJetCleaner : public AnalysisModule {
public:

    GenJetCleaner(const GenJetId & id_);
    virtual bool process(Event & event) override;

private:
    GenJetId id;
};
