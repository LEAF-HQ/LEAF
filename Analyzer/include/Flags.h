#pragma once
#include <TString.h>




// Container class for event flags
class Flags {

public:
  // Constructors, destructor
  Flags() = default;
  Flags(const Flags &) = default;
  Flags & operator = (const Flags &) = default;
  ~Flags() = default;

  const bool has(const TString s) const {auto it = m_map.find(s); return (it != m_map.end());};
  const bool get(const TString s) const {if(Flags::has(s)){return m_map.at(s);} else{throw runtime_error("Trying to get non-existent flag '" + s + "' from Flags class.");}};
  void set(TString s, bool b) {m_map[s] = b;};



protected:
  std::map<TString, bool> m_map;

};
