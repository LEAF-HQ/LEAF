#pragma once

#include "AnalysisModule.h"
#include "Event.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"

class GenJetCleaner : public AnalysisModule {
public:
    GenJetCleaner(const GenJetId & id_);
    virtual bool process(Event & event) override;

private:
    GenJetId id;
};

class GenJetVisTauCleaner : public AnalysisModule {
public:
    GenJetVisTauCleaner(const double & mindr_);
    virtual bool process(Event & event) override;

private:
    double mindr;
};

class GenVisTauCleaner : public AnalysisModule {
public:
    GenVisTauCleaner(const GenParticleId & id_);
    virtual bool process(Event & event) override;

private:
    GenParticleId id;
};
