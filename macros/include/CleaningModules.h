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

// template <typename T>
// class RecoObjectCleaner : public RecoAnalysisModule{
// public:
//     RecoObjectCleaner(const ID<T> & id_){id = id_;};
//     virtual bool process(RecoEvent & event) override;
//
// private:
//     ID<T> id;
// };
//
// template <typename T>
// bool RecoObjectCleaner::process(RecoEvent & event){
//   clean_collection(event.jets, event, id);
//   return true;
// }



class JetCleaner : public RecoAnalysisModule {
public:
    JetCleaner(const ID<Jet> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Jet> id;
};

class MuonCleaner : public RecoAnalysisModule {
public:
    MuonCleaner(const ID<Muon> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Muon> id;
};

class ElectronCleaner : public RecoAnalysisModule {
public:
    ElectronCleaner(const ID<Electron> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Electron> id;
};

class TauCleaner : public RecoAnalysisModule {
public:
    TauCleaner(const ID<Tau> & id_);
    virtual bool process(RecoEvent & event) override;

private:
    ID<Tau> id;
};
