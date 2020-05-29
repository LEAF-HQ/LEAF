#pragma once




// Container class for MET
class Met {

public:
  // Constructors, destructor
  Met() = default;
  Met(const Met &) = default;
  Met & operator = (const Met &) = default;
  ~Met() = default;

  double pt()  const {return m_pt;};
  double phi() const {return m_phi;};

  void set_pt(double x) {m_pt = x;};
  void set_phi(double x){m_phi = x;};


protected:
  double m_pt = 0.;
  double m_phi = 0.;

};
