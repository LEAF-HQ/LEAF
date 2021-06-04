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
  const bool has_prefix(const TString s) const {
    if(m_map.lower_bound(s) != m_map.end()) return true;
    return false;
  };
  const bool get(const TString s) const {if(Flags::has(s)){return m_map.at(s);} else{throw runtime_error("Trying to get non-existent flag '" + s + "' from Flags class.");}};
  const bool get_prefix(const TString s) const {
    if(m_map.lower_bound(s) == m_map.end()) throw runtime_error("Trying to get non-existent flag with pre-fix '" + s + "' from Flags class.");
    for(auto it=m_map.lower_bound(s); it != m_map.end(); ++it){
      if(!it->first.Contains(s)) continue;
      if(it->second) return true;
    }
    return false;
  };
  void set(TString s, bool b) {m_map[s] = b;};


  void list() {
    std::cout << "Available flags:" << std::endl;
    std::cout << "================" << std::endl << std::endl;
    for (auto const & x : m_map) std::cout << x.first << std::endl;
  };



protected:
  std::map<TString, bool> m_map;

};
