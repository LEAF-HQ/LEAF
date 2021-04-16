#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include "Analyzer/include/FlavorParticle.h"

using namespace std;

// Basically a FlavorParticle with a number of daughters
class GenParticle : public FlavorParticle {

public:

  enum StatusFlag{
    isPrompt,
    isDecayedLeptonHadron,
    isTauDecayProduct,
    isPromptTauDecayProduct,
    isDirectTauDecayProduct,
    isDirectPromptTauDecayProduct,
    isDirectHadronDecayProduct,
    isHardProcess,
    fromHardProcess,
    isHardProcessTauDecayProduct,
    isDirectHardProcessTauDecayProduct,
    fromHardProcessBeforeFSR,
    isFirstCopy,
    isLastCopy,
    isLastCopyBeforeFSR
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

  uint64_t statusflag_bits(){return m_statusflag_bits;};
  int ndaughters() const {return m_ndaughters;};
  int mother_identifier() const {return m_mother_identifier;};
  int status() const {return m_status;};
  int identifier() const {return m_identifier;};


  void set_statusflag_bits(uint64_t x){m_statusflag_bits = x;};
  void set_ndaughters(int x) {m_ndaughters = x;};
  void set_mother_identifier(int x) {m_mother_identifier = x;};
  void set_status(int x) {m_status = x;};
  void set_identifier(int x) {m_identifier = x;};


protected:
  uint64_t m_statusflag_bits;
  int m_ndaughters;
  int m_mother_identifier;
  int m_status;
  int m_identifier;



};
