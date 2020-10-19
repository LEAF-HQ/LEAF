#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "$MYANALYSISNAME/include/$MYEVENTCLASS.h"
#include "include/BaseHists.h"

using namespace std;

class $MYHISTNAME : public BaseHists{

public:
  // Constructors, destructor
  $MYHISTNAME(TString dir_);
  $MYHISTNAME(const $MYHISTNAME &) = default;
  $MYHISTNAME & operator = (const $MYHISTNAME &) = default;
  ~$MYHISTNAME() = default;

  // Main functions
  void fill(const $MYEVENTCLASS & event);


protected:

  shared_ptr<TH1D> hmetpt, hmetphi, hsumweights;

};
