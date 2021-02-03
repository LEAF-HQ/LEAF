#pragma once


// Container class for GenInfo
class GenInfo {

public:
  // Constructors, destructor
  GenInfo() = default;
  GenInfo(const GenInfo &) = default;
  GenInfo & operator = (const GenInfo &) = default;
  ~GenInfo() = default;

  std::vector<float> systweights_pdf() const {return m_systweights_pdf;};
  std::vector<float> systweights_scale() const {return m_systweights_scale;};
  float originalXWGTUP() const {return m_originalXWGTUP;};
  float binvar() const {return m_binvar;};
  int   id1() const {return m_id1;};
  int   id2() const {return m_id2;};
  float scale_pdf() const {return m_scale_pdf;};
  float weight() const {return m_weight;};
  float x1() const {return m_x1;};
  float x2() const {return m_x2;};
  float xpdf1() const {return m_xpdf1;};
  float xpdf2() const {return m_xpdf2;};

  void set_systweights_pdf(std::vector<float> x) {m_systweights_pdf = x;};
  void set_systweights_scale(std::vector<float> x) {m_systweights_scale = x;};
  void set_originalXWGTUP(float x) {m_originalXWGTUP = x;};
  void set_binvar(float x) {m_binvar = x;};
  void set_id1(int   x) {m_id1 = x;};
  void set_id2(int   x) {m_id2 = x;};
  void set_scale_pdf(float x) {m_scale_pdf = x;};
  void set_weight(float x) {m_weight = x;};
  void set_x1(float x) {m_x1 = x;};
  void set_x2(float x) {m_x2 = x;};
  void set_xpdf1(float x) {m_xpdf1 = x;};
  void set_xpdf2(float x) {m_xpdf2 = x;};


protected:
  std::vector<float> m_systweights_pdf, m_systweights_scale;
  float m_originalXWGTUP;
  float m_binvar;
  int   m_id1;
  int   m_id2;
  float m_scale_pdf;
  float m_weight;
  float m_x1;
  float m_x2;
  float m_xpdf1;
  float m_xpdf2;

};
