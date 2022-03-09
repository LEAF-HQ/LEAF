#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/GenEvent.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"

class GenJetCleaner : public AnalysisModule<GenEvent> {
public:
    GenJetCleaner(const GenID<GenJet> & id_);
    virtual bool process(GenEvent & event) override;

private:
    GenID<GenJet> id;
};

class GenJetVisTauCleaner : public AnalysisModule<GenEvent> {
public:
    GenJetVisTauCleaner(const double & mindr_);
    virtual bool process(GenEvent & event) override;

private:
    double mindr;
};

class GenVisTauCleaner : public AnalysisModule<GenEvent> {
public:
    GenVisTauCleaner(const GenID<GenParticle> & id_);
    virtual bool process(GenEvent & event) override;

private:
    GenID<GenParticle> id;
};



class JetCleaner : public AnalysisModule<RecoEvent> {
public:
    JetCleaner(const ID<Jet> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Jet> id;
};

class MuonCleaner : public AnalysisModule<RecoEvent> {
public:
    MuonCleaner(const ID<Muon> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Muon> id;
};

class ElectronCleaner : public AnalysisModule<RecoEvent> {
public:
    ElectronCleaner(const ID<Electron> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Electron> id;
};

class TauCleaner : public AnalysisModule<RecoEvent> {
public:
    TauCleaner(const ID<Tau> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Tau> id;
};


class PFCandCleaner : public AnalysisModule<RecoEvent> {
public:
    PFCandCleaner(const ID<PFCandidate> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<PFCandidate> id;
};
