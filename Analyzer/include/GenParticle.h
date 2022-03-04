#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/FlavorParticle.h"

using namespace std;

// Basically a FlavorParticle with a number of daughters
class GenParticle : public FlavorParticle {

public:

  enum StatusFlag{
    isHardProcess,
    fromHardProcess,
    fromHardProcessBeforeFSR,
    isPrompt,
    isFirstCopy,
    isLastCopy,
    isLastCopyBeforeFSR,
    isDecayedLeptonHadron,
    isDirectHadronDecayProduct,
    isTauDecayProduct,
    isPromptTauDecayProduct,
    isHardProcessTauDecayProduct,
    isDirectHardProcessTauDecayProduct,
    isDirectTauDecayProduct,
    isDirectPromptTauDecayProduct,
  };


  // Constructors, destructor
  GenParticle(){
    m_statusflag_bits = -1;
    m_ndaughters = -1;
    m_mother_identifier = -1;
    m_status = -1;
    m_identifier = -1;
  }



  bool get_statusflag(StatusFlag i) const {
    return (m_statusflag_bits & (uint64_t(1) << static_cast<uint64_t>(i)));
  }

  void set_statusflag(StatusFlag i, bool value) {
    if(value) m_statusflag_bits |=   uint64_t(1) << static_cast<uint64_t>(i);
    else      m_statusflag_bits &= ~(uint64_t(1) << static_cast<uint64_t>(i));
  }

  uint64_t statusflag_bits() const {return m_statusflag_bits;};
  int ndaughters() const {return m_ndaughters;};
  int mother_identifier() const {return m_mother_identifier;};
  int status() const {return m_status;};
  int identifier() const {return m_identifier;};


  void set_statusflag_bits(uint64_t x){m_statusflag_bits = x;};
  void set_ndaughters(int x) {m_ndaughters = x;};
  void set_mother_identifier(int x) {m_mother_identifier = x;};
  void set_status(int x) {m_status = x;};
  void set_identifier(int x) {m_identifier = x;};


  bool fromHardProcessFinalState() const {
    return (get_statusflag(GenParticle::fromHardProcess) && status() == 1);
  }
  bool fromHardProcessDecayed() const {
    return (get_statusflag(GenParticle::isDecayedLeptonHadron) && get_statusflag(GenParticle::fromHardProcess));
  }
  bool isPromptFinalState() const {
    return (get_statusflag(GenParticle::isPrompt) && status() == 1);
  }
  bool isPromptDecayed() const {
    return (get_statusflag(GenParticle::isDecayedLeptonHadron) && get_statusflag(GenParticle::isPrompt));
  }


protected:
  uint64_t m_statusflag_bits;
  int m_ndaughters;
  int m_mother_identifier;
  int m_status;
  int m_identifier;



};
