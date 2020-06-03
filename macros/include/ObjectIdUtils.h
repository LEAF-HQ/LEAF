#pragma once

#include <functional>
#include "Event.h"

typedef std::function<bool (const GenJet &, const Event &)> GenJetId;
typedef std::function<bool (const GenParticle &, const Event &)> GenParticleId;


class PtEtaId{
public:
 PtEtaId(float min_pt_, float max_eta_, float max_pt_ =-1, float min_eta_=-1): min_pt(min_pt_), max_eta(max_eta_), max_pt(max_pt_),min_eta(min_eta_){}

    bool operator()(const Particle & p, const Event & ) const{
      return p.pt() > min_pt && (p.pt() < max_pt || max_pt == -1) && std::fabs(p.eta()) < max_eta && std::fabs(p.eta()) > min_eta ;
    }

private:
    float min_pt, max_eta, max_pt, min_eta ;
};

template<typename T>
inline void clean_collection(std::vector<T>* objects, const Event & event, const std::function<bool (const T &, const Event &)> id){
    std::vector<T> result;
    for(size_t i=0; i<objects->size(); i++){
        T obj = objects->at(i);
        if(id(obj, event)){
            result.emplace_back(obj);
        }
    }
    std::swap(result, *objects);
    return;
}
