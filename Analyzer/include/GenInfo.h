#pragma once


// Container class for GenInfo
class GenInfo {

public:
  // Constructors, destructor
  GenInfo() = default;
  GenInfo(const GenInfo &) = default;
  GenInfo & operator = (const GenInfo &) = default;
  ~GenInfo() = default;

  // std::vector<double> systweights_pdf() const {return m_systweights_pdf;};
  // std::vector<double> systweights_scale() const {return m_systweights_scale;};
  std::vector<double> systweights() const {return m_systweights;};
  double originalXWGTUP() const {return m_originalXWGTUP;};
  // double binvar() const {return m_binvar;};
  int   id1() const {return m_id1;};
  int   id2() const {return m_id2;};
  double scale_pdf() const {return m_scale_pdf;};
  double weight() const {return m_weight;};
  double x1() const {return m_x1;};
  double x2() const {return m_x2;};
  double xpdf1() const {return m_xpdf1;};
  double xpdf2() const {return m_xpdf2;};

  // void set_systweights_pdf(std::vector<double> x) {m_systweights_pdf = x;};
  // void set_systweights_scale(std::vector<double> x) {m_systweights_scale = x;};
  void set_systweights(std::vector<double> x) {m_systweights = x;};
  void set_originalXWGTUP(double x) {m_originalXWGTUP = x;};
  // void set_binvar(double x) {m_binvar = x;};
  void set_id1(int   x) {m_id1 = x;};
  void set_id2(int   x) {m_id2 = x;};
  void set_scale_pdf(double x) {m_scale_pdf = x;};
  void set_weight(double x) {m_weight = x;};
  void set_x1(double x) {m_x1 = x;};
  void set_x2(double x) {m_x2 = x;};
  void set_xpdf1(double x) {m_xpdf1 = x;};
  void set_xpdf2(double x) {m_xpdf2 = x;};


protected:
  // std::vector<double> m_systweights_pdf, m_systweights_scale;
  std::vector<double> m_systweights; //
  double m_originalXWGTUP; //
  // double m_binvar;
  int   m_id1; //
  int   m_id2; //
  double m_scale_pdf; //
  double m_weight; //
  double m_x1; //
  double m_x2; //
  double m_xpdf1; //
  double m_xpdf2; //

};
