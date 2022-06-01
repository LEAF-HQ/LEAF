#include "TMath.h"

#include "LEAF/Analyzer/include/GenLevelUtils.h"


using namespace std;

bool isHadronic(int pdgId) { return (abs(pdgId) <= 5) ? true : false; }
bool isLeptonic(int pdgId) { return (abs(pdgId) >= 11 && abs(pdgId)<=18 && (abs(pdgId)%2 != 0)) ? true : false; }
bool isNeutrino(int pdgId) { return (abs(pdgId) >= 11 && abs(pdgId)<=18 && (abs(pdgId)%2 == 0)) ? true : false; }

Decay GetDecayMode(ParticleID pdgId1, ParticleID pdgId2) {
  if ( pdgId1 == ParticleID::g     && pdgId2 == ParticleID::g)     return Decay::gg;
  if ( pdgId1 <= ParticleID::s     && pdgId2 <= ParticleID::s)     return Decay::light;
  if ( pdgId1 == ParticleID::c     && pdgId2 == ParticleID::c)     return Decay::cc;
  if ( pdgId1 == ParticleID::b     && pdgId2 == ParticleID::b)     return Decay::bb;
  if ( pdgId1 == ParticleID::Z     && pdgId2 == ParticleID::Z)     return Decay::ZZ;
  if ( pdgId1 == ParticleID::W     && pdgId2 == ParticleID::W)     return Decay::WW;
  if ( pdgId1 == ParticleID::W     && pdgId2 == ParticleID::b)     return Decay::Wb;
  if ( pdgId1 == ParticleID::b     && pdgId2 == ParticleID::W)     return Decay::Wb;
  if ( pdgId1 == ParticleID::e     && pdgId2 == ParticleID::e)     return Decay::ee;
  if ( pdgId1 == ParticleID::mu    && pdgId2 == ParticleID::mu)    return Decay::mumu;
  if ( pdgId1 == ParticleID::tau   && pdgId2 == ParticleID::tau)   return Decay::tautau;
  if ( isNeutrino(pdgId1)          && pdgId2 == ParticleID::e)     return Decay::ve;
  if ( isNeutrino(pdgId1)          && pdgId2 == ParticleID::mu)    return Decay::vmu;
  if ( isNeutrino(pdgId1)          && pdgId2 == ParticleID::tau)   return Decay::vtau;
  if ( isNeutrino(pdgId1)          && isNeutrino(pdgId2))          return Decay::vv;
  return Decay::nodecay;
}

bool isDecayMode(ParticleID pdgId1, ParticleID pdgId2, Decay decay) {
  if (decay==Decay::nodecay) return true;
  if ( GetDecayMode(pdgId1, pdgId2) == decay ) return true;
  if ( isLeptonic(pdgId1) && isLeptonic(pdgId2) && decay == Decay::ll) return true;
  if ( isHadronic(pdgId1) && isHadronic(pdgId2) && decay == Decay::qq) return true;
  return false;
}


string pdgId2str(ParticleID pdgId) {
  if(pdgId == ParticleID::d)      return "d";
  if(pdgId == ParticleID::u)      return "u";
  if(pdgId == ParticleID::s)      return "s";
  if(pdgId == ParticleID::c)      return "c";
  if(pdgId == ParticleID::b)      return "b";
  if(pdgId == ParticleID::t)      return "t";
  if(pdgId == ParticleID::q)      return "q";
  if(pdgId == ParticleID::e)      return "e";
  if(pdgId == ParticleID::mu)     return "#mu";
  if(pdgId == ParticleID::tau)    return "#tau";
  if(pdgId == ParticleID::l)      return "l";
  if(pdgId == ParticleID::v_e)    return "#nu_{e}";
  if(pdgId == ParticleID::v_mu)   return "#nu_{#mu}";
  if(pdgId == ParticleID::v_tau)  return "#nu_{#tau}";
  if(pdgId == ParticleID::v)      return "#nu";
  if(pdgId == ParticleID::g)      return "g";
  if(pdgId == ParticleID::photon) return "#gamma";
  if(pdgId == ParticleID::Z)      return "Z";
  if(pdgId == ParticleID::W)      return "W";
  if(pdgId == ParticleID::H)      return "H";
  if(pdgId == ParticleID::pi_0)   return "#pi^{0}";
  if(pdgId == ParticleID::pi_plus)   return "#pi^{+}";
  if(pdgId == ParticleID::kaon_0_L)  return "K^{0}_{L}";
  if(pdgId == ParticleID::kaon_0_S)  return "K^{0}_{S}";
  if(pdgId == ParticleID::kaon_0)    return "K^{0}";
  if(pdgId == ParticleID::kaon_plus) return "K^{+}";
  if(pdgId == ParticleID::kaon_star_plus) return "K^{*+}";
  if(pdgId == ParticleID::kaon_star_0) return "K^{*0}";
  if(pdgId == ParticleID::D_plus)      return "D^{+}";
  if(pdgId == ParticleID::D_plus_S)    return "D^{+}_{S}";
  if(pdgId == ParticleID::D_star_plus) return "D^{*+}";
  if(pdgId == ParticleID::D_0)         return "D^{0}";
  if(pdgId == ParticleID::D_star_0)    return "D^{*0}";
  if(pdgId == ParticleID::phi)         return "#phi";
  if(pdgId == ParticleID::rho_0)       return "#rho^{0}";
  if(pdgId == ParticleID::rho_plus)    return "#rho^{+}";
  if(pdgId == ParticleID::omega)       return "#omega";
  if(pdgId == ParticleID::delta_plus_plus) return "#Delta^{++}";
  if(pdgId == ParticleID::lambda) return "#Lambda";
  if(pdgId == ParticleID::proton) return "p";
  return "unknown";
}


string decay2str(Decay decay) {
  if(decay == Decay::nodecay)        return "nodecay";
  if(decay == Decay::dd)             return "dd";
  if(decay == Decay::uu)             return "uu";
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
  if(decay == Decay::ve)             return "ve";
  if(decay == Decay::vmu)            return "vmu";
  if(decay == Decay::vtau)           return "vtau";
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

std::string type2str(ParticleType type){
  if(type == ParticleType::X)         return "undefined";
  if(type == ParticleType::e)         return "e";
  if(type == ParticleType::mu)        return "#mu";
  if(type == ParticleType::gamma)     return "#gamma";
  if(type == ParticleType::h)         return "ch. had.";
  if(type == ParticleType::h0)        return "neut. had.";
  if(type == ParticleType::h_HF)      return "HF had";
  if(type == ParticleType::egamma_HF) return "HF EM";
  return "undefined";
}


bool isHadronic(ParticleID pdgId) { return isHadronic((int)pdgId);}
bool isLeptonic(ParticleID pdgId) { return isLeptonic((int)pdgId);}
bool isNeutrino(ParticleID pdgId) { return isNeutrino((int)pdgId);}


Decay GetDecayMode(int pdgId1_, int pdgId2_) {
  return GetDecayMode(static_cast<ParticleID>(abs(pdgId1_)),static_cast<ParticleID>(abs(pdgId2_)));
}

bool isDecayMode(int pdgId1_, int pdgId2_, Decay decay) {
  return isDecayMode(static_cast<ParticleID>(abs(pdgId1_)),static_cast<ParticleID>(abs(pdgId2_)), decay);
}

string pdgId2str(int pdgId_) {
  return pdgId2str(static_cast<ParticleID>(abs(pdgId_)));
}

string decay2str(int decay_) {
  return decay2str(static_cast<Decay>(abs(decay_)));
}

std::string type2str(int type_){
  return type2str(static_cast<ParticleType>(abs(type_)));
}
