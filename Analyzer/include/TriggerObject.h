#pragma once


using namespace std;

class TriggerObject{

public:

  enum ID{
    Undefined = 0,
    Electron  = 11,
    Photon    = 22,
    Muon      = 13,
    Tau       = 15,
    Jet       = 1,
    FatJet    = 6,
    MET       = 2,
    HT        = 3,
    MHT       = 4,
  };

  TriggerObject(){
    m_id = Undefined;
    m_filter_bits = 0;
    m_pt = -1.;
    m_eta = -1.;
    m_phi = -1.;
    m_l1pt = -1.;
    m_l1pt2 = -1.;
    m_l1iso = -1;
    m_l1charge = -1;
    m_l2pt = -1.;
  }


  ID id(){return m_id;};
  int filter_bits(){return m_filter_bits;};
  double pt(){return m_pt;};
  double eta(){return m_eta;};
  double phi(){return m_phi;};
  double l1pt(){return m_l1pt;};
  double l1pt2(){return m_l1pt2;};
  int l1iso(){return m_l1iso;};
  int l1charge(){return m_l1charge;};
  double l2pt(){return m_l2pt;};

  void set_id(ID x){m_id = x;};
  void set_filter_bits(int x){m_filter_bits = x;};
  void set_pt(double x){m_pt = x;};
  void set_eta(double x){m_eta = x;};
  void set_phi(double x){m_phi = x;};
  void set_l1pt(double x){m_l1pt = x;};
  void set_l1pt2(double x){m_l1pt2 = x;};
  void set_l1iso(int x){m_l1iso = x;};
  void set_l1charge(int x){m_l1charge = x;};
  void set_l2pt(double x){m_l2pt = x;};

protected:
  ID m_id;
  int m_filter_bits;
  double m_pt;
  double m_eta;
  double m_phi;
  double m_l1pt;
  double m_l1pt2;
  int m_l1iso;
  int m_l1charge;
  double m_l2pt;


};
