#include "TMath.h"

#include "LEAF/Analyzer/include/GenLevelUtils.h"


using namespace std;

bool isHadronic(int pdgId) { return (fabs(pdgId) <= 5) ? true : false; }
bool isLeptonic(int pdgId) { return (fabs(pdgId)>= 11 && fabs(pdgId)<=18) ? true : false; }


bool DoubleDecay(int pdgId1, int pdgId2, Decay decay) {
  if (decay==Decay::nodecay) return true;
  if ( isLeptonic(pdgId1) && isLeptonic(pdgId2) && decay == Decay::ll) return true;
  if ( isHadronic(pdgId1) && isHadronic(pdgId2) && decay == Decay::qq) return true;
  if ( fabs(pdgId1) == ParticleID::g     && fabs(pdgId2) == ParticleID::g     && decay == Decay::gg)     return true;
  if ( fabs(pdgId1) <= ParticleID::s     && fabs(pdgId2) <= ParticleID::s     && decay == Decay::light)  return true;
  if ( fabs(pdgId1) == ParticleID::c     && fabs(pdgId2) == ParticleID::c     && decay == Decay::cc)     return true;
  if ( fabs(pdgId1) == ParticleID::b     && fabs(pdgId2) == ParticleID::b     && decay == Decay::bb)     return true;
  if ( fabs(pdgId1) == ParticleID::Z     && fabs(pdgId2) == ParticleID::Z     && decay == Decay::ZZ)     return true;
  if ( fabs(pdgId1) == ParticleID::W     && fabs(pdgId2) == ParticleID::W     && decay == Decay::WW)     return true;
  if ( fabs(pdgId1) == ParticleID::W     && fabs(pdgId2) == ParticleID::b     && decay == Decay::Wb)     return true;
  if ( fabs(pdgId1) == ParticleID::b     && fabs(pdgId2) == ParticleID::W     && decay == Decay::Wb)     return true;
  if ( fabs(pdgId1) == ParticleID::e     && fabs(pdgId2) == ParticleID::e     && decay == Decay::ee)     return true;
  if ( fabs(pdgId1) == ParticleID::mu    && fabs(pdgId2) == ParticleID::mu    && decay == Decay::mumu)   return true;
  if ( fabs(pdgId1) == ParticleID::tau   && fabs(pdgId2) == ParticleID::tau   && decay == Decay::tautau) return true;
  if ( fabs(pdgId1) == ParticleID::e     && fabs(pdgId2) == ParticleID::e     && decay == Decay::ll)     return true;
  if ( fabs(pdgId1) == ParticleID::mu    && fabs(pdgId2) == ParticleID::mu    && decay == Decay::ll)     return true;
  if ( fabs(pdgId1) == ParticleID::v_e   && fabs(pdgId2) == ParticleID::v_e   && decay == Decay::vv)     return true;
  if ( fabs(pdgId1) == ParticleID::v_mu  && fabs(pdgId2) == ParticleID::v_mu  && decay == Decay::vv)     return true;
  if ( fabs(pdgId1) == ParticleID::v_tau && fabs(pdgId2) == ParticleID::v_tau && decay == Decay::vv)     return true;
  return false;
}


string PdgID2str(int pdgId_) {
  ParticleID pdgId = static_cast<ParticleID>(fabs(pdgId_));

  if(pdgId == ParticleID::u)      return "u";
  if(pdgId == ParticleID::d)      return "d";
  if(pdgId == ParticleID::s)      return "s";
  if(pdgId == ParticleID::c)      return "c";
  if(pdgId == ParticleID::b)      return "b";
  if(pdgId == ParticleID::t)      return "t";
  if(pdgId == ParticleID::q)      return "q";
  if(pdgId == ParticleID::e)      return "e";
  if(pdgId == ParticleID::mu)     return "mu";
  if(pdgId == ParticleID::tau)    return "tau";
  if(pdgId == ParticleID::l)      return "l";
  if(pdgId == ParticleID::v_e)    return "v_e";
  if(pdgId == ParticleID::v_mu)   return "v_mu";
  if(pdgId == ParticleID::v_tau)  return "v_tau";
  if(pdgId == ParticleID::v)      return "v";
  if(pdgId == ParticleID::g)      return "g";
  if(pdgId == ParticleID::photon) return "photon";
  if(pdgId == ParticleID::Z)      return "Z";
  if(pdgId == ParticleID::W)      return "W";
  if(pdgId == ParticleID::H)      return "H";
  return "unknown";
}


string Decay2str(int decay_) {

  Decay decay = static_cast<Decay>(fabs(decay_));
  if(decay == Decay::nodecay)        return "nodecay";
  if(decay == Decay::uu)             return "uu";
  if(decay == Decay::dd)             return "dd";
  if(decay == Decay::ss)             return "ss";
  if(decay == Decay::cc)             return "cc";
  if(decay == Decay::bb)             return "bb";
  if(decay == Decay::tt)             return "tt";
  if(decay == Decay::light)          return "light";
  if(decay == Decay::qq)             return "qq";
  if(decay == Decay::gg)             return "gg";
  if(decay == Decay::ee)             return "ee";
  if(decay == Decay::mumu)           return "mumu";
  if(decay == Decay::tautau)         return "tautau";
  if(decay == Decay::ll)             return "ll";
  if(decay == Decay::vv)             return "vv";
  if(decay == Decay::gammagamma)     return "gammagamma";
  if(decay == Decay::ZZ)             return "ZZ";
  if(decay == Decay::WW)             return "WW";
  if(decay == Decay::ZZeeee)         return "ZZeeee";
  if(decay == Decay::ZZmumumumu)     return "ZZmumumumu";
  if(decay == Decay::ZZtautautautau) return "ZZtautautautau";
  if(decay == Decay::ZZvvvv)         return "ZZvvvv";
  if(decay == Decay::ZZeemumu)       return "ZZeemumu";
  if(decay == Decay::ZZeetautau)     return "ZZeetautau";
  if(decay == Decay::ZZeevv)         return "ZZeevv";
  if(decay == Decay::ZZmumutautau)   return "ZZmumutautau";
  if(decay == Decay::ZZmumuvv)       return "ZZmumuvv";
  if(decay == Decay::ZZtautauvv)     return "ZZtautauvv";
  if(decay == Decay::ZZllll)         return "ZZllll";
  if(decay == Decay::ZZqqqq)         return "ZZqqqq";
  if(decay == Decay::ZZqqll)         return "ZZqqll";
  if(decay == Decay::WWveve)         return "WWveve";
  if(decay == Decay::WWvevmu)        return "WWvevmu";
  if(decay == Decay::WWvevtau)       return "WWvevtau";
  if(decay == Decay::WWvlvl)         return "WWvlvl";
  if(decay == Decay::WWqqqq)         return "WWqqqq";
  if(decay == Decay::WWvlqq)         return "WWvlqq";
  if(decay == Decay::Wb)             return "Wb";
  return "nodecay";
}
