// Taken from https://github.com/UHH2/UHH2/blob/RunII_102X_v2/common/include/BTagCalibrationStandalone.h

#pragma once
#include <string>
#include <TF1.h>
#include <TH1.h>
#include <map>
#include <vector>
#include <istream>
#include <ostream>
#include <memory>

/**
*
* BTagEntry
*
* Represents one pt- or discriminator-dependent calibration function.
*
* measurement_type:    e.g. comb, ttbar, di-mu, boosted, ...
* sys_type:            e.g. central, plus, minus, plus_JEC, plus_JER, ...
*
* Everything is converted into a function, as it is easiest to store it in a
* txt or json file.
*
************************************************************/



class BTagEntry{

public:
  enum OperatingPoint {
    OP_LOOSE=0,
    OP_MEDIUM=1,
    OP_TIGHT=2,
    OP_RESHAPING=3,
  };

  enum JetFlavor {
    FLAV_B=5,
    FLAV_C=4,
    FLAV_UDSG=0,
  };

  OperatingPoint StringToOP(std::string op_string){
    if(op_string == "L") return OperatingPoint::OP_LOOSE;
    else if(op_string == "M") return OperatingPoint::OP_MEDIUM;
    else if(op_string == "T") return OperatingPoint::OP_TIGHT;
    else if(op_string == "shape") return OperatingPoint::OP_RESHAPING;
    else throw std::runtime_error("In BTagCalibrationStandalone.h: Invalid operating point given, must be L, M, T, or shape.");
  }

  struct Parameters {
    OperatingPoint operatingPoint;
    std::string measurementType;
    std::string sysType;
    JetFlavor jetFlavor;
    float etaMin;
    float etaMax;
    float ptMin;
    float ptMax;
    float discrMin;
    float discrMax;

    // default constructor
    Parameters(
      OperatingPoint op=OP_TIGHT,
      std::string measurement_type="comb",
      std::string sys_type="central",
      JetFlavor jf=FLAV_B,
      float eta_min=-99999.,
      float eta_max=99999.,
      float pt_min=0.,
      float pt_max=99999.,
      float discr_min=0.,
      float discr_max=99999.
    );
  };

  BTagEntry() {}
  BTagEntry(const std::string &csvLine);
  BTagEntry(const std::string &func, Parameters p);
  BTagEntry(const TF1* func, Parameters p);
  BTagEntry(const TH1* histo, Parameters p);
  ~BTagEntry() {}
  static std::string makeCSVHeader();
  std::string makeCSVLine() const;
  static std::string trimStr(std::string str);

  // public, no getters needed
  std::string formula;
  Parameters params;

};

/**
* BTagCalibration
*
* The 'hierarchy' of stored information is this:
* - by tagger (BTagCalibration)
*   - by operating point or reshape bin
*     - by jet parton flavor
*       - by type of measurement
*         - by systematic
*           - by eta bin
*             - as 1D-function dependent of pt or discriminant
*
************************************************************/


class BTagCalibration{
public:
  BTagCalibration(){};
  BTagCalibration(const std::string &filename);
  ~BTagCalibration(){}

  // std::string tagger() const {return tagger_;}

  void addEntry(const BTagEntry &entry);
  const std::vector<BTagEntry>& getEntries(const BTagEntry::Parameters &par) const;

  void readCSV(std::istream &s);
  void readCSV(const std::string &s);
  void makeCSV(std::ostream &s) const;
  std::string makeCSV() const;

protected:
  static std::string token(const BTagEntry::Parameters &par);

  // std::string tagger_;
  std::map<std::string, std::vector<BTagEntry> > data_;

};


/**
* BTagCalibrationReader
*
* Helper class to pull out a specific set of BTagEntry's out of a
* BTagCalibration. TF1 functions are set up at initialization time.
*
************************************************************/



class BTagCalibrationReader{
public:
  BTagCalibrationReader();
  BTagCalibrationReader(BTagEntry::OperatingPoint op, const std::string & sysType="central", const std::vector<std::string> & otherSysTypes={});
  ~BTagCalibrationReader();
  void load(const BTagCalibration & c, BTagEntry::JetFlavor jf, std::string measurementType="comb");
  double eval(BTagEntry::JetFlavor jf, float eta, float pt, float discr=0.) const;
  double eval_auto_bounds(const std::string & sys, BTagEntry::JetFlavor jf, float eta, float pt, float discr=0.) const;
  std::pair<float, float> min_max_pt(BTagEntry::JetFlavor jf, float eta, float discr=0.) const;
  std::pair<float, float> min_max_eta(BTagEntry::JetFlavor jf, float discr=0.) const;

protected:
  class BTagCalibrationReaderImpl;
  std::unique_ptr<BTagCalibrationReaderImpl> pimpl;
};
