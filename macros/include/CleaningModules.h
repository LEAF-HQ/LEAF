#pragma once

#include "AnalysisModule.h"
#include "Event.h"
#include "RecoEvent.h"
#include "ObjectIdUtils.h"
#include "useful_functions.h"

class GenJetCleaner : public GenAnalysisModule {
public:
    GenJetCleaner(const GenJetId & id_);
    virtual bool process(Event & event) override;

private:
    GenJetId id;
};

class GenJetVisTauCleaner : public GenAnalysisModule {
public:
    GenJetVisTauCleaner(const double & mindr_);
    virtual bool process(Event & event) override;

private:
    double mindr;
};

class GenVisTauCleaner : public GenAnalysisModule {
public:
    GenVisTauCleaner(const GenParticleId & id_);
    virtual bool process(Event & event) override;

private:
    GenParticleId id;
};

class JetCleaner : public RecoAnalysisModule {
public:
    JetCleaner(const JetId & id_);
    virtual bool process(RecoEvent & event) override;

private:
    JetId id;
};

class MuonCleaner : public RecoAnalysisModule {
public:
    MuonCleaner(const MuonId & id_);
    virtual bool process(RecoEvent & event) override;

private:
    MuonId id;
};

class ElectronCleaner : public RecoAnalysisModule {
public:
    ElectronCleaner(const ElectronId & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ElectronId id;
};

class TauCleaner : public RecoAnalysisModule {
public:
    TauCleaner(const TauId & id_);
    virtual bool process(RecoEvent & event) override;

private:
    TauId id;
};
