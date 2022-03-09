#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "LEAF/Analyzer/include/FlavorParticle.h"

using namespace std;

// Basically a FlavorParticle with a number of daughters
class GenParticle : public FlavorParticle {

public:

  enum class StatusFlag{
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

  // Easier access to StatusFlag bools
  bool isHardProcess() const {return get_statusflag(StatusFlag::isHardProcess);};
  bool fromHardProcess() const {return get_statusflag(StatusFlag::fromHardProcess);};
  bool fromHardProcessBeforeFSR() const {return get_statusflag(StatusFlag::fromHardProcessBeforeFSR);};
  bool isPrompt() const {return get_statusflag(StatusFlag::isPrompt);};
  bool isFirstCopy() const {return get_statusflag(StatusFlag::isFirstCopy);};
  bool isLastCopy() const {return get_statusflag(StatusFlag::isLastCopy);};
  bool isLastCopyBeforeFSR() const {return get_statusflag(StatusFlag::isLastCopyBeforeFSR);};
  bool isDecayedLeptonHadron() const {return get_statusflag(StatusFlag::isDecayedLeptonHadron);};
  bool isDirectHadronDecayProduct() const {return get_statusflag(StatusFlag::isDirectHadronDecayProduct);};
  bool isTauDecayProduct() const {return get_statusflag(StatusFlag::isTauDecayProduct);};
  bool isPromptTauDecayProduct() const {return get_statusflag(StatusFlag::isPromptTauDecayProduct);};
  bool isHardProcessTauDecayProduct() const {return get_statusflag(StatusFlag::isHardProcessTauDecayProduct);};
  bool isDirectHardProcessTauDecayProduct() const {return get_statusflag(StatusFlag::isDirectHardProcessTauDecayProduct);};
  bool isDirectTauDecayProduct() const {return get_statusflag(StatusFlag::isDirectTauDecayProduct);};
  bool isDirectPromptTauDecayProduct() const {return get_statusflag(StatusFlag::isDirectPromptTauDecayProduct);};

  // Easier access to combinations of StatusFlag bools
  bool isFinalState() const {
    return (status() == 1);
  }

  bool fromHardProcessFinalState() const {
    return (get_statusflag(StatusFlag::fromHardProcess) && isFinalState());
  }
  bool fromHardProcessDecayed() const {
    return (get_statusflag(StatusFlag::isDecayedLeptonHadron) && get_statusflag(StatusFlag::fromHardProcess));
  }
  bool isPromptFinalState() const {
    return (get_statusflag(StatusFlag::isPrompt) && isFinalState());
  }
  bool isPromptDecayed() const {
    return (get_statusflag(StatusFlag::isDecayedLeptonHadron) && get_statusflag(StatusFlag::isPrompt));
  }


protected:
  uint64_t m_statusflag_bits;
  int m_ndaughters;
  int m_mother_identifier;
  int m_status;
  int m_identifier;



};
